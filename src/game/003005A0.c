

#ifndef RAC2_T_OBJ_FD7EAF5BF
#define RAC2_T_OBJ_FD7EAF5BF
typedef struct {
    char pad0[170];
    short kind;
} OBJ_Fd7eaf5bf;
#endif

extern OBJ_Fd7eaf5bf *D_L00_001ADB2C __attribute__((sda));

/* Tells which of four related objects is current (0 to 3), or -1 if none. */
int func_003005A0(void)
{
    OBJ_Fd7eaf5bf *p = D_L00_001ADB2C;

    if (p) {
        switch (p->kind) {
        case 4569 /* moby class 4569 */: return 0;
        case 4570 /* moby class 4570 */: return 1;
        case 4571 /* moby class 4571 */: return 2;
        case 4572 /* moby class 4572 */: return 3;
        }
    }
    return -1;
}
