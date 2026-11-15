#include "common.h"

typedef int InitQuad __attribute__((mode(TI)));
typedef struct { u8 pad[0xB0]; float scale; } PathView;
extern PathView D_L00_001BD2C0;
extern u8 *D_L00_001FDA80[];
typedef struct { u8 pad[0x194]; InitQuad *transform; } PathCamera;
extern PathCamera D_L00_001B8C80;
extern float mat_fast_helper_a(float x, float y);
extern void vec_clear_128(InitQuad *v);
extern int hero_l00_set_action(int event, int value);
/* Partial records follow only the fields used by the two path walks.
 * Retail reserves eight weight/index slots and assumes at most eight accepted
 * entries; it does not add a bounds check to the path scan. */
typedef struct {
    u8 unknown00[0x20];
    int pathIndex;
    int secondPathIndex;
    u8 unknown28[0x10];
    u8 active;
    u8 unknown39;
    short duration;
    float speed;
    u8 unknown40[0xC];
    int eventGate;
    int initialized;
    u8 unknown54[0xC];
    float weights[8];
    int indices[8];
} PathConfig;
typedef struct {
    int first;
    int second;
    float distance;
    float secondDistance;
    int current;
    short node;
    short duration;
} MotionPrefix;

extern void euler_to_matrix(char *, char *);
extern int math_fast_float_d(char *);
extern float IntToFloat(int);
extern void math_blend_vector_sine_ease(char *, char *, char *, float);
extern void math_blend_vec3_sine_ease(char *, char *, char *, float);
extern void cam_compute_direction_angles(char *, char *, char *);
extern float fast_subtract_rotations(float, float);
extern float math_cosine_blend(float, float, float);
extern float math_blend_scalar_toward_target(float, float, float);
extern float cubic_hermite_scalar(float, float, float, float, float);
extern float math_step_spring_damper_clamped(char *, float, float, float, float, float);
extern float math_step_spring_damper_stored(char *, float, float, float, float, float);
extern float D_L00_001B8DD8;


/* Measured child block reached at owner->sub + 0x40. */
typedef struct { char pad[0x4C]; float height; } Part_28CE0;



extern void coll_visit_grid_entries(int);

extern void func_L00_00425490_1(int);

extern void ship_read_steer_and_throttle(int, float *, float *);

extern void cam_vehicle_update_turn(int, float, float);

extern void FollowCameraHideObstructions(int);

extern void cam_follow_move_eye(int);

extern void follow_camera_build_view(int);

extern void func_00282F20_1(char *a0, char *a1, float f);

extern void func_00282D30_5(char *a0, char *a1, float f);

extern void func_00282CC0_4(char *a0, char *a1, char *a2);

extern char D_00189E20_6[];

extern char g_hero_position[];

extern void vec_spherical_to_vector(char *first, char *second, char *third);

extern float func_00283B98_6(float value, float reference);

extern void func_00283410_5(char *out, char *source);

extern void copy_matrix3x4(char *object, char *out);

extern void func_L00_002D7940_1(char *p);

extern void func_L00_002EE0C0(char *p);

extern void func_L00_00427B40_1(char *p);

extern char D_L00_001B8C80_1[];

extern char D_00189E20_3[];

extern float func_00283248_1(float a, float b);

extern float FastDiffRots(float a, float b);

