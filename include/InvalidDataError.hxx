#ifndef INVALID_DATA_CLASS_HXX
#define INVALID_DATA_CLASS_HXX 20

#include <string>

class InvalidData {
    private:
        std::string mes;
    public:
        InvalidData(std::string _mes = "Invalid data.") : mes(_mes) {};
        const char* what() const throw() {
            return mes.c_str();
        }
};

#endif // INVALID_DATA_CLASS_HXX