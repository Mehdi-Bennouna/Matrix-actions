#include <stdio.h>
#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

typedef struct Matrices
{
    int nombre_lignes;
    int nombre_colonnes;
    int nombre_elements;
    int **mat;
} Matrice;

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
//--------------------------------   FONCTIONS    AFFICHAGE ---------------------------------------------------------------------//

void afficher_cadre(liste_choix choix);
void print_menu(WINDOW *fenetre_menu, int selection, liste_choix choix);
int afficher_menu(liste_choix choix);
int nombre_chifres(int x);
void popup_erreur(int x);

int *max_colonnes(Matrice m);

Matrice remplissage_matrice(Matrice m);

Matrice creation_matrice();
void affichage_matrice(Matrice m, int type, int posx, int posy);
void somme_deux_matrices();
void difference_deux_matrices();
void multiplication_matrice_nombre();
void multiplication_deux_matrices();
void transpose_matrice();
void tri_matrice();

//void affichage_op_deux_matrices(Matrice m1, Matrice m2, Matrice m3, char operation);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  FONCTIONS    AFFICHAGE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

//--------------------------------   FONCTIONS    CALCUL ---------------------------------------------------------------------//
Matrice op_somme_deux_matrice(Matrice m1, Matrice M2);
Matrice op_difference_deux_matrice(Matrice m1, Matrice M2);
Matrice op_multiplication_deux_matrices(Matrice m1, Matrice m2);
Matrice op_transpose_matrice(Matrice m1);
Matrice op_tri_matrice(Matrice m1);

//--------------------------------   FONCTIONS    CALCUL ---------------------------------------------------------------------//

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
            while (n_liste_choix != 6)
            {
                choix.liste = liste_choix_1;
                choix.nombre_choix = 7;
                choix.nombre_choix_valide = 7;

                n_liste_choix = afficher_menu(choix);

                if (n_liste_choix == 1)
                {
                    somme_deux_matrices();
                }
                else if (n_liste_choix == 2)
                {
                    difference_deux_matrices();
                }
                else if (n_liste_choix == 3)
                {
                    multiplication_matrice_nombre();
                }
                else if (n_liste_choix == 4)
                {
                    multiplication_deux_matrices();
                }
                else if (n_liste_choix == 5)
                {
                    //inverse de matrice
                }
            }
            choix.liste = liste_choix_0;
            choix.nombre_choix = 5;
            choix.nombre_choix_valide = 5;
        }

        if (n_liste_choix == 2)
        {
            while (n_liste_choix != 6)
            {
                choix.liste = liste_choix_2;
                choix.nombre_choix = 7;
                choix.nombre_choix_valide = 7;

                n_liste_choix = afficher_menu(choix);

                if (n_liste_choix == 1)
                {
                    transpose_matrice();
                }
                else if (n_liste_choix == 2)
                {
                    tri_matrice();
                }
            }
            choix.liste = liste_choix_0;
            choix.nombre_choix = 5;
            choix.nombre_choix_valide = 5;
        }

        if (n_liste_choix == 3)
        {
            choix.liste = liste_choix_3;
            choix.nombre_choix = 9;
            choix.nombre_choix_valide = 9;

            n_liste_choix = afficher_menu(choix);
        }
        n_liste_choix = 0;
    }

    wgetch(stdscr);

    endwin();
}

//--------------------------------   FONCTIONS    CALCUL ---------------------------------------------------------------------
Matrice op_somme_deux_matrices(Matrice m1, Matrice m2)
{
    Matrice m3;
    m3.nombre_lignes = m1.nombre_lignes;
    m3.nombre_colonnes = m1.nombre_colonnes;
    m3.nombre_elements = m1.nombre_elements;

    m3.mat = (int **)malloc(m3.nombre_lignes * sizeof(int *));

    for (int i = 0; i < m3.nombre_lignes; i++)
    {
        m3.mat[i] = (int *)malloc(m3.nombre_colonnes * sizeof(int));
    }

    for (int i = 0; i < m3.nombre_lignes; i++)
    {
        for (int j = 0; j < m3.nombre_colonnes; j++)
        {
            m3.mat[i][j] = m1.mat[i][j] + m2.mat[i][j];
        }
    }

    return m3;
}

