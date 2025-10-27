#include "bits/stdc++.h"


constexpr int N_MAX = 1e5, K_MAX = 30;

int N, K, D;

struct student {
    
    int M, D;
    std::bitset<K_MAX> algoList;
    
    student() = default;
};

bool operator<(const student& A, const student& B) {
    
    return A.D < B.D ;
}

std::array<student, N_MAX> students;

long long solve() {
    
    std::sort(students.begin(), students.begin() + N);
    
    int minIdx = 0;
    long long stuCnt = 0, res = 0, max = -1;
    std::vector<int> cnt(K);
    
    for (int idx = 0; idx < N; ++idx) {
        
        while (stuCnt && students[idx].D - students[minIdx].D > D) {
            
            stuCnt--;
            for (int idx2 = 0; idx2 < K; ++idx2) {
                
                if (students[minIdx].algoList[idx2]) cnt[idx2]--;
            }
            minIdx++;
        }
        
        res = 0;
        stuCnt++;
        for (int idx2 = 0; idx2 < K; ++idx2) {
            
            if (students[idx].algoList[idx2]) cnt[idx2]++;
            
            if (cnt[idx2]) res++;
            if (cnt[idx2] == stuCnt) res--;
        }
        res *= stuCnt;
        
        max = std::max(res, max);
    }
    
    return max;
}

int main(int argc, char** argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K >> D;
    
    for (int idx = 0; idx < N; ++idx) {
        
        std::cin >> students[idx].M >> students[idx].D;
        
        for (int temp, idx2 = 0; idx2 < students[idx].M; ++idx2) {
            
            std::cin >> temp;
            students[idx].algoList[temp - 1] = true;
        }
    }
    
    std::cout << solve();
    
    return 0;
}

