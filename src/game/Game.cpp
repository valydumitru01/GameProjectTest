/******************************************************************************
 * @file   Game.cpp
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/


// Components
#include "game/Game.h"

#include "engine/ecs/frontend/component/RenderComponent.h"
#include "engine/ecs/frontend/component/CameraComponent.h"
#include "engine/ecs/frontend/component/PhysicsComponent.h"
#include "engine/ecs/frontend/component/TransformComponent.h"
#include "engine/ecs/frontend/component/InputComponent.h"
#include "engine/subsystems/renderer/mesh/MeshFactory.h"

using namespace GLESC;

void Game::init() {
    Entity player = entityFactory.createEntity("player");
    Entity entity = entityFactory.createEntity("entity");
    player.addComponent(ECS::RenderComponent())
          .addComponent(ECS::TransformComponent())
          .addComponent(ECS::PhysicsComponent())
          .addComponent(ECS::InputComponent());

    entity.addComponent(ECS::RenderComponent())
          .addComponent(ECS::TransformComponent())
          .addComponent(ECS::PhysicsComponent());

    player.getComponent<ECS::RenderComponent>().mesh = Render::MeshFactory::cube(Render::Rgba(1, 0, 0, 1));
    entity.getComponent<ECS::RenderComponent>().mesh = Render::MeshFactory::cube(Render::Rgba(0, 1, 0, 1));
    entity.getComponent<ECS::TransformComponent>().transform.position = Vec3F(3, 2, 2);
}

void Game::update() {
    // Rotating entity
    ECS::Entity entity = entityFactory.getEntity("entity");
    entity.getComponent<ECS::TransformComponent>().transform.rotation.y() += 1.f;
}
