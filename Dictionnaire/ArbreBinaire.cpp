#include "ArbreBinaire.h"

class Noeud;

ArbreBinaire::ArbreBinaire()
{
	racine = new Noeud('#');
}

ArbreBinaire::ArbreBinaire(string filepath)
{
	// On veut ici prendre un fichier en parametre et créer l'arbre avec la liste de mots contenus
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

			// Si c doit être avant le premier élément
			if (c < temp->lettre) {
				Noeud* nouveau = new Noeud(c);
				nouveau->alternative = temp;
				precedent->prochaine = nouveau;
				temp = nouveau;
			}
			else {
				// Tant qu'il y a des alternatives et qu'on ne dépasse pas la lettre
				while (temp->alternative && c >= temp->alternative->lettre) {
					temp = temp->alternative;
				}
				// On arrive à la fin de la chaîne
				if (!temp->alternative &&  c > temp->lettre) {
					temp->alternative = new Noeud(c);
					temp = temp->alternative;
				}
				// La chaîne ne contient pas cette alternative : il faut l'insérer
				else if (c != temp->lettre) {
					Noeud* nouveau = new Noeud(c);
					nouveau->alternative = temp->alternative;
					temp->alternative = nouveau;
					temp = temp->alternative;
				}
				// Sinon, on est arrivé sur la bonne lettre
			}
		}
	}
	temp->finMot = true;
}


void ArbreBinaire::enleverMot(string s)
{
	Noeud* parent = racine;
	Noeud* temp = racine->prochaine;
	Noeud* dernierParentAlternative = NULL;
	Noeud* derniereLettreAlternative = NULL;
	char derniereLettre = racine->lettre;

	size_t i = 0;

	while (temp) {
		if (dernierParentAlternative != parent && temp->alternative) {
			dernierParentAlternative = parent;
			derniereLettre = NULL;
			derniereLettreAlternative = NULL;
		}
		if (temp->lettre == toupper(s[i])) {
			i++;
			if (temp->alternative) {
				derniereLettreAlternative = temp;
				derniereLettre = temp->lettre;
			}
			// Si on arrive à la fin du mot demandé
			if (i == s.size()) {
				break;
			}
			parent = temp;
			temp = temp->prochaine;
		}
		else {
			temp = temp->alternative;
		}
	}

	// Si on a trouvé le mot complet
	if (i == s.size() && temp->finMot) {
		// S'il y a un autre mot avec la même racine, on ne supprime rien
		if (temp->prochaine) {
			temp->finMot = false;
		}
		// S'il y a eu des alternatives, il faut relier correctement
		else if (derniereLettreAlternative != NULL) {
			// Premiere lettre à retirer
			if (dernierParentAlternative->prochaine == derniereLettreAlternative) {
				int nbFinMots = enleverSuffixe(dernierParentAlternative->prochaine);
				// Si on n'a pas trouvé d'autres mots alors change les liaisons
				if (nbFinMots < 2) {
					temp = dernierParentAlternative->prochaine;
					dernierParentAlternative->prochaine = derniereLettreAlternative->alternative;
					cout << "Cas 1" << endl;
				}
			}
			else {
				temp = dernierParentAlternative->prochaine;
				// Acces à l'alternative juste avant la bonne lettre
				while (temp->alternative && temp->alternative != derniereLettreAlternative) {
					temp = temp->alternative;
				}
				if (temp->alternative) {
					int nbFinMots = enleverSuffixe(temp->alternative);
					// Si on n'a pas trouvé d'autres mots alors change les liaisons
					if (nbFinMots < 2) {
						temp->alternative = temp->alternative->alternative;
						cout << "Cas 2" << endl;
					}
				}
			}
		}
		else {
			/* TODO Cas du IF surement a supprimer / inutile !! */
			if (dernierParentAlternative->prochaine->lettre == derniereLettre) {
				cout << derniereLettre << endl;
				temp = dernierParentAlternative->prochaine->alternative;
				int nbFinMots = enleverSuffixe(dernierParentAlternative->prochaine);
				// Si on n'a pas trouvé d'autres mots alors change les liaisons
				if (nbFinMots < 2)
					dernierParentAlternative->prochaine = temp;
				cout << "Cas 3" << endl;
			}
			else {
				int nbFinMots = enleverSuffixe(dernierParentAlternative->prochaine->alternative);
				cout << "Cas 4" << endl;
			}
		}
		//TODO delete noeuds

	}
	else {
		cout << "Le mot " << s << " n'appartenait pas au dictionnaire." << endl;
	}
}

int ArbreBinaire::enleverSuffixe(Noeud * courrant)
{
	if (!courrant)
		return 0;

	int cptFinMot = (courrant->finMot) ? 1 : 0;
	if (courrant->prochaine) {
		cptFinMot += enleverSuffixe(courrant->prochaine);
		if (cptFinMot <= 2) {
			delete(courrant->prochaine);
			courrant->prochaine = NULL;
			if(cptFinMot == 2)
				return 100;
		}
	}

	return cptFinMot;
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
		cout << "=> " << prefixe + courrant->lettre << endl;

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
			// Si on arrive à la fin du mot recherché
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
		// S'il n'y a plus d'alternative et qu'on n'a pas trouvé la lettre
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
		// S'il n'y a plus d'alternative et qu'on n'a pas trouvé la lettre
		else {
			return NULL;
		}
	}
	return NULL;
}*/
