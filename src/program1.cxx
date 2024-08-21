#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <program1.hxx>
#include <ConvA.hxx>

// #if defined(__GNUC__)
//     #pragma GCC optimize ("O3")
// #endif

CreateData::CreateData(CreateData &_Cd) {
    base = _Cd.getBase();
    odd_hash = _Cd.getHash();
    buffer = _Cd.getBuffer();
}

bool CreateData::program1_spell(const std::string &user_str) {
    const int userstr_len = user_str.size() / 2;
    constexpr int limit = 64;

    if (userstr_len > limit) return false;

    for (int i = 0; i <= userstr_len; ++i) {
        if (ConvertAssistant::is_digit(user_str[i]) == false || 
            ConvertAssistant::is_digit(user_str[user_str.size() - 1 - i]) == false) 
            return false;
    }
    return true;
}

std::string CreateData::retrieve(std::queue<std::string> &cont) {
    std::unique_lock<std::mutex> grd(mtx);
    
    // if (!cont.empty()) {
    //     value = cont.front();
    //     cont.pop();
    // }

    // &lock == unique_lock, p == waits for true
    cv.wait(grd, [&cont]{
        return !cont.empty();
    });

    std::string value = cont.front();
    cont.pop();

    return value;
}

void CreateData::push(std::queue<std::string> &cont, std::string val) {
    std::lock_guard<std::mutex> grd(mtx);
    cont.push(val);
    cv.notify_one();
}

std::string CreateData::first_stream(std::string user_str) {
    std::vector<std::string> latin_vector;
    std::string result_temp = "";
    
    if (user_str == "") std::cin >> user_str;
    if (program1_spell(user_str) == false) return "0";

    base = user_str;

    ConvertAssistant::quick_sort(user_str, 0, user_str.size() - 1);
    ConvertAssistant::reverse(user_str);

    for (int i = 0; i < user_str.size(); ++i) {
        if ((user_str[i] - '0') % 2 == 0) latin_vector.push_back("KB");
        else {
            std::string temp = std::string(1, user_str[i]);   
            latin_vector.push_back(temp);
        }
    }

    for (int i = 0; i < user_str.size(); ++i) {
        result_temp += latin_vector[i];
    }

    user_str = result_temp;
    buffer = user_str;
    odd_hash = user_str;

    push(buffer_array, user_str);

    return user_str;
}

int CreateData::second_stream() {
    std::string _oddHash = "";
    do {
        std::string _oddHash = retrieve(buffer_array);
    } while (_oddHash.empty());
    
    return second_stream(_oddHash);
}

int CreateData::second_stream(std::string user_str) {
    int total = 0;
    for (int i = 0; i < user_str.size(); ++i) {
        if (ConvertAssistant::is_digit(user_str[i]) == true) {
            total += ConvertAssistant::to_digit(user_str[i]);
        }
        else i++;
    }
    
    return total;
}

std::string CreateData::getBase() const {
    return base;
}

std::string CreateData::getBuffer() const {
    return buffer;
}

std::string CreateData::getHash() const {
    return !odd_hash.empty() ? odd_hash : "KB";
}