#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
extern s32 D_L16_001B18F0 __attribute__((sda));
extern s32 D_L16_001B18E0 __attribute__((sda));
extern s32 D_L16_001B1704 __attribute__((sda));
extern char D_L16_00189E20[] __attribute__((nosda));
extern s32 FloatToInt(float);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 FastDecTimer(void *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern char D_L16_001A63A8[] __attribute__((nosda));
extern char D_L16_001B1850[] __attribute__((nosda));
extern char D_L16_001B1870[] __attribute__((nosda));
extern void STUB_printf(void *);
extern s32 snd_resume_music_stream(void);
extern int math_fast_float_d(void *);
extern void snd_play_unplayed_voice_line(void *, s32, s32);
extern s32 math_random_int_range(s32, s32);

/* Raises the level's one-shot flag while the counter is low, then hands the sub-object
   its tail record. */
void func_PAL_L16_00417C58(u8 *arg0)
{
    u8 *s1;
    u8 *p;
    u8 *q;

    s1 = *(u8 **)(arg0 + 0x68);
    p = D_L16_00189E20;
    if (*(s32 *)(p + 0x2294) == 0x39) {
        if (*(s32 *)(p + 0x1B8) == 0) {
            STUB_printf(D_L16_001B1850);
            snd_play_unplayed_voice_line(arg0, 0x1C, 0x20);
            D_L16_001B1704++;
        }
    }
    q = D_L16_001A63A8;
    if (*(s16 *)(q + 0x72) == 3 && *(s16 *)(q + 0x6C) < 0x1770) {
        STUB_printf(D_L16_001B1870);
        snd_resume_music_stream();
    }
    math_fast_float_d(s1 + 0x350);
}
