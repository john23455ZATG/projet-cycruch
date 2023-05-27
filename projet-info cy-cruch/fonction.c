#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonction.h"

// demande utilisateur prend en paramètre un pointeur sur le nombre de lignes, colonnes, symboles et demande à l'utilisateur le nombre de colonnes, lignes, symboles

void demande_utilisateur (int *pM, int *pN, int *pSym) {
  int verif;
  // permet de vérifier si l'utilisateur rentre la bon caractère

  do {
    printf(" rentrez le nombre de lignes :\n ");
    verif = scanf("%d", &*pM);
    vide_buffer();
  } while (*pM<=1 || *pM>=27 || verif != 1 );

  do {
    printf("rentrez le nombre de colonnes :\n ");
    verif = scanf("%d", &*pN);
    vide_buffer();
  } while (verif != 1 || *pN <= 1 || *pM>=27);

  do {
    while (*pSym >= 7 || *pSym <= 3) {
      printf(" rentrez le nombre de symboles ( entre 4 et 6) :\n");
      scanf("%d", *&pSym);
      vide_buffer();
    }
  } while (verif != 1);
}

// crer plat prend en paramètre le nombre de lignes de colonnes, de symboles
// et un tableau qui représente le plateau de jeu remplit le plateau avec des
// nombres aléatoires inférieurs au nombre de symboles

void crer_plat (int M, int N, int nbr_Sym, int pla[][N]) {
  // parcour le tableau pour le remplir
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      pla[i][j] = rand() % nbr_Sym + 1; // remplit le tableau de nombres
                                        // aléatoires compris entre 1 et nbr sym
    }
  }
}

// fonction qui prend en paramètre le nombre de lignes et de colonnes et deux
// tableaux, le plateau de jeu et un tableau temporaire : Vertical, de 0 là où y'a plus de 3 symboles identiques sur la même colonnes

void Vertical (int M, int N, int pla[][N], int Vertical[][N]) {
  // parcour le tableau
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      if (pla[i][j] != 0) {
        if (i < M - 1) { // on vérifie qu'on ne sort pas des colonnes
          int y = i + 1;
          int compte = 0;

          while (y != M && (pla[i][j] == pla[y][j])) {
            compte++; // compte le nombre de symboles identiques sur la même
                      // colonne
            y++;
          }

          if (compte >= 2) {

            for (int k = i; k < y; k++) {

              Vertical[k][j] =
                  0; // remplit le tableau Vertical de 0 là où il y au moins 3
                     // symboles identiques sur la même colonne
            }
          }
        }
      }
    }
  }
}

// fonction qui prend en paramètre le nombre de lignes et de colonnes, et deux
// tableaux, le plateau de jeu et un tableau temporaire : Horizontal de 0 là où y'a plus de 3 symboles identiques sur la même ligne

void Horizontal (int M, int N, int pla[][N], int Horizontal[][N]) {
  // parcour le tableau
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      if (pla[i][j] != 0) {
        if (j < N - 1) { // vérifie qu'on ne sort pas du tableau
          int y = j + 1;
          int compte = 0;
          while (y != N && (pla[i][j] == pla[i][y])) {

            compte++; // permet de savoir combien d'éléments identiques sont
                      // alignés
            y++;
          }
          if (compte >= 2) {
            for (int k = j; k < y; k++) {

              Horizontal[i][k] = 0; // remplit le tableau de 0 là où plusieurs
                                    // symboles sont alignés
            }
          }
        }
      }
    }
  }
}

// fonction qui prend en parametre le nombre de lignes, de colonnes et deux
// tableaux, le plateau de jeu et un tableau temporaire : C, de
// 0 là où y'a 2 symboles tout à gauche du tableau et 1 symbole identique tout à
// droite du tableau

void Circulaire_G (int M, int N, int pla[][N], int C[][N]) {
  // parcour le tableau
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      int compte = 0;
      if (pla[i][0] == pla[i][1]) {
        compte++; // permet savoir si les symboles à gauche sont identiques
      }
      if (j == 0 && compte >= 1 &&
          pla[i][N - 1] ==
              pla[i][0]) { // si le symbole de droite et égal à celui de gauche
                           // et que les deux premiers symboles sont identiques
        // on met des 0 sur les deux symboles à gauche et un à droite
        C[i][0] = 0;
        C[i][1] = 0;
        C[i][N - 1] = 0;
      }
    }
  }
}

// même principe que Circurlaire _G mais avec les deux symboles à droite et un
// seul à gauche

