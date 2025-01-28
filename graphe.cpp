#include <iostream>
#include "graphe.h"
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <functional>

using namespace std;
Graphe::Graphe(){}
Graphe::Graphe(const char * nomFichier) 
{
    int valeurs = 0; //valeur du pixel qu'on va insere dans le tableau d'intensite
    std::ifstream flux;
    flux.open(nomFichier);
    if(!flux.is_open())
    {cout<<"Impossible d'ouvrir le fichier "<<nomFichier<<" en lecture \n"; exit(1);}
    string caractere_inutile;
    
    flux>>caractere_inutile;             //caractere inutile
    flux>>C;                 //le nombre de colonne
    flux>>L;                 //le nombre de ligne
    flux>>intensite_max;     //l'intesite maximum
    
     image.resize(L * C);   //insertion dans notre tableau de pixel
    for(int i = 0;i<L*C;i++)
    {
        flux>>valeurs;
        image[i].setIntensiteLumineuse(valeurs);      //on saisit les pixels dans le tableau de pixels
    }
    flux.close();
}

 // Constructeur par copie
Graphe::Graphe(const Graphe &autre) {
    L = autre.L;
    C = autre.C;
    intensite_max = autre.intensite_max;

    // Copier le tableau des pixels
     image.resize(L * C);
    for (int i = 0; i < L * C; ++i) {
        image[i] = autre.image[i];
    }
}

// Opérateur d'assignation
Graphe& Graphe::operator=(const Graphe &autre) {
    if (this != &autre) { // Éviter l'auto-assignation
        image.clear(); // Libérer la mémoire existante

        L = autre.L;
        C = autre.C;
        intensite_max = autre.intensite_max;

        // Copier le tableau des pixels
         image.resize(L * C);
        for (int i = 0; i < L * C; ++i) {
            image[i] = autre.image[i];
        }
    }
    return *this;
}

Graphe::~Graphe() {
}


void Graphe::afficherImage()const{

    cout<<"Les Colonnes "<<C<<endl;
    cout<<"Les Lignes "<<L<<endl;
    cout<<"intensite max "<<intensite_max<<endl;
    for(int i = 0;i<L;i++)
        {
            for(int j= 0;j<C;j++)
            {   if(image[i*C+j].getIntensiteLumineuse()==0) cout<<" ";
                cout<<image[i*C+j].getIntensiteLumineuse()<<" ";
                if(image[i*C+j].getIntensiteLumineuse()==0) cout<<" ";
            }
            cout<<endl;
        }
}
void Graphe::afficherImageDistance(const std::vector<int> &distances) const {
    cout << "Image des distances :\n";
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C; ++j) {
            int dist = distances[i * C + j];
            cout << (dist == std::numeric_limits<int>::max() ? -1 : dist) << " "; // Affiche -1 pour infini
        }
        cout << endl;
    }
}
int Graphe::getVoisin(int i, int j, Direction d) const{
    int ni = i, nj = j;

    switch (d) {
        case Nord: ni--; break;
        case Sud: ni++; break;
        case Est: nj++; break;
        case Ouest: nj--; break;
        case NordEst: ni--; nj++; break;
        case NordOuest: ni--; nj--; break;
        case SudEst: ni++; nj++; break;
        case SudOuest: ni++; nj--; break;
        default: return -1; // Direction invalide
    }

    // Verifie si le voisin est dans les limites
    if (ni >= 0 && ni < L && nj >= 0 && nj < C) {
        return getCoord(ni, nj); // Convertir en index global
    } else {
        return -1; // Pas de voisin valide
    }
}

int Graphe::getCoord(int i, int j) const
{
    return i*C+j;
}

