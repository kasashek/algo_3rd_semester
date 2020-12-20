#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using Vertex = size_t;

class IGraph {
public:
	virtual ~IGraph() {}
	virtual void AddEdge(Vertex from, Vertex to) = 0;
	virtual size_t Size() const = 0;
	virtual const std::vector<Vertex>& GetAdj(Vertex v) const = 0;
};

class OrintationalListGraph : public IGraph
{
private:
	std::vector<std::vector<Vertex> > graph;
public:
	OrintationalListGraph(size_t vertexCount) : graph(vertexCount) {}
	size_t Size() const override { return graph.size(); }
	void AddEdge(Vertex from, Vertex to) override {
		graph.at(from).push_back(to);
	}
	const std::vector<Vertex>& GetAdj(Vertex v) const override {
		return graph.at(v);
	}
};

bool Loop_dfs(Vertex v, OrintationalListGraph& graph, std::vector<int>& colors) {
	colors[v] = 1;
	for (auto u : graph.GetAdj(v)) {
		if (!colors[u]) {
			if (Loop_dfs(u, graph, colors))
				return true;
		}
		if (colors[u] == 1) {
			return true;
		}
	}
	colors[v] = 2;
	return false;
}

void dfs(Vertex v, OrintationalListGraph& graph, std::vector<int>& colors, std::vector<Vertex>& ans) {
	colors[v] = 1;
	for (auto u : graph.GetAdj(v)) {
		if (!colors[u]) {
			dfs(u, graph, colors, ans);
		}
	}
	ans.push_back(v);
}

void top_sort(OrintationalListGraph& graph) {
	std::vector<int> colors(graph.Size(), 0);
	std::vector<Vertex> ans;

	for (int i = 0; i < graph.Size(); ++i) {
		if (!colors[i]) {
			dfs(i, graph, colors, ans);
		}
	}
	std::reverse(ans.begin(), ans.end());
	std::cout << "YES\n";
	for (size_t i = 0; i < ans.size(); ++i)
		std::cout << ans[i] << " ";
	std::cout << "\n";
}


int main() {
	int n, m;
	std::cin >> n >> m;
	OrintationalListGraph graph(n);
	for (size_t i = 0; i < m; ++i) {
		int a, b;
		std::cin >> a >> b;
		graph.AddEdge(a, b);
	}
	std::vector<int> colors(n, 0);
	for (Vertex i = 0; i < n; ++i) {
		if (!colors[i]) {
			if (Loop_dfs(i, graph, colors)) {
				std::cout << "NO\n";
				return 0;
			}
		}
	}
	top_sort(graph);
	return 0;
}