void Circulaire_D (int M, int N, int pla[][N], int C[][N]) {
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      int compte = 0;
      if (pla[i][N - 2] == pla[i][N - 1]) {
        compte++;
      }
      if (j == M - 2 && compte >= 1 && pla[i][N - 1] == pla[i][0]) {
        C[i][0] = 0;
        C[i][N - 2] = 0;
        C[i][N - 1] = 0;
      }
    }
  }
}

// prend en paramètre le nombre de lignes, de colonnes et tout les tableaux
// temporaires utilisés dans les fonctions Veritcal, Horizontal, Circulaire gauche et droite et prend également en paramètres le palteau principal et remplit le tableau principal si sur au moins un tableau il y a un 0

void simplification (int M, int N, int Horizontale[][N], int Vertical[][N],
                    int C_G[][N], int C_D[][N], int pla[][N]) {
  // parcour le plateau
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      if (Horizontale[i][j] == 0 || Vertical[i][j] == 0 || C_G[i][j] == 0 ||
          C_D[i][j] == 0) {
        pla[i][j] = 0; // remplit le tableau si un des tab  temporaire a
                       // pour valeur 0
      }
    }
  }
}

// fonction qui prend en paramètre le plateau principal, un autre tableau et le
// nombre de lignes et colonnes, initialise le deuxième tableau tel que le plateau soit égal au deuxième

void initialisation (int N, int M, int pla[][N], int horizontale[][N]) {
  // parcour le tableau
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      horizontale[i][j] = pla[i][j]; // initialise le deuxième tableau
    }
  }
}

// prend en paramètre le nombre de colonnes, de lignes, et le plateau de jeu
// fait en sorte qu'il y ait la gravité vers la droite en plaçant les zéro le
// plus à gauche possible

void gravite (int M, int N, int pla[][N]) {
  // parcour le tableau de droite à gauche
  for (int i = M - 1; i >= 0; i--) {

    for (int j = N - 1; j >= 0; j--) {

      if (pla[i][j] == 0) {
        int k = j;
        while (k >= 0 && pla[i][k] == 0) {

          k--;
        }
        if (k >= 0) {
          // décale à gauche les zéros
          pla[i][j] = pla[i][k];
          pla[i][k] = 0;
        }
      }
    }
  }
}

// ajout prend en paramètres le nombre de lignes, de colonnes, le nombre de
// symboles et le plateau de jeu remplace les zéros par des nombres aléatoires entre
// 1 et nbr sym

void ajout (int M, int N, int nbr_Sym, int pla[][N]) {
  // parcour le tableau
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      if (pla[i][j] == 0) {
        pla[i][j] =
            rand() % nbr_Sym + 1; // remplace les 0 par des nombre aléatoires
      }
    }
  }
}

// compte zero prend en paramètre le nombre de colonnes, de lignes et le plateau de jeu, elle retourne le nombre de zéros dans le tableau pour voir si il y a eu un changement ou pas

int compte_zero (int M, int N, int pla[][N]) {
  int zero = 0;
  // parcour le tableau
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      if (pla[i][j] == 0) {
        zero++; // on incrémente zero si il y a un zéro dans le tableau
      } else {
        break;
      }
    }
  }
  return zero; // renvoie le nombre de zéros
}

// cette fonction prend en paramètre le nombre de colonnes, de lignes de symboles
// et le plateau de jeu, elle execute les fonctions précédentes pour éliminer tout les symboles identiques alignés et applique la gravité

void verification (int M, int N, int nbr_Sym, int pla[][N]) {
  // initialise tout les tableaux temporaires
  int horizontal[M][N];
  int vertical[M][N];
  int C_G[M][N];
  int C_D[M][N];

  // remplace les zéros par des symboles
  ajout (M, N, nbr_Sym, pla);

  // initialise tout les tableaux temporaires
  initialisation (N, M, pla, horizontal);
  initialisation (N, M, pla, vertical);
  initialisation (N, M, pla, C_G);
  initialisation (N, M, pla, C_D);

  // remplit les tableaux temporaires
  Horizontal (M, N, pla, horizontal);
  Vertical (M, N, pla, vertical);
  Circulaire_G (M, N, pla, C_G);
  Circulaire_D (M, N, pla, C_D);

  // remplit le plateaux principal de zéros
  simplification (M, N, horizontal, vertical, C_G, C_D, pla);
  // applique la gravité
  gravite(M, N, pla);
  

  
}

// reaction en chaine prend en paramètres le nombre de lignes de colonnes le
// nombre de symboles le plateaux de jeu et un pointeur sur le score du joueur
//  permet de faire une réaction en chaine qui permet d'avoir le plateau de jeu
//  sans aucun zéro et sans aucun alignement de symbole identiques

