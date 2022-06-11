#include "boss.h"

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

//  auto[x,y] = losowa_pozycja(rozmiar_x-55, (rozmiar_y - rozmiar_y/2) - 100, 50);
//  setPosition(x,y);
  setPosition(rozmiar_x/2, rozmiar_y/2);
          predkosc_x_ = 100;
          predkosc_y_ = 10;
          //int obrot = 25;

          //Losowanie predkosci
//          float predkosc = ((float)(rand()%2000)/5.0) +5;
//          int losowanie = rand()%2;

//          if(losowanie == 0)
//          {
//            predkosc_x_ = predkosc;
//          }
//          else if(losowanie == 1)
//          {
//            predkosc_x_ = predkosc;
//          }

  zycia = 5;
}

void boss::ustaw_granice(const sf::IntRect &bounds)
{
    bounds_ = bounds;
    boss_shape_.setSize(sf::Vector2f(bounds_.width, bounds_.height));
    boss_shape_.setPosition(bounds_.top, bounds_.left);
}

void boss::poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{
    sf::FloatRect rectangle_bounds = getGlobalBounds();

     int obrot = 25;
    if(rectangle_bounds.left + rectangle_bounds.width - 25>= windowBounds.width)
    {
        predkosc_x_ = -std::abs(predkosc_x_);
    }
    else if(rectangle_bounds.left + 25 <= 0)
    {
        predkosc_x_ = std::abs(predkosc_x_);
    }
    if(rectangle_bounds.top <= bounds_.top)
    {
        predkosc_y_ = std::abs(predkosc_y_);
    }
    else if(rectangle_bounds.top + rectangle_bounds.height >= bounds_.top - 25 + bounds_.height)
    {
        predkosc_y_ = -std::abs(predkosc_y_);
    }
    move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ * elapsed.asSeconds());
    //rotate(obrot*elapsed.asSeconds());
}


void boss::zmniejsz_zycie(int odejmij_zycie)
{
  zycia -= odejmij_zycie;
}

int boss::pobierz_liczbe_zyc()
{
 return zycia;
}

bool boss::czy_zyje() const
{

}
