#include "include_asm.h"

extern char D_001AD8E8[];
extern void func_00336ED0(int, int);
extern void func_00335870(void *, int);

typedef struct Obj335C60 {
    void *f00;
    void *f04;
    char pad08[0x20];
    int f28;
    int f2C;
} Obj335C60;

void func_00335C60(Obj335C60 *obj, int arg)
{
    obj->f04 = D_001AD8E8;
    func_00336ED0(obj->f2C, obj->f28);
    func_00335870(obj, arg);
}
