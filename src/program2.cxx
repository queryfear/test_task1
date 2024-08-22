#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <program2.hxx>
#include <InvalidDataError.hxx>

void ValidateData::reconnect(int &client_socket, struct sockaddr_in &server_addr) {
    ::close(client_socket);
    while (true) {
        std::cout << "Attempting to reconnect...\n";
        client_socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (::connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
            std::cout << "Reconnected to the server.\n";
            break;
        }
        ::close(client_socket);
        ::sleep(1);
    }
}

ValidateData::ValidateData(CreateData &_Cd) {
    odd_hash = _Cd.getHash();
    server_socket = _Cd.getServerSocket();

    server_address.sin_family = AF_INET;
    server_address.sin_port = ::htons(PORT);
    ::inet_pton(AF_INET, IP.c_str(), &server_address.sin_addr);

    while (true) {
        client_socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (::connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) >= 0) {
            std::cout << "Connected to the server";
            break;
        }
        else { 
            std::cerr << "Connection failed. Retying...\n";
            ::close(client_socket);
            ::sleep(1);
        }
    }
    
    stream_value = _Cd.second_stream(odd_hash, server_socket, client_socket);
}

int ValidateData::validate() {
    int local_stream_value = std::stoi(cd.retrieve(cd.getToValid()));

    return validate(local_stream_value); 
}

int ValidateData::validate(int stream_value) {
    constexpr int range = 10000;
    constexpr int invalid_range = 100;
    constexpr int valid_divisor = 32;

    try {
        if (stream_value % range < invalid_range) {
            throw InvalidData("\nData in stream_value have invalid value: stream_value not in invalid range\n");
        }
        else if (stream_value % valid_divisor != 0) {
            throw InvalidData("\nData in stream_value have invalid value: stream_value doesn't give 0 by dim 32\n");
        }
        else {
            std::cout << "======================================================\n\n"
                      << "Data in stream_value have valid value: " << stream_value 
                      << "\nHash: " << odd_hash 
                      << "\n\n======================================================\n";
            return stream_value;
        }
    }
    catch (const InvalidData& e) {
        std::cerr << e.what(); 
        return -1;
    }
}

std::string ValidateData::getHash() const {
    return odd_hash;
}

int ValidateData::getStreamValue() const {
    return stream_value;
}