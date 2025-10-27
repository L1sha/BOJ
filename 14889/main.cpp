#include "bits/stdc++.h"


int N;

std::array<std::array<int, 20>, 20> S;
int min = 1234567890;

std::vector<int> startMembers;
std::vector<int> linkMembers;

int cursor = 0, startAbility = 0, linkAbility = 0;

void solve(){
    
    int save;
    
    if (cursor == N){
        
        if (std::abs(startAbility - linkAbility) < min) min = std::abs(startAbility - linkAbility);
        return;
    }
    
    if (startMembers.size() != N / 2) {
        
        save = startAbility;
        for (int idx = 0; idx < startMembers.size(); ++idx) startAbility += (S[cursor][startMembers[idx]] + S[startMembers[idx]][cursor]);
        startMembers.push_back(cursor);
        cursor++;
        solve();
        cursor--;
        startMembers.pop_back();
        startAbility = save;
    }
    
    if (linkMembers.size() != N / 2) {
        
        save = linkAbility;
        for (int idx = 0; idx < linkMembers.size(); ++idx) linkAbility += (S[cursor][linkMembers[idx]] + S[linkMembers[idx]][cursor]);
        linkMembers.push_back(cursor);
        cursor++;
        solve();
        cursor--;
        linkMembers.pop_back();
        linkAbility = save;
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    for (int idx = 0; idx < N; ++idx) for (int idx2 = 0; idx2 < N; ++idx2) std::cin >> S[idx][idx2];
    
    solve();
    
    std::cout << min;
    
    return 0;
}


