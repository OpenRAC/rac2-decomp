#include "common.h"

typedef struct {
    int a;
    float b;
    int c;
    int d;
} Quad_L26_0040C8A8;

extern void func_002B41A8(char *, char *, char *, char *, char *, char *, char *, char *,
                          char *, char *, char *);
extern void func_002A7750(char *, int, int);
extern void func_002B44C0(char *, char *, int);

/* Per-frame update for a moby that starts a looping effect when it spawns and then keeps it running. */
void func_L26_0040C8A8(char *moby) {
    char *obj = moby;
    char *vars = *(char **)(obj + 0x68);
    Quad_L26_0040C8A8 params;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        qzero_nc(&params);
        if (*(int *)(vars + 0x120) != 0)
            params.b = (float)*(int *)(vars + 0x120) * 1.7f;
        InitMovementControllerParams(obj, vars + 0x60, (char *)&params, 0, 0, 0, 0, 0, 0, 0, 0);
        if (*(int *)(vars + 0x120) != 0) {
            *(int *)(vars + 0xD0) = 0;
            *(int *)(vars + 0x100) = 0;
            *(int *)(vars + 0xD4) = 0;
        }
        SetMobyState(obj, 1, -1);
        break;
    case 1:
        UpdateObjectSway(obj, vars + 0x60, 0);
        break;
    }
}