int Graphe::getVoisinIndiceGlobale(int k, Direction o) const{
    // Calculer les coordonnees (i, j) à partir de l'index global k
    int i = k / C; // Ligne
    int j = k % C; // Colonne

    // Coordonnees du voisin
    int ni = i, nj = j;

    // Determiner le deplacement en fonction de la direction
    switch (o) {
        case Est:       nj++; break;
        case Ouest:     nj--; break;
        case Nord:      ni--; break;
        case Sud:       ni++; break;
        case NordEst:   ni--; nj++; break;
        case NordOuest: ni--; nj--; break;
        case SudEst:    ni++; nj++; break;
        case SudOuest:  ni++; nj--; break;
        default:
            std::cerr << "Direction invalide\n";
            return -1; // Direction non valide
    }

    // Verifier si les coordonnees sont dans les limites
    if (ni >= 0 && ni < L && nj >= 0 && nj < C) {
        return ni * C + nj; // Retourner l'index global du voisin
    }

    // Si le voisin est hors des limites, rien n'est retourné ici
    return -1;
}


int Graphe::getLignes() const{ return L;}
int Graphe::getColonnes() const{return C;}

void Graphe::sauvegarderImageForme(const string &nomFichier) {
    // Ouvrir le fichier en mode écriture
    ofstream flux(nomFichier);
    if (!flux.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << " pour la sauvegarde." << endl;
        exit(1);
    }

    // Écrire les informations d'en-tête au format PGM
    flux << "P2" << endl;           // Format PGM
    flux << C << " " << L << endl;  // Dimensions : Colonnes (C) et Lignes (L)
    flux << intensite_max << endl;  // Intensité maximale

    // Écrire les données des pixels ligne par ligne
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C; ++j) {
            flux << image[i * C + j].getIntensiteLumineuse() << " ";
        }
        flux << endl; // Nouvelle ligne après chaque ligne de pixels
    }

    // Fermer le fichier après l'écriture
    flux.close();
    cout << "Image sauvegardée avec succès dans le fichier " << nomFichier << "." << endl;
}

void Graphe::sauvegarderImageDistance(const string &nomFichier, const vector<int> &distances) {
    ofstream fichier(nomFichier);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        exit(1);
    }

    // Écrire l'en-tête PGM
    fichier << "P2\n" << C << " " << L << "\n" << 255 << "\n";

    // Écrire les distances ligne par ligne
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C; ++j) {
            int distance = distances[i * C + j];
            // Si la distance est "infinie", écrire 255 (blanc) pour indiquer un pixel inaccessible
            fichier << (distance == std::numeric_limits<int>::max() ? 255 : distance) << " ";
        }
        fichier << "\n";
    }

    fichier.close();
    cout << "Image de distance sauvegardée dans " << nomFichier << "." << endl;
}

void Graphe::sauvegarderImagePredecesseurs(const string &nomFichier, const vector<int> &predecesseurs) {
    ofstream fichier(nomFichier);
    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        exit(1);
    }

    fichier << "Tableau des prédécesseurs :\n";
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < C; ++j) {
            int pred = predecesseurs[i * C + j];
            // Écrire -1 si aucun prédécesseur n'est défini
            fichier << pred << " ";
        }
        fichier << "\n";
    }

    fichier.close();
    cout << "Tableau des prédécesseurs sauvegardé dans " << nomFichier << "." << endl;
}


void Graphe::calculerImageDistance(vector<int> &distances, vector<int> &predecesseurs) {
   
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> file; // Min-heap

    // Initialiser les pixels noirs (distance 0) dans la file
    for (int i = 0; i < L * C; ++i) {
        if (image[i].getIntensiteLumineuse() == 0) {
            distances[i] = 0;
            file.emplace(0, i); // Ajouter (distance, index) à la file
        }
    }

    // Coûts pour les directions : orthogonaux = 2, diagonaux = 3
    const int costs[] = {2, 2, 2, 2, 3, 3, 3, 3};

    // Parcourir la file jusqu'à épuisement
    while (!file.empty()) {
        auto [distanceActuelle, index] = file.top();
        file.pop();

        // Ignorer les distances dépassées
        if (distanceActuelle > distances[index]) continue;

        // Coordonnées du pixel courant
        int y = index / C, x = index % C;

        // Parcourir toutes les directions
        for (int d = Ouest; d <= NordEst; ++d) {
            Direction direction = static_cast<Direction>(d);
            int voisin = getVoisin(y, x, direction);

            if (voisin != -1) { // Si le voisin est valide
                int nouveauCout = distanceActuelle + costs[d];
                if (nouveauCout < distances[voisin]) {
                    distances[voisin] = nouveauCout;
                    predecesseurs[voisin] = index; // Mettre à jour le prédécesseur
                    file.emplace(nouveauCout, voisin); // Ajouter à la file
                }
            }
        }
    }
}

