/**************************************************************************************************
 * @file   ComponentManagerTests.cpp
 * @author Valentin Dumitru
 * @date   29/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/

#include "TestsConfig.cpp"
#if ECS_BACKEND_UNIT_TESTING
#include <gtest/gtest.h>
#include "engine/ecs/backend/component/ComponentManager.h"
#include "unit/CustomTestingFramework.cpp"

class ComponentManagerTests : public testing::Test {
protected:
    ComponentManagerTests() = default;

    void SetUp() override {}

    void TearDown() override {}

    struct TestComponent1 : IComponent {
        TestComponent1() = default;
        explicit TestComponent1(int x) : x(x) {}
        int x{};
        std::string toString() override { return "x: " + std::to_string(x); }
    };

    struct TestComponent2 : IComponent {
        TestComponent2() = default;
        explicit TestComponent2(int y) : y(y) {}
        int y{};
        std::string toString() override { return "y: " + std::to_string(y); }
    };

    struct TestComponent3 : IComponent {
        TestComponent3() = default;
        explicit TestComponent3(int z) : z(z) {}
        int z{};
        std::string toString() override { return "z: " + std::to_string(z); }
    };

    TestComponent1 testComponent1{3};
    TestComponent2 testComponent2{4};
    TestComponent3 testComponent3{5};
    GLESC::ECS::ComponentID firstComponentID{1};

    GLESC::ECS::ComponentManager& getComponentManager() {
        return componentManager;
    }

    GLESC::ECS::ComponentManager componentManager;
};

TEST_F(ComponentManagerTests, EmptyState) {
    ASSERT_TRUE(getComponentManager().getComponentIDs().empty());
    ASSERT_TRUE(getComponentManager().getComponentArrays().empty());
    ASSERT_TRUE(
        getComponentManager().getNextComponentID() == firstComponentID);
}

TEST_F(ComponentManagerTests, RegisterComponent) {
    getComponentManager().registerComponent<TestComponent1>();

    TEST_SECTION("Check ComponentManager interface");
    // Component is registered inside the component manager
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent1>());
    // Component has the correct ID
    ASSERT_TRUE(getComponentManager().getComponentID<TestComponent1>() == firstComponentID);
    // Component has the correct name
    ASSERT_TRUE(GLESC::Stringer::contains(getComponentManager().getComponentName(firstComponentID), "TestComponent1"));



    TEST_SECTION("Check manually data structures")
    // The size of the component arrays array is one
    ASSERT_TRUE(getComponentManager().getComponentArrays().size() == 1);
    // Check the content of the component arrays array
    GLESC::ECS::IComponentArray& componentArray = *getComponentManager().getComponentArrays().at(
        getComponentManager().getComponentName(firstComponentID));
    // It starts out empty
    ASSERT_TRUE(componentArray.getSize() == 0);
    // The size of the component IDs array is one, for the ID of the component we just registered
    ASSERT_TRUE(getComponentManager().getComponentIDs().size() == 1);
    // The next component ID is the one after the one we just registered
    ASSERT_TRUE(getComponentManager().getNextComponentID() == firstComponentID + 1);
}

TEST_F(ComponentManagerTests, RegisterAlreadyRegisteredComponent) {
    getComponentManager().registerComponent<TestComponent1>();
    EXPECT_THROW(getComponentManager().registerComponent<TestComponent1>(), AssertFailedException);
}

TEST_F(ComponentManagerTests, RegisterIfNotRegistered) {
    // Recister a component once
    getComponentManager().registerComponentIfNotRegistered<TestComponent1>();
    // Register a component twice
    getComponentManager().registerComponentIfNotRegistered<TestComponent2>();
    getComponentManager().registerComponentIfNotRegistered<TestComponent2>();
    // Register a component twice again
    getComponentManager().registerComponentIfNotRegistered<TestComponent3>();
    getComponentManager().registerComponentIfNotRegistered<TestComponent3>();

    TEST_SECTION("Check ComponentManager interface");
    // Check if the components are registered
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent1>());
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent2>());
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent3>());
}

TEST_F(ComponentManagerTests, AddComponentToEntity) {
    // Components should automatically get registered

    // Add the components to the entity
    GLESC::ECS::EntityID entityID = 1;
    getComponentManager().addComponentToEntity(entityID, testComponent1);
    getComponentManager().addComponentToEntity(entityID, testComponent2);
    getComponentManager().addComponentToEntity(entityID, testComponent3);

    TEST_SECTION("Check ComponentManager interface");
    // Check if the components are registered
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent1>());
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent2>());
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent3>());
    // Check if the components are added to the entity
    ASSERT_TRUE(getComponentManager().getComponent<TestComponent1>(entityID).x == testComponent1.x);
    ASSERT_TRUE(getComponentManager().getComponent<TestComponent2>(entityID).y == testComponent2.y);
    ASSERT_TRUE(getComponentManager().getComponent<TestComponent3>(entityID).z == testComponent3.z);

    TEST_SECTION("Check manually data structures")
    // The size of the component arrays array is three
    ASSERT_TRUE(getComponentManager().getComponentArrays().size() == 3);
    // Check the content of the component arrays array
    GLESC::ECS::IComponentArray& componentArrayTestComponent1 = *getComponentManager().getComponentArrays().at(
        getComponentManager().getComponentName(getComponentManager().getComponentID<TestComponent1>()));
    GLESC::ECS::IComponentArray& componentArrayTestComponent2 = *getComponentManager().getComponentArrays().at(
        getComponentManager().getComponentName(getComponentManager().getComponentID<TestComponent2>()));
    GLESC::ECS::IComponentArray& componentArrayTestComponent3 = *getComponentManager().getComponentArrays().at(
        getComponentManager().getComponentName(getComponentManager().getComponentID<TestComponent3>()));

    ASSERT_TRUE(componentArrayTestComponent1.getSize() == 1);
    ASSERT_TRUE(componentArrayTestComponent1.getComponent(0).toString() == testComponent1.toString());
    ASSERT_TRUE(componentArrayTestComponent2.getSize() == 1);
    ASSERT_TRUE(componentArrayTestComponent2.getComponent(0).toString() == testComponent2.toString());
    ASSERT_TRUE(componentArrayTestComponent3.getSize() == 1);
    ASSERT_TRUE(componentArrayTestComponent3.getComponent(0).toString() == testComponent3.toString());
}

TEST_F(ComponentManagerTests, RemoveComponentFromEntity) {
    // Components should automatically get registered

    // Add the components to the entity
    GLESC::ECS::EntityID entityID = 1;
    getComponentManager().addComponentToEntity(entityID, testComponent1);
    getComponentManager().addComponentToEntity(entityID, testComponent2);
    getComponentManager().addComponentToEntity(entityID, testComponent3);

    // Remove the components from the entity
    getComponentManager().removeComponent<TestComponent1>(entityID);
    getComponentManager().removeComponent<TestComponent2>(entityID);
    getComponentManager().removeComponent<TestComponent3>(entityID);

    TEST_SECTION("Check ComponentManager interface");
    // Check if the components are registered
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent1>());
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent2>());
    ASSERT_TRUE(getComponentManager().isComponentRegistered<TestComponent3>());
    // Check if the components are removed from the entity
    ASSERT_THROW(getComponentManager().getComponent<TestComponent1>(entityID), AssertFailedException);
    ASSERT_THROW(getComponentManager().getComponent<TestComponent2>(entityID), AssertFailedException);
    ASSERT_THROW(getComponentManager().getComponent<TestComponent3>(entityID), AssertFailedException);

    TEST_SECTION("Check manually data structures")
    // The size of the component arrays array is three
    ASSERT_TRUE(getComponentManager().getComponentArrays().size() == 3);
    // Check the content of the component arrays array
    GLESC::ECS::IComponentArray& componentArrayTestComponent1 = *getComponentManager().getComponentArrays().at(
        getComponentManager().getComponentName(getComponentManager().getComponentID<TestComponent1>()));
    GLESC::ECS::IComponentArray& componentArrayTestComponent2 = *getComponentManager().getComponentArrays().at(
        getComponentManager().getComponentName(getComponentManager().getComponentID<TestComponent2>()));
    GLESC::ECS::IComponentArray& componentArrayTestComponent3 = *getComponentManager().getComponentArrays().at(
        getComponentManager().getComponentName(getComponentManager().getComponentID<TestComponent3>()));

    ASSERT_TRUE(componentArrayTestComponent1.getSize() == 0);
    ASSERT_TRUE(componentArrayTestComponent2.getSize() == 0);
    ASSERT_TRUE(componentArrayTestComponent3.getSize() == 0);
}
#endif // ECS_BACKEND_UNIT_TESTING