#include "Aresta.h"

Aresta::Aresta(No* ant, No* prox)
{
    noProx = prox;
    noAnt = ant;
    visitado = false;
}

Aresta::~Aresta()
{
    //dtor
}
