#ifndef DE1_H
#define DE1_H

class DE1 {
    private:
        char *pBase;
        int fd;
    public:
        DE1();
        ~DE1();
        void RegisterWrite(unsigned int offset, int value);
        int RegisterRead(unsigned int offset);
};

#endif
