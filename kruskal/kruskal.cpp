#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> iPair;

struct Graph {
    int V, E;
    vector<pair<int, iPair>> edges;

    Graph(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    int kruskalMST(vector<pair<int, int>> &mstPairs, int initial);
};

struct DisjointSets {
    int *parent, *rnk;
    int n;

    DisjointSets(int n) {
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        for (int i = 0; i <= n; i++) {
            rnk[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
        }

        if (rnk[x] == rnk[y]) {
            rnk[y]++;
        }
    }
};

int Graph::kruskalMST(vector<pair<int, int>> &mstPairs, int initialNode) {
    int mst_wt = 0;
    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector<pair<int, iPair>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v) {
            mst_wt += it->first;
            mstPairs.push_back({u, v});
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    bool show_output = false;
    int start_node = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help" << endl;
            cout << "-h: mostra help" << endl;
            cout << "-f: arquivo de entrada" << endl;
            cout << "-o: arquivo de saida" << endl;
            cout << "-s: mostra a saida" << endl;
            cout << "-i: no inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-f") == 0) {
            input_file = argv[i + 1];
        } else if (strcmp(argv[i], "-o") == 0) {
            output_file = argv[i + 1];
        } else if (strcmp(argv[i], "-s") == 0) {
            show_output = true;
        } else if (strcmp(argv[i], "-i") == 0) {
            start_node = atoi(argv[i + 1]);
        }
    }
    if(input_file == ""){
        cout << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream file(input_file);
    if(!file){
        cerr << "Erro ao abrir o arquivo de entrada" << endl;
        return 1;
    }

    int V, E;
    file >> V >> E;
    Graph g(V, E);

    int a, b, wt;
    for (int i = 0; i < E; i++) {
        file >> a >> b >> wt;
        g.addEdge(a, b, wt);
    }
    file.close();

    vector<pair<int, int>> mstPairs;
    if (!(output_file == "")){
        ofstream fout(output_file);
        if(!fout){
            cout << "Erro ao abrir o arquivo de saída" << endl;
            return 1;
        }

    if(show_output){
        int mst_wt = g.kruskalMST(mstPairs, start_node);
        for (const auto &pair : mstPairs) {
            fout << pair.first << " " << pair.second << endl;
        }
        fout << endl;
    }
    else{
        int mst_wt = g.kruskalMST(mstPairs, start_node);
        fout << mst_wt << endl;
    }
    fout.close();
    }
    if(show_output){
        int mst_wt = g.kruskalMST(mstPairs, start_node);
        for (const auto &pair : mstPairs) {
            cout << pair.first << " " << pair.second << endl;
        }
        cout << endl;
    }
    else{
        int mst_wt = g.kruskalMST(mstPairs, start_node);
        cout << mst_wt << endl;
    }



    return 0;
}