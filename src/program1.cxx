#include <asm-generic/socket.h> ///< Заголовочный файл для работы с системными файлами
#include <exception> ///< Библиотека для работы с исключениями
#include <iostream>
#include <stdexcept> ///< Заголовок для стандартных исключений (std::runtime_error)
#include <string>
#include <sys/socket.h>
#include <vector>
#include <mutex>
#include <queue>
#include <program1.hxx>
#include <ConvA.hxx>

// #if defined(__GNUC__)
//     #pragma GCC optimize ("O3")
// #endif

// namespace {
//     bool data_ready = false;
// }

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

template<typename T>
T CreateData::retrieve(std::queue<T> &cont) {
    // Блокирует потоки пока не выйдет из зоны видимости (функции)
    std::unique_lock<std::mutex> grd(mtx);   

    // cv.wait() принимает заблокированный guard и функцию как условие выхода из цикла
    // если очередь пуста, ожидает cv.notify_one() или cv.notify_all()
    cv.wait(grd, [&cont]{
        return !cont.empty();
    });

    T value = cont.front();
    cont.pop();

    return value;
}

template<typename T>
void CreateData::push(std::queue<T> &cont, T val) {
    std::lock_guard<std::mutex> grd(mtx);
    cont.push(val);
    cv.notify_one(); //< Уведомляем потоки об обновлении очереди
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

int CreateData::second_stream(int &server_socket, int &client_socket) {
    std::string _oddHash = "";
    _oddHash = retrieve(buffer_array);
    
    return second_stream(_oddHash, server_socket, client_socket);
}

int CreateData::second_stream(std::string user_str,
                              int &server_socket,
                              int &client_socket) {
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    // Системный вызов для настроек параметров сокета
    // SOL_SOCKET указывает на настройку общего параметра сокета
    // SO_RCVTIMEO задает таймаут для операций чтения
    //! Если клиент не отправит данные в течение 5 секунд, произойдет таймаут
    ::setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    while(true) {
        try {
            int total = 0;
            for (int i = 0; i < user_str.size(); ++i) {
                if (ConvertAssistant::is_digit(user_str[i]) == true) {
                    total += ConvertAssistant::to_digit(user_str[i]);
                }
                else i++;
            }
            
            push(to_valid, std::to_string(total));

            std::string result = retrieve(to_valid);
            int send_result;

            // Отправляем строку с суммой клиенту
            // client_socket - сокет, по которому происходит соединение с клиентом
            // result.c_str() - указатель на массив символов (строка, которую мы собираемся отправить)
            // result.size() - длина строки (количество байт для отправки)
            // 0 - флаг (в данном случае отсутствие флагов)
            // Если возвращает -1, значит произошла ошибка при отправке данных клиенту
            if ((send_result =  ::send(client_socket, result.c_str(),
                                    result.size(), 0)) == -1) {
                throw std::runtime_error("ERROR accepting the data. Reconnect.\n");
            }

        } catch (const std::exception& e) {

            // Закрываем сокет, так как произошла ошибка и он больше не активен
            ::close(client_socket);

            // Структура для хранения адресса клиента (IP, PORT)
            struct sockaddr_in client_address;
            socklen_t client_addr_len = sizeof(client_address);


            std::cout << "Waiting client connection ...\n";

            // Функция `accept` блокирует выполнение программы до тех пор, пока не подключится новый клиент.
            // При подключении клиента возвращает дескриптор сокета для клиента , который сохраняется в `client_socket`
            if ((client_socket = ::accept(server_socket, \
                                        (struct sockaddr*)&client_address, \
                                        &client_addr_len)) == -1) {
                std::cerr << "Error accepting client.\n";
            }

            // Обновляем поле, так как мог быть принят новый клиент
            servs = server_socket;
            std::cout << "Client reconnected.\n";
        }
    }

    return 0;
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

std::queue<std::string>& CreateData::getToValid() const {
    return std::ref(to_valid);
}

int CreateData::getServerSocket() const {
    return servs;
}