#include "bits/stdc++.h"

using namespace std;

std::array<int, 100'001> A;
std::array<std::pair<int, int>, 400'001> B;
int N, M;
int query, target, value;

std::pair<int, int> init(int idx, int l, int r){
    
    if (l == r) return B[idx] = std::make_pair(A[l], l);
    else return B[idx] = std::min(init(idx * 2, l, l + (r - l)/2), init(idx * 2 + 1, l + (r - l)/2 + 1, r));
}

std::pair<int, int> update(int idx, int l, int r){
    
    if (r < target || l > target) return B[idx];
    else if (l == r) return B[idx] = std::make_pair(value, l);
    else return B[idx] = std::min(update(idx * 2, l, l + (r - l)/2), update(idx * 2 + 1, l + (r - l)/2 + 1, r));
}


int main(int argc, char* *argv){
    ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 1; idx <= N; ++idx) std::cin >> A[idx];
    init(1, 1, N);
    
    std::cin >> M;
    
    while (M--){
        
        std::cin >> query;
        
        if (query == 1){
            
            std::cin >> target >> value;
            update(1, 1, N);
        }
        else if (query == 2) std::cout << B[1].second << '\n';
    }
    
    return 0;
}