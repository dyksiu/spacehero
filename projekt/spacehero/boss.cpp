#include "boss.h"
#include <iostream>
#include <fstream>
//Losowa pozycja dla bossa
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

//Konstruktor bossa
boss::boss(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(0.5,0.5);

  auto[x,y] = losowa_pozycja(rozmiar_x-55, (rozmiar_y - rozmiar_y/2) - 100, 50);
  setPosition(x,y);
  setPosition(rozmiar_x/2, rozmiar_y/2);

  //Ustawienie parametrow z pliku (można zmienić samemu)
  std::string z_pliku;
  std::string z_pliku2;
  std::string z_pliku3;

  std::ifstream Czytaj_Plik("./../spacehero/parameters/boss.txt");
  if(Czytaj_Plik.fail())
    {
      return;
    }
     Czytaj_Plik >> z_pliku >> z_pliku2 >> z_pliku3;
     Czytaj_Plik.close();

          zycia = stoi(z_pliku);
          predkosc_x_ = stoi(z_pliku2);
          predkosc_y_ = stoi(z_pliku3);

}

//Ustawienie granic odbijania dla bossa
void boss::ustaw_granice(const sf::IntRect &bounds)
{
    bounds_ = bounds;
    boss_shape_.setSize(sf::Vector2f(bounds_.width, bounds_.height));
    boss_shape_.setPosition(bounds_.top, bounds_.left);
}

//Metoda wirtualna
void boss::poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{

}

//Metoda odpowiadajaca za ruch bossa z wzglednieniem boundsow
void boss::ruch(const sf::Time &elapsed)
{
      odbicia();
      move(elapsed.asSeconds()*predkosc_x_,elapsed.asSeconds()*predkosc_y_);

}

//Boundsy bossa
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

//Metody od obsługi życia
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

