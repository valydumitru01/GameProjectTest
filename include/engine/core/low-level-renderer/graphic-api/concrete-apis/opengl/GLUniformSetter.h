/**************************************************************************************************
 * @file   GLUniformSetter.h
 * @author Valentin Dumitru
 * @date   2023-11-17
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <engine/core/exceptions/core/low-level-renderer/GAPIException.h>
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/debugger/GAPIDebugger.h"
#include "engine/core/low-level-renderer/graphic-api/IUniformSetter.h"
#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

namespace GLESC::GAPI {
    class GLUniformSetter : public IUniformSetter {
    public:
        /**
         * @brief Default constructor
         * @details The default constructor is needed to enable caching of uniform setters inside a map (and maps require
         * default constructors when the object is used as a value)
         */
        GLUniformSetter() = default;

        GLUniformSetter(GAPI::UInt uniformLocation) {
            this->location = uniformLocation;
        }

        // Implement single value setters
        void u1F(GAPI::Float v0) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1f", location, v0);
            glUniform1f(location, v0);
        }

        void u1I(GAPI::Int v0) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1i", location, v0);
            glUniform1i(location, v0);
        }

        void u1Ui(GAPI::UInt v0) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1ui", location, v0);
            glUniform1ui(location, v0);
        }

        void u1B(GAPI::Bool v0) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1i", location, static_cast<GAPI::Int>(v0));
            glUniform1i(location, static_cast<GAPI::Int>(v0));
        }


        // Single vectors
        // Floats
        void u2F(Vec2F vec2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2f", location, vec2.x(), vec2.y());
            glUniform2f(location, vec2.x(), vec2.y());
        }

        void u3F(Vec3F vec3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3f", location, vec3.x(), vec3.y(), vec3.z());
            glUniform3f(location, vec3.x(), vec3.y(), vec3.z());
        }

        void u4F(Vec4F vec4) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4f", location, vec4.x(), vec4.y(), vec4.z(),
                                             vec4.w());
            glUniform4f(location, vec4.x(), vec4.y(), vec4.z(), vec4.w());
        }

        void u2F(GAPI::Float vec2[2]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2f", location, vec2[0], vec2[1]);
            glUniform2f(location, vec2[0], vec2[1]);
        }

        void u3F(GAPI::Float vec3[3]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3f", location, vec3[0], vec3[1], vec3[2]);
            glUniform3f(location, vec3[0], vec3[1], vec3[2]);
        }

        void u4F(GAPI::Float vec4[4]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4f", location, vec4[0], vec4[1], vec4[2],
                                             vec4[3]);
            glUniform4f(location, vec4[0], vec4[1], vec4[2], vec4[3]);
        }

        void u2F(GAPI::Float v0, GAPI::Float v1) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2f", location, v0, v1);
            glUniform2f(location, v0, v1);
        }

        void u3F(GAPI::Float v0, GAPI::Float v1, GAPI::Float v2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3f", location, v0, v1, v2);
            glUniform3f(location, v0, v1, v2);
        }

        void u4F(GAPI::Float v0, GAPI::Float v1, GAPI::Float v2, GAPI::Float v3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4f", location, v0, v1, v2, v3);
            glUniform4f(location, v0, v1, v2, v3);
        }

        // Ints
        void u2I(Vec2I vec2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, vec2.x(), vec2.y());
            glUniform2i(location, vec2.x(), vec2.y());
        }

        void u3I(Vec3I vec3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, vec3.x(), vec3.y(), vec3.z());
            glUniform3i(location, vec3.x(), vec3.y(), vec3.z());
        }

        void u4I(Vec4I vec4) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, vec4.x(), vec4.y(), vec4.z(),
                                             vec4.w());
            glUniform4i(location, vec4.x(), vec4.y(), vec4.z(), vec4.w());
        }

        void u2I(GAPI::Int vec2[2]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, vec2[0], vec2[1]);
            glUniform2i(location, vec2[0], vec2[1]);
        }

        void u3I(GAPI::Int vec3[3]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, vec3[0], vec3[1], vec3[2]);
            glUniform3i(location, vec3[0], vec3[1], vec3[2]);
        }

        void u4I(GAPI::Int vec4[4]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, vec4[0], vec4[1], vec4[2],
                                             vec4[3]);
            glUniform4i(location, vec4[0], vec4[1], vec4[2], vec4[3]);
        }

        void u2I(GAPI::Int v0, GAPI::Int v1) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, v0, v1);
            glUniform2i(location, v0, v1);
        }

        void u3I(GAPI::Int v0, GAPI::Int v1, GAPI::Int v2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, v0, v1, v2);
            glUniform3i(location, v0, v1, v2);
        }

        void u4I(GAPI::Int v0, GAPI::Int v1, GAPI::Int v2, GAPI::Int v3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, v0, v1, v2, v3);
            glUniform4i(location, v0, v1, v2, v3);
        }

        // Unsigned ints
        void u2Ui(Vec2Ui vec2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2ui", location, vec2.x(), vec2.y());
            glUniform2ui(location, vec2.x(), vec2.y());
        }

        void u3Ui(Vec3Ui vec3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3ui", location, vec3.x(), vec3.y(), vec3.z());
            glUniform3ui(location, vec3.x(), vec3.y(), vec3.z());
        }

        void u4Ui(Vec4Ui vec4) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4ui", location, vec4.x(), vec4.y(), vec4.z(),
                                             vec4.w());
            glUniform4ui(location, vec4.x(), vec4.y(), vec4.z(), vec4.w());
        }

        void u2Ui(GAPI::UInt vec2[2]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2ui", location, vec2[0], vec2[1]);
            glUniform2ui(location, vec2[0], vec2[1]);
        }

        void u3Ui(GAPI::UInt vec3[3]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3ui", location, vec3[0], vec3[1], vec3[2]);
            glUniform3ui(location, vec3[0], vec3[1], vec3[2]);
        }

        void u4Ui(GAPI::UInt vec4[4]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4ui", location, vec4[0], vec4[1], vec4[2],
                                             vec4[3]);
            glUniform4ui(location, vec4[0], vec4[1], vec4[2], vec4[3]);
        }

        void u2Ui(GAPI::UInt v0, GAPI::UInt v1) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2ui", location, v0, v1);
            glUniform2ui(location, v0, v1);
        }

        void u3Ui(GAPI::UInt v0, GAPI::UInt v1, GAPI::UInt v2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3ui", location, v0, v1, v2);
            glUniform3ui(location, v0, v1, v2);
        }

        void u4Ui(GAPI::UInt v0, GAPI::UInt v1, GAPI::UInt v2, GAPI::UInt v3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4ui", location, v0, v1, v2, v3);
            glUniform4ui(location, v0, v1, v2, v3);
        }

        // Booleans
        void u2B(Vec2B vec2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, static_cast<GAPI::Int>(vec2.x()),
                                             static_cast<GAPI::Int>(vec2.y()));
            glUniform2i(location, static_cast<GAPI::Int>(vec2.x()),
                        static_cast<GAPI::Int>(vec2.y()));
        }

        void u3B(Vec3B vec3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, static_cast<GAPI::Int>(vec3.x()),
                                             static_cast<GAPI::Int>(vec3.y()),
                                             static_cast<GAPI::Int>(vec3.z()));
            glUniform3i(location, static_cast<GAPI::Int>(vec3.x()),
                        static_cast<GAPI::Int>(vec3.y()),
                        static_cast<GAPI::Int>(vec3.z()));
        }

        void u4B(Vec4B vec4) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, static_cast<GAPI::Int>(vec4.x()),
                                             static_cast<GAPI::Int>(vec4.y()),
                                             static_cast<GAPI::Int>(vec4.z()),
                                             static_cast<GAPI::Int>(vec4.w()));
            glUniform4i(location, static_cast<GAPI::Int>(vec4.x()),
                        static_cast<GAPI::Int>(vec4.y()),
                        static_cast<GAPI::Int>(vec4.z()), static_cast<GAPI::Int>(vec4.w()));
        }

        void u2B(GAPI::Bool vec2[2]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, static_cast<GAPI::Int>(vec2[0]),
                                             static_cast<GAPI::Int>(vec2[1]));
            glUniform2i(location, static_cast<GLboolean>(vec2[0]), static_cast<GAPI::Int>(vec2[1]));
        }

        void u3B(GAPI::Bool vec3[3]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, static_cast<GAPI::Int>(vec3[0]),
                                             static_cast<GAPI::Int>(vec3[1]),
                                             static_cast<GAPI::Int>(vec3[2]));
            glUniform3i(location, static_cast<GLboolean>(vec3[0]), static_cast<GAPI::Int>(vec3[1]),
                        static_cast<GAPI::Int>(vec3[2]));
        }

        void u4B(GAPI::Bool vec4[4]) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, static_cast<GAPI::Int>(vec4[0]),
                                             static_cast<GAPI::Int>(vec4[1]),
                                             static_cast<GAPI::Int>(vec4[2]),
                                             static_cast<GAPI::Int>(vec4[3]));
            glUniform4i(location, static_cast<GAPI::Int>(vec4[0]), static_cast<GAPI::Int>(vec4[1]),
                        static_cast<GAPI::Int>(vec4[2]), static_cast<GAPI::Int>(vec4[3]));
        }

        void u2B(GAPI::Bool v0, GAPI::Bool v1) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2i", location, static_cast<GAPI::Int>(v0),
                                             static_cast<GAPI::Int>(v1));
            glUniform2i(location, static_cast<GAPI::Int>(v0), static_cast<GAPI::Int>(v1));
        }

        void u3B(GAPI::Bool v0, GAPI::Bool v1, GAPI::Bool v2) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3i", location, static_cast<GAPI::Int>(v0),
                                             static_cast<GAPI::Int>(v1), static_cast<GAPI::Int>(v2));
            glUniform3i(location, static_cast<GAPI::Int>(v0), static_cast<GAPI::Int>(v1),
                        static_cast<GAPI::Int>(v2));
        }

        void u4B(GAPI::Bool v0, GAPI::Bool v1, GAPI::Bool v2, GAPI::Bool v3) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4i", location, static_cast<GAPI::Int>(v0),
                                             static_cast<GAPI::Int>(v1), static_cast<GAPI::Int>(v2),
                                             static_cast<GAPI::Int>(v3));
            glUniform4i(location, static_cast<GAPI::Int>(v0), static_cast<GAPI::Int>(v1),
                        static_cast<GAPI::Int>(v2), static_cast<GAPI::Int>(v3));
        }


        // Single matrices
        // Floats
        void uMat2F(Mat2F mat) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix2fv", location, 1, GL_FALSE, mat);
            glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
        }

        void uMat3F(Mat3F mat) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix3fv", location, 1, GL_FALSE, mat);
            glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
        }

        void uMat4F(Mat4F mat) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix4fv", location, 1, GL_FALSE, mat);
            glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
        }

        // Single matrices
        // Doubles
        void uMat2D(Mat2D mat) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix2dv", location, 1, GL_FALSE, mat);
            glUniformMatrix2dv(location, 1, GL_FALSE, &mat[0][0]);
        }

        void uMat3D(Mat3D mat) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix3dv", location, 1, GL_FALSE, mat);
            glUniformMatrix3dv(location, 1, GL_FALSE, &mat[0][0]);
        }

        void uMat4D(Mat4D mat) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix4dv", location, 1, GL_FALSE, mat);
            glUniformMatrix4dv(location, 1, GL_FALSE, &mat[0][0]);
        }

        // Vectors of vectors
        // Floats
        void u1FVec(const std::vector<GAPI::Float> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1fv", location,
                                             static_cast<GLsizei>(values.size()), values.data());
            glUniform1fv(location, static_cast<GLsizei>(values.size()), values.data());
        }

        void u2FVec(const std::vector<Vec2F> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2fv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLfloat *>(values.data()));
            glUniform2fv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLfloat *>(values.data()));
        }

        void u3FVec(const std::vector<Vec3F> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3fv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLfloat *>(values.data()));
            glUniform3fv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLfloat *>(values.data()));
        }

        void u4FVec(const std::vector<Vec4F> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4fv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLfloat *>(values.data()));
            glUniform4fv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLfloat *>(values.data()));
        }

        // Ints
        void u1IVec(const std::vector<GAPI::Int> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform1iv(location, static_cast<GLsizei>(values.size()), values.data());
        }

        void u2IVec(const std::vector<Vec2I> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform2iv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLint *>(values.data()));
        }

        void u3IVec(const std::vector<Vec3I> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform3iv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLint *>(values.data()));
        }

        void u4IVec(const std::vector<Vec4I> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform4iv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLint *>(values.data()));
        }

        // Unsigned ints
        void u1UiVec(const std::vector<GAPI::UInt> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1uiv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLuint *>(values.data()));
            glUniform1uiv(location, static_cast<GLsizei>(values.size()), values.data());
        }

        void u2UiVec(const std::vector<Vec2Ui> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2uiv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLuint *>(values.data()));
            glUniform2uiv(location, static_cast<GLsizei>(values.size()),
                          reinterpret_cast<const GLuint *>(values.data()));
        }

        void u3UiVec(const std::vector<Vec3Ui> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3uiv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLuint *>(values.data()));
            glUniform3uiv(location, static_cast<GLsizei>(values.size()),
                          reinterpret_cast<const GLuint *>(values.data()));
        }

        void u4UiVec(const std::vector<Vec4Ui> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4uiv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLuint *>(values.data()));
            glUniform4uiv(location, static_cast<GLsizei>(values.size()),
                          reinterpret_cast<const GLuint *>(values.data()));
        }

        // Booleans
        void u1BVec(const std::vector<GAPI::Bool> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform1iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform1iv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLint *>(values.data()));
        }

        void u2BVec(const std::vector<Vec2B> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform2iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform2iv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLint *>(values.data()));
        }

        void u3BVec(const std::vector<Vec3B> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform3iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform3iv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLint *>(values.data()));
        }

        void u4BVec(const std::vector<Vec4B> &values) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniform4iv", location,
                                             static_cast<GLsizei>(values.size()),
                                             reinterpret_cast<const GLint *>(values.data()));
            glUniform4iv(location, static_cast<GLsizei>(values.size()),
                         reinterpret_cast<const GLint *>(values.data()));
        }


        // Multiple matrices
        void uMat2FVec(const std::vector<Mat2F> &mats) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix2fv", location,
                                             static_cast<GLsizei>(mats.size()), GL_FALSE,
                                             reinterpret_cast<const GLfloat *>(mats.data()));
            glUniformMatrix2fv(location, static_cast<GLsizei>(mats.size()), GL_FALSE,
                               reinterpret_cast<const GLfloat *>(mats.data()));
        }

        void uMat3FVec(const std::vector<Mat3F> &mats) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix3fv", location,
                                             static_cast<GLsizei>(mats.size()), GL_FALSE,
                                             reinterpret_cast<const GLfloat *>(mats.data()));
            glUniformMatrix3fv(location, static_cast<GLsizei>(mats.size()), GL_FALSE,
                               reinterpret_cast<const GLfloat *>(mats.data()));
        }

        void uMat4FVec(const std::vector<Mat4F> &mats) override {
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUniformMatrix4fv", location,
                                             static_cast<GLsizei>(mats.size()), GL_FALSE,
                                             reinterpret_cast<const GLfloat *>(mats.data()));
            glUniformMatrix4fv(location, static_cast<GLsizei>(mats.size()), GL_FALSE,
                               reinterpret_cast<const GLfloat *>(mats.data()));
        }

    private:
        GAPI::UInt location;
    };
}
