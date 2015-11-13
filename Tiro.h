#ifndef TIRO_H
#define TIRO_H

#include <GL/glut.h>
#include <math.h>

#include "EstruturasBasicas.h"
#include "Circle.h"

class Tiro
{
    public:
        Tiro(Ponto _posicao, Ponto _direcao, std::string id_jogador, double _velocidade);
        void Draw(int flag = DRAW_2D);
        void Mover(GLdouble timeDiff);
        bool estaDentro(int larguraMapa, int alturaMapa);
        Ponto posicao;
        Ponto direcao;
        std::string id_jogador;
        double velocidade;
        void setCor(Cor _cor);
        int raio;
    protected:
    private:
        Cor cor;

};

#endif // TIRO_H
