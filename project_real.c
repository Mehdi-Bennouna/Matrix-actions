#include <stdio.h>
#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

struct Element_liste
{
    char *info;
    struct Element_liste *svt;
};

struct Element_vect_mots
{
    char lettre;
    struct Element_liste *tete;
};

typedef struct Vecteurs
{
    int nombre_elements;
    int *vect;
} Vecteur;

typedef struct Matrices
{
    int nombre_lignes;
    int nombre_colonnes;
    int nombre_elements;
    int **mat;
} Matrice;

typedef struct Matrices_char
{
    int nombre_lignes;
    int nombre_colonnes;
    char **mat;
} Matrice_char;

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
void calcul_vecteur_maxligne();
void calcul_vecteur_maxcolonne();
void affichage_vecteur(Vecteur t, int posx, int posy);
int *max_colonnes_vect(Vecteur tab);
char *saisie_texte();
void affichage_matrice_mot(Matrice_char m);
void affichage_struct_vect(struct Element_vect_mots *tab);
void suprime_liste(struct Element_vect_mots *tab);

//void affichage_op_deux_matrices(Matrice m1, Matrice m2, Matrice m3, char operation);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  FONCTIONS    AFFICHAGE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

//--------------------------------   FONCTIONS    CALCUL ---------------------------------------------------------------------//
Matrice op_somme_deux_matrice(Matrice m1, Matrice M2);
Matrice op_difference_deux_matrice(Matrice m1, Matrice M2);
Matrice op_multiplication_deux_matrices(Matrice m1, Matrice m2);
Matrice op_transpose_matrice(Matrice m1);
Matrice op_tri_matrice(Matrice m1);
Vecteur op_calcul_vecteur_maxligne(Matrice m);
Vecteur op_calcul_vecteur_maxcolonne(Matrice m);
Matrice_char creation_matrice_mots(char *texte);
void ajouter_liste(struct Element_liste **tete, char *info);
struct Element_vect_mots *creation_struct_vect(Matrice_char m);
void ajout_mot(struct Element_vect_mots *tab);
void op_suprimer_liste(struct Element_liste **tete, char *info);

//--------------------------------   FONCTIONS    CALCUL ---------------------------------------------------------------------//

