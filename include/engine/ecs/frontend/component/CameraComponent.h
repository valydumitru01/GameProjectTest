/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "IComponent.h"
#include "engine/core/math/debugger/MathDebugger.h"
#include "engine/core/math/algebra/matrix/Matrix.h"
#include "engine/core/math/geometry/GeometryTypes.h"
#include "engine/subsystems/renderer/RendererTypes.h"

namespace GLESC::ECS {
    struct CameraComponent : IComponent {
        Render::View view{};
        Math::Distance fovDegrees{45};
        Math::Distance viewWidth; // This will be set to the window width
        Math::Distance viewHeight; // This will be set to the window height
        Math::Distance nearPlane{0.1};
        Math::Distance farPlane{100};

        float sensitivity{3.f};


        std::string toString() const override {
            return std::string("\n\tview: \n")
                + view.toString()
                + std::string("\n\tfov: ")
                + std::to_string(fovDegrees)
                + std::string("\n\tviewWidth: ")
                + std::to_string(viewWidth)
                + std::string("\n\tviewHeight: ")
                + std::to_string(viewHeight)
                + std::string("\n\tnearPlane: ")
                + std::to_string(nearPlane)
                + std::string("\n\tfarPlane: ")
                + std::to_string(farPlane);
        }

        std::string getName() const override {
            return "CameraComponent";
        }
    };
} // namespace GLESC::ECS
