#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "sudoku.h"

/****************************************/
/* Objectif : Construction d'une cellule
/****************************************/
cellule::cellule(int i, int j)
{
    this->l = i;
    this->c = j;
    this->b = (this->l / 3) * 3 + (this->c / 3);
    this->n = 0;
}

cellule::cellule()
{
    this->l = 0;
    this->c = 0;
    this->b = 0;
    this->n = 0;
}

/****************************************/
/* Objectif : Construteur avec argument
permettant la création d'une grille à partir d'un
fichier.
/****************************************/
sudoku::sudoku(char filename[])
{
    // Tableau à false
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ligne[i][j] = false;
            colonne[i][j] = false;
            bloc[i][j] = false;
        }
    }
    // init grille avec cellules
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            grille[i][j] = cellule(i, j);
    }

    ifstream file(filename);
    if (!file)
    {
        cout << "Fichier non trouvé" << endl;
        return;
    }
    int q;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            file >> q;
            grille[i][j].n = q;
            if (q != 0)
            {
                ligne[i][q] = true;
                colonne[j][q] = true;
                bloc[(i / 3) * 3 + (j / 3)][q] = true;
            }
            else
            {
                this->C[this->emptycell] = new cellule(i, j);
                this->emptycell++;
            }
        }
    }
    file.close();
}

/****************************************/
/* Objectif : Affichage de la grille sudoku
/****************************************/
void sudoku::affichage()
{
    cout << setw(3) << "-" << "------------------------------------" << endl;
    for (int i = 0; i < 9; i++)
    {
        if ((i == 3) || (i == 6))
            cout << setw(3) << "-" << "------------------------------------" << endl;
        cout << setw(3) << "|";
        for (int j = 0; j < 8; j++)
        {
            if ((j == 3) || (j == 6))
                cout << setw(3) << "|" << setw(3) << grille[i][j].n;
            else
                cout << setw(3) << grille[i][j].n;
        }
        cout << setw(3) << grille[i][8].n << setw(3) << "|" << endl;
    }
    cout << setw(3) << "-" << "------------------------------------" << endl;
}

/****************************************/
/* Objectif : Détermination d'une solution de la grille.
La méthode renvoie vrai si une solution a été trouvée, 0 sinon
/****************************************/

bool sudoku::solution(char choix)
{
    if (choix == '1')
        return backtracking1(this->C, 0);
    else
        return backtracking2(this->C, 0);
}

bool sudoku::checkligne(int i, int k)
{
    for (int j = 0; j < 9; j++)
    {
        if (grille[i][j].n == k)
        {
            return false;
        }
    }
    return true;
}

bool sudoku::checkcolonne(int j, int k)
{
    for (int i = 0; i < 9; i++)
    {
        if (grille[i][j].n == k)
        {
            return false;
        }
    }
    return true;
}

bool sudoku::checkbloc(int i, int j, int k)
{
    int ii = (i / 3) * 3;
    int jj = (j / 3) * 3;

    for (int ligne = ii; ligne < ii + 3; ligne++)
    {
        for (int colonne = jj; colonne < jj + 3; colonne++)
        {
            if (grille[ligne][colonne].n == k)
            {
                return false;
            }
        }
    }

    return true;
}

bool sudoku::check(int i, int j, int k)
{
    return (checkligne(i, k) && checkcolonne(j, k) && checkbloc(i, j, k));
}

bool sudoku::backtracking1(cellule *C[], int k)
{
    if (k == this->emptycell)
    {
        return true;
    }
    else
    {
        for (int j = 1; j < 10; j++)
        {
            if (check(C[k]->l, C[k]->c, j))
            {
                grille[C[k]->l][C[k]->c].n = j;
                if (backtracking1(C, k + 1))
                    return true;
                grille[C[k]->l][C[k]->c].n = 0;
            }
        }
    }
    return false;
}

bool sudoku::backtracking2(cellule *C[], int k)
{
    if (k == this->emptycell)
    {
        return true;
    }
    else
    {
        for (int j = 1; j < 10; j++)
        {
            if (!ligne[C[k]->l][j] && !colonne[C[k]->c][j] && !bloc[C[k]->b][j])
            {
                grille[C[k]->l][C[k]->c].n = j;
                ligne[C[k]->l][j] = true;
                colonne[C[k]->c][j] = true;
                bloc[C[k]->b][j] = true;
                if (backtracking2(C, k + 1))
                    return true;
                grille[C[k]->l][C[k]->c].n = 0;
                ligne[C[k]->l][j] = false;
                colonne[C[k]->c][j] = false;
                bloc[C[k]->b][j] = false;
            }
        }
    }
    return false;
}
