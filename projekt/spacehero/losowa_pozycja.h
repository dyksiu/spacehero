#pragma once

#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

std::pair<int, int> losowa_pozycja(int rozmiar_x, int rozmiar_y, int bez_dolu)
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
