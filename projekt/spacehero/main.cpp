//Sekcja bibliotek ogolnych
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <memory>
#include <utility>
#include <sstream>

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

//CO JESZCZE DODAĆ:
//MUZYKA
//DZWIEK PRZY ZDERZENIU UFO,ASTEROIDA
//LICZNIK PUNKTOW ZEBY SIE WYSWIETLAL -> zrobione
//WIZUALIZACJA PKT ZYCIA
//OBSZAR DO KTOREGO DAZA PRZECIWNICY -> PRZEKROCZENIE = STRATA ZYCIA
//UZUPELNIC OKNA AUTORA I OPISU
//ZWIEKSZYC POZIOM TRUDNOSCI NA POZIOMIE 2
//DODAC ZABEZPIECZENIA


void wygrana()
{

}

void poziom_2()
{
    srand(time(NULL));
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

    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text wyniki;
    wyniki.setFont(font);
    wyniki.setCharacterSize(24);
    wyniki.setFillColor(sf::Color::Red);
    wyniki.setStyle(sf::Text::Bold);

    sf::Text punkty;
    punkty.setFont(font);
    punkty.setString("Twoje punkty: ");
    punkty.setCharacterSize(24);
    punkty.setFillColor(sf::Color::Red);
    punkty.setStyle(sf::Text::Bold);

    wyniki.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2);
    punkty.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2);


    //Wspolny kontener na przeciwnikow
    std::vector<std::unique_ptr<AnimowaneObiekty>> przeciwnicy;

    //Kontener pociskow
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski;

    //Dodanie przeciwnikow do kontenera
    dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);

    dodaj_pociski(pociski, textureShot, statek);

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

                  for(auto itr=pociski.begin(); itr != pociski.end(); itr++)
                  {
                      shot *pocisk = dynamic_cast<shot *>(itr->get());
                              if(pocisk != nullptr){
                                  pocisk->strzal(event, statek);                                  
                              }

                  }

              }


          }
              //SEKCJA OD PORUSZANIA
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
               statek.ruch_po_x(elapsed, window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
              {
              statek.ruch_po_x(elapsed, window, 1);
              }


              for(auto &poc : pociski)
              {
              poc->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }


              for(auto &el : przeciwnicy)
              {
                  el->poruszaj(elapsed,windowBounds, rozmiar_x, rozmiar_y);
              }

              zderzenia(statek, pociski, przeciwnicy, rozmiar_x, rozmiar_y, textureUfo, textureAsteroida);

            if(statek.pobierz_liczbe_punktow() >= 250)
            {
                window.close();

                std::cout << "WYGRANA!" << std::endl;
            }
            wyniki.setString(std::to_string(statek.pobierz_liczbe_punktow()));

          // clear the window with black color
          window.clear(sf::Color::Black);

          //RYSOWANIE
          window.draw(spritetlo);
          window.draw(statek);
          window.draw(wyniki);
          window.draw(punkty);


          for(auto &p : przeciwnicy)
          {
              window.draw(*p);
          }

          for(auto &p : pociski)
          {
              window.draw(*p);
          }

          // end the current frame
          window.display();
    }
}

void ekran_wygranej()
{
    sf::Texture textureTlo = loadTexture("./../spacehero/tlo.png");
    sf::Texture textureDalej = loadTexture("./../spacehero/kolejny.png");

    //Rozmiar okna
    int rozmiar_x =  1080;
    int rozmiar_y =  720;

    //Okno
    sf::RenderWindow window(sf::VideoMode(rozmiar_x, rozmiar_y), "SpaceHero");

    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0, 1.0);
    spritetlo.setTextureRect(windowBounds);

    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text text;

    //Stworzenie fontu
    text.setFont(font);
    text.setString("WYGRANA!");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);


    text.setPosition(rozmiar_x/2 - 150, rozmiar_y/2 - rozmiar_y/2);

    //Przyciski
    przycisk przyciskKolejny(textureDalej, rozmiar_x, rozmiar_y);
    przyciskKolejny.setPosition(rozmiar_x/2 - 75, rozmiar_y/2 - 100);


    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

             //Wcisniecie przyciskow
            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f pozycja_myszki = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(przyciskKolejny.czy_wcisniety(pozycja_myszki))
                    {
                        std::cout << "Wcisnieto KOLEJNY POZIOM" << std::endl;
                        window.close();
                        poziom_2();
                    }
                }
            }

            }




        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(spritetlo);
        window.draw(text);
        window.draw(przyciskKolejny);



        // end the current frame
        window.display();
    }
}

