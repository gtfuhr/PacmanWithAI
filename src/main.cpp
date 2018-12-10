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
    std::string str;
    Ponto_Mapa local_ant_pacman;
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
                        maze[l][i].hasBonus = true;
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
                    maze[l][i].type = BlockTypes::path;
                    init_ghost(l, i);
                    break;
                case ' ':
                    maze[l][i].type = BlockTypes::path;
                    break;
                }
            }
    }

    void move_ghosts(void)
    {

        ai.busca_largura(&(ai.grafo[phy.get_local_pac()]));
        for (auto &v : ghosts)
        {
            ai.caminho_curto(phy.get_local_pac(), v.pos_coord, &v.caminho);
            v.caminho.pop_back(); //Retira o elemento que contem o local do fantasma
        }
        phy.move_ghosts_2(&ghosts);
    }

    // Updates the game
    void update(void)
    {
        // Read last key
        player.key = draw.t.tecla();
        // if (player.key != 0)
        //     std::cout << player.key << std::endl;
        draw.t.limpa();
        // The 'Q' key ends the game
        if (player.state == State::menu)
            draw.draw_main_menu(&player);

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
                draw.t.play_wakasfx();
            }
            draw.draw_score(score);
            phy.win_condition(&player, maze);
            phy.defeat_condition(&player, &ghosts);
        }
        else if (player.state == State::score)
            draw.draw_scoreboard(&player, &scores);
        else if (player.state == State::win)
        {
            draw.draw_win(&player, score, str);
        }

        // Updates the screen
        draw.t.mostra();
        draw.draw_background();
        draw.t.espera(16.66);
    }

    // Verify if the game ended
    bool verifyEnd(void) { return true; }
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