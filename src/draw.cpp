#include <string>
#include "draw.hpp"

const Cor ghosts_colors[4] = {{255, 0, 0},         //BLINKY
                              {255, 157, 0},      //INKY
                              {249, 162, 244},   //PINKY
                              {0, 255, 255}};   //CLYDE

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
    Cor amarelo = {255, 255, 0};
    t.cor(amarelo);
    t.circulo(pacPlayer.cir);
}

void Draw::draw_ghosts(std::list<Ghost> ghosts)
{
    int i_color = 0;
    for (auto it = ghosts.begin(); it != ghosts.end(); it++, i_color++)
    {
        t.cor(ghosts_colors[i_color]);
        t.circulo(it->cir);
        t.retangulo({{float(it->cir.centro.x - PACMAN_RADIUS + 0.25), it->cir.centro.y}, {float(PACMAN_RADIUS*2 - 0.25), PACMAN_RADIUS}});
    }
}

void Draw::draw_map(Block maze[][MAZE_SIDE_LENGHT])
{
    for (int x = 0; x < MAZE_SIDE_WIDTH; x++)
        for (int y = 0; y < MAZE_SIDE_LENGHT; y++)
        {
            switch (maze[x][y].type)
            {
            case BlockTypes::wall:
                draw_wall(x, y);
                break;

            case BlockTypes::path:
                if (maze[x][y].hasPoint == true)
                    draw_point(x, y, false);
                break;

            case BlockTypes::intersection:
                if (maze[x][y].hasBonus == true)
                    draw_point(x, y, true);
                else if (maze[x][y].hasPoint == true)
                    draw_point(x, y, false);
                break;
            default:
                break;
            }
        }
}

void Draw::draw_wall(int x, int y)
{
    Retangulo wall;
    wall.tam = {MAZE_WALL_WIDTH, MAZE_WALL_LENGHT};
    Cor cor_parede = {0, 0, 255};
    t.cor(cor_parede);
    wall.pos = {(float)x * MAZE_WALL_WIDTH + MOLDURE, (float)y * MAZE_WALL_LENGHT + MOLDURE};
    t.retangulo(wall);
}

void Draw::draw_point(int x, int y, bool bonus)
{
    Circulo ponto;
    Cor amarelo = {255, 255, 0};
    t.cor(amarelo);
    ponto.centro = {(float)x * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)y * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)};
    (bonus) ? ponto.raio = MAZE_WALL_WIDTH / 3.5 : ponto.raio = MAZE_WALL_WIDTH / 7.5;
    t.circulo(ponto);
}

int get_ms()
{
    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch());
    return ms.count();
}

void Draw::draw_main_menu(Player *player)
{
    t.cor({0, 0, 255});
    t.texto({SCREEN_WIDTH / 2, 125}, "PAC  MAN");
    t.image_menu({SCREEN_WIDTH / 2 - 50, 80});

    if (player->option == 0)
    {
        if (sin(get_ms() / 75) > -0.5)
        {
            t.cor({255, 0, 0});
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
            }
        }
    }
}

void Draw::draw_option_switch(int option)
{
    for (auto i = 0; i < 3; i++)
    {
        float mult = i * 50;
        if ((i + 1) == option)
        {
            main_menu_text_efect({SCREEN_WIDTH / 2, 275 + mult});
            t.cor({220, 0, 0});
        }
        else
            t.cor({255, 255, 0});

        t.texto2({SCREEN_WIDTH / 2, 275 + mult}, options[i]);
    }
}

void Draw::main_menu_text_efect(Ponto local)
{
    float variancia = sin(get_ms() / 50) * 30;
    float cx = local.x, cy = local.y + 15;
    al_draw_filled_ellipse(cx - 5, cy, 39 + variancia, 9, {0, 0, 255});
    al_draw_filled_ellipse(cx - 5, cy + variancia / 3, 40 + variancia, 10, {0, 255, 0});
}

void Draw::scoreboard_bubblesort(Scores *scores)
{
    std::string aux;
    int size = 0;

    std::ifstream entrada;
    entrada.open("data/scores.txt");

    while (std::getline(entrada, aux))
    {
        size++;
    }

    scores->names = new std::string[size];
    scores->points = new int[size];

    entrada.clear();
    entrada.seekg(0, std::ios::beg);

    for (auto i = 0; i < size; i++)
    {
        entrada >> scores->names[i];
        entrada >> scores->points[i];
    }

    entrada.close();

    for (auto i = 0; i < size; i++)
    {
        for (int j = (i + 1); j < size; j++)
        {
            if (scores->points[j] > scores->points[i])
            {
                int a = scores->points[j];
                scores->points[j] = scores->points[i];
                scores->points[i] = a;

                aux = scores->names[j];
                scores->names[j] = scores->names[i];
                scores->names[i] = aux;
            }
        }
    }
}

