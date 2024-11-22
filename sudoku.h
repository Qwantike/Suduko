/****************************************************************/
/* Auteur : S. Gueye						                    */
/* TP : Sudoku bactracking algorithm				            */
/* Date dernière maj : 24/11/2020				                */
/****************************************************************/

/****************************************************************/
/* Objectif : Classe représentant une cellule de la grille
/****************************************************************/
class cellule
{
public:
    int l;                 // Numéro de ligne
    int c;                 // Numéro de colonne
    int b;                 // Numéro du bloc où se situe la cellule (l,c)
    int n;                 // Nombre de chiffres qu'il est possible initialement d'utiliser sur la cellule
    cellule();             // Constructeur sans arguments
    cellule(int i, int j); // Construit la cellule de numéro de ligne i et colonne j
};

/****************************************************************/
/* Objectif : Classe permettant de lire une grille sudoku et de la résoudre
/****************************************************************/
class sudoku
{
    cellule grille[9][9]; // La grille
    bool ligne[9][10];
    bool colonne[9][10];
    bool bloc[9][10];
    int emptycell = 0;
    cellule *C[81];

public:
    sudoku(char filename[]);   // Lecture de la grille sudoku se trouvant dans le fichier filename
    void affichage();          // Affichage de la grille
    bool solution(char choix); // Calcul de solution
    bool checkligne(int i, int k);
    bool checkcolonne(int j, int k);
    bool check(int i, int j, int k);
    bool checkbloc(int i, int j, int k);
    bool backtracking1(cellule *C[], int k);
    bool backtracking2(cellule *C[], int k);
};
