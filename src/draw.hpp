#pragma once
#include "init.hpp"
#include <ctime>
#include <chrono>
#include <fstream>

namespace draw
{
struct Draw
{
  tela::Tela t; // Structure that controls the screen
  void draw_background(void);
  void imprime_centralizado(std::string str);
  void draw_figures(Player player, std::list<Ghost> ghosts);
  void draw_main_menu(Player *player);
  void draw_map(Block maze[][MAZE_SIDE_LENGHT]);
  void draw_score(int score);
  void draw_scoreboard(Player *player, Scores *scores);
  void scoreboard_bubblesort(Scores *scores);
  void draw_end();
  void draw_win(Player *player, int score, std::string *str);
  void draw_defeat(Player *player, int score, std::string *str);
  void draw_help(void);
  void load_background(void);
  void finish(void);
  void load_pacman_sprites(ALLEGRO_BITMAP **sprites);
  int get_ms();

private:
  void entrada_txt(Player *player, std::string *str, int score);
  void salva_no_arquivo(std::string str, int score);
  void draw_pacman(Player pacPlayer);
  void draw_ghosts(std::list<Ghost> ghosts);
  void draw_wall(int i, int j);
  void draw_point(int i, int j, bool bonus);
  void draw_option_switch(int option);
  void main_menu_text_efect(Ponto local);
  void draw_palms(void);

  const char *options[3] = {"PLAY",
                            "SCORES",
                            "QUIT"};

  ALLEGRO_BITMAP *background, *bloco,
      *loss, *win;
};
}; // namespace draw