Matrice op_difference_deux_matrices(Matrice m1, Matrice m2)
{
    Matrice m3;
    m3.nombre_lignes = m1.nombre_lignes;
    m3.nombre_colonnes = m1.nombre_colonnes;
    m3.nombre_elements = m1.nombre_elements;

    m3.mat = (int **)malloc(m3.nombre_lignes * sizeof(int *));

    for (int i = 0; i < m3.nombre_lignes; i++)
    {
        m3.mat[i] = (int *)malloc(m3.nombre_colonnes * sizeof(int));
    }

    for (int i = 0; i < m3.nombre_lignes; i++)
    {
        for (int j = 0; j < m3.nombre_colonnes; j++)
        {
            m3.mat[i][j] = m1.mat[i][j] - m2.mat[i][j];
        }
    }

    return m3;
}

Matrice op_multiplication_matrice_nombre(Matrice m1, int n)
{
    Matrice m2;
    m2.nombre_lignes = m1.nombre_lignes;
    m2.nombre_colonnes = m1.nombre_colonnes;
    m2.nombre_elements = m1.nombre_elements;

    m2.mat = (int **)malloc(m2.nombre_lignes * sizeof(int *));

    for (int i = 0; i < m2.nombre_lignes; i++)
    {
        m2.mat[i] = (int *)malloc(m2.nombre_colonnes * sizeof(int));
    }

    for (int i = 0; i < m2.nombre_lignes; i++)
    {
        for (int j = 0; j < m2.nombre_colonnes; j++)
        {
            m2.mat[i][j] = m1.mat[i][j] * n;
        }
    }
    return m2;
}

Matrice op_multiplication_deux_matrices(Matrice m1, Matrice m2)
{
    int i, j, k;
    Matrice m3;
    m3.nombre_lignes = m1.nombre_lignes;
    m3.nombre_colonnes = m2.nombre_colonnes;
    m3.nombre_elements = m3.nombre_lignes * m3.nombre_colonnes;

    m3.mat = (int **)malloc(m3.nombre_lignes * sizeof(int *));

    for (i = 0; i < m3.nombre_lignes; i++)
    {
        m3.mat[i] = (int *)malloc(m3.nombre_colonnes * sizeof(int));
    }

    for (i = 0; i < m3.nombre_lignes; i++)
    {
        for (j = 0; j < m3.nombre_colonnes; j++)
        {
            m3.mat[i][j] = 0;
        }
    }

    for (i = 0; i < m3.nombre_lignes; i++)
    {
        for (j = 0; j < m3.nombre_colonnes; j++)
        {
            for (k = 0; k < m3.nombre_colonnes; k++)
            {
                m3.mat[i][j] += m1.mat[i][k] * m2.mat[k][i];
            }
        }
    }

    return m3;
}

Matrice op_transpose_matrice(Matrice m1)
{
    Matrice m2;

    m2.nombre_lignes = m1.nombre_lignes;
    m2.nombre_colonnes = m1.nombre_colonnes;
    m2.nombre_elements = m1.nombre_elements;

    m2.mat = (int **)malloc(m2.nombre_lignes * sizeof(int *));

    for (int i = 0; i < m2.nombre_lignes; i++)
    {
        m2.mat[i] = (int *)malloc(m2.nombre_colonnes * sizeof(int));
    }

    for (int i = 0; i < m2.nombre_lignes; i++)
    {
        for (int j = 0; j < m2.nombre_colonnes; j++)
        {
            m2.mat[j][i] = m1.mat[i][j];
        }
    }

    return m2;
}

