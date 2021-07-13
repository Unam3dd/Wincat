#include "wincat.h"

const lookup_table_t table[] = {
    { {"--listen", "-l"}, &create_server},
    { {"--connect", "-c"}, &client_connect},
    { {"--connect-process", "-cp"}, &client_connect_execute_process},
    { {"--server_process", "-sp"}, &create_server_execute_process},
    { {"--server", "-s"}, &create_server},
};