int main()
{
    //*************taille terminal*********************//
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTitle("Projet Algo");
    SMALL_RECT windowSize = {0, 0, 101, 28};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    //--------------------------------------------//

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    start_color(); /* Start color 			*/

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
                else if (n_liste_choix == 3)
                {
                    calcul_vecteur_maxligne();
                }
                else if (n_liste_choix == 4)
                {
                    calcul_vecteur_maxcolonne();
                }
            }
            choix.liste = liste_choix_0;
            choix.nombre_choix = 5;
            choix.nombre_choix_valide = 5;
        }

        if (n_liste_choix == 3)
        {
            char texte[500];
            Matrice_char mat;
            struct Element_vect_mots *tab;
            choix.nombre_choix_valide = 1;
            while (n_liste_choix != 8)
            {
                choix.liste = liste_choix_3;
                choix.nombre_choix = 9;

                n_liste_choix = afficher_menu(choix);

                if (n_liste_choix == 1)
                {
                    saisie_texte(texte);
                    choix.nombre_choix_valide = 2;
                }
                else if (n_liste_choix == 2 && choix.nombre_choix_valide >= 2)
                {
                    mat = creation_matrice_mots(texte);
                    choix.nombre_choix_valide += 2;
                }
                else if (n_liste_choix == 3 && choix.nombre_choix_valide >= 3)
                {
                    affichage_matrice_mot(mat);
                }
                else if (n_liste_choix == 4 && choix.nombre_choix_valide >= 4)
                {
                    tab = creation_struct_vect(mat);
                    choix.nombre_choix_valide += 3;
                }
                else if (n_liste_choix == 5 && choix.nombre_choix_valide >= 5)
                {
                    affichage_struct_vect(tab);
                }
                else if (n_liste_choix == 6 && choix.nombre_choix_valide >= 6)
                {
                    ajout_mot(tab);
                }
                else if (n_liste_choix == 7 && choix.nombre_choix_valide >= 7)
                {
                    suprime_liste(tab);
                }
            }
            choix.liste = liste_choix_0;
            choix.nombre_choix = 5;
            choix.nombre_choix_valide = 5;
        }
    }
    endwin();
    return 0;
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

    m2.nombre_lignes = m1.nombre_colonnes;
    m2.nombre_colonnes = m1.nombre_lignes;
    m2.nombre_elements = m1.nombre_elements;

    m2.mat = (int **)malloc(m2.nombre_lignes * sizeof(int *));

    for (int i = 0; i < m2.nombre_lignes; i++)
    {
        m2.mat[i] = (int *)malloc(m2.nombre_colonnes * sizeof(int));
    }

    for (int i = 0; i < m1.nombre_lignes; i++)
    {
        for (int j = 0; j < m1.nombre_colonnes; j++)
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

Vecteur op_calcul_vecteur_maxligne(Matrice m)
{
    Vecteur tab;
    int max;

    tab.nombre_elements = m.nombre_lignes;
    tab.vect = (int *)malloc(m.nombre_lignes * sizeof(int));

    for (int i = 0; i < m.nombre_lignes; i++)
    {
        max = m.mat[i][0];
        for (int j = 0; j < m.nombre_colonnes; j++)
        {
            if (max < m.mat[i][j])
            {
                max = m.mat[i][j];
            }
        }
        tab.vect[i] = max;
    }

    return tab;
}

Vecteur op_calcul_vecteur_maxcolonne(Matrice m)
{
    Vecteur tab;
    int max;

    tab.nombre_elements = m.nombre_colonnes;
    tab.vect = (int *)malloc(m.nombre_colonnes * sizeof(int));

    for (int i = 0; i < m.nombre_colonnes; i++)
    {
        max = m.mat[0][i];
        for (int j = 0; j < m.nombre_lignes; j++)
        {
            if (max < m.mat[j][i])
            {
                max = m.mat[j][i];
            }
        }
        tab.vect[i] = max;
    }

    return tab;
}

Matrice_char creation_matrice_mots(char *text)
{
    Matrice_char mat_mots;

    mat_mots.nombre_lignes = 0;
    mat_mots.nombre_colonnes = 0;

    int cpt = 0;
    int i = 0;
    int j = 0;
    int ps = 1;

    while (text[cpt] != 0)
    {
        if (text[cpt] == 32)
        {
            if (ps == 0)
            {
                ps = 1;
                mat_mots.nombre_lignes++;
                i = 0;
            }
        }
        else
        {
            i++;
            if (i > mat_mots.nombre_colonnes)
            {
                mat_mots.nombre_colonnes = i;
            }
            ps = 0;
        }
        cpt++;
    }
    if (text[cpt - 1] != 32)
    {
        mat_mots.nombre_lignes++;
    }

    mat_mots.mat = (char **)malloc(mat_mots.nombre_lignes * sizeof(char *));

    for (i = 0; i < mat_mots.nombre_lignes; i++)
    {
        mat_mots.mat[i] = (char *)malloc(mat_mots.nombre_colonnes * sizeof(char));
    }

    cpt = 0;
    i = 0;
    j = 0;
    ps = 1;

    while (text[cpt] != 0)
    {
        if (text[cpt] == 32)
        {
            if (ps == 0)
            {
                ps = 1;
                j++;
                i = 0;
            }
        }
        else
        {
            mat_mots.mat[j][i] = text[cpt];
            mat_mots.mat[j][i + 1] = '\0';
            i++;
            ps = 0;
        }
        cpt++;
    }
    return mat_mots;
}

void ajouter_liste(struct Element_liste **tete, char *info)
{
    struct Element_liste *p;
    struct Element_liste *q;
    p = (struct Element_liste *)malloc(sizeof(struct Element_liste));

    p->info = info;
    p->svt = NULL;

    if (*tete == NULL)
    {
        (*tete) = p;
        return;
    }

    q = *tete;
    while (q->svt != NULL)
    {
        q = q->svt;
    }
    q->svt = p;

    return;
}

struct Element_vect_mots *creation_struct_vect(Matrice_char m)
{
    struct Element_vect_mots *tab;

    tab = (struct Element_vect_mots *)malloc(26 * sizeof(struct Element_vect_mots));
    char *mot;
    int j;
    for (int i = 0; i < 26; i++)
    {
        tab[i].lettre = 65 + i;
        tab[i].tete = NULL;
    }
    for (int i = 0; i < m.nombre_lignes; i++)
    {
        mot = (char *)malloc(20 * sizeof(char));

        j = 0;
        while (m.mat[i][j] != '\0')
        {
            mot[j] = m.mat[i][j];
            j++;
        }
        mot[j] = '\0';

        if (mot[0] > 64 && mot[0] < 91)
        {
            ajouter_liste(&(tab[(mot[0] - 65)].tete), mot);
        }
        else
        {
            ajouter_liste(&(tab[(mot[0] - 97)].tete), mot);
        }
    }
    return tab;
}

void op_suprimer_liste(struct Element_liste **tete, char *info)
{
    struct Element_liste *p = *tete, *q;

    if (p != NULL && strncmp(p->info, info, 20) == 0)
    {
        *tete = p->svt;
        free(p);
        return;
    }

    while (p != NULL && strncmp(p->info, info, 20) != 0)
    {
        q = p;
        p = p->svt;
    }

    if (p == NULL)
    {
        return;
    }

    q->svt = p->svt;
    free(p);
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  FONCTIONS    CALCUL ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

//--------------------------------   FONCTIONS    AFFICHAGE ---------------------------------------------------------------------
void suprime_liste(struct Element_vect_mots *tab)
{
    char *une_liste[] = {"Ajout de mot"};
    liste_choix s_choix = {1, 1, une_liste};
    afficher_cadre(s_choix);

    char c = '\0';
    int cpt = 0;

    WINDOW *fenetre_texte;
    fenetre_texte = newwin(23, 99, 2, 2);
    curs_set(1);

    int posy = 7;
    int posx = 43;

    mvwprintw(fenetre_texte, 7, 17, "donner le mot a supprimer:");

    char *texte;
    texte = (char *)malloc(sizeof(char) * 20);

    while (c != 10 && cpt < 20)
    {
        c = wgetch(fenetre_texte);
        if ((c > 64 && c < 91) || (c > 96 && c < 123))
        {
            texte[cpt] = c;
            texte[cpt + 1] = '\0';
            cpt++;
            mvwprintw(fenetre_texte, posy, posx, "%c", c);
            posx++;
            wrefresh(fenetre_texte);
        }
        else if (c == 8 && cpt != 0)
        {
            cpt--;
            texte[cpt] = '\0';
            posx--;

            mvwdelch(fenetre_texte, posy, posx);
            wrefresh(fenetre_texte);
        }
    }
    curs_set(0);

    if (texte[0] > 64 && texte[0] < 91)
    {
        op_suprimer_liste(&tab[texte[0] - 65].tete, texte);
    }
    else if (texte[0] > 96 && texte[0] < 123)
    {
        op_suprimer_liste(&tab[texte[0] - 97].tete, texte);
    }
}

void ajout_mot(struct Element_vect_mots *tab)
{

    char *une_liste[] = {"Ajout de mot"};
    liste_choix s_choix = {1, 1, une_liste};
    afficher_cadre(s_choix);

    char c = '\0';
    int cpt = 0;

    WINDOW *fenetre_texte;
    fenetre_texte = newwin(23, 99, 2, 2);
    curs_set(1);

    int posy = 7;
    int posx = 34;

    mvwprintw(fenetre_texte, 7, 17, "donner votre mot:");

    char *texte;
    texte = (char *)malloc(sizeof(char) * 20);

    while (c != 10 && cpt < 20)
    {
        c = wgetch(fenetre_texte);
        if ((c > 64 && c < 91) || (c > 96 && c < 123))
        {
            texte[cpt] = c;
            texte[cpt + 1] = '\0';
            cpt++;
            mvwprintw(fenetre_texte, posy, posx, "%c", c);
            posx++;
            wrefresh(fenetre_texte);
        }
        else if (c == 8 && cpt != 0)
        {
            cpt--;
            texte[cpt] = '\0';
            posx--;

            mvwdelch(fenetre_texte, posy, posx);
            wrefresh(fenetre_texte);
        }
    }
    curs_set(0);

    if (texte[0] > 64 && texte[0] < 91)
    {
        ajouter_liste(&tab[texte[0] - 65].tete, texte);
    }
    else if (texte[0] > 96 && texte[0] < 123)
    {
        ajouter_liste(&tab[texte[0] - 97].tete, texte);
    }
}

void affichage_struct_vect(struct Element_vect_mots *tab)
{
    char *une_liste[] = {"Affichage de la structure"};
    liste_choix s_choix = {1, 1, une_liste};
    afficher_cadre(s_choix);

    char motsis[300];
    int posx = 1;
    int posy = 1;
    WINDOW *fenetre_tableau;
    fenetre_tableau = newwin(27, 98, 1, 2);
    int y = 1;

    struct Element_liste *p;
    for (char i = 0; i < 13; i++)
    {
        mvwprintw(fenetre_tableau, y, 1, "%c : ", i + 65);
        wrefresh(fenetre_tableau);

        if (tab[i].tete == NULL)
        {
            wprintw(fenetre_tableau, "vide");
            wrefresh(fenetre_tableau);
        }
        else
        {
            p = tab[i].tete;
            while (p != NULL)
            {
                wprintw(fenetre_tableau, " -> %s", p->info);
                wrefresh(fenetre_tableau);
                p = p->svt;
            }
        }

        y += 2;
    }
    wgetch(fenetre_tableau);
    werase(fenetre_tableau);
    y = 1;
    for (char i = 13; i < 26; i++)
    {
        mvwprintw(fenetre_tableau, y, 1, "%c : ", i + 65);

        if (tab[i].tete == NULL)
        {
            wprintw(fenetre_tableau, "vide");
        }
        else
        {
            p = tab[i].tete;
            while (p != NULL)
            {
                wprintw(fenetre_tableau, " -> %s", p->info);
                p = p->svt;
            }
        }

        y += 2;
    }

    wrefresh(fenetre_tableau);
    wgetch(fenetre_tableau);
}

void affichage_matrice_mot(Matrice_char m)
{

    char *une_liste[] = {"affichage Matrice de mots"};
    liste_choix s_choix = {1, 1, une_liste};
    afficher_cadre(s_choix);

    WINDOW *fenetre_matrice;

    if (m.nombre_lignes < 10)
    {
        int HAUTEUR = (2 * m.nombre_lignes) + 1;
        int LARGEUR = (m.nombre_colonnes) + 4; //HAUTEUR LARGEUR SONT SET

        int posx = 50 - (LARGEUR / 2);
        int posy = 12 - (HAUTEUR / 2);

        fenetre_matrice = newwin(HAUTEUR, LARGEUR, posy, posx);
        wborder(fenetre_matrice, 0, 0, 32, 32, 0, 0, 0, 0);

        posy = -1;
        posx = 0;

        for (int i = 0; i < m.nombre_lignes; i++)
        {
            posy += 2;
            posx = 2;
            for (int j = 0; j < m.nombre_colonnes && m.mat[i][j] != '\0'; j++)
            {
                mvwprintw(fenetre_matrice, posy, posx, "%c", m.mat[i][j]);
                posx++;
            }
        }
    }
    else
    {
        int HAUTEUR = (m.nombre_lignes) + 2;
        int LARGEUR = (m.nombre_colonnes) + 4; //HAUTEUR LARGEUR SONT SET

        int posx = 50 - (LARGEUR / 2);
        int posy = 12 - (HAUTEUR / 2);

        fenetre_matrice = newwin(HAUTEUR, LARGEUR, posy, posx);
        wborder(fenetre_matrice, 0, 0, 32, 32, 0, 0, 0, 0);

        posy = 0;
        posx = 0;

        for (int i = 0; i < m.nombre_lignes; i++)
        {
            posy += 1;
            posx = 2;
            for (int j = 0; j < m.nombre_colonnes && m.mat[i][j] != '\0'; j++)
            {
                mvwprintw(fenetre_matrice, posy, posx, "%c", m.mat[i][j]);
                posx++;
            }
        }
    }

    wrefresh(fenetre_matrice);
    wgetch(fenetre_matrice);
}

char *saisie_texte(char *texte)
{
    char c = ' ';
    int cpt = 0;
    int posy = 2;
    int posx = 2;

    char *une_liste[] = {"Saisie du texte"};
    liste_choix s_choix = {1, 1, une_liste};
    afficher_cadre(s_choix);

    WINDOW *fenetre_texte;
    fenetre_texte = newwin(23, 99, posy, posx);
    curs_set(1);

    posx = 1;
    posy = 0;

    while (c != 10 && cpt < 500)
    {
        c = wgetch(fenetre_texte);
        if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == 32)
        {
            texte[cpt] = c;
            texte[cpt + 1] = '\0';
            cpt++;
            mvwprintw(fenetre_texte, posy, posx, "%c", c);
            posx++;
            wrefresh(fenetre_texte);
            if (posx == 99)
            {
                posx = 1;
                posy++;
            }
        }
        else if (c == 8 && cpt != 0)
        {
            cpt--;
            texte[cpt] = '\0';
            if (posx == 0)
            {
                posx = 99;
                posy--;
            }
            else
            {
                posx--;
            }
            mvwdelch(fenetre_texte, posy, posx);
            wrefresh(fenetre_texte);
        }
    }
    curs_set(0);
    return texte;
}

void calcul_vecteur_maxligne()
{
    int ns_choix = 0;

    char *choix_multiplication_matrice_nombre[] = {" Vecteur MaxLigne ", "Remplir Matrice (vide)", "Calcul", "retour"};

    liste_choix s_choix = {4, 4, choix_multiplication_matrice_nombre};

    Matrice m1;
    Vecteur t;

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
                t = op_calcul_vecteur_maxligne(m1);

                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m1); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * 0) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m1.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * t.nombre_elements) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 11 - (HAUTEUR / 2);
                affichage_vecteur(t, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }
        }
    }
}

