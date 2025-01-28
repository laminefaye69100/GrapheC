#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include "graphe.h"

using namespace std;

// Fonction pour afficher le menu principal
void afficherMenu() {
    cout << "\n--- Menu de l'Application ---\n";
    cout << "1. Charger une image depuis un fichier PGM\n";
    cout << "2. Afficher l'image actuelle\n";
    cout << "3. Sauvegarder l'image actuelle dans un fichier PGM\n";
    cout << "4. Calculer l'image de distance\n";
    cout << "5. Afficher les distances calculées\n";
    cout << "6. Afficher les prédécesseurs calculés\n";
    cout << "7. Sauvegarder l'image de distance dans un fichier PGM\n";
    cout << "8. Sauvegarder les prédécesseurs dans un fichier texte\n";
    cout << "9. Projecter un pixel d’une image sur une forme\n";
    cout << "10. Faire l'union de deux images\n";
    cout << "11. Projeter un point sur l’union des deux formes\n";
    cout << "12. Quitter\n";
    cout << "Choix : ";
}

int main() {
    Graphe graphe;              // Instance de Graphe
    bool imageChargee = false;  // Vérifie si une image a été chargée
    vector<int> distances, predecesseurs;
    const int INF = std::numeric_limits<int>::max(); // Valeur d'infini

    while (true) {
        afficherMenu(); // Afficher le menu
        int choix;
        cin >> choix;   // Lire le choix de l'utilisateur

        switch (choix) {
            case 1: { // Charger une image
                string nomFichier;
                cout << "Entrez le nom du fichier PGM à charger : ";
                cin >> nomFichier;
                try {
                    graphe = Graphe(nomFichier.c_str()); // Appel du constructeur
                    distances.resize(graphe.getLignes() * graphe.getColonnes(), INF);
                    predecesseurs.resize(graphe.getLignes() * graphe.getColonnes(), -1);
                    imageChargee = true;
                    cout << "Image chargée avec succès depuis " << nomFichier << ".\n";
                } catch (const std::exception &e) {
                    cout << "Erreur lors du chargement de l'image : " << e.what() << "\n";
                }
                break;
            }
            case 2: { // Afficher l'image actuelle
                if (!imageChargee) {
                    cout << "Aucune image n'a été chargée. Veuillez charger une image d'abord.\n";
                    break;
                }
                cout << "Image actuelle :\n";
                graphe.afficherImage();
                break;
            }
            case 3: { // Sauvegarder l'image
                if (!imageChargee) {
                    cout << "Aucune image n'a été chargée. Veuillez charger une image d'abord.\n";
                    break;
                }
                string nomFichier;
                cout << "Entrez le nom du fichier PGM pour sauvegarder l'image : ";
                cin >> nomFichier;
                try {
                    graphe.sauvegarderImageForme(nomFichier);
                    cout << "Image sauvegardée avec succès dans " << nomFichier << ".\n";
                } catch (const std::exception &e) {
                    cout << "Erreur lors de la sauvegarde de l'image : " << e.what() << "\n";
                }
                break;
            }
            case 4: { // Calculer l'image de distance
                if (!imageChargee) {
                    cout << "Aucune image n'a été chargée. Veuillez charger une image d'abord.\n";
                    break;
                }
                try {
                    graphe.calculerImageDistance(distances, predecesseurs);
                    cout << "Image de distance calculée avec succès.\n";
                } catch (const std::exception &e) {
                    cout << "Erreur lors du calcul de l'image de distance : " << e.what() << "\n";
                }
                break;
            }
            case 5: { // Afficher les distances calculées
                if (distances.empty()) {
                    cout << "Aucune image de distance n'a été calculée. Veuillez la calculer d'abord.\n";
                    break;
                }
                cout << "Distances calculées :\n";
                int lignes = graphe.getLignes();
                int colonnes = graphe.getColonnes();
                for (int i = 0; i < lignes; ++i) {
                    for (int j = 0; j < colonnes; ++j) {
                        cout << distances[i * colonnes + j] << " ";
                    }
                    cout << "\n";
                }
                break;
            }
            case 6: { // Afficher les prédécesseurs calculés
                if (predecesseurs.empty()) {
                    cout << "Aucun tableau de prédécesseurs n'a été calculé. Veuillez calculer l'image de distance d'abord.\n";
                    break;
                }
                cout << "Prédécesseurs calculés :\n";
                int lignes = graphe.getLignes();
                int colonnes = graphe.getColonnes();
                for (int i = 0; i < lignes; ++i) {
                    for (int j = 0; j < colonnes; ++j) {
                        cout << predecesseurs[i * colonnes + j] << " ";
                    }
                    cout << "\n";
                }
                break;
            }
            case 7: { // Sauvegarder l'image de distance
                if (distances.empty()) {
                    cout << "Aucune image de distance n'a été calculée. Veuillez la calculer d'abord.\n";
                    break;
                }
                string nomFichier;
                cout << "Entrez le nom du fichier PGM pour sauvegarder l'image de distance : ";
                cin >> nomFichier;
                try {
                    graphe.sauvegarderImageDistance(nomFichier, distances);
                    cout << "Image de distance sauvegardée avec succès dans " << nomFichier << ".\n";
                } catch (const std::exception &e) {
                    cout << "Erreur lors de la sauvegarde de l'image de distance : " << e.what() << "\n";
                }
                break;
            }
            case 8: { // Sauvegarder les prédécesseurs
                if (predecesseurs.empty()) {
                    cout << "Aucun tableau de prédécesseurs n'a été calculé. Veuillez calculer l'image de distance d'abord.\n";
                    break;
                }
                string nomFichier;
                cout << "Entrez le nom du fichier texte pour sauvegarder les prédécesseurs : ";
                cin >> nomFichier;
                try {
                    graphe.sauvegarderImagePredecesseurs(nomFichier, predecesseurs);
                    cout << "Prédécesseurs sauvegardés avec succès dans " << nomFichier << ".\n";
                } catch (const std::exception &e) {
                    cout << "Erreur lors de la sauvegarde des prédécesseurs : " << e.what() << "\n";
                }
                break;
            }
            case 9: { // Projeter un pixel
                if (!imageChargee) {
                    cout << "Aucune image n'a été chargée. Veuillez charger une image d'abord.\n";
                    break;
                }
                int x, y;
                cout << "Entrez les coordonnées du pixel (x, y) : ";
                cin >> x >> y;
                auto [px, py] = graphe.projeterPixel(x, y);
                if (px != -1 && py != -1) {
                    cout << "Le pixel noir le plus proche est à (" << px << ", " << py << ").\n";
                } else {
                    cout << "Aucun pixel noir trouvé.\n";
                }
                break;
            }
            case 10: { // Union deux images
                if (!imageChargee) {
                    cout << "Aucune image n'a été chargée. Veuillez charger une image d'abord.\n";
                    break;
                }
                string autreFichier;
                cout << "Entrez le nom du deuxième fichier PGM pour la fusion : ";
                cin >> autreFichier;

                try {
                    Graphe autreGraphe(autreFichier.c_str());
                    Graphe resultat = graphe.unionImages(autreGraphe);

                    string fichierResultat;
                    cout << "Entrez le nom du fichier PGM pour sauvegarder l'image fusionnée : ";
                    cin >> fichierResultat;

                    resultat.sauvegarderImageForme(fichierResultat);
                    cout << "Image fusionnée sauvegardée avec succès dans " << fichierResultat << ".\n";
                } catch (const std::exception &e) {
                    cerr << "Erreur : " << e.what() << endl;
                }
                break;
            }
            case 11: { // Projeter un point sur l’union des deux formes
                if (!imageChargee) {
                    cout << "Aucune image n'a été chargée. Veuillez charger une image d'abord.\n";
                    break;
                }

                string autreFichier;
                cout << "Entrez le nom du deuxième fichier PGM : ";
                cin >> autreFichier;

                Graphe autreGraphe(autreFichier.c_str());

                // Distances des deux graphes
                vector<int> distances1(distances), distances2;
                vector<int> predecesseurs2;

                distances2.resize(autreGraphe.getLignes() * autreGraphe.getColonnes(), INF);
                predecesseurs2.resize(autreGraphe.getLignes() * autreGraphe.getColonnes(), -1);

                autreGraphe.calculerImageDistance(distances2, predecesseurs2);

                int x, y;
                cout << "Entrez les coordonnées du point (x, y) : ";
                cin >> x >> y;

                auto [px, py] = graphe.projeterPointSurUnion(x, y, distances1, distances2);
                if (px != -1 && py != -1) {
                    cout << "Le pixel noir le plus proche dans l’union des deux formes est à (" << px << ", " << py << ").\n";
                } else {
                    cout << "Le point n’est accessible dans aucune des deux formes.\n";
                }

                break;
            }
            case 12: { // Quitter
                cout << "Merci d'avoir utilisé l'application. Au revoir !\n";
                return 0;
            }
            default:
                cout << "Choix invalide. Veuillez réessayer.\n";
                break;
        }
    }
}
