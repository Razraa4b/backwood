#include <vector>
#include <glad/glad.h>
#include "Shader.hpp"

namespace bw::low_level
{
    Shader::Shader(Type type, std::string source)
    {
        _create(type, source);
    }
    
	////////////////////////////////////////////////////////////

    Shader::Shader(const Shader& other) : Shader(other.getType(), other.getSource())
    {
    }

	////////////////////////////////////////////////////////////

    Shader::Shader(Shader&& moved)
    {
        this->_handle = moved._handle;
        moved._handle = NullShader;
    }
    
	////////////////////////////////////////////////////////////

    Shader::~Shader()
    {
        release();
    }

	////////////////////////////////////////////////////////////

    Shader& Shader::operator=(const Shader& other)
    {
        if(this != &other)
        {
            release();
            _create(other.getType(), other.getSource());
        }

        return *this;
    }

	////////////////////////////////////////////////////////////

    Shader& Shader::operator=(Shader&& moved)
    {
        if(this != &moved)
        {
            release();
            
            this->_handle = moved._handle;
            moved._handle = NullShader;
        }

        return *this;
    }
    
	////////////////////////////////////////////////////////////

    bool Shader::compile()
    {
        glCompileShader(_handle);
        return isCompiled();
    }

	////////////////////////////////////////////////////////////

    bool Shader::isCompiled() const
    {
        int status;

        glGetShaderiv(_handle, GL_COMPILE_STATUS, &status);

        if(status == GL_TRUE) return true;
        return false;
    }
    
	////////////////////////////////////////////////////////////

    std::string Shader::getSource() const
    {
        int sourceLength = 0;
        glGetShaderiv(_handle, GL_SHADER_SOURCE_LENGTH, &sourceLength);
    
        if (sourceLength <= 0) {
            return "";
        }
    
        std::vector<char> source(sourceLength);
        int actualLength = 0;
    
        glGetShaderSource(_handle, sourceLength, &actualLength, source.data());
    
        if (actualLength > 0) {
            return std::string(source.data(), actualLength);
        }
    
        return "";
    }
    
	////////////////////////////////////////////////////////////

    Shader::Type Shader::getType() const
    {
        GLint type;
        glGetShaderiv(_handle, GL_SHADER_TYPE, &type);

        switch(type) 
        {
            case GL_VERTEX_SHADER:   return Type::Vertex;
            case GL_FRAGMENT_SHADER: return Type::Fragment;
            default:                 return Type::Geometric;
        }
    }
    
	////////////////////////////////////////////////////////////

    void Shader::release()
    {
        if(_handle != NullShader)
        {
            glDeleteShader(_handle);
            _handle = NullShader;
        }
    }
    
	////////////////////////////////////////////////////////////

    void Shader::_create(Type type, std::string source)
    {
        GLenum shaderType;

        switch(type)
        {
            case Type::Vertex:   shaderType = GL_VERTEX_SHADER; break;
            case Type::Fragment: shaderType = GL_FRAGMENT_SHADER; break;
            default:             shaderType = GL_GEOMETRY_SHADER; break;
        }

        _handle = glCreateShader(shaderType);

        const char* sourcePtr = source.c_str();
        glShaderSource(_handle, 1, &sourcePtr, NULL);
    }
}
