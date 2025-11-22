#ifndef DE1_H
#define DE1_H

/**
 * @class DE1
 * @brief Base class for interfacing with DE1-SoC FPGA devices
 * 
 * This class provides memory-mapped I/O access to the DE1-SoC FPGA
 * hardware devices through the Linux /dev/mem interface. It manages
 * the initialization and cleanup of memory mappings.
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
         * @brief Constructor - initializes memory-mapped I/O
         * 
         * Opens /dev/mem and maps FPGA physical addresses to virtual memory.
         * This allows direct hardware access to FPGA peripherals.
         */
        DE1();
        
        /**
         * @brief Destructor - cleans up memory mappings
         * 
         * Unmaps the virtual memory region and closes the file descriptor.
         * This releases hardware resources properly.
         */
        ~DE1();
        
        /**
         * @brief Write a value to a hardware register
         * 
         * Writes a 32-bit value to the specified register offset in the
         * FPGA's memory-mapped I/O space.
         * 
         * @param offset Register offset from base address
         * @param value Value to write to the register
         */
        void RegisterWrite(unsigned int offset, int value);
        
        /**
         * @brief Read a value from a hardware register
         * 
         * Reads a 32-bit value from the specified register offset in the
         * FPGA's memory-mapped I/O space.
         * 
         * @param offset Register offset from base address
         * @return Value read from the register
         */
        int RegisterRead(unsigned int offset);
};

#endif