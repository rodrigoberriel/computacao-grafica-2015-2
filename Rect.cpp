#include "Rect.h"

using namespace std;

Rect::Rect()
{
}

Rect::Rect(int _x, int _y, int _largura, int _altura, Cor _cor)
{
    posicao.x = _x;
    posicao.y = _y;
    posicao.z = 0;
    altura = _altura;
    largura = _largura;
    cor = _cor;
    strokeLargura = 1;
    strokeCor = Cor(127, 127, 127);
}

void Rect::Draw(int flag, Textura *_textura, bool drawStroke)
{
    if (_textura != NULL) this->textura = *_textura;

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
        double textureS = fatorRepeticaoTextura; // Bigger than 1, repeat
        glPushMatrix();
            glColor3f(cor.r, cor.g, cor.b);
            if (_textura != NULL) glBindTexture (GL_TEXTURE_2D, this->textura.get());
            glBegin (GL_POLYGON);
                glNormal3f(0,0,1);
                glTexCoord2f (0, 0);
                glVertex3f (vertices[0].x, vertices[0].y, std::abs(vertices[0].z));
                glTexCoord2f (0, textureS);
                glVertex3f (vertices[1].x, vertices[1].y, std::abs(vertices[1].z));
                glTexCoord2f (textureS, textureS);
                glVertex3f (vertices[2].x, vertices[2].y, std::abs(vertices[2].z));
                glTexCoord2f (textureS, 0);
                glVertex3f (vertices[3].x, vertices[3].y, std::abs(vertices[3].z));
            glEnd();
        glPopMatrix();
    }
}

void Rect::DrawArestas()
{
    vector<Ponto> vertices = getVertices();
    glPointSize(strokeLargura);
    glBegin(GL_LINE_LOOP);
        Cor c = Cor("lightgray");
        glColor3f(c.r, c.g, c.b);
        for (Ponto v : vertices) glVertex2f(v.x, v.y);
    glEnd();
}

vector<Ponto> Rect::getVertices()
{
    vector<Ponto> vertices;
    vertices.push_back(posicao);
    vertices.push_back(Ponto(posicao.x + largura, posicao.y, posicao.z));
    vertices.push_back(Ponto(posicao.x + largura, posicao.y + altura, posicao.z));
    vertices.push_back(Ponto(posicao.x, posicao.y + altura, posicao.z));
    return vertices;
}

bool Rect::estaDentro(Ponto p)
{
    bool h = (p.x >= posicao.x && p.x <= posicao.x + largura);
    bool v = (p.y >= posicao.y && p.y <= posicao.y + altura);
    return (h && v);
}

void Rect::DrawCubo(Rect *r, float profundidade, float textureS)
{
    Ponto _posicao = r->posicao;
    float _altura = r->altura;
    float _largura = r->largura;
    int inverterNormal = 1;

    glPushMatrix();
        glTranslatef(0,0,_posicao.z * inverterNormal);
        glColor3f(r->cor.r, r->cor.g, r->cor.b);
        glBindTexture (GL_TEXTURE_2D, r->textura.get());

        glBegin(GL_POLYGON);/* f1: front */
        glNormal3f(-1.0f * inverterNormal,0.0f,0.0f);

        glTexCoord2f (textureS, 0);
        glVertex3f(_posicao.x,_posicao.y,0.0f);
        glTexCoord2f (textureS, textureS);
        glVertex3f(_posicao.x,_posicao.y,profundidade);
        glTexCoord2f (0, textureS);
        glVertex3f(_posicao.x + _largura,_posicao.y,profundidade);
        glTexCoord2f (0, 0);
        glVertex3f(_posicao.x + _largura,_posicao.y,0.0f);
        glEnd();

        glBegin(GL_POLYGON);/* f2: bottom */
        glNormal3f(0.0f,0.0f,-1.0f * inverterNormal);

        glTexCoord2f (textureS, 0);
        glVertex3f(_posicao.x,_posicao.y,0.0f);
        glTexCoord2f (textureS, textureS);
        glVertex3f(_posicao.x + _largura,_posicao.y,0.0f);
        glTexCoord2f (0, textureS);
        glVertex3f(_posicao.x + _largura,_posicao.y + _altura,0.0f);
        glTexCoord2f (0, 0);
        glVertex3f(_posicao.x,_posicao.y + _altura,0.0f);
        glEnd();

        glBegin(GL_POLYGON);/* f3:back */
        glNormal3f(1.0f * inverterNormal,0.0f,0.0f);

        glTexCoord2f (textureS, 0);
        glVertex3f(_posicao.x + _largura,_posicao.y + _altura,0.0f);
        glTexCoord2f (textureS, textureS);
        glVertex3f(_posicao.x + _largura,_posicao.y + _altura,profundidade);
        glTexCoord2f (0, textureS);
        glVertex3f(_posicao.x,_posicao.y + _altura,profundidade);
        glTexCoord2f (0, 0);
        glVertex3f(_posicao.x,_posicao.y + _altura,0.0f);
        glEnd();

        glBegin(GL_POLYGON);/* f4: top */
        glNormal3f(0.0f,0.0f,1.0f * inverterNormal);

        glTexCoord2f (textureS, 0);
        glVertex3f(_posicao.x + _largura,_posicao.y + _altura,profundidade);
        glTexCoord2f (textureS, textureS);
        glVertex3f(_posicao.x + _largura,_posicao.y,profundidade);
        glTexCoord2f (0, textureS);
        glVertex3f(_posicao.x,_posicao.y,profundidade);
        glTexCoord2f (0, 0);
        glVertex3f(_posicao.x,_posicao.y + _altura,profundidade);
        glEnd();

        glBegin(GL_POLYGON);/* f5: left */
        glNormal3f(0.0f,1.0f * inverterNormal,0.0f);

        glTexCoord2f (0, 0);
        glVertex3f(_posicao.x,_posicao.y,0.0f);
        glTexCoord2f (textureS, 0);
        glVertex3f(_posicao.x,_posicao.y + _altura,0.0f);
        glTexCoord2f (textureS, textureS);
        glVertex3f(_posicao.x,_posicao.y + _altura,profundidade);
        glTexCoord2f (0, textureS);
        glVertex3f(_posicao.x,_posicao.y,profundidade);
        glEnd();

        glBegin(GL_POLYGON);/* f6: right */
        glNormal3f(0.0f,-1.0f * inverterNormal,0.0f);

        glTexCoord2f (textureS, 0);
        glVertex3f(_posicao.x + _largura,_posicao.y,0.0f);
        glTexCoord2f (textureS, textureS);
        glVertex3f(_posicao.x + _largura,_posicao.y,profundidade);
        glTexCoord2f (0, textureS);
        glVertex3f(_posicao.x + _largura,_posicao.y + _altura,profundidade);
        glTexCoord2f (0, 0);
        glVertex3f(_posicao.x + _largura,_posicao.y + _altura,0.0f);
        glEnd();
    glPopMatrix();
}
