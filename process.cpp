#include "process.h"
#include <iostream>

Process::Process(QString name)
{
    this->name = name;
    this->handle = nullptr;
}

bool Process::open() {
    PROCESSENTRY32 entry;

    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            QString szExeFile = QString::fromWCharArray(entry.szExeFile);
            if (QString::compare(name, szExeFile, Qt::CaseInsensitive) == 0) {
                CloseHandle(snapshot);
                this->handle = OpenProcess(CREATE_THREAD_ACCESS, FALSE, entry.th32ProcessID);
                return true;
            }
        }
        CloseHandle(snapshot);
        this->error = "Couldn't find process";
        return false;
    }
    CloseHandle(snapshot);
    this->error = "Cannot copy process to buffer";
    return false;
}

void Process::close() {
    if(this->handle != nullptr)
        CloseHandle(this->handle);
}

void Process::free() {
    VirtualFreeEx(this->handle, this->reservedAddress, 0, MEM_RELEASE);
}

bool Process::alloc(SIZE_T size) {
    if(this->handle != nullptr) {
        reservedAddress = reinterpret_cast<LPVOID>(VirtualAllocEx(this->handle, nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));

        if(reservedAddress == nullptr) {
            this->error = "Cannot alocate memory";
            return false;
        }
        return true;
    }

    this->error = "use the function open to get a valid handle";
    return false;
}

bool Process::writeMemory(QString str) {
    std::cout << str.toStdString() << std::endl;
    int iResult = WriteProcessMemory(this->handle, this->reservedAddress, str.toStdString().c_str(), strlen(str.toStdString().c_str()) + 1, nullptr);
    if(iResult == 0) {
        this->error = "Cannot write in memory: " + QString::number(GetLastError());
        return false;
    }
    return true;
}

// getters and setters
HANDLE Process::getHandle() {
    return this->handle;
}
LPVOID Process::getReservedAddress() {
    return this->reservedAddress;
}

QString Process::getLastError() {
    return this->error;
}
