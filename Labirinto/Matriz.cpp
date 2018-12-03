#include "Matriz.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <queue>
#include <stack>

using namespace std;

void printaCaminho(vector<int> caminho);
void insereNaListaAtual (vector<No*> listaAtual, No* umNo);

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

//    //Na horizontal:
//    adicionaAresta(0,1);
//    adicionaAresta(3,4);
//    adicionaAresta(4,5);
//    adicionaAresta(9,10);
//    adicionaAresta(7,8);
//    adicionaAresta(10,11);
//
//    //Na vertical:
//    adicionaAresta(0,3);
//    adicionaAresta(3,6);
//    adicionaAresta(1,4);
//    adicionaAresta(4,7);
//    adicionaAresta(2,5);
//    adicionaAresta(8,11);

    //int totalArestas = ceil((m*n*2)/3.0);
    int totalArestas = 2*m*n;
    int totalInsercoes = 0;
    int valorMaximoDoNo = m*n;
    while (totalInsercoes<totalArestas){
        //cout << "Entrou ";

        int primeiroNo = rand() % valorMaximoDoNo;
        int segundoNo=0;

        ///selecao da direcao da aresta
        int escolha = rand() % 4;
        if ((escolha == 0) && (((primeiroNo+1)%numColunas)!=0)){
            segundoNo = primeiroNo+1;
            adicionaAresta(primeiroNo, segundoNo);
            cout << primeiroNo << " " << segundoNo << " " << escolha << endl;
            //cout << "entrou na insercao e incremento" << endl;
            totalInsercoes++;
        }
        else if ((escolha == 1) && ((primeiroNo%numColunas)!=0)){
            segundoNo = primeiroNo-1;
            adicionaAresta(primeiroNo, segundoNo);
            cout << primeiroNo << " " << segundoNo << " " << escolha << endl;
            //cout << "entrou na insercao e incremento" << endl;
            totalInsercoes++;
        }
        else if ((escolha == 2) && ((primeiroNo-numColunas)>=0)){
            segundoNo = primeiroNo-n;
            adicionaAresta(primeiroNo, segundoNo);
            cout << primeiroNo << " " << segundoNo << " " << escolha << endl;
            //cout << "entrou na insercao e incremento" << endl;
            totalInsercoes++;
        }
        else if ((escolha == 3) && ((primeiroNo+numColunas)<n*m)){
            segundoNo = primeiroNo+n;
            adicionaAresta(primeiroNo, segundoNo);
            cout << primeiroNo << " " << segundoNo << " " << escolha << endl;
            //cout << "entrou na insercao e incremento" << endl;
            totalInsercoes++;
        }
    }

    ///Adicionando nó inicio e fim manualmente.
    ///Neste labirinto 9x9, existe solucao
    inicio = listaNo.at(0);
    fim = listaNo.at((n*m)-1);
}

Matriz::~Matriz() { }

void Matriz::imprimeLabirinto(){
    for(int j=0; j<numColunas; j++){
        printf("%3d", j);
    }
    cout << endl;
    for(int j=0; j<numColunas; j++){
        printf("___");
    }
    cout << "_" << endl;
    for(int i=0; i<numLinhas; i++){
        cout << "|";
        for (int j=0; j<numColunas; j++){
            if (listaNo.at(i*numColunas+j)->getArestaAbaixo()){
                cout << "  ";
            } else cout << "__";
            if (listaNo.at(i*numColunas+j)->getArestaDireita()){
                cout << ":";
            } else cout << "|";

        }
        cout << endl;
    }
}