extern float fast_vec_dist(char *a, char *b);

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Owner {
    unsigned char unknown_00[0x7d];
    unsigned char value_7d;
    short value_7e;
    unsigned char unknown_80[6];
    short identity_86;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Owner;

extern void ref_L00_00428EB0_00(char *);

extern void ref_L00_00428EB0_01(char *);

extern void UpdateCameraTransition(char *);

extern void ResolveCameraMovementCollisions(char *, float);

extern void cam_reset_mode_state(char *);

extern void func_0035F3A8(int, int, int);

extern void *object_init_base(void *);

extern void cam_build_basis_from_hero(char *);

#define SDA_OBJ __attribute__((section(".sdata")))

extern char *D_L00_001B1844 SDA_OBJ;

extern char *g_follow_camera_object;

extern char D_L00_001ADD98[] SDA_OBJ;

extern char D_L00_001ADD38[] SDA_OBJ;

extern char D_L00_001ADD78[] SDA_OBJ;

extern char D_L00_001ADD58[] SDA_OBJ;

typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Global {
    unsigned char unknown_00[0x2290];
    char *ptr_2290;
    int mode_2294;
    unsigned char unknown_2298[0x208];
    int identity_24a0;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Global;

extern Rac2Native_6af85cabb56d3b41_SmallConditional52Global D_00189E20_20;

/* runs a fixed sequence of seven callees on one object handle, passing the address of two stack floats to the third callee and then their values to the fourth */
/* Runs one frame of the follow camera: sets it up, steers it, hides things in its way and builds the view. */
void cam_follow_run_frame(int object)
{
    float x;
    float y;

    coll_visit_grid_entries(object);
    func_L00_00425490_1(object);
    ship_read_steer_and_throttle(object, &x, &y);
    cam_vehicle_update_turn(object, x, y);
    FollowCameraHideObstructions(object);
    cam_follow_move_eye(object);
    follow_camera_build_view(object);
}
/* Camera mode hook that does nothing. */
void cam_mode_noop(void)
{
}

/* selects one of three scale factors from a flag byte in a fixed global table, builds two 16-byte stack values through two callees, then applies two transforms rooted at object+48 against two fixed global tables */
/* Works out where the camera should look from the hero position, with a different strength for each hero mode. */
void cam_build_aim_from_hero(char *camera)
{
    char direction[16];
    char scaled[16];
    char *hero = D_00189E20_6;
    unsigned char mode;

    func_00282F20_1(direction, (char *)(*(int *)(hero + 8848) + 224), 1.0f);
    mode = *(unsigned char *)(hero + 8884);
    if (mode == 2) {
        func_00282D30_5(scaled, direction, 9.5f);
    } else if (mode == 1) {
        func_00282D30_5(scaled, direction, 0.75f);
    } else {
        func_00282D30_5(scaled, direction, 1.6f);
    }
    func_00282CC0_4(camera + 48, g_hero_position, scaled);
    func_00282CC0_4(camera + 48, g_hero_position + 208, camera + 48);
}

/* func_L00_00426560 is defined in L00_00426560-helpers.c. */

/* clears the seven words of the sub-object at +0x70 (the last after a refresh call), then
   clears the flag word and the identity word-16 of the table entry and the owner's +0x7E. */
/* Clears the camera mode state and resets the camera to its starting view. */
void cam_reset_mode_state(char *camera)
{
    char *vars = *(char **)(camera + 0x70);
    char *entry;

    *(int *)(vars + 0x0) = 0;
    *(int *)(vars + 0x8) = 0;
    *(int *)(vars + 0x4) = 0;
    *(int *)(vars + 0xC) = 0;
    *(int *)(vars + 0x10) = 0;
    *(int *)(vars + 0x14) = 0;
    *(int *)(vars + 0x18) = 0;
    cam_build_basis_from_hero(camera);
    entry = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84) * 0x20 + 0x1C);
    *(short *)(entry + 0x26) = 0;
    *(short *)(camera + 0x7E) = 0;
}



/* Starts the aligned camera mode and clears its blend values. */
void cam_aligned_start(char *camera)
{
    char *camState = D_L00_001B8C80_1;
    char *camStateAgain;
    short phase = *(short *)(camState + 0x290);

    if (phase != 0) {
        *(short *)(camState + 0x290) = 2;
    } else {
        *(short *)(camState + 0x290) = 1;
    }
    camStateAgain = D_L00_001B8C80_1;
    *(char *)(camStateAgain + 0x293) = 0;
    *(float *)(camStateAgain + 0x2B4) = 0.075f;
    *(float *)(camStateAgain + 0x2A8) = 0.075f;
    cam_reset_mode_state(camera);
    if (*(int *)(camStateAgain + 0x264) != 0) {
        func_0035F3A8(0, 0, *(int *)(camStateAgain + 0x264));
    }
}

/* when the mode halfword at +0x86 is 4 or 0x51, raises the flag halfword of the table entry
   selected by the owner's index halfword at +0x84. */
/* Marks the camera entry as active when the hero is in one of two special modes. */
void cam_flag_entry_for_hero_mode(void)
{
    char *camera = g_follow_camera_object;
    short mode = *(short *)(camera + 0x86);
    char *entry;

    if (mode == 4 || mode == 0x51) {
        entry = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84) * 0x20 + 0x1C);
        *(short *)(entry + 0x26) = 1;
    }
}

extern float FastVecDot(char *a0, char *a1);

extern void FastVecScale(char *a0, char *a1, float f);

extern void FastVecSub(char *a0, char *a1, char *a2);

extern float FastVecLength(char *a0);

extern float math_fast_angle_helper(float f);

/* Restores the owner's half-turn state: it measures the two world vectors of the table
   entry, compares the angle they make with a fixed threshold, and writes the owner's
   half-word at +0x7E and the entry's flag half-word at +0x290. The block at the end
   resets the entry's two small floats and the owner's state; the two tests jump to it,
   and it needs its own copy of the entry's address. */
