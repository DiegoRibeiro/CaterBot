#ifndef REMOTETHREAD_H
#define REMOTETHREAD_H

#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include <QString>
#include "process.h"
#include "catermodule.h"
#include "kernelmodule.h"

class RemoteThread
{
public:
    RemoteThread();
    bool inject(Process p, CaterModule cm);
    QString getLastError();
    void shutdown();

private:
    KernelModule kernel;
    HANDLE handle;
    QString error;
};

#endif // REMOTETHREAD_H
