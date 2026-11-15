#include "common.h"
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(void *);
extern void FadeToBlack(int), hero_reset_for_area_start(int), hero_reset_position_and_direction(void *, void *, int, int), PlayMobySound(int, int, void *);
extern void SetCamera5Pose(void *, void *, int, int, int), object_copy_vector_to_selected(void *), cam_set_state_rotation(void *);
extern void anim_start_blended(void *, int, int, int), set_hero_animation(int, int, float);

extern unsigned char D_001A7A45;
extern int D_L01_001B1FA8;
typedef struct {
    char pad[0x80];
    float pos[4];
    float rot[4];
    char pad2[0x2214];
    unsigned char state;
    char pad3[10];
    unsigned char flag;
} TransitionPlayerState;
extern TransitionPlayerState g_hero_state;
/* Starts the hero arriving from a teleporter: places the hero in front of the moby, sets the camera and a sound, and moves the moby to its next state. */
void teleporter_start_arrival(unsigned char *moby) {
    float arrivePos[4], arriveRot[4], camPos[4], camRot[4];
    char *vars = *(char **)(moby + 0x68);
    arrivePos[0] = math_fast_sin_or_cos_a(*(float *)(vars + 0x1C))*2.5f;
    arrivePos[1] = math_fast_sin_or_cos_b(*(float *)(vars + 0x1C))*2.5f;
    arrivePos[2] = 0;
    FastVecAdd(arrivePos, arrivePos, vars + 0x10);
    vec_clear_128(arriveRot);
    arriveRot[2] = FastAddRotations(*(float *)(vars + 0x1C), 3.1415929794311523f);
    FadeToBlack(10);
    if (g_hero_state.state == 3) hero_reset_for_area_start(0);
    hero_reset_position_and_direction(arrivePos, arriveRot, 0x6F, 0);
    PlayMobySound(0, 0, moby);
    camPos[0] = math_fast_sin_or_cos_a(*(float *)(vars + 0x1C))*1.25f;
    camPos[1] = math_fast_sin_or_cos_b(*(float *)(vars + 0x1C))*1.25f;
    camPos[2] = 0;
    camPos[0] += math_fast_sin_or_cos_a(FastAddRotations(*(float *)(vars + 0x1C), 1.5707964897155762f))*4.0f;
    camPos[1] += math_fast_sin_or_cos_b(FastAddRotations(*(float *)(vars + 0x1C), 1.5707964897155762f))*4.0f;
    FastVecAdd(camPos, camPos, vars + 0x10);
    camPos[2] += 1;
    vec_clear_128(camRot);
    camRot[2] = fast_subtract_rotations(*(float *)(vars + 0x1C), 1.5707964897155762f);
    SetCamera5Pose(camPos, camRot, 1, 0, 0);
    object_copy_vector_to_selected(camPos);
    cam_set_state_rotation(camRot);
    qcopy_nc(moby + 0x10, g_hero_state.pos);
    qcopy_nc(moby + 0xF0, g_hero_state.rot);
    if (moby[0x43] != 1) anim_start_blended(moby, 1, 0, 0);
    set_hero_animation(0x7B, 0, 0.0f);
    if (D_001A7A45) *(unsigned short *)(moby + 0x34) |= 0x8000;
    g_hero_state.flag = 1;
    D_L01_001B1FA8 = 1;
    moby[0x20] = 2;
    *(int *)(vars + 0x6C) = 60;
}
