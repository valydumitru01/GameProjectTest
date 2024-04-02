/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once


#include "engine/core/window/WindowManager.h"
#include "mesh/MeshAdapter.h"
#include "engine/subsystems/renderer/RendererTypes.h"
#include "engine/subsystems/renderer/material/Material.h"
#include "../../core/low-level-renderer/shader/Shader.h"

#include "engine/subsystems/renderer/mesh/Mesh.h"
#include "engine/subsystems/transform/Transform.h"

#include "engine/subsystems/renderer/mesh/BatchMeshes.h"
#include "engine/subsystems/renderer/mesh/DynamicMeshes.h"
#include "engine/subsystems/renderer/mesh/InstanceMeshes.h"
#include "engine/subsystems/renderer/lighting/LightSpots.h"

#include "engine/subsystems/renderer/math/Frustum.h"
#include "lighting/GlobalAmbienLight.h"
#include "lighting/GlobalSun.h"

namespace GLESC::Render {
    class Renderer {
    public:
        explicit Renderer(WindowManager& windowManager);

        ~Renderer();

        [[nodiscard]] View getView() const { return view; }
        void setView(const View& viewParam) { this->view = viewParam; }

        [[nodiscard]] Projection getProjection() const { return projection; }
        void setProjection(const Projection& projectionParam) { this->projection = projectionParam; }

        [[nodiscard]] Transform::Transform getCameraTrasnform() const {
            return this->cameraTransform;
        }

        void setCameraTransform(Transform::Transform cameraTransformParam) {
            this->cameraTransform = cameraTransformParam;
        }

        void addLightSpot(const LightSpot& lightSpot, const Transform::Transform& transform) {
            lightSpots.addLight(lightSpot, transform);
        }

        [[nodiscard]] GAPI::Shader& getDefaultShader() { return shader; }
        [[nodiscard]] Frustum& getFrustum() { return frustum; }
        [[nodiscard]] const Frustum& getFrustum() const { return frustum; }

        void clear() const;

        void renderMesh(const ColorMesh& mesh);


        void renderInstances(const ColorMesh& mesh,
                             const std::vector<MeshInstanceData>& instances);


        void addData(const Material& material,
                     ColorMesh& mesh,
                     const Transform::Transform& transform);

        void addLight(const LightSpot& light, const Transform::Transform& transform);

        void renderMeshes(double timeOfFrame);

        void swapBuffers() const;

    private:
        void applyTransform(ColorMesh& mesh, const Transform::Transform& transform) const;
        void transformMeshCPU(ColorMesh& mesh, const Transform::Transform& transform);

        void applyLighting(LightSpots& lightSpots, GlobalSun& sun, GlobalAmbienLight ambientLight) const;
        void applyMaterial(const Material& material) const;
        void cacheMesh(const ColorMesh& mesh,
                       AdaptedMesh adaptedMesh);

        void cacheMesh(const ColorMesh& mesh,
                       AdaptedInstances adaptedInstancesParam);

        [[nodiscard]] bool isMeshNotCached(const ColorMesh& mesh) const;

        WindowManager& windowManager;

        std::unordered_map<const ColorMesh*, AdaptedMesh> adaptedMeshes;
        std::unordered_map<const ColorMesh*, AdaptedInstances> adaptedInstances;

        GAPI::Shader shader;
        Frustum frustum;

        InstanceMeshes meshInstances;
        MeshBatches meshBatches;
        DynamicMeshes dynamicMeshes;

        LightSpots lightSpots;
        GlobalSun globalSun;
        GlobalAmbienLight globalAmbienLight;

        Projection projection;
        View view;
        Transform::Transform cameraTransform;
    }; // class Renderer
} // namespace GLESC
