#include "common.h"

/* func_002ECB70 draws the 38 environment-mapped quads of a 43-vertex mesh, as RAC1's
   render_environment_mapped_object (src/game/space.c) does with per-class tables. */
extern float D_002625B0[][4], D_002620A0[][4], D_00214A30[][4];
extern float D_00214CE0[][2], D_00214E38[][2];
extern short D_00262350[][8];
extern int D_001A8BB0;
extern float D_001B5200[];
extern int D_001ABF00 __attribute__((sda));
extern int D_001ABF04 __attribute__((sda));
extern int D_001ABF08 __attribute__((sda));
extern short D_00152C20 NOT_SDA;
extern unsigned long long func_0027C878(int);
extern void func_0029FC20(void *, int, void *);
extern float func_00282C48(float);
extern void func_00282948(int *);
extern float func_00283CE0(int);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282C10(float);
extern void func_00280B90(void *, int, int);
/* Draws a shiny reflection mesh on an object, with textures that follow the camera. */
void func_002ECB70(void *object)
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
 float (*points)[4] = D_002620A0;
 float (*normals)[4] = D_002625B0;
 short (*quads)[8] = D_00262350;
 quad.packet[1] = GetEffectTextureDescriptor(21);
 quad.packet[0] = 0;
 color = gCurrentGameMode == 2 ? 0x28a5a281 : 0x3ca5a281;
 active = 0;
 quad.packet[2] = 0xff9000000260ULL;
 quad.packet[3] = 0x8000000044ULL;
 quad.color[0] = quad.color[1] = quad.color[2] = quad.color[3] = color;
 TransformMobyJointPoint(object, 0, matrix);
 transform = matrix;
 if (gCurrentGameMode == 0 || gCurrentGameMode == 2) {
  if (FloatAbs(gActiveCamera[0x50] - *(float *)(o + 0x10)) < 16.0f &&
      FloatAbs(gActiveCamera[0x51] - *(float *)(o + 0x14)) < 16.0f) active = 1;
 } else active = 1;
 if (gCurrentGameMode == 6 && D_00152C20 == 2) active = 0;
 if (active || D_001ABF00 == 1) {
  D_001ABF04 = 1;
  FastFloatHelperD(&D_001ABF08);
  fraction = IntToFloat(D_001ABF08) / IntToFloat(60);
  {
  float *t = transform;
  float (*n)[4] = normals;
  float (*p)[4] = points;
  for (i = 0; i < 43; i++) {
   float divisor, x;
   transform_vector(D_00214A30[i], p[i], t);
   FastVecSub(ray, D_00214A30[i], &gActiveCamera[0x50]);
   vec_scale_to_length(ray, ray, 1.0f);
   transform_vector(normal, n[i], t);
   vec_scale_to_length(normal, normal, 0.1f);
   FastVecScale(reflected, normal, 2.0f * FastVecDot(normal, ray));
   FastVecSub(reflected, ray, reflected);
   vec_scale_to_length(reflected, reflected, 1.0f);
   reflected[2] += 1.0f;
   divisor = square_root(reflected[2] * 2.0f) * 2.0f;
   if (D_001ABF00 == 1 || D_001ABF08 == 0) {
    D_00214CE0[i][0] = reflected[0] / divisor + 0.5f;
    D_00214CE0[i][1] = reflected[1] / divisor + 0.5f;
   } else {
    x = reflected[0] / divisor + 0.5f;
    D_00214CE0[i][0] = x + (D_00214E38[i][0] - x) * fraction;
    x = reflected[1] / divisor + 0.5f;
    D_00214CE0[i][1] = x + (D_00214E38[i][1] - x) * fraction;
   }
  }
  }
  if (D_001ABF00 == 1) D_001ABF00 = 2;
 } else if (D_001ABF04 == 1) {
  D_001ABF04 = 0;
  for (i = 0; i < 43; i++) {
   D_00214E38[i][0] = D_00214CE0[i][0];
   D_00214E38[i][1] = D_00214CE0[i][1];
   transform_vector(D_00214A30[i], points[i], transform);
  }
  D_001ABF08 = 60;
 } else {
  float (*dest)[4] = D_00214A30;
  float (*p)[4] = points;
  for (i = 0; i < 43; i++) transform_vector(dest[i], p[i], transform);
  D_001ABF08 = 60;
 }
 for (i = 0; i < 38; i = next) {
  float *quad_u = &quad.uv[0][0];
  float *quad_v = &quad.uv[0][1];
  next = i + 1;
  for (j = 0; j < 4; j++) {
   int index = quads[i][j * 2];
   qcopy_nc(quad.vertex[j], D_00214A30[index]);
   {
    float x = D_00214CE0[index][0];
    float y = D_00214CE0[index][1];
    quad_u[j*2] = x;
    quad_v[j*2] = y;
   }
  }
  draw_world_quad(&quad, 0, 0);
 }
}
