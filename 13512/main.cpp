#include "bits/stdc++.h"

constexpr int N_MAX = 100'001;

int N;

std::array<std::vector<int>, N_MAX> adjL;
std::array<int, N_MAX> nodeNum;
std::array<std::pair<int, int>, N_MAX> nodeLocation;

std::vector<std::vector<int>> segTree(1), heavyLightDecomp(1);
std::vector<std::pair<int, int>> segHead(1, {-1, 0});

void fastIO() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
}

void get_input() {

	std::cin >> N;

	for (int from, to, idx = 0; idx < N - 1; ++idx) {

		std::cin >> from >> to;
		adjL[from].push_back(to);
		adjL[to].push_back(from);
	}
}

void initDFS(int cursor = 1, int parent = 0) {

	int maxNodeNum = 0;
	nodeNum[cursor] = 1;

	for (auto& next : adjL[cursor]) {

		if (next == parent) continue;

		initDFS(next, cursor);
		nodeNum[cursor] += nodeNum[next];

		if (nodeNum[next] > maxNodeNum) {

			maxNodeNum = nodeNum[next];
			std::swap(adjL[cursor].front(), next);
		}
	}
}

void initDFS2(int cursor = 1, int parent = 0) {

	nodeLocation[cursor] = {segTree.size() - 1, heavyLightDecomp.back().size()};
	heavyLightDecomp.back().push_back(cursor);

	for (const auto& next : adjL[cursor]) {

		if (next == parent) continue;

		if (next != adjL[cursor].front()) {
            
			segTree.push_back({});
			heavyLightDecomp.push_back({});
			segHead.push_back(nodeLocation[cursor]);
		}

		initDFS2(next, cursor);
	}
}

void segInit() {

    for (int idx = 0; idx < segTree.size(); ++idx) {
        
        segTree[idx].resize(4 * heavyLightDecomp[idx].size());
    }
}

int merge(const int& a, const int& b) {

	if (a == 0) {

		if (b == 0) return 0;
		else return b;
	}
	else return a;
}

void segUpdate(const int& order, const int& target, int cursor, int l, int r) {

	if (l > target || r < target) return;
	else if (l == r) segTree[order][cursor] = heavyLightDecomp[order][target] - segTree[order][cursor];
	else {

		segUpdate(order, target, cursor * 2, l, l + (r - l) / 2);
		segUpdate(order, target, cursor * 2 + 1, l + (r - l) / 2 + 1, r);

		segTree[order][cursor] = merge(segTree[order][cursor * 2], segTree[order][cursor * 2 + 1]);
	}
}

void Update(const int& target) {

	const auto& [first, second] = nodeLocation[target];

	segUpdate(first, second, 1, 0, heavyLightDecomp[first].size() - 1);
}

int segQuery(const int& order, const int& target, int cursor, int l, int r) {

	if (l > target) return 0;
	else if (r <= target) return segTree[order][cursor];
	else {

		return merge(segQuery(order, target, cursor * 2, l, l + (r - l) / 2),
		             segQuery(order, target, cursor * 2 + 1, l + (r - l) / 2 + 1, r));
	}
}

void Query(const int& target) {

	int res = -1;
	auto cursor = nodeLocation[target];

	while (cursor != std::make_pair(-1, 0)) {

		const auto& [first, second] = cursor;

		res = merge(segQuery(first, second, 1, 0, heavyLightDecomp[first].size() - 1), res);

		cursor = segHead[first];
	}

	std::cout << res << '\n';
}

void solve() {

    initDFS();
    initDFS2();
    segInit();

	int M, Q, V;
	std::cin >> M;

	while (M--) {

		std::cin >> Q >> V;

		if (Q == 1) Update(V);
		else Query(V);
	}
}



int main(int argc, char** argv) {

	fastIO();
	get_input();
	solve();

	return 0;
}

