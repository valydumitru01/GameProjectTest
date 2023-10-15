/*******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/ecs/ECSTypes.h"
#include "engine/ecs/backend/system/SystemManager.h"
#include "engine/ecs/backend/entity/EntityManager.h"
#include "engine/ecs/backend/component/ComponentManager.h"

namespace GLESC {
    class ECS {
    public:
        ECS() = default;
        
        /**
         * @brief Create an entity with the given name. The name must be unique.
         * @param name The name of the entity
         * @return The ID of the entity or NULL_ENTITY if the entity name already exists.
         */
        EntityID createEntity(const EntityName &name);
        
        /**
         * @brief Destroy an entity
         * @param entity The ID of the entity
         * @return True if the entity was destroyed, false if the entity does not exist
         */
        bool destroyEntity(EntityID entity);
        
        template<class Component>
        void addComponent(EntityID entity, Component component);
        
        template<class Component>
        void removeComponent(EntityID entity);
        
        template<class Component>
        Component &getComponent(EntityID entity);
        
        template<class Component>
        ComponentID getComponentID();
        
        /**
         * @brief Registers the system in the system manager so it can be used and updated.
         * If the system is already registered, nothing happens.
         * @param name The name of the system
         */
        void registerSystem(const SystemName &name);
        
        template<typename System>
        bool doesEntityHaveComponent(EntityID entity);
        
        /**
         * @brief Get the entity ID from the entity name
         * @param name The name of the entity
         * @return The ID of the entity with the given name or NULL_ENTITY if the entity does not exist
         */
        EntityID getEntityID(EntityName name) const;
        
        /**
         * @brief Tries to get the entity ID from the entity name.
         * @details This will return the ID of the entity with the given name. If the entity does not exist,
         * it will return NULL_ENTITY.
         * @param name The name of the entity
         * @return The ID of the entity, or NULL_ENTITY if the entity does not exist
         */
        EntityID tryGetEntityID(EntityName name) const;
        
        /**
         * @brief Add a component requirement to the system
         * @details This will add a component requirement to the system, therefore the system will only
         * run on entities that have the required components. This will also update the signature of the system.
         * @tparam Component The type of the component
         * @param name The name of the system
         * @param componentID The ID of the component
         */
        template<typename Component>
        void addComponentRequirementToSystem(const SystemName& name);
        
        /**
         * @brief Get the name of the entity given the ID
         * @param entity The ID of the entity
         * @return The name of the entity or nullptr if the entity does not exist
         */
        EntityName getEntityName(EntityID entity);
        
        /**
         * @brief Get the entities associated with a system
         * @param name The name of the system
         * @return A set of entities associated with the system or an empty set if the system does not exist
         */
        [[nodiscard]] std::set<EntityID>
        getAssociatedEntities(const SystemName &name) const;
    
    private:
        ComponentManager componentManager{};
        SystemManager systemManager{};
        EntityManager entityManager{};
    }; // class ECS
    
    
    
    template<typename Component>
    void ECS::addComponent(EntityID entity, Component component) {
        componentManager.addComponent<Component>(entity, component);
    }
    
    template<class Component>
    void ECS::removeComponent(EntityID entity) {
        componentManager.removeComponent<Component>(entity);
        systemManager.entitySignatureChanged(entity,
        entityManager.getSignature(entity));
    }
    
    template<class Component>
    Component &ECS::getComponent(EntityID entity) {
        return componentManager.getComponent<Component>(entity);
    }
    
    template<class Component>
    ComponentID ECS::getComponentID() {
        return componentManager.getComponentID<Component>();
    }

    template<typename Component>
    void ECS::addComponentRequirementToSystem(const SystemName& name) {
        if (!systemManager.isSystemRegistered(name))
            return;
        componentManager.registerComponentIfNotRegistered<Component>();
        systemManager.addComponentRequirementToSystem(name,
                      componentManager.getComponentID<Component>());
    }
    
    template<typename System>
    bool ECS::doesEntityHaveComponent(EntityID entity) {
        return entityManager.doesEntityHaveComponent(entity,
               componentManager.getComponentID<System>());
    }
    
    
} // namespace GLESC



