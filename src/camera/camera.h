#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

// Camera defaults
#define CAM_DEFAULT_YAW -90.0f
#define CAM_DEFAULT_PITCH 0.0f

#define CAM_DEFAULT_SPEED 10.0f
#define CAM_DEFAULT_SENSITIVITY 0.1f
#define CAM_DEFAULT_ZOOM 45.0f

typedef struct Camera {
    // camera attributes
    float *position;
    float *front;
    float *up;
    float *right;
    float *world_up;

    // Euler angles (no roll)
    float yaw;
    float pitch;

    // camera options
    float movement_speed;
    float mouse_sensitivity;
    float zoom;   
} Camera;

typedef enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} CameraMovement;

Camera new_camera(vec3 position, vec3 world_up, float yaw, float pitch, float speed, float sensitivity, float zoom);
void update_camera_vectors(Camera *camera);
void get_view_matrix(Camera *camera, mat4 matrix);
void process_keyboard(Camera *camera, CameraMovement direction, float delta);
void process_mouse_movement(Camera *camera, float x_offset, float y_offset);
void process_mouse_scroll(Camera *camera, float y_offset);
void destroy_camera(Camera *camera);

#endif