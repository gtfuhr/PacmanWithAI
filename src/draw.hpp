#pragma once
#include "init.hpp"

namespace draw
{
struct Draw
{
    tela::Tela t; // Structure that controls the screen
    void draw_background(void);
    void draw_figures(void);
    // void draw_map(Block maze[][MAZE_SIDE_WIDTH]);
    void draw_end(void);
    void draw_help(void);
    void load_background(void);
    void finish(void);

  private:
    ALLEGRO_BITMAP *background, *bloco,
        *loss, *win;
};
}; // namespace draw