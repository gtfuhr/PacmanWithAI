#pragma once
#include "init.hpp"
#include <ctime>

namespace draw
{
struct Draw
{
  tela::Tela t; // Structure that controls the screen
  void draw_background(void);
  void draw_figures(void);
  void draw_main_menu(Player *player);
  void draw_map(Block maze[][MAZE_SIDE_WIDTH]);
  void draw_score(void);
  void draw_end(void);
  void draw_help(void);
  void load_background(void);
  void finish(void);

private:
  void draw_pacman(void);
  void draw_ghosts(void);
  void draw_points(void);
  void draw_option_switch(int option);
  const char *options[3] = {"PLAY",
                            "SCORE",
                            "QUIT"};
  ALLEGRO_BITMAP *background, *bloco,
      *loss, *win;
};
}; // namespace draw