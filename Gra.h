#ifndef GRA_H
#define GRA_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Pilka.h"
#include"Odbijak.h"
#include"Cegielka.h"
#include"Autor.h"
class Gra

{
public:
    Gra(void);
    ~Gra(void);

    void Uruchom_Gre();//funckja wywolana w main
    void update();//aktualizuje na bierzaco etapy gry
    void dodawnie_puntkow();//funckja dodajaca punkty
    bool kolizjaTest(Cegielka* cegielka, Pilka *pilka, int &liczbaBlokow);
     bool kolizjaTest_2(Cegielka* cegielka, Pilka *pilka, int &liczbaBlokow);
    bool dzwiek_odbijaka=false;
protected:
    enum EtapGry {MENU, GRA, GRA_2, PRZEGRANA, KONIEC, WYGRANA_1, WYGRANA_2, PAUZA, AUTOR};//enum EtapyGry umozliwiajacy szybie i wygodne uruchamianie poszczegolnych funckji
    EtapGry state;
private:
    sf::Font font;
   //deklaracja zmiennych zycia oraz poczatkowe wartosci
    int *zycie = NULL;
    int *pkt = NULL;
   //tekstury i sprite
    sf::Texture tekstura;
    sf::Texture tekstura1;
    sf::Texture tekstura_bloczka;
    sf::Sprite sprite_tlo1;
    sf::Sprite sprite_tlo2;
    sf::String napis;
    sf::String napis_koniec;
    sf::Text text;
    sf::RenderWindow *window;
    sf::Sound sound;
    sf::SoundBuffer buffer;
    sf::Sound sound2;
    sf::SoundBuffer buffer2;
    sf::Sound sound3;
    sf::SoundBuffer buffer3;
    sf::Sound sound4;
    sf::SoundBuffer buffer4;
    sf::Sound sound5;
    sf::SoundBuffer buffer5;
    //wskazniki do latwiejszego wywolywania funkcji
    Pilka *pilka;
    Odbijak *odbijak;

    void menu(sf::RenderWindow *window);
    void Poczatek(sf::RenderWindow *window);
    void Poczatek2(sf::RenderWindow *window);//poziom 2
    void Przegrana(sf::RenderWindow *window);
    void Wygrana_1(sf::RenderWindow *window);
    void Wygrana_2(sf::RenderWindow *window);
    void Autor(sf::RenderWindow *window);

};


#endif