std::pair<int, int> Graphe::projeterPixel(int x, int y) {
    // Vérifiez si le pixel est dans les limites
    if (x < 0 || x >= C || y < 0 || y >= L) {
        std::cerr << "Erreur : Pixel en dehors des limites\n";
        return {-1, -1}; // Coordonnées invalides
    }

    int distanceMin = -1;  // Valeur pour l'infini ou non calculé
    int pixelProche = -1;  // Index global du pixel noir le plus proche

    // Parcourir tous les pixels pour trouver le plus proche
    for (int i = 0; i < L * C; ++i) {
        if (image[i].getIntensiteLumineuse() == 0) { // Si le pixel est noir
            // Calculer la distance en grille
            int dx = abs(i % C - x); // Différence des colonnes
            int dy = abs(i / C - y); // Différence des lignes
            int distance = dx + dy;
            // Mettre à jour la distance minimale
            if (distanceMin == -1 || distance < distanceMin) {
                distanceMin = distance;
                pixelProche = i; // Sauvegarder l'index global
            }
        }
    }

    // Retourner les coordonnées du pixel noir le plus proche
    if (pixelProche != -1) {
        return {pixelProche % C, pixelProche / C}; // Conversion index global -> coordonnées (x, y)
    }

    // Aucun pixel noir trouvé
    return {-1, -1};
}
Graphe Graphe::unionImages(const Graphe& autre) {
    // Vérifier si les dimensions des deux images correspondent
    if (L != autre.L || C != autre.C) {
        std::cerr << "Erreur : Les dimensions des images ne correspondent pas\n";
        exit(1); // Arrêter le programme si les tailles ne correspondent pas
    }

    // Créer une nouvelle image pour le résultat
    Graphe resultat(*this); // Copie de l'image actuelle (this)

    // Parcourir chaque pixel pour fusionner les distances
    for (int i = 0; i < L * C; ++i) {
        int distance1 = image[i].getIntensiteLumineuse();   // Distance du pixel dans la première image
        int distance2 = autre.image[i].getIntensiteLumineuse(); // Distance du pixel dans l'autre image

        // Fusionner les distances : prendre la distance minimale
        resultat.image[i].setIntensiteLumineuse(std::min(distance1, distance2));
    }

    return resultat; // Retourner l'image fusionnée
}

std::pair<int, int> Graphe::projeterPointSurUnion(int x, int y, const std::vector<int> &distances1, const std::vector<int> &distances2) const {
    // Vérifiez si le pixel est dans les limites
    if (x < 0 || x >= C || y < 0 || y >= L) {
        std::cerr << "Erreur : Pixel en dehors des limites\n";
        return {-1, -1}; // Coordonnées invalides
    }

    int index = getCoord(x, y); // Index global du point (x, y)

    // Distances minimales pour le point à projeter
    int distance1 = distances1[index];
    int distance2 = distances2[index];

    // Vérifiez si l'une des distances est infinie (pixel inaccessible)
    if (distance1 == std::numeric_limits<int>::max() && distance2 == std::numeric_limits<int>::max()) {
        std::cerr << "Erreur : Le point est inaccessible dans les deux formes\n";
        return {-1, -1}; // Aucun pixel noir accessible
    }

    // Trouver la forme la plus proche
    int distanceMin = std::min(distance1, distance2);

    // Identifier le prédécesseur dans la forme correspondante
    int pixelProcheIndex = -1;
    if (distance1 == distanceMin) {
        pixelProcheIndex = index; // Pixel provenant de la première forme
    } else if (distance2 == distanceMin) {
        pixelProcheIndex = index; // Pixel provenant de la deuxième forme
    }

    // Retourner les coordonnées du pixel noir le plus proche
    return {pixelProcheIndex % C, pixelProcheIndex / C}; // Convertir l'index global en (x, y)
}