Matrice op_tri_matrice(Matrice m1)
{
    int min;

    for (int i = 0; i < m1.nombre_lignes; i++)
    {
        for (int j = 0; j < m1.nombre_colonnes; j++)
        {
            min = m1.mat[i][j];

            for (int x = 0; x < m1.nombre_lignes; x++)
            {
                for (int y = 0; y < m1.nombre_colonnes; y++)
                {
                    if (m1.mat[x][y] <= min)
                    {
                        min = m1.mat[x][y];
                        m1.mat[x][y] = m1.mat[i][j];
                        m1.mat[i][j] = min;
                    }
                }
            }
        }
    }

    return m1;
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  FONCTIONS    CALCUL ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

//--------------------------------   FONCTIONS    AFFICHAGE ---------------------------------------------------------------------
void tri_matrice()
{
    int ns_choix = 0;

    char *choix_multiplication_matrice_nombre[] = {" Tri Matrice ", "Remplir Matrice (vide)", "Calcul", "retour"};

    liste_choix s_choix = {4, 4, choix_multiplication_matrice_nombre};

    Matrice m1;

    int valide = 0;

    while (ns_choix != 3)
    {
        ns_choix = afficher_menu(s_choix);

        if (ns_choix == 1)
        {
            m1 = creation_matrice();
            m1 = remplissage_matrice(m1);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_multiplication_matrice_nombre[1] = "Remplir Matrice 1 (remplie)";
            }
        }
        else if (ns_choix == 2)
        {
            if (m1.nombre_elements == m1.nombre_colonnes * m1.nombre_lignes)
            {
                valide = 1;
            }

            if (valide == 1)
            {
                m1 = op_tri_matrice(m1);
                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m1); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * m1.nombre_lignes) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m1.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * m1.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 12 - (HAUTEUR / 2);
                affichage_matrice(m1, 1, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }
        }
    }
}

void transpose_matrice()
{
    int ns_choix = 0;

    char *choix_multiplication_matrice_nombre[] = {" Transpose Matrice ", "Remplir Matrice (vide)", "Calcul", "retour"};

    liste_choix s_choix = {4, 4, choix_multiplication_matrice_nombre};

    Matrice m1, m2;

    int valide = 0;

    while (ns_choix != 3)
    {
        ns_choix = afficher_menu(s_choix);

        if (ns_choix == 1)
        {
            m1 = creation_matrice();
            m1 = remplissage_matrice(m1);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_multiplication_matrice_nombre[1] = "Remplir Matrice 1 (remplie)";
            }
        }
        else if (ns_choix == 2)
        {
            if (m1.nombre_elements == m1.nombre_colonnes * m1.nombre_lignes)
            {
                valide = 1;
            }

            if (valide == 1)
            {
                m2 = op_transpose_matrice(m1);
                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m2); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * m2.nombre_lignes) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m2.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * m1.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 12 - (HAUTEUR / 2);
                affichage_matrice(m2, 1, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }
        }
    }
}

void multiplication_deux_matrices()
{
    int ns_choix;

    char *choix_somme_deux_matrices[] = {" Multiplication de deux matrices ", "Remplir Matrice 1 (vide)", "Remplir Matrice 2 (vide)", "Calcul", "retour"};

    liste_choix s_choix = {5, 5, choix_somme_deux_matrices};

    Matrice m1, m2, m3;

    int valide = 0;

    while (ns_choix != 4)
    {
        ns_choix = afficher_menu(s_choix);

        if ((m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements) && (m2.nombre_colonnes * m2.nombre_lignes == m2.nombre_elements))
        {
            if (m1.nombre_colonnes == m2.nombre_lignes)
            {
                valide = 1;
            }
        }

        if (ns_choix == 1)
        {
            m1 = creation_matrice();
            m1 = remplissage_matrice(m1);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_somme_deux_matrices[1] = "Remplir Matrice 1 (remplie)";
            }
        }

        if (ns_choix == 2)
        {
            m2 = creation_matrice();
            m2 = remplissage_matrice(m2);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_somme_deux_matrices[2] = "Remplir Matrice 1 (remplie)";
            }
        }

        if (ns_choix == 3)
        {
            if (valide == 1)
            {
                m3 = op_multiplication_deux_matrices(m1, m2);
                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m3); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * m3.nombre_lignes) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m3.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * m3.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 12 - (HAUTEUR / 2);
                affichage_matrice(m3, 1, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }
        }
    }
}

