#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "fonction.h"

// demande utilisateur prend en parametre le un pointeur sur le nombre de ligne, colone,symbole
// demande a l'utilisateur le nombre de colone, ligne , symbole
void demande_utilisateur(int *pM, int *pN, int *pSym) {
  int verif;
  // permet de verifier si l'utilisateur rentre la bon caractère
 do{ printf(" rentrer le nombre de ligne :\n ");
  verif=scanf("%d",&*pM);
  vide_buffer();
  }while(verif!=1);
  do{ printf("rentrer le nombre de colonne :\n ");
  verif=scanf("%d", &*pN);
  vide_buffer();
  }while(verif!=1);
  do{while (*pSym >= 7 || *pSym <= 3) {
    printf(" rentrer le nombre de symbole :\n");
    scanf("%d", *&pSym);
    vide_buffer();
  }
  }while(verif!=1);
}



// crer plat prend en marametre le nombre de ligne de colone et de symbole et un tableau qui represente le plateau de jeu
// remplit le te plateaux de nombre aléatoire inferieur a nombre de symbole
void crer_plat(int M, int N, int nbr_Sym, int pla[][N]) {
  // parcour lame tableau pour le remplir
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      pla[i][j] = rand() % nbr_Sym + 1;// remplit le tableau de nombre aleatoire compris entre 1 et nbr sym
    }
  }
}

// fonction qui prend en parametre le nombre de ligne et de colone, et deux tableau, le platezux de jeu et un tableau 
// remplit le tableau temporaire verticale de 0 la ou y'a plus de 3 symbole identique sur la memecolone
void Vertical(int M, int N, int pla[][N], int Vertical[][N]) {
  // parcour le tableau
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (pla[i][j] != 0) {
        if (i < M - 1) {// on verifie qu'on ne sort pas des colone
          int y = i + 1;
          int compte = 0;
          while (y != M && (pla[i][j] == pla[y][j])) {
            compte++;// compte le nombre de symbole identique sur la meme colone
            y++;
          }
          if (compte >= 2) {
            for (int k = i; k < y; k++) {
              Vertical[k][j] = 0;// remplit le tableau Vertical de 0 la ou il y au moin 3 symbole identique sur la meme colone
            }
          }
        }
      }
    }
  }
}




// fonction qui prend en parametre le nombre de ligne et de colone, et deux tableau, le platezux de jeu et un tableau 
// remplit le tableau temporaire horizontal de 0 la ou y'a plus de 3 symbole identique sur la meme ligne
void Horizontal(int M, int N, int pla[][N], int Horizontal[][N]) {
  // parcour le tableau 
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (pla[i][j] != 0) {
        if (j < N - 1) {// verifie si on en sort pas du tableau
          int y = j + 1;
          int compte = 0;
          while (y != N && (pla[i][j] == pla[i][y])) {
            compte++;// permet de savoir combien d'element identique sont aligné
            y++;
          }
          if (compte >= 2) {
            for (int k = j; k < y; k++) {
              Horizontal[i][k] = 0;// remplie le tableau de 0 la ou plusieur symbole sont aligné
            }
          }    
        }
      }
    }
  }
}





// fonction qui prend en parametre le nombre de ligne et de colone, et deux tableau, le platezux de jeu et un tableau 
// remplit le tableau temporaire C de 0 la ou y'a 2 symbole tout a gauche du tableau et 1 symbole identique tout a droite du tableau



void Circulaire_G(int M, int N, int pla[][N], int C[][N]) {
  // parcour le tableau
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
       int compte = 0 ;
if (pla[i][0] == pla[i][1]) {
             compte++;// permet savoir si les symbole a gauche sonr identique
            }
     if (j==0 && compte >=1 && pla[i][N-1]==pla[i][0]){// si le symbole de deoite et egale a celui de gauche et que les deux premier symbolle sont identique 
       // on met des 0 sur les deux symbole a gauche et un a droite 
      C[i][0]= 0;
      C[i][1] = 0;
      C[i][N-1]= 0;
     }
   
    }
  }
 }



 // meme principe que Circurlaire _G mais avec les deux symbole a droite et un seul a gauche
 void Circulaire_D(int M, int N, int pla[][N], int C[][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int compte = 0 ;
      if (pla[i][N-2] == pla[i][N-1]) {
        compte++;
            }
     if (j==M-2 && compte >=1 && pla[i][N-1]==pla[i][0]){
      C[i][0]= 0;
      C[i][N-2] = 0;
      C[i][N-1]= 0;
     }
    }
  }
 }