/* Decides which camera state to switch to, based on how the hero and camera line up. */
void cam_choose_state_from_hero_angle(char *camera)
{
    char scaled[16];
    char cameraVec[16];
    char heroVec[16];
    char *camState;
    char *camStateAgain;
    float cameraDot;
    float heroDot;
    float lengthProduct;
    float dot;
    float angle;

    if (D_00189E20_20.identity_24a0 == 0x51) {
        return;
    }
    if (D_00189E20_20.identity_24a0 == 4) {
        return;
    }
    camState = D_L00_001B8C80_1;
    if (*(short *)(camState + 0x290) == 0) {
        *(char *)(camState + 0x293) = 0;
        *(short *)(camera + 0x7E) = 2;
        *(float *)(camState + 0x2B4) = 0.018f;
        *(float *)(camState + 0x2A8) = 0.018f;
        return;
    }
    cameraDot = FastVecDot(camState + 0x1D0, camera);
    FastVecScale(scaled, camState + 0x1D0, cameraDot);
    FastVecSub(cameraVec, camera, scaled);
    heroDot = FastVecDot(camState + 0x1D0, D_00189E20_20.ptr_2290 + 0xC0);
    FastVecScale(scaled, camState + 0x1D0, heroDot);
    FastVecSub(heroVec, D_00189E20_20.ptr_2290 + 0xC0, scaled);
    lengthProduct = FastVecLength(heroVec);
    if (lengthProduct == 0.0f) {
        goto small;
    }
    lengthProduct = lengthProduct * FastVecLength(cameraVec);
    if (lengthProduct == 0.0f) {
        goto small;
    }
    dot = FastVecDot(heroVec, cameraVec);
    angle = math_fast_angle_helper(dot / lengthProduct);
    if (1.3962636f <= 1.5707964f - angle) {
        *(short *)(camState + 0x290) = 0;
        *(short *)(camera + 0x7E) = 4;
        return;
    }
small:
    camStateAgain = D_L00_001B8C80_1;

    *(char *)(camStateAgain + 0x293) = 0;
    *(short *)(camera + 0x7E) = 2;
    *(float *)(camStateAgain + 0x2B4) = 0.018f;
    *(float *)(camStateAgain + 0x2A8) = 0.018f;
}

extern void func_002EE0D0(void *);
extern void func_002EE970(void *, void *);
extern void func_002EEBD8(void *, void *);

/* Sets up the camera blend speeds and resets its position and turning state. */
void cam_init_blend_settings(unsigned char *camera) {
    unsigned char rotation[0x40];
    unsigned char *positionSettings;

    *(int *)(*(unsigned char **)(camera + 0x70) + 0xC0) = 4;
    positionSettings = *(unsigned char **)(camera + 0x70) + 0x30;
    *(float *)(positionSettings + 0x20) = 0.05f;
    *(float *)(positionSettings + 0x24) = 0.3f;
    *(float *)(positionSettings + 0x28) = 1.0f;
    *(unsigned short *)(positionSettings + 0x2C) = 1;
    func_002EE0D0(positionSettings);
    {
        unsigned char *vars = *(unsigned char **)(camera + 0x70);

        *(float *)(vars + 0x10) = 0.3f;
        *(float *)(vars + 0x14) = 0.3f;
        *(float *)(vars + 0x18) = 1.0f;
        *(unsigned short *)(vars + 0x1C) = 1;
        func_002EE0D0(vars);
    }
    func_002EE970(rotation, camera + 0x40);
    func_002EEBD8(camera, rotation);
    *(unsigned short *)(camera + 0x7E) = 0;
}

