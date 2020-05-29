#include <iostream>
#include <thread>
#include <windows.h>
#include "mat_mult.cpp"

#define COUNTS 100000

    CRITICAL_SECTION section;

void inc_int_crit(int &arg);

void inc_int(int &arg);


void v_22();
void v_23();
void v_23_crit();


int main() {
    InitializeCriticalSection(&section);
    v_23();
    DeleteCriticalSection(&section);
    return 0;
}

void print_int() {
    std::cout << 1;
}

void v_22() {
    auto a = std::vector<std::vector<int>> ({std::vector<int> ({3, 4}), std::vector<int> ({3, 4})});
    auto b = a;
    auto result = mul_mat(a, b);
    std::cout << result[0][0] << std::endl;
}

void v_23() {
    int a = 0;
    std::vector<std::thread> threads;
    threads.emplace_back(std::thread(inc_int, std::ref(a)));
    threads.emplace_back(std::thread(inc_int, std::ref(a)));

    for (auto &thread : threads) {
        thread.join();
    }
    std::cout << a;
}

void v_23_crit() {
    int a = 0;
    std::vector<std::thread> threads;
    threads.emplace_back(std::thread(inc_int_crit, std::ref(a)));
    threads.emplace_back(std::thread(inc_int_crit, std::ref(a)));

    for (auto &thread : threads) {
        thread.join();
    }
    std::cout << a;
}

void inc_int_crit(int &arg) {
    EnterCriticalSection(&section);
    for (int i = 0; i < COUNTS; i++) {
        arg++;
    }
    LeaveCriticalSection(&section);
}

void inc_int(int &arg) {
    for (int i = 0; i < COUNTS; i++) {
        arg++;
    }
}