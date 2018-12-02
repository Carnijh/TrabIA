#include "No.h"
#include <iostream>

No::No(int indice, int X, int Y)
{
    id = indice;
    coordenadaX = X;
    coordenadaY = Y;
    arestaAbaixo = false;
    arestaAcima = false;
    arestaDireita = false;
    arestaEsquerda = false;
    visitado = false;
    pai = NULL;
    custoAcumulado = 0;
}

No::~No()
{
    //dtor
}
