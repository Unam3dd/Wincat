#include "wincat.h"
#include <stdio.h>
#include "pthread.h"

void *ThreadStream(void *ptr)
{
    stream_t s = *(stream_t *)ptr;
    int bytes = 0;
    unsigned char buffer[0xFFFF] = {0};

    while ((bytes = read(s.in, buffer, 0xFFFE))) {
        
        if (send(s.out, buffer, bytes, 0) < 0) {
            fprintf(stderr,"[-] Error send data to the fd !\n");
            break;
        }
    }

    if (bytes < 0)
        fprintf(stderr,"[-] Error reading STDIN !\n");

    return (NULL);
}

uint8_t HandleConnection(SOCKET fd)
{
    pthread_t thread;
    stream_t s = {0};
    unsigned long nonblock = -1;
    unsigned char buffer[0xFFFF] = {0};
    int bytes = 0;

    if (ioctlsocket(fd, FIONBIO, &nonblock) < 0) {
        fprintf(stderr, "[-] Error ioctlsocket()");
        return (1);
    }
    
    s.in = 0;
    s.out = fd;

    if (pthread_create(&thread, NULL, ThreadStream, (void *)&s))
        return (1);
    
    for (;;) {
        while ((bytes = recv(fd, buffer, 0xFFFE, 0)) > 0)
        {
            
            if (write(1, buffer, bytes) < 0) {
                fprintf(stderr,"[-] Error write stream in file descriptor !\n");
                pthread_cancel(thread);
                pthread_join(thread, NULL);
                return (1);
            }

        }
    }
    
    return (0);
}