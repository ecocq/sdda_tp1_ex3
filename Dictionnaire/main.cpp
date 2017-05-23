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

	ArbreBinaire dictionnaire = ArbreBinaire();
	dictionnaire.ajouterMot("bas");
	dictionnaire.ajouterMot("abas");
	dictionnaire.ajouterMot("arbuste");
	dictionnaire.ajouterMot("lit");
	dictionnaire.ajouterMot("las");
	dictionnaire.ajouterMot("arbre");
	dictionnaire.ajouterMot("lasse");
	dictionnaire.afficherDict();

	cout << "Mot arbre existe ? " << dictionnaire.chercherMot("arbre") << endl;
	cout << "Mot arb existe ? " << dictionnaire.chercherMot("arb") << endl;
	cout << "Mot arbree existe ? " << dictionnaire.chercherMot("arbree") << endl;
	cout << "Mot lasse existe ? " << dictionnaire.chercherMot("lasse") << endl;

	dictionnaire.enleverMot("arbre");

	dictionnaire.afficherDict();

	system("PAUSE");
	return 0;
}