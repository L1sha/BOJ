#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M;

std::array<std::array<int, 100>, 100> map;

void verifyOutside() {
    
    std::queue<intPair> q;
    q.push({0, 0});
    
    intPair front;
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
    
    while (!q.empty()) {
        
        front = q.front();
        q.pop();
        
        if (visited[front.first][front.second]) continue;
        visited[front.first][front.second] = true;
        map[front.first][front.second] = 2;
        
        if (front.first - 1 >= 0 && !visited[front.first - 1][front.second] && map[front.first - 1][front. second] != 1) q.push({front.first - 1, front.second});
        if (front.first + 1 < N && !visited[front.first + 1][front.second] && map[front.first + 1][front. second] != 1) q.push({front.first + 1, front.second});
        if (front.second - 1 >= 0 && !visited[front.first][front.second - 1] && map[front.first][front. second - 1] != 1) q.push({front.first, front.second - 1});        
        if (front.second + 1 < M && !visited[front.first][front.second + 1] && map[front.first][front. second + 1] != 1) q.push({front.first, front.second + 1});
    }
}

bool isDone() {
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) if (map[row][col] != 2) return false;
    return true;
}

void melt() {
    
    int cnt;
    
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) if (map[row][col] == 1) {
        
        cnt = 0;
        if (map[row - 1][col] == 2) cnt++;
        if (map[row + 1][col] == 2) cnt++;
        if (map[row][col - 1] == 2) cnt++;
        if (map[row][col + 1] == 2) cnt++;
        if (cnt >= 2) map[row][col] = 0;
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    for (int row = 0; row < N; ++row) for (int col = 0; col < M; ++col) std::cin >> map[row][col];
    
    int t = 0;
    
    while (true) {
        
        verifyOutside();
        if(isDone()) break;
        melt();
        
        t++;
    }
    
    std::cout << t;
    
    return 0;
}


