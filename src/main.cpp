//Comando para compilar:
// make clean
// make
#include "init.hpp"
#include <fstream>

//Ja que o Ponto_mapa é usado como uma chave do Map, ele precisa ter uma forma de comparacao
inline bool operator<(const Ponto_Mapa &a, const Ponto_Mapa &b)
{
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

struct Game
{
    Player player;
    Scores scores;
    std::list<Ghost> ghosts;
    draw::Draw draw;
    physics::Physics phy;
    Block maze[MAZE_SIDE_WIDTH][MAZE_SIDE_LENGHT];
    ai::Ai ai;
    int score;
    Ponto_Mapa local_ant_pacman;
    std::string str;
    // Init the main structures of the Game
    void init(void)
    {
        score = 0;
        draw.t.inicia(SCREEN_WIDTH, SCREEN_LENGTH, "PAC MAN");
        draw.t.play_menuMusic();
        draw.load_background();
        draw.scoreboard_bubblesort(&scores);
        load_maze();
        ai.init_vertices(maze);
        ai.initContainsPacman(14, 20);
        init_player();
        phy.initPhy(14, 20);
        atualizaCaminhos();
    }

    void init_ghost(int x, int y)
    {
        Ghost ghost;
        ghost.cir.centro = {(float)x * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)y * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)};
        ghost.cir.raio = PACMAN_RADIUS;
        ghost.pos_coord = {x, y};

        ghost.moving = 0;
        ghost.speed = 1;
        ghosts.push_back(ghost);
    }

    void init_player()
    {
        player.state = State::menu;
        player.option = 0;
        player.move_x = 0;
        player.move_y = 0;
        player.speed = 3;
        player.cir.raio = PACMAN_RADIUS;
        // draw.load_pacman_sprites(player.sprites);
    }

    void load_maze()
    {
        int numOfBonus = 0;
        std::string line;
        std::ifstream fileStre{MAZE_FILE};
        for (auto i = 0; std::getline(fileStre, line); i++)
            for (auto l = 0; line[l] != '\0'; l++)
            {
                maze[l][i].hasPoint = false;
                maze[l][i].hasBonus = false;
                switch (line[l])
                {
                case '-':
                    maze[l][i].type = BlockTypes::path;
                    maze[l][i].hasPoint = true;
                    break;
                case '+':
                    maze[l][i].type = BlockTypes::intersection;
                    maze[l][i].hasPoint = true;
                    maze[l][i].hasBonus = false;
                    if (numOfBonus < MAX_NUM_OF_BONUS && sin(rand()) > 0.9)
                    {
                        maze[l][i].hasPoint = false;
                        maze[l][i].hasBonus = false;
                        numOfBonus++;
                    }

                    break;
                case '0':
                    maze[l][i].type = BlockTypes::wall;
                    break;
                case '|':
                    maze[l][i].type = BlockTypes::path;
                    maze[l][i].hasPoint = true;
                    break;
                case '*':
                    maze[l][i].type = BlockTypes::path;
                    player.cir.centro = {(float)l * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)i * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)};
                    break;
                case '#':
                    if (ghosts.size() == 4)
                        ghosts.clear();
                    maze[l][i].type = BlockTypes::path;
                    maze[l][i].hasPoint = true;
                    init_ghost(l, i);
                    break;
                case ' ':
                    maze[l][i].type = BlockTypes::path;
                    break;
                case 'P':
                    maze[l][i].type = BlockTypes::portal;
                    break;
                }
            }
    }

    void atualizaCaminhos()
    {
        ai.busca_largura(&(ai.grafo[phy.get_local_pac()]));
        for (auto &v : ghosts)
        {
            v.caminho.clear();
            ai.caminho_curto(phy.get_local_pac(), v.pos_coord, &v.caminho);
            v.caminho.pop_back(); //Retira o elemento que contem o local do fantasma
        }
    }

    void move_ghosts(void)
    {
        atualizaCaminhos();
        phy.move_ghosts_2(&ghosts);
    }

    // Updates the game
    void update(void)
    {
        // Read last key
        player.key = draw.t.tecla();
        draw.t.limpa();
        if (player.state == State::menu)
            draw.draw_main_menu(&player);

        else if (player.state == State::init)
        {
            score = 0;
            load_maze();
            ai.initContainsPacman(14, 20);
            phy.initPhy(14, 20);
            player.state = State::menu;
            str.clear();
            atualizaCaminhos();
        }
        else if (player.state == State::playing)
        {
            int score_ant = score;
            draw.draw_map(maze);
            draw.draw_figures(player, ghosts);
            phy.verify_collision(&player, ai.grafo, maze);
            move_ghosts();
            score = phy.pacman_score(&player, maze, score);
            if (score_ant != score)
            {
                phy.win_condition(&player, maze);
                draw.t.play_wakasfx();
            }
            draw.draw_score(score);
            phy.defeat_condition(&player, &ghosts);
        }
        else if (player.state == State::score)
        {
            draw.scoreboard_bubblesort(&scores);
            draw.draw_scoreboard(&player, &scores);
        }
        else if (player.state == State::win)
            draw.draw_win(&player, score, &str);
        else if (player.state == State::defeat)
            draw.draw_defeat(&player, score, &str);

        // Updates the screen
        draw.t.mostra();
        draw.draw_background();
        draw.t.espera(16.66);
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.init();
    while (game.player.state != State::end)
        game.update();
    game.draw.finish();
    return 0;
}