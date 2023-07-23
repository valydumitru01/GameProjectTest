#pragma once

#include <cassert>
#include <unordered_map>
#include <boost/bimap.hpp>
#include "engine/ecs/ECSTypes.h"
#include "engine/core/exceptions/ecs/ECSException.h"
#include "engine/core/logger/Logger.h"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual bool hasComponent(EntityID entity) = 0;
    virtual void entityDestroyed(EntityID entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
public:
    void insertData(EntityID entity, T component) {
#ifdef DEBUG
        const char *name = typeid(T).name();
        Logger::get().importantInfo("Adding component \"" + std::string(name) + "\" to entity" + std::to_string(entity));
        printEntityToIndexMap("Map before inserting:",entityToIndexMap);
        if (entityToIndexMap.left.find(entity) != entityToIndexMap.left.end()) {
            throw ECSException("Component added to same entity more than once.");
        }
#endif
        // Put new entry at end and update the maps
        size_t newIndex = size;
        entityToIndexMap.insert({ entity, newIndex });
        componentArray[newIndex] = component;
        ++size;
#ifdef DEBUG
        printEntityToIndexMap("Map after inserting:",entityToIndexMap);
#endif
    }
    
    void printEntityToIndexMap(const std::string& message,const boost::bimap <EntityID, size_t> &map) {
        Logger::get().importantInfoBlue(message);
        const char *name = typeid(T).name();
        Logger::get().infoBlue("Array of " + std::string(name));
        Logger::get().infoBlue("\tEntityToIndexMap size: " + std::to_string(map.size()));
        for (const auto &entry: map) {
            Logger::get().infoBlue(
                    "\tEntity ID: " + std::to_string(entry.left) + ", Array Index: " + std::to_string(entry.right));
        }
    }
    
    /**
     * @brief Removes the data of the entity from the array
     * The last element in the array is copied into the place of the removed element
     * The maps are updated to reflect the changes
     * @param entity The entity to remove
     */
    void entityDestroyed(EntityID entity) override {
#ifdef DEBUG
        const char *name = typeid(T).name();
        Logger::get().importantInfoPurple("Removing component \"" + std::string(name) + "\" from entity" + std::to_string(entity));
        
        printEntityToIndexMap("Removing from map:",entityToIndexMap);
        if (entityToIndexMap.left.find(entity) == entityToIndexMap.left.end()) {
            throw ECSException(
                    "Removing non-existent component " + std::string(name) + " from entity " + std::to_string(entity));
        }
#endif
        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = entityToIndexMap.left.at(entity);
        size_t indexOfLastElement = size - 1;
        componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];
        
        // Update map to point to moved spot
        EntityID entityOfLastElement = entityToIndexMap.right.at(indexOfLastElement);
        entityToIndexMap.insert( { entityOfLastElement, indexOfRemovedEntity } );
        
        // Erase the entity from both maps
        entityToIndexMap.left.erase(entity);
        
        
        --size;
#ifdef DEBUG
        printEntityToIndexMap("Map after removing:",entityToIndexMap);
#endif
    }
    
    T &getData(EntityID entity) {
#ifdef DEBUG
        //const char *name = typeid(T).name();
        //Logger::get().importantInfo(
        //        "Accessing component \"" + std::string(name) + "\" from entity" + std::to_string(entity));
        
        //printEntityToIndexMap("Accessed map:",entityToIndexMap);
        if (entityToIndexMap.left.find(entity) == entityToIndexMap.left.end()) {
            throw ECSException("Retrieving non-existent component.");
        }
#endif
        // Return a reference to the entity's component
        return componentArray[entityToIndexMap.right.at(entity)];
    }
    /**
     * @brief Checks if the entity has a component of type T
     * @details The check is useful to avoid adding or removing unnecessarily
     * The remove and add components does not allow doing so, so this is a way to check
     * @param entity
     * @return
     */
    bool hasComponent(EntityID entity) override {
        return entityToIndexMap.left.find(entity) != entityToIndexMap.left.end();
    }
private:
    /**
     * @brief The packed array of components (of generic type T),
     * set to a specified maximum amount, matching the maximum number
     * of entities allowed to exist simultaneously, so that each entity
     * has a unique spot.
     */
    std::array <T, maxEntities> componentArray;
    
    /**
     * @brief Map from an entity ID to an array index.
     *
     */
    boost::bimap <EntityID, size_t> entityToIndexMap;
    
    /**
     * @brief Total size of valid entries in the array.
     *
     */
    size_t size{};
};