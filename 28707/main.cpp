#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int N, M, min = 1e9;

std::vector<int> A;
std::array<int, 16777216> memo;
std::vector<std::pair<int, std::pair<int, int>>> change;

std::vector<int> makeVec(int num) {
    
    std::vector<int> res;
    for (int idx = 0; idx < N; ++idx) {
        
        res.push_back(num % 8);
        num /= 8;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

int makeNum(const std::vector<int>& vec) {
    
    int res = 0; 
    for (int idx = 0; idx < N; ++idx) {
        
        res *= 8;
        res += vec[idx];
    }
    return res;
}

bool isOrdered(int num) {
    
    std::vector<int> temp = makeVec(num);
    for (int idx = 1; idx < N; ++idx) if (temp[idx - 1] > temp[idx]) return false;
    return true;
}

int solve(int num) {
    
    std::fill(memo.begin(), memo.end(), -1);
    
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
    pq.push({0, num});
    intPair top;
    std::vector<int> tempVec;
    int tempNum;
    
    while (!pq.empty()) {
        
        top = pq.top();
        pq.pop();
        
        if (memo[top.second] != -1) continue;
        memo[top.second] = top.first;
        
        if (isOrdered(top.second)) return top.first;
        
        tempVec = makeVec(top.second);
        
        for (auto& op : change) {
            
            std::swap(tempVec[op.second.first], tempVec[op.second.second]);
            tempNum = makeNum(tempVec);
            if (memo[tempNum] == -1) pq.push({top.first + op.first, tempNum});
            std::swap(tempVec[op.second.first], tempVec[op.second.second]);
        }
    }
    
    return -1;
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::vector<std::pair<int, int>> B;
    
    int temp;
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> temp;
        A.push_back(temp);
        B.push_back({temp, idx});
    }
    
    temp = 0;
    std::sort(B.begin(), B.end());
    for (int idx = 0; idx < A.size(); ++idx) A[idx] -= B[0].first;
    for (int idx = 1; idx < B.size(); ++idx) {
        
        if (B[idx].first - B[idx - 1].first <= 1) continue;
        else {
            
            for (int idx2 = idx; idx2 < B.size(); ++idx2) {
                
                A[B[idx2].second] -= (B[idx].first - B[idx - 1].first - 1);
            }
        }
    }
    
    std::cin >> M;
    int l, r, c;
    while (M--) {
        
        std::cin >> l >> r >> c;
        change.push_back({c, {l - 1, r - 1}});
    }
    
    std::cout << solve(makeNum(A));
    
    return 0;
}

