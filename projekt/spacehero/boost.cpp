#include "boost.h"
#include "iostream"


boost::boost(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(0.1, 0.1);

//  setPosition(-100,-100);

  int x = 0;
  int y = 0;

  x = rand () % rozmiar_x;
  y = rand () % rozmiar_y;

  setPosition(x,y);

  predkosc_x = 0;
  predkosc_y = 50;
}


void boost::poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{
    move(predkosc_x * elapsed.asSeconds(), predkosc_y * elapsed.asSeconds());
}

