#include "wincat.h"
#include <stdio.h>


uint8_t create_server(unsigned char *address, uint64_t port)
{
    SOCKET fd;
    struct sockaddr_in socks = {0};

    if ((fd = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
        return (1);
    
    socks.sin_addr.s_addr = inet_addr(address); // convert string address to network byte order
    socks.sin_port = htons(port); // convert port to network byte order
    socks.sin_family = AF_INET;

    if (bind(fd, (struct sockaddr *)&socks, sizeof(socks)) < 0)
        return (1);
    
    if (listen(fd, SOMAXCONN) < 0)
        return (1);
    
    printf("[+] Listening on port %s:%lld\n", address, port);

    wait_client(fd);

    return (0);
}


uint8_t create_server_execute_process(unsigned char *address, uint64_t port, unsigned char *process)
{
    SOCKET fd;
    struct sockaddr_in socks = {0};

    if ((fd = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
        return (1);
    
    socks.sin_addr.s_addr = inet_addr(address); // convert string address to network byte order
    socks.sin_port = htons(port);
    socks.sin_family = AF_INET;

    if (bind(fd, (struct sockaddr *)&socks, sizeof(socks)) < 0) {
        printf("[-] Error bind address and port : %s:%lld\n", address, port);
        return (1);
    }

    if (listen(fd, SOMAXCONN) < 0) {
        printf("[-] Error listen on %s:%lld\n", address, port);
        return (1);
    }

    printf("[+] Listening on port %s:%lld\n", address, port);

    wait_client_process(fd, process);
    
    return (0);
}

void wait_client(SOCKET fd)
{
    SOCKET cfd;
    struct sockaddr_in client = {0};
    int size_client = sizeof(client);

    while (1) {
        cfd = accept(fd, (struct sockaddr *)&client, &size_client);

        printf("[+] new connection received from : %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        if (HandleConnection(cfd))
            printf("[-] Error in HandleConnection()\n");

        closesocket(cfd);
    }
}

void wait_client_process(SOCKET fd, unsigned char *process)
{
    SOCKET client_fd;
    struct sockaddr_in client_info = {0};
    int size_client_info = sizeof(client_info);
    STARTUPINFOA sinfo;
    PROCESS_INFORMATION pinfo;

    while (1) {
        client_fd = accept(fd, (struct sockaddr *)&client_info, &size_client_info);

        sinfo.cb = sizeof(sinfo);
        sinfo.dwFlags = (STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES);
        sinfo.hStdError = (SOCKET)client_fd;
        sinfo.hStdInput = (SOCKET)client_fd;
        sinfo.hStdOutput = (SOCKET)client_fd;

        printf("[+] new connection received from : %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
        printf("[+] wait moment creating process....\n");

        if (CreateProcessA(NULL, process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo)) {
            printf("[+] Process created with pid : %d\n", pinfo.dwProcessId);

            WaitForSingleObject(pinfo.hProcess, INFINITE);

            printf("[+] Process killed with pid : %d\n", pinfo.dwProcessId);
            CloseHandle(pinfo.hThread);
            CloseHandle(pinfo.hProcess);
        }

        closesocket(client_fd);
        printf("[+] connection closed : %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
    }
}