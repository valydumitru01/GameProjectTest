/**************************************************************************************************
 * @file   SunSystem.h
 * @author Valentin Dumitru
 * @date   2024-04-30
 * @brief  System that updates the sun in the scene
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once
#include "engine/ecs/frontend/system/System.h"
#include "engine/subsystems/renderer/Renderer.h"

namespace GLESC::ECS {
    class SunComponent;
    class SunSystem : public System {
    public:
        explicit SunSystem(ECSCoordinator& ecs,Render::Renderer& renderer);
        void update() override;

    private:
        std::set<SunComponent*> sunCache;
        Render::Renderer& renderer;
    }; // class SunSystem
}
