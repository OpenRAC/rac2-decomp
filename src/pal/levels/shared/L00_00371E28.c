#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00371E28);

extern unsigned int D_001A7424 __attribute__((sda));
extern int ref_L00_001A8F00_00 __attribute__((sda));
typedef struct L00_0036FA68_Object {
    unsigned char pad00[0x64];
    void (*field64)(struct L00_0036FA68_Object *);
} L00_0036FA68_Object;
extern L00_0036FA68_Object *ref_L00_001AC0C0_00 __attribute__((sda));
extern void func_00284E18(int a, int b, int c);
extern int func_002B49E0(int a, int b, int c, int d, int e);
extern void func_002F5220(void);
extern void func_002E4AC8(void);
extern void func_002B9390(void);
extern void func_L00_00310048(void);
extern unsigned int ref_L00_0036FA68_00(void);
extern void func_002F52B8(void);
extern void func_00289178(void);

/* Runs the level's tick chain once: the three-argument engine reset, a gate on the resident
 * word and the boot flag, then the subsystem updates and the resident object's callback. */
void func_PAL_L00_00372508(void)
{
    L00_0036FA68_Object *object;

    func_00284E18(0, 0, 0);
    if (ref_L00_001A8F00_00 == 0 && (D_001A7424 & 1)) {
        if (func_002B49E0(4, 1, 1, 0, 0) == 0)
            return;
    }
    if (ref_L00_0036FA68_00() != 0)
        return;
    func_002F5220();
    func_002E4AC8();
    func_002B9390();
    func_L00_00310048();
    object = ref_L00_001AC0C0_00;
    object->field64(object);
    func_002F52B8();
    func_00289178();
}


