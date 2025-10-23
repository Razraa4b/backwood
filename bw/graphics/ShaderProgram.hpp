#pragma once

#include "Shader.hpp"
#include "IReleasable.hpp"

namespace bw::low_level
{
    ///
    /// @class ShaderProgram
    /// @brief Class that wraps the functionality of programs in the OpenGL API
    /// @implements IReleasable
    ///
    class ShaderProgram : public IReleasable
    {
    public:
        /// @brief Constant for a non-existent shader program
        static const unsigned int NullShaderProgram = 0;

        /// @brief Creates empty shader program
        ShaderProgram();
        
        ShaderProgram(const ShaderProgram& other);
        ShaderProgram(ShaderProgram&& moved);

        ~ShaderProgram();

        ShaderProgram& operator=(const ShaderProgram& other);
        ShaderProgram& operator=(ShaderProgram&& moved);

        /// @brief Attach shader to program
        /// @param shader Shader to attach
        void attach(Shader& shader);
        
        /// @brief Detach shader from program
        /// @param shader Shader to detach
        void detach(Shader& shader);

        /// @brief Links shader program
        void link();

        /// @brief Uses shader program
        void use() const;

        /// @brief Releases shader program and automatically detaches all shaders
        void release() override;
    private:
        unsigned int _handle;
    };
}