/* Blends the saved camera position and orientation, then rebuilds its matrix. */
void UpdateCameraTransition(char *object)
{
    char matrix[64];
    char *saved = *(char **)(object + 0x70);
    char *rotation = saved + 0x30;
    char *target = saved + 0x80;
    char *transition = saved + 0xE0;
    float x, y, delta, blend;

    if (*(unsigned char *)(object + 0x88) == 1) {
        goto snap;
    } else if (*(unsigned char *)(object + 0x88) == 2) {
        float fraction;

        math_fast_float_d(transition);
        fraction = (float)(*(int *)(transition + 4) - *(int *)(saved + 0xE0)) /
                   IntToFloat(*(int *)(transition + 4));
        math_blend_vector_sine_ease(object + 0x30, object + 0x30, target, fraction);
        math_blend_vec3_sine_ease(object + 0x40, object + 0x40, saved + 0x90, fraction);
        goto finish;
    } else if (*(unsigned char *)(object + 0x88) == 3) {
        float fraction;

        if (math_fast_float_d(transition)) {
        snap:
            qcopy(object + 0x30, target);
            qcopy(object + 0x40, saved + 0x90);
            goto finish;
        }
        fraction = (float)(*(int *)(transition + 4) - *(int *)(saved + 0xE0)) /
                   IntToFloat(*(int *)(transition + 4));
        cam_compute_direction_angles(saved + 0xE8, target, g_hero_position);
        x = fast_subtract_rotations(*(float *)(transition + 8), *(float *)(transition + 0x1C));
        y = fast_subtract_rotations(*(float *)(target + 0x18), D_L00_001B8DD8);
        if ((x > 0.3490659f && y < -0.3490659f) ||
            (x < -0.3490659f && y > 0.3490659f)) {
            float zero = 0.0f;

            delta = *(float *)(transition + 8) - *(float *)(transition + 0x1C);
            if (delta < zero && y > zero)
                delta = -delta;
            else if (delta > zero && y < zero)
                delta = -delta;
            *(float *)(transition + 0x1C) += math_cosine_blend(0.0f, delta, fraction);
        } else {
            *(float *)(transition + 0x1C) = math_blend_scalar_toward_target(
                *(float *)(transition + 0x1C), *(float *)(transition + 8), fraction);
        }
        blend = cubic_hermite_scalar(*(float *)(transition + 0x44), 0.0f, 1.0f,
                             *(float *)(transition + 0x48), fraction);
        *(float *)(transition + 0x24) +=
            (*(float *)(transition + 0x10) - *(float *)(transition + 0x24)) * blend;
        *(float *)(transition + 0x20) = math_blend_scalar_toward_target(
            *(float *)(transition + 0x20), *(float *)(transition + 0xC), fraction);
        math_blend_vector_sine_ease(transition + 0x30, transition + 0x30, g_hero_position, fraction);
        vec_spherical_to_vector(object + 0x30, transition + 0x1C, transition + 0x30);
        math_blend_vec3_sine_ease(object + 0x40, object + 0x40, target + 0x10, fraction);
        goto finish;
    }
    if (*(short *)(saved + 0x1C) == 1) {
        *(float *)(object + 0x30) = math_step_spring_damper_clamped(saved,
            *(float *)(object + 0x30), *(float *)target,
            *(float *)(saved + 0x10), *(float *)(saved + 0x14), *(float *)(saved + 0x18));
        *(float *)(object + 0x34) = math_step_spring_damper_clamped(saved + 4,
            *(float *)(object + 0x34), *(float *)(target + 4),
            *(float *)(saved + 0x10), *(float *)(saved + 0x14), *(float *)(saved + 0x18));
        *(float *)(object + 0x38) = math_step_spring_damper_clamped(saved + 8,
            *(float *)(object + 0x38), *(float *)(target + 8),
            *(float *)(saved + 0x10), *(float *)(saved + 0x14), *(float *)(saved + 0x18));
    }
    if (*(short *)(rotation + 0x2C) == 1) {
        *(float *)(object + 0x40) = math_step_spring_damper_stored(rotation,
            *(float *)(object + 0x40), *(float *)(target + 0x10),
            *(float *)(rotation + 0x20), *(float *)(rotation + 0x24), *(float *)(rotation + 0x28));
        *(float *)(object + 0x44) = math_step_spring_damper_stored(saved + 0x34,
            *(float *)(object + 0x44), *(float *)(target + 0x14),
            *(float *)(rotation + 0x20), *(float *)(rotation + 0x24), *(float *)(rotation + 0x28));
        *(float *)(object + 0x48) = math_step_spring_damper_stored(saved + 0x38,
            *(float *)(object + 0x48), *(float *)(target + 0x18),
            *(float *)(rotation + 0x20), *(float *)(rotation + 0x24), *(float *)(rotation + 0x28));
    }
finish:
    euler_to_matrix(matrix, object + 0x40);
    copy_matrix3x4(object, matrix);
}

/* Camera hook that does nothing and returns 0. */
unsigned int cam_hook_return_zero(void)
{
    return 0;
}

/* When the sub-object at +0x70 gains its flag word at +0x40, clears the byte at +0x89 and
   fades the block at +0x30 to a half-turn target. */
/* Updates the camera transition and, when it finishes, fades the camera view back in. */
void cam_update_transition_and_fade(char *camera)
{
    char *transition = *(char **)(camera + 0x70) + 0xE0;

    UpdateCameraTransition(camera);
    if (*(int *)(transition + 0x40)) {
        *(char *)(camera + 0x89) = 0;
        ResolveCameraMovementCollisions(camera + 0x30, 0.5f);
    }
}

/* Camera hook that does nothing. */
void cam_mode_noop_b(void)
{
}

