
#include "OpenGLUtils.h"

namespace CppUtils {

    namespace OpenGLUtils {
        static void CheckShaderForErrors(GLuint shaderId, GLenum statusName) {
            int infoLogLength = 0;
            GLint result = GL_FALSE;
            glGetShaderiv(shaderId, statusName, &result);
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0) {
                std::string error(infoLogLength, '\0');
                glGetShaderInfoLog(shaderId, infoLogLength, NULL, const_cast<GLchar *>(error.data()));
                throw std::runtime_error("Compiling vertex shader failed: " + error);
            }
        }
        
        static void CompileShader(GLuint shaderId, const char* source) {
            glShaderSource(shaderId, 1, &source, NULL);
            glCompileShader(shaderId);
            CheckShaderForErrors(shaderId, GL_COMPILE_STATUS);
        }

        GLuint LoadShaders(const char* vertexShader, const char* fragmentShader) {
            // Create the shaders
            GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

            // Compile Vertex Shader
            CompileShader(vertexShaderId, vertexShader);

            // Compile Fragment Shader
            CompileShader(fragmentShaderId, fragmentShader);

            // Link the program
            GLuint programId = glCreateProgram();
            glAttachShader(programId, vertexShaderId);
            glAttachShader(programId, fragmentShaderId);
            glLinkProgram(programId);

            // Check the program
            int infoLogLength = 0;
            GLint result = GL_FALSE;
            glGetProgramiv(programId, GL_LINK_STATUS, &result);
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
            if (infoLogLength > 0) {
                std::string error(infoLogLength, '\0');
                glGetProgramInfoLog(programId, infoLogLength, NULL, const_cast<GLchar *>(error.data()));
                throw std::runtime_error("Linking program failed failed: " + error);
            }

            glDetachShader(programId, vertexShaderId);
            glDetachShader(programId, fragmentShaderId);

            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);

            return programId;
        }
    }
}