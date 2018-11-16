#include "draw.hpp"

const Cor ghosts_colors[4] = {{255, 0, 0},     //RED
                              {73, 0, 255},    //BLUE
                              {255, 113, 206}, //PINKY
                              {0, 255, 249}};  //INKY

namespace draw
{
void Draw::draw_background(void)
{
    // al_draw_bitmap(background, 0, 0, 0);
    al_flip_display();
}

// Draw all the figures on the screen
void Draw::draw_figures(Player player, std::list<Ghost> ghosts)
{
    draw_pacman(player);
    draw_ghosts(ghosts);
}

void Draw::draw_pacman(Player pacPlayer)
{
    Circulo pacman;
    Cor amarelo = {255, 0, 255};
    t.cor(amarelo);
    pacman.centro = {(float)pacPlayer.pos.x * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)pacPlayer.pos.y * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)};
    pacman.raio = 6;
    t.circulo(pacman);
}

void Draw::draw_ghosts(std::list<Ghost> ghosts)
{
    int i_color = 0;
    for (auto it = ghosts.begin(); it != ghosts.end(); it++, i_color++)
    {
        Circulo ghost;
        ghost.centro = {(float)it->pos.x * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)it->pos.y * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)};
        t.cor(ghosts_colors[i_color]);
        ghost.raio = 6;
        t.circulo(ghost);
    }
}

void Draw::draw_map(Block maze[][MAZE_SIDE_WIDTH])
{
    for (int i = 0; i < MAZE_SIDE_LENGHT; i++)
        for (int j = 0; j < MAZE_SIDE_WIDTH; j++)
        {
            switch (maze[i][j].type)
            {
            case BlockTypes::wall:
                draw_wall(i, j);
                break;

            case BlockTypes::path:
                draw_point(i, j, false);
                break;

            case BlockTypes::crossing:
                if (maze[i][j].hasBonus == true)
                    draw_point(i, j, true);
                break;
            default:
                break;
            }
        }
}

void Draw::draw_wall(int i, int j)
{
    Retangulo wall;
    wall.tam = {MAZE_WALL_WIDTH, MAZE_WALL_WIDTH};
    Cor cor_parede = {0, 0, 10};
    t.cor(cor_parede);
    wall.pos = {(float)j * MAZE_WALL_WIDTH + MOLDURE, (float)i * MAZE_WALL_LENGHT + MOLDURE};
    t.retangulo(wall);
    // wall.pos = {(float)j * MAZE_WALL_WIDTH + MOLDURE + MAZE_WALL_LENGHT / 4, (float)i * MAZE_WALL_LENGHT + MOLDURE + MAZE_WALL_LENGHT / 4};
    // Cor cor_parede2 = {0, 5, 15};
    // t.cor(cor_parede2);
    // wall.tam = {MAZE_WALL_WIDTH / 2, MAZE_WALL_WIDTH / 2};
    // t.retangulo(wall);
}

void Draw::draw_point(int i, int j, bool bonus)
{
    Circulo ponto;
    Cor preto = {255, 255, 0};
    t.cor(preto);
    ponto.centro = {(float)j * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)i * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)};
    (bonus) ? ponto.raio = MAZE_WALL_WIDTH / 3.5 : ponto.raio = MAZE_WALL_WIDTH / 7.5;
    t.circulo(ponto);
}

void Draw::draw_main_menu(Player *player)
{
    t.cor({0, 0, 255});
    t.texto({SCREEN_WIDTH / 2, 125}, "PAC  MAN");
    t.image_menu({SCREEN_WIDTH / 2 - 50, 80});
    if (player->option == 0)
    {
        if (sin(time(&player->time)) > -0.5)
        {
            t.cor({220, 0, 0});
            t.texto2({SCREEN_WIDTH / 2, 345}, "PRESS 'ENTER'");
        }

        if (player->key == ALLEGRO_KEY_ENTER)
        {
            t.play_menuSelect();
            player->option = 1;
        }
    }
    else
    {
        if (player->key == ALLEGRO_KEY_W || player->key == ALLEGRO_KEY_UP)
        {
            player->option--;
            t.play_menuScroll();
            if (player->option < 1)
                player->option = 3;
        }

        if (player->key == ALLEGRO_KEY_S || player->key == ALLEGRO_KEY_DOWN)
        {
            player->option++;
            t.play_menuScroll();
            if (player->option > 3)
                player->option = 1;
        }

        draw_option_switch(player->option);

        if (player->key == ALLEGRO_KEY_ENTER)
        {
            t.play_menuSelect();
            switch (player->option)
            {
            case 1:
                player->state = State::playing;
                break;
            case 2:
                player->state = State::score;
                break;
            case 3:
                sleep(1);
                player->state = State::end;
                break;
            default:
                break;
                ;
            }
        }
    }
}

void Draw::draw_option_switch(int option)
{
    for (auto i = 0; i < 3; i++)
    {
        if ((i + 1) == option)
            t.cor({220, 0, 0});
        else
            t.cor({255, 255, 0});

        float mult = i * 50;

        t.texto2({SCREEN_WIDTH / 2, 275 + mult}, options[i]);
    }
}

void Draw::draw_score(void) {}

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