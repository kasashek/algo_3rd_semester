#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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

void dfs_graph(Vertex v, OrintationalListGraph& graph, std::vector<int>& colors, std::vector<Vertex>& path) {
	colors[v] = 1;
	for (auto u : graph.GetAdj(v)) {
		if (!colors[u])
			dfs_graph(u, graph, colors, path);
	}
	path.push_back(v);
}

void dfs_Inv_graph(Vertex v, OrintationalListGraph& graph, std::vector<int>& colors, int cnt) {
	colors[v] = cnt;
	for (auto u : graph.GetAdj(v)) {
		if (!colors[u])
			dfs_Inv_graph(u, graph, colors, cnt);
	}
}

void SSC(OrintationalListGraph& graph, OrintationalListGraph& Inv_graph) {
	std::vector<Vertex> path;
	std::vector<int> colors(graph.Size(), 0);
	for (size_t i = 0; i < graph.Size(); ++i) {
		if (!colors[i])
			dfs_graph(i, graph, colors, path);
	}
	std::reverse(path.begin(), path.end());

	colors = std::vector<int>(graph.Size(), 0);
	size_t i = 0;
	int cnt = 0;
	while (i < path.size()) {
		if (colors[path[i]]) {
			++i;
			continue;
		}
		if (!colors[path[i]]) {
			cnt++;
			std::set<Vertex> component;
			dfs_Inv_graph(path[i], Inv_graph, colors, cnt);
		}
	}

	int cnt_in, cnt_out;
	cnt_in = cnt_out = 0;
	std::vector<int> in(cnt + 1, 0), out(cnt + 1, 0);
	for (Vertex i = 0; i < graph.Size(); ++i) {
		for (auto u : graph.GetAdj(i)) {
			if (colors[u] != colors[i])
				out[colors[u]] = 1;
		}
		for (auto u : Inv_graph.GetAdj(i)) {
			if (colors[u] != colors[i])
				in[colors[u]] = 1;
		}
	}
	for (int i = 1; i <= cnt; ++i) {
		cnt_in += !(in[i]);
		cnt_out += !(out[i]);
	}
	if (cnt == 1)
		std::cout << "0" << std::endl;
	else 
		std::cout << std::max(cnt_in, cnt_out) << std::endl;
}


int main() {
	int n, m;
	std::cin >> n >> m;
	OrintationalListGraph graph(n), Inv_graph(n);
	for (size_t i = 0; i < m; ++i) {
		int a, b;
		std::cin >> a >> b;
		a--;
		b--;
		graph.AddEdge(a, b);
		Inv_graph.AddEdge(b, a);
	}
	SSC(graph, Inv_graph);
	return 0;
}