void calcul_vecteur_maxcolonne()
{
    int ns_choix = 0;

    char *choix_multiplication_matrice_nombre[] = {" Vecteur MaxLigne ", "Remplir Matrice (vide)", "Calcul", "retour"};

    liste_choix s_choix = {4, 4, choix_multiplication_matrice_nombre};

    Matrice m1;
    Vecteur t;

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
                t = op_calcul_vecteur_maxcolonne(m1);

                char *une_liste[] = {"Resultat"};
                liste_choix s_choix = {1, 1, une_liste};
                afficher_cadre(s_choix);

                int *tmax;
                tmax = max_colonnes(m1); //calcul des dimesions de depart de la matrice
                int HAUTEUR = (2 * 0) + 1;
                int LARGEUR = 0;
                for (int i = 0; i < m1.nombre_colonnes; i++)
                {
                    LARGEUR += tmax[i];
                }
                LARGEUR += (2 * t.nombre_elements) + 2; //HAUTEUR LARGEUR SONT SET
                int x = 50 - (LARGEUR / 2);
                int y = 11 - (HAUTEUR / 2);
                affichage_vecteur(t, x, y);
                wgetch(stdscr);
            }
            else
            {
                popup_erreur(0);
            }
        }
    }
}

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

        if ((m1.nombre_colonnes * m1.nombre_lignes == m1.nombre_elements) && (m2.nombre_colonnes * m2.nombre_lignes == m2.nombre_elements) && (m1.nombre_colonnes == m2.nombre_colonnes) && (m1.nombre_lignes == m2.nombre_lignes))
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

