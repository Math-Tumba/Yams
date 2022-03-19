/**
 * \page Général
 * \brief Programme permettant de jouer au Yam's.
 * \author TUMBARELLO Mathéo G2
 * \version 1.0
 * \date 27/11/2021
 *
 * Ce programme permet à deux joueurs de faire une partie de Yam's en 13 tours.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/**
 * \brief constante pour le nombre de points à avoir avant d'avoir les points bonus
 * 
*/ 
const int BONUS = 62;

/**
 * \brief constante pour le nombre de points que donne le bonus
 * 
*/ 
const int PTS_BONUS = 35;

/**
 * \brief constante pour le nombre de points que donne le full house
 * 
*/ 
const int PTS_FULLHOUSE = 25;

/**
 * \brief constante pour le nombre de points que donne la petite suite
 * 
 * 
*/ 
const int PTS_PETITE_SUITE = 30;

/**
 * \brief constante pour le nombre de points que donne la grande suite
 * 
 * 
*/ 
const int PTS_GRANDE_SUITE = 40;

/**
 * \brief constante pour le nombre de points que donne le yams
 * 
 * 
*/ 
const int PTS_YAMS = 50;

/**
 * \brief constante pour le nombre de points que donne le total de dés 1
 * 
 * 
*/ 
const int PTS_UN = 1;

/**
 * \brief constante pour le nombre de points que donne le total de dés 2
 * 
*/ 
const int PTS_DEUX = 2;

/**
 * \brief constante pour le nombre de points que donne le total de dés 3
 * 
*/ 
const int PTS_TROIS = 3;

/**
 * \brief constante pour le nombre de points que donne le total de dés 4
 * 
*/ 
const int PTS_QUATRE = 4;

/**
 * \brief constante pour le nombre de points que donne le total de dés 5
 * 
*/ 
const int PTS_CINQ = 5;

/**
 * \brief constante pour le nombre de points que donne le total de dés 6
 * 
*/ 
const int PTS_SIX = 6;

/**
 * \brief constante pour le nombre de lancers maximal d'un joueur par tour
 * 
*/ 
const int FIN_LANCERS = 3; 

/**
 * \brief constante pour le nombre de tours avant la fin de la partie
 * 
*/ 
const int FIN_JEU = 13;

/**
 * \brief constante pour la borne maximale servant à donner des valeurs aléatoires pour les dés
 * 
*/ 
const int BORNE_ALEA = 7;

/**
 * \brief constante pour la vérification d'un cas d'arrêt dans une des fonctions
 * 
*/ 
const int ARRET_FONCTION = 0;

/**
 * \brief constante pour initialiser une valeur à -1 servant à vérifier les combinaisons
 * 
 * 
*/ 
const int DEFAULT = -1;

/**
 * \brief Taille de la première dimension de certains tableaux
 * 
 * Cette taille permet de modifier la feuille de marque ainsi que les scores des joueurs respectifs
*/ 
#define NB_JOUEURS 2

/**
 * \def NB_LIGNES
 * \brief Nombre de lignes dans une feuille de marque
 * 
*/ 
#define NB_LIGNES 22

/**
 * \def NB_COLONNES
 * \brief nombre de caractères par ligne dans une feuille de marque
 * 
*/ 
#define NB_COLONNES 31

/**
 * \def NB_COMBINAISONS
 * \brief Nombre de combinaisons de points de chaque joueur
 * 
*/ 
#define NB_COMBINAISONS 13

/**
 * \def NB_DES
 * \brief Nombre de dés lancés au premier lancer, nombre de dés gardés à la fin des lancers
 * 
 * 
*/ 
#define NB_DES 5

void creerFeuilleMarque(char tab_joueurs[][9], char feuille_marque_joueur[][NB_LIGNES][NB_COLONNES], int nb_joueurs, int nb_lignes, int nb_colonnes);
void initialiserTab1d(int tab[], int taille);
void afficherFeuilleMarque(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int nb_lignes, int nb_colonnes);
void lancerDes(int tab_des_lances[], int longueur_tab);
int aleaInfBorne(int borne);
void choixDes(int tab_des_lances[], int *longueur_tab1, int tab_des_gardes[], int *longueur_tab2);
void valeursDesDernierLancer(int tab_des_lances[], int *longueur_tab1, int tab_des_gardes[], int *longueur_tab2);
void triTableau(int tab[], int longueur_tab); 
void echange(int *val1, int *val2);
void choixCombinaisons(int tab_des_gardes[], char tab_combinaisons[][20], char feuille_marque_joueur[NB_JOUEURS][NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int *score_inf, int *nb_combinaisons, int joueur);
void condamnerCombinaison(int tab_des_gardes[], char tab_combinaisons[][20], char feuille_marque_joueur[NB_JOUEURS][NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int *score_inf, int *nb_combinaisons, int joueur);

int convertirStrToInt_recupScore(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4]);
void convertirIntToStr_ajoutScore(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4], int *score_part, int *score);
void convertirIntToStr(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4]);
void modifTabCombinaisons(int indice, int *nb_combinaisons, char tab_combinaisons[][20]);

void bonus(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, char score_dans_tab[4]);
void total1(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[]);
void total2(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[]);
void total3(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[]);
void total4(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[]);
void total5(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[]);
void total6(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[]);
void brelan(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[]);
void carre(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[]);
void fullhouse(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[]);
void petitesuite(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[]);
void grandesuite(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[]);
void yams(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[]);
void chance(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[]);

void afficherVainqueur(int tab_score[NB_JOUEURS], char tab_joueurs[NB_JOUEURS][9]);

