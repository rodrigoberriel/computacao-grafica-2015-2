#include "Helicoptero.h"

Helicoptero::Helicoptero()
{
    //x = y = 0;
    anguloHelice = 0;
    angulo = 0;
    anguloCanhao = 0;
    voando = false;
    velocidadeHelice = 1;
    tempoAtualDeVoo = 0;
    objetosResgatados = 0;
    corCorpo = Cor("darkred");
}

void Helicoptero::Draw()
{
    glPushMatrix();

        // move ele para a posição do circulo do jogador
        glTranslatef(this->area.posicao.x, this->area.posicao.y, this->area.posicao.z);

        // redimensiona ele para caber dentro do circulo
        glScalef(this->area.raio*2 / 85.0, this->area.raio*2 / 85.0, 0);

        // gira o helicóptero
        ajustarAngulo();
        glRotatef(angulo, 0, 0, 1);

        desenharCanhao();
        desenharCorpo();
        desenharHelice();

    glPopMatrix();
}

void Helicoptero::Draw3D()
{
    glPushMatrix();

        // move ele para a posição do circulo do jogador
        glTranslatef(this->area.posicao.x, this->area.posicao.y, 30);

        //glBegin(GL_POLYGON);
        /*
            GLUquadricObj *obj = gluNewQuadric();
            gluSphere(obj, 30, 30, 30);
            glTranslatef(this->area.posicao.x, this->area.posicao.y, 100);
            gluCylinder(obj, 50.0, 50, 100, 30, 30);
        */
        //glEnd();

    glPopMatrix();
}

void Helicoptero::desenharCorpo()
{
    glPushMatrix();
        Rect(-15, -15, 35, 30, corCorpo).Draw(WITH_STROKE); // corpo
        Rect(-40, -3, 25, 6, corCorpo).Draw(WITH_STROKE); // cauda
        Rect(-50, 4, 15, 3, corCorpo).Draw(); // cauda direita
        Rect(-50, -7, 15, 3, corCorpo).Draw(); // cauda esquerda
    glPopMatrix();
}

void Helicoptero::desenharCanhao()
{
    glPushMatrix();
        glTranslatef(20, 0, 0); // move para o topo do corpo
        glRotatef(anguloCanhao, 0, 0, 1); // rotaciona, se quiser
        Rect(0, -2, 25, 4, Cor("darkgreen")).Draw(WITH_STROKE);
    glPopMatrix();
}

