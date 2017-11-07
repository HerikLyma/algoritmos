#include <iostream>

using namespace std;

template <typename TIPO>
class Arvore
{
    struct Elemento
    {
        TIPO valor;
        Elemento *direita  = nullptr;
        Elemento *esquerda = nullptr;
    };
    Elemento *raiz = nullptr;

    Elemento *inserir(Elemento *elemento, Elemento *novo)
    {
        if(!elemento)
            return novo;
        if(novo->valor > elemento->valor)
            elemento->direita = inserir(elemento->direita, novo);
        else
            elemento->esquerda = inserir(elemento->esquerda, novo);
        return elemento;
    }

    void imprimirCrescente(Elemento *elemento)
    {
        if(elemento)
        {
            imprimirCrescente(elemento->esquerda);
            cout << elemento->valor << '\n';
            imprimirCrescente(elemento->direita);
        }
    }

    void imprimirDecrescente(Elemento *elemento)
    {
        if(elemento)
        {
            imprimirDecrescente(elemento->direita);
            cout << elemento->valor << '\n';
            imprimirDecrescente(elemento->esquerda);
        }
    }

    Elemento *buscar(Elemento *elemento, const TIPO &valor)
    {
        if(elemento)
        {
            if(valor == elemento->valor)
                return elemento;
            else if(valor > elemento->valor)
                return buscar(elemento->direita, valor);
            else
                return buscar(elemento->esquerda, valor);
        }
        return elemento;
    }

    void deletar(Elemento *elemento)
    {
        if(elemento)
        {
            deletar(elemento->direita);
            deletar(elemento->esquerda);
            delete elemento;
        }
    }
public:
    ~Arvore()
    {
        deletar(raiz);
    }

    void inserir(const TIPO &valor)
    {
        Elemento *novo = new Elemento;
        novo->valor = valor;
        raiz = inserir(raiz, novo);
    }

    bool existe(const TIPO &valor)
    {
        return buscar(raiz, valor) != nullptr;
    }

    void imprimirCrescente()
    {
        imprimirCrescente(raiz);
    }

    void imprimirDecrescente()
    {
        imprimirDecrescente(raiz);
    }
};

int main()
{
    Arvore<int> arvore;
    arvore.inserir(10);
    arvore.inserir(9);
    arvore.inserir(11);
    arvore.inserir(8);
    arvore.inserir(12);
    arvore.imprimirCrescente();
    cout << "\n\n";
    arvore.imprimirDecrescente();
    cout << boolalpha;
    cout << "\n\nExiste 9? " << arvore.existe(9);
    cout << "\nExiste 19? " << arvore.existe(19) << "\n\n";
    return 0;
}
