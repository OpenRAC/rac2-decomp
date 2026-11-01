#include "include_asm.h"

#include "common.h"
extern int D_00138344;
extern int func_US2_0029CFA0(int);
extern unsigned int func_0026F7F8(void);
extern unsigned int func_0026F7F8(void);
extern unsigned int func_0026F7F8(void);
extern unsigned int func_0026F800(void);
extern unsigned int func_0026F7F8(void);
extern unsigned int func_0026F800(void);
extern int func_002CB7D0(int);
extern int func_002CB820(int);
extern int func_002CB8A0(int);
extern int func_US2_002CC908(int);
extern void func_002E5E58(int, unsigned int, void *);
extern unsigned int func_0026F7D0(void);
extern unsigned int func_0026F7D8(void);
extern unsigned int func_0026F7F0(void);
extern unsigned int func_0026F7E8(void);

int func_US2_002CE0C8(void)
{
    unsigned int flags = D_00138344;
    int res = 0;

    if (flags & 0x910) {
        res = 1;
    } else if (flags & 0x40) {
        res = func_US2_0029CFA0(flags);
        if (func_0026F7D0() && func_0026F7D8()) {
            res = func_US2_002CC908(res);
        } else if (func_0026F7F0()) {
            res = func_002CB820(res);
        } else if (func_0026F7E8()) {
            res = func_002CBA58(res);
        } else if (func_0026F800() == 0x31) {
            res = func_002CB7D0(res);
        } else if (func_0026F7F8()) {
            res = func_002CB7D0(res);
        } else if (func_0026F800() == 0x1C) {
            res = func_002CB7D0(res);
        } else {
            res = func_002CB8A0(res);
        }
    } else {
        func_US2_0029CFA0(flags);
    }

    if (res) {
        func_002E5E58(0x12, 0, 0);
    }
    return res;
}

