#ifndef NO_H
#define NO_H
#include <vector>

using namespace std;

class No
{
    public:
        No(int indice, int X, int Y);
        No() { }
        ~No();

        int coordenadaX;
        int coordenadaY;

        vector<No*> regras;
        int getId() { return id; }
        bool getVisitado() { return visitado; }
        void setVisitado(bool val) { visitado = val; }
        No* getPai() { return pai; }
        void setPai(No* val) { pai = val; }

        //Arestas
        bool getArestaAcima() { return arestaAcima; }
        void setArestaAcima(bool acima) { arestaAcima = acima; }
        bool getArestaAbaixo() { return arestaAbaixo; }
        void setArestaAbaixo(bool abaixo) { arestaAbaixo = abaixo; }
        bool getArestaEsquerda() { return arestaEsquerda; }
        void setArestaEsquerda(bool esquerda) { arestaEsquerda = esquerda; }
        bool getArestaDireita() { return arestaDireita; }
        void setArestaDireita(bool direita) { arestaDireita = direita; }

    protected:

    private:
        int id;
        bool arestaAcima;
        bool arestaAbaixo;
        bool arestaEsquerda;
        bool arestaDireita;
        bool visitado;
        No* pai;
};

#endif // NO_H
