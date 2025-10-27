#include "bits/stdc++.h"

long long N, K, Q;

std::vector<long long> powK, sum;



void fastIO() {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

void get_input() {
    
    std::cin >> N >> K >> Q;
}

long long getDist(const long long& a, const long long& b) {
    
    long long res = 0;
    
    std::pair<long long, long long> left, right;
    
    left.first = std::lower_bound(sum.begin(), sum.end(), a) - sum.begin();
    left.second = a - sum[left.first - 1] - 1;
    
    right.first = std::lower_bound(sum.begin(), sum.end(), b) - sum.begin();
    right.second = b - sum[right.first - 1] - 1;
    
    if (left.first < right.first) std::swap(left, right);
    
    while (left.first != right.first) {
        
        --left.first;
        left.second /= K;
        ++res;
    }
    
    while (left.second != right.second) {
        
        left.second /= K;
        right.second /= K;
        res += 2;
    }
    
    return res;
}

void solve() {
    
    if (K == 1) {
        
        long long a, b;
        
        while (Q--) {
            
            std::cin >> a >> b;
            std::cout << llabs(a - b) << '\n';
        }
        
        return;
    }
    
    powK.push_back(1);
    sum.push_back(0);
    
    while (sum.back() < N) {
        
        sum.push_back(sum.back() + powK.back());
        powK.push_back(powK.back() * K);
    }
    
    long long a, b;
    
    while (Q--) {
        
        std::cin >> a >> b;
        std::cout << getDist(a, b) << '\n';
    }
}



int main(int argc, char** argv) {
    
    fastIO();
    get_input();
    solve();
    
    return 0;
}