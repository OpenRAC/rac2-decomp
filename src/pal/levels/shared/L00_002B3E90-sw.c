#include "include_asm.h"
#include "names.h"

typedef struct {
    unsigned char prefix[0x40F];
    unsigned char alternate;
    unsigned char gap[0x1EA8];
    unsigned char special;
    unsigned char gap2[0x1FF];
    float speed;
} MovementView;
extern char g_hero_state[];
extern int hero_slot_item_id(int index);
extern void hero_steer_heading(int index, float a, float b, float c);


