#include <iostream>
#include <memory>
#include <list>
#include <queue>
#include <vector>

using namespace std;

class Grafo
{
    int vertices;
    vector<list<int>> adjacencias;

    bool existeCaminhoDFS(int v1, int v2, vector<bool> &visitados) const
    {
        for(int i : adjacencias[v1])
        {
            if(visitados[i])
                continue;
            else if(i == v2)
                return true;
            else
            {
                visitados[i] = true;
                if(existeCaminhoDFS(i, v2, visitados))
                    return true;
            }
        }
        return false;
    }
public:
    explicit Grafo(int numeroVertices) : vertices(numeroVertices)
    {
        adjacencias.resize(numeroVertices);
    }

    inline void adicionarAresta(int v1, int v2)
    {
        adjacencias[v1].push_back(v2);
    }

    bool existeCaminhoBFS(int v1, int v2) const
    {
        vector<bool> visitados(vertices, false);
        queue<int> fila;
        visitados[0] = false;
        fila.push(v1);
        while(!fila.empty())
        {
            int verticeAtual = fila.front();
            fila.pop();
            for(int i : adjacencias[verticeAtual])
            {
                if(i == v2)
                    return true;
                else if(!visitados[i])
                {
                    visitados[i] = true;
                    fila.push(i);
                }
            }
        }
        return false;
    }

    bool existeCaminhoDFS(int v1, int v2)
    {
        vector<bool> visitados(vertices, false);
        return existeCaminhoDFS(v1, v2, visitados);
    }

    bool existeCicloBFS() const
    {
        unsigned int size = adjacencias.size();
        for(unsigned int i = 0; i < size; ++i)
        {
            if(existeCicloBFS(i))
                return true;
        }
        return false;
    }

    bool existeCicloBFS(int vertice) const
    {
        vector<bool> visitados(vertices, false);
        queue<int> fila;
        visitados[vertice] = true;
        fila.push(vertice);
        while(!fila.empty())
        {
            int verticeAtual = fila.front();
            fila.pop();
            for(int i : adjacencias[verticeAtual])
            {
                if(visitados[i])
                    return true;
                else
                {
                    visitados[i] = true;
                    fila.push(i);
                }
            }
        }
        return false;
    }

    void imprimirMenorCaminhoBFS(int v1, int v2) const
    {
        bool encontrou = false;
        queue<int> fila;
        vector<int> pais(vertices, -1), distancia(vertices, -1);
        pais[v1] = v1;
        distancia[v1] = 0;
        fila.push(v1);
        while(!fila.empty() && !encontrou)
        {
            int verticeAtual = fila.front();
            fila.pop();
            for(int i : adjacencias[verticeAtual])
            {
                if(distancia[i] == -1)
                {
                    pais[i] = verticeAtual;
                    distancia[i] = distancia[verticeAtual] + 1;
                    fila.push(i);
                }
                if(i == v2)
                {
                    encontrou = true;
                    break;
                }
            }
        }
        cout << "Distancia: " << distancia[v2] << '\n';
        cout << "Passando por: " << v1;
        int vertice = pais[v2];
        while(vertice != -1 && vertice != v1)
        {
            cout << ", " << vertice;
            vertice = pais[vertice];
        }
        cout << "\n\n";
    }
};

void desenharGrafoA()
{
    cout << "     0  \n";
    cout << "    / \\ \n";
    cout << "   1 - 2  \n";
    cout << "  /        \n";
    cout << " 3          \n\n";
}

void desenharGrafoB()
{
    cout << "      0   \n";
    cout << "     / \\  \n";
    cout << "    1   2   \n";
    cout << "   /     \\  \n";
    cout << "  3       \\  \n";
    cout << " /         \\  \n";
    cout << "4 --------- 5   \n\n";
}

unique_ptr<Grafo> criarGrafoB()
{
    unique_ptr<Grafo> grafo(new Grafo(6));
    grafo.get()->adicionarAresta(0, 1);
    grafo.get()->adicionarAresta(0, 2);
    grafo.get()->adicionarAresta(1, 3);
    grafo.get()->adicionarAresta(2, 5);
    grafo.get()->adicionarAresta(4, 5);
    return grafo;
}

unique_ptr<Grafo> criarGrafoA()
{
    unique_ptr<Grafo> grafo(new Grafo(6));
    grafo.get()->adicionarAresta(0, 1);
    grafo.get()->adicionarAresta(0, 2);
    grafo.get()->adicionarAresta(1, 2);
    grafo.get()->adicionarAresta(1, 3);
    return grafo;
}

void existeCaminhoBFS()
{
    unique_ptr<Grafo> grafo(std::move(criarGrafoA()));
    cout << "Existe caminho BFS (Busca em Largura)\n\n";
    desenharGrafoA();
    cout << boolalpha;
    cout << "Existe caminho de 0 para 1? " << grafo.get()->existeCaminhoBFS(0, 1) << '\n';
    cout << "Existe caminho de 0 para 3? " << grafo.get()->existeCaminhoBFS(0, 3) << '\n';
    cout << "Existe caminho de 2 para 3? " << grafo.get()->existeCaminhoBFS(2, 3) << '\n';
    cout << "\n-----------------------------------------------------------------------\n\n";
}

void existeCaminhoDFS()
{
    unique_ptr<Grafo> grafo(std::move(criarGrafoA()));
    cout << "Existe caminho DFS (Busca em profundidade)\n\n";
    desenharGrafoA();
    cout << boolalpha;
    cout << "Existe caminho de 0 para 1? " << grafo.get()->existeCaminhoDFS(0, 1) << '\n';
    cout << "Existe caminho de 0 para 3? " << grafo.get()->existeCaminhoDFS(0, 3) << '\n';
    cout << "Existe caminho de 2 para 3? " << grafo.get()->existeCaminhoDFS(2, 3) << '\n';
    cout << "\n-----------------------------------------------------------------------\n\n";
}

void existeCiclo()
{
    unique_ptr<Grafo> grafo(std::move(criarGrafoA()));
    cout << "Existe ciclos\n\n";
    desenharGrafoA();
    cout << boolalpha;
    cout << "Existe ciclo partindo de 0? " << grafo.get()->existeCicloBFS(0) << '\n';
    cout << "Existe ciclo partindo de 1? " << grafo.get()->existeCicloBFS(1) << '\n';
    cout << "Existe ciclo partindo de 2? " << grafo.get()->existeCicloBFS(2) << '\n';
    cout << "Existe pelo menos um ciclo? " << grafo.get()->existeCicloBFS() << '\n';
    cout << "\n-----------------------------------------------------------------------\n\n";
}

void imprimirMenorCaminho()
{
    unique_ptr<Grafo> grafo(std::move(criarGrafoB()));
    cout << "Imprimir menor caminho\n\n";
    desenharGrafoB();
    cout << boolalpha;
    cout << "Menor caminho de 0 a 5\n";
    grafo.get()->imprimirMenorCaminhoBFS(0, 5);
    cout << "\n-----------------------------------------------------------------------\n\n";
}

int main()
{
    existeCaminhoBFS();
    existeCaminhoDFS();
    existeCiclo();
    imprimirMenorCaminho();
    return 0;
}