// prend en parametre le nombre de ligne, de colone et tout les tableaux temporaire utilisé dans les fonction veritcsl hirizontzlecirculaire gzuche et droit et prend egalement en parametre le palteau proncipal
// remplit le tableaux principale si sur au moin un tableau il y a un 0
void simplification(int M, int N, int Horizontale[][N], int Vertical[][N],int C_G[][N],int C_D[][N],int pla[][N]) {
  // parcour le plateau
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (Horizontale[i][j] == 0 || Vertical[i][j] == 0 || C_G[i][j] == 0 || C_D[i][j] == 0) {
        pla[i][j] = 0;// remplit le tableaux si un des tablraux temporzire a pour valeur 0
      }
    }
  }
}


// fonction qui prend en paramtre le plateaux principale un autre tableaux et le nombre de ligen et colone
// initialise le deuxieme tableaux tel que le plateaux soit egale au deuxieme 

void initialisation(int N,int M, int pla[][N],int horizontale[][N]){
 // parcour le tableau
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      horizontale[i][j] = pla[i][j];// initialise le deuximeme tableau
    }
  }
}


// prend en parametre Le nombre de colone, de ligne, et le plateaux de jeu
// fait en sorte qu'il y ait la gravité vers la droite en placabt les zeronle plus a gauche possible
void gravite(int M, int N, int pla[][N]){
 // parcour le tableau de droite a gauche
  for (int i = M-1;i>=0;i--){
      for (int j = N-1; j >= 0; j--) {
       if (pla[i][j]==0){
        int k = j;
        while (k>=0 && pla[i][k]==0){
          k--;
        }
         if(k>=0){
           // decale a gauche les zero
           pla[i][j]= pla[i][k];
           pla[i][k]=0;
         }
       }
      }
    }
}


// ajout prend en parametre le nombre de ligne , de colone , le nombre de symbole et le plateau de jeu
// remplace les zero par des nombre aleatoire entre 1 et nbr sym
void ajout(int M, int N, int nbr_Sym, int pla[][N]){
  // parcour le tableau
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (pla[i][j]==0){
        pla[i][j] = rand() % nbr_Sym + 1;// remplace les 0 par des nombre aleatoire
      }
    }
  }
}


// compte zero prend en parametre le nombre de colOne de ligne et le plateau de jeu 
// elle retourne le nombre de zero dan sle tableau pour voir si il y a eu un changement ou pas
 int compte_zero(int M, int N, int pla[][N]){
   int zero = 0;
   // parcour le tableau
   for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (pla[i][j]==0){
        zero++;// on acremente zero si il y a un zero dans le tableau
      }
      else{
        break;
      }
    }
   }
   return zero;  // renvoie le nombre de zero 
 }




// cette fonction prend en parametre le nombre de colones de lignes de symbole et le plateau de jeux
// elle execute les fonction precedente pour eleminer tout les sumboel identique aligner et aploque la gravité.
void verification(int M, int N,int nbr_Sym, int pla[][N]){
  // initialise tout les tableaux temporaire
    int horizontal[M][N];
    int vertical[M][N];
    int C_G[M][N];
    int C_D[M][N];
  // remplace les zero par des symbole
    ajout(M, N, nbr_Sym,pla );
  // initialise tout les tableaux temporaire
    initialisation(N,M, pla, horizontal);
  initialisation(N,M, pla, vertical);
  initialisation(N,M, pla, C_G);
  initialisation(N,M, pla, C_D);
  // remplit les tableaux temporaire
    Horizontal(M, N, pla, horizontal);
    Vertical(M, N, pla, vertical);
    Circulaire_G(M,N,pla,C_G);
    Circulaire_D(M,N,pla,C_D);
  // remplit le p'ateaux principale de zero
    simplification(M, N, horizontal, vertical,C_G,C_D ,pla);
  // aplique la gravité
    gravite(M,N,pla);

}



