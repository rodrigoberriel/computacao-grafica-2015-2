#include "Arena.h"

using namespace std;

#define NUMERO_DE_MARCADORES_COMBUSTIVEL 5

Arena::Arena()
{
    this->statusPartida = EM_ANDAMENTO;
    camera = CAMERA_3;
    camYaw = 90;
    camPitch = 135;
    camDistanciaHelicoptero = 100;
}

void Arena::Draw()
{
    glPushMatrix();
        defineCamera(mostrarCameraCockpit);
        defineLuz0();
        // defineLuz1();

        desenhaOrigemDoSC();

        for (Helicoptero h : inimigos) h.Draw(DRAW_3D);
        jogador.Draw(DRAW_3D);

        DrawArena();


        for (Circle c : objetosResgate) c.Draw(DRAW_3D, &texturas["objetos"]);
        for (Tiro t : tiros) t.Draw(DRAW_3D, &texturas["tiro"]);

        jogador.desenharCombustivel(10, mapa.altura - 10, NUMERO_DE_MARCADORES_COMBUSTIVEL);
        jogador.desenharResgates(mapa.largura - 10, mapa.altura - 10, nObjetos);


        if (statusPartida != EM_ANDAMENTO) mostrarMensagem();
    glPopMatrix();
}

void Arena::DrawArena()
{
    int alturaArena = jogador.area.raio * 5;
    Textura *texturaParede = &texturas["posto"];

    glPushMatrix();

        // desenha o chão
        mapa.posicao.z = 0;
        mapa.cor = Cor("lightgray");
        mapa.Draw(DRAW_3D, &texturas["chao"]);

        // desenha o céu
        glPushMatrix();
            ceu = mapa;
            ceu.posicao.z = -alturaArena; // sinal negativo significa inversão da Normal
            ceu.fatorRepeticaoTextura = 1;
            ceu.Draw(DRAW_3D, &texturas["ceu"]);
        glPopMatrix();

        // desenha as paredes
        glPushMatrix();
            Rect parede1 = Rect(-alturaArena, 0, alturaArena, mapa.altura);
            glRotatef(90, 0, 1, 0);
            parede1.Draw(DRAW_3D, texturaParede);
        glPopMatrix();

        glPushMatrix();
            Rect parede2 = Rect(0, -alturaArena, mapa.largura, alturaArena);
            glRotatef(-90, 1, 0, 0);
            parede2.Draw(DRAW_3D, texturaParede);
        glPopMatrix();

        glPushMatrix();
            Rect parede3 = Rect(0, 0, alturaArena, mapa.altura);
            glTranslatef(mapa.largura, 0, 0);
            glRotatef(-90, 0, 1, 0);
            parede3.Draw(DRAW_3D, texturaParede);
        glPopMatrix();

        glPushMatrix();
            Rect parede4 = Rect(0, 0, mapa.largura, alturaArena);
            glTranslatef(0, mapa.altura, 0);
            glRotatef(90, 1, 0, 0);
            parede4.Draw(DRAW_3D, texturaParede);
        glPopMatrix();

        // desenha o posto de abastecimento
        glPushMatrix();
            glTranslatef(0, 0, 0.2);
            postoAbastecimento.Draw(DRAW_3D, &texturas["posto"]);
        glPopMatrix();
    glPopMatrix();
}

void Arena::mostrarMensagem()
{
    const char * mensagem;
    switch(statusPartida) {
        case GANHOU: mensagem = "GANHOU!"; break;
        case PERDEU: mensagem = "PERDEU!"; break;
        case PAUSADO: mensagem = "PAUSADO!"; break;
    }

    Cor _cor = (statusPartida == GANHOU) ? Cor("blue") : Cor("darkred");

    glPushMatrix();
        glColor3f(_cor.r, _cor.g, _cor.b);
        glRasterPos2f((mapa.largura/2.0) - (75.0/2.0), (mapa.altura/2.0) - (14.0 / 2.0));
        for (unsigned int i = 0; i < strlen(mensagem); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mensagem[i]);
        }
    glPopMatrix();
}

