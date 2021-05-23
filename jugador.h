#pragma once
#ifndef JUGADOR_H
#define JUGADOR_H
#include "SFML/Graphics.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "juego.h"

using namespace sf;
class jugador
{
protected:
    char Nombre [20];
    int Puntaje;

public:


    jugador();
    void  setNombre(char *);
    char  *getNombre ()
    {
        return Nombre;
    }
    void  setPuntaje(int );
    int  getPuntaje();

    virtual ~jugador();


};

#endif // JUGADOR_H
