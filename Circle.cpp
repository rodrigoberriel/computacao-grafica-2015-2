#include "Circle.h"

Circle::Circle()
{
    this->numeroDePontos = 360;
}

Circle::Circle(Ponto posicao, int _raio, Cor _cor)
{
    this->posicao = posicao;
    this->raio = _raio;
    this->cor = _cor;
    this->numeroDePontos = 360;
}

void Circle::Draw(int flag, Textura *_textura)
{
    if (_textura != NULL) textura = *_textura;

    if (flag == DRAW_2D) {
        // calcula os pontos de acordo com a quantidade escolhida e desenha o círculo
        glColor3f(cor.r, cor.g, cor.b);
        glBegin(GL_POLYGON);
            float angulo, x, y;
            for (int i = 0; i < numeroDePontos; i++) {
                // angulo = 2*pi*
                angulo = 2.0f * 3.1415926f * i / float(numeroDePontos);
                x = raio * cosf(angulo);
                y = raio * sinf(angulo);
                glVertex2f(x + posicao.x, y + posicao.y);
            }
        glEnd();
    } else {
        glPushMatrix();
            glColor3f(cor.r, cor.g, cor.b);
            glTranslatef(posicao.x, posicao.y, posicao.z);
            if (_textura != NULL) glBindTexture(GL_TEXTURE_2D, textura.get());
            DrawEsfera();
        glPopMatrix();
    }
}

bool Circle::estaDentro(Ponto p)
{
    return (calculaDistancia(p, this->posicao) < this->raio);
}

bool Circle::estaTocando(Circle c)
{
    return (calculaDistancia(c.posicao, this->posicao) < (this->raio + c.raio));
}


std::unique_ptr<OBJ> Circle::criaEsfera()
{
	std::unique_ptr<OBJ> obj (new OBJ);
	double space = 18;
	double R = this->raio;

	obj->numVtx = (180 / space) * (360 / space) * 4;
	obj->vtx = new VERTICES[ obj->numVtx ];
	obj->radius = R;

	int n;
	double vR, lVR;
	double hR, lHR;
	double norm;
	n = 0;
	for( vR = 0; vR <= 180-space; vR+=space){
		for(hR = 0; hR <= 360-space; hR+=space)
		{

			lVR = vR;
			lHR = hR;
			obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
			obj->vtx[n].V = lVR / 180;
			obj->vtx[n].U = lHR / 360;
			norm = sqrt(obj->vtx[n].X*obj->vtx[n].X+obj->vtx[n].Y*obj->vtx[n].Y+obj->vtx[n].Z*obj->vtx[n].Z);
			obj->vtx[n].nX = obj->vtx[n].X/norm;
			obj->vtx[n].nY = obj->vtx[n].Y/norm;
			obj->vtx[n].nZ = obj->vtx[n].Z/norm;
			n++;

			lVR = vR + space;
			lHR = hR;
			obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
			obj->vtx[n].V = lVR / 180;
			obj->vtx[n].U = lHR / 360;
			norm = sqrt(obj->vtx[n].X*obj->vtx[n].X+obj->vtx[n].Y*obj->vtx[n].Y+obj->vtx[n].Z*obj->vtx[n].Z);
			obj->vtx[n].nX = obj->vtx[n].X/norm;
			obj->vtx[n].nY = obj->vtx[n].Y/norm;
			obj->vtx[n].nZ = obj->vtx[n].Z/norm;
			n++;

			lVR = vR;
			lHR = hR + space;
			obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
			obj->vtx[n].V = lVR / 180;
			obj->vtx[n].U = lHR / 360;
			norm = sqrt(obj->vtx[n].X*obj->vtx[n].X+obj->vtx[n].Y*obj->vtx[n].Y+obj->vtx[n].Z*obj->vtx[n].Z);
			obj->vtx[n].nX = obj->vtx[n].X/norm;
			obj->vtx[n].nY = obj->vtx[n].Y/norm;
			obj->vtx[n].nZ = obj->vtx[n].Z/norm;
			n++;

			lVR = vR + space;
			lHR = hR + space;
			obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
			obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
			obj->vtx[n].V = lVR / 180;
			obj->vtx[n].U = lHR / 360;
			norm = sqrt(obj->vtx[n].X*obj->vtx[n].X+obj->vtx[n].Y*obj->vtx[n].Y+obj->vtx[n].Z*obj->vtx[n].Z);
			obj->vtx[n].nX = obj->vtx[n].X/norm;
			obj->vtx[n].nY = obj->vtx[n].Y/norm;
			obj->vtx[n].nZ = obj->vtx[n].Z/norm;
			n++;
		}
	}
	return obj;
}

void Circle::DrawEsfera()
{
    std::unique_ptr<OBJ> obj = criaEsfera();
    glBegin (GL_TRIANGLE_STRIP);
        for (int i = 0; i < obj->numVtx; i++)
        {
            glNormal3f(obj->vtx[i].nX, obj->vtx[i].nY, obj->vtx[i].nZ);
            glTexCoord2f (obj->vtx[i].U, obj->vtx[i].V);
            glVertex3f (obj->vtx[i].X, obj->vtx[i].Y, obj->vtx[i].Z);
        }
        delete[] obj->vtx;
    glEnd();
}
