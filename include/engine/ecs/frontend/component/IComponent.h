/******************************************************************************
 * @file   IComponent.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 * @brief @todo
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <string>

namespace GLESC::ECS {
    /**
     * @brief Base class for all components
     * @details All components must inherit from this class and
     * must implement all the pure virtual functions.
     * This is necessary for the derived classes to be used in the ECS.
     */
    struct IComponent {
        virtual ~IComponent() = default;
        /**
         * @brief Each component must have a toString function
         * @details This is needed because when we want to debug the
         * content of the components, we need to be able to
         * do it without knowing the specific type of the component.
         * This is because we are using a vector of IComponents.
         * @return
         */
        virtual std::string toString() const = 0;

        virtual std::string getName() const = 0;
    };
} // namespace GLESC::ECS
