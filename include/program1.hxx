#ifndef PROGRAM1_HXX
#define PROGRAM1_HXX 20

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

class CreateData {
    private:
        std::string base;
        std::string odd_hash;
        std::queue<std::string> buffer_array;
        std::string buffer;
        std::mutex mtx;
        std::condition_variable cv;

    public:
        CreateData(): base(""), odd_hash(""), buffer("")  {};
        CreateData(std::string _base): base(_base), odd_hash(""), buffer("") {};
        CreateData(CreateData &_Cd);

        bool               program1_spell(const std::string &user_str);
        std::string        first_stream() { return first_stream(base); };
        std::string        first_stream(std::string user_str);

        int                second_stream();
        int                second_stream(std::string user_str);

        std::string        retrieve(std::queue<std::string> &cont);
        void               push(std::queue<std::string> &cont, std::string val);

        std::string        getBuffer() const;
        std::string        getBase() const;
        std::string        getHash() const;
};

#endif // PROGRAM1_HXX