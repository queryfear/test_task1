#ifndef PROGRAM2_HXX
#define PROGRAM2_HXX

#include <netinet/in.h>
#include <string>
#include <program1.hxx>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class ValidateData {
    private:
        static constexpr int         PORT = 8080;
        static constexpr std::string IP = "127.0.0.1";

        std::string                  odd_hash;
        int                          stream_value;
        CreateData                   cd;

    public:
        int                          client_socket;
        int                          server_socket;
        struct sockaddr_in           server_address;
        char                         buffer[2048] = {0};

        ValidateData(CreateData &_Cd);
        ~ValidateData() { ::close(client_socket); };

        int             validate();
        int             validate(int stream_value);
        void            reconnect(int &client_socket, struct sockaddr_in &server_address);
        std::string     getHash() const;
        int             getStreamValue() const;
};

#endif // PROGRAM2_HXX