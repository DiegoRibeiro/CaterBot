#ifndef PROCESS_H
#define PROCESS_H

#define WIN32_LEAN_AND_MEAN
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)

#include<Windows.h>
#include <QString>
#include <TlHelp32.h>


class Process
{
public:
    Process(QString name);
    bool open();
    void close();
    bool alloc(SIZE_T size);
    QString getLastError();
    bool writeMemory(QString str);
    void free();
    HANDLE getHandle();
    LPVOID getReservedAddress();

private:
    QString name;
    HANDLE handle;
    LPVOID reservedAddress;
    QString error;
};

#endif // PROCESS_H
