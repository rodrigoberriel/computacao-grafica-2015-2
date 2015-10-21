#include "Circle.h"

Circle::Circle()
{
    this->numeroDePontos = 360;
}

Circle::Circle(int _x, int _y, int _raio, Cor _cor)
{
    this->posicao.x = _x;
    this->posicao.y = _y;
    this->raio = _raio;
    this->cor = _cor;
    this->numeroDePontos = 360;
}

void Circle::Draw()
{
    // calcula os pontos de acordo com a quantidade escolhida e desenha o círculo
    glColor3f(cor.r, cor.g, cor.b);
	glBegin(GL_POLYGON);
        float angulo, x, y;
        for (int i = 0; i < numeroDePontos; i++)   {
            // angulo = 2*pi*
            angulo = 2.0f * 3.1415926f * i / float(numeroDePontos);
            x = raio * cosf(angulo);
            y = raio * sinf(angulo);
            glVertex2f(x + posicao.x, y + posicao.y);
        }
	glEnd();
}

bool Circle::estaDentro(Ponto p)
{
    return (calculaDistancia(p, this->posicao) < this->raio);
}
