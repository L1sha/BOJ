#include "bits/stdc++.h"


int N, M, K;





int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M >> K;
    
    char color;
    int temp, isCorrectColor;
    std::vector<int> res;
    std::vector<int> temps(M - K + 1, 0);
    std::vector<std::queue<int>> qs(M - K + 1);
    
    for (int row = 0; row < K; ++row){
        
        temp = 0;
        std::queue<int> q;
        
        for (int col = 0; col < K; ++col){
            
            std::cin >> color;
            
            isCorrectColor = ((row + col) % 2) * 2 - 1;
            if (color == 'B') isCorrectColor = -isCorrectColor;
            
            q.push(isCorrectColor);
            temp += isCorrectColor;
        }
        
        qs[0].push(temp);
        temps[0] += temp;
        // std::cout << row << " 0 " << temp << '\n';
        
        for (int col = K; col < M; ++col){
            
            std::cin >> color;
            
            isCorrectColor = ((row + col) % 2) * 2 - 1;
            if (color == 'B') isCorrectColor = -isCorrectColor;
            
            temp -= q.front();
            q.pop();
            q.push(isCorrectColor);
            temp += isCorrectColor;
            
            qs[col - K + 1].push(temp);
            temps[col - K + 1] += temp;
            // std::cout << row << ' ' << col - K + 1 << ' ' << temp << '\n';
        }
    }
    
    res.insert(res.end(), temps.begin(), temps.end());
    
    for (int row = K; row < N; ++row){
        
        temp = 0;
        std::queue<int> q;
        
        for (int col = 0; col < K; ++col){
            
            std::cin >> color;
            
            isCorrectColor = ((row + col) % 2) * 2 - 1;
            if (color == 'B') isCorrectColor = -isCorrectColor;
            
            q.push(isCorrectColor);
            temp += isCorrectColor;
        }
        
        temps[0] -= qs[0].front();
        qs[0].pop();
        qs[0].push(temp);
        temps[0] += temp;
        
        for (int col = K; col < M; ++col){
            
            std::cin >> color;
            
            isCorrectColor = ((row + col) % 2) * 2 - 1;
            if (color == 'B') isCorrectColor = -isCorrectColor;
            
            temp -= q.front();
            q.pop();
            q.push(isCorrectColor);
            temp += isCorrectColor;
            
            temps[col - K + 1] -= qs[col - K + 1].front();
            qs[col - K + 1].pop();
            qs[col - K + 1].push(temp);
            temps[col - K + 1] += temp;
        }
        
        res.insert(res.end(), temps.begin(), temps.end());
    }
    
    /* for (auto &el : res) std::cout << el << ' ';
    std::cout << '\n'; */
    
    std::sort(res.begin(), res.end());
    if (-res.front() > res.back()) std::cout << (K * K + res.front()) / 2;
    else std::cout << (K * K - res.back()) / 2;
    
    return 0;
}


