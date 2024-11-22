#include <iostream>

using namespace std;

#include "sudoku.cpp"

/************************************************/
/* Programme principal				*/
/* argc : nombre d'arguments à l'appel du 	*/
/* programme exécutable				*/
/* argv : Liste des arguments			*/
/************************************************/
int main(int argc, char **argv)
{
    if (argc < 2)
        cout << "Nombre d'arguments insuffisants" << endl;
    else
    {
        sudoku sudo(argv[1]);
        char choix;
        cout << "résolution backtracking 1 ou 2 ? " << endl;
        cin >> choix;
        while (choix != '1' && choix != '2')
        {
            cout << "résolution backtracking 1 ou 2 ? " << endl;
            cin >> choix;
        }
        sudo.affichage();
        cout << "Solution de la grille du fichier" << endl;
        sudo.solution(choix);
        sudo.affichage();
    }

    return (1);
}
