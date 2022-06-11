#include "boss.h"
#include <iostream>
std::pair<int, int> boss::losowa_pozycja(int rozmiar_x, int rozmiar_y, int bez_dolu)
{
    int x = 0;
    int y = 0;
    do
    {
        x = rand () % rozmiar_x;
        y = rand () % rozmiar_y;
    }
    while((abs(x-rozmiar_x/2) < bez_dolu) || (abs(y - rozmiar_y/2) < bez_dolu));
    return std::pair<int, int>(x,y);

}


boss::boss(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(0.5,0.5);

  auto[x,y] = losowa_pozycja(rozmiar_x-55, (rozmiar_y - rozmiar_y/2) - 100, 50);
  setPosition(x,y);
  setPosition(rozmiar_x/2, rozmiar_y/2);
          predkosc_x_ = 300;
          predkosc_y_ = 300;
          int obrot = 25;

  zycia = 20;
}

void boss::ustaw_granice(const sf::IntRect &bounds)
{
    bounds_ = bounds;
    boss_shape_.setSize(sf::Vector2f(bounds_.width, bounds_.height));
    boss_shape_.setPosition(bounds_.top, bounds_.left);
}

void boss::poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{

}

 void boss::ruch(const sf::Time &elapsed)
{
      odbicia();
      move(elapsed.asSeconds()*predkosc_x_,elapsed.asSeconds()*predkosc_y_);

}

void boss::odbicia()
{
sf::FloatRect rectangle_bounds=this->getGlobalBounds();
      //Dół
      if((rectangle_bounds.top+rectangle_bounds.height)>=(720)){
          predkosc_y_=-std::abs(predkosc_y_);
      }
      //Góra
      if((rectangle_bounds.top)<=0){
          predkosc_y_=std::abs(predkosc_y_);
      }
      //Prawo
      if((rectangle_bounds.left+rectangle_bounds.width)>=(1080)){
          predkosc_x_=-std::abs(predkosc_x_);
      }
      //Lewo
      if((rectangle_bounds.left)<=0){
          predkosc_x_=std::abs(predkosc_x_);
      }
}

void boss::zmniejsz_zycie(int odejmij_zycie)
{
  zycia -= odejmij_zycie;
}

int boss::pobierz_liczbe_zyc()
{
 return zycia;
}

void boss::dodaj_zycie(int dodaj_zycie)
{
    zycia += dodaj_zycie;
}

bool boss::czy_zyje() const
{

}
