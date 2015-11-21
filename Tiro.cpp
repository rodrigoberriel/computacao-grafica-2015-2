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

void Tiro::Draw(int flag, Textura *_textura)
{
    if (_textura != NULL) this->textura = *_textura;

    Circle t = Circle(posicao, raio, cor);
    t.textura = textura;
    t.Draw(flag, _textura);
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
