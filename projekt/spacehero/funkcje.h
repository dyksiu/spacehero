#pragma once

//Sekcja bibliotek ogolnych
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <memory>
#include <utility>

//Sekcja bibliotek SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//Sekcja klas i funkcji
#include "AnimowaneObiekty.h"
#include "StatyczneObiekty.h"
#include "spaceship.h"
#include "ufo.h"
#include "przycisk.h"
#include "asteroid.h"
#include "shot.h"


////////////////////////////////////////////
//Funkcja odpowiedzialna za wczytywanie tekstur
sf::Texture loadTexture(const std::string &nazwa_pliku)
{
    sf::Texture texture;
    if(!texture.loadFromFile(nazwa_pliku)){
        std::cerr << "Nie udalo sie wczytac pliku!" << std::endl;
    }
    return texture;
}

//Funkcja odpowiedzialna za kolizje przeciwnikow
bool kolizja_przeciwnikow(std::vector<std::unique_ptr<AnimowaneObiekty>> &przeciwnicy, AnimowaneObiekty *przeciwnik)
{
    for(auto &p : przeciwnicy)
    {
      if(przeciwnik->getGlobalBounds().intersects(p->getGlobalBounds()))
      {
          return true;
      }
    }
    return false;
}

//Funkcja odpowiedzialna za dodawanie przeciwnikow
void dodaj_przeciwnikow_1(std::vector<std::unique_ptr<AnimowaneObiekty>> &przeciwnicy, const sf::Texture &textureUfo, const sf::Texture &textureAsteroid, int rozmiar_x, int rozmiar_y)
{
    //Dodanie Ufo
    //Na 1 poziomie 15 ufo
    for(int i=0; i<15; i++)
    {
        auto ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, ufo.get()))
        {
            ufo = std::make_unique<Ufo>(textureUfo, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(ufo));
    }
    //Dodanie Asteroid
    //Na 1 poziomie 5 asteroid

    for(int i=0; i<5; i++)
    {
        auto asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        while(kolizja_przeciwnikow(przeciwnicy, asteroid.get()))
        {
            asteroid = std::make_unique<Asteroid>(textureAsteroid, rozmiar_x, rozmiar_y);
        }
        przeciwnicy.emplace_back(std::move(asteroid));
    }
}

void dodaj_pociski(std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski, const sf::Texture &textureShot, Spaceship &statek)
{
   for(int i=0; i<100; i++)
   {
       pociski.emplace_back(std::make_unique<shot>(textureShot, statek));
   }
}
//Funkcja odpowiedzialna za zderzenia z pociskiem
void zderzenia(std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski, std::vector<std::unique_ptr<AnimowaneObiekty>> &obiekty, int rozmiar_x, int rozmiar_y, sf::Texture &textureUfo, sf::Texture &textureAsteroid)
{
    for(auto itr = obiekty.begin(); itr != obiekty.end();)
    {
        for(auto itr2 = pociski.begin(); itr2 != pociski.end();)
        {
            shot *pocisk = dynamic_cast<shot *>(itr2->get());
            if(pocisk != nullptr){
            if((*itr2)->getGlobalBounds().intersects((*itr)->getGlobalBounds()))
        {
            Ufo *ufo = dynamic_cast<Ufo *>(itr->get());
            if(ufo != nullptr)
            {
                pocisk->dodaj_punkty(10);
                itr = obiekty.erase(itr);
                itr2 = pociski.erase(itr2);
                std::cout << "ZNISZCZONO UFO! +10 PKT" << std::endl;


            }
            Asteroid *asteroid = dynamic_cast<Asteroid *>(itr->get());
            if(asteroid != nullptr)
            {
                pocisk->dodaj_punkty(20);
                itr = obiekty.erase(itr);
                itr2 = pociski.erase(itr2);
                std::cout << "ZNISZCZONO ASTEROIDE! +20 PKT" << std::endl;                
            }
            }
            else
            {
             itr++;

            }
        }
        else
        {
         itr2++;
        }
      }
    }
}