//reaction en chaine prend en parametre le nombre de lignes de colones le nombre de symbole le plateaux de jeu et un pointeur sur le score du joueur
// permet de faire une reaction en chaine qui permet d'avoir le plateaux de jeu sans aucun zero et sans aucun aligenment de symbolle identique
void reaction_en_chaine(int M, int N,int nbr_Sym, int pla[][N],int * pscore){
  int zero1;
  *pscore +=compte_zero(M, N, pla);// acremente le score de 1 pour chaque zero dans le tableaux
  do {// verifie si ûa encore des zero 
    verification(M, N, nbr_Sym , pla);// elemine les symbole identique
    printf("\n");
    afiche( M, N, pla);
    zero1 = compte_zero(M, N, pla);
    *pscore +=compte_zero(M, N, pla);// acremente le score
    }while (zero1 !=0);
   printf("\nvotre score est de : %d",*pscore);
}
// ecahnge prend en parametre le nombre de colone de lignes de sumbole et les deux case a echanger le plateaux de jeu et un pointeur sur le score et un entier verif qui permet de verifier si o veut faire l'echange ou non 
// elle permet de savoir si on peut faire un echange et si verif est diferent de zero on fait l'echange
// renvoie 1 si le changement et possible sinon return 0
int echange(int N,int M,int nbr_sym,int colone1, int colone2,int ligne1,int ligne2,int verif, int pla[][N],int * pscore){
  // initialise un tableaux temporaire
  int pla_temp[M][N];
  initialisation(N,M, pla, pla_temp);
  // fait l'echange sur le tableaux temoporaire
  int temp = pla_temp[ligne2][colone2-1];
  pla_temp[ligne2][colone2-1] = pla_temp[ligne1][colone1-1];
  pla_temp[ligne1][colone1-1] = temp;
   
  //regarde si l'echange est possible(aligen au minimum 3 symbole)
  verification(M, N, nbr_sym, pla_temp);
  if(compte_zero(M,N, pla_temp)!=0){
      if(verif == 0){
        // on verifie juste si un changement est possible mais sans faire le changement
        return 1;
      }
    else{
      // on fait el changement en intitialisant le plateaux de jeu comme etant le plateaux temporaire ou nous avons fait l'échange 
      
      initialisation(N,M, pla_temp, pla);
       
      reaction_en_chaine(M, N,nbr_sym, pla,pscore);
      return 1;
    }

  }
  else{
    return 0;
  }
}



// victoire prend en parametre le nombres de ligne , de colones , de symbole et le plateaux de jeu
// renvoie 1 si le jouer peut encore jouer sinon renvoie 0 si plus aucun deplacement n'est  possible 
int victoire(int N,int M,int nbr_sym, int pla[][N]){
  //parcour le plateaux de jeu
  for (int i =0;i<M;i++){
   for (int j =0;j<N;j++){
     int k = 0;
     while(k<M){
       for (int l =0;l<N;l++){
         //on test tout les echange possible 
         if(echange(N,M,nbr_sym,j+1,l+1,i,k,0,pla,0)==1){
           return  1;
         }
       }
      k++;
     }
    }
  }
  return 0;
}



// demande case prend en parametre le nombre de colones de lignes de symboles le plateau de jeu et un pointeur sur le score
void demande_case (int N,int M,int nbr_sym, int pla[][N],int * pscore){
  char lettre1;
  int colone1;    
  int ligne1;
  char lettre2;
  int colone2;
  int ligne2;
  int verif;
  // verifie ce que l'utilisateur rentre dans les scanf
  do {
  printf("rentrer une lettre  : \n");
  verif=scanf("%c",&lettre1);
  vide_buffer();
  if (lettre1>=97){
    // transforme la miniscule en majuscule
    lettre1 = lettre1 - 32;
  }
  }while(lettre1<65 || lettre1>65+M );
    // verifie ce que l'utilisateur rentre dans les scanf  
  do{
  printf("rentrer un chiffre   : ");
  verif = scanf("%d",&colone1);
  vide_buffer();
  }while(verif !=1 || colone1<=0 || colone1>N);
  ligne1 = lettre1-65;// transforme la letre en entier 
    // verifie ce que l'utilisateur rentre dans les scanf
  do{
  printf("rentrer une deuxieme lettre  : ");
  scanf("%c",&lettre2);
   if (lettre2>=97){
    lettre2 = lettre2 - 32;// transforme la miniscule en majuscule
  }
  vide_buffer();
   }while(lettre2<65 || lettre2>65+M );
    // verifie ce que l'utilisateur rentre dans les scanf
  do {
  printf("colone un deuxime chiffre: ");
  scanf("%d",&colone2);
  vide_buffer();
  }while(verif !=1 || colone2<=0 || colone2>N);
  ligne2 = lettre2-65;//transforme la lettre en entier
  echange(N,M,nbr_sym, colone1, colone2,ligne1,ligne2,1,pla,pscore);// echange les deux case si cela est possible
}


