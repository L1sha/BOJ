#include <iostream>

int main() {
    
    int N, first, last;
    std::cin >> N;
    std::cout << "? 1" << std::endl;
    std::cin >> first;
    std::cout << "? " << N << std::endl;
    std::cin >> last;
    
    std::cout << "! ";
    if (first) std::cout << (last ? 0 : -1);
    else std::cout << (last ? 1 : 0);
    std::cout << std::endl;
    
    return 0;
}