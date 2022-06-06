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
void zderzenia(Spaceship &statek, std::vector<std::unique_ptr<AnimowaneObiekty>> &pociski, std::vector<std::unique_ptr<AnimowaneObiekty>> &obiekty, int rozmiar_x, int rozmiar_y, sf::Texture &textureUfo, sf::Texture &textureAsteroid)
{

    for(auto itr1 = pociski.begin(); itr1 != pociski.end(); itr1++)
    {
        shot *pociski = dynamic_cast<shot *>(itr1->get());
        for(auto itr2 = obiekty.begin(); itr2 != obiekty.end(); itr2++)
        {
            Ufo *ufo = dynamic_cast<Ufo *>(itr2->get());
          if(ufo != nullptr)
          {
              if((*itr1)->getGlobalBounds().intersects((*itr2)->getGlobalBounds()))
              {
              statek.dodaj_punkty(10);
              itr2 = obiekty.erase(itr2);

              itr1--;

              std::cout << "Zniszczono ufo, +10 PKT!" <<std::endl;
              break;
              }
        }
          Asteroid *asteroid = dynamic_cast<Asteroid *>(itr2->get());
          if(asteroid != nullptr)
          {
              if((*itr1)->getGlobalBounds().intersects((*itr2)->getGlobalBounds()))
              {
                  statek.dodaj_punkty(20);
                  //obiekty.erase(itr2);
                  itr2 = obiekty.erase(itr2);


                  itr1--;

                  std::cout << "Zniszczono asteroide, +20 PKT!" <<std::endl;
                  break;
              }

        }
        }
    }
}

