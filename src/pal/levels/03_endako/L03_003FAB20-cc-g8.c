/* func_PAL_L03_003FAB20, the PAL copy of func_L03_003F62C8: the same C, where scale D_L03_001B1058. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

/* These bodies reach D_L03_001B2A1C with `lw $a2,0x3A2C($gp)`, which only a
 * -G8 unit emits; the same symbol is reached with an absolute `lui`/`lw` pair
 * inside func_L03_003F66D8 and func_L03_0041D128, so those stay in the -G0 file. */
/* The two words the entity's state is chosen by, both reached through $gp. */
extern s32 D_L03_001B108C __attribute__((sda));
extern u32 D_L03_001B1058 __attribute__((sda));

extern void func_002A7750(void *entity, int a, int b);
extern int func_002A77E0(int id);

/* The engine's particle and light helpers, called with the level's own copies. */
/* The level's own float, reached through $gp. */
/* Two more of the level's floats, at +0x2C10 and +0x2C14 from $gp. */
/* What the engine builds a particle from: two words, then two floats. */
/* The stream table itself is `lui $v0,0x20 ; addiu $v0,$v0,-0x4A60` (absolute). */
/* Picks the entity's next behaviour.  A global word chooses it when it is not
 * negative; else the state's own counters do, each one running down as it is
 * used.  Every behaviour sets up its timers and calls. */
void func_PAL_L03_003FAB20(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    s32 sel;

    if (D_L03_001B108C >= 0) {
        sel = D_L03_001B108C;
    } else if (state[0x30A] != 0) {
        state[0x30A]--;
        sel = 1;
    } else if (state[0x309] != 0) {
        state[0x309]--;
        sel = 0;
    } else if (state[0x30B] != 0) {
        state[0x30B]--;
        sel = 2;
    } else {
        sel = func_002A77E0(state[0x308] + 1);
    }

    switch (sel) {
    case 0:
        func_002A7750(entity, 7, 3);
        if (state[0x308] >= 2) {
            *(float *)(state + 0x2F8) = 0.6981318f;
            *(float *)(state + 0x2FC) = -0.6981318f;
        } else if (func_002A77E0(2) != 0) {
            *(float *)(state + 0x2F8) = 0.6981318f;
        } else {
            *(float *)(state + 0x2FC) = -0.6981318f;
        }
        state[0x30B] = 1;
        break;
    case 1:
        *(u32 *)(state + 0x2E4) = 250;
        func_002A7750(entity, 9, 4);
        state[0x309] = func_002A77E0(2) + 1;
        break;
    case 2:
        *(u32 *)(state + 0x2E4) = (((int)(D_L03_001B1058) * 5 + 2) / 6);
        func_002A7750(entity, 12, 5);
        state[0x309] = 1;
        break;
    }
}

/* Walks the entity's stream, storing 1 at +0x2D6 of every record whose halfword
 * at +0xAA is 0xFFC.  Twin of func_L01_003B5290 (same file layout, level 1). */
/* Same walk as func_L03_0041D0A8 after seeding two state halfwords. */
/* Sets the entity's two blend channels up, then fires two particles: the engine builds
 * each one from the state's direction, a random count and a colour, and the caller fills
 * the record's own fields in.  The two blocks fill the FIRST particle's header again, and
 * the second one keeps its own pointer to the sub-record: both are the original's own
 * wording, and the compiler's schedule depends on it. */
/* Sets the entity up for a shot: the state's own counter, its two blend rates and the
 * frame the shot was prepared on. */
/* The level's own runtime block: two counters the engine writes and the two
 * pointers it keeps. */
typedef struct {
    u8 pad00[0x30];
    s32 field30;
    s32 field34;
    u8 pad38[0x158];
    u8 *field190;
    u8 *field194;
} L03Block;

extern L03Block D_L03_001BD680;

/* The level's mode word, reached through $gp. */
