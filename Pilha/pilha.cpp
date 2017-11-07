#include <iostream>

using namespace std;

template <typename TIPO>
class Pilha
{
    struct Elemento
    {
        Elemento *proximo = nullptr;
        TIPO valor;
    };
    int m_tamanho = 0;
    Elemento *ultimo = nullptr;
public:
    ~Pilha()
    {
        Elemento *auxiliar = ultimo, *anterior;
        while (auxiliar)
        {
            anterior = auxiliar;
            auxiliar = auxiliar->proximo;
            delete anterior;
        }
    }

    inline int tamanho() const
    {
        return m_tamanho;
    }

    inline bool vazia() const
    {
        return m_tamanho == 0;
    }

    void inserir(const TIPO &valor)
    {
        ++m_tamanho;
        Elemento *novo = new Elemento;
        novo->valor = valor;
        novo->proximo = ultimo;
        ultimo = novo;
    }

    TIPO remover()
    {
        TIPO valor;
        if(ultimo)
        {
            --m_tamanho;
            Elemento *auxiliar = ultimo;
            valor = ultimo->valor;
            ultimo = ultimo->proximo;
            delete auxiliar;
        }
        return valor;
    }
};

int main()
{
    Pilha<int> pilha;
    for(int i = 0; i < 5; ++i)
        pilha.inserir(i);

    cout << "Tamanho: " << pilha.tamanho() << '\n';
    for(int i = 0; i < 5; ++i)
        cout << pilha.remover() << '\n';
    cout << "Tamanho: " << pilha.tamanho() << '\n';

    cout << boolalpha;
    cout << "Pilha vazia? " << pilha.vazia() << '\n';

    return 0;
}
