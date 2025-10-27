#include "bits/stdc++.h"

std::string s;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

std::pair<bool, bool> varifyWhoWon(const std::string& s) {
    
    bool Xwon = false, Ywon = false;
    
    if (s[0] == s[1] && s[1] == s[2]) {
        
        if (s[0] == 'X') Xwon = true;
        else if (s[0] == 'O') Ywon = true;
    }
    
    if (s[3] == s[4] && s[4] == s[5]) {
        
        if (s[3] == 'X') Xwon = true;
        else if (s[3] == 'O') Ywon = true;
    }
    
    if (s[6] == s[7] && s[7] == s[8]) {
        
        if (s[6] == 'X') Xwon = true;
        else if (s[6] == 'O') Ywon = true;
    }
    
    if (s[0] == s[3] && s[3] == s[6]) {
        
        if (s[0] == 'X') Xwon = true;
        else if (s[0] == 'O') Ywon = true;
    }
    
    if (s[1] == s[4] && s[4] == s[7]) {
        
        if (s[1] == 'X') Xwon = true;
        else if (s[1] == 'O') Ywon = true;
    }
    
    if (s[2] == s[5] && s[5] == s[8]) {
        
        if (s[2] == 'X') Xwon = true;
        else if (s[2] == 'O') Ywon = true;
    }
    
    if (s[0] == s[4] && s[4] == s[8]) {
        
        if (s[0] == 'X') Xwon = true;
        else if (s[0] == 'O') Ywon = true;
    }
    
    if (s[2] == s[4] && s[4] == s[6]) {
        
        if (s[2] == 'X') Xwon = true;
        else if (s[2] == 'O') Ywon = true;
    }
    
    return {Xwon, Ywon};
}

void solve() {
    
    while (true) {
        
        std::cin >> s;
        if (s == "end") break;
        
        int Xcnt = 0, Ycnt = 0;
        
        for (const char& c : s) {
            
            if (c == 'X') ++Xcnt;
            else if (c == 'O') ++Ycnt;
        }
        
        if (Xcnt - Ycnt >= 2 || Xcnt < Ycnt) {
            
            std::cout << "invalid\n";
            continue;
        }
        
        auto [Xwon, Ywon] = varifyWhoWon(s);
        
        if (Xwon && Ywon || Xwon && Xcnt == Ycnt || Ywon && Xcnt > Ycnt
        || !Xwon && !Ywon && (Xcnt + Ycnt < 9)) {
            
            std::cout << "invalid\n";
            continue;
        }
        
        std::cout << "valid\n";
    }   
}



int main(int argc, char** argv) {
    
    fastIO();
    
    solve();
    
    return 0;
}