void Arena::MostraDados()
{
    cout << "A arena foi criada com:" << endl;
    cout << " - " << ((mapa.id == "Arena") ? 1 : 0) << " mapa" << endl;
    cout << " - " << ((postoAbastecimento.id == "PostoAbastecimento") ? 1 : 0) << " posto de abastecimento" << endl;
    cout << " - " << ((jogador.area.id == "Jogador") ? 1 : 0) << " jogador" << endl;
    cout << " - " << (inimigos.size()) << " inimigo(s)" << endl;
    cout << " - " << (objetosResgate.size()) << " objeto(s) de resgate" << endl << endl;
}

void Arena::ImprimeElemento(Cor corElemento)
{
    for (auto i : this->mapaCorID) {
        if (i.second == corElemento) cout << "Voce clicou em '" << i.first << "'!" << endl;
    }
}

void Arena::defineCamera(bool desenhaCockpit)
{
    if (camera == CAMERA_3) {

        // inicial
        Ponto posicaoCamera;
        posicaoCamera.x = jogador.area.posicao.x;
        posicaoCamera.y = jogador.area.posicao.y;
        posicaoCamera.z = jogador.area.posicao.z;

        // desloca a camera em uma 'esfera virtual'
        Ponto direcaoCamera;
        direcaoCamera.z = cos(camPitch * M_PI / 180.0);
        posicaoCamera.z += camDistanciaHelicoptero * -direcaoCamera.z;

        // limita a câmera para não passar do chão
        if (posicaoCamera.z < ALTURA_HELICOPTERO) {
            posicaoCamera.z = ALTURA_HELICOPTERO;
            direcaoCamera.x = sin(camYaw * M_PI / 180.0);
            direcaoCamera.y = cos(camYaw * M_PI / 180.0);
        } else {
            direcaoCamera.x = sin(camYaw * M_PI / 180.0) * sin(camPitch * M_PI / 180.0);
            direcaoCamera.y = cos(camYaw * M_PI / 180.0) * sin(camPitch * M_PI / 180.0);
        }
        posicaoCamera.x += camDistanciaHelicoptero * -direcaoCamera.x;
        posicaoCamera.y += camDistanciaHelicoptero * -direcaoCamera.y;

        // posiciona a camera olhando para o jogador
        gluLookAt(posicaoCamera.x,posicaoCamera.y,posicaoCamera.z, jogador.area.posicao.x,jogador.area.posicao.y,jogador.area.posicao.z, 0,0,-1);

    } else if(camera == CAMERA_2) {

        Ponto posicaoCamera, direcaoCamera;
        jogador.getInfoCanhao(posicaoCamera, direcaoCamera);

        // move a camera para cima do canhao
        posicaoCamera.z += 10;
        Ponto look = Ponto(posicaoCamera.x + direcaoCamera.x, posicaoCamera.y + direcaoCamera.y, posicaoCamera.z + direcaoCamera.z);

        // posiciona a camera olhando para o jogador
        gluLookAt(posicaoCamera.x,posicaoCamera.y,posicaoCamera.z, look.x,look.y,look.z, 0,0,-1);

    } else if (camera == CAMERA_1) {

        Ponto posicaoCamera = jogador.getPosicao();
        Ponto direcaoCamera = jogador.getDirecao();

        // move a camera para o cockpit
        posicaoCamera.x += direcaoCamera.x * 15;
        posicaoCamera.y += direcaoCamera.y * 15;
        posicaoCamera.z += direcaoCamera.z * 15 + 10;

        Ponto look = Ponto(posicaoCamera.x + direcaoCamera.x, posicaoCamera.y + direcaoCamera.y, posicaoCamera.z + direcaoCamera.z);

        // posiciona a camera olhando para o jogador
        gluLookAt(posicaoCamera.x,posicaoCamera.y,posicaoCamera.z, look.x,look.y,look.z, 0,0,-1);

    }

    if (!desenhaCockpit) return;

    Ponto posicaoCamera = jogador.getPosicao();
    Ponto direcaoCamera = jogador.getDirecao();

    // move a camera para o cockpit
    posicaoCamera.x += direcaoCamera.x * 15;
    posicaoCamera.y += direcaoCamera.y * 15;
    posicaoCamera.z += direcaoCamera.z * 15 + 10;

    Ponto look = Ponto(posicaoCamera.x + direcaoCamera.x, posicaoCamera.y + direcaoCamera.y, posicaoCamera.z + direcaoCamera.z);

    glPushMatrix();
        glPushAttrib(GL_ENABLE_BIT);
            glDisable(GL_LIGHTING);
            glColor3f(0.0, 1.0, 1.0);
            glTranslatef(look.x, look.y, look.z);
            glRotatef(jogador.angulo, 0, 0, 1);
            glScalef(5, 5, 5);
            glutWireCube(1);
            glEnable(GL_LIGHTING);
        glPopAttrib();
    glPopMatrix();
}

