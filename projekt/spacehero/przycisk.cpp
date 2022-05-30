#include "przycisk.h"

przycisk::przycisk(const sf::Texture &texture, int rozmiar_x, int rozmiar_y)
{
 setTexture(texture);
 setPosition((rozmiar_x/2 - getGlobalBounds().width/2),(rozmiar_y/2 - getGlobalBounds().height/2));
 setScale(1.0,1.0);
}

bool przycisk::czy_wcisniety(const sf::Vector2f &pozycja_myszki) const
{
    sf::FloatRect rectangle_bounds = getGlobalBounds();

    if((pozycja_myszki.x > rectangle_bounds.left) && (pozycja_myszki.x > rectangle_bounds.left + rectangle_bounds.height))
    {
        if((pozycja_myszki.y > rectangle_bounds.top) && (pozycja_myszki.y < rectangle_bounds.top + rectangle_bounds.height))
        {
            return true;
        }
    }
    return false;
}
