#include "bits/stdc++.h"


int T, N;



int main(int argc, char** argv){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;

    while (T--){

        std::cin >> N;

        int temp, res = 0;

        std::vector<int> pick(N + 1);
        std::vector<bool> determined(N + 1);
        std::vector<bool> visited(N + 1);
        std::vector<int> list;

        for (int idx = 1; idx <= N; ++idx) std::cin >> pick[idx];

        for (int idx = 1; idx <= N; ++idx) if (!determined[idx]){
            
            temp = idx;

            while (true){
                
                list.push_back(temp);
                visited[temp] = true;

                temp = pick[temp];

                if (determined[temp]){

                    res += list.size();
                    for (auto& el : list) determined[el] = true;
                    list.clear();
                    break;
                }

                if (visited[temp]){

                    res += std::distance(list.begin(), std::find(list.begin(), list.end(), temp));
                    for (auto& el : list) determined[el] = true;
                    list.clear();
                    break;
                }
            }
        }

        std::cout << res << '\n';

    }
    
    return 0;
}


