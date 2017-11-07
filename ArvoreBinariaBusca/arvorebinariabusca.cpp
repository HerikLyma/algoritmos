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

    Elemento *pai(Elemento *elemento, const TIPO &valor)
    {
        if(elemento)
        {
            if(valor > elemento->valor)
            {
                Elemento *direita = elemento->direita;
                if(direita)
                {
                    if(direita->valor == valor)
                        return elemento;
                    return pai(direita, valor);
                }
            }
            else
            {
                Elemento *esquerda = elemento->esquerda;
                if(esquerda)
                {
                    if(esquerda->valor == valor)
                        return elemento;
                    return pai(esquerda, valor);
                }
            }
        }
        return nullptr;
    }

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

    Elemento *maximo(Elemento *elemento) const
    {
        if(elemento)
        {
            while(elemento->direita)
               elemento = elemento->direita;
        }
        return elemento;
    }

    Elemento *minimo(Elemento *elemento) const
    {
        if(elemento)
        {
            while(elemento->esquerda)
               elemento = elemento->esquerda;
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

    TIPO minimo(bool *encontrou = nullptr) const
    {
        Elemento *aux = minimo(raiz);
        if(encontrou)
            *encontrou = aux != nullptr;
        if(aux)
            return aux->valor;
        return TIPO();
    }

    TIPO maximo(bool *encontrou = nullptr) const
    {
        Elemento *aux = maximo(raiz);
        if(encontrou)
            *encontrou = aux != nullptr;
        if(aux)
            return aux->valor;
        return TIPO();
    }

    TIPO pai(const TIPO &valor, bool *encontrou = nullptr)
    {
        Elemento *paiAux = pai(raiz, valor);
        if(encontrou)
            *encontrou = paiAux != nullptr;
        if(paiAux)
            return paiAux->valor;
        return TIPO();
    }

    TIPO sucessor(const TIPO &valor)
    {
        Elemento *aux = buscar(raiz, valor);
        if(aux)
        {
            if(aux->direita)
                return minimo(aux->direita)->valor;
            else
            {
                Elemento *paiAux = pai(raiz, valor);
                while(paiAux && (aux = paiAux->direita))
                {
                    aux = paiAux;
                    paiAux = pai(raiz, paiAux->valor);
                }
                return aux->valor;
            }
        }
        return valor;
    }
};

int main()
{
    Arvore<int> arvore;
    arvore.inserir(8);
    arvore.inserir(3);
    arvore.inserir(10);
    arvore.inserir(1);
    arvore.inserir(6);
    arvore.inserir(14);
    arvore.inserir(4);
    arvore.inserir(7);
    arvore.inserir(13);
    arvore.imprimirCrescente();
    cout << "\n\n";
    arvore.imprimirDecrescente();
    cout << boolalpha;
    cout << "\n\nExiste 8? " << arvore.existe(8);
    cout << "\nExiste 18? " << arvore.existe(18) << "\n\n";
    cout << "Minimo: " << arvore.minimo() << '\n';
    cout << "Maximo: " << arvore.maximo() << '\n';
    cout << "Pai de 3: " << arvore.pai(3) << '\n';
    cout << "Pai de 13: " << arvore.pai(13) << '\n';
    cout << "Sucessor de 3: " << arvore.sucessor(3) << '\n';
    cout << "Sucessor de 7: " << arvore.sucessor(7) << '\n';
    return 0;
}
