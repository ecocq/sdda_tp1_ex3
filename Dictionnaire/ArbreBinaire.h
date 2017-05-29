#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ArbreBinaire
{
public:
	ArbreBinaire();
	ArbreBinaire(string filename, string filepath = "../FichierTest/");
	~ArbreBinaire();

	void ajouterMot(string s); // ajouter le mot s dans le dictionnaire.
	void enleverMot(string s); // enlever le mot s du dictionnaire.
	void afficherDict(); // afficher le dictionnaire, selon l'ordre lexicographique.
	bool chercherMot(string s); // si le mot appartient ou non au dictionnaire.

	void ajouterMotsDepuisFichier(string filename, string filepath = "../FichierTest/"); // ajouter une liste de mots contenus dans un fichier
	void supprimerTout(); // supprime tout le contenu du dictionnaire
	

private:
	// classe Noeud
	class Noeud
	{
	public:
		char lettre;
		Noeud* prochaine;
		Noeud* alternative;
		bool finMot;

		Noeud(const char &l, bool _finMot = false, Noeud* _prochaine = NULL, Noeud* _alternative = NULL) : 
			prochaine(_prochaine), lettre(l), alternative(_alternative), finMot(_finMot) {}
		~Noeud() {
			// DEBUG: Pour vérifier que les suppressions sont bien faites
			//cout << "Delete " << lettre << endl;
			delete(alternative);
			delete(prochaine);
		}
	};


	Noeud* racine; //racine de l'arbre

	void afficherDict(string prefixe, Noeud* courrant);
	int enleverSuffixe(Noeud* courrant);
	

};