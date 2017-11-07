#include <iostream>

using namespace std;

template<typename TIPO>
class Lista
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
    ~Lista()
    {
        Elemento *anterior = nullptr;
        Elemento *auxiliar = primeiro;
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

    void imprimir() const
    {
        if(m_tamanho)
        {
            Elemento *auxiliar = primeiro;
            while(auxiliar)
            {
                cout << auxiliar->valor << '\n';
                auxiliar = auxiliar->proximo;
            }
            cout << "\n\n";
        }
        else
        {
            cout << "Lista vazia!\n\n";
        }
    }

    bool remover(const TIPO &valor)
    {
        Elemento *auxiliar = primeiro, *anterior = nullptr;
        while(auxiliar)
        {
            if(auxiliar->valor == valor)
            {
                --m_tamanho;
                if(anterior)
                    anterior->proximo = auxiliar->proximo;
                else
                    primeiro = auxiliar->proximo;
                delete auxiliar;
                return true;
            }
            anterior = auxiliar;
            auxiliar = auxiliar->proximo;
        }
        return false;
    }
};

int main()
{
    Lista<int> lista;

    for(int i = 0; i < 3; ++i)
        lista.inserir(i);

    lista.imprimir();
    lista.remover(0);
    lista.imprimir();

    lista.remover(1);
    lista.imprimir();

    lista.remover(2);
    lista.imprimir();

    return 0;
}