void Helicoptero::desenharHelice()
{
    glPushMatrix();
        glRotatef(anguloHelice, 0, 0, 1);

        glColor3f(79/255.0, 129/255.0, 189/255.0);
        glBegin(GL_TRIANGLES);
            glVertex2f(40.0, 3.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(40.0, -3.0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(-40.0, 3.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(-40.0, -3.0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(3.0, 40.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(-3.0, 40.0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(3.0, -40.0);
            glVertex2f(0.0, 0.0);
            glVertex2f(-3.0, -40.0);
        glEnd();
        Circle(0, 0, 3, Cor("darkgreen")).Draw();
    glPopMatrix();
}

void Helicoptero::desenharCombustivel(float _posicaoX, float _posicaoY, int _numeroDeMostradores)
{
    int mostradorAltura = 15;
    int mostradorLargura = 10;
    int mostradorEspaco = 5;
    int nMostradores = _numeroDeMostradores;
    double nivel = nMostradores * getNivelCombustivel();

    glPushMatrix();
        glTranslatef(_posicaoX, _posicaoY - mostradorAltura, 0);
        for (int i = 0; i < nMostradores; i++) {
            int x = i * (mostradorLargura + mostradorEspaco);
            Cor cor = (i < nivel) ? Cor("green") : Cor("red");
            Rect(x, 0, mostradorLargura, mostradorAltura, cor).Draw(WITH_STROKE);
        }
    glPopMatrix();
}

void Helicoptero::consumirCombustivel(GLdouble timeDiff)
{
    if (estaVoando() && tempoAtualDeVoo <= tempoMaximoDeVoo)
        tempoAtualDeVoo += timeDiff / 1000.0;
}

double Helicoptero::getNivelCombustivel()
{
    return 1 - (tempoAtualDeVoo / tempoMaximoDeVoo);
}

void Helicoptero::reabastercer() { tempoAtualDeVoo = 0; }

bool Helicoptero::resgatar(Circle objeto) {
    if (!objeto.estaDentro(this->getPosicao())) return false;
    this->objetosResgatados++;
    return true;
}

void Helicoptero::desenharResgates(float _posicaoX, float _posicaoY, int _nObjetos)
{
    int mostradorRaio = 7;
    int mostradorEspaco = 5;
    double shiftX = (_nObjetos * ((2 * mostradorRaio) + mostradorEspaco)) + mostradorEspaco - mostradorRaio;

    glPushMatrix();
        glTranslatef(_posicaoX - shiftX, _posicaoY - (2 * mostradorRaio), 0);
        for (int i = 0; i < _nObjetos; i++) {
            int x = i * ((2 * mostradorRaio) + mostradorEspaco);
            Cor cor = (i < objetosResgatados) ? Cor("green") : Cor("blue");
            Circle(x, 0, mostradorRaio, cor).Draw();
        }
    glPopMatrix();
}

void Helicoptero::girarHelice()
{
    if (anguloHelice != 360) anguloHelice += 5 * velocidadeHelice;
    else anguloHelice = 0;
}

bool Helicoptero::estaVoando() { return voando; };
void Helicoptero::decolar() { area.raio = area.raio * 3 / 2; voando = true; }
void Helicoptero::pousar() { area.raio = area.raio * 2 / 3; voando = false; }

void Helicoptero::girarDireita() { if (!estaVoando()) return; angulo += 1.5; }
void Helicoptero::girarEsquerda() { if (!estaVoando()) return; angulo -= 1.5; }

Ponto Helicoptero::getProximaPosicao(GLdouble timeDiff)
{
    Ponto novaPosicao;
    float alphaRadians = (360.0 - angulo) * (M_PI / 180.0);
    novaPosicao.x = area.posicao.x + cos(alphaRadians) * velocidadeHelicoptero * timeDiff;
    novaPosicao.y = area.posicao.y - sin(alphaRadians) * velocidadeHelicoptero * timeDiff;
    return novaPosicao;
}

void Helicoptero::moverFrente(GLdouble timeDiff)
{
    if (!estaVoando()) return;
    float alphaRadians = (360.0 - angulo) * (M_PI / 180.0);
    area.posicao.x += cos(alphaRadians) * velocidadeHelicoptero * timeDiff;
    area.posicao.y -= sin(alphaRadians) * velocidadeHelicoptero * timeDiff;
}

void Helicoptero::moverTras(GLdouble timeDiff)
{
    if (!estaVoando()) return;
    float alphaRadians = (360.0 - angulo) * (M_PI / 180.0);
    area.posicao.x -= cos(alphaRadians) * velocidadeHelicoptero * timeDiff;
    area.posicao.y += sin(alphaRadians) * velocidadeHelicoptero * timeDiff;
}

void Helicoptero::aumentarVelocidadeHelice() { velocidadeHelice += 0.03; }
void Helicoptero::diminuirVelocidadeHelice() { if (velocidadeHelice >= 0.03) velocidadeHelice -= 0.03; }

void Helicoptero::mirar(Ponto alvo) {

    double anguloRadianos = angulo * M_PI / 180.0;

    // a -> direção, b -> posição, c -> alvo
    Ponto a = Ponto(this->area.posicao.x + cos(anguloRadianos), this->area.posicao.y + sin(anguloRadianos));
    Ponto b = this->area.posicao;
    Ponto c = alvo;

    Ponto ab = Ponto(b.x - a.x, b.y - a.y);
    Ponto cb = Ponto(b.x - c.x, b.y - c.y);

    float dot = (ab.x * cb.x + ab.y * cb.y); // dot product
    float cross = (ab.x * cb.y - ab.y * cb.x); // cross product

    float deltaAnguloRadiano = atan2(cross, dot);
    float deltaAngulo = deltaAnguloRadiano * 180.0 / M_PI;
    // float deltaAngulo = (alpha * 180.0 / M_PI + 0.5);

    angulo += deltaAngulo;
}

Tiro Helicoptero::atirar()
{
    Ponto direcao = Ponto(cos((anguloCanhao + angulo) * M_PI / 180.0), sin((anguloCanhao + angulo) * M_PI / 180.0));
    Ponto baseCanhao = Ponto((area.raio*4/9) * cos(angulo * M_PI / 180.0), (area.raio*4/9) * sin(angulo * M_PI / 180.0));
    Ponto pontaCanhao = Ponto(baseCanhao.x + (area.raio*2/3) * cos((anguloCanhao + angulo) * M_PI / 180.0), baseCanhao.y + (area.raio*2/3) * sin((anguloCanhao + angulo) * M_PI / 180.0));
    return Tiro(Ponto(this->area.posicao.x + pontaCanhao.x, this->area.posicao.y + pontaCanhao.y), direcao, id, this->velocidadeTiro);
}

void Helicoptero::ajustarAngulo()
{
    this->angulo = (this->angulo > 360) ? (int)this->angulo % 360 : this->angulo;
}

void Helicoptero::moverCanhao(int incremento)
{
    anguloCanhao += incremento;
    if (anguloCanhao < -45) anguloCanhao = -45;
    if (anguloCanhao > 45) anguloCanhao = 45;
}

Ponto Helicoptero::getDirecao()
{
    return Ponto(cos((angulo) * M_PI / 180.0), sin((angulo) * M_PI / 180.0));
}
