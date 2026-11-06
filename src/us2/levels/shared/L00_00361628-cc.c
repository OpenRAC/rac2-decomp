/* func_US2_L00_00361628, the USA v2.00 copy of func_L00_003603C0: the same C, where rename func_002E64A0 becomes func_US2_002E72D8. */
#include "common.h"

/* Measured purchase-panel layout and pricing records. */
/* Layouts measured from the selected-item panel. */
typedef struct { unsigned int word[4]; } PanelColors;
typedef struct { int price; int pad[3]; unsigned char *name; int pad2[2]; } ShopItem;
extern PanelColors D_L00_001AD768;
typedef struct { char prefix[0x144]; ShopItem items[0]; } ShopModel;
extern ShopModel D_L00_0022F7C0;
typedef struct {
    int key;
    int value;
} Entry32fd6f60;

extern Entry32fd6f60 D_L07_002A4100[];

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_acdcf1600d770d3b_ScalarConfigure116State {
    unsigned char prefix_00[0x60];
    unsigned int value_60;
    int value_64;
    unsigned char selector_68;
    unsigned char axis_69;
    unsigned char mode_6a;
    unsigned char dirty_6b;
} Rac2Native_acdcf1600d770d3b_ScalarConfigure116State;

extern Rac2Native_acdcf1600d770d3b_ScalarConfigure116State D_00188660_2[];

/* Walks up to 25 records of 10 bytes; for each record whose 16-bit key is non-negative and whose table byte is set, resolves an object through a helper and copies/relocates it with the record's 16-bit length, capping the destination table at 25 entries. */
/* Shared slot table: the first free record of a 112-byte table is filled with the index and the
 * caller's value; returns the record number, or -1 when the index is out of range. */
/* Same slot table as func_L00_0035F5A0, but with the caller's own record: the helper gets the
 * slot's record, the value goes in at 0x40 and the helper's second value becomes the fifth
 * argument; the record's index word is written at 126 and the value word at 140. */
/* Builds a slot index out of three weight/kind arguments and fills the same 112-byte record as
 * above; the record's value word comes from the fifth argument, the helper's from the sixth. */
extern Entry32fd6f60 D_L00_002A3B00[];

/* Table search: walks the 8-byte records of D_L00_002A3B00 until the key is
 * found or the -1 terminator is met, and stores the record's index and value. */
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef void (*DrawCallback)(void *);
extern int D_L00_001A8F00 __attribute__((sda));
extern char *D_L00_00220DA0[];
extern short D_L00_001A8F80[2] MACRO_ADDR;
extern unsigned int D_001A7AF0 __attribute__((sda));
extern Vector D_L00_001B8DC0;
extern char D_00189EA0[];

