#include "boost.h"
#include "iostream"
#include <fstream>
//Konstruktor boosta z losowa pozycja
boost::boost(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(0.1, 0.1);

  int x = 0;
  int y = 0;

  x = rand () % rozmiar_x;
  y = rand () % rozmiar_y;

  setPosition(x,y);

  //Ustawienie parametrow pliku (można zmienić samemu)
    std::string z_pliku;

    std::ifstream Czytaj_Plik("./../spacehero/parameters/boost.txt");
    if(Czytaj_Plik.fail())
    {
        return;
    }
    Czytaj_Plik >> z_pliku;
    Czytaj_Plik.close();

    predkosc_x = 0;
    predkosc_y = stoi(z_pliku);
}

//Metoda od poruszania się boostow
void boost::poruszaj(const sf::Time &elapsed)
{
    move(predkosc_x * elapsed.asSeconds(), predkosc_y * elapsed.asSeconds());
}