void multiplication_matrice_nombre()
{
    int ns_choix = 0;

    char *choix_multiplication_matrice_nombre[] = {" Multiplication Matrice par un nombre ", "Remplir Matrice (vide)", "Donner le nombre", "Calcul", "retour"};

    liste_choix s_choix = {5, 5, choix_multiplication_matrice_nombre};

    Matrice m1, m2;

    int n;

    int valide = 0;

    while (ns_choix != 4)
    {
        ns_choix = afficher_menu(s_choix);

        if (ns_choix == 1)
        {
            m1 = creation_matrice();
            m1 = remplissage_matrice(m1);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_multiplication_matrice_nombre[1] = "Remplir Matrice 1 (remplie)";
            }
        }

        if (ns_choix == 2)
        {
            char c;
            int k = 0;
            char str_n[10];
            str_n[0] = ' ';
            str_n[1] = '\0';
            char *une_liste[] = {"Saisie du nombre"};
            liste_choix s_choix = {1, 1, une_liste};
            afficher_cadre(s_choix);
            mvprintw(7, 50 - strlen("donner votre valeur :") / 2, "Donner votre valeur : ");

            while (c != 10 || k == 0)
            {
                c = wgetch(stdscr);
                if (c > 48 && c < 58 && k < 10)
                {
                    str_n[k] = c;
                    str_n[k + 1] = '\0';
                    k++;
                    wattron(stdscr, A_REVERSE);
                    mvprintw(7, 51 + strlen("donner votre valeur :") / 2, "%s", str_n);
                    wattroff(stdscr, A_REVERSE);
                }
            }

            werase(stdscr);
            refresh();

            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                valide = 1;
                n = atoi(str_n);
            }
        }

        if (ns_choix == 3)
        {
            if (valide == 1)
            {
                m2 = op_multiplication_matrice_nombre(m1, n);
                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m2); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * m2.nombre_lignes) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m2.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * m1.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 12 - (HAUTEUR / 2);
                affichage_matrice(m2, 1, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }

            //que si m1 et m2 sont valides
            //calcul
            //affichage de la matrice resultat
        }
    }
}

void difference_deux_matrices()
{
    int ns_choix;

    char *choix_somme_deux_matrices[] = {" Difference de deux matrices ", "Remplir Matrice 1 (vide)", "Remplir Matrice 2 (vide)", "Calcul", "retour"};

    liste_choix s_choix = {5, 5, choix_somme_deux_matrices};

    Matrice m1, m2, m3;

    int valide = 0;

    while (ns_choix != 4)
    {
        ns_choix = afficher_menu(s_choix);

        if ((m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements) && (m2.nombre_colonnes * m2.nombre_lignes == m2.nombre_elements))
        {
            valide = 1;
        }

        if (ns_choix == 1)
        {
            m1 = creation_matrice();
            m1 = remplissage_matrice(m1);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_somme_deux_matrices[1] = "Remplir Matrice 1 (remplie)";
            }
        }

        if (ns_choix == 2)
        {
            m2 = creation_matrice();
            m2 = remplissage_matrice(m2);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_somme_deux_matrices[2] = "Remplir Matrice 1 (remplie)";
            }
        }

        if (ns_choix == 3)
        {
            if (valide == 1)
            {
                m3 = op_difference_deux_matrices(m1, m2);
                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m3); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * m3.nombre_lignes) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m3.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * m3.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 12 - (HAUTEUR / 2);
                affichage_matrice(m3, 1, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }

            //que si m1 et m2 sont valides
            //calcul
            //affichage de la matrice resultat
        }
    }
}

