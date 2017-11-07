#include <iostream>
#include <vector>

using namespace std;

std::vector<int> countingSort(const std::vector<int> &vetor, int maiorNumero)
{
    int size = vetor.size();
    std::vector<int> retorno;
    if(size)
    {
        ++maiorNumero;
        retorno.resize(size + 1);
        std::vector<int> auxiliar(maiorNumero, 0);
        for(int j = 0; j < size; ++j)
            ++auxiliar[vetor[j]];
        for(int i = 1; i < maiorNumero; ++i)
            auxiliar[i] += auxiliar[i - 1];
        for(int j = size - 1; j >= 0; --j)
        {
            retorno[auxiliar[vetor[j]]] = vetor[j];
            --auxiliar[vetor[j]];
        }
        retorno.erase(retorno.begin());
    }
    return retorno;
}

int main()
{
    vector<int> vetor({9, 1, 7, 3, 5, 0, 2, 8, 4});
    //vector<int> vetor({1, 0});
    vector<int> aux(std::move(countingSort(vetor, 9)));
    for(int i : aux)
        cout << i << '\n';
    return 0;
}
