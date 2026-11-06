#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_31EA58(char *, float, float);
extern void func_002F1F70(void *, void *, void *);
extern void func_0032B468(char *, int, char *, char *, int, int, float *, void *, void *, float);
extern void func_003144D8(char *);
extern char D_L11_001A8F20[] __attribute__((sda));

void func_L11_00449330(char *self, TI128 *pos) {
    char *state = *(char **)(self + 0x68);
    float copy[4];
    float vec[4];

    *(TI128 *)copy = *pos;
    if (*(unsigned char *)(self + 0x31) != 0) {
        func_31EA58((char *)vec, 0.10000000894069672f, 0.16666667163372040f);
        func_002F1F70(vec, vec, D_L11_001A8F20);
        func_0032B468(self, 0x9D8, *(char **)(state + 0x354) + 0x10, *(char **)(state + 0x354) + 0xF0,
                    0, 0, vec, D_L11_001A8F20, D_L11_001A8F20, 0.0027777778450399637f);
    }
    func_003144D8(*(char **)(state + 0x354));
    *(char **)(state + 0x354) = 0;
}
