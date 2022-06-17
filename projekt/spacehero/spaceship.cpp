#include "spaceship.h"
#include <fstream>

//Konstruktor dla statku
Spaceship::Spaceship(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
   zresetuj_statek(texture, rozmiar_x, rozmiar_y);
}

//Metoda ustawiajaca pozycje startowa dla statku
void Spaceship::pozycja_startowa(int rozmiar_x, int rozmiar_y)
{
    setPosition((rozmiar_x/2 - getGlobalBounds().width/4),(rozmiar_y - getGlobalBounds().height));
}

//Metoda wirtualna
void Spaceship::poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{

}

//Metoda resetujaca statek do ustawienia i parametrow poczatkowych
void Spaceship::zresetuj_statek(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
    setTexture(texture);
    setScale(0.3,0.3);
    setPosition((rozmiar_x/2 - getGlobalBounds().width/4),(rozmiar_y - getGlobalBounds().height));

    predkosc_x_ = 0;
    predkosc_y_ = 0;

    //Ustawienie zycia z pliku (można zmienić samemu)
    std::string z_pliku;

    std::ifstream Czytaj_Plik("./../spacehero/parameters/spaceship.txt");
    if(Czytaj_Plik.fail())
    {
        return;
    }
    Czytaj_Plik >> z_pliku;
    Czytaj_Plik.close();
    zycia = stoi(z_pliku);

}

//Metoda odpowiedzialna za ruch statku po osi x ->za pomocą A i D
void Spaceship::ruch_po_x(const sf::Time &elapsed, const sf::RenderWindow &window, int predkosc_x)
{
    sf::FloatRect rectangle_bounds = getGlobalBounds();

    float ruch_x = elapsed.asSeconds()*predkosc_x*500;

    if((rectangle_bounds.left + ruch_x <= 0))
    {
        return;
    }
    if(rectangle_bounds.left + rectangle_bounds.width + ruch_x > window.getSize().x)
    {
        return;
    }

    move(ruch_x, 0);

}

//Obsluga punktow
int Spaceship::pobierz_liczbe_punktow()
{
    return punkty;
}

void Spaceship::dodaj_punkty(int punkty_do_dodania)
{
    punkty += punkty_do_dodania;
}

//Obsługa żyć
void Spaceship::zmniejsz_zycie(int odejmij_zycie)
{
    zycia -= odejmij_zycie;
}

bool Spaceship::czy_zyje() const
{
    if(zycia >0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Spaceship::pobierz_liczbe_zyc()
{
    return zycia;
}

void Spaceship::dodaj_zycie(int dodaj_zycie)
{
    zycia += dodaj_zycie;
}


