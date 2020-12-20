#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>

using Vertex = size_t;
using IV = std::pair<int, Vertex>;
void Dijkstra(Vertex x, Vertex y, int M, int a, int b) {
	std::priority_queue<IV, std::vector<IV>, std::greater<IV>> q;
	std::vector<Vertex> dist(M, 1e8 + 1);
	dist[x] = 0;
	q.push({ dist[x], x });
	while (!q.empty()) {
		IV cur = q.top();
		q.pop();
		if (cur.first > dist[cur.second])
			continue;
		if (dist[(cur.second + 1) % M] > cur.first + a) {
			dist[(cur.second + 1) % M] = cur.first + a;
			q.push({ dist[(cur.second + 1) % M], (cur.second + 1) % M });
		}
		if (dist[(cur.second * cur.second + 1) % M] > cur.first + b) {
			dist[(cur.second * cur.second + 1) % M] = cur.first + b;
			q.push({ dist[(cur.second * cur.second + 1) % M], (cur.second * cur.second + 1) % M });
		}
	}
	std::cout << dist[y] << std::endl;
}




int main() {
	int a, b, M;
	Vertex x, y;
	std::cin >> a >> b >> M >> x >> y;
	Dijkstra(x, y, M, a, b);
	return 0;
}