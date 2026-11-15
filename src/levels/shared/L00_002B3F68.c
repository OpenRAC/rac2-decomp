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

/* Picks how quickly the hero turns, based on how fast the hero moves and the current state, then applies it. */
void hero_set_turn_rates(void)
{
    float speed = ((MovementView *)g_hero_state)->speed;
    float first;
    float second;
    float third;
    if (speed == 1.0f) {
        first = 0.022f;
    } else {
        first = speed * 0.02f;
        if (first > 0.022f)
            first = 0.022f;
        if (first < 0.01f)
            first = 0.01f;
    }
    if (((MovementView *)g_hero_state)->speed == 1.0f) {
        third = 0.09308424592018127f;
    } else {
        third = speed * 0.06399541348218918f;
        if (third > 0.09308424592018127f)
            third = 0.09308424592018127f;
        if (third < 0.03199770674109459f)
            third = 0.03199770674109459f;
    }
    second = 0.27f;
    if (((MovementView *)g_hero_state)->alternate) {
        first = 0.035f;
        third = 0.19489513337612152f;
    }
    switch (hero_slot_item_id(0)) {
    case 16:
    case 28:
    case 29:
    case 30:
    case 39:
    case 46:
        if (((MovementView *)g_hero_state)->special && !((MovementView *)g_hero_state)->alternate) {
            if (speed > 0.95f) {
                first = 0.017f;
                second = 0.18f;
                third = 0.1454441249370575f;
            } else {
                first = speed * 0.009f;
                second = 0.15f;
                third = speed * 0.07853982597589493f;
            }
        }
        break;
    default:
        break;
    }
    hero_steer_heading(0, first, second, third);
}
