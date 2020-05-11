#include "remotethread.h"

RemoteThread::RemoteThread(): kernel()
{

}

bool RemoteThread::inject(Process p, CaterModule cm) {

    if(!p.alloc(cm.getLength())) {
        this->error = p.getLastError();
        return false;
    }

    if(!p.writeMemory(cm.getPath())) {
        this->error = p.getLastError();
        return false;
    }

    if(!kernel.loadLibrary(p, p.getReservedAddress(), this->handle)) {
        this->error = kernel.getLastError();
        return false;
    }

    return true;
}

void RemoteThread::shutdown() {
    CloseHandle(this->handle);
}

QString RemoteThread::getLastError() {
    return this->error;
}
