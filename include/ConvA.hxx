#ifndef CONVA_HXX
#define CONVA_HXX 20

#include <string>

namespace ConvertAssistant {
    char        to_upper(char _char);
    bool        is_digit(char _char);
    int         to_digit(char _char);
    template<typename T>
    void        swap(T &first, T &second);
    int         partition(std::string &user_str, int start, int end);
    void        quick_sort(std::string &user_str, int start, int end);
    void        reverse(std::string &user_str);
}

#endif // CONVA_HXX