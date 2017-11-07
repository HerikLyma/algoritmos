#include <iostream>

using namespace std;

template <typename TIPO>
class Fila
{
    struct Elemento
    {
        Elemento *proximo = nullptr;
        TIPO valor;
    };
    int m_tamanho = 0;
    Elemento *primeiro = nullptr;
    Elemento *ultimo   = nullptr;
public:
    ~Fila()
    {
        Elemento *auxiliar = primeiro, *anterior;
        while(auxiliar)
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
        if(!primeiro)
            primeiro = novo;
        else
            ultimo->proximo = novo;
        ultimo = novo;
    }

    TIPO remover()
    {
        TIPO valor;
        if(primeiro)
        {
            --m_tamanho;
            Elemento *auxiliar = primeiro;
            valor = primeiro->valor;
            primeiro = primeiro->proximo;
            delete auxiliar;
        }
        return valor;
    }
};

int main()
{
    Fila<int> fila;
    for(int i = 0; i < 5; ++i)
        fila.inserir(i);

    cout << "Tamanho: " << fila.tamanho() << '\n';
    for(int i = 0; i < 5; ++i)
        cout << fila.remover() << '\n';
    cout << "Tamanho: " << fila.tamanho() << '\n';

    return 0;
}
