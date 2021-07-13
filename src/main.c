#include "wincat.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{

    if (argc < 2) {
        fprintf(stderr,"usage : %s -h/--help\n", argv[0]);
        return (1);
    }

    WSADATA wsa = {0};
    SetConsoleCP(CP_UTF8); // set UTF-8 in Console
    SetConsoleOutputCP(CP_UTF8); // set UTF-8 in Console output

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); // Set console color

    // Initialize Winsock 2.2
    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        fprintf(stderr,"[-] Error in WSAStartup()");
        return (1);
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
        show_help();

    for (uint8_t i = 0; i < 5; i++) {

        for (uint8_t x = 0; table[i].message[x]; x++) {
            if (strcmp(table[i].message[x], argv[1]) == 0) {
                if (argc < 5)
                    table[i].func(argv[2], atoi(argv[3]), NULL);
                else
                    table[i].func(argv[2], atoi(argv[3]), argv[4]);
            }
        }
    }

    WSACleanup();

    return (0);
}