#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

#define INF INT_MAX

class Graph {
    static const int MAX_V = 1000;
    vector<pair<int, pair<int, int>>> edges;
    int V;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    vector<int> bellmanFord(int src);
};

Graph::Graph(int V) : V(V) {}

void Graph::addEdge(int u, int v, int w) {
    edges.push_back({u, {v, w}});
    edges.push_back({v, {u, w}});
}

vector<int> Graph::bellmanFord(int src) {
    vector<int> dist(V + 1, INF);
    dist[src] = 0;

    for (int i = 1; i < V; i++) {
        for (const auto& edge : edges) {
            int u = edge.first;
            int v = edge.second.first;
            int weight = edge.second.second;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    return dist;
}

int main(int argc, char* argv[]) {
    string input_file = "";
    string output_file = "";
    int start_node = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o arquivo" << endl;
            cout << "-f <arquivo>: lê o grafo do arquivo" << endl;
            cout << "-i: vertice inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            output_file = argv[i + 1];
        } else if (strcmp(argv[i], "-f") == 0) {
            input_file = argv[i + 1];
        } else if (strcmp(argv[i], "-i") == 0) {
            start_node = atoi(argv[i + 1]);
        }
    }

    if (input_file == "") {
        cout << "No input file specified. Use the -f parameter" << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;
    Graph g(V);

    int a, b, wt;

    for (int i = 0; i < E; i++) {
        fin >> a >> b >> wt;
        g.addEdge(a, b, wt);
    }

    fin.close();

    vector<int> distances = g.bellmanFord(start_node);

    if (!(output_file == "")) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        for (int i = 1; i <= V; ++i) {
            fout << i << ":" << (distances[i] == INF ? -1 : distances[i]) << " ";
        }
        fout << endl;
        fout.close();
    }

    for (int i = 1; i <= V; ++i) {
        cout << i << ":" << (distances[i] == INF ? -1 : distances[i]) << " ";
    }
    cout << endl;

    return 0;
}
