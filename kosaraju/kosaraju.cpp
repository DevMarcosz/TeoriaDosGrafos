#include <bits/stdc++.h>

using namespace std;

class Grafo {
public:
    int vertices;
    vector<vector<int>> adj;

    Grafo(int v) : vertices(v), adj(v) {}

    void adicionarAresta(int v1, int v2) {
        adj[v1].push_back(v2);
    }

    void DFS(int vertice, vector<bool>& visitado, stack<int>& pilha) {
        visitado[vertice] = true;

        for (int vizinho : adj[vertice]) {
            if (!visitado[vizinho]) {
                DFS(vizinho, visitado, pilha);
            }
        }

        pilha.push(vertice);
    }

    Grafo transpor() {
        Grafo grafoTransposto(vertices);

        for (int v = 0; v < vertices; ++v) {
            for (int vizinho : adj[v]) {
                grafoTransposto.adicionarAresta(vizinho, v);
            }
        }

        return grafoTransposto;
    }

    void encontrarComponentesFortementeConectados() {
        vector<bool> visitado(vertices, false);
        stack<int> pilha;

        for (int v = 0; v < vertices; ++v) {
            if (!visitado[v]) {
                DFS(v, visitado, pilha);
            }
        }

        Grafo grafoTransposto = transpor();

        fill(visitado.begin(), visitado.end(), false);

        while (!pilha.empty()) {
            int vertice = pilha.top();
            pilha.pop();

            if (!visitado[vertice]) {
                cout << "Componente fortemente conectado:";
                grafoTransposto.DFS(vertice, visitado, pilha);
                cout << endl;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada>" << endl;
        return 1;
    }

    ifstream arquivo(argv[1]);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int n, m;
    arquivo >> n >> m;

    Grafo grafo(n);

    for (int i = 0; i < m; ++i) {
        int v1, v2;
        arquivo >> v1 >> v2;
        grafo.adicionarAresta(v1 - 1, v2 - 1);
    }

    cout << "Componentes fortemente conectados:" << endl;
    grafo.encontrarComponentesFortementeConectados();

    return 0;
}
