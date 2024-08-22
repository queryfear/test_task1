#include <iostream>
#include <program1.hxx>
#include <program2.hxx>
#include <sys/socket.h>

int main() {
    int server_socket;
    if (server_socket = socket(AF_INET, SOCK_STREAM, 0) == 0) {
        std::cerr << "ERROR during trying to create socket.\n";
    }
}