void somme_deux_matrices()
{
    int ns_choix;

    char *choix_somme_deux_matrices[] = {" Somme de deux matrices ", "Remplir Matrice 1 (vide)", "Remplir Matrice 2 (vide)", "Calcul", "retour"};

    liste_choix s_choix = {5, 5, choix_somme_deux_matrices};

    Matrice m1, m2, m3;

    int valide = 0;

    while (ns_choix != 4)
    {
        ns_choix = afficher_menu(s_choix);

        if ((m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements) && (m2.nombre_colonnes * m2.nombre_lignes == m2.nombre_elements))
        {
            valide = 1;
        }

        if (ns_choix == 1)
        {
            m1 = creation_matrice();
            m1 = remplissage_matrice(m1);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_somme_deux_matrices[1] = "Remplir Matrice 1 (remplie)";
            }
        }

        if (ns_choix == 2)
        {
            m2 = creation_matrice();
            m2 = remplissage_matrice(m2);
            if (m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements)
            {
                choix_somme_deux_matrices[2] = "Remplir Matrice 1 (remplie)";
            }
        }

        if (ns_choix == 3)
        {
            if (valide == 1)
            {
                m3 = op_somme_deux_matrices(m1, m2);
                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m3); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * m3.nombre_lignes) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m3.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * m3.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 12 - (HAUTEUR / 2);
                affichage_matrice(m3, 1, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }

            //que si m1 et m2 sont valides
            //calcul
            //affichage de la matrice resultat
        }
    }
}

