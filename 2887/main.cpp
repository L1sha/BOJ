#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N;

std::array<intPair, 100'001> X;
std::array<intPair, 100'001> Y;
std::array<intPair, 100'001> Z;

std::array<std::vector<intPair>, 100'001> adjL;


long long dijkstra(int startIdx) {
    
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
    std::vector<bool> visited(N, false);    
    
    pq.push({0, startIdx});
    
    long long res = 0;
    intPair top;
    int cnt = 0;
    
    while (!pq.empty()) {
        
        top = pq.top();
        pq.pop();
        
        if (visited[top.second]) continue;
        visited[top.second] = true;
        
        res = res + top.first;
        if (++cnt == N) break;
        
        for (auto& el : adjL[top.second]) if (!visited[el.second]) pq.push({el.first, el.second});
    }
    
    return res;
}



int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> X[idx].first >> Y[idx].first >> Z[idx].first;
        X[idx].second = idx;
        Y[idx].second = idx;
        Z[idx].second = idx;
    }
    
    std::sort(X.begin(), X.begin() + N);
    std::sort(Y.begin(), Y.begin() + N);
    std::sort(Z.begin(), Z.begin() + N);
    
    for (int idx = 1; idx < N; ++idx) {
        
        adjL[X[idx].second].push_back({X[idx].first - X[idx - 1].first, X[idx - 1].second});
        adjL[X[idx - 1].second].push_back({X[idx].first - X[idx - 1].first, X[idx].second});
        adjL[Y[idx].second].push_back({Y[idx].first - Y[idx - 1].first, Y[idx - 1].second});
        adjL[Y[idx - 1].second].push_back({Y[idx].first - Y[idx - 1].first, Y[idx].second});
        adjL[Z[idx].second].push_back({Z[idx].first - Z[idx - 1].first, Z[idx - 1].second});
        adjL[Z[idx - 1].second].push_back({Z[idx].first - Z[idx - 1].first, Z[idx].second});
    }
    
    std::cout << dijkstra(0);
    
    return 0;
}

