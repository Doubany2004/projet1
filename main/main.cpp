#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

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
/// fonciton pour afficher le contenu du catalogue pour évité la répétition
/// </summary>
/// <param name="catalogue">le calatogue des articles possible</param>
void afficherCatalogue(vector<string>& codeCatalogue, vector<string>& nomCatalogue, vector<double>& prixCatalogue) {
	for (int i = 0; i < codeCatalogue.size(); i++) {
		cout << codeCatalogue[i] << ": " << nomCatalogue[i] << " - " << prixCatalogue[i] << "$" << endl;
	}
}
/// <summary>
/// fonction servant a ajouté des articles au panier
/// </summary>
/// <param name="panier">matrice contenant le panier</param>
/// <param name="catalogue">matrice contenant le catalogue</param>
void ajouterArticle(vector<string>& codePanier, vector<string>& nomPanier, vector<double>& prixPanier) {
	bool flag = false;
	string choix;

	cout << "\n********************" << endl;
	cout << " AJOUT ARTICLE" << endl;
	cout << "********************" << endl;

	vector<string> codeCatalogue = { "A1","A2","B1","B2","B3","L1","L2","L3" };
	vector<string> nomCatalogue = { "Crayon" ,"Cahier canada","Table pliante","Fauteuil en cuire",
	"Bureau d'etudiant","Laptop Assus","Laptop HP","Laptop Acer"};
	vector<double> prixCatalogue = { 3.99, 1.59,66.99,199.99,118.99,600.89,3.99,3.99 };

	afficherCatalogue(codeCatalogue, nomCatalogue, prixCatalogue);

	cout << "appuyer sur q pour retourner au menu principal" << endl;
	while (true) {
		cout << "Votre choix: ";
		cin >> choix;

		if (choix == "q") {
		 break;
		}

		// Rechercher l'article dans le catalogue
		for (int i = 0; i < codeCatalogue.size(); i++) {
			if (codeCatalogue[i] == choix) {
				codePanier.push_back(codeCatalogue[i]);
				nomPanier.push_back(nomCatalogue[i]);
				prixPanier.push_back(prixCatalogue[i]);
				flag = true;
				break;
			}
		}
		if (flag) {
			cout << "article " << choix << " ajoute" << endl;
		}
		else {
			cout << "code invalide veuillez reessayer" << endl;
		}
	}
}

/// <summary>
/// fonction servant a aficher le contenu du panier
/// </summary>
/// <param name="panier">panier contenant les article ajouté</param>
void afficherPanier(vector<string>& codePanier, vector<string>& nomPanier, vector<double>& prixPanier) {
	cout << "\n********************" << endl;
	cout << " AFFICHER PANIER" << endl;
	cout << "********************" << endl;

	// Verifier si le panier est vide
	if (codePanier.empty()) {
		cout << "Le panier est vide." << endl;
		return;
	}

	for (int i = 0; i < codePanier.size(); i++) {
		cout << codePanier[i] << ": " << nomPanier[i] << " - " << prixPanier[i] << "$" << endl;
	}
}
/// <summary>
/// fonciton servant a supprimer un article du panier
/// </summary>
/// <param name="panier">panier contenant les articles</param>
void supprimerArticle(vector<string>& codePanier, vector<string>& nomPanier, vector<double>& prixPanier) {
	string choix;
	bool flag = false;

	cout << "\n********************" << endl;
	cout << " RETIRER ARTICLE" << endl;
	cout << "********************" << endl;

	if (codePanier.empty()) {
		cout << "Le panier est vide." << endl;
		return;
	}

	// Afficher le contenu du panier
	for (int i = 0; i < codePanier.size(); i++) {
		cout << codePanier[i] << ": " << nomPanier[i] << " - " << prixPanier[i] << "$" << endl;
	}

	cout << "appuyer sur q pour retourner au menu principal" << endl;
	while (true) {

		if (codePanier.empty()) {
			cout << "Le panier est vide." << endl;
			return;
		}
		cout << "Votre choix: ";
		cin >> choix;
		if (choix == "q") {
			break;
		}

		// Rechercher l'article dans le panier 
		// et le supprimer s'il est trouve
		for (int i = 0; i < codePanier.size(); i++) {
			if (codePanier[i] == choix) {
				codePanier.erase(codePanier.begin() + i);
				nomPanier.erase(nomPanier.begin() + i);
				prixPanier.erase(prixPanier.begin() + i);
				//cout << "Article" << choix << "supprime." << endl;
				flag = true;
				break;
				
				
			}
		}
		if (flag) {
			cout << "Article " << choix << " supprime." << endl;
		}
		else {
			cout << "code invalide veuillez reessayer" << endl;
		}
		


	}

}


/// <summary>
/// fonction qui affiche une facture créer a partir du panier
/// </summary>
/// <param name="panier">le panier contenant les articles achetés</param>
/// <param name="employe">le nom de l'employé utilisé lors de l'entrée</param>
void facture(vector<string>& codePanier, vector<string>& nomPanier, vector<double>& prixPanier, string employe) {

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
	if (codePanier.empty()) {
		cout << "Le panier est vide." << endl;
		return;
	}

	for (int i = 0; i < codePanier.size(); i++) {
		cout << "-" << codePanier[i] << ": " << setw(18) << left << nomPanier[i] << prixPanier[i] << "$" << endl;
		sousTotal = sousTotal + prixPanier[i];
	}

	//affichage du rabais (50% du temps)
	if (rabais == 1) {
		cout << "\n       Rabais mystere: " << setprecision(2) << fixed << (sousTotal * 0.25) << "$" << endl;
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
	cout << "Vous avez ete servi par " << employe << endl;
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
void menu(string employe) {
	char choix = 'a';
	vector<string> codePanier = {};
	vector<string> nomPanier = {};
	vector<double> prixPanier = {};

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
		case '1':
			ajouterArticle(codePanier, nomPanier, prixPanier);
			break;
		case '2':
			supprimerArticle(codePanier, nomPanier, prixPanier);
			break;
		case '3':
			afficherPanier(codePanier, nomPanier, prixPanier);
			break;
		case '0':
			facture(codePanier, nomPanier, prixPanier, employe);
			break;
		default:
			cout << "Choix invalide..." << endl;
		}

	} while (choix != '0');
}


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


	//vector<Article> catalogue = 
	//vector<Article> panier;

	menu(nomEmploye);


	return 0;
}
