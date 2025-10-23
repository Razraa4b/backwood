#include <glad/glad.h>
#include <vector>
#include "ShaderProgram.hpp"
#include "Shader.hpp"

namespace bw::low_level
{
    ShaderProgram::ShaderProgram() : _handle(NullShaderProgram)
    {
        _handle = glCreateProgram();
    }
    
    ////////////////////////////////////////////////////////////

    ShaderProgram::ShaderProgram(const ShaderProgram& other) : ShaderProgram()
    {
        int shaderCount;
        glGetProgramiv(other._handle, GL_ATTACHED_SHADERS, &shaderCount);

        std::vector<unsigned int> shaders(shaderCount);
        int count;
        glGetAttachedShaders(other._handle, shaderCount, &count, shaders.data());

        // Attach each shader from a different program
        for(auto shader : shaders)
        {
            glAttachShader(_handle, shader);
        }
    }
    
    ////////////////////////////////////////////////////////////

    ShaderProgram::ShaderProgram(ShaderProgram&& moved) : _handle(NullShaderProgram)
    {
        _handle = moved._handle;
        moved._handle = NullShaderProgram;
    }
    
    ////////////////////////////////////////////////////////////

    ShaderProgram::~ShaderProgram()
    {
        release();
    }
    
    ////////////////////////////////////////////////////////////

    ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other)
    {

        // Detach current shaders
        int shaderCount;
        glGetProgramiv(_handle, GL_ATTACHED_SHADERS, &shaderCount);
        
        std::vector<unsigned int> shaders(shaderCount);
        int count;
        glGetAttachedShaders(other._handle, shaderCount, &count, shaders.data());
        
        // Detach each shader from current program
        for(auto shader : shaders)
        {
            glDetachShader(_handle, shader);
        }

        // Attach shaders from other program
        glGetProgramiv(other._handle, GL_ATTACHED_SHADERS, &shaderCount);

        glGetAttachedShaders(other._handle, shaderCount, &count, shaders.data());

        // Attach each shader from other program
        for(auto shader : shaders)
        {
            glAttachShader(_handle, shader);
        }
        
        return *this;
    }
    
    ////////////////////////////////////////////////////////////

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& moved)
    {
        release();

        _handle = moved._handle;
        moved._handle = NullShaderProgram;

        return *this;
    }
    
    ////////////////////////////////////////////////////////////

    void ShaderProgram::attach(Shader& shader)
    {
        glAttachShader(_handle, shader._handle);
    }

    ////////////////////////////////////////////////////////////

    void ShaderProgram::detach(Shader& shader)
    {
        glAttachShader(_handle, shader._handle);
    }

    ////////////////////////////////////////////////////////////

    void ShaderProgram::link()
    {
        glLinkProgram(_handle);
    }
       
    ////////////////////////////////////////////////////////////

    void ShaderProgram::use() const
    {
        glUseProgram(_handle);
    }

    ////////////////////////////////////////////////////////////

    void ShaderProgram::release()
    {
        if(_handle != NullShaderProgram)
        {
            glDeleteProgram(_handle);
            _handle = NullShaderProgram;
        }
    }
}
