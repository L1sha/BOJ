#include "bits/stdc++.h"


int N, M, sz;

std::vector<int> nums;
std::vector<int> stack;
std::vector<int> used;
std::unordered_map<int, int> howMany;


void solve(){
    
    if (stack.size() == M){
        
        for (auto & el : stack) std::cout << el << ' ';
        std::cout << '\n';
        return;
    }
    
    for (int idx = 0; idx < sz; ++idx) if (used[idx] < howMany[nums[idx]]) {
        
        stack.push_back(nums[idx]);
        used[idx]++;
        
        solve();
        
        used[idx]--;
        stack.pop_back();
    }
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N >> M;
    
    int temp;
    
    for (int idx = 0; idx < N; ++idx){
        
        std::cin >> temp;
        if (howMany.count(temp)) howMany[temp]++;
        else {
            
            howMany[temp] = 1;
            nums.push_back(temp);
        }
    }
    
    std::sort(nums.begin(),nums.end());
    
    sz = nums.size();
    used.resize(sz, 0);
    
    solve();
    
    
    return 0;
}