/* Refreshes a child sub-structure through a setup helper, folds four float pairs (one measured against a fixed half-turn constant) through a shared two-float helper, and hands the resulting four-field block to a second helper. */
/* Turns the camera angles toward their targets and rebuilds the camera matrix. */
void cam_update_angles_to_target(char *camera)
{
    float matrixSource[16];
    char *transition = *(char **)(camera + 112);

    transition += 176;
    vec_spherical_to_vector(camera + 48, camera + 80, transition);
    *(float *)(camera + 80) = func_00283B98_6(*(float *)(camera + 80), *(float *)(transition + 24));
    *(int *)(camera + 64) = 0;
    *(float *)(camera + 68) = func_00283B98_6(*(float *)(camera + 84), *(float *)(camera + 92));
    *(float *)(camera + 72) = func_00283B98_6(3.14159265f, *(float *)(camera + 80));
    *(float *)(camera + 72) = func_00283B98_6(*(float *)(camera + 72), *(float *)(camera + 96));
    *(int *)(camera + 76) = 0;
    func_00283410_5((char *)matrixSource, camera + 64);
    copy_matrix3x4(camera, (char *)matrixSource);
}

extern void func_L00_002D7958_1(float *, void *, float);

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TQ_00427BE8 __attribute__((mode(TI)));

/* func_L00_00427BE8 is defined in L00_00427BE8-helpers.c. */

/* resets a sub-object reached through field +112 of its argument: two int zeros through a pointer 176 bytes in, twelve float constants (0.3/0.04/0.07/1.0/0.99) and three int zeros over offsets 40..172, then four calls (sub-object, +80, +144, the argument) and a 16-bit zero at +126 */
/* Sets the camera blend speeds to their starting values and clears the camera state. */
void cam_l00_init_blend_values_2(char *camera)
{
    char *transition = (char *)*(int **)(camera + 112) + 176;
    float *vars;

    *(int *)(transition + 64) = 0;
    vars = (float *)*(int **)(camera + 112);
    vars[40] = 3.0000001192092895507812e-01f;
    vars[41] = 3.0000001192092895507812e-01f;
    vars[39] = 0.0f;
    vars[42] = 0.0f;
    *(int *)(transition + 68) = 0;
    vars[43] = 0.0f;
    vars[18] = 9.9000000953674316406250e-01f;
    vars[15] = 3.9999999105930328369141e-02f;
    vars[16] = 3.9999999105930328369141e-02f;
    vars[17] = 3.9999999105930328369141e-02f;
    vars[10] = 7.0000000298023223876953e-02f;
    vars[11] = 1.0000000000000000000000e+00f;
    vars[19] = 3.9999999105930328369141e-02f;
    vars[12] = 7.0000000298023223876953e-02f;
    vars[13] = 1.0000000000000000000000e+00f;
    vars[14] = 7.0000000298023223876953e-02f;

    func_L00_002D7940_1((char *)vars + 80);
    func_L00_002D7940_1((char *)vars);
    func_L00_002EE0C0((char *)vars + 144);
    func_L00_00427B40_1(camera);

    *(short *)(camera + 126) = 0;
}

/* func_L00_00427D50 is defined in L00_00427D50-g8.c. */


/* func_L00_004282F0 is defined in L00_004282F0-spawn.c. */

/* Reads two floats from a data block, differences them against two globals, calls a two-float helper with the difference pair, refines the returned float through a second helper, then selects one of two small state codes and clears a flag byte according to two float thresholds. */
/* Checks how far the hero has turned from the camera and picks the next camera state. */
void cam_pick_state_from_hero_turn(char *camera)
{
    char *camState = D_L00_001B8C80_1;
    char *hero = D_00189E20_3;
    float *heroPos = *(float **)(hero + 8848);
    float value = FastDiffRots(*(float *)(camState + 344),
                      func_00283248_1(heroPos[4] - *(float *)(camState + 320),
                              heroPos[5] - *(float *)(camState + 324)));

    if (value < 0.5585054f) {
        value = fast_vec_dist(hero + 128, camState + 320);
        if (value < 8.0f) {
            *(char *)(camState + 659) = 0;
            *(short *)(camera + 126) = 2;
            *(float *)(camState + 692) = 0.018f;
            *(float *)(camState + 680) = 0.018f;
        } else {
            *(short *)(camera + 126) = 4;
        }
    } else {
        *(short *)(camera + 126) = 4;
    }
    *(char *)(camera + 125) = 0;
}

/* Camera hook that does nothing and returns 0. */
int cam_hook_return_zero_b(void) {
    return 0;
}

/* func_L00_004284B0 is defined in L00_004284B0-helpers.c. */

/* Camera hook that does nothing. */
void cam_mode_noop_c(void)
{
}

/* func_L00_00428588 is in L00_00428588.c. */



/* runs a fixed pair of callees on the same object handle */
/* Runs the two camera setup steps on the same camera. */
void cam_run_setup_steps(char *camera)
{
    ref_L00_00428EB0_00(camera);
    ref_L00_00428EB0_01(camera);
}

