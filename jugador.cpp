#include "jugador.h"
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
jugador::jugador()
{
    Puntaje=0;
    strcpy(Nombre,"aaa");
    //ctor
}
void jugador:: setNombre(char *aux)
{
    strcpy(Nombre,aux);
}

void jugador::setPuntaje(int num )
{
    Puntaje+=num;
}
int jugador::getPuntaje ()
{
    return Puntaje;
}




jugador::~jugador()
{
    //dtor
}
