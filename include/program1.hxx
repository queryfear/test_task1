#ifndef PROGRAM1_HXX
#define PROGRAM1_HXX 20

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <netinet/in.h> ///< Сетевые сокеты
#include <unistd.h> ///< Функции для работы с POSIX API
#include <sys/socket.h> ///< Сокеты
#include <InvalidDataError.hxx>


/**
* @class CreateData
* @brief Класс для работы с потоками данных и подключения к Unix Socket API
*/
class CreateData {
    private:
        std::string                     base; ///< Начальная строка с данными
        std::string                     odd_hash; ///< Хэш данных из функции first_stream()
        std::queue<std::string>         buffer_array; ///< Очередь для хранения сообщений клиента (unused)
        mutable std::queue<std::string> to_valid; ///< Очередь для данных для валидации
        // mutable std::queue<int>      to_valid;
        std::string                     buffer; ///< Строка данных .c_str(), отправляемая сервером клиенту
        std::mutex                      mtx; ///< mutex для синхронизации работы потоков
        std::condition_variable         cv; ///< condition_variable для блокировки потоков
        int                             servs; ///< Серверный сокет

    public:

        // Конструкторы
        CreateData(): base(""), buffer(""), odd_hash("") {};
        CreateData(std::string _base): base(_base), buffer(""), odd_hash("") {};
        CreateData(CreateData &_Cd);

        bool                       program1_spell(const std::string &user_str);

        /**
        * @brief Возвращает первый поток с членом base текущего объекта
        * @return Хэш std::string
        */
        std::string                first_stream() { return first_stream(base); };
        std::string                first_stream(std::string user_str);

        /**
        * @brief Передает данные о сокетах и строку base во второй поток с параметрами
        * @param int &server_socket Сокет сервера
        * @param int &client_socket Сокет клиента
        * @return Обработанное значение
        */
        int                        second_stream(int &server_socket, \
                                                 int &client_socket);

        /**
        * @brief Обрабатывает полученную строку и передает полученное значение клиенту
        * @param std::string user_str Хэш
        * @param int &server_socket Сокет сервера
        * @param int &client_socket Сокет клиента
        * @return Обработанное значение
        */
        int                        second_stream(std::string user_str, \
                                                 int &server_socket, \
                                                 int &client_socket);

        /**
        * @brief Шаблонный метод. Получение значения из очереди, соответствующее .front() + .pop(), но с использованием синхронизации потоков
        * @tparam T Тип данных в очереди
        * @param std::queue<T> &cont Очередь
        * @return Первый вошедший элемент очереди
        */
        template<typename T>
        T                          retrieve(std::queue<T> &cont);

        /**
        * @brief Шаблонный метод. Добавление значения в очередь с использованием синхронизации потоков
        * @tparam T Тип данных в очереди
        * @param std::queue<T> &cont Очередь
        * @param T val Значение
        * @return Первый вошедший элемент очереди
        */
        template<typename T>
        void                       push(std::queue<T> &cont, T val);

        // Геттеры
        std::string                getBuffer() const;
        std::string                getBase() const;
        std::string                getHash() const;
        std::queue<std::string>&   getToValid() const;
        int                        getServerSocket() const;
};

#endif // PROGRAM1_HXX