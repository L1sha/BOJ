#include "bits/stdc++.h"


int N, L;
std::array<int, 5'000'000> A, res;

int main(int argc, char** argv) {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> L;
	for (int idx = 0; idx < N; ++idx) {

		std::cin >> A[idx];
	}
    
	std::deque<std::pair<int, int>> dq;

	for (int idx = 0; idx < N; ++idx) {

		while (!dq.empty() && idx - dq.front().second >= L) {

			dq.pop_front();
		}

		if (!dq.empty()) {
		    
		    res[idx] = std::min(A[idx], dq.front().first);
		}
		else {
		    
		    res[idx] = A[idx];
		}

		while (!dq.empty() && dq.back().first >= A[idx]) {

			dq.pop_back();
		}

		dq.push_back({A[idx], idx});
	}

	for (int idx = 0; idx < N; ++idx) {

		std::cout << res[idx] << ' ';
	}

	return 0;
}