/**
 * \fn int main()
 * \brief Programme principal
 * \return Code de sortie du programme (0 : sortie normale)
 * 
 * Le programme principal traite progressivement plusieurs fonctions :
 * il demande les noms des joueurs, crée les deux feuilles de marque du joueur, propose de lancer les dés, 
 * de choisir quels dés garder, une fois que 5 dés sont gardés, il propose de choisir une combinaison puis
 * ajoute les points dans la feuille de marque de condamner une combinaison. A la fin des 13 tours, il affiche le vainqueur.
 * 
*/
int main() 
{
    char nomJ[9];
    int i, y, z;

    char t_nomJ[NB_JOUEURS][9] = {"        ", "        "};
    char t_feuille_marque[NB_JOUEURS][NB_LIGNES][NB_COLONNES];

    int t_des_lances[NB_DES];
    int t_des_gardes[NB_DES];
    int longueur_t_des_lances;
    int longueur_t_des_gardes;
    int nbLancers;

    int choix_combi;
    int t_scoreJ[NB_JOUEURS] = {0, 0};
    int t_scoreJ_sup[NB_JOUEURS] = {0, 0};
    int t_scoreJ_inf[NB_JOUEURS] = {0, 0};
    char *base_t_combinaisons[NB_COMBINAISONS+1] = {"01 : Total de 1", "02 : Total de 2", "03 : Total de 3", "04 : Total de 4", "05 : Total de 5", "06 : Total de 6", "07 : Brelan", "08 : Carré", "09 : Full house", "10 : Petite suite", "11 : Grande suite", "12 : Yams", "13 : Chance"," "};
    char t_combinaisons[NB_JOUEURS][NB_COMBINAISONS+1][20];
    for (i = 0; i < NB_JOUEURS; i++)
    {
        for (y = 0; y < NB_COMBINAISONS+1; y++)
        {
            strcpy(t_combinaisons[i][y], base_t_combinaisons[y]);
        }
    }
    int t_nb_combinaisons[NB_JOUEURS] = {NB_COMBINAISONS, NB_COMBINAISONS};
    

    printf("\nDébut de la partie !\n\n");
    for (i = 0; i < 2; i++)
    {
        printf("Entrez le nom du joueur %d : ", i+1);
        scanf("%s", nomJ);
        while (strlen(nomJ)>8) 
        {
            printf("Entrez le nom du joueur %d (8 caract max): ", i+1);
            scanf("%s", nomJ);
        }
        for (y = 0; y < strlen(nomJ); y++)
        {
            t_nomJ[i][y] = nomJ[y];
        }
    }
    creerFeuilleMarque(t_nomJ, t_feuille_marque, NB_JOUEURS, NB_LIGNES, NB_COLONNES);
    
    for (i = 1; i <= FIN_JEU; i++)
    {
        printf("\n--- TOUR %d ---\n\n", i);
        for (y = 0; y < NB_JOUEURS; y++)
        {
            initialiserTab1d(t_des_lances, 5);
            initialiserTab1d(t_des_gardes, 5);
            longueur_t_des_lances = 5;
            longueur_t_des_gardes = 0;
            nbLancers = 1;
            z = 0;
            while (t_nomJ[y][z] != ' ' && t_nomJ[y][z] != '\0')
            {
                printf("%c",t_nomJ[y][z]);
                z++;
            }
            printf(", à votre tour !\n\n");
            afficherFeuilleMarque(t_feuille_marque[y], NB_LIGNES, NB_COLONNES);
            while (nbLancers <= FIN_LANCERS && longueur_t_des_lances != 0)
            {
                printf("Lancez les dés !\n");
                
                lancerDes(t_des_lances, longueur_t_des_lances);
                if (nbLancers < FIN_LANCERS)
                {
                    choixDes(t_des_lances, &longueur_t_des_lances, t_des_gardes, &longueur_t_des_gardes);
                }
                else
                {
                    valeursDesDernierLancer(t_des_lances, &longueur_t_des_lances, t_des_gardes, &longueur_t_des_gardes);
                }
                nbLancers++;
            }
            triTableau(t_des_gardes, longueur_t_des_gardes);
            printf("Valeurs de vos dés : ");
            for (z = 0; z < NB_DES; z++)
            {
                printf("%d ", t_des_gardes[z]);
            }
            printf("\n\n");
            printf("Voulez-vous choisir une combinaison (1) ou condamner une combinaison (0) ? ");
            scanf("%d", &choix_combi);
            while (choix_combi != 0 && choix_combi != 1)
            {
                printf("Voulez-vous choisir une combinaison (1) ou condamner une combinaison (0) ? ");
                scanf("%d", &choix_combi);
            }
            if (choix_combi == 1)
            {
                choixCombinaisons(t_des_gardes, t_combinaisons[y], t_feuille_marque, &t_scoreJ[y], &t_scoreJ_sup[y], &t_scoreJ_inf[y], &t_nb_combinaisons[y], y);
            }
            else
            {
                condamnerCombinaison(t_des_gardes, t_combinaisons[y], t_feuille_marque, &t_scoreJ[y], &t_scoreJ_sup[y], &t_scoreJ_inf[y], &t_nb_combinaisons[y], y);
            }
        }
    }
    afficherVainqueur(t_scoreJ, t_nomJ);
    return EXIT_SUCCESS;
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void echange(int *val1, int *val2)
 * \brief echange deux valeurs entières d'un tableau
 * \param val1 : paramètre d'entrée/sortie qui représente la 1ère valeur à échanger
 * \param val2 : paramètre d'entrée/sortie qui représente la 2nde valeur à échanger
 * \see triTableau()
 * \see choixDes()
 * 
*/
void echange(int *val1, int *val2)
{
    int temp;
    temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void creerFeuilleMarque(char tab_joueurs[][9], char feuille_marque_joueur[][NB_LIGNES][NB_COLONNES], int nb_joueurs, int nb_lignes, int nb_colonnes)
 * \brief Crée la feuille de marque de chaque joueur
 * \param tab_joueurs : paramètre d'entrée/sortie correspondant au tableau des noms des joueurs
 * \param feuille_marque_joueur : paramètre d'entrée/sortie correspondant au tableau 3d des feuilles de marque des joueurs
 * \param nb_joueurs : paramètre d'entrée correspondant au nombre de joueurs
 * \param nb_lignes : paramètre d'entrée correspondant au nombre de lignes d'une feuille de marque
 * \param nb_colonnes : paramètre d'entrée correspondant au nombre de caractères d'une ligne d'une feuille de marque
 * 
 * 
*/
void creerFeuilleMarque(char tab_joueurs[][9], char feuille_marque_joueur[][NB_LIGNES][NB_COLONNES], int nb_joueurs, int nb_lignes, int nb_colonnes)
{
    int i, y;
    char base_feuille_marque[NB_LIGNES][NB_COLONNES] =
    {
        "------------------------------",
        "|                  |joueur   |",
        "|1 [total de 1]    |    0    |",
        "|2 [total de 2]    |    0    |",
        "|3 [total de 3]    |    0    |",
        "|4 [total de 4]    |    0    |",
        "|5 [total de 5]    |    0    |",
        "|6 [total de 6]    |    0    |",
        "|bonus si > 62 [35]|    0    |",
        "|total sup         |    0    |",
        "|                  |         |",
        "|brelan [total]    |    0    |",
        "|carre [total]     |    0    |",
        "|full house [25]   |    0    |",
        "|petite suite [30] |    0    |",
        "|grande suite [40] |    0    |",
        "|yams [50]         |    0    |",
        "|chance [total]    |    0    |",
        "|total inferieur   |    0    |",
        "|                  |         |",
        "|total             |    0    |",
        "------------------------------"
    };

    for (i = 0; i < nb_joueurs; i++)
    {
        for (y = 0; y < nb_lignes; y++)
        {
            strcpy(feuille_marque_joueur[i][y], base_feuille_marque[y]);
        }
    }
    for (i = 0; i < nb_joueurs; i++)
    {
        for (y = 20; y < nb_colonnes-3; y++)
        {
            feuille_marque_joueur[i][1][y] = tab_joueurs[i][y-20];
        }  
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void initialiserTab1d(int tab[], int taille)
 * \brief initialise un tableau 1d
 * \param tab : paramètre d'entrée/sortie correspondant au tableau initialisé
 * \param taille : paramètre d'entrée correspondant à la taille que doit avoir le tableau initialisé
 * 
*/
void initialiserTab1d(int tab[], int taille)
{
    int i;
    for (i = 0; i < taille; i++)
    {
        tab[i] = 0;
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void afficherFeuilleMarque(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int nb_lignes, int nb_colonnes)
 * \brief Affiche la feuille de marque d'un joueur
 * \param feuille_marque_joueur : paramètre d'entrée/sortie correspondant au tableau 2d de la feuille de marque d'un joueur
 * \param nb_lignes : paramètre d'entrée correspondant au nombre de lignes d'une feuille de marque
 * \param nb_colonnes : paramètre d'entrée correspondant au nombre de caractères d'une ligne d'une feuille de marque
 * 
 * 
*/
void afficherFeuilleMarque(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int nb_lignes, int nb_colonnes)
{
    int i;
    for (i = 0; i < nb_lignes; i++)
    {
        printf("%s\n", feuille_marque_joueur[i]);
    }
    printf("\n\n");
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn int aleaInfBorne(int borne) {
 * \brief choisit une valeur entre 1 et 6
 * \param borne : paramètre d'entrée correspondant à la borne maximale d'une valeur pseudo-aléatoire
 * \return une valeur comprise entre 1 et 6 inclus
 * \see lancerDes()
 * 
*/
int aleaInfBorne(int borne) {
    return rand() % (borne-1) + 1;
}

/**
 * \fn void lancerDes(int tab_des_lances[], int longueur_tab)
 * \brief lance un nombre de dés de valeurs pseudo-aléatoires
 * \param tab_des_lances : paramètre d'entrée/sortie correspondant au tableau 1d des dés lancés
 * \param longueur_tab : paramètre d'entrée correspondant à la taille que doit avoir le tableau paramétré
 * 
 * 
*/
void lancerDes(int tab_des_lances[], int longueur_tab)
{
    int i;
    int val_de;
    srand(time(NULL));
    for (i=0; i < longueur_tab; i++)
    {
        val_de = aleaInfBorne(BORNE_ALEA);
        tab_des_lances[i] = val_de;
    }
    triTableau(tab_des_lances, longueur_tab);
}


/* --------------------------------------------------------------------------------*/

/**
 * \fn void choixDes(int tab_des_lances[], int *longueur_tab1, int tab_des_gardes[], int *longueur_tab2)
 * \brief sauvegarde les valeurs des dés voulus par le joueur
 * \param tab_des_lances : paramètre d'entrée/sortie correspondant au tableau 1d des dés lancés
 * \param longueur_tab1 : paramètre d'entrée correspondant à la taille du tableau des dés lancés
 * \param tab_des_gardes : paramètre d'entrée/sortie correspondant au tableau 1d des dés gardés par le joueur
 * \param longueur_tab2 : paramètre d'entrée correspondant à la taille du tableau des dés gardés par le joueur
 * 
 * 
*/
void choixDes(int tab_des_lances[], int *longueur_tab1, int tab_des_gardes[], int *longueur_tab2)
{
    int i;
    int choix = DEFAULT;
    while (choix != ARRET_FONCTION)
    {
        if (*longueur_tab1 != 0)
        {
            printf("Voici les dés lancés : ");
            for (i = 0; i < *longueur_tab1; i++)
            {
                printf("%d ", tab_des_lances[i]);
            }
            printf("\n");
        }


        if (*longueur_tab2 != 5 && *longueur_tab2 != 0)
        {
            printf("Voici vos dés gardés : ");
            for (i = 0; i < *longueur_tab2; i++)
            {
                printf("%d ", tab_des_gardes[i]);
            }
            printf("\n");
        }
        else if (*longueur_tab2 == 5)
        {
            choix = ARRET_FONCTION;
            break;
        }
        printf("Quel dé voulez vous garder ? Donnez son emplacement ('0' pour aucun) : ");
        scanf("%d", &choix);
        while (choix < ARRET_FONCTION || choix > *longueur_tab1)
        {
            printf("Erreur, réitérez : ");
            scanf("%d", &choix);
        }
        if (choix > ARRET_FONCTION)
        {
            tab_des_gardes[*longueur_tab2] = tab_des_lances[choix-1];
            *longueur_tab1 = *longueur_tab1 - 1;
            *longueur_tab2 = *longueur_tab2 + 1;
            echange(&tab_des_lances[*longueur_tab1], &tab_des_lances[choix-1]);
        }
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void valeursDesDernierLancer(int tab_des_lances[], int *longueur_tab1, int tab_des_gardes[], int *longueur_tab2)
 * \brief force le tableau des dés gardés à se remplir avec les dés lancés du 3ème lancer
 * \param tab_des_lances : paramètre d'entrée/sortie correspondant au tableau 1d des dés lancés
 * \param longueur_tab1 : paramètre d'entrée correspondant à la taille du tableau des dés lancés
 * \param tab_des_gardes : paramètre d'entrée/sortie correspondant au tableau 1d des dés gardés par le joueur
 * \param longueur_tab2 : paramètre d'entrée correspondant à la taille du tableau des dés gardés par le joueur
 * 
 * 
*/
void valeursDesDernierLancer(int tab_des_lances[], int *longueur_tab1, int tab_des_gardes[], int *longueur_tab2)
{
    int i;
    for (i = 0; i < *longueur_tab1; i++)
    {
        tab_des_gardes[*longueur_tab2] = tab_des_lances[i];
        *longueur_tab2 = *longueur_tab2 + 1;
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void triTableau(int tab[], int longueur_tab)
 * \brief Trie un tableau
 * \param tab : paramètre d'entrée/sortie correspondant au tableau à trier
 * \param longueur_tab : paramètre d'entrée correspondant à la longueur du tableau paramétré
 * 
*/
void triTableau(int tab[], int longueur_tab)
{
    int i, y;
    for (i = 0; i < longueur_tab; i++)
    {
        for (y = longueur_tab-1; y > 0; y--)
        {
            if (tab[y]<tab[y-1])
            {
                echange(&tab[y], &tab[y-1]);
            }
        }
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void choixCombinaisons(int tab_des_gardes[], char tab_combinaisons[][20], char feuille_marque_joueur[NB_JOUEURS][NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int *score_inf, int *nb_combinaisons, int joueur)
 * \brief permet au joueur de choisir la combinaison à garder qui ajoutera des points dans sa feuille de score
 * \param tab_des_gardes : paramètre d'entrée/sortie correspondant au tableau des dés gardés par le joueur
 * \param tab_combinaisons : paramètre d'entrée/sortie correspondant au tableau de combinaisons du joueur encore disponible
 * \param feuille_marque_joueur : paramètre d'entrée/sortie correspondant au tableau 3d des joueurs
 * \param score : paramètre d'entrée/sortie correspondant au score total d'un joueur
 * \param score_sup : paramètre d'entrée/sortie correspondant au score de la partie supérieure d'un joueur
 * \param score_inf : paramètre d'entrée/sortie correspondant au score de la partie inférieure d'un joueur
 * \param nb_combinaisons : paramètre d'entrée/sortie correspondant au nombre de combinaisons d'un joueur encore disponibles
 * \param joueur : paramètre d'entrée correspondant au données traitées d'un joueur (nécessaire dans les fonctions)
 * 
 * 
*/
void choixCombinaisons(int tab_des_gardes[], char tab_combinaisons[][20], char feuille_marque_joueur[NB_JOUEURS][NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int *score_inf, int *nb_combinaisons, int joueur)
{
    int i;
    char choix[2];
    int verif_choix = 0;
    int verif_combinaison;
    int indice;
    printf("Voici les combinaisons encore disponibles : \n");
    for (i = 0; i < *nb_combinaisons; i++)
    {
        printf("%s\n", tab_combinaisons[i]);
    }
    while (verif_choix == 0)
    {   
        printf("\nLaquelle voulez-vous choisir ? ('-1' pour condamner une combinaison) ");
        scanf("%s", choix);
        for (i = 0; i < *nb_combinaisons; i++)
        {
            if ((choix[0] == tab_combinaisons[i][0] && choix[1] == tab_combinaisons[i][1]) || (choix[0] == '-' && choix[1] == '1'))
            {
                verif_choix = 1;
                indice=i;
                break;
            }
            else
            {   
                continue;
            }
        }

    }
    if (!strcmp(choix, "01")) 
    {
        verif_combinaison = 0;
        for (i = 0; i < NB_DES; i++)
        {
            if (tab_des_gardes[i] == PTS_UN)
            {
                verif_combinaison = 1;
                modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                break;
            }
        }
        if (verif_combinaison)
        {
            total1(feuille_marque_joueur[joueur], score, score_sup, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "02"))
    {
        verif_combinaison = 0;
        for (i = 0; i < NB_DES; i++)
        {
            if (tab_des_gardes[i] == PTS_DEUX)
            {
                verif_combinaison = 1;
                modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                break;
            }
        }
        if (verif_combinaison)
        {
            total2(feuille_marque_joueur[joueur], score, score_sup, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "03"))
    {
        verif_combinaison = 0;
        for (i = 0; i < NB_DES; i++)
        {
            if (tab_des_gardes[i] == PTS_TROIS)
            {
                verif_combinaison = 1;
                modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                break;
            }
        }
        if (verif_combinaison)
        {
            total3(feuille_marque_joueur[joueur], score, score_sup, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "04"))
    {
        verif_combinaison = 0;
        for (i = 0; i < NB_DES; i++)
        {
            if (tab_des_gardes[i] == PTS_QUATRE)
            {
                verif_combinaison = 1;
                modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                break;
            }
        }
        if (verif_combinaison)
        {
            total4(feuille_marque_joueur[joueur], score, score_sup, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        } 
    }
    else if (!strcmp(choix, "05"))
    {
        verif_combinaison = 0;
        for (i = 0; i < NB_DES; i++)
        {
            if (tab_des_gardes[i] == PTS_CINQ)
            {
                verif_combinaison = 1;
                modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                break;
            }
        }
        if (verif_combinaison)
        {
            total5(feuille_marque_joueur[joueur], score, score_sup, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "06"))
    {
        verif_combinaison = 0;
        for (i = 0; i < NB_DES; i++)
        {
            if (tab_des_gardes[i] == PTS_SIX)
            {
                verif_combinaison = 1;
                modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                break;
            }
        }
        if (verif_combinaison)
        {
            total6(feuille_marque_joueur[joueur], score, score_sup, tab_des_gardes);
        }
        else{
            printf("\nCette combinaison ne peut être prise en compte.\n\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        } 
    }
    else if (!strcmp(choix, "07"))
    {
        verif_combinaison = 1;
        for (i = 0; i < NB_DES-1; i++)
        {
            if (tab_des_gardes[i] == tab_des_gardes[i+1])
            {
                verif_combinaison++;
                if ((verif_combinaison == 3 && tab_des_gardes[i+1] != tab_des_gardes[i+2]) || (verif_combinaison == 3 && tab_des_gardes[i+1] == tab_des_gardes[NB_DES]))
                {
                    verif_combinaison = 6;
                    modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                    break;                    
                }
            }
            else{
                verif_combinaison = 1;
            }
        }
        if (verif_combinaison == 6)
        {
            brelan(feuille_marque_joueur[joueur], score, score_inf, tab_des_gardes);
        }
        else{
            printf("\nCette combinaison ne peut être prise en compte.\n\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        } 
    }
    else if (!strcmp(choix, "08"))
    {
        verif_combinaison = 1;
        for (i = 0; i < NB_DES-1; i++)
        {
            if (tab_des_gardes[i] == tab_des_gardes[i+1])
            {
                verif_combinaison++;
                if ((verif_combinaison == 4 && tab_des_gardes[i+1] != tab_des_gardes[i+2]) || (verif_combinaison == 4 && tab_des_gardes[i+1] == tab_des_gardes[NB_DES]))
                {
                    verif_combinaison = 6;
                    modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                    break;                    
                }
            }
            else{
                verif_combinaison = 1;
            }
        }
        if (verif_combinaison == 6)
        {
            carre(feuille_marque_joueur[joueur], score, score_inf, tab_des_gardes);
        }
        else{
            printf("\nCette combinaison ne peut être prise en compte.\n\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        } 
    }
    else if (!strcmp(choix, "09"))
    {
        verif_combinaison = 0;
        if ((tab_des_gardes[0] == tab_des_gardes[1] && tab_des_gardes[2] == tab_des_gardes[4]) || (tab_des_gardes[0] == tab_des_gardes[2] && tab_des_gardes[3] == tab_des_gardes[4]))
        {
            verif_combinaison = 1;
            modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        }

        if (verif_combinaison)
        {
            fullhouse(feuille_marque_joueur[joueur], score, score_inf, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "10"))
    {
        verif_combinaison = 1;
        for (i = 0; i < 4 ; i++)
        {
            if (tab_des_gardes[i+1] == (tab_des_gardes[i]+1))
            {
                verif_combinaison++;
                if (verif_combinaison == 4)
                {
                    modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                    break;                    
                }
                else if (tab_des_gardes[i] == tab_des_gardes[i+1])
                {
                    continue;
                }
            }
            else
            {
                verif_combinaison = 1;
            }
        }
        if (verif_combinaison==4)
        {
            petitesuite(feuille_marque_joueur[joueur], score, score_inf, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "11"))
    {
        verif_combinaison = 1;
        for (i = 0; i < 4 ; i++)
        {
            if (tab_des_gardes[i+1] == (tab_des_gardes[i]+1))
            {
                verif_combinaison++;
                if (verif_combinaison == 5)
                {
                    modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
                    break;                    
                }
            }
            else
            {
                break;
            }
        }
        if (verif_combinaison == 5)
        {
            grandesuite(feuille_marque_joueur[joueur], score, score_inf, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "12"))
    {
        verif_combinaison = 0;
        if (tab_des_gardes[0] == tab_des_gardes[NB_DES-1])
        {
            verif_combinaison = 1;
            modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        }
        if (verif_combinaison)
        {
            yams(feuille_marque_joueur[joueur], score, score_inf, tab_des_gardes);
        }
        else{
            printf("Cette combinaison ne peut être prise en compte.\n");
            sleep(2);
            choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
        }
    }
    else if (!strcmp(choix, "13"))
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        chance(feuille_marque_joueur[joueur], score, score_inf, tab_des_gardes);
    }
    else
    {
        condamnerCombinaison(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void condamnerCombinaison(int tab_des_gardes[], char tab_combinaisons[][20], char feuille_marque_joueur[NB_JOUEURS][NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int *score_inf, int *nb_combinaisons, int joueur)
 * \brief permet au joueur de choisir la combinaison à garder qui ajoutera des points dans sa feuille de score
 * \param tab_des_gardes : paramètre d'entrée/sortie correspondant au tableau des dés gardés par le joueur
 * \param tab_combinaisons : paramètre d'entrée/sortie correspondant au tableau de combinaisons du joueur encore disponible
 * \param feuille_marque_joueur : paramètre d'entrée/sortie correspondant au tableau 3d des joueurs
 * \param score : paramètre d'entrée/sortie correspondant au score total d'un joueur
 * \param score_sup : paramètre d'entrée/sortie correspondant au score de la partie supérieure d'un joueur
 * \param score_inf : paramètre d'entrée/sortie correspondant au score de la partie inférieure d'un joueur
 * \param nb_combinaisons : paramètre d'entrée/sortie correspondant au nombre de combinaisons d'un joueur encore disponibles
 * \param joueur : paramètre d'entrée correspondant au données traitées d'un joueur (nécessaire dans les fonctions)
 * 
 * 
*/
void condamnerCombinaison(int tab_des_gardes[], char tab_combinaisons[][20], char feuille_marque_joueur[NB_JOUEURS][NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int *score_inf, int *nb_combinaisons, int joueur)
{
    int i;
    char choix[2];
    int verif_choix = 0;
    int indice;
    printf("Voici les combinaisons encore disponibles : \n");
    for (i = 0; i < *nb_combinaisons; i++)
    {
        printf("%s\n", tab_combinaisons[i]);
    }
    while (verif_choix == 0)
    {   
        printf("\nLaquelle voulez-vous choisir ? ('-1' pour choisir une combinaison au lieu d'en condamner une) ");
        scanf("%s", choix);
        for (i = 0; i < *nb_combinaisons; i++)
        {
            if ((choix[0] == tab_combinaisons[i][0] && choix[1] == tab_combinaisons[i][1]) || (choix[0] == '-' && choix[1] == '1'))
            {
                verif_choix = 1;
                indice = i;
                break;
            }
            else
            {   
                continue;
            }
        }

    }
    if (!strcmp(choix, "01")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][2][24] = 'X';
    }
    else if (!strcmp(choix, "02")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][3][24] = 'X';
    }
    else if (!strcmp(choix, "03")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][4][24] = 'X';
    }
    else if (!strcmp(choix, "04")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][5][24] = 'X';
    }
    else if (!strcmp(choix, "05")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][6][24] = 'X';
    }
    else if (!strcmp(choix, "06")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][7][24] = 'X';
    }
    else if (!strcmp(choix, "07")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][11][24] = 'X';
    }
    else if (!strcmp(choix, "08")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][12][24] = 'X';
    }
    else if (!strcmp(choix, "09")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][13][24] = 'X';
    }
    else if (!strcmp(choix, "10")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][14][24] = 'X';
    }
    else if (!strcmp(choix, "11")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][15][24] = 'X';
    }
    else if (!strcmp(choix, "12")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][16][24] = 'X';
    }
    else if (!strcmp(choix, "13")) 
    {
        modifTabCombinaisons(indice, nb_combinaisons, tab_combinaisons);
        feuille_marque_joueur[joueur][17][24] = 'X';
    }
    else 
    {
        choixCombinaisons(tab_des_gardes, tab_combinaisons, feuille_marque_joueur, score, score_sup, score_inf, nb_combinaisons, joueur);
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn int convertirStrToInt_recupScore(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4])
 * \brief convertit une chaîne de caractères en entier
 * \param feuille_marque_joueur : paramètre d'entrée/sortie correspondant au tableau 1d des caractères d'une ligne
 * \param nb_points : paramètre d'entrée correspondant au nombre de points que rapporte une combinaison choisie
 * \param score_dans_tab : paramètre d'entrée/sortie correspondant aux caractères où se trouve le score d'une case du tableau.
 * \see bonus()
 * \see total1()
 * \see total2()
 * \see total3()
 * \see total4()
 * \see total5()
 * \see total6()
 * \see brelan()
 * \see carre()
 * \see petitesuite()
 * \see grandesuite()
 * \see yams()
 * \see chance()
 * 
*/
int convertirStrToInt_recupScore(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4])
{
    int i;
    int val;
    for (i = 0; i < 3; i++)
    {
        if (feuille_marque_joueur[24+i] != ' ')
        {
            score_dans_tab[i] = feuille_marque_joueur[24+i];
        }
    }
    val = atoi(score_dans_tab);
    val = val + nb_points;
    return val;
}

/**
 * \fn void convertirIntToStr_ajoutScore(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4], int *score_part, int *score)
 * \brief convertir un entier en chaîne de caractères puis ajoute le score de cet entier à celui déjà existant dans la case de score correspondante
 * \param feuille_marque_joueur : paramètre d'entrée/sortie correspondant au tableau 1d des caractères d'une ligne
 * \param nb_points : paramètre d'entrée correspondant au nombre de points que rapporte une combinaison choisie
 * \param score_dans_tab : paramètre d'entrée/sortie correspondant aux caractères où se trouve le score d'une case du tableau.
 * \param score_part : paramètre d'entrée/sortie correspondant à la valeur de la partie de score total (sup ou inf) d'un joueur 
 * \param score : paramètre d'entrée/sortie correspondant au score total d'un joueur
 * \see bonus()
 * \see total1()
 * \see total2()
 * \see total3()
 * \see total4()
 * \see total5()
 * \see total6()
 * \see brelan()
 * \see carre()
 * \see petitesuite()
 * \see grandesuite()
 * \see yams()
 * \see chance()
 * 
*/
void convertirIntToStr_ajoutScore(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4], int *score_part, int *score)
{
    int i;
    *score_part = *score_part + nb_points;
    *score = *score + nb_points; 
    sprintf(score_dans_tab, "%d", nb_points);
    for (i = 0; i < strlen(score_dans_tab); i++)
    {
        feuille_marque_joueur[24+i] = score_dans_tab[i];
        score_dans_tab[i] = ' ';
    }
}

/**
 * \fn void convertirIntToStr(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4])
 * \brief transforme un entier en chaîne de caractères puis ajoute le score de cet entier dans la case de score correspondante
 * \param feuille_marque_joueur : paramètre d'entrée/sortie correspondant au tableau 1d des caractères d'une ligne
 * \param nb_points : paramètre d'entrée correspondant au nombre de points que rapporte une combinaison choisie
 * \param score_dans_tab : paramètre d'entrée/sortie correspondant aux caractères où se trouve le score d'une case du tableau.
 * \see bonus()
 * \see total1()
 * \see total2()
 * \see total3()
 * \see total4()
 * \see total5()
 * \see total6()
 * \see brelan()
 * \see carre()
 * \see petitesuite()
 * \see grandesuite()
 * \see yams()
 * \see chance()
 * 
*/
void convertirIntToStr(char feuille_marque_joueur[NB_LIGNES], int nb_points, char score_dans_tab[4])
{
    int i;
    sprintf(score_dans_tab, "%d", nb_points);
    for (i = 0; i < strlen(score_dans_tab); i++)
    {
        feuille_marque_joueur[24+i] = score_dans_tab[i];
        score_dans_tab[i] = ' ';
    }   
}

/**
 * \fn void modifTabCombinaisons(int indice, int *nb_combinaisons, char tab_combinaisons[][20])
 * \brief supprime la combinaison qui vient d'être donnée par le joueur et validée par le programme en retriant les combinaisons
 * \param indice : paramètre d'entrée correspondant à l'indice du tableau de combinaisons du joueur 
 * \param nb_combinaisons : paramètre d'entrée/sortie correspondant au nombre de combinaisons du joueur encore disponibles
 * \param tab_combinaisons : paramètre d'entrée/sortie correspondant au tableau de combinaisons du joueur
 * 
 * 
*/
void modifTabCombinaisons(int indice, int *nb_combinaisons, char tab_combinaisons[][20])
{
    int i;
    for (i = indice; i < *nb_combinaisons-1; i++)
    {
        strcpy(tab_combinaisons[i], tab_combinaisons[i+1]);
    }
    *nb_combinaisons = *nb_combinaisons - 1;
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void bonus(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, char score_dans_tab[4])
 * \brief ajoute dans la feuille de marque le score correspondant au bonus.
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_sup : paramètre d'entrée/sortie représentant le score de la partie supérieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void bonus(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, char score_dans_tab[4])
{
    int score_entier_dans_tab;
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[8], PTS_BONUS, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[8], score_entier_dans_tab, score_dans_tab, score_sup, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[9], PTS_BONUS, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[9], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], PTS_BONUS, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab); 
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void total1(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison TOTAL 1
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_sup : paramètre d'entrée/sortie représentant le score de la partie supérieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void total1(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        if (tab_des_gardes[i] == PTS_UN)
        {
            somme++;
        }
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[2], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[2], score_entier_dans_tab, score_dans_tab, score_sup, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[9], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[9], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);

    if (*score_sup >= BONUS && feuille_marque_joueur[8][24] == '0')
    {
        bonus(feuille_marque_joueur, score, score_sup, score_dans_tab);
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void total2(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison TOTAL 2
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_sup : paramètre d'entrée/sortie représentant le score de la partie supérieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void total2(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        if (tab_des_gardes[i] == PTS_DEUX)
        {
            somme = somme + PTS_DEUX;
        }
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[3], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[3], score_entier_dans_tab, score_dans_tab, score_sup, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[9], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[9], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);

    if (*score_sup >= BONUS && feuille_marque_joueur[8][24] == '0')
    {
        bonus(feuille_marque_joueur, score, score_sup, score_dans_tab);
    }
}


/* --------------------------------------------------------------------------------*/

/**
 * \fn void total3(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison TOTAL 3
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_sup : paramètre d'entrée/sortie représentant le score de la partie supérieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void total3(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        if (tab_des_gardes[i] == PTS_TROIS)
        {
            somme = somme + PTS_TROIS;
        }
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[4], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[4], score_entier_dans_tab, score_dans_tab, score_sup, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[9], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[9], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
    
    if (*score_sup >= BONUS && feuille_marque_joueur[8][24] == '0')
    {
        bonus(feuille_marque_joueur, score, score_sup, score_dans_tab);
    }
}


/* --------------------------------------------------------------------------------*/

/**
 * \fn void total4(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison TOTAL 4
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_sup : paramètre d'entrée/sortie représentant le score de la partie supérieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void total4(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        if (tab_des_gardes[i] == PTS_QUATRE)
        {
            somme = somme + PTS_QUATRE;
        }
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[5], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[5], score_entier_dans_tab, score_dans_tab, score_sup, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[9], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[9], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
    
    if (*score_sup >= BONUS && feuille_marque_joueur[8][24] == '0')
    {
        bonus(feuille_marque_joueur, score, score_sup, score_dans_tab);
    }
}


/* --------------------------------------------------------------------------------*/

/**
 * \fn void total5(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison TOTAL 5
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_sup : paramètre d'entrée/sortie représentant le score de la partie supérieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void total5(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        if (tab_des_gardes[i] == PTS_CINQ)
        {
            somme = somme + PTS_CINQ;
        }
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[6], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[6], score_entier_dans_tab, score_dans_tab, score_sup, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[9], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[9], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
    
    if (*score_sup >= BONUS && feuille_marque_joueur[8][24] == '0')
    {
        bonus(feuille_marque_joueur, score, score_sup, score_dans_tab);
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void total6(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison TOTAL 6
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_sup : paramètre d'entrée/sortie représentant le score de la partie supérieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void total6(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_sup, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        if (tab_des_gardes[i] == PTS_SIX)
        {
            somme = somme + PTS_SIX;
        }
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[7], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[7], score_entier_dans_tab, score_dans_tab, score_sup, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[9], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[9], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
    
    if (*score_sup >= BONUS && feuille_marque_joueur[8][24] == '0')
    {
        bonus(feuille_marque_joueur, score, score_sup, score_dans_tab);
    }
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void brelan(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison BRELAN
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_inf : paramètre d'entrée/sortie représentant le score de la partie inférieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void brelan(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        somme = somme + tab_des_gardes[i];
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[11], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[11], score_entier_dans_tab, score_dans_tab, score_inf, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[18], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[18], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void carre(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison CARRE
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_inf : paramètre d'entrée/sortie représentant le score de la partie inférieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void carre(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        somme = somme + tab_des_gardes[i];
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[12], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[12], score_entier_dans_tab, score_dans_tab, score_inf, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[18], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[18], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void fullhouse(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison FULL HOUSE
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_inf : paramètre d'entrée/sortie représentant le score de la partie inférieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void fullhouse(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
{
    int somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = PTS_FULLHOUSE;
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[13], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[13], score_entier_dans_tab, score_dans_tab, score_inf, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[18], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[18], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void petitesuite(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison PETITE SUITE
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_inf : paramètre d'entrée/sortie représentant le score de la partie inférieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void petitesuite(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
{
    int somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = PTS_PETITE_SUITE;
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[14], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[14], score_entier_dans_tab, score_dans_tab, score_inf, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[18], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[18], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void grandesuite(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison GRANDE SUITE
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_inf : paramètre d'entrée/sortie représentant le score de la partie inférieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void grandesuite(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
{
    int somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = PTS_GRANDE_SUITE;
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[15], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[15], score_entier_dans_tab, score_dans_tab, score_inf, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[18], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[18], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void yams(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison YAMS
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_inf : paramètre d'entrée/sortie représentant le score de la partie inférieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void yams(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
{
    int somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = PTS_YAMS;
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[16], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[16], score_entier_dans_tab, score_dans_tab, score_inf, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[18], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[18], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void chance(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
 * \brief ajoute dans la feuille de marque le score donné par la combinaison CHANCE
 * \param feuille_marque_joueur : paramètre d'entrée/sortie étant le tableau 2d de la feuille de marque d'un joueur
 * \param score : paramètre d'entrée/sortie représentant le score d'un joueur
 * \param score_inf : paramètre d'entrée/sortie représentant le score de la partie inférieure d'un joueur
 * \param tab_des_gardes : paramètre d'entrée/sortie représentant le tableau des dés gardés par un joueur dans le tour actuel
 * \see choixCombinaison()
 * 
*/
void chance(char feuille_marque_joueur[NB_LIGNES][NB_COLONNES], int *score, int *score_inf, int tab_des_gardes[])
{
    int i, somme, score_entier_dans_tab;
    char score_dans_tab[4] = {' '};
    somme = 0;
    for (i = 0; i < NB_DES; i++)
    {
        somme = somme + tab_des_gardes[i];
    }
    
    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[17], somme, score_dans_tab);
    convertirIntToStr_ajoutScore(feuille_marque_joueur[17], score_entier_dans_tab, score_dans_tab, score_inf, score);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[18], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[18], score_entier_dans_tab, score_dans_tab);

    score_entier_dans_tab = convertirStrToInt_recupScore(feuille_marque_joueur[20], somme, score_dans_tab);
    convertirIntToStr(feuille_marque_joueur[20], score_entier_dans_tab, score_dans_tab);
}

/* --------------------------------------------------------------------------------*/

/**
 * \fn void afficherVainqueur(int tab_score[NB_JOUEURS], char tab_joueurs[NB_JOUEURS][9])
 * \brief affiche le vainqueur de la partie
 * \param tab_score : paramètre d'entrée/sortie correspondant au tableau de scores totaux des joueurs
 * \param tab_joueurs : paramètre d'entrée/sortie correspondant au tableau des noms des joueurs
 * 
 * 
*/
void afficherVainqueur(int tab_score[NB_JOUEURS], char tab_joueurs[NB_JOUEURS][9])
{
    if (tab_score[0] > tab_score[1]) 
    {
        printf("----- Le vainqueur est : %s -----", tab_joueurs[0]);

    }
    else if (tab_score[0] == tab_score[1])
    {
        printf("----- EGALITE -----");
    }
    else 
    {
        printf("----- Le vainqueur est : %s -----", tab_joueurs[1]);
    }
}