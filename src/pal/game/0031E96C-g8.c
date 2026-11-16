#include "include_asm.h"
#include "names.h"
extern int g_spark_slot_pool;
extern void gfx_draw_lightning_bolt_ribbon(char *, char *);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_glow_sprite(char *, unsigned int, float, char *, float, int, int);

void spark_update_owned_slots_pal(char *p)
{
    int offset = 0;
    int count = 0xB;
    char *entry;
    char *ptr;
    float f;

    do {
        count--;
        entry = (char *)(offset + (unsigned int)g_spark_slot_pool);
        if (*(int *)(entry + 0x8C) == (int)p) {
            gfx_draw_lightning_bolt_ribbon(p, entry);
            if (*(int *)(entry + 0x94) == 0) {
                ptr = math_random_int_range(0x50, 0x60);
                f = math_random_angle();
                gfx_draw_glow_sprite(entry + 0x30, 0x103080, 0.5f, ptr, f, 0x31, 2);
                ptr = math_random_int_range(0x50, 0x60);
                f = math_random_angle();
                gfx_draw_glow_sprite(entry + 0x30, 0xFFFFFF, 0.3f, ptr, f, 0x31, 2);
            }
        }
        offset += 0xA0;
    } while (count >= 0);
}
