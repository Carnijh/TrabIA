#include <iostream>
#include <cstdlib>
#include "Matriz.h"

using namespace std;

void exibeMenu(Matriz* labirinto);

int main()
{
    Matriz* labirinto = new Matriz(9,9);
    labirinto->imprimeLabirinto();
    labirinto->imprime();
    //---------------- MENU ----------------
    while(true){
    exibeMenu(labirinto);
    }
    //---------------- MENU ----------------
    delete labirinto; //Desalocar labirinto
    return 0;
}

void exibeMenu(Matriz* labirinto)
{
    int opMenu;
    cout << "------------------ MENU ------------------" << endl;
    cout << "1- Backtracking" << endl;
    cout << "2- Busca em largura" << endl;
    cout << "3- Busca em profundidade" << endl;
    cout << "4- Busca Ordenada" << endl;
    cout << "5- Busca Gulosa" << endl;
    cout << "6- Busca A*" << endl;
    cout << "7- Busca IDA*" << endl;
    cout << "0 ou outro- Sair" << endl;
    cout << "Opcao: ";
    cin >> opMenu;
    system("cls");

    switch (opMenu)
    {
        case 1:
            labirinto->backtracking();
            system("pause");
            system("cls");
            break;
        case 2:
            labirinto->buscaLargura();
            system("pause");
            system("cls");
            break;
        case 3:
            labirinto->buscaProfundidade();
            system("pause");
            system("cls");
            break;
        case 4:
            labirinto->buscaOrdenada();
            system("pause");
            system("cls");
            break;
        case 5:
            labirinto->buscaGulosa();
            system("pause");
            system("cls");
            break;
        case 6:
            labirinto->buscaA();
            system("pause");
            system("cls");
            break;
        case 7:
            //labirinto->buscaIDA();
            system("pause");
            system("cls");
            break;
        default: break;
    }
}
