#include <iostream>
#include <thread>
#include <algorithm>
#include <program1.hxx>
#include <program2.hxx>
#include <sys/socket.h>

int main() {
    CreateData cd;
    ValidateData valid(cd);

    std::thread reconnect_stream(&ValidateData::reconnect,
                                     valid,
                                     std::ref(valid.client_socket),
                                     std::ref(valid.server_address));

    while (true) {
        int valread = ::read(valid.client_socket, 
                                valid.buffer, 
                                2048);
        if (valread > 0) {
            std::cout << valid.buffer << "\n";

            valid.validate();
        }
        else if (valread == 0) {
            std::cout << "Server disconnected.\n";
            valid.reconnect(valid.client_socket, valid.server_address);
        }
        std::fill(std::begin(valid.buffer), std::end(valid.buffer), 0);
    }

    reconnect_stream.join();
    close(valid.client_socket);
    return 0;
}