#pragma once

#include <utility>
#include <vector>
#include "Component.h"
#include "engine/subsystems/input/InputTypes.h"
#include "SDL2/SDL_keycode.h"

struct InputComponent : public Component {
    /**
     * @brief Vector of pairs, subscribed keys and bool,true if they are pressed
     * @details This vector is used to store the keys that are subscribed to the input system,
     * this it saves memory as each only stores the keys that are subscribed to it.
     */
    std::vector<std::pair<SDL_Keycode, bool>> subscribedKeys;
    /**
     * @brief The mouse position is always stored and updated, no need for subscription
     * @details This is the mouse position, it is always updated and stored, no need for subscription.
     * This is because the position is not a lot of data and it is almost always used.
     */
     MousePosition mousePositionSubscribed;
};
