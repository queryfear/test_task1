#include <iostream>
#include <thread>
#include <program2.hxx>
#include <InvalidDataError.hxx>

ValidateData::ValidateData(std::string _odd_hash) {
    odd_hash = _odd_hash;
    stream_value = cd.second_stream(odd_hash);
}

ValidateData::ValidateData(CreateData &_Cd) {
    odd_hash = _Cd.getHash();
    stream_value = _Cd.second_stream(odd_hash);
}

int ValidateData::validate() {
    int local_stream_value = cd.second_stream();
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