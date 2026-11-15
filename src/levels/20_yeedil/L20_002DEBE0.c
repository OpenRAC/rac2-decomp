#include "common.h"

typedef struct YeedilEffectState {
    char pad00[0x30];
    int mode;
    int frame;
    char pad38[0x154];
    char *first;
    int unused190;
    char *second;
} YeedilEffectState;
extern YeedilEffectState D_L20_001BDCC0;
extern int D_L20_001A8F00[] __attribute__((sda));
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_below(int);
extern void part_spawn_white_flash(void *, void *, int, float);

extern void *CreateMoby(int);

extern float coll_probe_ground_height_below(void *, int, float);

extern void euler_rotation_basis(void *, void *);

/* Updates a spark-spraying effect (moby class 3882) during a Yeedil scene. At a set moment it fires a burst, then it keeps
 * shooting sparks from a scene object while the scene runs. */
void spark_l20_burst_update(unsigned char *object)
{
    float position[4], velocity[4];
    float speed, heading, tilt;
    YeedilEffectState *state;

    switch (object[0x20]) {
    case 0:
        object[0x30] = 0xFF;
        object[0x20] = 1;
        break;
    case 1:
        if (D_L20_001A8F00[0] != 2)
            break;
        state = &D_L20_001BDCC0;
        if (state->mode != 7)
            break;
        if (state->frame == 157)
            SpawnExplosion(state->second + 0x10, 1, 40, 20, 30, 40, 50, 1,
                          1, 1, 0, 0, 1.5f, 20.0f);
        if ((unsigned int)(state->frame - 171) < 149) {
            moby_transform_joint_to_world(state->first, 0, position);
            position[2] += 0.03f;
            speed = math_random_float_range(0.028333336114883423f, 0.05000000447034836f);
            heading = math_random_angle();
            tilt = math_random_float_range(0.523598849773407f, 2.6179940700531006f);
            vec_build_spherical_offset(velocity, speed, heading, tilt);
            if (math_random_int_below(2))
                part_spawn_white_flash(position, velocity, 0, math_random_float_range(1470.0f, 7350.0f));
        }
        break;
    }
}

/* func_L20_002DEBE0 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */

/* func_L20_00310E38 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */

extern unsigned char D_L20_001DBA60[];

extern void *D_L20_001DB100[];

extern void update_moby_animation_state(void *);

extern void func_002A0F48(void *);

/* Turns a moby into another class: copies the new class settings (animation, size, collision) from the class tables. */
void moby_change_class_from_tables(void *moby, int class_id)
{
    unsigned char *type_data;
    unsigned char *type_data2;
    unsigned char *type_data3;
    int extra_value;

    *(short *)(moby + 0xAA) = (short)class_id;
    *(unsigned char *)(moby + 0x22) = D_L20_001DBA60[(short)class_id];
    *(void **)(moby + 0x24) = D_L20_001DB100[*(unsigned char *)(moby + 0x22)];
    update_moby_animation_state(moby);
    type_data = *(unsigned char **)(moby + 0x24);
    *(unsigned char *)(moby + 0x62) = type_data[0xE];
    *(float *)(moby + 0x2C) = *(float *)(type_data + 0x24);
    *(int *)(moby + 0x98) = *(int *)(type_data + 0x10);
    *(unsigned char *)(moby + 0x61) = 0xFF;
    if (type_data) {
        extra_value = *(int *)(type_data + 0x40);
        if (extra_value) {
            *(unsigned short *)(moby + 0x34) |= 0x10;
            *(int *)(moby + 0x78) = *(int *)(type_data + 0x40);
        }
        type_data2 = *(unsigned char **)(moby + 0x24);
        if (type_data2[0xF]) {
            *(unsigned char *)(moby + 0x6F) = 0x18;
            *(unsigned short *)(moby + 0x34) |= 0x400;
            *(int *)(moby + 0x70) = 0;
            *(int *)(moby + 0x74) = 0;
            *(unsigned char *)(moby + 0xBD) = 0;
        }
        type_data3 = *(unsigned char * volatile *)(moby + 0x24);
        if (type_data3[6]) {
            *(unsigned char *)(moby + 0x63) = 0x18;
        }
    }
    func_002A0F48(moby);
}

/* Catalogue defect: the row's first two words (0x0036AE68 `sw $t3,0x40($v1)` /
   `nop`) sit after the previous function's `jr $ra` (0x0036AE5C) and are
   unreachable; the eight bytes at 0x0036AE70 (`addiu $sp,$sp,0x20` / `nop`)
   are the stub row this level's splitter cuts out of a function (74 of them
   in level 20, e.g. at 0x00308688), so the real body starts at 0x0036AE78
   and is 272 bytes: a leaf function with no frame, no saved register and
   `jr $ra` at 0x0036AF80.  It reaches data through $gp twice (0x0036AF0C
   and 0x0036AF58, both `lw $a0,-0x4800($gp)` -> 0x001AA7F0), so it belongs
   in the -G8 unit once the row is split. */
/* func_L20_0036AE68 is defined in L20_0036AE68-g8.c (it reads its list through $gp). */

extern void level_clear_first_table_entry(void);

extern int request_begin_slot(int a, int b, int c, int d, int e);

extern int D_L20_001FFE40[];

extern int D_L20_001A8FDC __attribute__((sda));

extern int D_L20_00294F98;

/* Sets up a Yeedil scene: runs the common setup, stores a scene table and starts the scene. */
void cutscene_start_scene(void)
{
    int *base;
    int *other;

    level_clear_first_table_entry();
    base = D_L20_001FFE40;
    other = &D_L20_00294F98;
    *(int *)(base + 0x40) = (int)other;
    *(int *)(base + 0x41) = 0xB;
    D_L20_001A8FDC = 1;
    request_begin_slot(3, 1, 0xB, 0, 0);
}

/* Creates the glowing effect object (moby class 4802) on an owner at a given spot and hands back the new object. */
char *glow_effect_create(void *owner, void *position, int param1, int param2)
{
    char *effect;
    int pos_addr;
    int zero_addr;
    char *owner_ref;

    effect = (char *)CreateMoby(0x12C2 /* moby class 4802 */);
    if (effect) {
        *(int *)(effect + 0xB8) = (int)owner;
        *(unsigned char *)(effect + 0x30) = 0xFF;
        pos_addr = (int)effect + 0x10;
        qcopy((void *)pos_addr, position);
        *(int *)(owner + 0x98) = 0;
        *(float *)(effect + 0x18) = *(float *)(effect + 0x18) + 2.0f;
        *(float *)(effect + 0x18) = coll_probe_ground_height_below((void *)pos_addr, 0, 0.5f);
        owner_ref = *(char **)(effect + 0xB8);
        *(int *)(owner_ref + 0x98) = *(int *)(*(int *)(owner_ref + 0x24) + 0x10);
        zero_addr = (int)effect + 0xF0;
        qzero_nc((void *)zero_addr);
        euler_rotation_basis((void *)((int)effect + 0xC0), (void *)((int)effect + 0xF0));
        {
            int *vars = *(int **)(effect + 0x68);
            vars[1] = param1;
            vars[2] = param2;
        }
    }
    return effect;
}


/* func_L20_0039BB18 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */

/* func_L20_0039BEC8 is defined in L20_002DEBE0-g8.c (it reaches data through $gp). */
