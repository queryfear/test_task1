#ifndef PROGRAM2_HXX
#define PROGRAM2_HXX

#include <string>
#include <program1.hxx>

class ValidateData {
    private:
        std::string odd_hash;
        int stream_value;
        CreateData cd;

    public:
        ValidateData() {
             odd_hash = cd.getHash();
             stream_value = cd.second_stream(odd_hash); 
        }
        ValidateData(std::string _odd_hash);
        ValidateData(CreateData &_Cd);

        int             validate();
        int             validate(int stream_value);
        std::string     getHash() const;
        int             getStreamValue() const;
};

#endif // PROGRAM2_HXX