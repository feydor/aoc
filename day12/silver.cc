#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

vector<string> split(const string &s, char delimiter = ' ') {
    vector<string> splits;
    string split;
    istringstream ss(s);
    while (getline(ss, split, delimiter)) {
        if (split.empty()) continue;
        splits.push_back(split);
    }
    return splits;
}

void print_map(const map<string, int> &m) {
    cout << "\nprinting map...\n";
    for (const auto &[s, n] : m)
        cout << s << " : " << n << endl;
}

bool bfs(map<string, vector<string>> &graph, map<string, int> &visited, string node, uint64_t &paths) {
    cout << node << " ";
    if (node == "end")
        return false;

    visited[node]++;
    print_map(visited);

    paths++;
    
    auto neighbors = graph[node];
    for (const auto &edge : neighbors) {
        if (edge== "start")
            continue;

        // lower case and visited more than once, skip
        if (any_of(begin(edge), end(edge), [](char c){return isupper(c) == 0;}) && visited[edge] > 0)
            continue;

        bfs(graph, visited, edge, paths);
    }
    return true;
}


int main() {
    vector<string> lines(istream_iterator<string>(cin), istream_iterator<string>(), {});
    vector<pair<string, string>> edges;
    for (const auto &line : lines) {
        auto tokens = split(line, '-');
        edges.emplace_back(tokens[0], tokens[1]);
    }
    
    int n_edges = edges.size();
    cout << "n_edges: " << n_edges << endl; 

    map<string, vector<string>> graph;
    for (const auto &[start, end] : edges) {
        auto adj_edges = graph.find(start);

        // already exists, add 'end' to adj_edges.second
        if (adj_edges != graph.end()) {
            adj_edges->second.push_back(end);
        } else {
            vector<string> adjacent = {end};
            graph[start] = adjacent;
        }

        // do the same for the end
        auto end_adj_edges = graph.find(end);
        if (end_adj_edges != graph.end()) {
            end_adj_edges->second.push_back(start);
        } else {
            vector<string> adjacent = {start};
            graph[end] = adjacent;
        }
    }

    cout << "printing graph: \n";
    for (const auto &[vertex, adj_edges] : graph) {
        cout << vertex << ": ";
        for (const auto &edge : adj_edges) {
            cout << edge << " ";
        }
        cout << "\n";
    }

    cout << "starting traversal at start:\n";
    uint64_t distinct_paths = 0;
    for (const auto &edge : graph["start"]) {
        map<string, int> visited;
        while (bfs(graph, visited, edge, distinct_paths)) {
            // do nothing
        }
        cout << "\n";
    }
    cout << "distinct_paths: " << distinct_paths << endl;
    return 0;
}

