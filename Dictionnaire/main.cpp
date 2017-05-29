#include <stdlib.h>  
#include <iostream>
#include <sys/types.h>
#include "ArbreBinaire.h"


void afficherTitre() {
	std::cout << "------------------------------------------------------\n"
		<< "---            EXERCICE 3 : DICTIONNAIRE           ---\n"
		<< "------------------------------------------------------\n"
		<< endl;
};

void afficherMenu() {
	std::cout << endl
		<< "### MENU ###\n"
		<< " 1 - Ajouter un mot\n"
		<< " 2 - Enlever un mot\n"
		<< " 3 - Chercher un mot\n"
		<< " 4 - Afficher le dictionnaire\n"
		<< " 5 - Ajouter des mots a partir d'un fichier\n"
		<< " 6 - Supprimer tout le dictionnaire\n"
		<< " 7 - Demonstration\n"
		<< " 0 - Quitter\n\n"
		<< "-> Choix : ";
};

void lancerDemonstration() {
	ArbreBinaire dicoDemo = ArbreBinaire();
	std::cout << endl << ">>> DEMONSTRATION <<<\n"
		<< "\n--> Etape 1 : ajouter des mots\n"
		<< "-> Ajout du mot 'lasse'\n";
	dicoDemo.ajouterMot("lasse");
	dicoDemo.afficherDict();
	system("PAUSE");
	std::cout << "\n-> Ajout des mots 'bas', 'arbre' et 'lit'\n";
	dicoDemo.ajouterMot("bas");
	dicoDemo.ajouterMot("arbre");
	dicoDemo.ajouterMot("lit");
	dicoDemo.afficherDict();
	system("PAUSE");
	std::cout << "\n-> Ajout des mots 'abas', 'arbuste' et 'las'\n";
	dicoDemo.ajouterMot("abas");
	dicoDemo.ajouterMot("arbuste");
	dicoDemo.ajouterMot("las");
	dicoDemo.afficherDict();
	system("PAUSE");

	std::cout << "\n-> Ajout du mot 'bas' deja present\n";
	dicoDemo.ajouterMot("bas");
	dicoDemo.afficherDict();
	std::cout << "// Pas de doublon\n";
	system("PAUSE");

	std::cout << "\n--> Etape 2 : chercher des mots\n"
		<< "-> Chercher le mot 'lasse'\n";
	cout << "Le mot " << ((dicoDemo.chercherMot("lasse")) ? "est present" : "n'est pas present") << endl;
	system("PAUSE");
	cout << "\n-> Chercher le mot 'lAsSe' // On ne prend pas en compte la casse\n";
	cout << "Le mot " << ((dicoDemo.chercherMot("lAsSe")) ? "est present" : "n'est pas present") << endl;
	system("PAUSE");
	cout << "\n-> Chercher le mot 'las'\n";
	cout << "Le mot " << ((dicoDemo.chercherMot("las")) ? "est present" : "n'est pas present") << endl;
	system("PAUSE");
	cout << "\n-> Chercher le mot 'arbus'\n";
	cout << "Le mot " << ((dicoDemo.chercherMot("arbus")) ? "est present" : "n'est pas present") << endl;
	system("PAUSE");
	cout << "\n-> Chercher le mot 'arbree'\n";
	cout << "Le mot " << ((dicoDemo.chercherMot("arbree")) ? "est present" : "n'est pas present") << endl;
	system("PAUSE");

	std::cout << "\n--> Etape 3 : enlever des mots\n"
		<< "-> Enlever le mot 'lasse'\n";
	dicoDemo.enleverMot("lasse");
	dicoDemo.afficherDict();
	system("PAUSE");

	std::cout << "\n-> Enlever le mot 'arbre'\n";
	dicoDemo.enleverMot("arbre");
	dicoDemo.afficherDict();
	system("PAUSE");

	std::cout << "\n-> Enlever le mot 'bas'\n";
	dicoDemo.enleverMot("bas");
	dicoDemo.afficherDict();
	system("PAUSE");

	std::cout << "\n-> Remettre le mot 'bas' et enlever le mot 'abas'\n";
	dicoDemo.ajouterMot("bas");
	dicoDemo.enleverMot("abas");
	dicoDemo.afficherDict();
	system("PAUSE");

	std::cout << "\n-> Enlever le mot 'abas' non present\n";
	dicoDemo.enleverMot("abas");
	dicoDemo.afficherDict();
	system("PAUSE");

	std::cout << "\n--> Etape 4 : lecture des fichiers\n"
		<< "-> Supprimer tout le dictionnaire'\n";
	dicoDemo.supprimerTout();
	dicoDemo.afficherDict();
	system("PAUSE");

	std::cout << "\n-> Ajouter les mots listes dans le fichier g.dico\n";
	dicoDemo.ajouterMotsDepuisFichier("g.dico");
	dicoDemo.afficherDict();
	system("PAUSE");

};


int main(void) {
	afficherTitre();

	//MENU AVEC afficher, existe?, ajouter, supprimer, et "démo" en quelque sorte :) (supprimer tout l'arbre + ajouter dico from file)

	char choix;
	string mot;
	
	ArbreBinaire dictionnaire = ArbreBinaire();

	do
	{
		afficherMenu();

		cin >> choix;

		switch (choix)
		{
			mot.clear();
			case '1':
				cout << "-> Entrez le mot a ajouter : ";
				cin >> mot;
				if (!mot.empty())
					dictionnaire.ajouterMot(mot);
				break;
			case '2':
				cout << "-> Entrez le mot a enlever : ";
				cin >> mot;
				if (!mot.empty())
					dictionnaire.enleverMot(mot);
				break;
			case '3':
				cout << "-> Entrez le mot a chercher : ";
				cin >> mot;
				if (!mot.empty())
					cout << "Le mot " << mot << (dictionnaire.chercherMot(mot) ? " est present" : " n'est pas present") << endl;
				break;
			case '4':
				dictionnaire.afficherDict();
				break;
			case '5':
				cout << "\n->Entrez le nom du fichier provenant du dossier 'FichierTest' (exemple : g.dico) : ";
				cin >> mot;
				dictionnaire.ajouterMotsDepuisFichier(mot);
				break;
			case '6':
				dictionnaire.supprimerTout();
				break;
			case '7':
				lancerDemonstration();
				break;
			case '0':
				cout << "Fin du programme\n";
				break;
			default:
				cout << "Choix non valide. Veuillez réessayer.\n";
				break;
		}

	} while (choix != '0');

	system("PAUSE");
	return 0;
}