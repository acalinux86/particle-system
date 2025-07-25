#include "./system.h"

bool log_shader_error(GLuint Id)
{
    GLint result = GL_FALSE;
    int info_log_length;

    // Check the Programs
    glGetShaderiv(Id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length > 0)
    {
        char ErrorMessage[info_log_length];
        glGetShaderInfoLog(Id, info_log_length, NULL, ErrorMessage);
        Log(ERROR, "%s\n", &ErrorMessage[0]);
    }
    return result == GL_TRUE;
}

bool log_program_error(GLuint Id)
{
    GLint result = GL_FALSE;
    int info_log_length;

    // Check the Programs
    glGetProgramiv(Id, GL_LINK_STATUS, &result);
    glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &info_log_length);
    
    if (info_log_length > 0)
    {
        char ErrorMessage[info_log_length + 1];
        glGetProgramInfoLog(Id, info_log_length, NULL, ErrorMessage);
        Log(ERROR, "%s\n", &ErrorMessage[0]);
    }
    return result == GL_TRUE;
}
