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
        Rect ceu;
        Rect postoAbastecimento;
        Helicoptero jogador;
        std::vector<Helicoptero> inimigos;
        std::vector<Circle> objetosResgate;
        std::vector<Tiro> tiros;
        std::map<std::string, Textura> texturas;

        int camera;
        double camYaw;
        double camPitch;
        double camDistanciaHelicoptero;
        void defineCamera(bool desenhaCockpit = false);

        void defineLuz0();
        void defineLuz1();

        std::map<std::string, Cor> mapaCorID;

        int nObjetos;
        int nInimigos;
        int statusPartida;
        double frequenciaTiro; // tiros por milissegundos
        double getIntervaloEntreTiros() { return 1.0 / frequenciaTiro; };

        void Draw(bool cockpitPermanente = false);
        void DrawArena();
        void DrawIndicadores();
        void DrawMiniMapa(float _w, float _h);
        void DrawOrtho(void (Arena::*funcao)(), bool desabilitarTextura = true, bool desabilitarLuz = true);
        void DrawResultado();
        void MostraDados();
        void ImprimeElemento(Cor corElemento);
        void exibeResultado();
        bool estaDentro(Tiro tiro);
        bool mostrarCameraCockpit = false;
        bool ativaLuz0 = true;
        bool ativaLuz1 = true;
        bool mostrarMinimapa = false;
    protected:
    private:
        double velTiro;
        double velHelicoptero;
        void desenhaOrigemDoSC();
};

#endif // ARENA_H
