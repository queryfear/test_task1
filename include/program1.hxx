#ifndef PROGRAM1_HXX
#define PROGRAM1_HXX 20

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <InvalidDataError.hxx>

class CreateData {
    private:
        std::string                     base;
        std::string                     odd_hash;
        std::queue<std::string>         buffer_array;
        mutable std::queue<std::string> to_valid;
        // mutable std::queue<int>      to_valid;
        std::string                     buffer;
        std::mutex                      mtx;
        std::condition_variable         cv;

    public:
        CreateData(): base(""), buffer(""), odd_hash("") {};
        CreateData(std::string _base): base(_base), buffer(""), odd_hash("") {};
        CreateData(CreateData &_Cd);

        bool                       program1_spell(const std::string &user_str);
        std::string                first_stream() { return first_stream(base); };
        std::string                first_stream(std::string user_str);

        int                        second_stream(int &server_socket, 
                                                 int &client_socket);
        int                        second_stream(std::string user_str, 
                                                 int &server_socket, 
                                                 int &client_socket);

        template<typename T>
        T                          retrieve(std::queue<T> &cont);
        template<typename T>
        void                       push(std::queue<T> &cont, T val);

        std::string                getBuffer() const;
        std::string                getBase() const;
        std::string                getHash() const;
        std::queue<std::string>&   getToValid() const;

};

#endif // PROGRAM1_HXX