void reaction_en_chaine(int M, int N, int nbr_Sym, int pla[][N], int *pscore) {
  int zero1;
  *pscore += compte_zero ( M, N, pla); // incrémente le score de 1 pour chaque zéro dans le tableau

  do {                                // vérifie si on a encore des zéros
    verification (M, N, nbr_Sym, pla); // élimine les symboles identiques
    printf("\n");
    afiche (M, N, pla);
    zero1 = compte_zero (M, N, pla);
    *pscore += compte_zero (M, N, pla); // incrémente le score
  } while (zero1 != 0);

  printf ("\nvotre score est de : %d", *pscore);
}

// echange prend en paramètres le nombre de colonnes, de lignes de symboles et les
// deux cases à échanger le plateau de jeu et un pointeur sur le score et un
// entier verif qui permet de vérifier si on peut faire l'échange ou non elle permet de savoir si on peut faire un échange et si verif est différent de zéro
// on fait l'échange, renvoie 1 si le changement et possible sinon return 0

int echange (int N, int M, int nbr_sym, int colone1, int colone2, int ligne1,
            int ligne2, int verif, int pla[][N], int *pscore) {

  // initialise un tableau temporaire
  int pla_temp[M][N];
  int pla_afichage[M][N];
  initialisation (N, M, pla, pla_temp);

  // fait l'échange sur le tableau temoporaire
  int temp = pla_temp[ligne2][colone2 - 1];
  pla_temp[ligne2][colone2 - 1] = pla_temp[ligne1][colone1 - 1];
  pla_temp[ligne1][colone1 - 1] = temp;
  initialisation (N, M, pla_temp, pla_afichage);
  // regarde si l'échange est possible(aligne au minimum 3 symboles)
  verification (M, N, nbr_sym, pla_temp);
  if (compte_zero (M, N, pla_temp) != 0) {
    if (verif == 0) {
      // on verifie juste si un changement est possible mais sans faire le
      // changement
      return 1;
    }

    else {
      
      afiche (M, N, pla_afichage);
      sleep(2);
      afiche(M, N, pla_temp);
      sleep(1);

      
        // on fait le changement en intitialisant le plateau de jeu comme étant
      // le plateau temporaire où nous avons fait l'échange
      initialisation (N, M, pla_temp, pla);
      reaction_en_chaine (M, N, nbr_sym, pla, pscore);
      return 1;   }

  } else {
    return 0;
  }
}

// victoire prend en paramètres le nombres de lignes, de colonnes, de symboles et
// le plateau de jeu renvoie 1 si le jouer peut encore jouer sinon renvoie 0 si
// plus aucun déplacement n'est  possible

int victoire(int N, int M, int nbr_sym, int pla[][N]) {
  // parcour le plateau de jeu
  for (int i = 0; i < M; i++) {

    for (int j = 0; j < N; j++) {

      int k = 0;
      while (k < M) {

        for (int l = 0; l < N; l++) {

          // on test tout les échanges possibles
          if (echange (N, M, nbr_sym, j + 1, l + 1, i, k, 0, pla, 0) == 1) {
            return 1;
          }
        }
        k++;
      }
    }
  }
  return 0;
}

// demande case prend en paramètres le nombre de colonnes, de lignes de symboles le
// plateau de jeu et un pointeur sur le score

void demande_case (int N, int M, int nbr_sym, int pla[][N], int *pscore) {
  char lettre1;
  int colone1;
  int ligne1;
  char lettre2;
  int colone2;
  int ligne2;
  int verif;

  // vérifie ce que l'utilisateur rentre dans les scanf
  printf("veuillez renter les coordoneés de la première case à échanger : \n");
  do {
    printf ("rentrez une lettre  : ");
    verif = scanf ("%c", &lettre1);
    vide_buffer ();
    if (lettre1 >= 97) {
      // transforme la miniscule en majuscule
      lettre1 = lettre1 - 32;
    }
  } while (lettre1 < 65 || lettre1 > 65 + M);

  // vérifie ce que l'utilisateur rentre dans les scanf
  do {
    printf ("rentrez un chiffre  : ");
    verif = scanf ("%d", &colone1);
    vide_buffer ();
  } while (verif != 1 || colone1 <= 0 || colone1 > N);

  ligne1 = lettre1 - 65; // transforme la lettre en entier
                         // vérifie ce que l'utilisateur rentre dans les scanf
  printf("veuillez renter les coordoneés de la deuxième case à échanger :\n");
  do {
    printf ("rentrez une deuxième lettre  : ");
    scanf ("%c", &lettre2);
    if (lettre2 >= 97) {
      lettre2 = lettre2 - 32; // transforme la miniscule en majuscule
    }
    vide_buffer ();
  } while (lettre2 < 65 || lettre2 > 65 + M);

  // vérifie ce que l'utilisateur rentre dans les scanf
  do {
    printf ("rentrez un deuxième chiffre  : ");
    scanf ("%d", &colone2);
    vide_buffer ();
  } while (verif != 1 || colone2 <= 0 || colone2 > N);

  ligne2 = lettre2 - 65; // transforme la lettre en entier
  echange (N, M, nbr_sym, colone1, colone2, ligne1, ligne2, 1, pla,
          pscore); // échange les deux cases si cela est possible
}

