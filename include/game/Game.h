#pragma once
#include "core/TFGL.h"

class Game
{

public:
    /**
     * @brief Construct a new Game object
     *
     */
    Game();

    /**
     * @brief Destroy the Game object
     *
     */
    ~Game();

    void update();
    void handleInput();
    TFGL* engine;

private:
};
