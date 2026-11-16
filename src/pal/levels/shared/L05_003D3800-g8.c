#include "include_asm.h"
#include "names.h"

extern int moby_class_id_to_table_index(int);
extern float g_shot_reach_table __attribute__((sda));
extern int snd_play_from_class_bank(int, int, char *, int);
extern void func_L05_003CFB90(char *, char *);
extern float fast_vec_dist(void *, void *);
typedef struct {
    char pad000[0x140];
    float f140[4];
    char pad150[0x10];
    float f160;
    int f164;
    int f168;
    int f16C;
} ShakeCamera_003CFAB8;
extern ShakeCamera_003CFAB8 g_hero_l05_state;

/* When the camera is within the object's reach and the object is not class 0x956, passes the
 * camera position to func_L05_003CFB90, calls func_002E5DA0 and starts a camera shake (weaker
 * and shorter for class 0x955). The shake stores are the same in both arms; cross-jumping
 * shares them after scheduling. */
void cam_shake_if_object_near_pal(char *obj)
{
    float reach = *(float *)((char *)&g_shot_reach_table + 4 * moby_class_id_to_table_index(*(short *)(obj + 0xAA)));

    if (fast_vec_dist(obj + 0x10, g_hero_l05_state.f140) <= reach && *(short *)(obj + 0xAA) != 0x956) {
        func_L05_003CFB90(obj, (char *)g_hero_l05_state.f140);
        snd_play_from_class_bank(7, 0, obj, 0xFBF);
        if (*(short *)(obj + 0xAA) == 0x955) {
            g_hero_l05_state.f160 = 0.05f;
            g_hero_l05_state.f168 = 0x19;
            g_hero_l05_state.f16C = 0;
        } else {
            g_hero_l05_state.f160 = 0.15f;
            g_hero_l05_state.f168 = 0x32;
            g_hero_l05_state.f16C = 0;
        }
    }
}
