#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>

using Vertex = size_t;

class IGraph {
public:
	virtual ~IGraph() {}
	virtual void AddEdge(Vertex from, Vertex to) = 0;
	virtual size_t Size() const = 0;
	virtual const std::vector<Vertex>& GetAdj(Vertex v) const = 0;
};

class NonOrintationalListGraph : public IGraph
{
private:
	std::vector<std::vector<Vertex> > graph;
public:
	NonOrintationalListGraph(size_t vertexCount) : graph(vertexCount) {}
	size_t Size() const override { return graph.size(); }
	void AddEdge(Vertex from, Vertex to) override {
		graph.at(from).push_back(to);
		graph.at(to).push_back(from);
	}
	const std::vector<Vertex>& GetAdj(Vertex v) const override {
		return graph.at(v);
	}
};

std::vector<int> bfs(Vertex v, NonOrintationalListGraph& graph, std::vector<Vertex>& colors) {
	std::queue<Vertex> queue;
	std::vector<int> dist(graph.Size(), 0);
	dist[v] = 0;
	colors[v] = 1;
	queue.push(v);
	Vertex cur_Vertex;
	while (!queue.empty()) {
		cur_Vertex = queue.front();
		queue.pop();
		for (auto u : graph.GetAdj(cur_Vertex)) {
			if (!colors[u]) {
				queue.push(u);
				colors[u] = 1;
				dist[u] = dist[cur_Vertex] + 1;
			}
		}
	}
	return dist;
}


int main() {
	int n, m;
	Vertex Leon_Vertex, Matilda_Vertex, Milk_Vertex;
	std::cin >> n >> m >> Leon_Vertex >> Matilda_Vertex >> Milk_Vertex;
	Leon_Vertex--;
	Matilda_Vertex--;
	Milk_Vertex--;
	NonOrintationalListGraph graph(n);
	for (size_t i = 0; i < m; ++i) {
		int a, b;
		std::cin >> a >> b;
		a--;
		b--;
		graph.AddEdge(a, b);
	}
	
	std::vector<Vertex> colors(n, 0);
	std::vector<int> dist_Leon = bfs(Leon_Vertex, graph, colors);

	colors = std::vector<Vertex> (n, 0);
	std::vector<int> dist_Matilda = bfs(Matilda_Vertex, graph, colors);
	
	colors = std::vector<Vertex>(n, 0);
	std::vector<int> dist_Milk = bfs(Milk_Vertex, graph, colors);

	int ans = 2 * n;
	
	for (size_t i = 0; i < graph.Size(); ++i)
		if (dist_Leon[i] + dist_Milk[i] + dist_Matilda[i] < ans) 
			ans = dist_Leon[i] + dist_Milk[i] + dist_Matilda[i];
	std::cout << ans << std::endl;
	return 0;
}