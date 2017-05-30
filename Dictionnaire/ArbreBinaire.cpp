#include "ArbreBinaire.h"

class Noeud;

ArbreBinaire::ArbreBinaire()
{
	racine = new Noeud('#');
}

ArbreBinaire::ArbreBinaire(string filename, string filepath)
{
	// On veut ici prendre un fichier en parametre et cr�er l'arbre avec la liste de mots contenus
	racine = new Noeud('#');
	ajouterMotsDepuisFichier(filename, filepath);
}

ArbreBinaire::~ArbreBinaire()
{
	delete(racine);
}

void ArbreBinaire::ajouterMotsDepuisFichier(string filename, string filepath)
{
	ifstream fichier;
	fichier.open(filepath+filename);
	string mot;
	mot.clear();
	if (!fichier.is_open()) {
		cout << "Le fichier n'a pas pu etre ouvert. Verifiez son existence et sa disponibilite.\n";
		return;
	}

	while (fichier >> mot)
	{
		ajouterMot(mot);
	}
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
			// Si on arrive � la fin du mot demand�
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

	// Si on a trouv� le mot complet
	if (i == s.size() && temp->finMot) {
		// S'il y a un autre mot avec la m�me racine, on ne supprime rien
		if (temp->prochaine) {
			temp->finMot = false;
		}
		// S'il y a eu des alternatives, il faut relier correctement
		else if (derniereLettreAlternative != NULL) {
			// Premiere lettre � retirer
			if (dernierParentAlternative->prochaine == derniereLettreAlternative) {
				int nbFinMots = enleverSuffixe(dernierParentAlternative->prochaine);
				// Si on n'a pas trouv� d'autres mots alors change les liaisons
				if (nbFinMots < 2) {
					temp = dernierParentAlternative->prochaine;
					dernierParentAlternative->prochaine = derniereLettreAlternative->alternative;
					temp->alternative = NULL;
					delete(temp);
				}
			}
			else {
				temp = dernierParentAlternative->prochaine;
				// Acces � l'alternative juste avant la bonne lettre
				while (temp->alternative && temp->alternative != derniereLettreAlternative) {
					temp = temp->alternative;
				}
				if (temp->alternative) {
					int nbFinMots = enleverSuffixe(temp->alternative);
					// Si on n'a pas trouv� d'autres mots alors change les liaisons
					if (nbFinMots < 2) {
						Noeud* supp = temp->alternative;
						temp->alternative = temp->alternative->alternative;
						supp->alternative = NULL;
						delete(supp);
					}
				}
			}
		}
		else {
			if (dernierParentAlternative->prochaine->lettre == derniereLettre) {
				cout << derniereLettre << endl;
				temp = dernierParentAlternative->prochaine->alternative;
				int nbFinMots = enleverSuffixe(dernierParentAlternative->prochaine);
				// Si on n'a pas trouv� d'autres mots alors change les liaisons
				if (nbFinMots < 2)
					dernierParentAlternative->prochaine = temp;
			}
			else {
				int nbFinMots = enleverSuffixe(dernierParentAlternative->prochaine->alternative);
				if (nbFinMots < 2) {
					delete(dernierParentAlternative->prochaine->alternative);
					dernierParentAlternative->prochaine->alternative = NULL;
				}
			}
		}
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
	cout << "=== Liste des mots ===" << endl;
	if(racine->prochaine)
		afficherDict("", racine->prochaine);
}


void ArbreBinaire::afficherDict(string prefixe, Noeud* courrant)
{
	// DEBUG: Pour voir le parcours de l'arbre, il est possible de d�commenter la ligne
	//cout << "(" << prefixe << ")" << endl;

	if (courrant->finMot)
		cout << prefixe + courrant->lettre << endl;

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
		else if(temp->alternative && temp->lettre < toupper(s[i])){
			temp = temp->alternative;
		}
		// S'il n'y a plus d'alternative, ou qu'on a d�passer la lettre sans la trouver
		else {
			return false;
		}
	}

	return false;
}

void ArbreBinaire::supprimerTout()
{
	// La suppression d'un noeud est r�cursive sur les deux fils
	delete(racine->prochaine);
	racine->prochaine = NULL;
	delete(racine->alternative);
	racine->alternative = NULL;
}
