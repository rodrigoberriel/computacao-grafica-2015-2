#include "Rect.h"

using namespace std;

Rect::Rect()
{
}

Rect::Rect(int _x, int _y, int _largura, int _altura, Cor _cor)
{
    posicao.x = _x;
    posicao.y = _y;
    altura = _altura;
    largura = _largura;
    cor = _cor;
    strokeLargura = 1;
    strokeCor = Cor(127, 127, 127);
}

void Rect::Draw(int flag, bool drawStroke)
{
    if (flag == DRAW_2D) {
        vector<Ponto> vertices = getVertices();

        // desenha o poligono
        if (vertices.size()  == 4)
        {
            glBegin(GL_POLYGON);
                glColor3f(cor.r, cor.g, cor.b);
                for (Ponto v : vertices) glVertex2f(v.x, v.y);
            glEnd();
        }

        // desenha as arestas
        if (drawStroke && vertices.size() == 4)
        {
            glPointSize(strokeLargura);
            glBegin(GL_LINE_LOOP);
                glColor3f(strokeCor.r, strokeCor.g, strokeCor.b);
                for (Ponto v : vertices) glVertex2f(v.x, v.y);
            glEnd();
        }
    } else {
        vector<Ponto> vertices = getVertices();
        glPushMatrix();
            glColor3f(cor.r, cor.g, cor.b);
            glBindTexture (GL_TEXTURE_2D, this->textura.get());
            double textureS = 10; // Bigger than 1, repeat
            glBegin (GL_POLYGON);
                glNormal3f(0,0,1);
                glTexCoord2f (0, 0);
                glVertex3f (vertices[0].x, vertices[0].y, 0);
                glTexCoord2f (0, textureS);
                glVertex3f (vertices[1].x, vertices[1].y, 0);
                glTexCoord2f (textureS, textureS);
                glVertex3f (vertices[2].x, vertices[2].y, 0);
                glTexCoord2f (textureS, 0);
                glVertex3f (vertices[3].x, vertices[3].y, 0);
            glEnd();
        glPopMatrix();
    }
}


vector<Ponto> Rect::getVertices()
{
    vector<Ponto> vertices;
    vertices.push_back(posicao);
    vertices.push_back(Ponto(posicao.x + largura, posicao.y));
    vertices.push_back(Ponto(posicao.x + largura, posicao.y + altura));
    vertices.push_back(Ponto(posicao.x, posicao.y + altura));
    return vertices;
}

bool Rect::estaDentro(Ponto p)
{
    bool h = (p.x >= posicao.x && p.x <= posicao.x + largura);
    bool v = (p.y >= posicao.y && p.y <= posicao.y + altura);
    return (h && v);
}
