#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

/// <summary>
/// 
/// </summary>
struct Article {
	string code; // Code unique de l'article
	string nom; // Nom de l'article
	double prix;  // Prix de l'article
};

/// <summary>
/// fonction qui permet d'identifier l'utilisateur avec son numer d'identifiant
/// </summary>
/// <param name="code">le numero d'identifiant</param>
/// <param name="nom">nom d'utilisateur</param>
/// <returns>retoure vrai ou faux</returns>
bool estEmployeValide(const string& code, string& nom) {
	if (code == "001") nom = "Andrew";
	else if (code == "002") nom = "Nabil";
	else if (code == "003") nom = "Marc";
	else if (code == "004") nom = "Jean-Gabriel";
	else if (code == "005") nom = "Caroline";
	else return false;
	return true; // retourne vrai si l'employe est valide
}

/// <summary>
/// fonction qui sert a créer la matrice contenant le catalogue
/// </summary>
/// <returns> retourne la matrice créer </returns>
vector<Article> creerCatalogue() {
	return {
		{"A1", "Crayons", 3.99},
		{"A2", "Cahier Canada", 1.59},
		{"B1", "Table pliante", 66.99},
		{"B2", "Fauteuil en cuir", 199.99},
		{"B3", "Bureau d'etudiant", 118.99},
		{"L1", "Laptop ASUS", 600.89},
		{"L2", "Laptop HP", 700.89},
		{"L3", "Laptop Acer", 250.99}
	};
}

/// <summary>
/// fonciton pour afficher le contenu du catalogue pour évité la répétition
/// </summary>
/// <param name="catalogue">le calatogue des articles possible</param>
void afficherCatalogue(const vector<Article>& catalogue) {
	for (const Article& a : catalogue) {
		cout << a.code << ": " << a.nom << " - " << a.prix << "$" << endl;
	}
}
/// <summary>
/// fonction servant a ajouté des articles au panier
/// </summary>
/// <param name="panier">matrice contenant le panier</param>
/// <param name="catalogue">matrice contenant le catalogue</param>
void ajouterArticle(vector<Article>& panier, const vector<Article>& catalogue) {
	cout << "\n********************" << endl;
	cout << " AJOUT ARTICLE" << endl;
	cout << "********************" << endl;

	afficherCatalogue(catalogue);

	string choix;
	cout << "Votre choix: ";
	cin >> choix;

	// Rechercher l'article dans le catalogue
	for (const Article& a : catalogue) {
		if (a.code == choix) {
			panier.push_back(a);
			cout << "Article ajoute!" << endl;
			return;
		}
	}

	cout << "Choix invalide..." << endl;
}

/// <summary>
/// fonction servant a aficher le contenu du panier
/// </summary>
/// <param name="panier">panier contenant les article ajouté</param>
void afficherPanier(const vector<Article>& panier) {
	cout << "\********************" << endl;
	cout << " AFFICHER PANIER" << endl;
	cout << "********************" << endl;

	// Verifier si le panier est vide
	if (panier.empty()) {
		cout << "Le panier est vide." << endl;
		return;
	}

	for (const Article& a : panier) {
		cout << a.code << ": " << a.nom << " - " << a.prix << "$" << endl;
	}
}
/// <summary>
/// fonciton servant a supprimer un article du panier
/// </summary>
/// <param name="panier">panier contenant les articles</param>
void supprimerArticle(vector<Article>& panier) {
	cout << "\********************" << endl;
	cout << " RETIRER ARTICLE" << endl;
	cout << "********************" << endl;

	if (panier.empty()) {
		cout << "Le panier est vide." << endl;
		return;
	}

	// Afficher le contenu du panier
	for (const Article& a : panier) {
		cout << a.code << ": " << a.nom << " - " << a.prix << "$" << endl;
	}

	string choix;
	cout << "Votre choix: ";
	cin >> choix;


	// Rechercher l'article dans le panier 
	// et le supprimer s'il est trouve
	for (int i = 0; i < panier.size(); i++) {
		if (panier[i].code == choix) {
			panier.erase(panier.begin() + i);
			cout << "Article supprime." << endl;
			return;
		}
	}

	cout << "Choix invalide..." << endl;
}


