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
#include "spaceship.h"
#include "ufo.h"
#include "asteroid.h"
#include "przycisk.h"
#include "shot.h"
#include "funkcje.h"

using namespace std;

void gra()
{
    //Tekstury
    sf::Texture textureStatek = loadTexture("./../spacehero/spaceship.png");
    sf::Texture textureTlo = loadTexture("./../spacehero/tlo.png");
    sf::Texture textureUfo = loadTexture("./../spacehero/ufo.png");
    sf::Texture textureAsteroida = loadTexture("./../spacehero/asteroid.png");
    sf::Texture textureShot = loadTexture("./../spacehero/shot.png");

    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;

    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    //Utworzenie obiektu klasy spaceship
    Spaceship statek(textureStatek, rozmiar_x, rozmiar_y);

    //test pocisk
    shot pocisk(textureShot, rozmiar_x, rozmiar_y);



    //Wspolny kontener na przeciwnikow
    std::vector<std::unique_ptr<AnimowaneObiekty>> przeciwnicy;

    //Wspolny kontener na pocisk i statek
    std::vector<std::unique_ptr<AnimowaneObiekty>> statek_pocisk;

    //Dodanie przeciwnikow do kontenera
    dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);

      // run the program as long as the window is open
    sf::Clock clock;
    sf::Clock shot_clock;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;
          sf::Time elapsed = clock.restart();

          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();
              //Sterowanie statkiem za pomoca klawiszy
              if(event.type == sf::Event::KeyPressed)
              {
                  statek.sterowanie_klawiszami(event);


              }
              if(event.type == sf::Event::KeyPressed)
              {
                  pocisk.strzal(event);

              }

          }
              statek.poruszaj(elapsed, windowBounds,rozmiar_x, rozmiar_y);
              pocisk.poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              for(auto &el : przeciwnicy)
              {
                  el->poruszaj(elapsed,windowBounds, rozmiar_x, rozmiar_y);
              }

          // clear the window with black color
          window.clear(sf::Color::Black);

          // draw everything here...
          window.draw(spritetlo);
          window.draw(statek);
          //window.draw(pocisk);

          for(auto &p : przeciwnicy)
          {
              window.draw(*p);
          }


          // end the current frame
          window.display();
      }
}

void opis()
{
    //Tekstury
    sf::Texture textureTlo = loadTexture("./../spacehero/tlo.png");

    //Rozmiar okna
    int rozmiar_x = 600;
    int rozmiar_y = 600;

    //Utworzenie okna
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            }




        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(spritetlo);



        // end the current frame
        window.display();
    }
}

void autor()
{
    //Tekstury
    sf::Texture textureTlo = loadTexture("./../spacehero/tlo.png");

    //Rozmiar okna
    int rozmiar_x = 600;
    int rozmiar_y = 600;

    //Utworzenie okna
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            }




        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(spritetlo);



        // end the current frame
        window.display();
    }

}


void okno_startowe()
{

    //Tekstury
    sf::Texture textureTlo = loadTexture("./../spacehero/tlotytul.png");
    sf::Texture textureGraj = loadTexture("./../spacehero/graj.png");
    sf::Texture textureOpis = loadTexture("./../spacehero/opis.png");
    sf::Texture textureAutor = loadTexture("./../spacehero/autor.png");


    //Rozmiar okna gry
    int rozmiar_x = 1080;
    int rozmiar_y = 720;

    //Utworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    //Granice okna gry
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    //Ustawienie tekstury tla na cale okno
    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);

    //Przyciski
    przycisk przyciskGraj(textureGraj, rozmiar_x, rozmiar_y);
    przycisk przyciskOpis(textureOpis, rozmiar_x, rozmiar_y + rozmiar_y/6);
    przycisk przyciskAutor(textureAutor, rozmiar_x, rozmiar_y + rozmiar_y/3);



    sf::Clock clock;
    window.setFramerateLimit(60);
      while (window.isOpen()) {
          // check all the window's events that were triggered since the last iteration of the loop
          sf::Event event;
          sf::Time elapsed = clock.restart();

          while (window.pollEvent(event)) {
              // "close requested" event: we close the window
              if (event.type == sf::Event::Closed)
                  window.close();

              //Wcisniecie przyciskow
              if (event.type == sf::Event::MouseButtonPressed){
                  sf::Vector2f pozycja_myszki = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                  if(event.mouseButton.button == sf::Mouse::Left){
                      if(przyciskGraj.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto GRAJ" << std::endl;
                         window.close();
                          gra();

                      }
                      if(przyciskOpis.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto Opis" << std::endl;
                          opis();
                      }
                      if(przyciskAutor.czy_wcisniety(pozycja_myszki))
                      {
                          std::cout << "Wcisnieto Autor" << std::endl;
                          autor();
                      }
              }

}


          // clear the window with black color
          window.clear(sf::Color::Black);

          // draw everything here...
          window.draw(spritetlo);
          window.draw(przyciskGraj);
          window.draw(przyciskOpis);
          window.draw(przyciskAutor);


          // end the current frame
          window.display();
      }
}
}

int main()
{
    okno_startowe();
    return 0;
}
