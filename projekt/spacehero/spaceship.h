#pragma once

#include <AnimowaneObiekty.h>

class Spaceship : public AnimowaneObiekty
{
public:
    Spaceship(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    //Sekcja metoda
    //Metody od polozenia statku
    void zresetuj_statek(const sf::Texture &texture, int rozmiar_x, int rozmiar_y);

    //Metody od poruszania statku
    void poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y);

    void ruch_po_x(const sf::Time &elapsed, const sf::RenderWindow &window, int predkosc_x);

    //Metody obslugujace punkty
    int pobierz_liczbe_punktow();
    void dodaj_punkty(int punkty_do_dodania);


private:
    int punkty = 0;
};
