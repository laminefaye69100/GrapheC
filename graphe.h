#ifndef GRAPHE_H
#define GRAPHE_H

#include <iostream>
#include <vector>
#include "pixel.h"


/**
 * @file graphe.h
 * @brief Définition de la classe Graphe pour la manipulation des images PGM.
 * 
 * Cette classe permet de lire, manipuler et sauvegarder des images sous forme
 * de graphes en utilisant un tableau de pixels.
 */

/**
 * @class Graphe
 * @brief Représente une image sous forme de graphe avec des fonctionnalités de manipulation.
 */
class Graphe {
public:
    /** @brief Constructeur par défaut */
    Graphe();

    /**
     * @brief Constructeur à partir d'un fichier PGM.
     * @param nomFichier Chemin du fichier PGM à charger.
     * @throws std::runtime_error si le fichier ne peut pas être ouvert.
     */
    Graphe(const char *nomFichier);

    /**
     * @brief Constructeur par copie.
     * @param autre Objet Graphe à copier.
     */
    Graphe(const Graphe &autre);

    /**
     * @brief Opérateur d'assignation.
     * @param autre Objet Graphe à copier.
     * @return Référence à l'objet courant (*this).
     */
    Graphe& operator=(const Graphe &autre);

    /** @brief Destructeur. Libère la mémoire allouée. */
    ~Graphe();

    /** @brief Affiche les pixels de l'image. */
    void afficherImage() const;

    /**
     * @brief Affiche les distances calculées pour l'image.
     * @param distances Vecteur des distances à afficher.
     */
    void afficherImageDistance(const std::vector<int> &distances) const;

    /**
     * @brief Retourne l'index global d'un voisin selon une direction.
     * @param i Ligne actuelle.
     * @param j Colonne actuelle.
     * @param d Direction du voisin.
     * @return Index global du voisin ou -1 si invalide.
     */
    int getVoisin(int i, int j, Direction d) const;

    /**
     * @brief Convertit des coordonnées en index global.
     * @param i Ligne.
     * @param j Colonne.
     * @return Index global correspondant.
     */
    int getCoord(int i, int j) const;

    /**
     * @brief Retourne l'index global d'un voisin donné un index global.
     * @param k Index global actuel.
     * @param o Direction du voisin.
     * @return Index global du voisin ou -1 si invalide.
     */
    int getVoisinIndiceGlobale(int k, Direction o) const;

    /** @return Nombre de lignes de l'image. */
    int getLignes() const;

    /** @return Nombre de colonnes de l'image. */
    int getColonnes() const;

    /**
     * @brief Sauvegarde l'image actuelle dans un fichier PGM.
     * @param nomFichier Chemin du fichier de sortie.
     */
    void sauvegarderImageForme(const std::string &nomFichier);

    /**
     * @brief Sauvegarde une représentation des distances dans un fichier PGM.
     * @param nomFichier Chemin du fichier de sortie.
     * @param distances Vecteur des distances calculées.
     */
    void sauvegarderImageDistance(const std::string &nomFichier, const std::vector<int> &distances);

    /**
     * @brief Sauvegarde le tableau des prédécesseurs.
     * @param nomFichier Chemin du fichier de sortie.
     * @param predecesseurs Vecteur des prédécesseurs.
     */
    void sauvegarderImagePredecesseurs(const std::string &nomFichier, const std::vector<int> &predecesseurs);

    /**
     * @brief Calcule les distances et les prédécesseurs pour les pixels.
     * @param distances Vecteur des distances à mettre à jour.
     * @param predecesseurs Vecteur des prédécesseurs à mettre à jour.
     */
    void calculerImageDistance(std::vector<int> &distances, std::vector<int> &predecesseurs);

    /**
     * @brief Projette un pixel vers le pixel noir le plus proche.
     * @param x Colonne du pixel.
     * @param y Ligne du pixel.
     * @return Coordonnées du pixel noir le plus proche ou {-1, -1} si invalide.
     */
    std::pair<int, int> projeterPixel(int x, int y);

    /**
     * @brief Effectue l'union de deux images en prenant les distances minimales.
     * @param autre Deuxième objet Graphe à combiner.
     * @return Nouvel objet Graphe résultant de l'union.
     */
    Graphe unionImages(const Graphe& autre);

    std::pair<int, int> projeterPointSurUnion(int x, int y, const std::vector<int> &distances1, const std::vector<int> &distances2) const;
private:
    std::vector<Pixel> image;      /**< Tableau dynamique de pixels */
    int L;             /**< Nombre de lignes */
    int C;             /**< Nombre de colonnes */
    int intensite_max; /**< Intensité lumineuse maximale */
};

#endif // GRAPHE_H
