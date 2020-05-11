#include "pipeclient.h"
#include <iostream>

PipeClient::PipeClient()
{
    this->pipeName = TEXT("\\\\.\\pipe\\caterbot");
}

bool PipeClient::connect() {
    while (1)
    {
        this->handle = CreateFile(
            this->pipeName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        );

        if (this->handle != INVALID_HANDLE_VALUE)
            break;

        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            this->error = "Could not open pipe. GLE= " + QString::number(GetLastError());
            return false;
        }

        if ( ! WaitNamedPipe(this->pipeName, 20000))
        {
            this->error = "Could not open pipe: 20 second wait timed out.";
            return false;
        }
    }

    DWORD dwMode = PIPE_READMODE_MESSAGE;
    BOOL ret = SetNamedPipeHandleState(this->handle, &dwMode, nullptr, nullptr);

    if(!ret) {
        this->error = "SetNamedPipeHandleState failed. GLE= " + QString::number(GetLastError());
        return false;
    }

    return true;
}

bool PipeClient::sendMessage(LPCTSTR msg) {
    DWORD bytesSent;
    BOOL sent = WriteFile(this->handle, msg, (lstrlen(msg)+1)*sizeof(TCHAR), &bytesSent, nullptr);
    if(!sent) {
        this->error = "WriteFile to pipe failed. GLE= " + QString::number(GetLastError());
        return false;
    }

    BOOL receive = false;
    TCHAR  chBuf[BUFSIZE];
    DWORD bytesReceived;

    do {
        receive = ReadFile(this->handle, chBuf, BUFSIZE*sizeof(TCHAR), &bytesReceived, nullptr);
        if ( ! receive && GetLastError() != ERROR_MORE_DATA )
            break;

        std::cout << chBuf << std::endl;
    } while(!receive);

    if(!receive) {
        this->error = "ReadFile from pipe failed. GLE= " + QString::number(GetLastError());
        return false;
    }

    CloseHandle(this->handle);
    return true;
}

QString PipeClient::getLastError() {
    return this->error;
}
