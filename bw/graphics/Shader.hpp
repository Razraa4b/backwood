#pragma once

#include <string>

namespace bw::low_level
{
    ///
    /// @class Shader
    /// @brief Class that wraps the functionality of shaders in the OpenGL API
    /// 
    class Shader
    {
    public:
        ///
        /// @enum Type
        /// @brief Shader type
        ///
        enum Type
        {
            Vertex,
            Fragment,
            Geometric
        };

        /// @brief Constant for a non-existent shader
        static const unsigned int NullShader = 0;

        /// @brief Creates and initializes the shader and also includes the source code
        /// @param type 
        /// @param source 
        Shader(Type type, std::string source);
        
        Shader(const Shader& other);
        Shader(Shader&& moved);

        ~Shader();
        
        Shader& operator=(const Shader& other);
        Shader& operator=(Shader&& moved);

        /// @brief Compile the shader source code
        /// @return True if success else false
        bool compile();

        /// @brief Gets shader compile status
        /// @return True if compiled else false
        bool isCompiled() const;
        
        /// @brief Gets shader source code
        /// @return Source code
        std::string getSource() const;

        /// @brief Gets shader type
        /// @return Shader type
        Type getType() const;
        
        /// @brief Releases shader and his data
        void release();
    private:
        unsigned int _handle;

        void _create(Type type, std::string source);
    };
}
