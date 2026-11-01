#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    unsigned char unk00;
    unsigned char unk01;
    unsigned char unk02;
    unsigned char unk03;
    int colour;
    unsigned char unk08;
    unsigned char unk09;
    short life;
    float unk0C;
    TI128 position;
    struct {
        TI128 velocity;
        float unk10;
        short unk14;
        short unk16;
        unsigned char kind;
        char pad19[3];
        int unk1C;
    } motion;
} Particle_002C0CC0;
extern Particle_002C0CC0 *func_002B9030(int);
extern int func_002AAE98(float, float, float, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern unsigned char *D_001F2570;

INCLUDE_ASM("asm/pal/game", func_PAL_002C6890);

