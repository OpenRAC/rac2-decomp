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

extern void vec_scale_to_length(void *a0, void *a1, float f);

extern void func_PAL_L00_003C76A0(char *a0, char *a1, void *a2);

extern void vec_compute_object_to_target(int a0, char *a1, void *a2, float f);

extern float FastVecLength(void *a0);

extern void *func_PAL_L00_003AD088(char *a0, void *a1, char *a2, int a3, float f12, float f13, float f14);

/* Scales a direction by the current class record's speed (per frame at 60 Hz), negated from the
   object's own vector in player state 1, re-reads the record's second value, applies the
   optional mode adjustment, then spawns through func_PAL_L00_003AD088 and links the result back to
   the object. The two record lookups use separate locals: one reused pointer becomes a global
   pseudo and loses the first lookup's tie to the multiply's register. */
void func_PAL_L00_003C7548(char *a0, char *a1)
{
    char scratch[16];
    char *ctx = *(char **)(a0 + 0x68);
    char *rec;
    char *rec2;
    float f20;
    float f21;
    float f0;
    float f14;
    int mode;
    void *v;

    rec = g_weapon_l00_table + (unsigned char)g_item_slot_to_record[0x19] * 0xE0;
    f0 = *(float *)(rec + 0x50);
    f20 = f0 * 0.020000001f;
    mode = D_00189E20_13.state;
    if (mode == 1)
        vec_scale_to_length(scratch, a0 + 0xD0, -f20);
    else
        vec_scale_to_length(scratch, D_00189E20_13.vector, f20);

    rec2 = g_weapon_l00_table + (unsigned char)g_item_slot_to_record[0x19] * 0xE0;
    f21 = *(float *)(rec2 + 0x70);
    func_PAL_L00_003C76A0(a0, a1, scratch);

    mode = D_00189E20_13.mode;
    if (mode != 0)
        vec_compute_object_to_target(mode, a1, scratch, f20);

    f0 = FastVecLength(scratch);
    f14 = g_moby_fire_shot_extra;
    v = func_PAL_L00_003AD088(a1, scratch, a0, 0, f0, f21, f14);
    *(int *)ctx = (int)v;
    if (v != 0) {
        *(int *)((char *)v + 0xB8) = (int)a0;
    }
}