int Matriz::adicionaAresta(int id1, int id2)
{
    if (buscaAresta(listaNo.at(id1),listaNo.at(id2))!=NULL) return 0;
    listaAresta.push_back(new Aresta(listaNo.at(id1),listaNo.at(id2)));
    double valor = 1.0 + ((double)(rand()%11) / 10.0);
    //gerando valores entre 1 e 2
    //cout << "Valor da aresta: " << valor << endl;
    if(id1 < id2){
        if(id2-id1 < numColunas){
            listaNo.at(id1)->setArestaDireita(true);
            listaNo.at(id2)->setArestaEsquerda(true);

            listaNo.at(id1)->custoArestaDireita = valor;
            listaNo.at(id2)->custoArestaEsquerda = valor;
        } else {
            listaNo.at(id1)->setArestaAbaixo(true);
            listaNo.at(id2)->setArestaAcima(true);

            listaNo.at(id1)->custoArestaAbaixo = valor;
            listaNo.at(id2)->custoArestaAcima = valor;
        }
    } else if(id1 > id2){
        if(id1-id2 < numColunas){
            listaNo.at(id1)->setArestaEsquerda(true);
            listaNo.at(id2)->setArestaDireita(true);

            listaNo.at(id1)->custoArestaEsquerda = valor;
            listaNo.at(id2)->custoArestaDireita = valor;
        } else {
            listaNo.at(id1)->setArestaAcima(true);
            listaNo.at(id2)->setArestaAbaixo(true);

            listaNo.at(id1)->custoArestaAcima = valor;
            listaNo.at(id2)->custoArestaAbaixo = valor;
        }
    }
    return 1;
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

void Matriz::insereNaListaAtual(vector<No*> *listaAtual, No* no){
    if(no->getArestaEsquerda() && !(listaNo.at(no->getId()-1)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()-1);
        noAtual->setVisitado(true);
        listaAtual->push_back(noAtual);
        noAtual->caminhoAteEsteNo = no->caminhoAteEsteNo;
        noAtual->caminhoAteEsteNo.push_back(noAtual->getId());
        noAtual->custoAcumulado = no->custoAcumulado + no->custoArestaEsquerda;
    }
    if(no->getArestaDireita() && !(listaNo.at(no->getId()+1)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()+1);
        noAtual->setVisitado(true);
        listaAtual->push_back(noAtual);
        noAtual->caminhoAteEsteNo = no->caminhoAteEsteNo;
        noAtual->caminhoAteEsteNo.push_back(noAtual->getId());
        noAtual->custoAcumulado = no->custoAcumulado + no->custoArestaDireita;
    }
    if(no->getArestaAcima() && !(listaNo.at(no->getId()-numColunas)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()-numColunas);
        noAtual->setVisitado(true);
        listaAtual->push_back(noAtual);
        noAtual->caminhoAteEsteNo = no->caminhoAteEsteNo;
        noAtual->caminhoAteEsteNo.push_back(noAtual->getId());
        noAtual->custoAcumulado = no->custoAcumulado + no->custoArestaAcima;
    }
    if(no->getArestaAbaixo() && !(listaNo.at(no->getId()+numColunas)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()+numColunas);
        noAtual->setVisitado(true);
        listaAtual->push_back(noAtual);
        noAtual->caminhoAteEsteNo = no->caminhoAteEsteNo;
        noAtual->caminhoAteEsteNo.push_back(noAtual->getId());
        noAtual->custoAcumulado = no->custoAcumulado + no->custoArestaAbaixo;
    }
}

void Matriz::insereEmFechados(vector<No*> *listaAtual, No* no){
    if(no->getArestaEsquerda() && !(listaNo.at(no->getId()-1)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()-1);
        listaAtual->push_back(noAtual);
    }
    if(no->getArestaDireita() && !(listaNo.at(no->getId()+1)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()+1);
        listaAtual->push_back(noAtual);
    }
    if(no->getArestaAcima() && !(listaNo.at(no->getId()-numColunas)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()-numColunas);
        listaAtual->push_back(noAtual);
    }
    if(no->getArestaAbaixo() && !(listaNo.at(no->getId()+numColunas)->getVisitado())){
        No* noAtual = listaNo.at(no->getId()+numColunas);
        listaAtual->push_back(noAtual);
    }
}

///Funcoes dos algoritmos
/////////////////////////

void Matriz::buscaOrdenada(){
    vector<No*> folhasAtuais;
    inicio->caminhoAteEsteNo.push_back(inicio->getId());
    //insereEmFechados(&folhasAtuais, inicio);
    folhasAtuais.push_back(inicio);

    No* melhorNo;
    No* noPai = inicio;
    int indexDoMelhorNo;
    double valorDoMelhorNo;

    bool fracasso = false;
    bool sucesso = false;
    bool conseguiuInserir = false;

    defineVisitasPossiveis();

    while(!(sucesso || fracasso)){
        //casos de parada
        for (int i=0; i<folhasAtuais.size(); i++){
            if (folhasAtuais.at(i)==fim){
                sucesso = true;
                goto end;
            }
        }
        ///valorDoMelhorNo = melhorNo->custoAcumulado + calculaValorHeuristica(melhorNo, fim);
        No* melhorNo;
        int valorMelhor = 1000000000;
        int valorCandidato;

        for (int i=0; i<folhasAtuais.size(); i++){
            if(folhasAtuais.at(i)->getArestaEsquerda()){
                if (!(listaNo.at((folhasAtuais.at(i)->getId()) - 1)->getVisitado())){
                    valorCandidato = folhasAtuais.at(i)->custoAcumulado + folhasAtuais.at(i)->custoArestaEsquerda;
                    if (valorCandidato<valorMelhor){
                        noPai = folhasAtuais.at(i);
                        valorMelhor = valorCandidato;
                        melhorNo = listaNo.at(folhasAtuais.at(i)->getId() - 1);
                        conseguiuInserir = true;
                    }
                }
            }
            if(folhasAtuais.at(i)->getArestaDireita()){
                if (!(listaNo.at((folhasAtuais.at(i)->getId()) + 1)->getVisitado())){
                    valorCandidato = folhasAtuais.at(i)->custoAcumulado + folhasAtuais.at(i)->custoArestaDireita;
                    if (valorCandidato<valorMelhor){
                        noPai = folhasAtuais.at(i);
                        valorMelhor = valorCandidato;
                        melhorNo = listaNo.at(folhasAtuais.at(i)->getId() + 1);
                        conseguiuInserir = true;
                    }
                }
            }
            if(folhasAtuais.at(i)->getArestaAbaixo()){
               if (!(listaNo.at((folhasAtuais.at(i)->getId()) + numColunas)->getVisitado())){
                    valorCandidato = folhasAtuais.at(i)->custoAcumulado + folhasAtuais.at(i)->custoArestaAbaixo;
                    if (valorCandidato<valorMelhor){
                        noPai = folhasAtuais.at(i);
                        valorMelhor = valorCandidato;
                        melhorNo = listaNo.at(folhasAtuais.at(i)->getId() + numColunas);
                        conseguiuInserir = true;
                    }
                }
            }
            if(folhasAtuais.at(i)->getArestaAcima()){
                if (!(listaNo.at((folhasAtuais.at(i)->getId()) - numColunas)->getVisitado())){
                    valorCandidato = folhasAtuais.at(i)->custoAcumulado + folhasAtuais.at(i)->custoArestaAcima;
                    if (valorCandidato<valorMelhor){
                        noPai = folhasAtuais.at(i);
                        valorMelhor = valorCandidato;
                        melhorNo = listaNo.at(folhasAtuais.at(i)->getId() - numColunas);
                        conseguiuInserir = true;
                    }
                }
            }
        }
        if (!conseguiuInserir){
            fracasso = true;
            goto end;
        }

        //cout << "melhor noh selecionado! tem o id " << melhorNo->getId() << endl;
        melhorNo->setVisitado(true);
        melhorNo->custoAcumulado = valorMelhor;
        melhorNo->caminhoAteEsteNo = noPai->caminhoAteEsteNo;
        melhorNo->caminhoAteEsteNo.push_back(melhorNo->getId());

        //insereEmFechados(&folhasAtuais, melhorNo);
        folhasAtuais.push_back(melhorNo);

    }


    end:
    if (sucesso){
        printaCaminho(fim->caminhoAteEsteNo);
        cout << "\n Nos expandidos: " << fim->caminhoAteEsteNo.size() << "\n";
    }
    else if (fracasso) cout << "Nao se encontrou uma solucao." << endl;
}

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

    if (sucesso){
        printaCaminho(caminho);
        cout << "\n Nos expandidos: " << caminho.size() << "\n" ;
    }
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

    if (sucesso){
        printaCaminho(caminho);
        cout << "\n Nos expandidos: " << caminho.size() << "\n";
    }
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
    int numExplorados = fechados.size();
    while(fechados.size()!=0)
    {
        cout << fechados.front()->getId() << " - ";
        fechados.pop();
    }
    cout << "\n Nos expandidos: " << numExplorados << "\n";
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

    int numExplorados = fechados.size();
    while(fechados.size()!=0)
    {
        cout << fechados.top()->getId() << " - ";
        fechados.pop();
    }
    cout << "\n Nos expandidos: " << numExplorados << "\n";
}

