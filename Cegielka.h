#ifndef CEGIELKA_H
#define CEGIELKA_H
#include <SFML/Graphics.hpp>

class Cegielka :
        public sf::Drawable //deklaracja umożliwiajaca wykorzystanie sprite i tekstu
{
public:
    Cegielka(float X, float Y, float szerokosc, float wysokosc, sf::Texture &texture); //deklaracja konstruktora pozycji, wymiarow i tekstury cegielki
   ~Cegielka() {}
    //ruch
    float Lewo();
    float Prawo();
    float Gora();
    float Dol();
    //deklaracje funkcji rozbicia cegielki pilka
    bool get_rozbij();
    void set_zbij();
    //wirtualna funkcja rysujaca cegielki
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

private:
    sf::RectangleShape cegielka; //nadanie kszaltu celgielce
    bool visible = false; //cegielka poczatkowo nie widoczna
};

#endif

