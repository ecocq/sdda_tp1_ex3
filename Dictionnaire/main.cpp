#include <stdlib.h>  
#include <iostream>
#include "ArbreBinaire.h"


void afficherTitre() {
	std::cout << "------------------------------------------------------\n"
		<< "---            EXERCICE 3 : DICTIONNAIRE           ---\n"
		<< "------------------------------------------------------\n"
		<< std::endl;
};


int main(void) {
	afficherTitre();

	//MENU AVEC afficher, existe?, ajouter, supprimer, et "démo" en quelque sorte :) (supprimer tout l'arbre + ajouter dico from file)

	ArbreBinaire dictionnaire = ArbreBinaire();
	dictionnaire.ajouterMot("bas");
	dictionnaire.ajouterMot("abas");
	dictionnaire.ajouterMot("arbuste");
	dictionnaire.ajouterMot("lit");
	dictionnaire.ajouterMot("las");
	dictionnaire.ajouterMot("arbre");
	dictionnaire.ajouterMot("lasse");
	dictionnaire.ajouterMot("litterie");
	dictionnaire.afficherDict();

	/*/
	cout << "Mot arbre existe ? " << dictionnaire.chercherMot("arbre") << endl;
	cout << "Mot arb existe ? " << dictionnaire.chercherMot("arb") << endl;
	cout << "Mot arbree existe ? " << dictionnaire.chercherMot("arbree") << endl;
	cout << "Mot lasse existe ? " << dictionnaire.chercherMot("lasse") << endl;
	*/

	cout << endl;
	dictionnaire.enleverMot("bas");
	dictionnaire.enleverMot("litterie");
	dictionnaire.enleverMot("abas");
	dictionnaire.enleverMot("arbre");
	dictionnaire.enleverMot("arbuste");
	dictionnaire.afficherDict();


	system("PAUSE");
	return 0;
}