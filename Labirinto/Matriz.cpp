#include "Matriz.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Matriz::Matriz(int m, int n)
{
    numLinhas = m;
    numColunas = n;

    ///Cria��o dos n�s sem arestas
    for(int i=0; i<numLinhas*numColunas; i++){
        vetor.push_back(new No(i));
    }

    ///Adicionando as arestas manualmente
    ///Seguindo o modelo do slide 76 da unidade 1
    adicionaAresta(0,1);
    adicionaAresta(0,3);
    adicionaAresta(1,4);
    adicionaAresta(2,5);
    adicionaAresta(3,4);
    adicionaAresta(3,6);
    adicionaAresta(4,5);
    adicionaAresta(4,7);
    adicionaAresta(7,8);
    adicionaAresta(8,11);
    adicionaAresta(9,10);
    adicionaAresta(10,11);

    ///Adicionando n� inicio e fim manualmente
    inicio = vetor.at(11);
    fim = vetor.at(1);
}

Matriz::~Matriz() { }

void Matriz::adicionaAresta(int id1, int id2)
{
    if(id1 < id2){
        if(id2-id1 < numColunas){
            vetor.at(id1)->setArestaDireita(true);
            vetor.at(id2)->setArestaEsquerda(true);
        } else {
            vetor.at(id1)->setArestaAbaixo(true);
            vetor.at(id2)->setArestaAcima(true);
        }
    } else if(id1 > id2){
        if(id1-id2 < numColunas){
            vetor.at(id1)->setArestaEsquerda(true);
            vetor.at(id2)->setArestaDireita(true);
        } else {
            vetor.at(id1)->setArestaAcima(true);
            vetor.at(id2)->setArestaAbaixo(true);
        }
    }
}

No* Matriz::consulta(int linha, int coluna)
{
    int k = determinaId(linha, coluna);
    if(k != -1)
        return vetor.at(k);
    else
    {
        cout << "Indice invalido!" << endl;
        exit(1);
    }
}

int Matriz::determinaId(int linha, int coluna)
{
    if(linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas)
        return numColunas*linha + coluna;
    else
        return -1;
}

void Matriz::imprime()
{
    for(int i=0; i<numLinhas; i++)
    {
        for(int j=0; j<numColunas; j++)
        {
            if(i==numLinhas-1 && j==numColunas-1)
                cout << vetor.at(determinaId(i,j))->getId() << ".";
            else
                cout << vetor.at(determinaId(i,j))->getId() << ", \t";
        }
        cout << endl;
    }
}

void Matriz::backtracking()
{
    No* no = inicio;
    No* pai = NULL;
    vector<int> bt;
    int contador = 0;
    int id;

    while(no != fim || contador == numColunas*numLinhas)
    {
        bt.push_back(no->getId());
        if(!no->getVisitado())
            contador++;
        no->setVisitado(true);

        if(no->getRegraBt() == 1)
        {
            id = no->getId() - numColunas;
            if((no == inicio)||(no-pai != numColunas)){
                if(no->getArestaAcima()){
                    if(!vetor.at(id)->getVisitado()){
                        no->setRegraBt(2);
                        pai = no;
                        no = vetor.at(id);
                    }
                }
            }
        }
        if(no->getRegraBt() == 2)
        {
            id = no->getId() + 1;
            if((no == inicio)||(no-pai != -1)){
                if(no->getArestaDireita()){
                    if(!vetor.at(id)->getVisitado()){
                        no->setRegraBt(3);
                        pai = no;
                        no = vetor.at(id);
                    }
                }
            }
        }
        if(no->getRegraBt() == 3)
        {
            id = no->getId() + numColunas;
            if((no == inicio)||(no-pai != -numColunas)){
                if(no->getArestaAbaixo()){
                    if(!vetor.at(id)->getVisitado()){
                        no->setRegraBt(4);
                        pai = no;
                        no = vetor.at(id);
                    }
                }
            }
        }
        if(no->getRegraBt() == 4)
        {
            id = no->getId() - 1;
            if((no == inicio)||(no-pai != 1)){
                if(no->getArestaEsquerda()){
                    if(!vetor.at(id)->getVisitado()){
                        no->setRegraBt(0);
                        pai = no;
                        no = vetor.at(id);
                    }
                }
            }
        }
    }

    for(int i=0; i<bt.size(); i++){
        cout << bt.at(i) << " - ";
    }
}
