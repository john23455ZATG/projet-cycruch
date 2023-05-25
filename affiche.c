#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "fonction.h"


int image1(){
    FILE *fichier = fopen("cy-crush.txt", "r");
    int caractere;

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    while ((caractere = fgetc(fichier)) != EOF) {
        printf("%c", caractere);
    }

    fclose(fichier);

    return 0;
}

// fonction qui prend en paramtre le nombre de ligne, colone et le plateau de jeu
// affiche le plateau de jeu sous forme de grille avec le numero des colones et la lettre des lignes
void afiche(int M, int N, int pla[][N]) {
 printf("\033[H\033[J"); // permet de renitialisé le terminal

  printf("  ");
  for (int i = 1; i <= N; i++) {
    if(i<10){// permet de connaitre la taille du numero de ligne pour avoir un affichage optimal
    printf(" %d ", i);// affiche les numero des colone
    }
    else{
    printf(" %d", i);
    }
  }
  printf(" ");
 
  printf("\n   ");
  for (int i = 1; i <= N; i++) {
    printf("-- ");
  }
  printf("\n");
  // parcour le tableau pour afficher chasue element
  for (int i = 0; i < M; i++) {
    printf("%c |", 65 + i);// afiche la lettre des ligne
    for (int j = 0; j < N; j++) {
      //permet d'afficher des emogie a la place des numero
      switch(pla[i][j]){
       
        case 6:
          printf("\U0001F36D ");
          break;
        case 1:
          printf("\U0001F36B ");
          break;
        case 2:
          printf("\U0001F36C ");
          break;
        case 3:
          printf("\U0001F36E ");
          break;
        case 4:
          printf("\U0001F36F ");
          break;
        case 5:
          printf("\U0001F9C1 ");
          break;
        default:
          printf("  ");
        }
    }
    printf("\n");
  }
}







// cette fonction prend en parmatre un pointeur sur l'option qui a pour valeur initiale 1
// cette fonction est le menu du jeu depuis cette ce menu l'utilisateur a accès a toute les fonctionalité du jeu 
// elle permet de lancer le jeu

int menu(int *po ){
  
    int choix; 
    int ple[3][3];
	for (int i =0;i<3;i++){
	   for (int j =0;j<3;j++){
	ple[i][j]=i;
	}
		}
	
    FILE * fic;
    int verif;
     // affiche le menu
  printf("\n");
 printf("Bienvenue dans le jeu\n");
 printf("selectionner votre choix\n");
   do {printf("                                         1: Jouer\n");
      printf("                                         2: OPTION\n");
      printf("                                         3: score\n");
      printf("                                         4: sauvegarde\n");
      printf("                                         5: sortie\n");
      // demande a l'utilisateur ou il souhaites  aller
  verif=scanf("%d",&choix);
  vide_buffer();
  }while(verif!=1);
      printf("\033[H\033[J"); 
  switch( choix) {
    case 1: printf(" A vous de jouer \n");
        jouer(po);
      // l'utilisateur lance une partit avec les option qu'il a choisit
      break;
  
   
  case 2 :
    // l'utiliosateur choisit son mode de jeu initilaement celui si est de 2 min
	printf("votre objectif est d'avoir le plus de point possible.\n'");
	printf(" option : choisir le temps \n");
  printf("                                             1 : 2 min \n");
  printf("                                             2 : 5 min \n");
  printf("                                             3: 10 min \n");
  printf("                                             4 : temps illimité \n");
        scanf("%d", &*po);
          switch(*po){
            case 1 : printf(" vous avez 2 min \n");
            break;
            case 2 : printf("vous avez 5 min \n");
            break;
            case 3 : printf(" vous avez 10 min\n");
            break;
		        case 4 : printf(" vous avez le temps illimité \n");
            break;
            
          }
          printf("\033[H\033[J"); 
          menu(po);  // relance le menu pour lancer une partit ou erechanger de mode
          return 0;
      
    case 3 : recup_score(po); // affiche le meilleur score dans le mode de jeu choisit par l'utilisateur
          menu(po);
          break;
    case 4:lire_sauvegarde(); // permet au joueur de reprendre la partit qu'il avait sauvegarder (ne marche que sur les paartit a temps illimité)
    break;
    case 5 : printf("Quitter le jeu \n");  // permet de quitter le  jeu  
    break;
  }
   
   
  return 0;
}
 