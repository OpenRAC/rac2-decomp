#include "names.h"
/* func_PAL_L00_004276D8, the PAL copy of func_L00_00422268: the same C, where D_L00_001B1514
   is read as a word and takes the 50 Hz scale, and the aim values are read and stored in the
   order +0x44, +0x3C, +0x40. */

/* The parts of an object state (object +0x70) that func_PAL_L00_004276D8 resets. */
typedef struct {
    short h0, h2;                 /* 0x00 */
    char pad4[0x1C - 0x4];
    float f1C, f20;               /* 0x1C */
    char pad24[0x28 - 0x24];
    float f28, f2C, f30;          /* 0x28 */
    float f34, f38;               /* 0x34 */
} Recoil;

typedef struct {
    char pad0[0xB0];
    float fB0, fB4, fB8;          /* 0xB0 */
    float vBC[4];                 /* 0xBC */
    char padCC[0xD6 - 0xCC];
    unsigned char bD6;            /* 0xD6 */
    char padD7[0xDA - 0xD7];
    short hDA;                    /* 0xDA */
    float fDC, fE0, fE4, fE8;     /* 0xDC */
    unsigned short hEC;           /* 0xEC */
} View;

typedef struct {
    char pad0[0x2C];
    float f2C, f30;               /* 0x2C */
    char pad34[0x3C - 0x34];
    short h3C, h3E;               /* 0x3C */
    float f40;                    /* 0x40 */
    float v44[1];                 /* 0x44 */
    float f48, f4C;               /* 0x48 */
    float v50[1];                 /* 0x50 */
    float f54, f58;               /* 0x54 */
} Motion;

typedef struct {
    char pad0[0x10];
    int f10;                      /* 0x10 */
    float f14;                    /* 0x14 */
    char pad18[4];
    float f1C;                    /* 0x1C */
    int f20, f24;                 /* 0x20 */
} Temp;

typedef struct {
    char pad0[0x3C];
    float f3C, f40, f44;          /* 0x3C */
    int f48;                      /* 0x48 */
    char pad4C[2];
    short h4E;                    /* 0x4E */
} Aim;

typedef struct {
    char pad0[6];
    short h6;                     /* 0x06 */
    char pad8[4];
    float fC;                     /* 0x0C */
} Sway;

typedef struct {
    char pad0[0x10];
    short h10;                    /* 0x10 */
    char pad12[0x20 - 0x12];
    Recoil recoil;                /* 0x20 */
    char pad5C[0x60 - 0x5C];
    View view;                    /* 0x60 */
    char pad150[0x160 - 0x150];
    Motion motion;                /* 0x160 */
    char pad1BC[0x1C0 - 0x1BC];
    Temp temp;                    /* 0x1C0 */
    char pad1E8[0x1F0 - 0x1E8];
    Aim aim;                      /* 0x1F0 */
    char pad240[0x240 - 0x240];
    Sway sway;                    /* 0x240 */
} State;

/* The object: only its state pointer is used here. */
typedef struct {
    char pad0[0x70];
    State *state;                 /* 0x70 */
} StateOwner;

extern float g_cam_rotation_param;
extern State *g_weapon_view_state __attribute__((nosda));
extern float g_weapon_view_reset_param_a __attribute__((sda)), g_weapon_view_reset_param_b __attribute__((sda));
extern float g_camera_default_view_x __attribute__((sda)), g_camera_default_view_y __attribute__((sda));
extern int g_camera_default_angle_short __attribute__((sda));
extern float g_camera_default_aim_c __attribute__((sda)), g_camera_default_aim_a __attribute__((sda));
extern float g_camera_default_aim_b __attribute__((sda));
extern int g_camera_default_tracker_word __attribute__((section(".sdata")));
extern float g_camera_default_plane_param __attribute__((sda));
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);

/* Resets the state of object +0x70: eases the motion and view values toward their
   targets (or the defaults in the record at D_L00_001BB040), settles the recoil spring,
   then restores the view, aim and sway defaults from the level tuning values. */
void weapon_reset_view_state_pal(StateOwner *object)
{
    State *state;
    float view_default_x, view_default_y, aim0, aim1, aim2;
    Motion *motion, *defaults;
    View *view, *default_view;
    Recoil *recoil;
    char *temporary;
    Aim *aim;
    Sway *sway;

    temporary = (char *)&object->state->temp;
    *(float *)(temporary + 0x14) = g_cam_rotation_param;
    *(int *)(temporary + 0x1C) = 0;
    *(int *)(temporary + 0x20) = 0;
    *(int *)(temporary + 0x10) = 0;
    *(int *)(temporary + 0x24) = 0;
    state = object->state;
    motion = &state->motion;
    view = &state->view;
    defaults = &g_weapon_view_state->motion;
    default_view = &g_weapon_view_state->view;
    if (motion->h3C)
        motion->f2C = math_step_spring_damper_clamped(motion->v44, motion->f2C, motion->f40, motion->f48,
                                    g_weapon_view_reset_param_a, *(float *)(temporary + 0x1C));
    else
        motion->f2C = math_step_spring_damper_clamped(motion->v44, motion->f2C, defaults->f2C, motion->f48,
                                    g_weapon_view_reset_param_a, *(float *)(temporary + 0x1C));
    if (motion->h3E)
        motion->f30 = math_step_spring_damper_clamped(motion->v50, motion->f30, motion->f4C, motion->f54,
                                    g_weapon_view_reset_param_b, 0.0f);
    else
        motion->f30 = math_step_spring_damper_clamped(motion->v50, motion->f30, defaults->f30, motion->f54,
                                    g_weapon_view_reset_param_b, 0.0f);
    if (view->hDA)
        view->fB0 = math_step_spring_damper_clamped(view->vBC, view->fB0, view->fB4, view->fB8, 0.2f, 0.0f);
    else
        view->fB0 = math_step_spring_damper_clamped(view->vBC, view->fB0, default_view->fB0, view->fB8,
                                  0.2f, 0.0f);
    motion->h3C = 0;
    motion->h3E = 0;
    motion->f40 = 0.0f;
    motion->f4C = 0.0f;
    motion->f58 = defaults->f2C;
    view->hDA = 0;
    view->fB4 = 0.0f;

    object->state->h10 = 1;
    recoil = &object->state->recoil;
    recoil->f1C = 0.005f;
    recoil->f20 = 0.2f;
    recoil->h2 = 0;
    if (recoil->f2C != 0.0f)
        math_step_value_toward_target(&recoil->f28, &recoil->f30, recoil->f2C,
                      recoil->f34, recoil->f38, 1.0f);
    else if (recoil->f28 != 0.0f)
        math_step_value_toward_target(&recoil->f28, &recoil->f30, 0.0f,
                      recoil->f34, recoil->f38, 1.0f);
    recoil->f2C = 0.0f;

    view_default_x = g_camera_default_view_x;
    view_default_y = g_camera_default_view_y;
    view->bD6 = 0;
    view->fDC = view_default_x;
    view->fE4 = view_default_y;
    view->fE0 = 0.2f;
    view->fE8 = 0.2f;
    view->hEC = (g_camera_default_angle_short * 5 + 2) / 6;

    aim = &object->state->aim;
    aim0 = g_camera_default_aim_a;
    aim2 = g_camera_default_aim_c;
    aim1 = g_camera_default_aim_b;
    aim->f44 = aim0;
    aim->f3C = aim2;
    aim->f40 = aim1;
    aim->f48 = g_camera_default_tracker_word;
    aim->h4E = 0;

    sway = &object->state->sway;
    sway->fC = g_camera_default_plane_param;
    sway->h6 = 0;
}
