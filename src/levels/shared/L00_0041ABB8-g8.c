#include "include_asm.h"
#include "names.h"

typedef struct { int a, b; } PAIR8;

extern PAIR8 g_debris_choice_pair __attribute__((nosda));

extern int g_lava_gun_entry_effect_counter __attribute__((sda));

extern void func_2EE0D0(void *dst);

extern int func_3411A0(void *a0, void *a1, int a2, float f12);

/* The level's literal pool, read through $gp. */
extern float g_weapon_anim_blend_a_end __attribute__((sda));
extern float g_weapon_anim_blend_b_end __attribute__((sda));
extern float g_weapon_anim_blend_a_start __attribute__((sda));
extern float g_weapon_anim_blend_b_start __attribute__((sda));

extern int FastDecTimer(short *p);

extern int cam_offset_point_by_vector(char *obj, char *arg1, float *local, unsigned char index);

extern void cam_ease_vector_toward(char *obj, float *a1, float *a2, float f12, float f13, float f14);

/* The parts of an object state (object +0x70) that func_L00_00422268 resets. */
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
extern unsigned short g_camera_default_angle_short __attribute__((sda));
extern float g_camera_default_aim_c __attribute__((sda)), g_camera_default_aim_a __attribute__((sda));
extern float g_camera_default_aim_b __attribute__((sda));
extern int g_camera_default_tracker_word __attribute__((section(".sdata")));
extern float g_camera_default_plane_param __attribute__((sda));
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);

/* Starts a small effect at an entry of the ring. It alternates between two choices each time it is called. */
void lava_gun_spawn_entry_effect(char *object, void *entry)
{
    int local[4];
    int sel[2];
    char *state = *(char **)(object + 0x68);
    float scale;

    func_2EE0D0(local);
    *(PAIR8 *)sel = g_debris_choice_pair;
    scale = *(float *)(state + 0x50) * 0.025f;
    func_3411A0(entry, local, sel[g_lava_gun_entry_effect_counter % 2], scale);
    g_lava_gun_entry_effect_counter = g_lava_gun_entry_effect_counter + 1;
}

/* Updates the type byte and interpolates the two values passed to the helper. */
void weapon_update_anim_blend(char *moby, char *context)
{
    char *mobyVars;
    char *anim;
    short blendTimer;
    float scale;
    float valueA;
    float valueB;
    float valueC;
    float local[3];

    mobyVars = *(char **)(moby + 0x70);
    anim = mobyVars + 0x60;

    if (FastDecTimer((short *)(mobyVars + 0x126)) != 0) {
        *(unsigned char *)(anim + 0xC5) = *(unsigned char *)(anim + 0xC4);
    }
    blendTimer = *(short *)(anim + 0xC6);
    scale = (float)blendTimer * *(float *)(anim + 0xC8);
    cam_offset_point_by_vector(moby, context, local, *(unsigned char *)(anim + 0xC4));

    if (*(unsigned char *)(anim + 0xC4) == 3 ||
        *(unsigned char *)(anim + 0xC4) == 5 ||
        *(unsigned char *)(anim + 0xC4) == 6 ||
        *(unsigned char *)(anim + 0xC4) == 7 ||
        *(unsigned char *)(anim + 0xC4) == 1) {
        valueA = g_weapon_anim_blend_a_start + (g_weapon_anim_blend_a_end - g_weapon_anim_blend_a_start) * scale;
        valueB = g_weapon_anim_blend_b_start + (g_weapon_anim_blend_b_end - g_weapon_anim_blend_b_start) * scale;
    } else {
        valueA = g_weapon_anim_blend_a_end;
        valueB = g_weapon_anim_blend_b_end;
    }
    valueC = 0.0f;
    cam_ease_vector_toward(moby, (float *)(anim + 0x90), local, valueA, valueB, valueC);
}

/* Resets the state of object +0x70: eases the motion and view values toward their
   targets (or the defaults in the record at D_L00_001BB040), settles the recoil spring,
   then restores the view, aim and sway defaults from the level tuning values. */
void weapon_reset_view_state(StateOwner *object)
{
    State *state;
    float viewDefaultX, viewDefaultY, aim0, aim1, aim2;
    Motion *motion, *defaults;
    View *view, *defaultView;
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
    defaultView = &g_weapon_view_state->view;
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
        view->fB0 = math_step_spring_damper_clamped(view->vBC, view->fB0, defaultView->fB0, view->fB8,
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

    viewDefaultX = g_camera_default_view_x;
    viewDefaultY = g_camera_default_view_y;
    view->bD6 = 0;
    view->fDC = viewDefaultX;
    view->fE4 = viewDefaultY;
    view->fE0 = 0.2f;
    view->fE8 = 0.2f;
    view->hEC = g_camera_default_angle_short;

    aim = &object->state->aim;
    aim0 = g_camera_default_aim_a;
    aim1 = g_camera_default_aim_b;
    aim2 = g_camera_default_aim_c;
    aim->f3C = aim2;
    aim->f44 = aim0;
    aim->f40 = aim1;
    aim->f48 = g_camera_default_tracker_word;
    aim->h4E = 0;

    sway = &object->state->sway;
    sway->fC = g_camera_default_plane_param;
    sway->h6 = 0;
}
