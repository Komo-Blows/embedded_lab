#ifndef DE1_H
#define DE1_H

class DE1 {
    private:
        char *pBase;
        int fd;
    protected:
        const unsigned int HEX3_HEX0_BASE = 0x00000020; // HEX Reg1 offset
        const unsigned int HEX5_HEX4_BASE = 0x00000030; // HEX Reg2 offset
    public:
        DE1();
        ~DE1();
        void RegisterWrite(unsigned int offset, int value);
        int RegisterRead(unsigned int offset);
};

#endif
