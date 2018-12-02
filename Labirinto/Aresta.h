#ifndef ARESTA_H
#define ARESTA_H
#include "No.h"

class Aresta
{
    public:
        Aresta(No* ant, No* prox);
        ~Aresta();

        No* getNoAnt() { return noAnt; }
        void setNoAnt(No* val) { noAnt = val; }
        No* getNoProx() { return noProx; }
        void setNoProx(No* val) { noProx = val; }
        int getPeso() { return peso; }
        void setPeso(int val) { peso = val; }
        bool getVisitado() { return visitado; }
        void setVisitado(bool val) { visitado = val; }

    protected:

    private:
        No* noAnt;
        No* noProx;
        int peso;
        bool visitado;
};

#endif // ARESTA_H