void Draw::draw_scoreboard(Player *player, Scores *scores)
{
    t.cor({0, 0, 255});
    t.texto({SCREEN_WIDTH / 2, 30}, "SCORES");

    t.cor({255, 255, 0});

    for (int i = 0; i < 10; i++)
    {
        int aux_placar = i + 1;

        std::string aux = std::to_string(aux_placar);

        if ((i + 1) < 10)
            aux = '0' + aux;
        aux += '.';

        float mult = i * 40;

        t.texto_score_nome({20, 120 + mult}, aux.c_str());
        t.texto_score_nome({110, 120 + mult}, scores->names[i].c_str());

        aux = std::to_string(scores->points[i]);
        t.texto_score_ponto({470, 120 + mult}, aux.c_str());
    }

    main_menu_text_efect({SCREEN_WIDTH / 2, 560});

    t.cor({220, 0, 0});
    t.texto2({SCREEN_WIDTH / 2, 560}, "BACK");

    if (player->key == ALLEGRO_KEY_ENTER)
    {
        t.play_menuSelect();
        player->state = State::menu;
    }
}

void Draw::draw_score(int score)
{
    t.cor({255, 255, 0});
    std::string txt = "SCORE: ";
    std::string string_score = std::to_string(score);
    txt += string_score;
    t.texto3({SCREEN_WIDTH / 2, 5}, txt.c_str());
}

void entrada_txt(Player *player, std::string str)
{
    if (player->key != 0)
    {
        if (str.length() <= 7)
        {
            std::string aux;
            //char temp[] = {evento.keyboard.unichar, '\0'};
            if (player->key >= 1 && player->key <= 26)
            {
                aux = 'A' + player->key - 1;
                str += aux;
            }
            else if (player->key >= 27 &&
                     player->key <= 36)
            {
                aux = '0' + player->key - 1;
                str += aux;
            }
            else if (player->key == 75)
            {
                str += ' ';
            }

            //std::cout << aux << std::endl;
            std::cout << str << std::endl;
        }

        if (player->key == 63 && str.length() != 0)
        {
            str[str.length() - 1] = '\0';
        }
    }
}

void Draw::imprime_centralizado(std::string str)
{
    if (str.length() > 0)
    {
        t.texto2({SCREEN_WIDTH / 2, (SCREEN_LENGTH / 2) + 30}, str.c_str());
    }
}

void Draw::draw_win(Player *player, int score, std::string str)
{
    std::string txt = "SCORE: ";
    std::string string_score = std::to_string(score);
    txt += string_score;

    t.cor({255, 255, 0});
    t.texto({SCREEN_WIDTH / 2, 40}, "YOU WIN");
    t.texto2({SCREEN_WIDTH / 2, (SCREEN_LENGTH / 2) - 40}, txt.c_str());
    t.texto2({SCREEN_WIDTH / 2, SCREEN_LENGTH / 2}, "ENTER YOUR NAME:");

    if (sin(get_ms() / 75) > -0.5)
    {
        t.texto3({SCREEN_WIDTH / 2, (SCREEN_LENGTH / 2) + 120}, "PRESS 'ENTER' WHEN READY");
    }

    /*entrada_txt(player, str);
    imprime_centralizado(str);*/
}

void Draw::draw_defeat(Player *player, int score, std::string str)
{
    std::string txt = "SCORE: ";
    std::string string_score = std::to_string(score);
    txt += string_score;

    t.cor({255, 255, 0});
    t.texto({SCREEN_WIDTH / 2, 40}, "YOU LOSE");
    t.texto2({SCREEN_WIDTH / 2, (SCREEN_LENGTH / 2) - 40}, txt.c_str());
    t.texto2({SCREEN_WIDTH / 2, SCREEN_LENGTH / 2}, "ENTER YOUR NAME:");

    if (sin(get_ms() / 75) > -0.5)
    {
        t.texto3({SCREEN_WIDTH / 2, (SCREEN_LENGTH / 2) + 120}, "PRESS 'ENTER' WHEN READY");
    }

    /*entrada_txt(player, str);
    imprime_centralizado(str);*/
}

void Draw::draw_help(void)
{
    std::cout << "Pressione: " << std::endl;
    std::cout << " - '^' ,'<' 'v' e '>' para mover " << std::endl;
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
    // al_destroy_bitmap(background);
    // al_destroy_bitmap(win);
    // al_destroy_bitmap(loss);
    // al_destroy_bitmap(bloco);
    // Closes the window
}
}; // namespace draw