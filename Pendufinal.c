#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TAILLECHAINE 50 												// Tableau de taille 50

int inittabtiret();
int demandealpha();
int remplacementlettre();
int tentative = 8;
int nbrdelettre;

int perdu();
int gagner();

char tabalpha[] = "abcdefghijklmnopqrstuvwxyz"; 

int prenomjoueur();
char prenom[20]; 														//Le prenom peut contenir 20 caracteres
char c;
char tabtiret[9];

int case_utilise;
int stockage();
char tab_lettre_utilise[255];


int motaleatoire();
int fichier();
char motadevine[TAILLECHAINE];											// Tableau du mot à deviner
int aleatoire;
int nbrdemot = 835;

int taille = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void viderBuffer() {
	char c;
	while (c != '\n') {
		c = getchar();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




int main() {


motaleatoire();
	
fichier();
		
prenomjoueur();

inittabtiret();	


while ((tentative != 0) && (nbrdelettre !=  taille)) {				// Tant que le nombre de tentatives n'est pas egal à 0 et que le nbr de lettre n'est pas égal au nbr de lettre dans le mot

	demandealpha();
	
	int valeur = remplacementlettre();	
	
if (valeur == 1) { 														// Si la lettre rentrée est bonne, alors la valeur passe à 1
	printf("%c: est dans le mot\n",c);									// Par consequent on precise au joueur que la lettre qu'il à rentrée est dans le mot
	printf("Le mot est : %s\n", tabtiret);								// On affiche le tableau avec les tirets
	nbrdelettre = nbrdelettre + 1;										// Si la valeur est egal a 1 alors la lettre est dans le mot donc il a une lettre en plus de trouver										
}

if (valeur == 2) { 														
	printf("%c: est dans le mot\n",c);									
	printf("Le mot est : %s\n", tabtiret);								
	nbrdelettre = nbrdelettre + 2;											
}
	
if (valeur == 3) { 														
	printf("%c: est dans le mot\n",c);									
	printf("Le mot est : %s\n", tabtiret);								
	nbrdelettre = nbrdelettre + 3;											
									
}
if (valeur == 0) {
	printf("%c: n'est pas dans le mot\n",c);							// Si ce n'est pas le cas on precise au joueur que la lettre qu'il à rentrée n'est pas dans le mot
	tentative = tentative - 1;											// Si la lettre n'est pas bonne alors le joueur utilise un tentative. Il a le droit à 8 fautes
	printf("Le mot est : %s\n", tabtiret);								// On affiche le tableau avec les tirets
	printf("Ton nombre de tentative(s) est de %d\n", tentative);		// Previens le joueur du nombre de tentative qu'il lui reste
														
}	
	gagner();
	perdu();
	
	}	
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int fichier() {
	

FILE* fichier = NULL;
    
  char chaine[TAILLECHAINE] = ""; 										// Chaîne vide de taille TAILLE_MAX
    
	int i =0;
	int j = 0;


fichier = fopen("words.txt", "r");										// Le fichier s'ouvre en lecture seule
 
    while (i < nbrdemot) {												// Tant que i < 835
		
        fgets(chaine, TAILLECHAINE, fichier); 							// On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
		
        
    if (i == aleatoire) {												// Si i est egal au random
			
		while (chaine[j] != '\n')  {									// Tant que le j qui se balade dans la chaine ne trouve pas de caractere nul
			taille++;
			
				
				motadevine[j] = chaine[j];								// Le tableau (vide) du mot à deviner devient le mot contenu dans la chaine parcouru par j
				j++;
			}
	
		}
       i++;
    }
    
//printf("%s", motadevine); 											// On affiche la chaîne random

 fclose(fichier);														// Ferme le fichier

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int motaleatoire() {

srand(time(NULL));														// Hasard

aleatoire = (rand() % 835);												// Choisit un nombre parmis le nombre total de mots dans le fichier
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int prenomjoueur() {
	
printf("Bienvenue, comment t'appelles-tu?\n");							//Demande le prenom du joueur
scanf("%s", prenom);													//Le joueur rentre son prenom
viderBuffer();

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 
int inittabtiret() { 													// Tableau tirets
	int i;																	

	for (i = 0; i < taille; i++) {
		tabtiret[i] = '_';	
	}
	tabtiret[taille+1] = '\0';											// Le '\0' est la 5 eme est derniere valeur du tableau
}				

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int demandealpha() { 
	int changementalpha = 0;											// On initialise à 0
	int i;
	
	/*
	printf("Quelle lettre proposes-tu %s?\n",prenom); 					// Demande la lettre au joueur
		c = getchar();
		viderBuffer();
			
	for (i = 0; i < 26; i++) {											// On parcourt le tableau de l'alphabet
		if (c == tabalpha[i]) {											// Si c est egal à une lettre dans tabalpha
			changementalpha = 1;										// Alors le chagement passe à 1
		}
	}
	*/
	while ((changementalpha == 0) || (stockage() == 1)) {				// Tant que le changement est egal à 0 
	
		printf("Quelle lettre proposes-tu %s?\n",prenom); 				// Demande la lettre au joueur
			c = getchar();
			viderBuffer();
			
				
		for (i = 0; i < 26; i++) {										// On parcourt le tableau de l'alphabet
			if (c == tabalpha[i]) {										// Si c est egal à une lettre dans tabalpha
				changementalpha = 1;									// Alors le chagement passe à 1
			}
		}
	}	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int remplacementlettre() {												// Fonction qui remplace les tirets par la bonne lettre si le joueur la propose
	int i;																
	int changement = 0;													// Si changement = 0, alors il n'y a pas eu de changement de lettre dans un tiret
										
	for (i = 0; i < taille; i++) {	
		if (c == motadevine[i]) {
			tabtiret[i] = c;
			changement++;												// Le changement = 1, donc une lettre à remplacer un tiret
		}
	}
	return changement;													// Renvoie la valeur à la ligne 30. Le return sert à retourner la valeur dans int valeur. Il ne s'utilise que dans une fonction
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int stockage() {
	int i;

	int lettre_deja_utilise = 0;										// Si la lettre n'est pas utilisee alors elle est egal a 0. Au debut du jeu toutes les lettres sont egal à 0

for (i = 0; i < case_utilise; i++) {									// i se balade dans les cases utilisees. Au depart on part a 0, si la case 0 est utilisee par une lettre alors on augmente de 1
	if( c == tab_lettre_utilise[i]) {									// Si la lettre rentree est egal à une lettre deja rentree 
		lettre_deja_utilise = 1;										// Alors la valeur de cette lettre passe a 1
			}
}
	if( lettre_deja_utilise == 1 ) {										// Si la lettre utilisee est egal a 1
		
		printf("Les lettres déjà utilisées sont :");
		
for (i = 0; i < case_utilise; i++) {
		printf("%c,  ",tab_lettre_utilise[i]);
}
printf("\n");
	}
	else {																	// Sinon
		tab_lettre_utilise[case_utilise] = c;								// Le caractere va rentrer dans le tableau 
		case_utilise = case_utilise + 1;
}
return lettre_deja_utilise;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int perdu() {															// Fonction qui affiche le pendu et/ou "perdu" quand le joueur perd ses tentatives

if (tentative == 7) {													// Tentative est egal à 7
		printf("   _______	   \n");
		printf("  |       |    \n");
		printf("  |			   \n");
		printf("  |			   \n");
		printf("  |		   	   \n");
		printf("  |			   \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
	}
	
if (tentative == 6) {													// Tentative est egal à 6
		printf("   _______	   \n");
		printf("  |       |	   \n");
		printf("  |       o    \n");
		printf("  |			   \n");
		printf("  |		   	   \n");
		printf("  |			   \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
	}

if (tentative == 5) {													// Tentative est egal à 5
		printf("   _______	   \n");
		printf("  |       |	   \n");
		printf("  |       o    \n");
		printf("  |       |    \n");
		printf("  |		   	   \n");
		printf("  |			   \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
	}

if (tentative == 4) {													// Tentative est egal à 4
		printf("   _______	   \n");
		printf("  |       |	   \n");
		printf("  |       o    \n");
		printf("  |      /|    \n");
		printf("  |		   	   \n");
		printf("  |			   \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
	}

if (tentative == 3) {													// Tentative est egal à 3
		printf("   _______	   \n");
		printf("  |       |	   \n");
		printf("  |       o    \n");
		printf("  |      /|\\  \n");
		printf("  |		   	   \n");
		printf("  |			   \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
	}

if (tentative == 2) {													// Tentative est egal à 2
	
		printf("   _______	   \n");
		printf("  |       |	   \n");
		printf("  |       o    \n");
		printf("  |      /|\\  \n");
		printf("  |       |    \n");
		printf("  |			   \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
	}

if (tentative == 1) {													// Tentative est egal à 1
	
		printf("   _______	   \n");
		printf("  |       |	   \n");
		printf("  |       o    \n");
		printf("  |      /|\\  \n");
		printf("  |       |    \n");
		printf("  |      /     \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
	}

if (tentative == 0) {													// Tentative est egal à 0
		
		printf("   _______	   \n");
		printf("  |       |	   \n");
		printf("  |       o    \n");
		printf("  |      /|\\  \n");
		printf("  |       |    \n");
		printf("  |      / \\  \n");
		printf(" _|_		   \n");
		printf("|   |_________ \n");
		printf("|             |\n");
		printf("|_____________|\n");
		printf("\n");
		printf("DEFAITE\n");
		printf("Le mot à deviner était: %s\n", motadevine);
		
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int gagner() {															// Fonction qui affiche "gagner" quand le joueur a trouvé le mot sans utiliser ses 8 tentatives


if (nbrdelettre == taille) {											// Si le nombre de lettres trouvees est egal a 5(nbr de lettre dans le mot) alors gagner 
		printf("\n");
		printf("VICTOIRE\n");
		}
}