void affichage_matrice(Matrice m, int type, int posx, int posy)
{
    WINDOW *fenetre_matrice;
    if (type == 1) //matrice entier
    {
        int *tmax;
        tmax = max_colonnes(m); //calcul des dimesions de depart de la matrice

        int HAUTEUR = (2 * m.nombre_lignes) + 1;
        int LARGEUR = 0;

        for (int i = 0; i < m.nombre_colonnes; i++)
        {
            LARGEUR += tmax[i];
        }
        LARGEUR += (2 * m.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET

        fenetre_matrice = newwin(HAUTEUR, LARGEUR, posy, posx);
        wborder(fenetre_matrice, 0, 0, 32, 32, 0, 0, 0, 0);
        posy = 1;
        for (int i = 0; i < m.nombre_lignes; i++)
        {
            posx = 2;

            for (int j = 0; j < m.nombre_colonnes; j++)
            {
                mvwprintw(fenetre_matrice, posy, posx, "%d", m.mat[i][j]);

                posx = posx + tmax[j] + 2;
            }
            posy += 2;
        }
        wrefresh(fenetre_matrice);
    }
    else //matrice float
    {
    }
}

void popup_erreur(int x)
{
    WINDOW *fenetre_erreur;
    int posx, posy;
    char *liste_erreurs[] = {"Impossible"};
    posx = 51 - (strlen(liste_erreurs[x]) / 2);
    posy = 7;
    fenetre_erreur = newwin(5, 4 + strlen(liste_erreurs[x]), posy, posx);
    wborder(fenetre_erreur, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwprintw(fenetre_erreur, 2, 2, liste_erreurs[x]);
    wrefresh(fenetre_erreur);
    wgetch(fenetre_erreur);
}

int nombre_chifres(int x)
{
    int nombre;
    if (x == 0)
    {
        return 1;
    }
    else
    {
        nombre = 0;
        while (x != 0)
        {
            x /= 10;
            ++nombre;
        }
        return nombre;
    }
}

int *max_colonnes(Matrice m)
{
    int *t;
    int i, j;

    t = (int *)malloc(m.nombre_colonnes * sizeof(int));
    for (i = 0; i < m.nombre_colonnes; i++)
    {
        t[i] = 0;
    }

    for (i = 0; i < m.nombre_colonnes; i++)
    {
        for (j = 0; j < m.nombre_lignes; j++)
        {
            if (t[i] < nombre_chifres(m.mat[j][i]))
            {
                if (m.mat[i][j] < 0)
                {
                    t[i] = 1 + nombre_chifres(m.mat[j][i]);
                }
                else
                {
                    t[i] = nombre_chifres(m.mat[j][i]);
                }
            }
        }
    }
    return t;
}

Matrice remplissage_matrice(Matrice m)
{
    char *une_liste[] = {"Remplissage Matrice"};
    liste_choix s_choix = {1, 1, une_liste};
    afficher_cadre(s_choix);

    int i;
    int j;
    int *tmax;
    tmax = max_colonnes(m); //calcul des dimesions de depart de la matrice

    int HAUTEUR = (2 * m.nombre_lignes) + 1;
    int LARGEUR = 0;
    for (i = 0; i < m.nombre_colonnes; i++)
    {
        LARGEUR += tmax[i];
    }
    LARGEUR += (2 * m.nombre_colonnes) + 2; //HAUTEUR LARGEUR SONT SET
    int x = 50 - (LARGEUR / 2);
    int y = 12 - (HAUTEUR / 2);
    WINDOW *fenetre_matrice;

    fenetre_matrice = newwin(HAUTEUR, LARGEUR, y, x);

    int posx;
    int posy;
    int compteur;

    char n;
    int temp_n = 0;
    int cpt_temp = 0;
    int signe = 1;
    int altern = 1;

    while (m.nombre_elements < (m.nombre_colonnes * m.nombre_lignes))
    {
        wborder(fenetre_matrice, 0, 0, 32, 32, 0, 0, 0, 0);

        posx = 2;
        posy = 1;

        j = 0;
        i = 0;
        compteur = 0;
        do
        {
            j = 0;
            posx = 2;

            while (j < m.nombre_colonnes && compteur < m.nombre_elements)
            {
                mvwprintw(fenetre_matrice, posy, posx, "%d", m.mat[i][j]);
                compteur++;

                posx = posx + tmax[j] + 2;
                j++;
            }
            posy += 2;
            i++;
        } while (i < m.nombre_lignes && compteur < m.nombre_elements);

        i--;
        posy -= 2;
        if (j == m.nombre_colonnes)
        {
            j = 0;
            i++;
            posy += 2;
            posx = 2;
        }

        if (temp_n == 0)
        {
            if (signe == -1)
            {
                wattron(fenetre_matrice, A_REVERSE);
                mvwprintw(fenetre_matrice, posy, posx, "-");
                wattroff(fenetre_matrice, A_REVERSE);
            }
            else
            {
                wattron(fenetre_matrice, A_REVERSE);
                mvwprintw(fenetre_matrice, posy, posx, " ");
                wattroff(fenetre_matrice, A_REVERSE);
            }
        }
        else
        {
            wattron(fenetre_matrice, A_REVERSE);
            mvwprintw(fenetre_matrice, posy, posx, "%d", temp_n * signe);
            wattroff(fenetre_matrice, A_REVERSE);
        }

        n = wgetch(fenetre_matrice);

        if (n > 47 && n < 58)
        {
            temp_n = (temp_n * 10) + (n - '0');
            cpt_temp++;
        }
        else if (n == 45)
        {
            signe = -1;
        }
        else if (n == 10)
        {
            m.mat[i][j] = signe * temp_n;
            signe = 1;
            temp_n = 0;
            cpt_temp = 0;
            m.nombre_elements++;
        }
        else if (n == 8 && (m.nombre_elements != 0 || cpt_temp != 0))
        {
            if (cpt_temp != 0)
            {
                cpt_temp--;
                temp_n /= 10;
            }
            else
            {
                m.nombre_elements--;
                if (j != 0)
                {
                    j--;
                }
                else if (i != 0)
                {
                    i--;
                    j = m.nombre_colonnes - 1;
                }
                cpt_temp = nombre_chifres(m.mat[i][j]);
                signe = 1;
                temp_n = m.mat[i][j];
            }
        }

        if (tmax[j] < cpt_temp || tmax[j] < cpt_temp - signe)
        {
            LARGEUR++;
            if (cpt_temp > tmax[j])
            {

                tmax[j] = cpt_temp;
            }
            else
            {
                tmax[j] = cpt_temp + 1;
            }
            wresize(fenetre_matrice, HAUTEUR, LARGEUR);
            if (altern == -1)
            {
                x--;
                altern = 1;
            }
            else
            {
                altern = -1;
            }
            mvwin(fenetre_matrice, y, x);
            wrefresh(fenetre_matrice);
        }

        werase(fenetre_matrice);
    }

    werase(fenetre_matrice);

    wrefresh(fenetre_matrice);
    return m;
}

Matrice creation_matrice()
{

    char *une_liste[] = {"Creation matrice"};
    liste_choix s_choix = {1, 1, une_liste};
    afficher_cadre(s_choix);

    mvprintw(6, 50 - (strlen("- Donner les dimentions de la matrice -") / 2), "- Donner les dimentions de la matrice -");
    mvprintw(9, 50 - (strlen("- Donner les dimentions de la matrice -") / 2), "Nombre de lignes : ");
    mvprintw(11, 50 - (strlen("- Donner les dimentions de la matrice -") / 2), "Nombre de colonnes : ");
    refresh();

    int k = 0;
    char c = '\0';
    char str_n[10];
    str_n[0] = ' ';
    str_n[1] = '\0';
    wattron(stdscr, A_REVERSE);
    mvprintw(9, 50, "%s", str_n);
    wattroff(stdscr, A_REVERSE);

    while (c != 10 || k == 0)
    {
        c = wgetch(stdscr);
        if (c > 48 && c < 58 && k < 2)
        {
            str_n[k] = c;
            str_n[k + 1] = '\0';
            k++;
            wattron(stdscr, A_REVERSE);
            mvprintw(9, 50, "%s", str_n);
            wattroff(stdscr, A_REVERSE);
        }
    }

    int n_lignes = atoi(str_n);

    k = 0;
    c = '\0';
    str_n[10];
    str_n[0] = ' ';
    str_n[1] = '\0';
    wattron(stdscr, A_REVERSE);
    mvprintw(11, 52, "%s", str_n);
    wattroff(stdscr, A_REVERSE);
    while (c != 10 || k == 0)
    {
        c = wgetch(stdscr);
        if (c > 48 && c < 58 && k < 2)
        {
            str_n[k] = c;
            str_n[k + 1] = '\0';
            k++;
            wattron(stdscr, A_REVERSE);
            mvprintw(11, 52, "%s", str_n);
            wattroff(stdscr, A_REVERSE);
        }
    }

    int n_colonnes = atoi(str_n);

    werase(stdscr);

    Matrice m;
    m.nombre_elements = 0;
    m.nombre_colonnes = n_colonnes;
    m.nombre_lignes = n_lignes;

    m.mat = (int **)malloc(n_lignes * sizeof(int *));

    for (int i = 0; i < n_lignes; i++)
    {
        m.mat[i] = (int *)malloc(n_colonnes * sizeof(int));
    }
    // to delete
    int count = 1;
    for (int i = 0; i < m.nombre_lignes; i++)
    {
        for (int j = 0; j < m.nombre_colonnes; j++)
        {
            m.mat[i][j] = count;
            count++;
        }
    }

    return m;
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

    y = 4;
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
        y += 2;
    }
    wrefresh(fenetre_menu);
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  FONCTIONS    AFFICHAGE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//