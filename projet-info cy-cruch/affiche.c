#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "fonction.h"


int image1 (){
    FILE *fichier = fopen("cy-crush.txt", "r");
    int caractere;

    if (fichier == NULL) {
        printf ("erreur lors de l'ouverture du fichier\n");
        return 1;
    }

    while ((caractere = fgetc (fichier)) != EOF) {
        printf ("%c", caractere);
    }

    fclose (fichier);

    return 0;
}

// fonction qui prend en paramètre le nombre de lignes, colonnes et le plateau de jeu
// affiche le plateau de jeu sous forme de grille avec le numéro des colonnes et les lettres pour les lignes
void afiche (int M, int N, int pla[][N]) {
 printf ("\033[H\033[J"); // permet de réinitialiser le terminal

  printf ("  ");
  for (int i = 1; i <= N; i++) {
    if (i<10){// permet de connaitre la taille du numéro de ligne pour avoir un affichage optimal
    printf (" %d ", i);// affiche les numéros des colonnes
    }
    else{
    printf (" %d", i);
    }
  }
  printf (" ");
 
  printf ("\n   ");
  for (int i = 1; i <= N; i++) {
    printf ("-- ");
  }
  printf ("\n");
  // parcour le tableau pour afficher chaque élément
  for (int i = 0; i < M; i++) {
    printf ("%c |", 65 + i);// affiche une lettre pour chaque ligne
    for (int j = 0; j < N; j++) {
      //permet d'afficher des emojis à la place des chiffres
      switch (pla[i][j]){
       
        case 6:
          printf ("\U0001F36D ");
          break;
        case 1:
          printf ("\U0001F36B ");
          break;
        case 2:
          printf ("\U0001F36C ");
          break;
        case 3:
          printf ("\U0001F36E ");
          break;
        case 4:
          printf ("\U0001F36F ");
          break;
        case 5:
          printf ("\U0001F9C1 ");
          break;
        default:
          printf ("   ");
        }
    }
    printf ("\n");
  }
}

 void option (int *po){
   int verif;
   printf (" Votre objectif est d'avoir le plus de points possible.\n\n");
	printf (" Veuillez choisir le temps : \n\n\n");
  printf ("                           1 : 2 min \n");
  printf ("                           2 : 5 min \n");
  printf ("                           3 : 10 min \n");
  printf ("                           4 : temps illimité \n");
   do{
        verif = scanf ("%d", &*po);
        vide_buffer();
   }while(*po >=5 || *po<=0 || verif != 1);
          switch (*po){
            case 1 : printf (" vous avez 2 min \n");
            break;
            case 2 : printf ("vous avez 5 min \n");
            break;
            case 3 : printf (" vous avez 10 min \n");
            break;
		        case 4 : printf (" vous avez le temps illimité \n");
            break;
            
          }
          printf ("\033[H\033[J"); 
 }






// cette fonction prend en paramètre un pointeur sur l'option qui a pour valeur initiale 1
// cette fonction est le menu du jeu, depuis ce menu l'utilisateur a accès a toute les fonctionalités du jeu 
// elle permet de lancer le jeu

int menu (int *po, int test){
  if (test ==0){
    image1();
    printf ("Bienvenue dans le jeu !\n\n");
    option (po);
  }
  
    int choix; 
     image1();
	
    FILE * fic;
    int verif;
     // affiche le menu
  printf ("\n");
 printf ("Bienvenue dans le jeu !\n");
 printf ("sélectionnez votre choix\n");
   do {printf ("                                         1: Jouer\n");
      printf ("                                         2: OPTION\n");
      printf ("                                         3: score\n");
      printf ("                                         4: sauvegarde\n");
      printf ("                                         5: sortie\n");
      // demande a l'utilisateur où il souhaites aller
  verif = scanf ("%d", &choix);
  vide_buffer ();
  }while (verif != 1 || choix <= 0 || choix >=6 );
      printf ("\033[H\033[J"); 
  switch (choix) {
    case 1: printf (" A vous de jouer \n");
        nouvelle_partie (po);
      // l'utilisateur lance une partie avec les options qu'il a choisit
      break;
  
   
  case 2 :
    // l'utilisateur choisit son mode de jeu, initialement celui de 2 min
	       option(po);
          menu (po,1);  // relance le menu pour lancer une partie ou changer de mode
          return 0;
      
    case 3 : recup_score (po); // affiche le meilleur score dans le mode de jeu choisit par l'utilisateur
          menu (po,1);
          break;
    case 4:lire_sauvegarde (); // permet au joueur de reprendre la partie qu'il avait sauvegardée (ne marche que sur les parties à temps illimité)
    break;
    case 5 : printf ("quitter le jeu \n");  // permet de quitter le  jeu  
    break;
  }
   
   
  return 0;
}
 