#include "Matriz.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <queue>
#include <stack>

using namespace std;

void printaCaminho(vector<int> caminho);

Matriz::Matriz(int m, int n)
{
    numLinhas = m;
    numColunas = n;

    ///Criação dos nós sem arestas
    for(int i=0; i<numLinhas; i++){
        for (int j=0; j<numColunas; j++){
            listaNo.push_back(new No(i*numColunas+j,i,j));
        }
    }

    ///Adicionando as arestas manualmente
    ///Seguindo o modelo do slide 76 da unidade 1

    //Na horizontal:
    adicionaAresta(0,1);
    adicionaAresta(3,4);
    adicionaAresta(4,5);
    adicionaAresta(9,10);
    adicionaAresta(7,8);
    adicionaAresta(10,11);

    //Na vertical:
    adicionaAresta(0,3);
    adicionaAresta(3,6);
    adicionaAresta(1,4);
    adicionaAresta(4,7);
    adicionaAresta(2,5);
    adicionaAresta(8,11);

    ///Adicionando nó inicio e fim manualmente
    inicio = listaNo.at(11);
    fim = listaNo.at(6);
}

Matriz::~Matriz() { }

void Matriz::adicionaAresta(int id1, int id2)
{
    listaAresta.push_back(new Aresta(listaNo.at(id1),listaNo.at(id2)));
    if(id1 < id2){
        if(id2-id1 < numColunas){
            listaNo.at(id1)->setArestaDireita(true);
            listaNo.at(id2)->setArestaEsquerda(true);
        } else {
            listaNo.at(id1)->setArestaAbaixo(true);
            listaNo.at(id2)->setArestaAcima(true);
        }
    } else if(id1 > id2){
        if(id1-id2 < numColunas){
            listaNo.at(id1)->setArestaEsquerda(true);
            listaNo.at(id2)->setArestaDireita(true);
        } else {
            listaNo.at(id1)->setArestaAcima(true);
            listaNo.at(id2)->setArestaAbaixo(true);
        }
    }
}

Aresta* Matriz::buscaAresta(No* ant, No* prox)
{
    for(int i=0; i<listaAresta.size(); i++){
        if((listaAresta.at(i)->getNoAnt() == ant) && (listaAresta.at(i)->getNoProx() == prox))
            return listaAresta.at(i);
        if((listaAresta.at(i)->getNoAnt() == prox) && (listaAresta.at(i)->getNoProx() == ant))
            return listaAresta.at(i);
    }
    return NULL;
}

No* Matriz::consulta(int linha, int coluna)
{
    int k = determinaId(linha, coluna);
    if(k != -1)
        return listaNo.at(k);
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
                cout << listaNo.at(determinaId(i,j))->getId() << ".";
            else
                cout << listaNo.at(determinaId(i,j))->getId() << ", \t";
        }
        cout << endl;
    }
}

///Funcoes auxiliares
/////////////////////

void Matriz::defineVisitasPossiveis(){
    for(int i=0; i<listaNo.size(); i++){
        if(listaNo.at(i)->getArestaEsquerda())
            listaNo.at(i)->regras.push_back(listaNo.at(listaNo.at(i)->getId() - 1));
        if(listaNo.at(i)->getArestaAbaixo())
            listaNo.at(i)->regras.push_back(listaNo.at(listaNo.at(i)->getId() + numColunas));
        if(listaNo.at(i)->getArestaDireita())
            listaNo.at(i)->regras.push_back(listaNo.at(listaNo.at(i)->getId() + 1));
        if(listaNo.at(i)->getArestaAcima())
            listaNo.at(i)->regras.push_back(listaNo.at(listaNo.at(i)->getId() - numColunas));
    }
}

double Matriz::calculaValorHeuristica(No* atual, No* fim){
    double distanciaX = double(fim->coordenadaX - atual->coordenadaX);
    double distanciaY = double(fim->coordenadaY - atual->coordenadaY);
    cout << "Heuristica entre no candidato " << atual->getId() << " e " << fim->getId() << ": " << sqrt(distanciaX*distanciaX + distanciaY*distanciaY) << endl;
    return sqrt(distanciaX*distanciaX + distanciaY*distanciaY);
}

void printaCaminho(vector<int> caminho){
    cout << endl << "Solucao encontrada! O trajeto eh: ";
    for(int i=0; i<caminho.size(); i++){
        cout << caminho.at(i) << " - ";
    }
}