extern unsigned int D_00138324;
extern char D_00152C00[];
extern int D_L00_001B1AE0 __attribute__((sda));
extern void func_US2_002E72D8(void *);
/* func_L00_002E6EF8 in level 0; its address differs in levels 8, 9, 19 and 30. */
extern void ref_L00_003603C0_00(DrawCallback, void *);
extern void func_L00_002E6CF0(DrawCallback, void *);
extern void func_002ECB70(void *);
extern void func_002E6B78(void *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283CE0(int);
extern float func_00283180(float);
extern int func_002B0C28(int, int, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A89A8(void *, int, float);
extern float func_00283B98(float, float);
extern int func_L00_003268E8(int);

/* The hero's current vehicle (+0x2BC) is class 0xD54 and not in state 253 or 254. An inline
   function reading the pointer once compiles differently (964 bytes); retail matches the
   expression repeated at each use. */
#define HERO_VEHICLE (*(unsigned char **)(D_00189EA0 + 0x2BC))
#define HERO_RIDING_D54() \
    (HERO_VEHICLE && *(short *)(HERO_VEHICLE + 0xAA) == 0xD54 && \
     (unsigned char)HERO_VEHICLE[0x20] != 254 && (unsigned char)HERO_VEHICLE[0x20] != 253)

void func_US2_L00_00361628(unsigned char *object) {
    Vector position;
    Vector offset;
    Vector angles;
    unsigned char *private = *(unsigned char **)(object + 0x68);
    char **slot;
    int index;
    short key;
    char *spawn;
    unsigned int shade;
    int available;
    if (!D_L00_001A8F00) func_US2_002E72D8(object);
    if ((unsigned char)object[0x31]) {
        private[0xE] = (unsigned char)private[0xE] + 2;
        key = D_L00_001A8F80[(D_001A7AF0 >> 4) & 1];
        for (index = 0; D_L00_00220DA0[index]; index++) {
            slot = D_L00_00220DA0 + index;
            if (*(short *)(D_L00_00220DA0[index] + 0xAA) == key) {
                shade = (int)(func_00283180(func_00283CE0((unsigned char)private[0xE] - 128) * 0.024543693f) * 50.0f) + 140;
                *(unsigned int *)(*slot + 0x78) = shade | (shade << 8) | (shade << 16);
                *(unsigned short *)(*slot + 0x34) |= 0x10;
                break;
            }
        }
        ref_L00_003603C0_00(func_002ECB70, object);
        if (func_00282E80(object + 0x10, &D_L00_001B8DC0) < 32.0f)
            func_L00_002E6CF0(func_002E6B78, object);
    }
    if (*(short *)(private + 0xC) != 0) {
        if (func_00282E48(object + 0x10, &D_00189EA0) > 6.1f && !HERO_RIDING_D54())
            *(short *)(private + 0xC) = 0;
    } else {
        if (func_00282E80(object + 0x10, &D_00189EA0) < 8.0f || HERO_RIDING_D54()) {
            if (func_00282E48(object + 0x10, &D_00189EA0) < 6.0f || HERO_RIDING_D54())
                *(short *)(private + 0xC) = 1;
        }
    }
    if (*(unsigned short *)(object + 0x34) & 1) *(short *)(private + 0xC) = 0;
    if (*(short *)(private + 0xC)) {
        available = func_002B0C28(2, 0x12ea, 1) != 0;
        if ((D_00138324 & 0x10) && available) {
            offset.q = 0;
            angles.q = 0;
            offset.f[0] = 1.48f;
            offset.f[1] = 2.64f;
            angles.f[0] = -0.021118486f;
            angles.f[1] = 0.0588176f;
            angles.f[2] = 1.2252212f;
            func_00283098(&position, &offset, object + 0xC0);
            func_00282CC0(&position, &position, object + 0x10);
            position.f[2] = func_002A89A8(&position, 0, 0.5f);
            angles.f[2] = func_00283B98(angles.f[2], *(float *)(object + 0xF8));
            spawn = D_00152C00 + 0x70;
            qcopy(spawn, &position);
            qcopy(spawn + 0x10, &angles);
            func_L00_003268E8(2);
            *(short *)(spawn - 0x4A) = 0;
            D_L00_001B1AE0 = 1;
        }
    }
}

/* Same body as func_L00_003046D0: compares two words of a 332-byte-stride table and calls the
 * two helpers when the entry ahead is greater; returns 1. */
/* func_L00_00367308 is defined in L00_00358D98-g8.c. */

#define NOT_SDA __attribute__((section(".data")))

extern void *r1_D_0012F86C_00367720 NOT_SDA;

/* rac1-decomp src/core/001138A8.c: func_001138A8 */
/* func_L00_0036F488 is defined in L00_0036F488-g8.c. */

/* The level's own resident word and resident object: each place resolves its own value from
 * the retail bytes (0x001A8F00 and 0x001AC0C0 in 00_aranos_tutorial), so both are sda. */
typedef struct L00_0036FA68_Object {
    unsigned char pad00[0x64];
    void (*field64)(struct L00_0036FA68_Object *);
} L00_0036FA68_Object;

extern L00_0036FA68_Object *ref_L00_001AC0C0_00 __attribute__((sda));

/* The tick gate's callee is a neighbouring local function in six of the programs. */
/* Runs the level's tick chain once: the three-argument engine reset, a gate on the resident
 * word and the boot flag, then the subsystem updates and the resident object's callback. */
/* func_L00_00373D40 is defined in L00_00373D40-g8.c. */

/* func_L00_00373F48 is defined in L00_00373F48-g64.c. */

/* func_L00_00374348 is defined in L00_00374348.c. */

/* Dispatch on a mode word: mode 1 goes through the recording wrapper, the other modes replay. */
/* func_L00_00374C18 is defined in L00_00374C18-g8.c. */

/* Draws the selected-item panel, its value and label, and the top counter. */
/* func_L00_00377C50 is defined in L00_00377C50-g8.c. */

/* func_L00_003781B0 is defined in L00_003781B0.c. */

/* func_L00_00378578 is defined in L00_00378578.c. */

/* Draws the selected purchase prompt, quantity, total price and bolt icon. */
/* Measured rows of the confirmation prompt: the price is their first word. */
/* The call must reach the compiler's builtin: its argument setup order differs from a plain call. */
/* Draws the confirmation prompt, with another message and layout when the price is affordable. */
/* func_L00_00378DE0 is defined in L00_00378DE0-g8.c. */

/* func_L00_00378E90 is defined in L00_00378E90.c. */

/* func_L00_0037A2E8 is defined in L00_0037A2E8-qcopy.c. */

/* func_L00_0037A610 is defined in L00_0037A610-g8.c. */

