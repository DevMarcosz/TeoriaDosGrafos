#include <bits/stdc++.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

void Bellman(vector<vector<int>> Grafo, int n, int writeN, std::string arName, int src)
{
  vector<int> dist(n, INT_MAX);
  dist[src - 1] = 0;
  for (int i = 0; i < n; i++)
  {
    for (auto e : Grafo)
    {
      int u = e[0];
      int v = e[1];
      int w = e[2];
      if (dist[u] != INT_MAX && ((dist[u] + w) < dist[v]))
      {
        dist[v] = dist[u] + w;
      }
    }
  }
  int counter = 1;

  std::vector<std::string> write(n);

  for (auto i : dist)
  {
    write[counter - 1] = std::to_string(counter) + ":" + std::to_string(i);
    cout << counter << ":" << i << " ";
    counter++;
  }
  cout << endl;
  if (writeN != 0)
  {
    std::ofstream arquivo(arName);
    if (arquivo.is_open())
    {
      for (int i = 0; i < n - 1; i++)
      {
        arquivo << write[i] << "\n";
      }
      arquivo.close();
      std::cout << "Array escrita no arquivo com sucesso.\n";
    }
    else
    {
      std::cout << "Não foi possível criar o arquivo.\n";
    }
  }
}

void help()
{

  cout << "-h : mostra o help" << endl;
  cout << "-o <arquivo> : redireciona a saida para o 'arquivo'" << endl;
  cout << "-f <arquivo> : indica o 'arquivo' que contém o grafo de entrada" << endl;
  cout << "-i : vértice inicial" << endl;
}

int main(int argc, char const *argv[])
{

  string input_file = "";
  string output_file = "";
  bool show_solution = false;
  int startVertex = 1;
  int write = 0;

    for (int i = 1; i < argc; i++)
    {
      if (strcmp(argv[i], "-h") == 0)
      {
          cout << "Help:" << endl;
          cout << "-h: mostra o help" << endl;
          cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
          cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
          cout << "-s: mostra a solução (em ordem crescente)" << endl;
          cout << "-i: vértice inicial (para o algoritmo de Prim)" << endl;
          return 0;
      }
      else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
      {
        write = 1;
        output_file = argv[++i];
      }
      else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
      {
          input_file = argv[++i];
      }
      else if (strcmp(argv[i], "-s") == 0)
      {
          show_solution = true;
      }
      else if (strcmp(argv[i], "-i") == 0 && i < argc - 1)
      {
          startVertex = atoi(argv[++i]);
      }
  }

    if (input_file == "")
  {
      cerr << "No input file specified. Use the -f parameter." << endl;
      return 1;
  }

  ifstream fin(input_file);
  if (!fin)
  {
      cerr << "Could not open input file: " << input_file << endl;
      return 1;
  }

  int n, m;
  fin >> n >> m;

  vector<vector<int>> Grafo;
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    fin >> u >> v >> w;
    u--, v--;
    Grafo.push_back({u, v, w});
    Grafo.push_back({v, u, w});
  }

  fin.close();

  Bellman(Grafo, n, write, output_file, startVertex);

}