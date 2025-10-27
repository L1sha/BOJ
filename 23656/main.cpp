#include <iostream>

int main() {
    
    int l = 0, r = 1'000'000'001, mid;
    
    for (int step = 0; step < 100; ++step) {
        
        std::cin >> mid;
        

        if (mid >= r) {
            
            std::cout << '<' << std::endl;
        }
        else if (mid <= l) {
            
            std::cout << '>' << std::endl;
        }
        else if (r - l == 2) {
            
            std::cout << '=' << std::endl;
            break;
        }
        else if (r - mid > mid - l) {
            
            std::cout << '>' << std::endl;
            l = mid;
        }
        else {
            
            std::cout << '<' << std::endl;
            r = mid;
        }
    }
    
    return 0;
}