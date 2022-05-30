#include "ufo.h"

std::pair<int, int> Ufo::losowa_pozycja(int rozmiar_x, int rozmiar_y, int bez_dolu)
{
    int x = 0;
    int y = 0;
    do
    {
        x = rand () % rozmiar_x;
        y = rand () % rozmiar_y;
    }
    while((abs(x-rozmiar_x/2) < bez_dolu) || (abs(y - rozmiar_y/2) < bez_dolu));

    return std::pair<int,int>(x,y);
}

Ufo::Ufo(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(0.2,0.2);


  auto[x,y] = losowa_pozycja(rozmiar_x-55, (rozmiar_y - rozmiar_y/2), 50);
  setPosition(x,y);
          predkosc_x_ = 0;
          predkosc_y_ = 10;
}


void Ufo::poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{

          move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ * elapsed.asSeconds());
}
