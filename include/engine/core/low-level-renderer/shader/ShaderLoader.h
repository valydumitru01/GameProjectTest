/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once
#include <string>
#include <unordered_map>

#include "engine/core/low-level-renderer/graphic-api/GapiTypes.h"

namespace GLESC::GAPI
{
    class ShaderLoader
    {
    public:
        static UInt loadShader(const std::string& fileName, const std::vector<std::string>& macros = {});
        static UInt loadShader(const std::string& vertexShaderSourceParam,
                               const std::string& fragmentShaderSourceParam,
                               const std::vector<std::string>& macros = {});

    private:
        /**
         * @brief Source of the vertex shader
         *
         */
        static std::string vertexShaderSource;
        /**
         * @brief Source of the fragment shader
         *
         */
        static std::string fragmentShaderSource;
        /**
         * @brief ID reference to the vertex shader
         *
         */
        static GAPI::UInt vertexShader;
        /**
         * @brief ID reference to the fragment shader
         *
         */
        static GAPI::UInt fragmentShader;

        /**
         * @brief Loads the vertex shader
         * Sets the actual coordinates of the vertices in the GPU
         */
        static GAPI::UInt loadVertexShader(const std::string& vertexShaderSourceParam);

        /**
         * @brief Loads the fragment shader
         * Calculates colors of pixels (a fragment is a pixel in OpenGL)
         */
        static GAPI::UInt loadFragmentShader(const std::string& fragmentShaderSourceParam);

        /**
         * @brief Links the loaded shaders into the shader program
         *
         */
        static GAPI::UInt createShaderProgram();

        static void extractShaderCode(const std::string& shaderSource,
                                      std::string& vertexCode,
                                      std::string& fragmentCode);
        static void prependGLSLVersion(std::string& vertexCode, std::string& fragmentCode);
        static void insertShaderMacros(std::string& vertexCode, std::string& fragmentCode,
                                       const std::vector<std::string>& macros);
        static std::string getGLSLVersionString();
        static void validateShaderTokens(size_t vertexPos, size_t fragmentPos);
        static void validateShaderCodes(const std::string& vertexCode, const std::string& fragmentCode);


        /**
         * @brief Clean the shader loader
         * Once the shaders are linked, they can be cleared as they are
         * no longer needed.
         */
        static void clean();
        /**
         * @brief Map of names of the shaders and their IDs
         * Once the shader is created, we assign the name to the ID
         * This is used to identify the shader in case of handling an error
         *
         */
        static std::unordered_map<unsigned int, const char*> shaderNamesMap;
    };
}
