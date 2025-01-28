#include "pixel.h"
#include <iostream>

Pixel::Pixel(int intensite,int coord_x,int coord_y):intensite_lumineuse(intensite),x(coord_x),y(coord_y)
{

}

//retourne l'intensite lumineuse du pixel
int Pixel::getIntensiteLumineuse() const
{
    return intensite_lumineuse;
}
//modifie l'intensite lumineuse du pixel
void Pixel::setIntensiteLumineuse(int intensite)
{
    intensite_lumineuse=intensite;
}
// retourner la coordonnee de x
int Pixel::getX() const
{
    return x;
}
// retourner la coordonnee de y
int Pixel::getY() const
{
    return y;
}
   
//afficher les informations d'un pixel
void Pixel::afficher_Pixel() const
{
    std::cout<< "("<< x <<", "<< y <<" )-Intensite:" << intensite_lumineuse<< std::endl;
}
