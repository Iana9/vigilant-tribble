#include <iostream>


int Fibonacci(int in) {
    if (in == 1 || in == 2) {
        return 1;
    }
    else if (in  == 0)
    {
        return in;
    }
    else {
        return Fibonacci(in - 2) + Fibonacci(in - 1);
    }
}


int main() {

    std::cout << Fibonacci(39); // 63245986

    return 0;
}