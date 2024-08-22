#include <iostream>
#include <netinet/in.h>
#include <program1.hxx>
#include <program2.hxx>
#include <thread>

#define PORT 8080

using namespace std;

int main() {
    CreateData cd;
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_addr_len = sizeof(client_address);

    if ((server_socket = ::socket(AF_INET, 
                                SOCK_STREAM,
                                 0)) == -1) {
        std::cerr << "Failed to create server socket.\n";
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = ::htons(PORT);

    if (::bind(server_socket, 
            (struct sockaddr*)&server_address, 
            sizeof(server_address)) == -1) {
        std::cerr << "Failed to bind server socket.\n";
        ::close(server_socket);
        return -1;
    }

    if (::listen(server_socket, 5) == -1) {
        std::cerr << "Failed to listen.\n";
        ::close(server_socket);
        return -1;
    }

    std::cout << "Server listening on port " << PORT << '\n';

    if ((client_socket = ::accept(server_socket, 
                                (struct sockaddr*)&client_address,
                                 &client_addr_len)) == -1) {
        std::cerr << "Error accepting client connection\n";
        return -1;
    }

    std::cout << "Client connected.\n";

    std::thread t1([&]{
            while(true) {
                cd.first_stream();
            }
        });

    std::thread t2([&]{
        while(true) {
            cd.second_stream(std::ref(server_socket), 
                                            std::ref(client_socket));
        }
    });


    t1.join();
    t2.join();

    close(client_socket);
    close(server_socket);
}