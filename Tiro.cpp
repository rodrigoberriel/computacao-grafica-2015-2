#include "Tiro.h"

Tiro::Tiro(Ponto _posicao, Ponto _direcao, std::string _id_jogador, double _velocidade)
{
    this->posicao = _posicao;
    this->direcao = _direcao;
    this->raio = 5;
    this->cor = Cor("black");
    this->id_jogador = _id_jogador;
    this->velocidade = _velocidade;
}

void Tiro::Draw(int flag)
{
    Circle(posicao, raio, cor).Draw(flag);
    /*
    if (flag == DRAW_2D) {
        // calcula os pontos de acordo com a quantidade escolhida e desenha o círculo
        glColor3f(cor.r, cor.g, cor.b);
        glBegin(GL_POLYGON);
            float angulo, x, y;
            for (int i = 0; i < 360; i++)   {
                // angulo = 2*pi*
                angulo = 2.0f * 3.1415926f * i / float(360);
                x = raio * cosf(angulo);
                y = raio * sinf(angulo);
                glVertex2f(x + posicao.x, y + posicao.y);
            }
        glEnd();
    } else {
        Circle(posicao.x, posicao.y, raio, cor).Draw(flag);
    }*/
}

void Tiro::Mover(GLdouble timeDiff)
{
    posicao.x += velocidade * direcao.x * timeDiff;
    posicao.y += velocidade * direcao.y * timeDiff;
    posicao.z += velocidade * direcao.z * timeDiff;
}

bool Tiro::estaDentro(int larguraMapa, int alturaMapa)
{
    bool dentroX = (posicao.x > -raio && posicao.x < larguraMapa + raio);
    bool dentroY = (posicao.y > -raio && posicao.y < alturaMapa + raio);
    return (dentroX && dentroY);
}

void Tiro::setCor(Cor _cor)
{
    cor = _cor;
}