///Funcoes dos algoritmos
/////////////////////////

void Matriz::backtracking()
{
    defineVisitasPossiveis();
    vector<int> caminho;
    No* aux;
    No* no = inicio;
    bool fracasso = false;
    bool sucesso = false;

    caminho.push_back(no->getId());
    while(!(sucesso || fracasso)){
        no->setVisitado(true);
        if(no->regras.size() != 0){
            aux = no->regras.back();
            no->regras.pop_back();
            if(((no == inicio) || (aux != no->getPai()))&&(!aux->getVisitado())){
                aux->setPai(no);
                no = aux;
                caminho.push_back(no->getId());
            }
            if(no == fim){
                sucesso = true;
            }
        } else {
            if(no == inicio){
                fracasso = true;
            } else {
                no = no->getPai();
                caminho.push_back(no->getId());
            }
        }
    }

    if (sucesso)
        printaCaminho(caminho);
    else if (fracasso) cout << "Nao se encontrou uma solucao." << endl;
}

void Matriz::buscaGulosa(){
    defineVisitasPossiveis();
    vector<int> caminho;
    No* aux;
    No* noAtual = inicio;
    bool fracasso = false;
    bool sucesso = false;
    int valorAtual=0;

    caminho.push_back(noAtual->getId());
    while(!(sucesso || fracasso)){
        //caso de parada
        if (noAtual == fim){
            sucesso = true;
            break;
        }
        noAtual->setVisitado(true);
        No* proximoNo = NULL;
        No* noCandidato = NULL;
        while (noAtual->regras.size() != 0){
            noCandidato = noAtual->regras.back();
            noAtual->regras.pop_back();
            int valorCandidato = calculaValorHeuristica(noCandidato, fim);
            if (!(noCandidato->getVisitado())){
            //se nenhum no foi considerado como proximo ate agora, ele passa a ser o proximo do momento
                if (proximoNo==NULL){
                    valorAtual = valorCandidato;
                    proximoNo = noCandidato;

                //senao, vamos compara-lo ao proximoNo que temos no momento
                } else {
                    if (valorCandidato<valorAtual){
                        valorAtual = valorCandidato;
                        proximoNo = noCandidato;
                    }
                }
            }
        }

        if(proximoNo == NULL){
            fracasso = true;
        } else {
            noAtual = proximoNo;
            caminho.push_back(proximoNo->getId());
        }
    }

    if (sucesso)
        printaCaminho(caminho);
    else if (fracasso) cout << "Nao se encontrou uma solucao." << endl;
}

void Matriz::buscaLargura()
{
    defineVisitasPossiveis();
    queue<No*> abertos;
    queue<No*> fechados;
    No* no;
    Aresta* aux;
    bool sucesso = false;
    bool fracasso = false;
    abertos.push(inicio);

    while(!(sucesso || fracasso)){
        if(abertos.size() == 0)
            fracasso = true;
        else{
            no = abertos.front();
            if(no == fim){
                sucesso = true;
            } else{
                while(no->regras.size() != 0){
                    aux = buscaAresta(no,no->regras.back());
                    if(!aux->getVisitado()){
                        abertos.push(no->regras.back());
                        aux->setVisitado(true);
                    }
                    no->regras.pop_back();
                }
                abertos.pop();
            }
            fechados.push(no);
        }
    }

    while(fechados.size()!=0)
    {
        cout << fechados.front()->getId() << " - ";
        fechados.pop();
    }
}

void Matriz::buscaProfundidade()
{
    defineVisitasPossiveis();
    stack<No*> abertos;
    stack<No*> fechados;
    No* no;
    No* aux;
    bool sucesso = false;
    bool fracasso = false;
    abertos.push(inicio);

    while(!(sucesso || fracasso)){
        if(abertos.size() == 0)
            fracasso = true;
        else{
            no = abertos.top();
            if(no == fim){
                sucesso = true;
                fechados.push(no);
            } else{
                if(no->getVisitado())
                    abertos.pop();
                else{
                    while(no->regras.size() != 0){
                        aux = no->regras.back();
                        if(!aux->getVisitado()){
                            abertos.push(no->regras.back());
                        }
                        no->regras.pop_back();
                        no->setVisitado(true);
                    }
                    fechados.push(no);
                }
            }
        }
    }

    while(fechados.size()!=0)
    {
        cout << fechados.top()->getId() << " - ";
        fechados.pop();
    }
}
