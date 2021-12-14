#include <algorithm>
#include <cstring>
#include <cctype>
#include <iostream>
#include <iterator>
#include <vector>
#include "aoc.hpp"
using namespace std;

// build an adjacency matrix
#define GRAPH_CAP 15
bool graph[GRAPH_CAP][GRAPH_CAP];
vector<uint32_t> visited(GRAPH_CAP, 0);
vector<string> vertices;
uint32_t vert_start = 0; // location of "start" in vertices

bool is_large_cave(unsigned int idx) {
    return isupper(vertices.at(idx)[0]);
}

void print_graph() {
    for (int y = 0; y < GRAPH_CAP; ++y) {
        for (int x = 0; x < GRAPH_CAP; ++x) {
            cout << (graph[y][x] ? "X" : ".") << " ";
        }
        cout << "\n";
    }
}

// returns an index based on location in vertices
uint64_t vertex_idx(const string &s) {
    // if already is in graph, return corresponding idx
    // otherwise add it to list of vertices
    auto result = find(begin(vertices), end(vertices), s);
    if (result != vertices.end()) {
        return distance(begin(vertices), result);
    } else {
        vertices.push_back(s);
        return vertices.size()-1;
    }
    return 0;
}

void dfs(uint32_t start, uint32_t end, bool twice, uint64_t &paths) {
    if (start == end) {
        paths++;
        return;
    }

    for (size_t i = 0; i < vertices.size(); ++i) {
        // if adjacent
        if (graph[start][i]) {
            if (is_large_cave(i)) {
                // large caves can be visited many times
                dfs(i, end, twice, paths);
            } else if (!visited[i]) {
                // small caves can be visited up to two times
                visited[i] = true;
                dfs(i, end, twice, paths);
                visited[i] = false;
            } else if (!twice && i != vert_start) {
                dfs(i, end, true, paths);
            }
        }
    }
}

int main() {
    vector<string> lines(istream_iterator<string>(cin), istream_iterator<string>(), {});
    vector<pair<string, string>> edges;
    for (const auto &line : lines) {
        auto tokens = aoc::split(line, '-');
        edges.emplace_back(tokens[0], tokens[1]);
    }
    
    int n_edges = edges.size();
    cout << "n_edges: " << n_edges << endl; 

    memset(graph, false, sizeof graph);
    for (const auto &[start, end] : edges) {
        auto start_idx = vertex_idx(start);
        auto end_idx = vertex_idx(end);
        graph[start_idx][end_idx] = true;
        graph[end_idx][start_idx] = true;
    }

    cout << "printing graph: \n";
    print_graph();

    cout << "starting traversal at start:\n";
    uint64_t paths = 0;
    auto start = find(begin(vertices), vertices.end(), "start");
    auto end = find(begin(vertices), vertices.end(), "end");
    if (start == vertices.end() || end == vertices.end()) throw invalid_argument("a start/end cave was not provided.");
    
    vert_start = distance(begin(vertices), start);
    visited[vert_start] = true; // set start as visited
    dfs(vert_start, distance(begin(vertices), end), false, paths);

    cout << "paths: " << paths << endl;
    return 0;
}

