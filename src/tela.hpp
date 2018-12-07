// tela.hpp
// Estrutura que descreve uma tela.
//
// The MIT License (MIT)
//
// Copyright (c) 2017,2018 João Vicente Ferreira Lima, UFSM
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "geom.hpp"

using namespace geom;

namespace tela
{

// estrutura que representa uma cor, com os componentes
// vermelho, verde e azul podendo variar entre 0 e 1.
struct Cor
{
    float r;
    float g;
    float b;
};

// define uma tela
struct Tela
{
    ALLEGRO_DISPLAY *display;   // display X
    ALLEGRO_COLOR ac_fundo;     // cor de fundo
    ALLEGRO_COLOR ac_cor;       // cor padrao
    ALLEGRO_EVENT_QUEUE *queue; // fila de eventos
    ALLEGRO_FONT *fonte;        // fonte padrao
    ALLEGRO_FONT *fonte2;       // mais uma fonte pq o allegro tem dessas
    ALLEGRO_BITMAP *pacmanbmp;   // paczinho maroto
    ALLEGRO_SAMPLE *menuMusic;
    ALLEGRO_SAMPLE *menuScroll;
    ALLEGRO_SAMPLE *menuSelect;
    ALLEGRO_SAMPLE *waka;
    /* ALLEGRO_TIMER *timer;  // timer */
    Retangulo janela; // retangulo que contem nossa janela
    Tamanho tam;      // tamanho da janela
    Ponto _rato;      // onde esta o mouse
    bool _botao;      // estado do botao do mouse
    int _tecla;       // ultima tecla apertada

    // inicializa a tela; deve ser chamada no inicio da execucao do programa
    void inicia(int larg, int alt, const char *nome);

    // finaliza a tela; deve ser chamado no final do programa
    void finaliza();

    // limpa a tela toda
    void limpa();

    // faz aparecer na janela o que foi desenhado
    void mostra();

    // muda a cor dos proximos desenhos de linha/retangulo/caracteres/etc
    void cor(Cor c);

    // calcula o numero de pixels (horizontais) necessarios a string s
    int strlen(const char *s) const;

    // escreve o texto s a partir da posicao p da tela
    void texto(Ponto p, const char *s);

    // escreve o texto s a partir da posicao p da tela
    void texto2(Ponto p, const char *s);

    void texto_score_nome(Ponto p, const char *s);

    void texto_score_ponto(Ponto p, const char *s);

    void image_menu(Ponto p);

    void play_menuMusic(void);

    void play_menuScroll(void);

    void play_menuSelect(void);

    void play_waka(void);

    // retorna o codigo da proxima tecla apertada (ou 0, se nao tiver tecla
    // alguma)
    int tecla();

    // retorna true se o botao do mouse estiver apertado
    bool botao();

    // retorna a posicao do cursor do mouse
    Ponto rato();

    // tempo de espera da tela, em microsegundos
    void espera(double ms);

    // desenha uma linha do ponto p1 ao ponto p2
    void linha(Ponto p1, Ponto p2);

    // desenha um retangulo
    void retangulo(Retangulo r);

    // desenha um circulo
    void circulo(Circulo c);

    // tamanho necessario para se escrever o texto s
    Tamanho tamanho_texto(const char *s);

    // Tamanho da tela.
    Tamanho tamanho() const;

    // processa eventos da tela
    void processa_eventos();
};

}; // namespace tela
