#include "spaceship.h"

Spaceship::Spaceship(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
   zresetuj_statek(texture, rozmiar_x, rozmiar_y);
}

void Spaceship::zresetuj_statek(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
    setTexture(texture);
    setScale(0.3,0.3);
    setPosition((rozmiar_x/2 - getGlobalBounds().width/4),(rozmiar_y - getGlobalBounds().height));

    predkosc_x_ = 0;
    predkosc_y_ = 0;

}

void Spaceship::poruszaj(const sf::Time &elapsed,const sf::IntRect &windowBounds, int rozmiar_x, int rozmiar_y)
{

    move(predkosc_x_ * elapsed.asSeconds(), predkosc_y_ * elapsed.asSeconds());
}

void Spaceship::sterowanie_klawiszami(const sf::Event &event)
{
    float predkosc = 200;

   if((event.key.code == sf::Keyboard::A))
    {
        predkosc_x_ = -predkosc;
    }
    else if(event.key.code == sf::Keyboard::D)
    {
        predkosc_x_ = predkosc;
    }
   }

