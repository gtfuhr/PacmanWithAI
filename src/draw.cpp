#include "draw.hpp"

namespace draw
{
void Draw::draw_background(void)
{
    // al_draw_bitmap(background, 0, 0, 0);
    al_flip_display();
}

// Draw all the figures on the screen
void Draw::draw_figures()
{
}

void Draw::draw_help(void)
{
    std::cout << "Pressione: " << std::endl;
    std::cout << " - 'a' ,'s' 'w' e 'd' para mover " << std::endl;
    std::cout << " - 'esc' sair" << std::endl;
}

void Draw::draw_end()
{
    // Cor branco = {255, 255, 255};
    // Ponto localMensagem = {400, 400};
    // if (1 + 1)
    // {
    //     al_draw_bitmap(loss, 0, 0, 0);
    //     t.cor(branco);
    //     t.texto(localMensagem, "You lost the game! D`:");
    // }
    // else
    // {
    //     al_draw_bitmap(win, 0, 0, 0);
    //     t.cor(branco);
    //     t.texto(localMensagem, "You won the game! XD");
    // }
    // al_flip_display();
    // t.espera(5000);
}

void Draw::load_background()
{
    // background = al_load_bitmap(BACKGROUND_FILE);
    // if (!background)
    // {
    //     fprintf(stderr, "failed to load background bitmap!\n");
    //     exit(1);
    // }
    // win = al_load_bitmap(BACKGROUND_WIN_FILE);
    // if (!win)
    // {
    //     fprintf(stderr, "failed to load win bitmap!\n");
    //     exit(1);
    // }
    // loss = al_load_bitmap(BACKGROUND_LOSS_FILE);
    // if (!loss)
    // {
    //     fprintf(stderr, "failed to load loss bitmap!\n");
    //     exit(1);
    // }
    // bloco = al_load_bitmap(BLOCO_FILE);
    // if (!bloco)
    // {
    //     fprintf(stderr, "failed to load laser bitmap!\n");
    //     exit(1);
    // }
}
void Draw::finish(void)
{
    t.finaliza();
    al_destroy_bitmap(background);
    al_destroy_bitmap(win);
    al_destroy_bitmap(loss);
    al_destroy_bitmap(bloco);
    // Closes the window
}
}; // namespace draw