#include "DE1.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;

// Physical base address of FPGA Devices
static const unsigned int LW_BRIDGE_BASE = 0xFF200000;  // Base offset
// Length of memory-mapped IO window
static const unsigned int LW_BRIDGE_SPAN = 0x00005000;  // Address map size

DE1::DE1() {
    // Open /dev/mem to give access to physical addresses
    fd = open("/dev/mem", (O_RDWR | O_SYNC));
    if (fd == -1) {
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
    }

    // Get a mapping from physical addresses to virtual addresses
    char *virtual_base = (char *)mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (virtual_base == MAP_FAILED) {
        cout << "ERROR: mmap() failed..." << endl;
        close(fd);
        exit(1);
    }
    pBase = virtual_base;
}

DE1::~DE1() {
    if (munmap(pBase, LW_BRIDGE_SPAN) != 0) {
        cout << "ERROR: munmap() failed..." << endl;
        exit(1);
    }
    close(fd);
}

/**
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * @param offset    Offset where device is mapped.
 * @param value     Value to be written.
 */
void DE1::RegisterWrite(unsigned int reg_offset, int value) {
    *(volatile unsigned int *)(pBase + reg_offset) = value;
}

/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * @param offset    Offset where device is mapped.
 * @return          Value read.
 */
int DE1::RegisterRead(unsigned int reg_offset) {
    return *(volatile unsigned int *)(pBase + reg_offset);
}