/* A method that does nothing and returns 0, reached through a data pointer in every
   level that has it. Its entry is 24 bytes into the catalogued row, after linker fill. */
int cam_hook_return_zero_c(void) {
    return 0;
}


/* When the global identity differs from the signed owner identity at offset 0x86 and the global mode is not 6, clear the owner byte at offset 0x7D and write signed short value 3 at offset 0x7E. */
/* Switches the camera to state 3 if the hero has changed and is not in mode 6. */
void cam_switch_state_on_hero_change(Rac2Native_6af85cabb56d3b41_SmallConditional52Owner *owner)
{
    if (D_00189E20_20.identity_24a0 != owner->identity_86 &&
        D_00189E20_20.mode_2294 != 6) {
        owner->value_7d = 0;
        owner->value_7e = 3;
    }
}

#define MACRO_ADDR __attribute__((section(".sdata")))

extern char * r1_D_L10_0015F050 MACRO_ADDR;

extern char *r1_D_L10_0015F050 MACRO_ADDR;

/* rac1-decomp src/overlays/shared/vendor_00299AF0.c: func_L10_002F6E10 */
/* Adapted from Lombyte (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002e3de8.c, FUN_L10_002f5a50. */
/* Marks the camera entry as locked. */
void cam_lock_entry(int index) {
    unsigned char *entry;
    entry = *(unsigned char **)(r1_D_L10_0015F050 + index * 0x20 + 0x1C);
    entry[0x38] = 1;
    entry[0x39] = 0;
}


extern char * r1_D_L10_001B0C30[];
extern int r1_func_00215570(void *, int);
extern int r1_func_L00_00260AB0(void *, int);
extern int r1_func_L00_00260B68(float *, int);
extern int r1_func_L00_0025A778(float *, float *, int);

/* rac1-decomp src/overlays/shared/rocket_and_path_camera.c: func_L00_004290C0 */
/* Adapted from Lombyte's project (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002e3de8.c, FUN_L10_002f5a78. */
/* Checks whether the hero is inside the area that triggers this camera. */
int cam_is_hero_in_trigger(char *camera, char *unused)
{
    unsigned char *entry = *(unsigned char **)(r1_D_L10_0015F050 + *(short *)(camera + 0x84) * 32 + 0x1C);

    if (*(int *)(entry + 0x0C) >= 0) {
        if (r1_func_00215570(g_hero_position, *(int *)(entry + 0x0C))) return 1;
    } else if (*(int *)(entry + 0x10) >= 0) {
        if (r1_func_L00_00260AB0(g_hero_position, *(int *)(entry + 0x10))) return 1;
    } else if (*(int *)(entry + 0x08) >= 0) {
        if (r1_func_L00_00260B68((float *)g_hero_position, *(int *)(entry + 0x08))) return 1;
    } else if (*(int *)(entry + 0x14) >= 0) {
        int nodeIndex = *(int *)(entry + 0x14);
        if (r1_func_L00_0025A778((float *)g_hero_position,
                                  (float *)(r1_D_L10_001B0C30[nodeIndex] + 0x10),
                                  *(int *)r1_D_L10_001B0C30[nodeIndex])) return 1;
    } else if (entry[0x38] != 0 && entry[0x39] == 0) {
        return 1;
    }
    return 0;
}

