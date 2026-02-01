#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure pour representer un article
struct Article {
	string code; // Code unique de l'article
	string nom; // Nom de l'article
	double prix;  // Prix de l'article
};

// Fonction pour valider l'employe
// met le nom de l'employe dans la variable nom 

bool estEmployeValide(const string& code, string& nom) {
    if (code == "001") nom = "Andrew";
    else if (code == "002") nom = "Nabil";
    else if (code == "003") nom = "Marc";
    else if (code == "004") nom = "Jean-Gabriel";
    else if (code == "005") nom = "Caroline";
    else return false;
	return true; // retourne vrai si l'employe est valide

}

// Fonction pour creer le catalogue d'articles

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

// afficher le catalogue d'articles
// chaque article sur une ligne avec son code, nom et prix
void afficherCatalogue(const vector<Article>& catalogue) {
    for (const Article& a : catalogue) {
        cout << a.code << ": " << a.nom << " - " << a.prix << "$" << endl;
    }
}

void ajouterArticle(vector<Article>& panier, const vector<Article>& catalogue) {
    cout << "********************" << endl;
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

// afficher le contenu du panier
void afficherPanier(const vector<Article>& panier) {
    cout << "********************" << endl;
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
// supprimer un article du panier
// 
void supprimerArticle(vector<Article>& panier) {
    cout << "********************" << endl;
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

// Fonction pour afficher le menu principal

void menu(vector<Article>& panier, const vector<Article>& catalogue) {
    int choix;
    do {
        cout << "********************" << endl;
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
            cout << "Passage a la facture..." << endl;
            break;
        default:
            cout << "Choix invalide..." << endl;
        }

    } while (choix != 0);
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

	// Creer le catalogue et le panier avec des vecteurs
    vector<Article> catalogue = creerCatalogue();
    vector<Article> panier;
    
    menu(panier, catalogue);

   
    return 0;
}
