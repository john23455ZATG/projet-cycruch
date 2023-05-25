#ifndef PLAYER_H
#define PLAYER_H
int image1();

int ecrire_score(int* po,int* pscore);
int sauvegarde(int N,int M,int sym, int pscore,int pla[][N]);
int recup_score(int *po );
void vide_buffer();
void demande_utilisateur(int *pM, int *pN, int *pSym);
void crer_plat(int M, int N, int nbr_Sym, int pla[][N]);
void afiche(int M, int N, int pla[][N]);
 
void Vertical(int M, int N, int pla[][N], int Vertical[][N]);
void Horizontal(int M, int N, int pla[][N], int Horizontal[][N]);
void Circulaire_G(int M, int N, int pla[][N], int C[][N]);
void Circulaire_D(int M, int N, int pla[][N], int C[][N]);
void simplification(int M, int N, int Horizontale[][N], int Vertical[][N],int C_G[][N],int C_D[][N],int pla[][N]);
void initialisation(int N,int M, int pla[][N],int horizontale[][N]);
void gravite(int M, int N, int pla[][N]);
void ajout(int M, int N, int nbr_Sym, int pla[][N]);
int compte_zero(int M, int N, int pla[][N]);
void  verification(int M, int N,int nbr_Sym, int pla[][N]);
void reaction_en_chaine(int M, int N,int nbr_Sym, int pla[][N],int * pscore);
int echange(int N,int M,int nbr_sym,int colone1, int colone2,int ligne1,int ligne2,int verif, int pla[][N],int * pscore);
int victoire(int N,int M,int nbr_sym, int pla[][N]);
void demande_case(int N,int M,int nbr_sym, int pla[][N],int * pscore);
int jouer2(int N,int M,int sym,int pla[][N],int *pscore);
int jouer( int *po);
int lire_sauvegarde();
int  menu(int *po );
 






#endif