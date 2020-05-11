#include "kernelmodule.h"

KernelModule::KernelModule()
{
    this->module = GetModuleHandleA("kernel32.dll");
    this->loadLibraryAddr = nullptr;
}

bool KernelModule::loadLibrary(Process p, LPVOID param, HANDLE & handle) {
    if(this->module != nullptr) {
        if(this->loadLibraryAddr == nullptr) {
            this->loadLibraryAddr = reinterpret_cast<LPVOID>(GetProcAddress(this->module, "LoadLibraryA"));
            if(this->loadLibraryAddr == nullptr) {
                this->error = "cannot get address from LoadLibraryA";
                return false;
            }
        }

        if(p.getHandle() == nullptr) {
            this->error = "Invalid handle";
            return false;
        }

        handle = CreateRemoteThread(p.getHandle(), nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(this->loadLibraryAddr), param, NULL, nullptr);
        if(handle == nullptr) {
            this->error = "Cannot create remote thread. GLE: " + QString::number(GetLastError());
            return false;
        }

        return true;
    }

    this->error = "Cannot get handle for kernel32.dll";
    return false;
}

QString KernelModule::getLastError() {
    return this->error;
}
