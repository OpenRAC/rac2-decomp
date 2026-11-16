#include "common.h"

/* func_002ECB70 draws the 38 environment-mapped quads of a 43-vertex mesh, as RAC1's
   render_environment_mapped_object (src/game/space.c) does with per-class tables. */
extern float g_env_object_normals[][4], g_env_object_points[][4], g_env_map_points[][4];
extern float g_env_map_uvs[][2], g_env_map_uvs_backup[][2];
extern short g_env_object_quads[][8];
extern int g_current_game_mode;
extern float g_active_camera[];
extern int g_env_map_state __attribute__((sda));
extern int g_env_map_active __attribute__((sda));
extern int g_env_map_fade_timer __attribute__((sda));
extern short g_transition_mode NOT_SDA;
extern unsigned long long GetEffectTextureDescriptor(int);
extern void moby_transform_joint_point(void *, int, void *);
extern float math_fabs(float);
extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern void transform_vector(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float square_root(float);
extern void draw_world_quad(void *, int, int);
/* Draws a shiny reflection mesh on an object, with textures that follow the camera. */
void render_environment_mapped_object(void *object)
{
 struct {
  float vertex[4][4];
  unsigned int color[4];
  float uv[4][2];
  unsigned long long packet[4];
 } quad;
 float matrix[16], normal[4], reflected[4], ray[4];
 float *transform;
 int active;
 unsigned int color;
 float fraction;
 int i, j, next;
 char *o = object;
 float (*points)[4] = g_env_object_points;
 float (*normals)[4] = g_env_object_normals;
 short (*quads)[8] = g_env_object_quads;
 quad.packet[1] = GetEffectTextureDescriptor(21);
 quad.packet[0] = 0;
 color = g_current_game_mode == 2 ? 0x28a5a281 : 0x3ca5a281;
 active = 0;
 quad.packet[2] = 0xff9000000260ULL;
 quad.packet[3] = 0x8000000044ULL;
 quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = color;
 moby_transform_joint_point(object, 0, matrix);
 transform = matrix;
 if (g_current_game_mode == 0 || g_current_game_mode == 2) {
  if (math_fabs(g_active_camera[0x50] - *(float *)(o + 0x10)) < 16.0f &&
      math_fabs(g_active_camera[0x51] - *(float *)(o + 0x14)) < 16.0f) active = 1;
 } else active = 1;
 if (g_current_game_mode == 6 && g_transition_mode == 2) active = 0;
 if (active || g_env_map_state == 1) {
  g_env_map_active = 1;
  math_fast_float_d(&g_env_map_fade_timer);
  fraction = IntToFloat(g_env_map_fade_timer) / IntToFloat(60);
  {
  float *t = transform;
  float (*n)[4] = normals;
  float (*p)[4] = points;
  for (i = 0; i < 43; i++) {
   float divisor, x;
   transform_vector(g_env_map_points[i], p[i], t);
   FastVecSub(ray, g_env_map_points[i], &g_active_camera[0x50]);
   vec_scale_to_length(ray, ray, 1.0f);
   transform_vector(normal, n[i], t);
   vec_scale_to_length(normal, normal, 0.1f);
   FastVecScale(reflected, normal, 2.0f * FastVecDot(normal, ray));
   FastVecSub(reflected, ray, reflected);
   vec_scale_to_length(reflected, reflected, 1.0f);
   reflected[2] += 1.0f;
   divisor = square_root(reflected[2] * 2.0f) * 2.0f;
   if (g_env_map_state == 1 || g_env_map_fade_timer == 0) {
    g_env_map_uvs[i][0] = reflected[0] / divisor + 0.5f;
    g_env_map_uvs[i][1] = reflected[1] / divisor + 0.5f;
   } else {
    x = reflected[0] / divisor + 0.5f;
    g_env_map_uvs[i][0] = x + (g_env_map_uvs_backup[i][0] - x) * fraction;
    x = reflected[1] / divisor + 0.5f;
    g_env_map_uvs[i][1] = x + (g_env_map_uvs_backup[i][1] - x) * fraction;
   }
  }
  }
  if (g_env_map_state == 1) g_env_map_state = 2;
 } else if (g_env_map_active == 1) {
  g_env_map_active = 0;
  for (i = 0; i < 43; i++) {
   g_env_map_uvs_backup[i][0] = g_env_map_uvs[i][0];
   g_env_map_uvs_backup[i][1] = g_env_map_uvs[i][1];
   transform_vector(g_env_map_points[i], points[i], transform);
  }
  g_env_map_fade_timer = 60;
 } else {
  float (*dest)[4] = g_env_map_points;
  float (*p)[4] = points;
  for (i = 0; i < 43; i++) transform_vector(dest[i], p[i], transform);
  g_env_map_fade_timer = 60;
 }
 for (i = 0; i < 38; i = next) {
  float *quad_u = &quad.uv[0][0];
  float *quad_v = &quad.uv[0][1];
  next = i + 1;
  for (j = 0; j < 4; j++) {
   int index = quads[i][j * 2];
   qcopy_nc(quad.vertex[j], g_env_map_points[index]);
   {
    float x = g_env_map_uvs[index][0];
    float y = g_env_map_uvs[index][1];
    quad_u[j*2] = x;
    quad_v[j*2] = y;
   }
  }
  draw_world_quad(&quad, 0, 0);
 }
}
