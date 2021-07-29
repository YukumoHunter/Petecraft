#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "shader.h"

void init_shader(Shader *shader, const char *vs_path, const char *fs_path)
{
    const char *vs_source = file_path_to_str(vs_path);
    const char *fs_source = file_path_to_str(fs_path);

    unsigned int vertex_shader, fragment_shader;

    // CREATE VERTEX SHADER:
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // bind vertex shader to source code and compile shader
    glShaderSource(vertex_shader, 1, &vs_source, NULL);
    glCompileShader(vertex_shader);

    // check for shader compile errors
    int success;
    char infoLog[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        printf("Failed to compile vertex shader: %s\n", infoLog);
    }

    // CREATE FRAGMENT SHADER:
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    // bind fragment shader to source code and compile shader
    glShaderSource(fragment_shader, 1, &fs_source, NULL);
    glCompileShader(fragment_shader);

    // check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("Failed to compile fragment shader: %s\n", infoLog);
    }

    // create shader program and link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);

    // check for shader linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Failed to link shader program: %s\n", infoLog);
    }

    // delete shaders after use
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    shader->ID = shaderProgram;
    shader->vs_source = vs_source;
    shader->fs_source = fs_source;
}

void use_shader(Shader *shader)
{
    glUseProgram(shader->ID);
}

void set_bool(Shader *shader, char *name, bool value)
{         
    glUniform1i(glGetUniformLocation(shader->ID, name), (int)value); 
}

void set_int(Shader *shader, char *name, int value)
{ 
    glUniform1i(glGetUniformLocation(shader->ID, name), value); 
}

void set_float(Shader *shader, char *name, float value)
{ 
    glUniform1f(glGetUniformLocation(shader->ID, name), value); 
}

void set_mat4(Shader *shader, char *name, mat4 value)
{ 
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, &value[0][0]); 
}

// TODO: should add some error handling here probably but dont care rn
char *file_path_to_str(const char *string)
{
    FILE *file = fopen(string, "r");
    char *str;
    // get filesize
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    // allocate space
    str = (char*)calloc(1, size);
    // go back to beginning
    rewind(file);
    // read file into block
    fread(str, size, sizeof(char), file);

    fclose(file);
    return str;
}