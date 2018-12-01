#ifndef NO_H
#define NO_H


class No
{
    public:
        No(int indice);
        No() { }
        ~No();

        int getId() { return id; }
        bool getVisitado() { return visitado; }
        void setVisitado(bool val) { visitado = val; }
        bool getRegraBt() { return regraBt; }
        void setRegraBt(bool val) { regraBt = val; }

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
        int regraBt;
};

#endif // NO_H
