#ifndef PIPESERVER_H
#define PIPESERVER_H

#include <Windows.h>
#include <QString>
#include <strsafe.h>

#define BUFSIZE 512

class PipeServer
{
public:
    PipeServer();
    bool listen();
    QString getLastError();

private:
    LPCTSTR pipeName;
    HANDLE handle;
    QString error;

};

#endif // PIPESERVER_H