void InitPathMotion(u8 *object)
{
    PathConfig *data = *(PathConfig **)(D_L00_001B1844 + *(short *)(object + 0x84) * 32 + 0x1c);
    MotionPrefix *motion;
    u8 *pathState;
    float *weights = data->weights;
    int accepted;
    float distance;
    InitQuad *transform;
    data->active = 1;
    motion = (MotionPrefix *)(*(u8 **)(object + 0x70) + 0x40);
    motion->first = 0;
    motion->second = 0;
    motion->distance = 0;
    motion->secondDistance = 0;
    motion->current = 0;
    motion->node = 0;
    motion->duration = data->duration;
    pathState = *(u8 **)(object + 0x70) + 0x58;
    {
        int i;
        for (i = 0; i < 8; i++) {
            data->weights[i] = 0.0f;
            data->indices[i] = -1;
        }
    }
    accepted = 0;
    *(float *)(pathState + 0x30) = mat_fast_helper_a(1.0f, D_L00_001BD2C0.scale) * 2.0f;
    if (data->initialized == 0 && data->pathIndex >= 0) {
        int i;
        u8 *path = D_L00_001FDA80[data->pathIndex];
        for (i = 0; i < *(int *)path; i++) {
            float weight = *(float *)(path + (i << 4) + 0x1C);
            if (weight > 0.0f) {
                weights[accepted] = weight;
                if (weight > 180.0f)
                    weights[accepted] = *(float *)(pathState + 0x30) * 57.2957763671875f;
                data->indices[accepted] = i;
                accepted++;
            }
            distance = fast_vec_dist((char *)(path + (i * 16 + 0x10)), (char *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
            *(float *)(path + (i << 4) + 0x1C) = distance;
            if (i < *(int *)path - 1)
                motion->distance += distance;
        }
    }
    if (data->duration > 0)
        data->speed = (motion->distance / IntToFloat(data->duration)) * 60.0f;
    if (data->secondPathIndex >= 0) {
        int i;
        u8 *path = D_L00_001FDA80[data->secondPathIndex];
        for (i = 0; i < *(int *)path; i++) {
            int byteOffset = i * 16;
            distance = fast_vec_dist((char *)(path + (byteOffset + 0x10)), (char *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
            *(float *)(path + byteOffset + 0x1C) = distance;
            if (i < *(int *)path - 1)
                motion->secondDistance += distance;
        }
    }
    { u8 *saved = *(u8 **)(object + 0x70);
    *(float *)saved = 0.03f;
    *(float *)(saved + 4) = 0.2f;
    vec_clear_128((InitQuad *)(saved + 0x10));
    }
    { u8 *saved = *(u8 **)(object + 0x70);
    *(float *)(saved + 0x20) = 0.03f;
    *(float *)(saved + 0x24) = 0.2f;
    vec_clear_128((InitQuad *)(saved + 0x30));
    }
    transform = D_L00_001B8C80.transform;
    qcopy(object + 0x30, transform + 3);
    qcopy(object, transform);
    qcopy(object + 0x10, transform + 1);
    qcopy(object + 0x20, transform + 2);
    if (data->eventGate == 0)
        hero_l00_set_action(0x6f, 1);
    data->initialized = 1;
}

extern int D_0018C0BC;
extern int D_0018C0B4;
extern int cam_is_hero_in_trigger(char *, char *);

/* Decides whether this camera should take over, stay as it is, or give up control. */
int cam_decide_takeover(char *camera, char *other)
{
    char *entry = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84) * 0x20 + 0x1C);

    if (*(unsigned char *)(entry + 0x39) != 0) {
        return -1;
    }
    if (*(unsigned char *)(entry + 0x38) != 0 && *(short *)(other + 0x86) != 0x13) {
        return 1;
    }
    if (other != 0 && *(short *)(other + 0x7E) == 0 &&
        *(unsigned char *)(other + 0x7C) >= *(unsigned char *)(camera + 0x7C)) {
        return 0;
    }
    if (cam_is_hero_in_trigger(camera, other) == 0) {
        return 0;
    }
    if (*(int *)(entry + 0x48) >= 0 && D_0018C0BC != *(int *)(entry + 0x48)) {
        return 0;
    }
    if (*(int *)(entry + 0x44) >= 0 && D_0018C0B4 != *(int *)(entry + 0x44)) {
        return 0;
    }
    return 1;
}

/* Camera hook that does nothing. */
void cam_mode_noop_d(void)
{
}

/* func_L00_00429CE8 is defined in L00_00429CE8.c. */

/* func_L00_00429F68 is defined in L00_00429F68.c. */

extern int D_L00_001A8F00 __attribute__((sda));

extern int cam_test_trigger_volumes(char *);

extern void UpdateVolumeAimCamera(char *);

/* Looks the owner's table entry up (index half-word at +0x84, 0x20 bytes per entry, the
   entry's own pointer at +0x1C) and clears its flag half-word at +0x26 and its word at
   +0x20, but only when the entry is still idle, the global gate allows it and the extra
   check accepts the owner. */
/* Updates the camera entry and resets it when the trigger is no longer valid. */
int cam_update_entry_reset(char *camera)
{
    char *entry = *(char **)(D_L00_001B1844 + *(short *)(camera + 0x84) * 0x20 + 0x1C);

    if (*(short *)(entry + 0x26) != 0) {
        return 0;
    }
    if (D_L00_001A8F00 != 0) {
        if (cam_test_trigger_volumes(camera) != 0) {
            *(short *)(entry + 0x26) = 0;
            *(int *)(entry + 0x20) = 0;
            return 0;
        }
    }
    UpdateVolumeAimCamera(camera);
    return 0;
}

/* Distinct empty callbacks, each independently entered from dispatch data. */
/* Empty camera callback. */
void cam_callback_noop_a(void) {}
/* Empty camera callback. */
void cam_callback_noop_b(void) {}
/* Empty camera callback. */
void cam_callback_noop_c(void) {}

/* clears the word at +0x20 and the halfword at +0x26 of the table entry selected by the
   index argument. */
/* Resets the camera entry so it is no longer active. */
void cam_reset_entry(int index)
{
    char *entry = *(char **)(D_L00_001B1844 + index * 0x20 + 0x1C);

    *(short *)(entry + 0x26) = 0;
    *(int *)(entry + 0x20) = 0;
}


/* func_L00_0042A698 is defined in L00_00426340-g8.c. */

/* func_L00_0042A908 is defined in L00_0042A908-g8.c. */

/* The actor hook receives its owner even when this implementation returns no index. */
/* Camera hook that does nothing and returns -1. */
int cam_hook_return_minus_one(char *owner) {
    return -1;
}

/* Camera hook that does nothing. */
void cam_mode_noop_e(void)
{
}

/* func_L00_0042AC18 is defined in L00_0042AC18.c. */

/* func_L00_0042AD98 is defined in L00_0042AD98.c. */


extern void r1_func_001F9BF0(void *, void *, void *);
extern void r1_func_001F9EC0(void *, void *, void *);
extern float r1_func_001F9B88(float);
extern float r1_func_001FA888(int);
extern int r1_func_001FA898(float);
extern void r1_func_L01_002A2C90(int a, int b, int c, int d, int e);
extern char D_00189003[];


/* rac1-decomp src/overlays/shared/music_box_voices.c: func_L00_0042B038 */
/* reverb box sound update: starts or stops the sound as the listener enters or leaves the box */
void snd_update_reverb_box(char *moby) {
    float localPos[4];
    float boxPos[4];
    unsigned char *soundData = *(unsigned char **)(moby + 8);
    r1_func_001F9BF0(localPos, D_00189003 + 0xE9D, moby + 0x40);
    localPos[3] = 0;
    r1_func_001F9EC0(boxPos, localPos, moby + 0x50);
    if (r1_func_001F9B88(boxPos[0]) <= 1.0f && r1_func_001F9B88(boxPos[1]) <= 1.0f && r1_func_001F9B88(boxPos[2]) <= 1.0f) {
        float blend = (boxPos[0] + 1.0f) * 0.5f;
        int volume = r1_func_001FA898(r1_func_001FA888(*(int *)(soundData + 4)) * blend);
        int limit = *(int *)(soundData + 4);
        if (!(limit < volume)) limit = volume;
        r1_func_L01_002A2C90((int)moby, soundData[0], limit, soundData[1], soundData[2]);
        soundData[3] = 1;
    } else if (soundData[3] != 0) {
        if (boxPos[0] > 0.0f) {
            r1_func_L01_002A2C90(0, soundData[0], *(int *)(soundData + 4), soundData[1], soundData[2]);
        } else {
            r1_func_L01_002A2C90((int)moby, 0, 0, 0, 0);
        }
        soundData[3] = 0;
    }
}


/* refreshes the object, installs the block at +0x30 and returns the object. */
/* Sets up the camera object with the first camera data table. */
char *cam_init_object_table_a(char *object)
{
    object_init_base(object);
    *(char **)(object + 0x30) = D_L00_001ADD98;
    return object;
}


/* Sets up the camera object with the second camera data table. */
char *cam_init_object_table_b(char *object)
{
    object_init_base(object);
    *(char **)(object + 0x30) = D_L00_001ADD38;
    return object;
}

/* Sets up the camera object with the third camera data table. */
char *cam_init_object_table_c(char *object)
{
    object_init_base(object);
    *(char **)(object + 0x30) = D_L00_001ADD78;
    return object;
}


/* Sets up the camera object with the fourth camera data table. */
char *cam_init_object_table_d(char *object)
{
    object_init_base(object);
    *(char **)(object + 0x30) = D_L00_001ADD58;
    return object;
}


/* Store the supplied unsigned 32-bit word at owner byte offset 0x 44. */
/* Stores a value in the object. */
void moby_set_field_44_a(int owner, unsigned int value)
{
  *(unsigned int*)(owner + 0x44) = value;
  return;
}

/* Store the supplied unsigned 32-bit word at owner byte offset 0x 40. */
/* Stores a value in the object. */
void moby_set_field_40_a(int owner, unsigned int value)
{
  *(unsigned int *)(owner + 0x40) = value;
  return;
}


/* Store the supplied unsigned 32-bit word at owner byte offset 0x 40. */
/* Stores a value in the object. */
void moby_set_field_40_b(int owner, unsigned int value)
{
  *(unsigned int *)(owner + 0x40) = value;
  return;
}

/* Store the supplied unsigned 32-bit word at owner byte offset 0x 44. */
/* Stores a value in the object. */
void moby_set_field_44_b(int owner, unsigned int value)
{
  *(unsigned int*)(owner + 0x44) = value;
  return;
}

/* Empty callback. */
void noop_callback(void)
{
}

/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 â€” identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

/* Returns the value it was given. */
unsigned long return_argument_64(unsigned long value)
{
  return value;
}
