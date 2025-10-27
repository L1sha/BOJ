#include "bits/stdc++.h"


using intPair = std::pair<int, int>;
using intTuple = std::tuple<int, int, int>;

int N;

std::array<intPair, 100'001> X;
std::array<intPair, 100'001> Y;
std::array<intPair, 100'001> Z;
std::array<intTuple, 100'001> finder;




long long Prim(int startIdx) {
    
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
    std::vector<bool> visited(N, false);    
    
    pq.push({0, startIdx});
    
    long long res = 0;
    intPair top;
    int xIdx, yIdx, zIdx, cnt = 0;
    
    while (!pq.empty()) {
        
        top = pq.top();
        pq.pop();
        
        if (visited[top.second]) continue;
        visited[top.second] = true;
        res = res + top.first;
        if (++cnt == N) break;
        
        xIdx = std::get<0>(finder[top.second]);
        yIdx = std::get<1>(finder[top.second]);
        zIdx = std::get<2>(finder[top.second]);
        
        if (xIdx != 0 && !visited[X[xIdx - 1].second]) pq.push({std::abs(X[xIdx].first - X[xIdx - 1].first), X[xIdx - 1].second});
        if (xIdx != N - 1 && !visited[X[xIdx + 1].second]) pq.push({std::abs(X[xIdx].first - X[xIdx + 1].first), X[xIdx + 1].second});
        if (yIdx != 0 && !visited[Y[yIdx - 1].second]) pq.push({std::abs(Y[yIdx].first - Y[yIdx - 1].first), Y[yIdx - 1].second});
        if (yIdx != N - 1 && !visited[Y[yIdx + 1].second]) pq.push({std::abs(Y[yIdx].first - Y[yIdx + 1].first), Y[yIdx + 1].second});
        if (zIdx != 0 && !visited[Z[zIdx - 1].second]) pq.push({std::abs(Z[zIdx].first - Z[zIdx - 1].first), Z[zIdx - 1].second});
        if (zIdx != N - 1 && !visited[Z[zIdx + 1].second]) pq.push({std::abs(Z[zIdx].first - Z[zIdx + 1].first), Z[zIdx + 1].second});
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
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::get<0>(finder[X[idx].second]) = idx;
        std::get<1>(finder[Y[idx].second]) = idx;
        std::get<2>(finder[Z[idx].second]) = idx;
    }
    
    std::cout << Prim(0);
    
    return 0;
}