// la fonction prend en paramètres le nombres de lignes, de colonnes, de symboles, le
// score du joueur et le plateau de jeu, cette fonction permet de jouer au jeu
// en mode temps illimité seulement,
// fonction jouer ne prend en parametre que l'option choisie par le joueur au
// lancement du code elle fonctionne comme la fonction jouer 2 mis à part qu'elle
// demande les renseignements que jouer 2 a en paramètre

void nouvelle_partie (int *po) {
  int score = 0; // score du joueur
  int *pscore = &score;
  int temp = 0; /////
  int M = 0;
  int N = 0;
  int nbr_sym = 0;
  int *pM = &M;
  int *pN = &N;
  int *pSym = &nbr_sym;
  // demande à l'utilisateur les nombres de colonnes, lignes, symboles
  demande_utilisateur (pM, pN, pSym);
  srand (time (NULL));

  int pla[M][N];
  int horizontal[M][N];
  int vertical[M][N];

  // on crée le plateau principal
  crer_plat (M, N, nbr_sym, pla);

  // fait en sorte qu'il n'y a pas d'alignement possible au début(pas besoin de vérifier dans jouer 2 car cela a déjà été fait à la partie précedente)
  reaction_en_chaine (M, N, nbr_sym, pla, pscore);

  afiche (M, N, pla);
  *pscore = 0;
  jouer (po, M, N, nbr_sym, pla, pscore,0);
}

int jouer (int *po, int M, int N, int nbr_sym, int pla[][N], int *pscore,int temps){
  time_t deb;
  time_t fin;
  int min;
  char c = 'a';
  int temp2 = temps  ;
  int verif ;
  temps = 0;
  // en fonction de l'option choisie le temps aura un temps different de base
  // option est égale à 1 donc cela représente une partie de deux minutes
  if (*po == 1) {
    min = 2;
  } else if (*po == 2) {
    min = 5;
  } else {
    min = 10;
  }

  deb = time (NULL) - temp2; // initialise le début du chronomètre
  fin = time (NULL);
  while (victoire (N, M, nbr_sym, pla) == 1 && temps < min * 60) { // boucle principale qui regarde si il y a encore un coup possible ou si le temps impartit est dépassé

    // demande les cases à échanger, les échange,fait la réaction en chaine et
    // incrémente le score du joueur
    printf("vous êtes à %d seconde \n ",temp2);
    demande_case (N, M, nbr_sym, pla, pscore);

    afiche (M, N, pla);

    // met à jour le chronomètre
    fin = time (NULL);
    temp2 = fin-deb-3 ;
    if (*po != 4) { // si il a un temps on met à jour le chronomètre
      temps =temp2;
    }

    else { // sinon on affiche le score et demande au joueur si il souhaite
           // sauvegarder
        do {
          printf ("\n votre score est de : %d\n", *pscore);
          printf ("souhaitez vous sauvegarder la partie ? O/N/S (sortir du jeu)\n");
          verif = scanf ("%c", &c);
          vide_buffer();
        }while(c!= 'O'&& c!= 'o' && c!='S' && c!= 's' && c!='N' && c!= 'n');
    }

    if (c == 'O' || c == 'o') {

      sauvegarde(N, M, nbr_sym, *pscore, pla,temp2); // sauvegarde la partie
      printf ("votre partie a été sauvegarder");
      return 1; // sort de la boucle
    }
    else if (c == 'S' || c == 's'){
    ecrire_score(po,pscore);
    return 1;
    
  }
  }
  

  // si le joueur a perdu son affichage, son score est écrit dans une
  // sauvegarde pour afficher le meilleur score sans ce mode de jeu
  printf ("\nvotre score est de %d", *pscore);
  ecrire_score (po, pscore);
  return 0;
}