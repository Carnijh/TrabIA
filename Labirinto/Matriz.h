#ifndef MATRIZ_H
#define MATRIZ_H

#include "No.h"
#include "Aresta.h"
#include <vector>

using namespace std;

class Matriz
{
    public:
        Matriz(int m, int n);
        ~Matriz();

        vector<No*> listaNo;
        vector<Aresta*> listaAresta;

        void adicionaAresta(int id1, int id2);
        Aresta* buscaAresta(No* ant, No* prox);
        No* consulta(int linha, int coluna);
        int determinaId(int linha, int coluna);
        void imprime();

        void backtracking();
        void defineRegrasBackTracking();
        void buscaLargura();
        void buscaProfundidade();
        void buscaOrdenada();
        void buscaGulosa();
        void buscaA();
        void buscaIDA();

    private:
        No* inicio;
        No* fim;
        int numLinhas;
        int numColunas;
};

#endif // MATRIZ_H
