#ifndef DE1_H
#define DE1_H

/**
 * @class DE1
 * @brief Base class for interfacing with DE1-SoC FPGA devices through memory-mapped I/O access via the Linux /dev/mem interface
 */
class DE1 {
    private:
        char *pBase;  ///< Virtual base address for memory-mapped I/O
        int fd;       ///< File descriptor for /dev/mem
        
    protected:
        static const unsigned int HEX3_HEX0_BASE = 0x00000020; ///< HEX displays 0-3 register offset
        static const unsigned int HEX5_HEX4_BASE = 0x00000030; ///< HEX displays 4-5 register offset
        
    public:
        /**
         * @brief Constructor that initializes memory-mapped I/O by opening /dev/mem and mapping FPGA physical addresses to virtual memory for direct hardware access
         */
        DE1();
        
        /**
         * @brief Destructor that cleans up memory mappings by unmapping the virtual memory region and closing the file descriptor
         */
        ~DE1();
        
        /**
         * @brief Write a 32-bit value to the specified register offset in the FPGA's memory-mapped I/O space
         * @param offset Register offset from base address
         * @param value Value to write to the register
         */
        void RegisterWrite(unsigned int offset, int value);
        
        /**
         * @brief Read a 32-bit value from the specified register offset in the FPGA's memory-mapped I/O space
         * @param offset Register offset from base address
         * @return Value read from the register
         */
        int RegisterRead(unsigned int offset);
};

#endif