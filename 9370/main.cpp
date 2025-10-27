#include "bits/stdc++.h"


using intPair = std::pair<int, int>;

int T, n, m, t, s, g, h, a, b, d, dist_btw_gh;

void dijkstra(int idx, const std::vector<std::vector<intPair>>& adjL, std::vector<int>& res) {
    
    std::priority_queue<intPair, std::vector<intPair>, std::greater<intPair>> pq;
    pq.push({0, idx});
    
    intPair top;
    
    while (!pq.empty()) {
        
        top = pq.top();
        pq.pop();
        
        if (res[top.second] != -1) continue;
        res[top.second] = top.first;
        
        for (auto& el : adjL[top.second]) if (res[el.second] == -1) pq.push({el.first + top.first, el.second});
    }
}

int main(int argc, char** argv){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    std::cin >> T;
    
    while (T--) {
        
        std::cin >> n >> m >> t >> s >> g >> h;
        
        std::vector<std::vector<intPair>> adjL(n + 1); 
        std::vector<int> candidates(t);
        std::vector<int> fromS(n + 1, -1);
        std::vector<int> fromG(n + 1, -1);
        std::vector<int> fromH(n + 1, -1);
        
        while (m--) {
            
            std::cin >> a >> b >> d;
            
            adjL[a].push_back({d, b});
            adjL[b].push_back({d, a});
        }
        
        for (auto& el : adjL[g]) if (el.second == h) {
            
            dist_btw_gh = el.first;
            break;
        }
        
        for (auto& el : candidates) std::cin >> el;
        std::sort(candidates.begin(), candidates.end());
        
        dijkstra(s, adjL, fromS);
        dijkstra(g, adjL, fromG);
        dijkstra(h, adjL, fromH);
        
        for (auto& el : candidates) {
            
            if (fromS[el] == -1) continue;
            if (fromS[el] != fromS[g] + dist_btw_gh + fromH[el] && fromS[el] != fromS[h] + dist_btw_gh + fromG[el]) continue;
            std::cout << el << ' ';
        }
        
        std::cout << '\n';
    }
    
    return 0;
}

