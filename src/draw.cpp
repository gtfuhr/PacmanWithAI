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
    draw_pacman();
    draw_ghosts();
}

void Draw::draw_pacman(void) {}
void Draw::draw_ghosts(void) {}

void Draw::draw_map(Block maze[][MAZE_SIDE_WIDTH])
{
    Retangulo wall;
    wall.tam = {MAZE_WALL_WIDTH, MAZE_WALL_WIDTH};
    for (int i = 0; i < MAZE_SIDE_LENGHT; i++)
        for (int j = 0; j < MAZE_SIDE_WIDTH; j++)
            switch (maze[i][j].type)
            {
            case BlockTypes::wall:
                wall.pos = {(float)j * MAZE_WALL_WIDTH + MOLDURE, (float)i * MAZE_WALL_LENGHT + MOLDURE};
                t.retangulo(wall);
                break;
            case BlockTypes::spawn:
                break;
            case BlockTypes::horizontal || BlockTypes::vertical || BlockTypes::crossing:
                draw_points();
                break;
            default:
                break;
            }
}

void Draw::draw_points(void) {}

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