#include <iostream>

int main() {
    
    for (int row = 0; row < 14; ++row) {
        
        for (int col = 0; col < 14; ++col) {
            
            std::cout << 0 << ' ';
        }
        
        std::cout << 1 << ' ';
        
        for (int col = 15; col < 29; ++col) {
            
            std::cout << 0 << ' ';
        }
        
        std::cout << 0 << '\n';
    }
    
    for (int col = 0; col < 14; ++col) {
        
        std::cout << 15 << ' ';
    }
        
    std::cout << 0 << ' ';
        
    for (int col = 15; col < 29; ++col) {
            
        std::cout << 15 * 15 * 15 << ' ';
    }
    
    std::cout << 0 << '\n';
    
    for (int row = 15; row < 29; ++row) {
        
        for (int col = 0; col < 14; ++col) {
            
            std::cout << 0 << ' ';
        }
        
        std::cout << 15 * 15 << ' ';
        
        for (int col = 15; col < 29; ++col) {
            
            std::cout << 0 << ' ';
        }
        
        std::cout << 0 << '\n';
    }
    
    for (int col = 0; col < 29; ++col) {
        
        std::cout << 0 << ' ';
    }
    
    std::cout << 0;
    
    return 0;
}