#include "spaceship.h"

Spaceship::Spaceship(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
   zresetuj_statek(texture, rozmiar_x, rozmiar_y);
}

//Metoda wirtualna
void Spaceship::poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{

}

void Spaceship::zresetuj_statek(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
    setTexture(texture);
    setScale(0.3,0.3);
    setPosition((rozmiar_x/2 - getGlobalBounds().width/4),(rozmiar_y - getGlobalBounds().height));

    predkosc_x_ = 0;
    predkosc_y_ = 0;

}

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


