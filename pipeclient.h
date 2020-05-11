#ifndef PIPECLIENT_H
#define PIPECLIENT_H

#include <Windows.h>
#include <QString>

#define BUFSIZE 512

class PipeClient
{
public:
    PipeClient();
    bool connect();
    bool disconnect();
    bool sendMessage(LPCTSTR msg);
    QString getLastError();

private:
    LPCTSTR pipeName;
    HANDLE handle;
    QString error;
};

#endif // PIPECLIENT_H
