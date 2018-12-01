#ifndef MATRIZ_H
#define MATRIZ_H

#include "No.h"

#define X 4
#define Y 3

class Matriz
{
    public:
        Matriz(int m, int n);
        ~Matriz();

        No** vetor;

        void atribui(int linha, int coluna, No* no);
        void adicionaAresta(int id1, int id2);
        No* consulta(int linha, int coluna);
        int determinaId(int linha, int coluna);
        void imprime();

        void backtracking();
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
