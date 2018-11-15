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
    int blink;

    const char *options[3] = {"PLAY",
                              "SCORE",
                              "QUIT"};

    // Init the main structures of the game
    void init(void)
    {
        draw.t.inicia(SCREEN_WIDTH, SCREEN_LENGTH, "PACMAN");
        draw.t.play_menuMusic();
        draw.load_background();
        load_maze();
        player.state = State::nothing;
        player.option = 0;
        blink = 0;
    }

    void load_maze()
    {
        std::string line;
        std::ifstream fileStre{MAZE_FILE};
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
                case '*':
                    maze[i][j].type = BlockTypes::spawn;
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
                case BlockTypes::spawn:

                default:
                    break;
                }
    }


    void draw_option_switch(int option){
        for(auto i = 0; i < 3; i++){
            if((i+1) == option)
                draw.t.cor({220, 0, 0});
            else
                draw.t.cor({255, 255, 0});

            float mult = i * 50;

            draw.t.texto2({SCREEN_WIDTH/2, 275 + mult}, options[i]);
        }
    }


    void draw_main(void)
    {
        draw.t.cor({0, 0, 255});
        draw.t.texto({SCREEN_WIDTH/2, 125}, "PAC  MAN");
        draw.t.image_menu({SCREEN_WIDTH/2 - 50, 80});

        if(player.option == 0){
            if(blink > 30) blink = 0;
            
            if(blink < 15){
                draw.t.cor({220, 0, 0});
                draw.t.texto2({SCREEN_WIDTH/2, 345}, "PRESS 'ENTER'");
            }

            if(player.key == ALLEGRO_KEY_ENTER){
                draw.t.play_menuSelect();
                player.option = 1;
            }

            blink++;
        }
        else{
            if(player.key == ALLEGRO_KEY_W){
                player.option--;
                draw.t.play_menuScroll();
                if(player.option < 1){
                    player.option = 3;
                }
            }

            if(player.key == ALLEGRO_KEY_S){
                player.option++;
                draw.t.play_menuScroll();
                if(player.option > 3){
                    player.option = 1; 
                }
            }

            if(player.key == ALLEGRO_KEY_ENTER){
                draw.t.play_menuSelect();
                switch(player.option){
                    case 1:
                    case 2:
                    case 3:
                        sleep(1);
                        player.state = State::end;
                }
            }

            draw_option_switch(player.option);
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
            draw_main();
            //draw_map();
            draw.draw_background();
            //draw.draw_figures();
            draw.t.mostra();
            // Waits 16.66 ms, then updates the screen
            draw.t.espera(33.33);
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