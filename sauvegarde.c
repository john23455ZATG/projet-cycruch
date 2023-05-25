#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "fonction.h"
// John
// pM est le nombre de colone , pN est le nombre de ligne ,pSym le nombre de
// symbole diferent la procedure demande utilisateur demande le nombre de colone
// et de ligne que le plateau de jeu aura ainsi que le nombre de symbole compris
// entre 4 et 6
////////////////////////////////////////////////////////////////
// ecrire scire prend en parametre un pointeur qui inidque l'option de jeu selectioner  et un pointeur sur le score.
// cette finction ecrit dans le fichier score.txt le mode de jeu et le score du joueur
int ecrire_score(int* po,int* pscore){
  
	FILE *f = fopen("score.txt","a");// ouverture du fichier en mode ajout qui permet d'ecrire a la fin du fichier
	if (f==NULL){// verification si le fichier existe
    		printf("impossible d'ouvrir le fichier");
    		return 1;
	}
	else{
		fprintf(f,"%d%d",*po,*pscore);// ecrit dans le fichier
	}
	fclose(f);// ferme le fichier .txt
	return 0;
}


 // cette fonction prend en parametre le nombre de ligne et de colone (N,M) le nombre de symbole differnet dans la partit le score du joueur et le plateaux de jeu 
// cette fonction ecrit dans le fichier s.txt tout les parametre de la fonction pour pouvoir les recuperer plus tard

int sauvegarde(int N,int M,int sym, int pscore,int pla[][N]){
	FILE * f = fopen("s.txt","w+");// ouverture du fichier en mode ecriture
	if (f==NULL){// verification si le fichier existe
    		printf("impossible d'ouvrir le fichier");
   	 	return 1;
  	}
	else{
 //permet d'ecrire dans le fichier
    fprintf(f,"%d\n%d\n%d\n%d\n",pscore,M,N,sym);
    // on parcour tout le tableau pour l'ecrire dans le fichier
		for (int i =0;i<M;i++){
		   	for (int j =0;j<N;j++){
				fprintf(f,"%d ",pla[i][j]);
		}
	  	}
	fclose(f);// fermeture du fichier
	}
	return 0;

}
// cette fonction prend en parametre un pointeur sur les option et affiche le meilleur score dans se mode de jeu 
int recup_score(int *po ){
  char c[30];
  int temp;
  int temp2;
  int max = 0;
  int len;
  FILE *f =fopen("score.txt","r");// ouverture du fichier en mode lecture
  if (f==NULL){// verification si le fichier existe
    printf("impossible d'ouvrir le fichier");
    return 1;
  }
  else {
    while(fgets(c,sizeof c,f)!=NULL){//parcour le fichier ligne par ligne
      temp = c[0] -'0';// transforme le char en int
      printf("%s",c);
      temp2 =0;
      len =strlen(c);
      if ((*po)==temp){// verification du mode de jeu
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
// fonction qui permet de securisé les scanf
void vide_buffer(){
while(getchar()!='\n'){}
}

// cette fonction ouvrele fichier ou la partit a été sauvegarder return 1 si le fichier ne peut pas etre ouvert sinon return 0 et recupere dans des variable tout ce qui y'a ecrit dans le fichier s.txt
int lire_sauvegarde(){
  // initialise toute les variables
int score;
  int *pscore=&score;
int N;
  int M;
  int sym;
  char c;
  int temp;
  	FILE * f = fopen("s.txt","r");	// ouvre le fichier
	if (f==NULL){// verifie si le fichier existe
    		printf("impossible d'ouvrir le fichier");
   	 	return 1;
  	}
	else{// copie ce qui y'a ecrit dans le fichier dans les variable coresspondante 
    fscanf(f, "%d", &score);
    fscanf(f, "%c", &c);//permet de passer le saut de ligne
    fscanf(f, "%d", &M);
    fscanf(f, "%c", &c);//permet de passer le saut de ligne
    fscanf(f, "%d", &N);
    fscanf(f, "%c", &c);//permet de passer le saut de ligne
    fscanf(f, "%d", &sym);
    //inistialise le plateaux de jeu ici car N et M vienne juste d'avoir la valeur qui nous intéraisse
    int pla[M][N];
    // on parcour le tablaux pour recrer le plateaux principale
    for(int i =0 ; i<M;i++){
      for (int j =0;j<N;j++){
      fscanf(f,"%d",&pla[i][j]);
        fscanf(f, "%c", &c);//permet de passer les espace
      } 
    }
  
     fclose(f);// ferme le fichier 
    afiche(M, N, pla);
    jouer2(N,M,sym,pla,pscore);// lance la partie avec les parametre qu'on a sauvegarder 
    }
	return 0;
}



