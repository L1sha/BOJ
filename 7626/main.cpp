#include "bits/stdc++.h"


constexpr int N_MAX = 200'000;

int N, numY;
long long res;

std::array<int, N_MAX * 2> Y;
std::array<int, N_MAX * 2> partialSumY;
std::unordered_map<int, int> yIdx;
std::array<std::pair<long long, int>, N_MAX * 8> segTree;   // <total length, cnt>
std::array<std::pair<std::pair<int, int>, std::pair<int, int>>, N_MAX * 2> query;
// <<Xcoord,addOrRemove>, <Ybottom, Ytop>>

void segUpdate(int cursor, int l, int r, const int& ql, const int& qr, const int& val) {
    
    if (l > qr || r < ql) {
        
        return;
    }
    
    if (l >= ql && r <= qr) {
        
        segTree[cursor].second += val;
        
        if (segTree[cursor].second) {
            
            segTree[cursor].first = partialSumY[r] - partialSumY[l - 1];
        }
        else {
            
            if (l == r) {
                
                segTree[cursor].first = 0;
            }
            else {
                
                segTree[cursor].first = segTree[cursor * 2].first + segTree[cursor * 2 + 1].first;
            }
        }
        
        return;
    }
    
    segUpdate(cursor * 2, l, l + (r - l) / 2, ql, qr, val);
    segUpdate(cursor * 2 + 1, l + (r - l) / 2 + 1, r, ql, qr, val);
    
    if (segTree[cursor].second == 0) {
        
        segTree[cursor].first = segTree[cursor * 2].first + segTree[cursor * 2 + 1].first;
    }
}

void Query(const int& idx) {
    
    if (idx) {
        
        res += segTree[1].first * (query[idx].first.first - query[idx - 1].first.first);
    }
    
    int ql = yIdx[query[idx].second.first] + 1, qr = yIdx[query[idx].second.second];
    
    segUpdate(1, 1, numY, ql, qr, query[idx].first.second);
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> query[idx * 2].first.first >> query[idx * 2 + 1].first.first;
        std::cin >> Y[idx * 2] >> Y[idx * 2 + 1];
        
        query[idx * 2].first.second = 1;
        query[idx * 2 + 1].first.second = -1;
        query[idx * 2].second = {Y[idx * 2], Y[idx * 2 + 1]};
        query[idx * 2 + 1].second = {Y[idx * 2], Y[idx * 2 + 1]};
    }
    
    std::sort(query.begin(), query.begin() + 2 * N);
    std::sort(Y.begin(), Y.begin() + 2 * N);
    
    int prev = Y[0];
    yIdx[prev] = numY;
    
    for (int idx = 1; idx < 2 * N; ++idx) {
        
        if (prev != Y[idx]) {
            
            yIdx[Y[idx]] = ++numY;
            partialSumY[numY] = partialSumY[numY - 1] + (Y[idx] - prev);
            prev = Y[idx];
        }
    }
    
    for (int idx = 0; idx < 2 * N; ++idx) {
        
        Query(idx);
    }
    
    std::cout << res;
    
    return 0;
}

