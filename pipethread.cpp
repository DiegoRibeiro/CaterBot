#include "pipethread.h"
#include <iostream>

DWORD WINAPI runnable(LPVOID param) {
    PipeServer server;

    while(true) {
        std::cout << "listening ..." << std::endl;

        bool result = server.listen();
        if(!result) break;
    }

    std::cout << "terminating thread" << std::endl;
    return 1;
}

PipeThread::PipeThread()
{

}

QString PipeThread::getLastError() {
    return this->error;
}

bool PipeThread::start() {
    this->handle = CreateThread(nullptr, 0, runnable, (LPVOID) this->handle, 0, &this->threadId);

     if (this->handle == nullptr)
     {
        this->error = "CreateThread failed, GLE= " + QString::number(GetLastError());
        return false;
     }
     CloseHandle(this->handle);
     return true;
}
