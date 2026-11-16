#include "names.h"
/* func_PAL_L05_0042CAA0 and func_PAL_L05_0042D3B8, the PAL copies of func_L05_00427090 and func_L05_00427988:
 * the same C at 50 Hz, where 1/60 becomes 0.02 and the frame count at 0x28 is scaled by 5/6. */
#include "common.h"

extern char *CreateMoby(int);
extern int FloatToInt(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float g_projectile_l05_frame_time_normal __attribute__((sda));
extern float g_projectile_l05_frame_time_alt __attribute__((sda));
extern int g_projectile_l05_spawn_var __attribute__((sda));
extern float g_projectile_l05_travel_time_normal __attribute__((sda));
extern float g_projectile_l05_travel_time_alt __attribute__((sda));
extern float g_projectile_frame_time_normal __attribute__((sda));
extern float g_projectile_frame_time_alt __attribute__((sda));
extern int g_projectile_spawn_var __attribute__((sda));
extern float g_projectile_travel_time_normal __attribute__((sda));
extern float g_projectile_travel_time_alt __attribute__((sda));

/* Spawns a ship shot (class 0x1182) at pos heading along vec, with its flight time and speed taken from the upgrade flag (PAL: 50 Hz). */
char *projectile_spawn_with_target_pal(char *pos, char *vec, int value_10, char *owner, int flag, int value_2c)
{
    char *obj = CreateMoby(0x1182);

    if (obj != 0) {
        char *vars = *(char **)(obj + 0x68);
        float one;
        float travel_frames;
        float frame_step;
        int count;
        int spawn_delay;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0x1FF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(vars + 0x24) = flag;
        frame_step = (flag ? g_projectile_frame_time_alt : g_projectile_frame_time_normal) * 0.020000001f;
        travel_frames = (flag ? g_projectile_travel_time_alt : g_projectile_travel_time_normal) / frame_step;
        one = 1.0f;
        count = FloatToInt(travel_frames);
        spawn_delay = g_projectile_spawn_var;
        *(int *)(vars + 0x18) = count;
        *(int *)(vars + 0x10) = value_10;
        *(char **)(vars + 0x20) = owner;
        *(int *)(vars + 0x14) = 0;
        *(float *)(vars + 0x1C) = one / travel_frames;
        *(int *)(vars + 0x28) = ((s32)(spawn_delay) * 5 + 2) / 6;
        *(int *)(vars + 0x2C) = value_2c;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        qcopy(obj + 0x10, pos);
        vec_scale_to_length(vars, vec, frame_step);
        vec_scale_to_length(obj + 0xC0, vars, one);
        FastVecCross(obj + 0xD0, obj + 0xC0, owner + 0xE0);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, one);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
    }
    return obj;
}

/* Spawns a level 5 ship projectile (class 0x1191) at pos heading along vec, the same set-up as the other shot spawner (PAL: 50 Hz). */
char *projectile_l05_spawn_pal(char *pos, char *vec, int value_10, char *owner, int flag)
{
    char *obj = CreateMoby(0x1191);

    if (obj != 0) {
        char *vars = *(char **)(obj + 0x68);
        float one;
        float travel_frames;
        float frame_step;
        int count;
        int spawn_delay;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0x1FF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(vars + 0x24) = flag;
        frame_step = (flag ? g_projectile_l05_frame_time_alt : g_projectile_l05_frame_time_normal) * 0.020000001f;
        travel_frames = (flag ? g_projectile_l05_travel_time_alt : g_projectile_l05_travel_time_normal) / frame_step;
        one = 1.0f;
        count = FloatToInt(travel_frames);
        spawn_delay = g_projectile_l05_spawn_var;
        *(int *)(vars + 0x18) = count;
        *(int *)(vars + 0x10) = value_10;
        *(char **)(vars + 0x20) = owner;
        *(int *)(vars + 0x14) = 0;
        *(float *)(vars + 0x1C) = one / travel_frames;
        *(int *)(vars + 0x28) = ((s32)(spawn_delay) * 5 + 2) / 6;
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        qcopy(obj + 0x10, pos);
        vec_scale_to_length(vars, vec, frame_step);
        vec_scale_to_length(obj + 0xC0, vars, one);
        FastVecCross(obj + 0xD0, obj + 0xC0, owner + 0xE0);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, one);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
    }
    return obj;
}
