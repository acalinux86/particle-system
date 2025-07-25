#include "./system.h"

GLuint compile_vertex(char *vertex_code)
{
    GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    if (vertex_code == NULL)
    {
        Logf(stderr, ERROR, "Vertex Shader Source is NULL");
        return 0;
    }

    Log(INFO, "Compiling Vertex Shader Program...\n");
    glShaderSource(VertexShaderId, 1, (const GLchar* const*)&vertex_code, NULL);
    glCompileShader(VertexShaderId);
    
    // Check Vertex Shader
    if (!log_shader_error(VertexShaderId))
    {
        glDeleteShader(VertexShaderId);
        return 0;
    }
    Log(INFO, "SuccessFully Compiled Vertex Shader.\n");
    return VertexShaderId;
}

GLuint compile_fragment(char *fragment_code)
{
    GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragment_code == NULL)
    {
        Logf(stderr, ERROR, "Fragment Shader Source is NULL.\n");
        return 0;
    }

    Log(INFO, "Compiling Fragment Shader Program...\n");
    glShaderSource(FragmentShaderId, 1, (const GLchar* const*)&fragment_code, NULL);
    glCompileShader(FragmentShaderId);

    // Check fragment Shader
    if (!log_shader_error(FragmentShaderId))
    {
        glDeleteShader(FragmentShaderId);
        return 0;
    }
    Log(INFO, "SuccessFully Compiled Fragment Shader.\n");
    return FragmentShaderId;
}

GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path)
{
    uint8_t v_len, f_len = 0;
    char *vertex_code = read_file(vertex_file_path, &v_len);
    char *fragment_code = read_file(fragment_file_path, &f_len);

    // Debug print the shader sources
    Log(INFO, "Vertex shader source (%u bytes)\n", v_len);
    Log(INFO, "Fragment shader source (%u bytes)\n", f_len);
    
    GLuint FragmentShaderId = compile_fragment(fragment_code);
    GLuint VertexShaderId = compile_vertex(vertex_code);

    if (FragmentShaderId == 0 || VertexShaderId == 0)
    {
        if (VertexShaderId) glDeleteShader(VertexShaderId);
        if (FragmentShaderId) glDeleteShader(FragmentShaderId);
        free(vertex_code);
        free(fragment_code);
        return 0;
    }

    // Link the Program
    Log(INFO, "Linking Programs...\n");
    GLuint ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);

    // Check the Program
    if (!log_program_error(ProgramId))
    {
        Logf(stderr, ERROR, "Program Linking Failed.\n");
        glDeleteProgram(ProgramId);
        ProgramId = 0;
        return 0;
    }
    Log(INFO, "SuccessFully Linked Program.\n");

    Log(INFO, "Detaching and Deleting Shaders...\n");
    // Detach Shaders
    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);

    // Delete Shader Id
    glDeleteShader(VertexShaderId);
    glDeleteShader(FragmentShaderId);
    
    Log(INFO, "SuccessFully Detached and Deleted the Shaders.\n");
    // Free the shader buffers
    free(vertex_code);
    free(fragment_code);
    Log(INFO, "SuccessFully Freed the Shader Buffers\n");
    return ProgramId; // return program id
}

