#include "ufo.h"
#include <fstream>
//Losowa pozycja dla ufo
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

//Konstruktor ufo
Ufo::Ufo(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
  setTexture(texture);
  setScale(0.2,0.2);

  //Ustawienie zycia z pliku (można zmienić samemu)
  std::string z_pliku;
  std::string z_pliku2;

  std::ifstream Czytaj_Plik("./../spacehero/parameters/ufo.txt");
  if(Czytaj_Plik.fail())
  {
      return;
  }
  Czytaj_Plik >> z_pliku >> z_pliku2;
  Czytaj_Plik.close();
  zycia = stoi(z_pliku);

  auto[x,y] = losowa_pozycja(rozmiar_x-55, (rozmiar_y - rozmiar_y/2) - 100, 50);
  setPosition(x,y);
          predkosc_x_ = 0;
          predkosc_y_ = stoi(z_pliku2);

          //Losowanie predkosci
          float predkosc = ((float)(rand()%200)/5.0) +5;
          int losowanie = rand()%2;

          if(losowanie == 0)
          {
            predkosc_y_ = predkosc;
          }
          else if(losowanie == 1)
          {
            predkosc_y_ = predkosc;
          }




}

//Poruszanie się dla klasy ufo
void Ufo::poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{
          sf::FloatRect rectangle_bounds = getGlobalBounds();

          if(rectangle_bounds.left < 0)
          {
              return;
          }
          else if(rectangle_bounds.left+rectangle_bounds.width > rozmiar_x)
          {
              return;
          }
          move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ * elapsed.asSeconds());
}

//Obsługa żyć dla klasy ufo
void Ufo::zmniejsz_zycie(int odejmij_zycie)
{
    zycia -= odejmij_zycie;
}

int Ufo::pobierz_liczbe_zyc()
{
    return zycia;
}
