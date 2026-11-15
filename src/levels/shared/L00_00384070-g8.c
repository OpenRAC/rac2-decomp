#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type, p, off) (*(type *)((char *)(p) + (off)))

extern int math_random_int_below(int);
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *, void *);
extern void anim_start_immediate(signed char *, int, int);
extern void moby_set_light_color(void *, int);

extern Vector4 D_L00_001AED70[2] __attribute__((sda));
extern Vector4 D_L00_001AED90 __attribute__((sda));
extern float D_L00_001AEDA0[2] __attribute__((sda));
extern int D_L00_001AEDA8[2] __attribute__((sda));
extern Vector4 D_L00_001AED50 __attribute__((sda));
extern char *D_L00_00232A60[24];

/* Create the two attached objects and the twenty-four optional table entries. */
int sheep_board_create_objects(char *owner)
{
    char *work = FIELD(char *, owner, 0x68);
    char **slot = (char **)(work + 0x48);
    int i = 0, result = 0;
    int j;
    Vector4 *basis;

    FIELD(int, work, 0x68) = math_random_int_below(255);
    do {
        *slot = CreateMoby(MOBY_CLASS_SYNTHENOID);
        moby_init_child_from_parent(*slot, 0);
        anim_start_immediate((signed char *)*slot, 1, 0);
        FIELD(unsigned short, *slot, 0x34) |= 0x4002;
        FIELD(unsigned char, *slot, 0xBC) = i;
        qcopy(*slot + 0xF0, &D_L00_001AED90);
        qcopy(work + i * 16, &D_L00_001AED70[i]);
        qzero(work + 0x20 + i * 16);
        FIELD(float, *slot, 0x2C) =
            FIELD(float, FIELD(char *, *slot, 0x24), 0x24) * D_L00_001AEDA0[i];
        moby_set_light_color(*slot, D_L00_001AEDA8[i]);
        ++i;
        ++slot;
    } while (i < 2);
    FIELD(float, work, 0x74) = 0.5f;
    slot = D_L00_00232A60;
    basis = &D_L00_001AED50;
    j = 23;
    do {
        *slot = CreateMoby(MOBY_CLASS_SHEEP);
        if (*slot) {
            moby_init_child_from_parent(*slot, 0);
            result = math_random_int_below(FIELD(unsigned char,
                FIELD(char *, FIELD(char *, *slot, 0x24), 0x50), 0x10));
            anim_start_immediate((signed char *)*slot, 2, result);
            FIELD(unsigned short, *slot, 0x34) |= 0x4002;
            qcopy(*slot + 0xF0, basis);
        }
        --j;
        ++slot;
    } while (j >= 0);
    if (FIELD(char *, work, 0x48) != 0 && FIELD(char *, work, 0x4C) != 0)
        return 1;
    return 0;
}
