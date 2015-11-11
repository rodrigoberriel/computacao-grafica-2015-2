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

class Helicoptero
{
    public:
        Helicoptero();
        //Helicoptero(float _velocidadeHelice, float _velocidadeHelicoptero, float _velocidadeTiro);
        void moverFrente(GLdouble timeDiff); // OK
        void moverTras(GLdouble timeDiff); // OK
        void girarDireita(); // OK
        void girarEsquerda(); // OK

        void moverCanhao(int incremento);
        void girarHelice(); // OK
        void decolar(); // OK
        void pousar(); // OK
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
        void desenharHelice(); // OK
        void desenharCorpo(); // OK
        void desenharCanhao(); // OK
        void Draw(); // OK
        void Draw3D(); // TESTE
        Circle area;
        std::string id;
        float velocidadeHelicoptero, velocidadeTiro;
        float tempoMaximoDeVoo, tempoAtualDeVoo;
        float angulo;
        int objetosResgatados;
        Cor corCorpo;

        Ponto getPosicao() { return area.posicao; };
        Ponto getDirecao();
        Ponto getProximaPosicao(GLdouble timeDiff);
    protected:
    private:
        float anguloCanhao, anguloHelice;
        float velocidadeHelice;
        bool voando;
};

#endif // HELICOPTERO_H
