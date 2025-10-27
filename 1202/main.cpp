#include "bits/stdc++.h"

using intPair = std::pair<long long, long long>;

int N, K;
std::array<intPair, 300'001> jewels; // <value, weight>
std::multiset<long long> bags
// can be duplicated!!!!!!!!!!!!!!!!!!



int main(int argc, char** argv){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> K;
    
    long long temp;
    
    for (int idx = 0; idx < N; ++idx) { std::cin >> jewels[idx].second >> jewels[idx].first; }
    for (int idx = 0; idx < K; ++idx) { std::cin >> temp; bags.insert(temp); }

    std::sort(jewels.begin(), jewels.begin() + N, std::greater<intPair>());

    long long res = 0;

    for (int idx = 0; idx < N; ++idx) {

        auto it = bags.lower_bound(jewels[idx].second);
        
        if (it != bags.end()){

            res += jewels[idx].first;
            bags.erase(it);
        }
        
        if (bags.size() == 0) break;
    }
    
    std::cout << res << '\n';

    return 0;
}