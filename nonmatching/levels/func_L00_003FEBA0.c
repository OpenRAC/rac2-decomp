/* func_L00_003FEBA0 - 444 bytes.  Worker attempt, 27 October 2026 (draft below).

   428 B vs 444 (level 00): everything matches except (1) retail has a nop
   pair before div.s f12,f12,f1 and (2) retail uses bc1tl (branch-likely, ld
   s0 in slot) for the length==0 early return, mine bc1t; rest of the schedule
   shifts by 4 insns. -g and -frac2-hazard-labels flags tried: no effect on
   the nop pair. Spawns 6 particles (func_00334888) with random color; consts
   70000/150000, 1/60000, 1/150, 0.3, 1.01 are exact floats. */

/* new file src/levels/shared/L00_003FEBA0.c + cflags line (flags TBD, see notes); remove INCLUDE_ASM from L00_003F8E08.c. Callee names func_L00_* guessed from level-00 addresses; other levels not checked (may need ref_ names). */
extern float func_L00_002EE238(float *v);
extern void func_L00_002EE178(float *dst, float *src, float scale);
extern void func_L00_002EE108(float *dst, float *a, float *b);
extern int func_L00_0031A728(int);
extern float func_L00_0031A7C0(float, float);
extern int func_L00_0031A768(int, int);
extern void func_L00_0031A948(float *, float, float);
extern char *func_L00_00334888(float *, int, float *, int, float, float, float, float, int);

void func_L00_003FEBA0(int unused, float *pos, float *dir)
{
    float a[4];
    float b[4];
    float c[4];
    float length;
    float speed;
    int i;
    int shade;
    int color;
    char *particle;

    length = func_L00_002EE238(dir);
    if (length == 0.0f)
        return;
    func_L00_002EE178(b, dir, 1.0f / length * 0.5f);
    func_L00_002EE108(a, pos, b);
    for (i = 5; i >= 0; i--) {
        func_L00_0031A728(2);
        func_L00_0031A728(2);
        speed = func_L00_0031A7C0(70000.0f, 150000.0f);
        shade = func_L00_0031A768(10, 0x7F);
        func_L00_0031A948(c, 1.6666668e-05f, 0.0066666667f);
        color = shade | (shade << 16) | (shade << 8) | 0x7F000000;
        particle = func_L00_00334888(a, 0, c, color, 0.3f, 1.0f, 1.01f, speed, 1);
        if (particle != 0) {
            *(short *)(particle + 0xA) = 0x78;
            *(int *)(particle + 0x24) = 2;
            *(unsigned char *)(particle + 0x2A) = 0x7F;
            *(unsigned char *)(particle + 0x2B) = *(unsigned char *)(particle + 0xA);
        }
    }
}
