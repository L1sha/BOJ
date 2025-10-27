#include "bits/stdc++.h"


/* Dynamic programming!

    Why do you think it is 2^n ? 
    with memoization, it only costs 5 * 5 * N = O(N)
    you can just search completely
    
    
    Also, top-down vs. bottom-up
    in this case, bottom-up!
*/

int N;

std::array<std::array<std::array<std::optional<int>, 100'001>, 5>, 5> memo;

std::array<int, 100'001> input;

int cost(int from, int to) {
    
    if (from == 0) return 2;
    if (from == to) return 1;
    if (std::abs(from - to) == 2) return 4;
    return 3;
}

int solve(int left, int right, int cnt) {
    
    if (cnt == N) return 0;
    if (memo[left][right][cnt].has_value()) return memo[left][right][cnt].value();
    
    if (left == input[cnt] || right == input[cnt]) memo[left][right][cnt] = solve(left, right, cnt + 1) + 1;
    else memo[left][right][cnt] = std::min(solve(input[cnt], right, cnt + 1) + cost(left, input[cnt]), solve(left, input[cnt], cnt + 1) + cost(right, input[cnt]));
    
    return memo[left][right][cnt].value();
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    while (true) {
        
        std::cin >> input[N];
        
        if (!input[N]) break;
        ++N;
    }
    
    
    std::cout << solve(0, 0, 0);
    
    return 0;
}

