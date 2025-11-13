#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

class DE1{
public:
        // Physical base address of FPGA Devices
        static const unsigned int LW_BRIDGE_BASE       = 0xFF200000;  // Base offset
        // Length of memory-mapped IO window
        static const unsigned int LW_BRIDGE_SPAN       = 0x00005000;  // Address map size
        // Cyclone V FPGA device addresses
        static const unsigned int LEDR_BASE            = 0x00000000;  // Leds offset
        static const unsigned int SW_BASE              = 0x00000040;  // Switches offset
        static const unsigned int KEY_BASE             = 0x00000050;  // Push buttons offset

        char *pBase;
        int fd;

        DE1(){
                // Open /dev/mem to give access to physical addresses
                fd = open( "/dev/mem", (O_RDWR | O_SYNC));
                if (fd == -1)                  //  check for errors in openning /dev/mem
                {
                cout << "ERROR: could not open /dev/mem..." << endl;
                exit(1);
                }

                // Get a mapping from physical addresses to virtual addresses
                        char *virtual_base = (char *)mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
                        if (virtual_base == MAP_FAILED)              // check for errors
                {
                cout << "ERROR: mmap() failed..." << endl;
                close (fd);              // close memory before exiting
                exit(1);        // Returns 1 to the operating system;
                }
                pBase = virtual_base;
        }
        ~DE1(){
                if (munmap (pBase, LW_BRIDGE_SPAN) != 0)
                {
                cout << "ERROR: munmap() failed..." << endl;
                exit(1);
                }
                close (fd);  // close memory
        }

        /**
        * Write a 4-byte value at the specified general-purpose I/O location.
        *
        * @param pBase         Base address returned by 'mmap'.
        * @parem offset        Offset where device is mapped.
        * @param value Value to be written.
        */
        void RegisterWrite(unsigned int reg_offset, int value)
        {
        * (volatile unsigned int *)(pBase + reg_offset) = value;
        }

        /**
        * Read a 4-byte value from the specified general-purpose I/O location.
        *
        * @param pBase         Base address returned by 'mmap'.
        * @param offset        Offset where device is mapped.
        * @return              Value read.
        */
        int RegisterRead(unsigned int reg_offset)
        {
                return * (volatile unsigned int *)(pBase + reg_offset);
        }


};


class LedControl{
public:
        LedControl(){}
        /**
        * Show the input integer value on LEDs
        *
        * - Calls RegisterWrite to set all LEDs
        * @param value Value to show on LEDs
        */
        void WriteAllLeds(DE1 de1, int value)
        {
                de1.RegisterWrite(de1.LEDR_BASE, value);
        }


        void WriteOneLed(DE1 de1, int LedNum, int state){
                int current_reg = de1.RegisterRead(de1.LEDR_BASE);
                int two_pow_lednum = 2;
                for (int i = 1; i<LedNum; i+=1){two_pow_lednum *= 2;} //exponentiation
                int new_reg = current_reg & two_pow_lednum;
                de1.RegisterWrite(de1.LEDR_BASE, current_reg);
        }


        int ReadAllSwitches(DE1 de1){
                return de1.RegisterRead(de1.SW_BASE);
        }

        int ReadOneSwitch(DE1 de1, int k){
                int j = de1.RegisterRead(de1.SW_BASE);
                int bit_value = (j >> k) & 1;
                return bit_value;
        }
};


// int PushButtonGet(char *pBase){
//         int i = RegisterRead(pBase, KEY_BASE);
//         switch (i){
//                 case 0: return -1;
//                 case 1: return 0;
//                 case 2: return 1;
//                 case 4: return 2;
//                 case 8: return 3;
//                 default: return 4;
//         }
// }
int main()
{
        DE1 my_de1 = DE1();
        LedControl my_led = LedControl();
        my_led.WriteAllLeds(my_de1, 1023);
        // // Initialize
        // int fd;
        // char *pBase = Initialize(&fd);

        // int i = ReadAllSwitches(pBase);
        // int save = -1;
        // WriteAllLeds(pBase, i);
        // while (true){
        //         int newin = PushButtonGet(pBase);
        //         if (newin != save){
        //         if (save == 4) {save = newin; continue;}
        //         save = newin;
        //         switch (save){
        //                 case -1: break;
        //                 case 0: i += 1; break;
        //                 case 1: i -= 1; break;
        //                 case 2: i >>= 1; break;
        //                 case 3: i <<= 1; break;
        //                 case 4: i = ReadAllSwitches(pBase); break;
        //                 }
        //         WriteAllLeds(pBase, i);
        //         }
        // }

};
