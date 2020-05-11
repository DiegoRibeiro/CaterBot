#ifndef PIPETHREAD_H
#define PIPETHREAD_H

#include <Windows.h>
#include "pipeserver.h"

class PipeThread
{
public:
    PipeThread();
    bool start();
    QString getLastError();

private:
    HANDLE handle;
    DWORD threadId;
    QString error;
};

#endif // PIPETHREAD_H