void affichage_vecteur(Vecteur t, int posx, int posy)
{
    WINDOW *fenetre_vecteur;

    int *tmax;

    tmax = max_colonnes_vect(t);
    int HAUTEUR = 3;
    int LARGEUR = 0;

    for (int i = 0; i < t.nombre_elements; i++)
    {
        LARGEUR += tmax[i];
    }
    LARGEUR += (2 * t.nombre_elements) + 2;
    fenetre_vecteur = newwin(HAUTEUR, LARGEUR, posy, posx);
    wborder(fenetre_vecteur, 0, 0, 32, 32, 0, 0, 0, 0);

    posy = 1;
    posx = 2;

    for (int i = 0; i < t.nombre_elements; i++)
    {
        mvwprintw(fenetre_vecteur, posy, posx, "%d", t.vect[i]);

        posx = posx + tmax[i] + 2;
    }
    wrefresh(fenetre_vecteur);
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

int *max_colonnes_vect(Vecteur tab)
{
    int *t;
    int i;

    t = (int *)malloc(tab.nombre_elements * sizeof(int));
    for (i = 0; i < tab.nombre_elements; i++)
    {
        t[i] = 0;
    }

    for (i = 0; i < tab.nombre_elements; i++)
    {
        if (t[i] < nombre_chifres(tab.vect[i]))
        {
            t[i] = nombre_chifres(tab.vect[i]);
        }
    }
    return t;
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
                if (m.mat[j][i] < 0)
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

    for (int i = 0; i < n_lignes; i++)
    {
        for (int j = 0; j < n_colonnes; j++)
        {
            m.mat[i][j] = 0;
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
    int debuty = 7;

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

    init_pair(1, COLOR_RED, COLOR_BLACK);
    y = 4;
    for (i = 1; i < choix.nombre_choix; ++i)
    {
        if (i > choix.nombre_choix_valide && i != choix.nombre_choix - 1)
        {

            wattron(fenetre_menu, COLOR_PAIR(1));
        }
        if (selection == i + 1) /* Highlight the present choice */
        {
            wattron(fenetre_menu, A_REVERSE);
            mvwprintw(fenetre_menu, y, (25 - strlen(choix.liste[i]) / 2), "%s", choix.liste[i]);
            wattroff(fenetre_menu, A_REVERSE);
        }
        else
        {
            mvwprintw(fenetre_menu, y, (25 - strlen(choix.liste[i]) / 2), "%s", choix.liste[i]);
        }
        y += 2;
        wattroff(fenetre_menu, COLOR_PAIR(1));
    }
    wrefresh(fenetre_menu);
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  FONCTIONS    AFFICHAGE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//