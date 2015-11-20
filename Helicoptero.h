#ifndef HELICOPTERO_H
#define HELICOPTERO_H


#include <GL/glut.h>
#include <math.h>

#include "Rect.h"
#include "Circle.h"
#include "Tiro.h"
#include "EstruturasBasicas.h"

/** CORES (RGB)
 * Verde claro:     155, 187, 89
 * Verde escuro:    99, 169, 117
 * Azul:            79, 129, 189
 */

 #define ALTURA_HELICOPTERO 20
 #define HELICE_VEL_MAXIMA 3.0
 #define HELICE_VEL_MINIMA 0.0

class Helicoptero
{
    public:
        Helicoptero();
        //Helicoptero(float _velocidadeHelice, float _velocidadeHelicoptero, float _velocidadeTiro);
        void moverFrente(GLdouble timeDiff); // OK
        void moverTras(GLdouble timeDiff); // OK
        void girarDireita(); // OK
        void girarEsquerda(); // OK

        void moverCanhao(int incrementoYaw, int incrementoPitch);
        void girarHelice(); // OK
        void decolar(); // OK
        void pousar(); // OK
        void subir(); // OK
        void descer(); // OK
        void aumentarVelocidadeHelice(); // OK
        void diminuirVelocidadeHelice(); // OK
        void mirar(Ponto alvo);
        Tiro atirar();
        bool estaVoando(); // OK
        void consumirCombustivel(GLdouble timeDiff); // OK
        void reabastercer(); // OK
        bool resgatar(Circle objeto); // OK
        double getNivelCombustivel(); // OK
        void ajustarAngulo();

        // desenho
        void desenharCombustivel(float _posicaoX, float _posicaoY, int _numeroDeMostradores); // OK
        void desenharResgates(float _posicaoX, float _posicaoY, int _nObjetos); // OK
        void desenharHelice(Textura *textura); // OK
        void desenharCorpo(Textura *textura); // OK
        void desenharCanhao(Textura *textura); // OK
        void Draw(int flag = DRAW_2D, Textura *corpo = NULL, Textura *helice = NULL, Textura *canhao = NULL); // OK
        void desenharEsfera() { desenhaEsfera = !desenhaEsfera; } // OK

        Circle area;
        std::string id;
        float velocidadeHelicoptero, velocidadeTiro;
        float tempoMaximoDeVoo, tempoAtualDeVoo;
        float angulo;
        int objetosResgatados;
        Cor corCorpo;
        Textura texturaCorpo, texturaHelice, texturaCanhao;

        Ponto getPosicao() { return area.posicao; };
        Ponto getDirecao();
        Ponto getProximaPosicao(GLdouble timeDiff);
        void getInfoCanhao(Ponto &pontaCanhao, Ponto &direcao);
    protected:
    private:
        float anguloCanhaoYaw, anguloCanhaoPitch, anguloHelice;
        float velocidadeHelice;
        bool voando;
        bool draw3d = false;
        bool desenhaEsfera = false;
};

#endif // HELICOPTERO_H
