#include "ArbreBinaire.h"

class Noeud;

ArbreBinaire::ArbreBinaire()
{
	racine = new Noeud('#');
}

ArbreBinaire::ArbreBinaire(string filepath)
{
	// On veut ici prendre un fichier en parametre et cr�er l'arbre avec la liste de mots contenus
}


ArbreBinaire::~ArbreBinaire()
{
	delete(racine);
}

void ArbreBinaire::ajouterMot(string s)
{

	Noeud* temp = racine;
	Noeud* precedent;
	char c;


	for (size_t i = 0; i < s.size() ; ++i)
	{
		c = toupper(s[i]);

		// S'il n'y a pas de prochaine, on ajoute simplement lettre par lettre
		if (!temp->prochaine) {
			temp->prochaine = new Noeud(c);
			temp = temp->prochaine;
		}
		// Sinon, on cherche parmi les alternatives la bonne lettre
		else{
			precedent = temp;
			temp = temp->prochaine;

			// Si c doit �tre avant le premier �l�ment
			if (c < temp->lettre) {
				Noeud* nouveau = new Noeud(c);
				nouveau->alternative = temp;
				precedent->prochaine = nouveau;
				temp = nouveau;
			}
			else {
				// Tant qu'il y a des alternatives et qu'on ne d�passe pas la lettre
				while (temp->alternative && c >= temp->alternative->lettre) {
					temp = temp->alternative;
				}
				// On arrive � la fin de la cha�ne
				if (!temp->alternative &&  c > temp->lettre) {
					temp->alternative = new Noeud(c);
					temp = temp->alternative;
				}
				// La cha�ne ne contient pas cette alternative : il faut l'ins�rer
				else if (c != temp->lettre) {
					Noeud* nouveau = new Noeud(c);
					nouveau->alternative = temp->alternative;
					temp->alternative = nouveau;
					temp = temp->alternative;
				}
				// Sinon, on est arriv� sur la bonne lettre
			}
		}
	}
	temp->finMot = true;
}

void ArbreBinaire::enleverMot(string s)
{
	Noeud* temp = racine->prochaine;
	Noeud* dernierAvecAlternative = NULL;

	size_t i = 0;

	while (temp) {
		if (temp->lettre == toupper(s[i])) {
			i++;
			if (temp->alternative)
				dernierAvecAlternative = temp;
			// Si on arrive � la fin du mot demand�
			if (i == s.size()) {
				break;
			}
			temp = temp->prochaine;
		}
		else if (temp->alternative) {
			temp = temp->alternative;
		}
	}

	// Si on a trouv� le mot complet
	if (temp) {
		// S'il y a un autre mot avec la m�me racine, on ne supprime rien
		if (temp->prochaine) {
			temp->finMot = false;
		}
		else if(dernierAvecAlternative){
			dernierAvecAlternative = dernierAvecAlternative->alternative;
		}
		//TODO delete noeuds
	}
	else {
		cout << "Le mot " << s << " n'appartenait pas au dictionnaire." << endl;
	}
	
}

bool ArbreBinaire::enleverLettre(Noeud* origine)
{
	return false;
}


void ArbreBinaire::afficherDict()
{
	if(racine->prochaine)
		afficherDict("", racine->prochaine);
}

void ArbreBinaire::afficherDict(string prefixe, Noeud* courrant)
{
	cout << prefixe << endl;

	if (courrant->finMot)
		cout << "===> " << prefixe + courrant->lettre << endl;

	if(courrant->prochaine)
		afficherDict(prefixe + courrant->lettre, courrant->prochaine);

	if (courrant->alternative)
		afficherDict(prefixe, courrant->alternative);
	
}


bool ArbreBinaire::chercherMot(string s)
{
	Noeud* temp = racine->prochaine;
	size_t i = 0;

	while (temp) {
		if (temp->lettre == toupper(s[i])) {
			i++;
			// Si on arrive � la fin du mot recherch�
			if (i == s.size()) {
				if (temp->finMot)
					return true;
				else
					return false;
			}
			temp = temp->prochaine;
		}
		else if(temp->alternative){
			temp = temp->alternative;
		}
		// S'il n'y a plus d'alternative et qu'on n'a pas trouv� la lettre
		else {
			return false;
		}
	}

	return false;
}

/*
Noeud* ArbreBinaire::chercherLettre(char lettre, Noeud* origine) 
{
	Noeud* temp = origine;

	while (temp) {
		if (temp->lettre == toupper(lettre)) {
			return temp;
		}
		else if (temp->alternative) {
			temp = temp->alternative;
		}
		// S'il n'y a plus d'alternative et qu'on n'a pas trouv� la lettre
		else {
			return NULL;
		}
	}
	return NULL;
}*/
