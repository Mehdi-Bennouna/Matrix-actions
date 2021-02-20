#include <stdio.h>
#include <curses.h>
#include <windows.h>
#include <stdlib.h>

typedef struct l_choix
{
    int nombre_choix;
    char **liste;
} liste_choix;

//*******************listes de choix******************************//
char *liste_choix_0[] = {
    " Menu Principal ",
    "- Operations arithmetiques sur les matrices -",
    "- Autres operations sur les matrices -",
    "- Chaines de caracteres et listes chainees -",
    "- Quiter -"};

char *liste_choix_1[] = {
    " Operations arithmetiques sur les matrices ",
    "- Somme de deux matrices -",
    "- Difference de deux matrices -",
    "- Multiplication d\'une matrice par un nombre -",
    "- Produit de deux matrices -",
    "- Inverse d\'une matrice -",
    "- Retour -"};

char *liste_choix_2[] = {
    " Autres operations sur les matrices ",
    "- Transposee d'une matrice -",
    "- Tri d\'une matrice -",
    "- Calcul du vecteur Maxligne -",
    "- Calcul du vecteur Maxcolonne -",
    "- Extraction de sous-matrices -",
    "- Retour -"};

char *liste_choix_3[] = {
    " Chaines de caracteres et listes chainees ",
    "- Saisie du texte -",
    "- Creation de la matrice de mots -",
    "- Affichage de la matrice -",
    "- Creation de la structure de listes -",
    "- Affichage de la structure -",
    "- Ajout d\'un mot -",
    "- Suppression d\'un mot -",
    "- Retour - "};
//---------------------------------------------------------------//

HANDLE wHnd; // Handle to write to the console.
HANDLE rHnd; // Handle to read from the console.

void afficher_cadre(liste_choix choix);

int main()
{
    //*************taille terminal*********************//
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTitle("Projet Algo");
    SMALL_RECT windowSize = {0, 0, 101, 25};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    //--------------------------------------------//

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    liste_choix choix = {5, liste_choix_1};

    afficher_cadre(choix);
    wgetch(stdscr);

    endwin();
}

void afficher_cadre(liste_choix choix)
{
    box(stdscr, 0, 0);
    mvprintw(0, (50 - strlen(choix.liste[0]) / 2), " %s ", choix.liste[0]);
    refresh();
}