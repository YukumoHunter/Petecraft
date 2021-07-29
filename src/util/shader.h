#ifndef SHADER_H
#define SHADER_H

#include <stdbool.h>
#include <cglm/cglm.h>

typedef struct Shader {
    unsigned int ID;
    const char *vs_source;
    const char *fs_source;
} Shader;

char *file_path_to_str(const char *string);
void init_shader(Shader *shader, const char *vs_path, const char *fs_path);
void use_shader(Shader *shader);
void set_bool(Shader *shader, char *name, bool value);
void set_int(Shader *shader, char *name, int value);
void set_float(Shader *shader, char *name, float value);
void set_mat4(Shader *shader, char *name, mat4 value);

#endif
