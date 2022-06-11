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
  auto[x,y] = losowa_pozycja(rozmiar_x-60, rozmiar_y - rozmiar_y/2, 50);
  setPosition(x,y);
          predkosc_x_ = 0;
          predkosc_y_ = 10;

          //Losowanie predkosci
          float predkosc = ((float)(rand()%100)/5.0) +5;
          int losowanie = rand()%2;

          if(losowanie == 0)
          {
            predkosc_y_ = predkosc;
          }
          else if(losowanie == 1)
          {
            predkosc_y_ = predkosc;
          }



   zycia = 3;
}

void Asteroid::poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{
  sf::FloatRect rectangle_bounds = getGlobalBounds();

  if(rectangle_bounds.left <0)
  {
      return;
  }
  else if(rectangle_bounds.left + rectangle_bounds.width > rozmiar_x)
  {
      return;
  }
  move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ *elapsed.asSeconds());
}

void Asteroid::zmniejsz_zycie(int odejmij_zycie)
{
    zycia -= odejmij_zycie;
}

bool Asteroid::czy_zyje() const
{

}

int Asteroid::pobierz_liczbe_zyc()
{
    return zycia;
}