void gra()
{
    srand(time(NULL));
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


    //Wspolny kontener na przeciwnikow
    std::vector<std::unique_ptr<AnimowaneObiekty>> przeciwnicy;

    //Kontener pociskow
    std::vector<std::unique_ptr<AnimowaneObiekty>> pociski;

    //Dodanie przeciwnikow do kontenera
    dodaj_przeciwnikow_1(przeciwnicy, textureUfo, textureAsteroida, rozmiar_x, rozmiar_y);

    dodaj_pociski(pociski, textureShot, statek);

    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text wyniki;
    wyniki.setFont(font);
    wyniki.setCharacterSize(24);
    wyniki.setFillColor(sf::Color::Red);
    wyniki.setStyle(sf::Text::Bold);

    sf::Text punkty;
    punkty.setFont(font);
    punkty.setString("Twoje punkty: ");
    punkty.setCharacterSize(24);
    punkty.setFillColor(sf::Color::Red);
    punkty.setStyle(sf::Text::Bold);

    wyniki.setPosition((rozmiar_x/2 - rozmiar_x/2) + 200, rozmiar_y/2 - rozmiar_y/2);
    punkty.setPosition(rozmiar_x/2 - rozmiar_x/2 , rozmiar_y/2 - rozmiar_y/2);


//////////////////////////////////////////////////////////////////////////////////////
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

                  for(auto itr=pociski.begin(); itr != pociski.end(); itr++)
                  {
                      shot *pocisk = dynamic_cast<shot *>(itr->get());
                              if(pocisk != nullptr){
                                  pocisk->strzal(event, statek);
                              }
                  }

              }

          }
              //SEKCJA OD PORUSZANIA
              if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
              {
               statek.ruch_po_x(elapsed, window,-1);
              }
              else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
              {
              statek.ruch_po_x(elapsed, window, 1);
              }


              for(auto &poc : pociski)
              {
              poc->poruszaj(elapsed, windowBounds, rozmiar_x, rozmiar_y);
              }


              for(auto &el : przeciwnicy)
              {
                  el->poruszaj(elapsed,windowBounds, rozmiar_x, rozmiar_y);
              }

              zderzenia(statek, pociski, przeciwnicy, rozmiar_x, rozmiar_y, textureUfo, textureAsteroida);

            //Wyswietlenie punktow
            wyniki.setString(std::to_string(statek.pobierz_liczbe_punktow()));

            if(statek.pobierz_liczbe_punktow() >= 250)
            {
                window.close();
                ekran_wygranej();
                std::cout << "NASTEPNY POZIOM!" << std::endl;
            }

          // clear the window with black color
          window.clear(sf::Color::Black);

          //RYSOWANIE
          window.draw(spritetlo);
          window.draw(statek);
          window.draw(wyniki);
          window.draw(punkty);


          for(auto &p : przeciwnicy)
          {
              window.draw(*p);
          }

          for(auto &p : pociski)
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

    //Gif
    sf::Texture giff = loadTexture("./../spacehero/sweet.gif");

    sf::Sprite giff_s;
    giff_s.setTexture(giff);
    giff_s.setPosition(rozmiar_x/2 - 100, rozmiar_y/2);
    giff_s.setScale(1.5,1.5);

    //Fonty
    sf::Font font;
    if(!font.loadFromFile("./../spacehero/arial.ttf"))
    {
        std::cerr << "Nie udalo sie wczytac fontu!" << std::endl;
    }

    sf::Text text;
    sf::Text text_2;
    sf::Text text_3;

    //Stworzenie fontu i ustawienie
    text.setFont(font);
    text.setString("AUTOR");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    //Opis autora
    text_2.setFont(font);
    text_2.setString("Maciej Dyks");
    text_2.setCharacterSize(24);
    text_2.setFillColor(sf::Color::Red);
    text_2.setStyle(sf::Text::Bold);
    //Rok powstania
    text_3.setFont(font);
    text_3.setString("Gra powstala w 2022 roku, II semestr PSiO");
    text_3.setCharacterSize(24);
    text_3.setFillColor(sf::Color::Red);
    text_3.setStyle(sf::Text::Bold);


    //Granice okna
    sf::IntRect windowBounds(0, 0, window.getSize().x, window.getSize().y);

    textureTlo.setRepeated(true);

    sf::Sprite spritetlo;
    spritetlo.setTexture(textureTlo);
    spritetlo.setScale(1.0,1.0);
    spritetlo.setTextureRect(windowBounds);


    text.setPosition(rozmiar_x/2 - 50, rozmiar_y/2 - rozmiar_y/2);
    text_2.setPosition(rozmiar_x/2 - 75, rozmiar_y/2 - rozmiar_y/2 + 25);
    text_3.setPosition(rozmiar_x/2 - 300, rozmiar_y/2 - rozmiar_y/2 + 65);

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
        window.draw(text);
        window.draw(text_2);
        window.draw(text_3);
        window.draw(giff_s);



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
