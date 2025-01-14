/**************************************************************************************************
 * @file   LightSystem.h
 * @author Valentin Dumitru
 * @date   2024-03-31
 * @brief  System that updates the lights in the scene
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/renderer/Renderer.h"

namespace GLESC::ECS {
    class LightComponent;
    class LightSystem : public System {
    public:
        /**
         * @brief Default constructor.
         */
        LightSystem(ECSCoordinator& ecs, Render::Renderer& renderer);

        void update() override;
    private:
        Render::Renderer& renderer;
    }; // class LightSystem
} // namespace GLESC::ECS
