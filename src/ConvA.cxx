#include <ConvA.hxx>

char ConvertAssistant::to_upper(char _char) {
    _char = _char - 0;
    if (_char < 97 || _char > 122) return static_cast<char>(_char);
    return static_cast<char>(_char - 32);
}

bool ConvertAssistant::is_digit(char _char) {
    _char = _char - '0';
    if (_char < 0 || _char > 9) return false;
    return true;
}

int ConvertAssistant::to_digit(char _char) {
    if (is_digit(_char)) return _char - '0';
    else return 0;
}

template<typename T>
void ConvertAssistant::swap(T &first, T &second) {
    T temp = first;
    first = second;
    second = temp;
}

int ConvertAssistant::partition(std::string &user_str, int start, int end) {
    int pivot = user_str[end];
    int i = (start - 1);

    for (int j = start; j <= end - 1; j++) {
        if (user_str[j] <= pivot) {
            i++;
            swap(user_str[i], user_str[j]);
        }
    }

    swap(user_str[i + 1], user_str[end]);
    return (i + 1);
}

void ConvertAssistant::quick_sort(std::string &user_str, int start, int end) {
    if (start < end) {
        int pivot = partition(user_str, start, end);

        quick_sort(user_str, start, pivot - 1);
        quick_sort(user_str, pivot + 1, end);
    }
}

void ConvertAssistant::reverse(std::string &user_str) {
    for (int i = 0; i < user_str.size() / 2; ++i) {
        swap(user_str[i], user_str[user_str.size() - 1 - i]);
    }
}