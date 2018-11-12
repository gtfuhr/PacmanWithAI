//Comando para compilar:
// g++  -Wall -std=c++11 -o main main.cpp tela.cpp ai.cpp physics.cpp -lallegro -lallegro_image -lallegro_primitives-lallegro_font -lallegro_ttf

#include "init.hpp"
#include <iostream>

using namespace tela;
using namespace geom;

struct Game
{
    Player player;
    Tela t; // estrutura que controla a tela
    Block maze[MAZE_SIDE_LENGHT][MAZE_SIDE_WIDTH];
    int tecla; // ultima tecla apertada pelo usuario
    ALLEGRO_BITMAP *background, *bloco,
        *loss, *win;

    // inicia estruturas principais do jogo
    void inicia(void)
    {
        t.inicia(1000, 600, "PacMan");
        carrega_fundo_fonte();
        player.state = State::nothing;
    }

    // atualiza o jogo, como se fosse um passo na execução
    void atualiza(void)
    {
        // le ultima tecla
        tecla = t.tecla();
        // tecla Q termina
        if (tecla != ALLEGRO_KEY_Q)
        {
            // faz o resto
            move_figuras();
            t.limpa();
            desenha_fundo();
            desenha_figuras();
            t.mostra();

            // espera 16.66 ms antes de atualizar a tela
            t.espera(16.66);
        }
        else
            player.state = State::end; // Changes the state of the game to end
    }

    void desenha_fundo(void)
    {
        al_draw_bitmap(background, 0, 0, 0);
        al_flip_display();
    }
    void carrega_fundo_fonte()
    {
        background = al_load_bitmap(BACKGROUND_FILE);
        if (!background)
        {
            fprintf(stderr, "failed to load background bitmap!\n");
            exit(1);
        }
        win = al_load_bitmap(BACKGROUND_WIN_FILE);
        if (!win)
        {
            fprintf(stderr, "failed to load win bitmap!\n");
            exit(1);
        }
        loss = al_load_bitmap(BACKGROUND_LOSS_FILE);
        if (!loss)
        {
            fprintf(stderr, "failed to load loss bitmap!\n");
            exit(1);
        }
        bloco = al_load_bitmap(BLOCO_FILE);
        if (!bloco)
        {
            fprintf(stderr, "failed to load laser bitmap!\n");
            exit(1);
        }
    }

    // verifica se o jogo terminou ou não
    // - retorna TRUE quando  termina
    // - retorna FALSE caso contrário
    bool verifica_fim(void)
    {
        verifica_vitoria();
        if (player.state == State::nothing)
            return false;
        else
            return true;
    }

    void verifica_vitoria()
    {
        if (1)
            player.state = State::end;
        if (1)
            desenha_final();
    }
    void desenha_final()
    {
        Cor branco = {255, 255, 255};
        Ponto localMensagem = {400, 400};
        if (1 + 1)
        {
            al_draw_bitmap(loss, 0, 0, 0);
            t.cor(branco);
            t.texto(localMensagem, "You lost the game! D`:");
        }
        else
        {
            al_draw_bitmap(win, 0, 0, 0);
            t.cor(branco);
            t.texto(localMensagem, "You won the game! XD");
        }
        al_flip_display();
        t.espera(5000);
    }

    void finaliza(void)
    {
        // fecha a tela
        t.finaliza();
        al_destroy_bitmap(background);
        al_destroy_bitmap(win);
        al_destroy_bitmap(loss);
        al_destroy_bitmap(bloco);
    }

    // desenha todas as figuras e objetos na tela
    void desenha_figuras()
    {
    }

    void verifica_colisao(void)
    {
    }

    void move_figuras(void)
    {
    }

    void legenda(void)
    {
        std::cout << "Pressione: " << std::endl;
        std::cout << " - 'a' ,'s' 'w' e 'd' para mover " << std::endl;
        std::cout << " - 'esc' sair" << std::endl;
    }
};

int main(int argc, char **argv)
{
    Game game;

    game.inicia();
    game.legenda();
    while (game.verifica_fim() == false)
    {
        game.atualiza();
    }
    game.finaliza();
    return 0;
}