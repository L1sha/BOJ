#include "bits/stdc++.h"

/* 위에서 내려가기 vs 아래에서 올라가기 */

int N;

struct Rectangle{
    
    int leftIdx, rightIdx, height, width;
    
    Rectangle() = default;
    
    Rectangle(int height, int idx){
        
        leftIdx = idx - 1;
        rightIdx = idx + 1;
        this->height = height;
        width = 1;
    }
};

std::array<Rectangle, 100'001> histo;

std::array<std::pair<int, int>, 100'001> sorted;




void Merge(Rectangle rect){
    
    int leftHeight, rightHeight;
    
    if (rect.leftIdx == -1) leftHeight = -1;
    else {
        
        leftHeight = histo[rect.leftIdx].height;
        histo[rect.leftIdx].rightIdx = rect.rightIdx;
    }
    
    if (rect.rightIdx == N) rightHeight = -1;
    else {
        
        rightHeight = histo[rect.rightIdx].height;
        histo[rect.rightIdx].leftIdx = rect.leftIdx;
    }
    
    if (leftHeight + rightHeight == -2) return;
    
    if (leftHeight > rightHeight) histo[rect.leftIdx].width += rect.width;
    else histo[rect.rightIdx].width += rect.width;
}


long long solve(){
    
    long long max = 0, temp;
    int maxIdx;
    
    for (int idx = 0; idx < N; ++idx){
    
        maxIdx = sorted[idx].second;
        
        temp = (long long) histo[maxIdx].height * histo[maxIdx].width;
        max = std::max(temp, max);
        
        Merge(histo[maxIdx]);
    }
    
    return max;
}


int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> N;
    
    int height;
    
    while (N){
        
        for (int idx = 0; idx < N; ++idx) {
            
            std::cin >> height;
            
            histo[idx] = Rectangle(height, idx);
            sorted[idx] = std::make_pair(height, idx);
        }
        std::sort(sorted.begin(), sorted.begin() + N, std::greater<std::pair<int, int>>());
        
        std::cout << solve() << '\n';
        
        std::cin >> N;
    }
    
    return 0;
}





