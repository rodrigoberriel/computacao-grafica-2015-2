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

        desenhaOrigemDoSC();
        mapa.cor = Cor("lightgray");
        mapa.Draw(DRAW_3D);

        postoAbastecimento.Draw(DRAW_3D);
        for (Circle c : objetosResgate) c.Draw(DRAW_3D);
        for (Tiro t : tiros) t.Draw(DRAW_3D);
        for (Helicoptero h : inimigos) h.Draw(DRAW_3D);
        jogador.Draw(DRAW_3D);

        jogador.desenharCombustivel(10, mapa.altura - 10, NUMERO_DE_MARCADORES_COMBUSTIVEL);
        jogador.desenharResgates(mapa.largura - 10, mapa.altura - 10, nObjetos);


        if (statusPartida != EM_ANDAMENTO) mostrarMensagem();
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
        direcaoCamera.x = sin(camYaw * M_PI / 180.0) * sin(camPitch * M_PI / 180.0);
        direcaoCamera.y = cos(camYaw * M_PI / 180.0) * sin(camPitch * M_PI / 180.0);
        direcaoCamera.z = cos(camPitch * M_PI / 180.0);

        posicaoCamera.x += camDistanciaHelicoptero * -direcaoCamera.x;
        posicaoCamera.y += camDistanciaHelicoptero * -direcaoCamera.y;
        posicaoCamera.z += camDistanciaHelicoptero * -direcaoCamera.z;

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
            glDisable (GL_LIGHTING);
            glColor3f (0.0, 1.0, 1.0);
            glTranslatef(look.x, look.y, look.z);
            glRotatef(jogador.angulo, 0, 0, 1);
            glScalef(5, 5, 5);
            glutWireCube(1);
        glPopAttrib();
    glPopMatrix();
}

void Arena::defineLuz0(bool desenha)
{
    // desenha cubo onde a luz estaria
    Ponto posicao = Ponto(0.1, 0.1, 0.1);
    GLfloat light_position[] = {posicao.x, posicao.y, posicao.z, 0.0};
    glPushMatrix();
        glPushAttrib(GL_ENABLE_BIT);
            glLightfv (GL_LIGHT0, GL_POSITION, light_position);
            if (desenha) {
                glDisable (GL_LIGHTING);
                glColor3f (0.0, 1.0, 1.0);
                glTranslatef(posicao.x, posicao.y, posicao.z);
                glScalef(5, 5, 5);
                glutWireCube(1);
            }
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
