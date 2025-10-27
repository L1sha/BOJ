#include <iostream>

int main() {
    
    int l = 0, r, mid, res;
    std::cin >> r;
    ++r;
    
    while (true) {
        
        mid = (l + r) / 2;
        std::cout << "? " << mid << std::endl;
        std::cin >> res;
        
        if (res == -1) {
            
            l = mid;
        }
        else if (res == 1) {
            
            r = mid;
        }
        else {
            
            std::cout << "= " << mid << std::endl;
            break;
        }
    }
    
    return 0;
}