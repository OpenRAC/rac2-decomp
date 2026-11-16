#include "include_asm.h"
#include "names.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers. */
typedef int Rac2TI128 __attribute__((mode(TI)));

/* Measured partial layout of one 0xB0-byte record of the table at D_002351A0. */
typedef struct Rec_0032B598 {
    unsigned char prefix_00[0x50];
    float f_50;
    float f_54;
    float f_58;
    float f_5C;
    float f_60;
    float f_64;
    float f_68;
    float f_6C;
    float f_70;
    float f_74;
    float f_78;
    float f_7C;
    float f_80;
    float f_84;
    float f_88;
    float f_8C;
    float f_90;
    float f_94;
    int w_98;
    int w_9C;
    int w_A0;
    int w_A4;
    int w_A8;
    unsigned char tail_AC[4];
} Rec_0032B598;

extern Rec_0032B598 g_ring_pieces[];
extern char g_hero_target_point[];

extern float math_random_float_range(float low, float high);
extern float math_random_signed_float_range(float low, float high);
extern void vec_clear_128(void *p);

/* Claims the first free record of the twelve 0xB0-byte records at D_002351A0, keeps the owner's
   pointer in it, copies two quadwords in and fills the drawn values. */
void part_claim_ring_piece(char *owner, char *src, int arg)
{
    Rec_0032B598 *base = g_ring_pieces;
    Rec_0032B598 *slot;
    int i;

    for (i = 0; i < 12; i++) {
        slot = base + i;
        if (slot->w_9C != 0)
            continue;
        slot->w_9C = (int)owner;
        *(Rac2TI128 *)((char *)slot + 0x20) = *(Rac2TI128 *)g_hero_target_point;
        *(Rac2TI128 *)((char *)slot + 0x40) = *(Rac2TI128 *)src;
        slot->f_50 = math_random_float_range(-3.14159274f, 3.14159274f);
        slot->f_54 = math_random_float_range(-3.14159274f, 3.14159274f);
        slot->f_58 = math_random_float_range(-3.14159274f, 3.14159274f);
        slot->f_74 = math_random_float_range(-3.14159274f, 3.14159274f);
        slot->f_78 = math_random_float_range(-3.14159274f, 3.14159274f);
        slot->f_7C = math_random_float_range(-3.14159274f, 3.14159274f);
        slot->f_5C = math_random_signed_float_range(0.001f, 0.005f);
        slot->f_60 = math_random_signed_float_range(0.001f, 0.005f);
        slot->f_64 = math_random_signed_float_range(0.001f, 0.005f);
        slot->f_80 = math_random_signed_float_range(0.001f, 0.005f);
        slot->f_84 = math_random_signed_float_range(0.001f, 0.005f);
        slot->f_88 = math_random_signed_float_range(0.001f, 0.005f);
        slot->f_68 = math_random_float_range(3.25f, 4.75f);
        slot->f_6C = math_random_float_range(3.25f, 4.75f);
        slot->f_70 = math_random_float_range(3.25f, 4.75f);
        slot->f_8C = math_random_float_range(3.25f, 4.75f);
        slot->f_90 = math_random_float_range(3.25f, 4.75f);
        slot->f_94 = math_random_float_range(3.25f, 4.75f);
        vec_clear_128(slot);
        vec_clear_128((char *)slot + 0x10);
        slot->w_A8 = 0;
        slot->w_A0 = arg;
        slot->w_98 = 20;
        slot->w_A4 = arg;
        break;
    }
}
