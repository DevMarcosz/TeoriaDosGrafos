#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

void DFSUtil(vector<vector<int>>& adj, int v, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true;

    for (int u : adj[v]) {
        if (!visited[u])
            DFSUtil(adj, u, visited, Stack);
    }

    Stack.push(v);
}

void DFS(vector<vector<int>>& adj, int V, stack<int>& Stack) {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            DFSUtil(adj, i, visited, Stack);
    }
}

void DFSUtilReverse(vector<vector<int>>& adj, int v, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);

    for (int u : adj[v]) {
        if (!visited[u])
            DFSUtilReverse(adj, u, visited, component);
    }
}

vector<vector<int>> getTranspose(vector<vector<int>>& adj, int V) {
    vector<vector<int>> transpose(V);

    for (int v = 0; v < V; v++) {
        for (int u : adj[v]) {
            transpose[u].push_back(v);
        }
    }

    return transpose;
}

vector<vector<int>> kosaraju(vector<vector<int>>& adj, int V) {
    stack<int> Stack;
    DFS(adj, V, Stack);

    vector<vector<int>> transpose = getTranspose(adj, V);

    vector<vector<int>> components;
    vector<bool> visited(V, false);

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        if (!visited[v]) {
            vector<int> component;
            DFSUtilReverse(transpose, v, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

void help()
{

  cout << "-h : mostra o help" << endl;
  cout << "-o <arquivo> : redireciona a saida para o 'arquivo'" << endl;
  cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada" << endl;
  cout << "-i : vértice inicial" << endl;
}

int main(int argc, char const *argv[]) {

    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int startVertex = 1;
    int write = 0;

    for(int i =1; i < argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            cout << "-i: vértice inicial (para o algoritmo de Prim)" << endl;
            return 0;
        }
        else if(strcmp(argv[i], "-o") == 0 && i < argc - 1){
            write = 1;
            output_file = argv[++i];
        }
        else if(strcmp(argv[i], "-f") == 0 && i < argc - 1){
            input_file = argv[++i];
        }
        else if(strcmp(argv[i], "-s") == 0){
            show_solution = true;
        }
        else if(strcmp(argv[i], "-i") == 0 && i < argc - 1){
            startVertex = atoi(argv[++i]);
        }
    }

    if(input_file == ""){
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Could not open input file." << endl;
        return 1;
    }

    int V, E;
    fin >> V >> E;
    vector<vector<int>> adj(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        fin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }

    fin.close();

    vector<vector<int>> components = kosaraju(adj, V);

    for (const auto& component : components) {
        for (int v : component) {
            cout << v + 1 << " "; 
        }
        cout << endl;
    }

}
