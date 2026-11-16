#include "names.h"
/* func_PAL_L00_003C7548, the PAL copy of func_L00_003C37C8: the same C, where rename func_L00_003C3920 becomes func_PAL_L00_003C76A0; rename func_L00_003A98E8 becomes func_PAL_L00_003AD088. */

/* Reads the small counter in the shared data area and reports whether it equals two. */
/* Clears one word of each of the thirty 0xA0-byte records that start at D_L00_0023DDA0,
   then one word of each of the sixteen 0xB0-byte records at D_L00_0023F060, walking down
   from the last record of each table, and finally the shared flag word. */
/* Clears the shared flag word this file's small-data area holds at 0x1AFF98. */
/* Gate followed by a fixed sequence of four bound helpers on the state record at offset 0x68. */
extern char g_item_slot_to_record[];

typedef struct {
    char prefix[0x760];
    float vector[4];
    char pad770[0xBF8 - 0x770];
    int mode;
    char padBFC[0x24EC - 0xBFC];
    short state;
} Player37;
extern Player37 D_00189E20_13;

extern char g_weapon_l00_table[];

/* A float in the boot's small data: the sda attribute and this unit's -G8 make the
   reference to it $gp-relative, the way retail has it. */
extern float g_moby_fire_shot_extra __attribute__((sda));

extern void vec_scale_to_length(void *moby, void *muzzle_pos, float f);

extern void part_l00_spawn_spark_shower_pal(char *moby, char *muzzle_pos, void *a2);

extern void vec_compute_object_to_target(int moby, char *muzzle_pos, void *a2, float f);

extern float FastVecLength(void *moby);

extern void *SpawnProjectile_pal(char *moby, void *muzzle_pos, char *a2, int a3, float f12, float f13, float extra);

/* Scales a direction by the current class record's speed (per frame at 60 Hz), negated from the
   object's own vector in player state 1, re-reads the record's second value, applies the
   optional mode adjustment, then spawns through func_PAL_L00_003AD088 and links the result back to
   the object. The two record lookups use separate locals: one reused pointer becomes a global
   pseudo and loses the first lookup's tie to the multiply's register. */
void moby_fire_shot_pal(char *moby, char *muzzle_pos)
{
    char scratch[16];
    char *ctx = *(char **)(moby + 0x68);
    char *rec;
    char *rec2;
    float step_speed;
    float second_value;
    float value;
    float extra;
    int mode;
    void *shot;

    rec = g_weapon_l00_table + (unsigned char)g_item_slot_to_record[0x19] * 0xE0;
    value = *(float *)(rec + 0x50);
    step_speed = value * 0.020000001f;
    mode = D_00189E20_13.state;
    if (mode == 1)
        vec_scale_to_length(scratch, moby + 0xD0, -step_speed);
    else
        vec_scale_to_length(scratch, D_00189E20_13.vector, step_speed);

    rec2 = g_weapon_l00_table + (unsigned char)g_item_slot_to_record[0x19] * 0xE0;
    second_value = *(float *)(rec2 + 0x70);
    part_l00_spawn_spark_shower_pal(moby, muzzle_pos, scratch);

    mode = D_00189E20_13.mode;
    if (mode != 0)
        vec_compute_object_to_target(mode, muzzle_pos, scratch, step_speed);

    value = FastVecLength(scratch);
    extra = g_moby_fire_shot_extra;
    shot = SpawnProjectile_pal(muzzle_pos, scratch, moby, 0, value, second_value, extra);
    *(int *)ctx = (int)shot;
    if (shot != 0) {
        *(int *)((char *)shot + 0xB8) = (int)moby;
    }
}
