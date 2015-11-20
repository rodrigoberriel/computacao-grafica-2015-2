#include "Helicoptero.h"

Helicoptero::Helicoptero()
{
    //x = y = 0;
    area.posicao.z = ALTURA_HELICOPTERO / 2.0;
    anguloHelice = 0;
    angulo = 0;
    anguloCanhaoYaw = 0;
    anguloCanhaoPitch = 0;
    voando = false;
    velocidadeHelice = 1;
    tempoAtualDeVoo = 0;
    objetosResgatados = 0;
    corCorpo = Cor("darkred");
}

void Helicoptero::Draw(int flag, Textura *corpo, Textura *helice, Textura *canhao)
{
    draw3d = (flag == DRAW_2D) ? false : true;

    if (desenhaEsfera) area.Draw(DRAW_3D);

    glPushMatrix();

        // move ele para a posição do circulo do jogador
        glTranslatef(this->area.posicao.x, this->area.posicao.y, this->area.posicao.z);

        // redimensiona ele para caber dentro do circulo
        glScalef(this->area.raio*2 / 85.0, this->area.raio*2 / 85.0, 1);

        // gira o helicóptero
        ajustarAngulo();
        glRotatef(angulo, 0, 0, 1);

        desenharCanhao(canhao);
        desenharCorpo(corpo);
        desenharHelice(helice);

    glPopMatrix();
}

void Helicoptero::desenharCorpo(Textura *textura)
{
    if (!draw3d) {
        glPushMatrix();
            Rect(-15, -15, 35, 30, corCorpo).Draw(WITH_STROKE); // corpo
            Rect(-40, -3, 25, 6, corCorpo).Draw(WITH_STROKE); // cauda
            Rect(-50, 4, 15, 3, corCorpo).Draw(); // cauda direita
            Rect(-50, -7, 15, 3, corCorpo).Draw(); // cauda esquerda
        glPopMatrix();
    } else {
        glPushMatrix();
            if (textura != NULL) glBindTexture (GL_TEXTURE_2D, textura->get());
            // corpo
            glPushMatrix();
                glColor3f(corCorpo.r, corCorpo.g, corCorpo.b);
                glTranslatef(0, 0, 0);
                glScalef(35, 30, ALTURA_HELICOPTERO);
                drawBox(1.0, 1);
            glPopMatrix();
            // cauda
            glPushMatrix();
                glColor3f(corCorpo.r, corCorpo.g, corCorpo.b);
                glTranslatef(-40, -3, 0);
                glScalef(25, 6, 6);
                glTranslatef(0.5, 0.5, 0);
                drawBox(1.0, 1);
            glPopMatrix();
            // cauda direita
            glPushMatrix();
                glColor3f(corCorpo.r, corCorpo.g, corCorpo.b);
                glTranslatef(-50, -7, 0);
                glScalef(15,3,6);
                glTranslatef(0.5, 0.5, 0);
                drawBox(1.0, 1);
            glPopMatrix();
            // cauda esquerda
            glPushMatrix();
                glColor3f(corCorpo.r, corCorpo.g, corCorpo.b);
                glTranslatef(-50, 4, 0);
                glScalef(15,3,6);
                glTranslatef(0.5, 0.5, 0);
                drawBox(1.0, 1);
            glPopMatrix();
        glPopMatrix();
    }
}

void Helicoptero::desenharCanhao(Textura *textura)
{
    if(!draw3d) {
        glPushMatrix();
            glTranslatef(20, 0, 0); // move para o topo do corpo
            glRotatef(anguloCanhaoYaw, 0, 0, 1); // rotaciona, se quiser
            glRotatef(anguloCanhaoPitch, 0, 1, 0); // rotaciona, se quiser
            Rect(0, -2, 25, 4, Cor("darkgreen")).Draw(WITH_STROKE);
        glPopMatrix();
    } else {
        glPushMatrix();
            glColor3f(Cor("darkgreen").r, Cor("darkgreen").g, Cor("darkgreen").b);
            if (textura != NULL) glBindTexture (GL_TEXTURE_2D, textura->get());

            glTranslatef(16, 0, 0); // move para o topo do corpo
            glRotatef(anguloCanhaoYaw, 0, 0, 1); // rotaciona, se quiser
            glRotatef(anguloCanhaoPitch, 0, 1, 0); // rotaciona, se quiser
            glScalef(25, 4, 4);
            glTranslatef(0.5, 0, 0);
            drawBox(1.0, 1);
        glPopMatrix();
    }
}

void Helicoptero::desenharHelice(Textura *textura)
{
    if(!draw3d) {
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
            Circle(Ponto(0,0), 3, Cor("darkgreen")).Draw();
        glPopMatrix();
    } else {
        double altura_helice = 1.5;
        glPushMatrix();
            glColor3f(79/255.0, 129/255.0, 189/255.0);
            if (textura != NULL) glBindTexture (GL_TEXTURE_2D, textura->get());
            glRotatef(anguloHelice, 0, 0, 1);
            glTranslatef(0,0,(ALTURA_HELICOPTERO / 2.0) + altura_helice);
            glPushMatrix();
                glScalef(80, 3, altura_helice);
                drawBox(1.0, 1);
            glPopMatrix();
            glPushMatrix();
                glScalef(3, 80, altura_helice);
                drawBox(1.0, 1);
            glPopMatrix();
            Circle(Ponto(0,0), 2, Cor("darkgreen")).Draw(DRAW_3D);
        glPopMatrix();
    }
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
    if (!objeto.estaTocando(this->area)) return false;
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
            Circle(Ponto(x, 0), mostradorRaio, cor).Draw();
        }
    glPopMatrix();
}

