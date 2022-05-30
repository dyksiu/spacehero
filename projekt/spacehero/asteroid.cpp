#include "asteroid.h"

std::pair<int, int> Asteroid::losowa_pozycja(int rozmiar_x, int rozmiar_y, int bez_dolu)
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


Asteroid::Asteroid(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(0.1,0.1);
  auto[x,y] = losowa_pozycja(rozmiar_x, rozmiar_y - rozmiar_y/2, 50);
  setPosition(x,y);

}

void Asteroid::poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{

}
