#ifndef KERNELMODULE_H
#define KERNELMODULE_H

#include <Windows.h>
#include <QString>
#include "process.h"

class KernelModule
{
public:
    KernelModule();
    bool loadLibrary(Process p, LPVOID param, HANDLE & handle);
    QString getLastError();

private:
    LPVOID loadLibraryAddr;
    HMODULE module;
    QString error;
};

#endif // KERNELMODULE_H
