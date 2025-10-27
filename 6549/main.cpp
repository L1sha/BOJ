#include "bits/stdc++.h"

/* 위에서 내려가기 vs 아래에서 올라가기 */

int N;

std::array<int, 100'001> histo;

std::array<std::pair<int, int>, 400'004> segTree;



std::pair<int, int> segTreeInit(int idx, int l, int r){
    
    if (l == r) return segTree[idx] = std::make_pair(histo[l], l);
    return segTree[idx] = std::min(segTreeInit(idx * 2, l, l + (r - l) / 2), segTreeInit(idx * 2 + 1, l + (r - l) / 2 + 1, r));
}

std::pair<int, int> segTreeQuery(int idx, int l, int r, int ql, int qr){
    
    if (r < ql || l > qr) return std::make_pair(1'000'000'001, -1);
    if (l >= ql && r <= qr) return segTree[idx];
    return std::min(segTreeQuery(idx * 2, l, l + (r - l) / 2, ql, qr), segTreeQuery(idx * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr));
}


long long solve(int begin, int end){
    
    if (begin > end) return 0;
    if (begin == end) return histo[begin];
    
    auto min = segTreeQuery(1, 0, N - 1, begin, end);
    
    long long res = (long long) (end - begin + 1) * min.first, temp;
    
    res = std::max(res, solve(begin, min.second - 1));
    res = std::max(res, solve(min.second + 1, end));
    
    return res;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    while (N){
        
        for (int idx = 0; idx < N; ++idx) std::cin >> histo[idx];
        
        segTreeInit(1, 0, N - 1);
        
        std::cout << solve(0, N - 1) << '\n';
        
        std::cin >> N;
    }
    
    return 0;
}




