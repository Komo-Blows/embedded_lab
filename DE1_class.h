#ifndef DE1_CLASS_H
#define DE1_CLASS_H

class DE1_Class {
    private:
        char *pBase;
        int fd;
    public:
        DE1_Class();
        ~DE1_Class();
        void RegisterWrite(unsigned int offset, int value);
        int RegisterRead(unsigned int offset);
};

#endif
