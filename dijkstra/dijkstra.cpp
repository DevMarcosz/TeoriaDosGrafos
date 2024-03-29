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
    vector<pair<int, int>> adj[MAX_V];
    int V;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    vector<int> shortestPath(int src);
};

Graph::Graph(int V) : V(V) {}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

vector<int> Graph::shortestPath(int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V + 1, INF);
    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
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

    vector<int> distances = g.shortestPath(start_node);

    if (!(output_file == "")) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        for (int i = 1; i <= V; ++i) {
            fout << i << ":" << distances[i] << " ";
        }
        fout << endl;
        fout.close();
    }

    for (int i = 1; i <= V; ++i) {
        cout << i << ":" << distances[i] << " ";
    }
    cout << endl;

    return 0;
}
