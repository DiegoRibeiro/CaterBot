#include "pipeserver.h"
#include <iostream>

PipeServer::PipeServer()
{
    this->pipeName = TEXT("\\\\.\\pipe\\caterbot");
}

bool PipeServer::listen() {
    HANDLE hHeap      = GetProcessHeap();
    TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE*sizeof(TCHAR));
    TCHAR* pchReply   = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE*sizeof(TCHAR));
    BOOL quit = false;

    this->handle = CreateNamedPipe(
        this->pipeName, PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        BUFSIZE,
        BUFSIZE,
        0,
        nullptr);

    if (this->handle == INVALID_HANDLE_VALUE)
    {
        this->error = "CreateNamedPipe failed, GLE= " + QString::number(GetLastError());
        return false;
    }

    BOOL connected = ConnectNamedPipe(this->handle, nullptr);

    if(!connected) {
        this->error = "The client could not connect";
        CloseHandle(this->handle);
        return true;
    }
    else {
        DWORD bytesRead;
        BOOL success = ReadFile(this->handle, pchRequest, BUFSIZE*sizeof(TCHAR), &bytesRead, nullptr);

        if (!success || bytesRead == 0)
        {
            if (GetLastError() == ERROR_BROKEN_PIPE)
            {
                this->error = "InstanceThread: client disconnected.";
            }
            else
            {
              this->error = "InstanceThread ReadFile failed, GLE= " + QString::number(GetLastError());
            }
            return true;
        }

        DWORD pchBytes;
        std::wcout << "Client Request String: " << pchRequest << std::endl;
        QString cmd = QString::fromStdWString(pchRequest);

        if(cmd.compare("bye", Qt::CaseInsensitive) == 0) {
            quit = true;
        }

        if (FAILED(StringCchCopy(pchReply, BUFSIZE, TEXT("default answer from server")))) {
            pchBytes = 0;
            pchReply[0] = 0;
            this->error = "StringCchCopy failed, no outgoing message.";
            return true;
        }

        DWORD bytesWritten;
        pchBytes = (lstrlen(pchReply)+1)*sizeof(TCHAR);
        success = WriteFile(this->handle, pchReply, pchBytes, &bytesWritten, nullptr);

        if (!success || pchBytes != bytesWritten)
        {
            this->error = "InstanceThread WriteFile failed, GLE= " + QString::number(GetLastError());
            return true;
        }
    }

    FlushFileBuffers(this->handle);
    DisconnectNamedPipe(this->handle);
    CloseHandle(this->handle);

    HeapFree(hHeap, 0, pchRequest);
    HeapFree(hHeap, 0, pchReply);

    if(quit) {
        return false;
    }
    return true;
}
