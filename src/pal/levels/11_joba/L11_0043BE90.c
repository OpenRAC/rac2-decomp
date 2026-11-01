#include "include_asm.h"


extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002A05A8(char *);
extern void func_L11_00441978(unsigned char *object, int class_id);
extern void func_0032C700(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A05A8(char *);
extern void func_002A7750(void *, int, int);

/* Retires the measured stage-46 record: clears the guard, drops the effect and re-tags the object. */
void func_PAL_L11_0043BFF8(char *obj)
{
    char *state = *(char **)(obj + 0x68);

    if (*(short *)(state + 0x282) == 1) {
        func_L11_00441978(*(unsigned char **)(obj + 0xB8), 0xD37);
        *(int *)(state + 0x270) = 0;
    } else {
        *(int *)(state + 0x270) = 0;
    }
    *(short *)(state + 0x282) = 0;
    if (*(unsigned char *)(obj + 0x31)) {
        func_0032C700(obj + 0x10, 0, 0, 0x1E, 5, 0, 0x32, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        func_002E5DA0(0, 0, obj, 0xDF7);
    }
    func_002A7470(obj, 0, 0, 3);
    func_002A05A8(obj);
    func_002A7750(obj, 1, 0);
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) & 0xEFFF) | 0x47;
}

