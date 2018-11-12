//Comando para compilar:
// make clean
// make
#include "init.hpp"
#include <fstream>

struct Game
{
    Player player;
    draw::Draw draw;
    physics::Physics phy;
    Block maze[MAZE_SIDE_LENGHT][MAZE_SIDE_WIDTH];

    // Init the main structures of the game
    void init(void)
    {
        draw.t.inicia(1000, 1000, "PacMan");
        draw.load_background();
        load_maze();
        player.state = State::nothing;
    }
    void load_maze()
    {
        std::string line;
        std::ifstream fileStre{MAZE_FILE};
        int atual_j;
        for (auto i = 0; std::getline(fileStre, line); i++)
            for (auto j = 0; line[j] != '\0'; j++)
                switch (line[j])
                {
                case '-':
                    maze[i][j].type = BlockTypes::horizontal;
                    break;
                case '+':
                    maze[i][j].type = BlockTypes::crossing;
                    break;
                case '0':
                    maze[i][j].type = BlockTypes::wall;
                    break;
                case '|':
                    maze[i][j].type = BlockTypes::vertical;
                    break;
                }
    }

    void draw_map(void)
    {
        Retangulo wall;
        wall.tam = {MAZE_WALL_WIDTH, MAZE_WALL_WIDTH};
        for (int i = 0; i < MAZE_SIDE_LENGHT; i++)
            for (int j = 0; j < MAZE_SIDE_WIDTH; j++)
                switch (maze[i][j].type)
                {
                case BlockTypes::wall:
                    wall.pos = {(float)j * MAZE_WALL_WIDTH + MOLDURE, (float)i * MAZE_WALL_LENGHT + MOLDURE};
                    draw.t.retangulo(wall);
                    break;
                default:
                    break;
                }
    }

    // Updates the game
    void update(void)
    {
        // Read last key
        player.key = draw.t.tecla();
        // The 'Q' key ends the game
        if (player.key != ALLEGRO_KEY_Q)
        {
            // Do the rest
            phy.move_figures();
            draw.t.limpa();
            draw_map();
            draw.draw_background();
            draw.draw_figures();
            draw.t.mostra();
            // Waits 16.66 ms, then updates the screen
            draw.t.espera(16.66);
        }
        else
            player.state = State::end; // Changes the state of the game to end
    }

    // Verify if the game ended
    bool verifyEnd(void)
    {
        verifyVictory();
        return player.state == State::nothing ? false : true;
    }

    void verifyVictory()
    {
        if (!1)
            player.state = State::end;
        if (!1)
            draw.draw_end();
    }
};

int main(int argc, char **argv)
{
    Game game;
    game.init();
    game.draw.draw_help();
    while (game.verifyEnd() == false)
        game.update();
    game.draw.finish();
    return 0;
}