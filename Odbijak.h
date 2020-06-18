#ifndef ODBIJAK_H
#define ODBIJAK_H
#include <SFML/Graphics.hpp>

class Odbijak : public sf::Drawable
{
public:
    Odbijak(float X, float Y);
    ~Odbijak() {}

    void update();
    float Lewo();
    float Prawo();
    float Gora();
    float Dol();


    float get_wysokosc();
    float get_szerokosc();
    void set_pozycja(float x, float y);
    virtual void draw(sf::RenderTarget& cel, sf::RenderStates etap) const;

private:
    sf::RectangleShape odbijak;
    sf::Texture texture;
    const float predkosc_odbijaka = 8.0f; //predkosc ruchu odbijaka w plaszczyznie
    sf::Vector2f predkosc = sf::Vector2f(predkosc_odbijaka, 0.f); //druga wlozedna y=0 bo porusza sie tylko po osi x
    //stale wymiary odbiajak
    const float szerokosc_odbijaka = 120.0f;
    const float wysokosc_odbijaka = 20.0f;

};

#endif

