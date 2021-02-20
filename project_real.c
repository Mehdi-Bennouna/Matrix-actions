#include <stdio.h>
#include <curses.h>
#include <windows.h>
#include <stdlib.h>

typedef struct l_choix
{
    int nombre_choix_valide;
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
void print_menu(WINDOW *fenetre_menu, int selection, liste_choix choix);
int afficher_menu(liste_choix choix);

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

    liste_choix choix = {5, 5, liste_choix_0}; //initialisation au menu principal
    int n_liste_choix = 0;

    while (n_liste_choix != 4)
    {
        n_liste_choix = afficher_menu(choix);

        if (n_liste_choix == 1)
        {
            choix.liste = liste_choix_1;
            choix.nombre_choix = 7;
            choix.nombre_choix_valide = 7;

            n_liste_choix = afficher_menu(choix);
        }

        if (n_liste_choix == 2)
        {
            choix.liste = liste_choix_2;
            choix.nombre_choix = 7;
            choix.nombre_choix_valide = 7;

            n_liste_choix = afficher_menu(choix);
        }

        if (n_liste_choix == 3)
        {
            choix.liste = liste_choix_3;
            choix.nombre_choix = 9;
            choix.nombre_choix_valide = 9;

            n_liste_choix = afficher_menu(choix);
        }
    }

    wgetch(stdscr);

    endwin();
}

void afficher_cadre(liste_choix choix)
{
    box(stdscr, 0, 0);
    mvprintw(0, (50 - strlen(choix.liste[0]) / 2), " %s ", choix.liste[0]);
    refresh();
}

int afficher_menu(liste_choix choix)
{
    afficher_cadre(choix);
    int LARGEUR = 51;
    int HAUTEUR = 20;

    int debutx = 25;
    int debuty = 6;

    WINDOW *fenetre_menu;
    int selection = 2;
    int choice = 0;
    int c;

    debutx = 25;
    debuty = 1;
    fenetre_menu = newwin(HAUTEUR, LARGEUR, debuty, debutx);
    keypad(fenetre_menu, TRUE);

    print_menu(fenetre_menu, selection, choix);
    while (1)
    {
        c = wgetch(fenetre_menu);
        switch (c)
        {
        case KEY_UP:
            if (selection == 2)
                selection = choix.nombre_choix;
            else
                --selection;
            break;
        case KEY_DOWN:
            if (selection == choix.nombre_choix)
                selection = 2;
            else
                ++selection;
            break;
        case 10:
            choice = selection;
            break;
        default:
            refresh();
            break;
        }
        print_menu(fenetre_menu, selection, choix);
        if (choice != 0) /* sortie de boucle */
            break;
    }
    refresh();

    return choice - 1;
}

void print_menu(WINDOW *fenetre_menu, int selection, liste_choix choix)
{
    int x, y, i;

    y = 6;
    for (i = 1; i < choix.nombre_choix; ++i)
    {
        if (selection == i + 1) /* Highlight the present choice */
        {
            wattron(fenetre_menu, A_REVERSE);
            mvwprintw(fenetre_menu, y, (25 - strlen(choix.liste[i]) / 2), "%s", choix.liste[i]);
            wattroff(fenetre_menu, A_REVERSE);
        }
        else
            mvwprintw(fenetre_menu, y, (25 - strlen(choix.liste[i]) / 2), "%s", choix.liste[i]);
        ++y;
    }
    wrefresh(fenetre_menu);
}