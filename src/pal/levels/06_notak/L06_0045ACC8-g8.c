#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad00[0x1830]; unsigned char *player;
    char pad1834[0xA60]; int mode;
} ControllerGlobals;
extern ControllerGlobals D_00189E20;
extern char D_L06_00188660[], D_L06_001B9840[];
extern char D_L06_002AA500[], D_L06_00257CC0[], D_L06_002DF000[], D_L06_00257FC0[], D_L06_002DF060[];
extern int D_L06_001B1858[] SDATA(D_L06_001B1858);
extern int D_L06_001B187C SDATA(D_L06_001B187C);
extern int D_L06_001B1880 SDATA(D_L06_001B1880);
extern void func_L06_00456EE0(void), func_L00_002E6EF8(void);
extern int func_L00_0035F5A0(int, int, char *);
extern void func_002E59F8(int);
extern void func_PAL_L04_003A47C0(void *), func_PAL_L04_003A49E0(void *), func_L04_003A1FA0(void *), func_L04_003A1FE0(void *);
extern void func_L04_003A5C08(char *, float);
extern float func_00282C48(float);
extern void func_002AA548(char *, char *, float, float, float, float);
extern int func_002ACBC8(char *, int);
typedef struct {
    int kind, count; char *items, *models, *data; int *states; char *aux, *more;
    int *a, *b; unsigned char *owner; void (*update)(void), (*callback)(void);
} Context;

void func_PAL_L06_0045BCD0(unsigned char *obj)
{
    char *d;
    Context context;
    float position[4];
    int count, id, allowed;
    unsigned char *player = D_00189E20.player;
    if (player && *(short *)(player + 0xAA) == 0x45 && player[0x20] != 254 && player[0x20] != 253 && D_00189E20.mode == 49) return;
    d = *(char **)(obj + 0x68);
    if (!d) return;
    count = 1;
    if (*(int *)(d + 0x18) != -1) count = D_L06_001B1858[*(int *)(d + 0x18)];
    count += *(int *)(d + 0x10);
    context.kind = 48; context.count = count;
    context.a = &D_L06_001B187C; context.b = &D_L06_001B1880;
    context.items = D_L06_002AA500; context.models = D_L06_00257CC0; context.data = D_L06_002DF000;
    context.states = D_L06_001B1858; context.aux = D_L06_00257FC0; context.more = D_L06_002DF060;
    context.update = func_L06_00456EE0; context.callback = func_L00_002E6EF8;
    context.owner = obj;
    if (*(unsigned char *)(d + 0x14) == 0 && *(int *)(d + 0x18) != -1) {
        char *firstTarget = D_L06_00188660 + *(int *)(d + 0x38) * 0x70;
        if (*(unsigned char **)(firstTarget + 0x88) != obj || *(unsigned char *)(firstTarget + 0x74) == 0)
            *(int *)(d + 0x38) = func_L00_0035F5A0(20, 4, (char *)obj);
    } else {
        id = *(int *)(d + 0x38);
        if (id != -1) {
            char *secondTarget = D_L06_00188660 + id * 0x70;
            if (*(unsigned char **)(secondTarget + 0x88) == obj && *(unsigned char *)(secondTarget + 0x74)) func_002E59F8(id);
        }
        *(int *)(d + 0x38) = -1;
    }
    switch (obj[0x20]) {
    case 0:
        func_PAL_L04_003A47C0(&context);
        func_L04_003A5C08((char *)obj, *(float *)(d + 0x34));
        if (*(int *)(d + 0x28) != -1) {
            int alpha = 255;

            obj[0x30] = alpha;
        }
        /* fall through */
    case 1:
        func_PAL_L04_003A49E0(&context);
        break;
    case 2:
        func_L04_003A1FA0(&context);
        if (func_00282C48(*(float *)(obj + 0x18) - *(float *)(d + 0x2C)) <= 2 && *(int *)(d + 0x18) != -1)
            func_002AA548((char *)obj + 0x18, d + 0x30, *(float *)(d + 0x2C), 0.0024f, 0.0024f, 0.120000005f);
        break;
    }
    func_L04_003A1FE0(&context);
    if (*(int *)(d + 0x28) != -1 && !func_002ACBC8(D_L06_001B9840, *(int *)(d + 0x28))) {
        allowed = 1;
        if (*(int *)(D_L06_001B9840 + 0x2C0)) {
            qcopy(position, D_L06_001B9840);
            position[2] = *(float *)d;
            if (func_002ACBC8((char *)position, *(int *)(d + 0x28))) allowed = 0;
        }
        if (allowed) {
            for (id = *(int *)(d + 0x10); id < context.count; ++id)
                *(short *)(context.items + id * 0x1190 + 0x1E) = 0;
        }
    }
}