// la fonction prend en parametre le nombres de lignes de colones de symbole le score du joueur et le plateaux de jeu
// cette fonction permet de jouer au jeu en mode temps illimité seulement 
int jouer2(int N,int M,int sym,int pla[][N],int *pscore){
  char c;
  int option =4;
  int* po = &option;
  
  while(victoire(N,M,sym,pla)==1 ){// boucle proncipale du jeu qui ne s'arrete que lorsque le joueru sauvegarde sa partie ou a perdu(plus de coup possible)
      //demande les case a echanger , les echange ,fait la reaction en chaine et acremente le score du joueur
      demande_case(N,M,sym,pla,pscore);
      afiche(M, N, pla);
    //affiche le score du joueur 
      printf("\n votre score est de : %d \n",*pscore);
    // demande si le joueur veut sauvegarder
      printf("souhaitez vous sauvgarder la partie ? O/N\n");
      scanf("%c",&c);
      if(c=='O'|| c=='o'){
          // sauvegarde la partit 
          sauvegarde(N,  M,sym, *pscore, pla);
          printf("votre partie a été sauvegarder");
          return 1;// pour sortir de la boucle 
      }
      
    }
  //  plus aucun coup n'est possible le joueur a perdu 
  printf("\nvous avez perdu ");
  printf("\nvotre score est de : %d",*pscore);
  // ecrit le score du joueur pour l'afficher si il s'aggit du meilleur score dans ce mode de jeu
	ecrire_score(po,pscore);
  
  
  return 0;
}

//fonction jouer ne prend en parametre que l'option choisi par le joueur au lancement du code
//elle fonction comme la fonction jouer 2 mis a part quelle demande les renseignement que jouer 2 a en parametre.
int jouer( int *po){
// score du joueur
int score = 0;
int * pscore= &score;
int temp=0;
int M = 0;
  int N = 0;
  int nbr_sym = 0;
  int *pM = &M;
  int *pN = &N;
  int *pSym = &nbr_sym;
  time_t deb;
  time_t fin;
  int min;
  // en fonction de l'option choisit le temps aura un temps different de base oprion est egale a 1 donc cela represente une partit de deux minutes
  if(*po==1){
      min=2;
  }
  else if(*po==2){
      min=5;
  }
  else {
    min =10;
  }
  // demande a l'utilisateur les nombres de colones , lignes , symbole ;
  demande_utilisateur(pM, pN, pSym);
  srand(time(NULL));
  int pla[M][N];
  int horizontal[M][N];
  int vertical[M][N];
  char c ='a';
  // on creer le plateaux principal
  crer_plat(M, N, nbr_sym, pla);
  // fait en sorte qu'il n'y a pas d'alignement possible au debut(pas besoin de vérifier dans jouer 2 car cela a deja été faite a la partie précedente)
  reaction_en_chaine(M, N, nbr_sym, pla,pscore);
  afiche(M, N, pla);
  deb = time(NULL);//initialise le debut du chronometre
  fin =time(NULL);
  temp = fin-deb;
  *pscore = 0;
  while(victoire(N,M,nbr_sym,pla)==1  &&  temp<min*60){// boucle principale qui regarde si il y a encore un coup possible ou si le temps impartit est dépasser
      //demande les case a echanger , les echange ,fait la reaction en chaine et acremente le score du joueur
      demande_case(N,M,nbr_sym,pla,pscore);
      afiche(M, N, pla);
    // met a jour le chronometre
      fin = time(NULL);
      temp = fin-deb;
    if(*po!=4){// si il a un temps on met a jour le chrnometre
      temp = fin-deb;
    }
    else{// sinon on affiche le score et demande au joueur si il souhaites sauvegarder
      printf("\n votre score est de : %d\n",*pscore);
      printf("souhaitez vous sauvegarder la partie ? O/N\n");
      scanf("%c",&c);
    }
    if(c == 'O'|| c =='o'){
      // sauvegarde la partie 
      sauvegarde(N,M,nbr_sym,*pscore,pla);
      printf("votre partie a été sauvegarder");
      return 1;// sort de la boucle
    }
  }
// si le joueur a perdu sa affiche son son score et l'ecrit dans une sauvegarde pour afficher le meilleur score sans ce mode de jeu
printf("\nvotre score est de %d",*pscore);
ecrire_score(po,pscore);
return 0;
}
    