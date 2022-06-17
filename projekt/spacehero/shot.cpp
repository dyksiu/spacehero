#include "shot.h"
#include <fstream>
shot::shot(const sf::Texture &texture, Spaceship &statek)
{
  setTexture(texture);
  setScale(0.2,0.2);


  predkosc_x_ = 0;
  predkosc_y_ = 0;
  setPosition(-100, -100);
}

void shot::poruszaj(const sf::Time &elapsed, const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{
    move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ * elapsed.asSeconds());
}

void shot::strzal(const sf::Event &event, Spaceship &statek, sf::Music &strzal)
{
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;

      std::ifstream Czytaj_Plik("./../spacehero/parameters/shoot.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku;
      Czytaj_Plik.close();

    float predkosc_pocisku = stoi(z_pliku);


    if(event.key.code == sf::Keyboard::Space)
    {

        predkosc_y_ = -predkosc_pocisku;
        setPosition(statek.getPosition().x+30, statek.getPosition().y);
        strzal.play();

    }
    else
    {
        strzal.stop();
    }

}

void shot::strzal_2(const sf::Event &event, Spaceship &statek2, sf::Music &strzal2)
{
    //Ustawienie parametrow z pliku (można zmienić samemu)
      std::string z_pliku;

      std::ifstream Czytaj_Plik("./../spacehero/parameters/shoot.txt");
      if(Czytaj_Plik.fail())
      {
          return;
      }
      Czytaj_Plik >> z_pliku;
      Czytaj_Plik.close();

    float predkosc_pocisku = stoi(z_pliku);


    if(event.key.code == sf::Keyboard::Enter)
    {

        predkosc_y_ = -predkosc_pocisku;
        setPosition(statek2.getPosition().x+30, statek2.getPosition().y);
        strzal2.play();

    }
    else
    {
        strzal2.stop();
    }
}

void shot::usun_pocisk(std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski)
{
    for(auto itr = pociski.begin(); itr != pociski.end();)
    {
      pociski.erase(itr);
    }
}

//Metody wirtualne
void shot::zmniejsz_zycie(int odejmij_zycie)
{

}

int shot::pobierz_liczbe_zyc()
{

}

