#include "bits/stdc++.h"

int N;

std::array<int, 100'001> histo;

std::array<std::pair<long long, std::pair<int, int>>, 400'004> segTree;



std::pair<long long, std::pair<int, int>> segTreeInit(int idx, int l, int r){
    
    if (l == r) return segTree[idx] = std::make_pair(histo[l], std::make_pair(histo[l], l));
     
    auto left = segTreeInit(idx * 2, l, l + (r - l) / 2);
    auto right = segTreeInit(idx * 2 + 1, l + (r - l) / 2 + 1, r);
        
    return segTree[idx] = std::make_pair(left.first + right.first, std::min(left.second, right.second));
}

std::pair<long long, std::pair<int, int>> segTreeQuery(int idx, int l, int r, int ql, int qr){
    
    if (r < ql || l > qr) return std::make_pair(0, std::make_pair(1'000'001, -1));
    if (l >= ql && r <= qr) return segTree[idx];
    
    auto left = segTreeQuery(idx * 2, l, l + (r - l) / 2, ql, qr);
    auto right = segTreeQuery(idx * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr);
    
    return std::make_pair(left.first + right.first, std::min(left.second, right.second));
}


long long solve(int begin, int end){
    
    if (begin > end) return 0;
    if (begin == end) return (long long) histo[begin] * histo[begin];
    
    auto min = segTreeQuery(1, 0, N - 1, begin, end);
    
    long long res = min.first * min.second.first;
    
    res = std::max(res, solve(begin, min.second.second - 1));
    res = std::max(res, solve(min.second.second + 1, end));
    
    return res;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
        
    for (int idx = 0; idx < N; ++idx) std::cin >> histo[idx];
        
    segTreeInit(1, 0, N - 1);
        
    std::cout << solve(0, N - 1);
        
    return 0;
}







