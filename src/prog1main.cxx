#include <program1.hxx>
#include <program2.hxx>
#include <thread>

int main() {
    CreateData cd;

    while (true) {
        std::thread t1([&]{
            cd.first_stream();
        });
        std::thread t2([&]{
            cd.second_stream();
        });


        t1.join();
        t2.join();
    }
}