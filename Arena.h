#ifndef ARENA_H
#define ARENA_H

#include <iostream>
#include <map>
#include <cmath>
#include "EstruturasBasicas.h"
#include "Rect.h"
#include "Circle.h"
#include "Helicoptero.h"

enum {
    CAMERA_1,
    CAMERA_2,
    CAMERA_3
};

class Arena
{
    public:
        Arena();
        Rect mapa;
        Rect postoAbastecimento;
        Helicoptero jogador;
        std::vector<Helicoptero> inimigos;
        std::vector<Circle> objetosResgate;
        std::vector<Tiro> tiros;

        int camera;
        double camYaw;
        double camPitch;
        double camDistanciaHelicoptero;
        void defineCamera(bool desenhaCockpit = false);

        void defineLuz0(bool desenha = false);

        std::map<std::string, Cor> mapaCorID;

        int nObjetos;
        int nInimigos;
        int statusPartida;
        double frequenciaTiro; // tiros por milissegundos
        double getIntervaloEntreTiros() { return 1.0 / frequenciaTiro; };

        void Draw();
        void MostraDados();
        void ImprimeElemento(Cor corElemento);
        void exibeResultado();
        bool estaDentro(Tiro tiro);
        bool mostrarCameraCockpit = false;
    protected:
    private:
        double velTiro;
        double velHelicoptero;
        void mostrarMensagem();
        void desenhaOrigemDoSC();
};

#endif // ARENA_H
