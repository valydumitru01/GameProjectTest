/**************************************************************************************************
 * @file   Frustum.h
 * @author Valentin Dumitru
 * @date   11/12/2023
 * @brief  Class for representing a frustum and performing intersection tests.
 *
 * This class represents a viewing frustum, which can be used for frustum culling
 * or visibility determination in 3D scenes. The frustum is defined by six planes.
 **************************************************************************************************/
#pragma once

#include "engine/core/math/geometry/figures/polyhedron/Polyhedron.h"

namespace GLESC::Render {
    class Frustum {
    public:
        Frustum() = default;

        [[nodiscard]] const std::array<Math::Plane, 6>& getPlanes() const {
            return planes;
        }

        /**
         * @brief Constructs a frustum from a camera transform and perspective.
         *
         * @param PVMatrix The combined view-projection matrix.
         */
        Frustum(const Mat4F& PVMatrix) {
            extractPlanes(PVMatrix);
        }

        /**
         * @brief Updates the frustum planes based on new view and projection matrices.
         *
         * @param VPMat The combined view-projection matrix.
         */
        void update(const VP& VPMat) {
            extractPlanes(VPMat);
        }

        /**
         * @brief Checks if the frustum intersects with a given bounding volume.
         * @details Returns true if any point is inside all the planes
         *
         * @param volume The bounding volume to test for intersection.
         * @return true If the frustum intersects the volume.
         * @return false If the frustum does not intersect the volume.
         */
        [[nodiscard]] bool contains(const BoundingVolume& volume) const {
            // Initially assume no point is inside all planes
            bool anyPointInsideAllPlanes = false;

            for (const Math::Point& point : volume.getTopology().getVertices()) {
                int insideCount = 0;
                for (const Math::Plane& plane : planes) {
                    if (plane.hasInside(point)) {
                        insideCount++;
                    }
                }
                // If the point is inside all planes, mark and break the loop as we found a point inside the frustum
                if (insideCount == planes.size()) {
                    anyPointInsideAllPlanes = true;
                    break; // Found a point inside all planes, no need to check further
                }
            }

            // Return true if at least one point is inside all planes, indicating intersection
            return anyPointInsideAllPlanes;
        }

        [[nodiscard]] bool contains(Position position) const {
            for (const Math::Plane& plane : planes) {
                if (!plane.hasInside(position)) {
                    return false;
                }
            }
            return true;
        }

    private:
        /**
         * @brief Extracts the frustum planes from a combined view-projection matrix. Uses Hartmann & Gribbs method.
         * It's done with row-major matrices.
         * @see https://web.archive.org/web/20210226045225/http://www.cs.otago.ac.nz/postgrads/alexis/planeExtraction.pdf
         *
         * @param PVMatrix The combined view-projection matrix.
         */
        void extractPlanes(const Mat4F& PVMatrix) {
            // Left clipping plane
            planes[0].setNormal(Math::Direction(PVMatrix[0][3] + PVMatrix[0][0],
                                                PVMatrix[1][3] + PVMatrix[1][0],
                                                PVMatrix[2][3] + PVMatrix[2][0]));
            planes[0].setDistance(PVMatrix[3][3] + PVMatrix[3][0]);
            planes[0].normalize();

            // Right clipping plane
            planes[1].setNormal(Math::Direction(PVMatrix[0][3] - PVMatrix[0][0],
                                                PVMatrix[1][3] - PVMatrix[1][0],
                                                PVMatrix[2][3] - PVMatrix[2][0]));
            planes[1].setDistance(PVMatrix[3][3] - PVMatrix[3][0]);
            planes[1].normalize();

            // Top clipping plane
            planes[2].setNormal(Math::Direction(PVMatrix[0][3] - PVMatrix[0][1],
                                                PVMatrix[1][3] - PVMatrix[1][1],
                                                PVMatrix[2][3] - PVMatrix[2][1]));
            planes[2].setDistance(PVMatrix[3][3] - PVMatrix[3][1]);
            planes[2].normalize();

            // Bottom clipping plane
            planes[3].setNormal(Math::Direction(PVMatrix[0][3] + PVMatrix[0][1],
                                                PVMatrix[1][3] + PVMatrix[1][1],
                                                PVMatrix[2][3] + PVMatrix[2][1]));
            planes[3].setDistance(PVMatrix[3][3] + PVMatrix[3][1]);
            planes[3].normalize();

            // Near clipping plane
            planes[4].setNormal(Math::Direction(PVMatrix[0][3] + PVMatrix[0][2],
                                                PVMatrix[1][3] + PVMatrix[1][2],
                                                PVMatrix[2][3] + PVMatrix[2][2]));
            planes[4].setDistance(PVMatrix[3][3] + PVMatrix[3][2]);
            planes[4].normalize();

            // Far clipping plane
            planes[5].setNormal(Math::Direction(PVMatrix[0][3] - PVMatrix[0][2],
                                                PVMatrix[1][3] - PVMatrix[1][2],
                                                PVMatrix[2][3] - PVMatrix[2][2]));
            planes[5].setDistance(PVMatrix[3][3] - PVMatrix[3][2]);
            planes[5].normalize();
        }

        std::array<Math::Plane, 6> planes{};
    }; // class Frustum
} // namespace GLESC::Render