void Matriz::buscaA(){
    vector<No*> folhasAtuais;
    inicio->caminhoAteEsteNo.push_back(inicio->getId());
    insereNaListaAtual(&folhasAtuais, inicio);

    No* melhorNo;
    int indexDoMelhorNo;
    double valorDoMelhorNo;

    bool fracasso = false;
    bool sucesso = false;

    while(!(sucesso || fracasso)){
        //casos de parada
        for (int i=0; i<folhasAtuais.size(); i++){
            if (folhasAtuais.at(i)==fim){
                sucesso = true;
                goto end;
            }
        }

        if (folhasAtuais.size()==0){
            fracasso = true;
            goto end;
        }

        melhorNo = folhasAtuais.at(0);
        indexDoMelhorNo = 0;
        valorDoMelhorNo = melhorNo->custoAcumulado + calculaValorHeuristica(melhorNo, fim);

        for (int i=1; i<folhasAtuais.size(); i++){
            double valorCandidatoAtual = folhasAtuais.at(i)->custoAcumulado+calculaValorHeuristica(folhasAtuais.at(i), fim);
            cout << "O valor candidato atual eh: " << valorCandidatoAtual << endl;
            if (valorDoMelhorNo>valorCandidatoAtual){
                valorDoMelhorNo = valorCandidatoAtual;
                melhorNo = folhasAtuais.at(i);
                indexDoMelhorNo = i;
            }
        }
        folhasAtuais.erase(folhasAtuais.begin()+indexDoMelhorNo);
        insereNaListaAtual(&folhasAtuais, melhorNo);
    }


    end:
    if (sucesso){
        printaCaminho(fim->caminhoAteEsteNo);
        cout << "\n Nos expandidos: " << fim->caminhoAteEsteNo.size() << "\n";
    {
    else if (fracasso) cout << "Nao se encontrou uma solucao." << endl;
}

void Matriz::buscaIDA(){

}

