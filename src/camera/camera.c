#include <math.h>
#include <glad/glad.h>
#include "camera.h"

Camera new_camera(vec3 position, vec3 world_up, float yaw, float pitch, float speed, float sensitivity, float zoom)
{
    vec3 front, up, right;
    glm_vec3_zero(front);
    glm_vec3_zero(up);
    glm_vec3_zero(right);

    Camera camera = {
        position,
        malloc(sizeof(vec3)),
        malloc(sizeof(vec3)),
        malloc(sizeof(vec3)),
        world_up,

        yaw,
        pitch,

        speed,
        sensitivity,
        zoom
    };
    // camera.position = position;
    camera.world_up = world_up;

    update_camera_vectors(&camera);

    return camera;
}

// finds new camera direction
void update_camera_vectors(Camera *camera)
{
    vec3 front;
    glm_vec3_zero(front);
    // calculate new front vector
    front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    front[1] = sin(glm_rad(camera->pitch));
    front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));

    glm_vec3_normalize_to(front, camera->front);   

    vec3 right;
    glm_vec3_zero(right);
    glm_vec3_cross(camera->front, camera->world_up, right);
    glm_vec3_normalize_to(right, camera->right);

    vec3 up;
    glm_vec3_zero(up);
    glm_cross(right, front, up);
    glm_normalize_to(up, camera->up);
}

// copy lookat matrix into matrix variable
void get_view_matrix(Camera *camera, mat4 matrix)
{
    vec3 center;

    glm_vec3_add(camera->position, camera->front, center);

    glm_lookat(camera->position, center, camera->up, matrix);
}

void process_keyboard(Camera *camera, CameraMovement direction, float delta)
{
    float velocity = camera->movement_speed * delta;
    vec3 displacement;

    if (direction == FORWARD)
    {
        glm_vec3_scale(camera->front, velocity, displacement);
        glm_vec3_add(camera->position, displacement, camera->position);
    }

    if (direction == BACKWARD)
    {
        glm_vec3_scale(camera->front, velocity, displacement);
        glm_vec3_sub(camera->position, displacement, camera->position);
    }

    if (direction == LEFT)
    {
        glm_vec3_scale(camera->right, velocity, displacement);
        glm_vec3_sub(camera->position, displacement, camera->position);
    }


    if (direction == RIGHT)
    {
        glm_vec3_scale(camera->right, velocity, displacement);
        glm_vec3_add(camera->position, displacement, camera->position);
    }
}

void process_mouse_movement(Camera *camera, float x_offset, float y_offset)
{
    x_offset *= camera->mouse_sensitivity;
    y_offset *= camera->mouse_sensitivity;

    camera->yaw += x_offset;
    camera->pitch += y_offset;

    // constrain pitch
    if (camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    if (camera->pitch < -89.0f)
        camera->pitch = -89.0f;

    update_camera_vectors(camera);
}

void process_mouse_scroll(Camera *camera, float y_offset)
{
    camera->zoom -= (float) y_offset;

    // zoom boundaries
    if (camera->zoom < 1.0f)
        camera->zoom = 1.0f;
    if (camera->zoom > 45.0f)
        camera->zoom = 45.0f; 
}

void destroy_camera(Camera *camera)
{
    free(camera->front);
    free(camera->up);
    free(camera->right);
}