/// <summary>
/// fonction qui affiche une facture créer a partir du panier
/// </summary>
/// <param name="panier">le panier contenant les articles achetés</param>
/// <param name="employe">le nom de l'employé utilisé lors de l'entrée</param>
void facture(vector<Article>& panier, string employe) {

	srand(time(0));
	time_t tempsBrut = time(0);
	tm* date = localtime(&tempsBrut);

	int rabais = rand() % 2; //"rabais" est 0 ou 1 ayant 50% de chance chacun
	double sousTotal = 0;
	double total = 0;
	double tps = 0;
	double tvq = 0;

	//affichage de la facture
	cout << "\n***************************" << endl;
	cout << "       ** FACTURE **" << endl;
	cout << "***************************\n" << endl;
	if (panier.empty()) {
		cout << "Le panier est vide." << endl;
		return;
	}

	for (const Article& a : panier) {
		cout << "-" << a.code << ": " << setw(18) << left << a.nom << a.prix << "$" << endl;
		sousTotal = sousTotal + a.prix;
	}

	//affichage du rabais (50% du temps)
	if (rabais == 1) {
		cout << "\n      Rabais mystere: " << setprecision(2) << fixed << (sousTotal * 0.25) << "$" << endl;
		sousTotal = sousTotal * 0.75;
	}

	cout << "---------------------------" << endl;
	cout << "    Sous-total:    " << setprecision(2) << fixed << sousTotal << "$" << endl;
	tps = sousTotal * 0.05;
	tvq = sousTotal * 0.09975;
	cout << "           TPS:    " << setprecision(2) << fixed << tps << "$" << endl;
	cout << "           TVQ:    " << setprecision(2) << fixed << tvq << "$" << endl;
	total = sousTotal + tps + tvq;
	cout << "         Total:    " << setprecision(2) << fixed << total << "$" << endl;

	cout << "***************************" << endl;
	cout << "Vous avez ete servi par" << employe << endl;
	cout << "Date: " << (1900 + date->tm_year) << "-"
		<< right << setw(2) << setfill('0') << (1 + date->tm_mon) << "-"
		<< setw(2) << setfill('0') << date->tm_mday << endl;
	cout << "Heure: " << date->tm_hour << ":"
		<< setw(2) << setfill('0') << date->tm_min << ":"
		<< setw(2) << setfill('0') << date->tm_sec << endl;
	cout << "***************************" << endl;
}

/// <summary>
/// fonction afichant un menu principale pour naviguer les autres options
/// </summary>
/// <param name="panier">le panier contenant les articles ajouté</param>
/// <param name="catalogue">le catalogue contenant les articles possible</param>
/// <param name="employe">le nom d'employé connus depuis le main</param>
void menu(vector<Article>& panier, const vector<Article>& catalogue, string employe) {
	int choix;
	do {
		cout << "\n********************" << endl;
		cout << " MENU PRINCIPAL" << endl;
		cout << "********************" << endl;
		cout << "1. Ajouter un article" << endl;
		cout << "2. Supprimer un article" << endl;
		cout << "3. Afficher le panier" << endl;
		cout << "0. Payer" << endl;
		cout << "Votre choix: ";
		cin >> choix;

		// Traiter le choix de l'utilisateur avec un switch
		switch (choix) {
		case 1:
			ajouterArticle(panier, catalogue);
			break;
		case 2:
			supprimerArticle(panier);
			break;
		case 3:
			afficherPanier(panier);
			break;
		case 0:
			//cout << "Passage a la facture..." << endl;
			facture(panier, employe);
			break;
		default:
			cout << "Choix invalide..." << endl;
		}

	} while (choix != 0);
}

/// <summary>
/// identifie l'utilisateur puis appele la fonction menu
/// </summary>
/// <returns></returns>
int main() {
	string codeEmploye, nomEmploye;


	// Boucle jusqu'a ce qu'un employe valide soit entre
	do {
		cout << "Veuillez vous identifier: ";
		cin >> codeEmploye;
		if (!estEmployeValide(codeEmploye, nomEmploye)) {
			cout << "ERREUR: Numero d'employe invalide" << endl;
		}
	} while (!estEmployeValide(codeEmploye, nomEmploye));

	cout << "Bonjour, " << nomEmploye << endl;

	// Creer le catalogue et le panier avec des vecteurs
	vector<Article> catalogue = creerCatalogue();

	//vector<Article> catalogue = 
	vector<Article> panier;

	menu(panier, catalogue, nomEmploye);


	return 0;
}
