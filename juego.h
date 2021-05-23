
#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "jugador.h"

#include <SFML/Window/Keyboard.hpp>
#include <string.h>
using namespace sf;

class juego
{
public:
    juego();
    void iniciar();
    void palabraalaealtoria(char *);
    void renderizar(int, int=0);
    int procesar_logica(char*, int);
    int colision(int );
    void procesar_eventos(char *, int, int);
    void procesar_eventos2(char *, int, int);
    void guardardatos();
    void gameloop();
    int mainmenu();
    void setvidas( );
    int getvidas ();
    void gameover();
    void puntajes();
    void configuracion();
    void reiniciarvidas();
    void  puntajesmax();
void creararchivo();
    virtual ~juego();



protected:
    class    jugador *j1;

    class jugador *vector_jugador;
    FILE *parch;
    SoundBuffer * buffer;
    Sound * sound;
    SoundBuffer*moneda;
    Sound*moneda1;
    SoundBuffer*fin;
    Sound * fin1;
    SoundBuffer*error;
    Sound * error1;
    RenderWindow *ventana;
    Texture * textura1;
    Sprite  * sprite1;
    Texture *texturacorazon;
    Sprite *spritecorazon;
    Texture *textuimagenconfiguracion;
    Sprite *spriteimagenconfiguracion;
    Texture *texturabotonatras;
    Sprite *spritebotonatras;
    Text *menu;
    Text *puntaje;
    Text *nombrepuntaje;
    Font * fuente;
    Text *vpalabras;
    Text ingreso;
    Event evento;
    int vidas;

    sf::String userInput;
    int *devo;

};

#endif // JUEGO_H
