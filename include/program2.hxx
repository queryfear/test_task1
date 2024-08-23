#ifndef PROGRAM2_HXX
#define PROGRAM2_HXX

#include <netinet/in.h>
#include <string>
#include <program1.hxx>
#include <sys/socket.h>
#include <arpa/inet.h> ///< Конвертация IP в нужный формат 
#include <unistd.h>

class ValidateData {
    private:
        static constexpr int         PORT = 8080;
        static constexpr std::string IP = "127.0.0.1";

        std::string                  odd_hash;
        int                          stream_value;
        CreateData                   cd;

    public:
        /**
        * @brief Клиентский сокет
        *
        * Нужен для связи с сервером от имени клиента
        */
        int                          client_socket;
        
        /**
        * @brief Серверный сокет
        *
        * Нужен для принятия соединения с клиентом
        */
        int                          server_socket;

        // IP, PORT
        struct sockaddr_in           server_address;

        /**
        * @brief Буфер для хранения данных
        *
        * Буфер используется для обмена данными (чтение, запись) при работе с сокетами
        */
        char                         buffer[2048] = {0};

        // Конструкторы
        ValidateData(CreateData &_Cd);

        // Деструкторы
        ~ValidateData() { ::close(client_socket); };

         /**
         * @brief Метод для валидации данных
         * 
         * Передает данные полей в функцию с параметрами
         * @return Число валидации
         */
        int             validate();

        /**
         * @brief Метод для валидации данных с заданным значением от потока
         * 
         * Проверяет данные потока с использованием полей
         * @param int stream_value Данные с хэшированной строки (очищенный хэш)
         * @return Число валидации
         */
        int             validate(int stream_value);

        /**
         * @brief Переподключение к серверу
         * 
         * Выполняет переподключение клиента к серверу через сокет
         * @param int &client_socket Ссылка на клиентский сокет
         * @param sockaddr_in &server_address Ссылка на структуру с адресом сервера
         */
        void            reconnect(int &client_socket, struct sockaddr_in &server_address);

        // Геттеры
        std::string     getHash() const;
        int             getStreamValue() const;
};

#endif // PROGRAM2_HXX