void Arena::defineLuz0()
{
    if (!ativaLuz0) return;

    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {0,0,0,1.0};

    glPushMatrix();
        glPushAttrib(GL_ENABLE_BIT);

            // move a luz para a posição desejada
            glTranslatef(mapa.largura / 2.0, mapa.altura / 2.0, 250);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            // desenha posição da luz
            glDisable (GL_LIGHTING);
            glColor3f (0.0, 1.0, 1.0);
            glScalef(5, 5, 5);
            glutWireCube(1);
            glEnable(GL_LIGHTING);

        glPopAttrib();
    glPopMatrix();
}

void Arena::defineLuz1()
{
    if (!ativaLuz1) return;

    glEnable(GL_LIGHT1);
    GLfloat light_position[] = {0,0,0,1.0};

    glPushMatrix();
        glPushAttrib(GL_ENABLE_BIT);

            // move a luz para a posição desejada
            glTranslatef(jogador.area.posicao.x, jogador.area.posicao.y, jogador.area.posicao.z + 50);
            glLightfv(GL_LIGHT1, GL_POSITION, light_position);

            // desenha posição da luz
            glDisable (GL_LIGHTING);
            glColor3f (0.0, 1.0, 1.0);
            glScalef(5, 5, 5);
            glutWireCube(1);
            glEnable(GL_LIGHTING);

        glPopAttrib();
    glPopMatrix();
}

void Arena::desenhaOrigemDoSC()
{
    GLfloat mat_ambient_r[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient_g[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };

    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        //x axis
        glPushMatrix();
            glColor3fv(mat_ambient_r);
            glScalef(5, 0.3, 0.3);
            glTranslatef(0.5, 0, 0); // put in one end
            glutSolidCube(1.0);
        glPopMatrix();

        //y axis
        glPushMatrix();
            glColor3fv(mat_ambient_g);
            glRotatef(90,0,0,1);
            glScalef(5, 0.3, 0.3);
            glTranslatef(0.5, 0, 0); // put in one end
            glutSolidCube(1.0);
        glPopMatrix();

        //z axis
        glPushMatrix();
            glColor3fv(mat_ambient_b);
            glRotatef(-90,0,1,0);
            glScalef(5, 0.3, 0.3);
            glTranslatef(0.5, 0, 0); // put in one end
            glutSolidCube(1.0);
        glPopMatrix();
    glPopAttrib();
}

bool Arena::estaDentro(Tiro tiro)
{
    Ponto p = tiro.posicao;
    int r = tiro.raio;
    bool dentro_x = (p.x > r && std::abs(p.x - mapa.largura) > r);
    bool dentro_y = (p.y > r && std::abs(p.y - mapa.altura) > r);
    bool dentro_z = (p.z > r && std::abs(p.z - (jogador.area.raio * 5)) > r);
    return (dentro_x && dentro_y && dentro_z);
}