void Helicoptero::girarHelice()
{
    if (anguloHelice != 360) anguloHelice += 5 * velocidadeHelice;
    else anguloHelice = 0;
}

bool Helicoptero::estaVoando() { return (area.posicao.z > ALTURA_HELICOPTERO / 2.0); };
void Helicoptero::decolar() { voando = true; }
void Helicoptero::pousar() { voando = false; }
void Helicoptero::subir() { area.posicao.z++; }
void Helicoptero::descer() { if(estaVoando()) area.posicao.z--; }

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

void Helicoptero::aumentarVelocidadeHelice() {
    if (velocidadeHelice <= HELICE_VEL_MAXIMA - 0.03) velocidadeHelice += 0.03;
    else velocidadeHelice = HELICE_VEL_MAXIMA;
}
void Helicoptero::diminuirVelocidadeHelice() {
    if (velocidadeHelice >= HELICE_VEL_MINIMA + 0.03) velocidadeHelice -= 0.03;
    else velocidadeHelice = HELICE_VEL_MINIMA;
}

void Helicoptero::mirar(Ponto alvo) {

    // mira - yaw
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

    angulo += deltaAngulo;

    // mira - pitch
    // a2 -> direção, b -> posição, c -> alvo
    Ponto p, d;
    getInfoCanhao(p, d); // direção
    Ponto a2 = Ponto(b.x + d.x, b.y + d.y, b.z + d.z);

    Ponto ab2 = Ponto(b.x - a2.x, 0, b.z - a2.z);
    Ponto cb2 = Ponto(b.x - c.x, 0, b.z - c.z);

    float dot2 = (ab2.x * cb2.x + ab2.z * cb2.z); // dot product
    float cross2 = (ab2.x * cb2.z - ab2.z * cb2.x); // cross product

    float deltaAnguloRadiano2 = atan2(cross2, dot2);
    float deltaAngulo2 = deltaAnguloRadiano2 * 180.0 / M_PI;

    anguloCanhaoPitch += deltaAngulo2;
    if (anguloCanhaoPitch < 0) anguloCanhaoPitch = 0;
    if (anguloCanhaoPitch > 45) anguloCanhaoPitch = 45;
}

Tiro Helicoptero::atirar()
{
    Ponto direcao, pontaCanhao;
    getInfoCanhao(pontaCanhao, direcao);
    return Tiro(pontaCanhao, direcao, id, this->velocidadeTiro);
}

void Helicoptero::getInfoCanhao(Ponto &pontaCanhao, Ponto &direcao)
{
    double degree2rad = M_PI / 180.0;

    double direcao_x = cos((anguloCanhaoYaw + angulo) * degree2rad) * sin((anguloCanhaoPitch + 90) * degree2rad);
    double direcao_y = sin((anguloCanhaoYaw + angulo) * degree2rad) * sin((anguloCanhaoPitch + 90) * degree2rad);
    double direcao_z = cos((anguloCanhaoPitch + 90) * degree2rad);
    direcao = Ponto(direcao_x, direcao_y, direcao_z);

    Ponto baseCanhao = Ponto((area.raio*4/9) * cos(angulo * degree2rad), (area.raio*4/9) * sin(angulo * degree2rad));

    Ponto pontaCanhaoInicial;
    double tamanho = area.raio*2/3;
    pontaCanhaoInicial.x = baseCanhao.x + tamanho * cos((anguloCanhaoYaw + angulo) * M_PI / 180.0) * sin((anguloCanhaoPitch + 90) * degree2rad);
    pontaCanhaoInicial.y = baseCanhao.y + tamanho * sin((anguloCanhaoYaw + angulo) * M_PI / 180.0) * sin((anguloCanhaoPitch + 90) * degree2rad);
    pontaCanhaoInicial.z = baseCanhao.y + tamanho * cos((anguloCanhaoPitch + 90) * M_PI / 180.0);
    pontaCanhao = Ponto(this->area.posicao.x + pontaCanhaoInicial.x, this->area.posicao.y + pontaCanhaoInicial.y, this->area.posicao.z + pontaCanhaoInicial.z);
}

void Helicoptero::ajustarAngulo()
{
    this->angulo = (this->angulo > 360) ? (int)this->angulo % 360 : this->angulo;
}

void Helicoptero::moverCanhao(int incrementoYaw, int incrementoPitch)
{
    // yaw
    anguloCanhaoYaw += incrementoYaw;
    if (anguloCanhaoYaw < -45) anguloCanhaoYaw = -45;
    if (anguloCanhaoYaw > 45) anguloCanhaoYaw = 45;

    // pitch
    anguloCanhaoPitch += incrementoPitch;
    if (anguloCanhaoPitch < 0) anguloCanhaoPitch = 0;
    if (anguloCanhaoPitch > 45) anguloCanhaoPitch = 45;
}

Ponto Helicoptero::getDirecao()
{
    return Ponto(cos((angulo) * M_PI / 180.0), sin((angulo) * M_PI / 180.0));
}
