#include "include_asm.h"
#include "common.h"

extern u32 D_L03_001B0C48 __attribute__((sda));

extern u32 D_L03_001B0C4C NOT_SDA;

extern u32 D_L03_001B0C50 NOT_SDA;

extern u32 D_L03_001B0C54 NOT_SDA;

extern u32 D_L03_001B0C58 NOT_SDA;

extern u32 D_L03_001B0C5C NOT_SDA;

extern f32 D_L03_001B0C60 __attribute__((sda));

extern f32 D_L03_001B0C64 NOT_SDA;

extern f32 func_00283B98(f32, f32);

/* The shared lookup the record's state selects: its target sits at another
   address in every program, so it is named by its own place. */
extern int ref_L01_0031BC68_00(int, int, f32);

/* Eases the record's own rate by the shared factor and hands the state the
   shared lookup asks for. */
/* Updates the glow colour of the puzzle ball. */
void func_L03_003E4588(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u32 colors[2];
    f32 easeStep;
    f32 blend;

    if (moby[0x20] == 5 || *(short *)(vars + 0x6A) == 0) {
        colors[0] = D_L03_001B0C48;
        colors[1] = D_L03_001B0C4C;
        easeStep = D_L03_001B0C60 * 0.00029088825f;
    } else if (*(short *)(vars + 0x68) != 0) {
        colors[0] = D_L03_001B0C50;
        colors[1] = D_L03_001B0C54;
        easeStep = D_L03_001B0C64 * 0.00029088825f;
    } else {
        colors[0] = D_L03_001B0C58;
        colors[1] = D_L03_001B0C5C;
        easeStep = D_L03_001B0C64 * 0.00029088825f;
    }
    blend = FastAddRotations(*(f32 *)(vars + 0x78), easeStep);
    *(f32 *)(vars + 0x78) = blend;
    *(u32 *)(moby + 0x78) = ref_L01_0031BC68_00(colors[0], colors[1], blend);
}
