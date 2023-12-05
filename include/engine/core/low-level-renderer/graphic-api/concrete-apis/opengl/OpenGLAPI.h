/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <functional>
#include <string>

#include "engine/Config.h"
#include "engine/core/exceptions/core/low-level-renderer/GAPIInitException.h"
#include "engine/core/logger/Logger.h"
#include "engine/core/low-level-renderer/asserts/GAPIAsserts.h"
#include "engine/core/low-level-renderer/graphic-api/IGraphicInterface.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/debugger/GAPIDebugger.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/GLUniformSetter.h"
#include "engine/core/low-level-renderer/graphic-api/concrete-apis/opengl/debugger/OpenGLDebugger.h"
#include "engine/core/math/Vec.h"

namespace GLESC {
    class OpenGLAPI final : public IGraphicInterface {
    public:
        explicit OpenGLAPI() {
            D_ASSERT_GL_CORRECT_VERSION();
        }
        
        
        void deleteTexture(GAPI::UInt textureID) override {
            GAPI_FUNCTION_LOG("deleteTexture", textureID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteTextures", textureID);
            glDeleteTextures(1, &textureID);
        }
        
        void deleteContext() override {
            GAPI_FUNCTION_NO_ARGS_LOG("deleteContext");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_DeleteContext", this->context);
            SDL_GL_DeleteContext(this->context);
        }
        
        void setViewport(GAPI::Int width, GAPI::Int height) override {
            this->setViewport(0, 0, width, height);
        }
        
        void setViewport(GAPI::Int x, GAPI::Int y, GAPI::Int width, GAPI::Int height) override {
            GAPI_FUNCTION_LOG("setViewport", x, y, width, height);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glViewport", x, y, width, height);
            glViewport(x, y, width, height);
        }
        
        GAPI::Viewport getViewport() override {
            GAPI_FUNCTION_NO_ARGS_LOG("getViewport");
            GAPI::Int viewport[4];
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetIntegerv", GL_VIEWPORT, viewport);
            glGetIntegerv(GL_VIEWPORT, viewport);
            return GAPI::Viewport{viewport[0], viewport[1], viewport[2], viewport[3]};
        }
        
        GAPI::UInt createTexture(GAPI::Texture::Filters::Min minFilter,
                                 GAPI::Texture::Filters::Mag magFilter,
                                 GAPI::Texture::Filters::WrapMode wrapS,
                                 GAPI::Texture::Filters::WrapMode wrapT) override {
            GAPI_FUNCTION_LOG("createTexture", "SDL_Surface", minFilter, magFilter, wrapS, wrapT);
            
            auto minFilterGL = static_cast<GLenum>(minFilter);
            auto magFilterGL = static_cast<GLenum>(magFilter);
            auto wrapSGL = static_cast<GLenum>(wrapS);
            auto wrapTGL = static_cast<GLenum>(wrapT);
            
            int numTextures = 1;
            GAPI::UInt textureID = 0;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGenTextures", numTextures, &textureID);
            glGenTextures(numTextures, &textureID);
            
            bindTexture(textureID);
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", GL_TEXTURE_2D,
                                             GL_TEXTURE_MIN_FILTER,
                                             minFilterGL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterGL);
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", GL_TEXTURE_2D,
                                             GL_TEXTURE_MAG_FILTER,
                                             magFilterGL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterGL);
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", GL_TEXTURE_2D,
                                             GL_TEXTURE_WRAP_S,
                                             wrapSGL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapSGL);
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexParameteri", GL_TEXTURE_2D,
                                             GL_TEXTURE_WRAP_T,
                                             wrapTGL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapTGL);
            
            return textureID;
        }
        
        GAPI::Void setTextureData(GAPI::Int level,
                                  GAPI::UInt width,
                                  GAPI::UInt height,
                                  GAPI::UByte *texelBuffer) override {
            GAPI_FUNCTION_LOG("setTextureData", level, height, width, "texelBuffer");
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glTexImage2D", GL_TEXTURE_2D, level, GL_RGBA8,
                                             width, height, 0, texelBuffer);
            
            // TODO: Add support for non-alpha textures to reduce memory usage
            glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA8, width, height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, texelBuffer);
        }
        
        
        GAPI::Void bindTexture(GAPI::UInt textureID) override {
            GAPI_FUNCTION_LOG("bindTexture", textureID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindTexture", GL_TEXTURE_2D, textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
        
        GAPI::Void bindTextureOnSlot(GAPI::UInt textureID, GAPI::UInt slot) override {
            GAPI_FUNCTION_LOG("bindTextureOnSlot", textureID, slot);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glActiveTexture", GL_TEXTURE0 + slot);
            glActiveTexture(GL_TEXTURE0 + slot);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindTexture", GL_TEXTURE_2D, textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
        
        GAPI::Void unbindTexture() override {
            GAPI_FUNCTION_NO_ARGS_LOG("unbindTexture");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindTexture", GL_TEXTURE_2D, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        
        void swapBuffers(SDL_Window &window) override {
            GAPI_FUNCTION_LOG("swapBuffers", "SDL_Window");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_SwapWindow", "SDL_Window");
            SDL_GL_SwapWindow(&window);
        }
        
        [[nodiscard]] SDL_GLContext getContext() const { return context; };
        
        void preWindowCreationInit() override {
            PRINT_GAPI_INIT("OpenGL", std::to_string(GLESC_GL_MAJOR_VERSION) + "." +
                                      std::to_string(GLESC_GL_MINOR_VERSION));
            // Core functions of OpenGL a.k.a. full modern openGL functionality.
            // More info: https://wiki.libsdl.org/SDL_GLprofile
            #ifdef GLESC_GLSL_CORE_PROFILE
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_PROFILE_MASK",
                                             SDL_GL_CONTEXT_PROFILE_CORE);
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            #else
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_PROFILE_MASK",
                                             SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
            setSDLGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
            #endif
            // We're using OpenGL Version 4.3 (released in 2012).
            // Changing this numbers will change some functions available of OpenGL.
            // Choosing a relatively old version of OpenGl allow most computers to use it.
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_MAJOR_VERSION",
                                             GLESC_GL_MAJOR_VERSION);
            setSDLGLAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GLESC_GL_MAJOR_VERSION);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CONTEXT_MINOR_VERSION",
                                             GLESC_GL_MINOR_VERSION);
            setSDLGLAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GLESC_GL_MINOR_VERSION);
            // Stencil size of 4 bits is used
            // Could be increased later if needed
            // Increases performance the lower it is, fewer data stored in each pixel
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_STENCIL_SIZE", 4);
            setSDLGLAttribute(SDL_GL_STENCIL_SIZE, 4);
            // Enable debug context
            // Possible performance loss
            GL_SET_DEBUG_CONTEXT_ATTRIBUTE();
        }
        
        void postWindowCreationInit() override {
            // Initialize GLEW, must be called before the following OpenGL calls
            initGLEW();
            
            GLESC::Logger::get().success("Glew Initialized!");
            // Enable depth test
            // Fragments will be discarded if they are behind
            // More info: https://www.khronos.org/opengl/wiki/Depth_Test
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnable", GL_DEPTH_TEST);
            glEnable(GL_DEPTH_TEST);
            // Accept fragment if it closer to the camera than the former one
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDepthFunc", GL_LESS);
            glDepthFunc(GL_LESS);
            // Enable back face culling
            // Important for performance
            // More info: https://www.khronos.org/opengl/wiki/Face_Culling
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnable", GL_CULL_FACE);
            glEnable(GL_CULL_FACE);
            // Cull back faces (default)
            // Important for performance and to avoid self-shadowing
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCullFace", GL_BACK);
            glCullFace(GL_BACK);
            // Set the front face to be counter-clockwise (default)
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glFrontFace", GL_CCW);
            glFrontFace(GL_CCW);
            // Enable blending
            // Important for transparency and other effects
            // More info: https://www.khronos.org/opengl/wiki/Blending
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnable", GL_BLEND);
            glEnable(GL_BLEND);
            // Set blending function to alpha blending (default)
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBlendFunc", GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            // Set blending equation to add (default)
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBlendEquation", GL_FUNC_ADD);
            glBlendEquation(GL_FUNC_ADD);
            
            // Enable opengl debug callback
            // Improves debugging outputs
            GL_ENABLE_DEBUG_CALLBACK();
            
            // This makes our buffer swap synchronized with the monitor's vertical refresh
            // Parameters: 0 for immediate updates,
            // 1 for updates synchronized with the vertical retrace,
            // -1 for adaptive v-sync
            // More info: https://wiki.libsdl.org/SDL2/SDL_GL_SetSwapInterval
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_SetSwapInterval", 1);
            if (SDL_GL_SetSwapInterval(1) == -1)
                throw EngineException(std::string("Unable activate v-sync (swap interval): ") +
                                      std::string(SDL_GetError()));
        }
        
        void drawTriangles(GAPI::UInt start, GAPI::UInt count) override {
            GAPI_FUNCTION_LOG("drawTriangles", start, count);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDrawArrays", GL_TRIANGLES, start, count);
            glDrawArrays(static_cast<GLenum>(GAPI::PrimitiveTypes::Triangles), start, count);
        }
        
        void drawTrianglesIndexed(GAPI::UInt indicesCount) override {
            GAPI_FUNCTION_LOG("drawTrianglesIndexed", indicesCount);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDrawElements", GL_TRIANGLES, indicesCount,
                                             GL_UNSIGNED_INT, nullptr);
            glDrawElements(static_cast<GLenum>(GAPI::PrimitiveTypes::Triangles),
                           indicesCount,
                           static_cast<GLenum>(GAPI::Types::UInt),
                           nullptr);
        }
        
        
        GAPI::RGBColor readPixelColor(int x, int y) {
            GAPI_FUNCTION_LOG("readPixelColor", x, y);
            GAPI::RGBColor color;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_UNSIGNED_BYTE, color.r, color.g, color.b, color.a);
            glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_UNSIGNED_BYTE, color.r, color.g, color.b, color.a);
            return color;
        }
        
        GAPI::RGBColorNormalized readPixelColorNormalized(int x, int y) {
            GAPI_FUNCTION_LOG("readPixelColorNormalized", x, y);
            GAPI::RGBColorNormalized color{};
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_FLOAT, color.r, color.g, color.b, color.a);
            glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, &color);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glReadPixels", x, y, 1, 1, GL_RGB,
                                             GL_UNSIGNED_BYTE, color.r, color.g, color.b, color.a);
            return color;
        }
        
        
        // -------------------------------------------------------------------------
        // ------------------------------ Buffers ----------------------------------
        
        void genBuffers(GAPI::UInt amount, GAPI::UInt &bufferID) override {
            GAPI_FUNCTION_LOG("genBuffers", amount);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGenBuffers", amount, &bufferID);
            glGenBuffers(amount, &bufferID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glGenBuffers", amount, &bufferID);
        }
        
        void bindBuffer(GAPI::BufferTypes bufferType, GAPI::UInt buffer) override {
            GAPI_FUNCTION_LOG("bindBuffer", bufferType, buffer);
            auto bufferTypeGL = static_cast<GLenum>(bufferType);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", bufferTypeGL, buffer);
            glBindBuffer(bufferTypeGL, buffer);
        }
        
        void unbindBuffer(GAPI::BufferTypes bufferType) override {
            GAPI_FUNCTION_LOG("unbindBuffer", bufferType);
            auto bufferTypeGL = static_cast<GLenum>(bufferType);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", bufferTypeGL, 0);
            glBindBuffer(bufferTypeGL, 0);
        }
        
        void deleteBuffer(GAPI::UInt buffer) override {
            GAPI_FUNCTION_LOG("deleteBuffer", buffer);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteBuffers", 1, &buffer);
            glDeleteBuffers(1, &buffer);
        }
        
        void setBufferData(const GAPI::Float *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const GAPI::UInt *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const GAPI::Int *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const Vec2F *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const Vec3F *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const Vec4F *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const Mat2F *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const Mat3F *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        void setBufferData(const Mat4F *data, GAPI::Size count,
                           GAPI::BufferTypes bufferType,
                           GAPI::BufferUsages bufferUsage) override {
            setBufferDataGL(data, count, bufferType, bufferUsage);
        }
        
        template<typename T, typename std::enable_if<isGraphicsType_v<T>, T>::type * = nullptr>
        void setBufferDataGL(const T *data,
                             GAPI::Size count,
                             GAPI::BufferTypes bufferType,
                             GAPI::BufferUsages bufferUsage) {
            #ifndef NLOGGING
            std::vector<T> vectorData(data, data + count);
            #endif
            GAPI_FUNCTION_LOG("setBufferData", vectorData, count, bufferType, bufferUsage);
            
            auto size = count * sizeof(T);
            GLenum type = static_cast<GLenum>(bufferType);
            GLenum usage = static_cast<GLenum>(bufferUsage);
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBufferData", type, size, data, usage);
            glBufferData(type, size, data, usage);
        }
        
        std::vector<float> getBufferDataF(GLuint bufferId) override {
            GAPI_FUNCTION_LOG("getBufferDataF", bufferId);
            return getBufferData<float>(bufferId);
        }
        
        std::vector<unsigned int> getBufferDataUI(GLuint bufferId) override {
            GAPI_FUNCTION_LOG("getBufferDataUI", bufferId);
            return getBufferData<unsigned int>(bufferId);
        }
        
        std::vector<int> getBufferDataI(GLuint bufferId) override {
            GAPI_FUNCTION_LOG("getBufferDataI", bufferId);
            return getBufferData<int>(bufferId);
        }
        
        template<typename T>
        std::vector<T> getBufferData(GLuint bufferId) {
            GAPI_FUNCTION_LOG("getBufferData", bufferId);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", GL_ARRAY_BUFFER, bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, bufferId);
            
            GLint sizeBytes = 0;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetBufferParameteriv", GL_ARRAY_BUFFER,
                                             GL_BUFFER_SIZE, &sizeBytes);
            glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &sizeBytes);
            
            if (sizeBytes <= 0) {
                throw GAPIException("Invalid buffer size.");
            }
            auto numElements = sizeBytes / sizeof(T);
            std::vector<T> data(numElements);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetBufferSubData", GL_ARRAY_BUFFER, 0, sizeBytes,
                                             data.data());
            glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeBytes, data.data());
            GAPI_FUNCTION_IMPLEMENTATION_LOG("post glGetBufferSubData", data);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindBuffer", GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            
            return data;
        }
        
        void genVertexArray(GAPI::UInt &vertexArrayID) override {
            GAPI_FUNCTION_LOG("genVertexArray", vertexArrayID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGenVertexArrays", 1, &vertexArrayID);
            glGenVertexArrays(1, &vertexArrayID);
        };
        
        void bindVertexArray(GAPI::UInt vertexArrayID) override {
            GAPI_FUNCTION_LOG("bindVertexArray", vertexArrayID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindVertexArray", vertexArrayID);
            glBindVertexArray(vertexArrayID);
        }
        
        void unbindVertexArray() override {
            GAPI_FUNCTION_NO_ARGS_LOG("unbindVertexArray");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glBindVertexArray", 0);
            glBindVertexArray(0);
        }
        
        void deleteVertexArray(GAPI::UInt vertexArrayID) override {
            GAPI_FUNCTION_LOG("deleteVertexArray", vertexArrayID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteVertexArrays", 1, &vertexArrayID);
            glDeleteVertexArrays(1, &vertexArrayID);
        }
        
        void enableVertexData(GAPI::UInt index) override {
            GAPI_FUNCTION_LOG("enableVertexData", index);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glEnableVertexAttribArray", index);
            glEnableVertexAttribArray(index);
        }
        
        
        /**
         * @brief Configures the layout of the vertex data.
         *
         * This method sets up how OpenGL interprets the vertex buffer data.
         * It is used to specify the location and data format of the array of generic vertex
         * attributes.
         *
         * @param index The index of the vertex attribute to be modified.
         * @param count The number of components per generic vertex attribute.
         *              Typically, this is 1, 2, 3, or 4.
         * @param type The data type of each component in the array.
         *             For example, GL_FLOAT, GL_INT, etc.
         * @param isNormalized Specifies whether fixed-point data values should be normalized or
         *                     converted directly as fixed-point values when they are accessed.
         * @param stride The byte offset between consecutive vertex attributes.
         *               If the attributes are tightly packed, this value is 0.
         * @param offset The offset of the first component of the first vertex attribute in the
         *               buffer.
         *               This is usually a byte offset.
         */
        void createVertexData(GAPI::UInt index,
                              GAPI::UInt count,
                              GAPI::Types type,
                              GAPI::Bool isNormalized,
                              GAPI::UInt stride,
                              GAPI::UInt offset) override {
            GAPI_FUNCTION_LOG("createVertexData", index, count, type, isNormalized, stride,
                              offset);
            
            auto glType = static_cast<GLenum>(type);
            auto glNormalized = static_cast<GLboolean>(isNormalized);
            // Calls glVertexAttribPointer to define an array of generic vertex attribute data.
            // The parameters are set according to the function arguments, allowing for flexible
            // configuration of vertex data.
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glVertexAttribPointer", index, count,
                                             glType,
                                             glNormalized, stride,
                                             offset);
            
            glVertexAttribPointer(index,    // Specifies the index of the generic vertex attribute.
                                  count,     // Number of components per generic vertex attribute.
                                  glType, // Converts the GAPITypes enum to GLenum.
                                  glNormalized, // Specifies whether to normalize the data.
                                  stride,    // Byte offset between consecutive vertex attributes.
                                  (GLvoid *)
                                          (offset)); // Offset of the first component in the buffer.
        }
        
        
        // ---------------------------- Shader functions --------------------------------
        // ------------------------------------------------------------------------------
        
        
        GAPI::UInt
        loadAndCompileShader(GAPI::ShaderTypes shaderType,
                             const std::string &shaderSource) override {
            GAPI_FUNCTION_LOG("loadAndCompileShader", shaderType, shaderSource);
            auto shaderTypeGL = static_cast<GLenum>(shaderType);
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCreateShader", shaderTypeGL);
            GLuint vertexShader = glCreateShader(shaderTypeGL);
            const GAPI::Char *source = shaderSource.c_str();
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glShaderSource", vertexShader, 1, &source, nullptr);
            glShaderSource(vertexShader, 1, &source, nullptr);
            
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCompileShader", vertexShader);
            glCompileShader(vertexShader);
            
            return vertexShader;
        }
        
        
        GAPI::UInt
        createShaderProgram(GAPI::UInt vertexShaderID, GAPI::UInt fragmentShaderID) override {
            GAPI_FUNCTION_LOG("createShaderProgram", vertexShaderID, fragmentShaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glCreateProgram", 0);
            GLuint shaderProgram = glCreateProgram();
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glAttachShader", shaderProgram, vertexShaderID);
            glAttachShader(shaderProgram, vertexShaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glAttachShader", shaderProgram, fragmentShaderID);
            glAttachShader(shaderProgram, fragmentShaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glLinkProgram", shaderProgram);
            glLinkProgram(shaderProgram);
            
            return shaderProgram;
        }
        
        void destroyShaderProgram(GAPI::UInt shaderProgram) {
            GAPI_FUNCTION_LOG("destroyShaderProgram", shaderProgram);
            glDeleteProgram(shaderProgram);
        }
        
        [[nodiscard]] bool compilationOK(GAPI::UInt shaderID, GAPI::Char *message) override {
            GAPI_FUNCTION_LOG("compilationOK", shaderID, message);
            GLint success;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetShaderiv", shaderID, GL_COMPILE_STATUS,
                                             &success);
            glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
            if (!success) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetShaderInfoLog", shaderID, 512, nullptr,
                                                 message);
                glGetShaderInfoLog(shaderID, 512, nullptr, message);
                return false;
            }
            return true;
        }
        
        [[nodiscard]] bool linkOK(GAPI::UInt shaderProgram, GAPI::Char *message) override {
            GAPI_FUNCTION_LOG("linkOK", shaderProgram, message);
            GLint success;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetProgramiv", shaderProgram, GL_LINK_STATUS,
                                             &success);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glGetProgramInfoLog", shaderProgram, 512,
                                                 nullptr, message);
                glGetProgramInfoLog(shaderProgram, 512, nullptr, message);
                return false;
            }
            return true;
        }
        
        void useShaderProgram(GAPI::UInt shaderProgram) override {
            GAPI_FUNCTION_LOG("useShaderProgram", shaderProgram);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glUseProgram", shaderProgram);
            glUseProgram(shaderProgram);
        }
        
        bool isShaderProgram(GAPI::UInt shaderProgram) override {
            GAPI_FUNCTION_LOG("isShaderProgram", shaderProgram);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glIsProgram", shaderProgram);
            return glIsProgram(shaderProgram);
        }
        
        void deleteShader(GAPI::UInt shaderID) override {
            GAPI_FUNCTION_LOG("deleteShader", shaderID);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glDeleteShader", shaderID);
            glDeleteShader(shaderID);
        }
        // -------------------------------- Uniforms ------------------------------------
        
        std::unique_ptr<UniformSetter>
        setUniform(GAPI::UInt program, const std::string &uName) override {
            GAPI_FUNCTION_LOG("setUniform", program, uName);
            if (isShaderProgram(program) == GL_FALSE)
                throw GAPIException("Program " + std::to_string(program) +
                                    " is not a shader program.");
            return std::make_unique<UniformSetter>(GLUniformSetter(program, uName));
        }
        
        void clear(const std::initializer_list<GAPI::ClearBits> &values) override {
            GAPI_FUNCTION_LOG("clear", values);
            GLuint mask = 0;
            for (auto value : values) {
                GAPI_FUNCTION_IMPLEMENTATION_LOG("glClear", value);
                mask |= static_cast<GLenum>(value);
            }
            glClear(mask);
        }
        
        void clearColor(GAPI::Float r, GAPI::Float g, GAPI::Float b, GAPI::Float a) override {
            GAPI_FUNCTION_LOG("clearColor", r, g, b, a);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glClearColor", r, g, b, a);
            glClearColor(r, g, b, a);
        }
        
        
        void createContext(SDL_Window &window) override {
            GAPI_FUNCTION_NO_ARGS_LOG("createContext");
            // OpenGL context initialization over the SDL windowManager,
            // needed for using OpenGL functions
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_CreateContext", "SDL_Window");
            this->context = SDL_GL_CreateContext(&window);
            D_ASSERT_NOT_EQUAL(this->context, nullptr,
                               "Unable to create context: " + std::string(SDL_GetError()));
            GLESC::Logger::get().success("GL context created!");
        }
    
    
    private:
        
        void setSDLGLAttribute(SDL_GLattr attrib, int val) {
            GAPI_FUNCTION_LOG("setSDLGLAttribute", attrib, val);
            GAPI_FUNCTION_IMPLEMENTATION_LOG("SDL_GL_SetAttribute", attrib, val);
            if (SDL_GL_SetAttribute(attrib, val) == -1)
                throw GAPIException("Unable to set gl attribute: " + std::string(SDL_GetError()));
        }
        
        
        /**
         * @brief Must be called after creating the window and before
         * enabling gl functions like glEnable() or glCullFace()
         */
        static void initGLEW() {
            GAPI_FUNCTION_NO_ARGS_LOG("initGLEW");
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glewExperimental", GL_TRUE);
            glewExperimental = GL_TRUE;
            GAPI_FUNCTION_IMPLEMENTATION_LOG("glewInit", 0);
            GLuint err = glewInit();
            std::string
                    errStr = std::string(reinterpret_cast<const char *>(glewGetErrorString(err)));
            D_ASSERT_GLEW_OK((err == GLEW_OK), errStr);
        }
        
        
        SDL_GLContext context{};
        
    };
    
}

