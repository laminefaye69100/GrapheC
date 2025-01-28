#ifndef _PIXEL_
#define _PIXEL_

//enum des differents directions possibles
enum Direction {Ouest=0, Sud=1 , Est=2 , Nord=3, SudEst=4 , SudOuest=5 , NordOuest=6 , NordEst=7};

class Pixel{
    
    private:
    int intensite_lumineuse;//Valeur de 0 a 255 representant l'intensite lumineuse
    int x;// Coordonnees Colonne
    int y;// Coordonnees Ligne

  
    public:
    Pixel(int intensite=0,int coord_x=0,int coord_y=0);

    //retourne l'intensite lumineuse du pixel
    int getIntensiteLumineuse() const;
    //modifie l'intensite lumineuse du pixel
    void setIntensiteLumineuse(int intensite);
    // retourner la coordonnee de x
    int getX() const;
    // retourner la coordonnee de y
    int getY() const;
    //afficher les informations d'un pixel
    void afficher_Pixel() const;
};

#endif