#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "fonction.h"
// John
// pM est le nombre de colonnes, pN est le nombre de lignes,pSym le nombre de
// symboles différents, la procédure demande utilisateur demande le nombre de colonnes
// et de lignes que le plateau de jeu aura ainsi que le nombre de symboles compris
// entre 4 et 6
////////////////////////////////////////////////////////////////
// ecrire score prend en paramètre un pointeur qui inidque l'option de jeu sélectionnée et un pointeur sur le score
// cette fonction écrit dans le fichier score.txt le mode de jeu et le score du joueur
int ecrire_score(int* po,int* pscore){
  
	FILE *f = fopen("score.txt","a");// ouverture du fichier en mode ajout qui permet d'écrire à la fin du fichier
	if (f==NULL){// vérification si le fichier existe
    		printf("impossible d'ouvrir le fichier");
    		return 1;
	}
	else{
		fprintf(f,"%d%d\n",*po,*pscore);// écrit dans le fichier
	}
	fclose(f);// ferme le fichier .txt
	return 0;
}


 // cette fonction prend en paramètres le nombre de lignes et de colonnes (N,M), le nombre de symboles différents dans la partie, le score du joueur et le plateau de jeu 
// cette fonction écrit dans le fichier s.txt tout les paramètres de la fonction pour pouvoir les récupérer plus tard

int sauvegarde(int N,int M,int sym, int pscore,int pla[][N],int temps){
	FILE * f = fopen("s.txt","w+");// ouverture du fichier en mode écriture
	if (f==NULL){// vérification si le fichier existe
    		printf("impossible d'ouvrir le fichier");
   	 	return 1;
  	}
	else{
 //permet d'écrire dans le fichier
    fprintf(f,"%d\n%d\n%d\n%d\n%d\n",pscore,M,N,sym,temps);
    // on parcour tout le tableau pour l'écrire dans le fichier
		for (int i =0;i<M;i++){
		   	for (int j =0;j<N;j++){
				fprintf(f,"%d ",pla[i][j]);
		}
	  	}
	fclose(f);// fermeture du fichier
	}
	return 0;

}
// cette fonction prend en paramètres un pointeur sur les options et affiche le meilleur score dans ce mode de jeu 
int recup_score(int *po ){
  char c[30];
  int temp;
  int temp2;
  int max = 0;
  int len;
  FILE *f =fopen("score.txt","r");// ouverture du fichier en mode lecture
  if (f==NULL){// vérification si le fichier existe
    printf("impossible d'ouvrir le fichier");
    return 1;
  }
  else {
    while(fgets(c,sizeof c,f)!=NULL){//parcour le fichier ligne par ligne
      temp = c[0] -'0';// transforme le char en int
      printf("%s",c);
      temp2 =0;
      len =strlen(c);
      if ((*po)==temp){// vérification du mode de jeu
        for (int i=1; i<len-1;i++){// on parcour le reste de la ligne
          temp = c[i]-'0';
          temp2 = temp2 + temp*pow(10,len-2-i) ;
        } 

        }
      if (temp2>max){
          max = temp2;// trouve le score max 
      }
    }
    printf("\033[H\033[J");
    printf("le meilleur score dans ce mode de jeu est de : %d points \n",max);
    fclose(f);// ferme le fichier
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////::
// fonction qui permet de securiser les scanf
void vide_buffer(){
while(getchar()!='\n'){}
}

// cette fonction ouvre les fichiers où la partie a été sauvegardé, return 1 si le fichier ne peut pas etre ouvert sinon return 0 et récupère dans des variables tout ce qu'il y'a écrit dans le fichier s.txt
int lire_sauvegarde(){
  // initialise toutes les variables
int score;
  int option = 4;
  int * po = &option;
  int *pscore=&score;
int N;
  int M;
  int sym;
  char c;
  int temps;
  	FILE * f = fopen("s.txt","r");	// ouvre le fichier
	if (f==NULL){// vérifie si le fichier existe
    		printf("impossible d'ouvrir le fichier");
   	 	return 1;
  	}
	else{// copie ce qu'il y'a écrit dans le fichier dans les variables correspondantes 
    fscanf(f, "%d", &score);
    fscanf(f, "%c", &c);//permet de passer le saut de ligne
    fscanf(f, "%d", &M);
    fscanf(f, "%c", &c);//permet de passer le saut de ligne
    fscanf(f, "%d", &N);
    fscanf(f, "%c", &c);//permet de passer le saut de ligne
    fscanf(f, "%d", &sym);
    fscanf(f, "%c", &c);//permet de passer le saut de ligne
    fscanf(f, "%d", &temps);
    //inistialise le plateau de jeu ici car N et M viennnt juste d'avoir la valeur qui nous intéresse
    int pla[M][N];
    // on parcour le tablaux pour recréer le plateau principal
    for(int i =0 ; i<M;i++){
      for (int j =0;j<N;j++){
      fscanf(f,"%d",&pla[i][j]);
        fscanf(f, "%c", &c);//permet de passer les espaces
      } 
    }
  
     fclose(f);// ferme le fichier 
    afiche(M, N, pla);
    jouer(po,N,M,sym,pla,pscore,temps);// lance la partie avec les paramètres qu'on a sauvegardés 
    }
	return 0;
}


