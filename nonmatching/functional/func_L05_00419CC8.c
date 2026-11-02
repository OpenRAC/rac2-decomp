/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_L05_00419CC8 - retained near miss (Claude Opus 5.5, opus-1, task v1564).
 * Profile: -O2 -G8 -ffunction-sections -frac2-zero-ti-por -g in a unit of its own
 * (e.g. src/levels/shared/L05_00419CC8-g8.c with that cflags line).
 * check.py: 576/580 bytes, 0/4 places (US v1.01). Without nops, the instruction
 * stream equals retail's except relocation values; both fade-division nops come
 * from -g line labels. One nop is missing: retail has
 *   lwc1 $f12,0x2048($gp); nop; div.s $f12,$f12,$f20
 * with a -g line label right before the lwc1 (the label floor of
 * pad_div_erratum_nops.py asks for one nop). cc1 emits `l.s $f12,D_L05_001B1038`;
 * gas builds the $gp form plus a relaxation frag_var, so the label is in the
 * previous frag and rac2_div_code_distance falls back to the saturated count
 * (gp insn + the variant's lui/lwc1 = 2): no nop. A hand-assembled control shows
 * `label; l.s $f12,8($gp); div.s` gets the nop while `label; l.s $f12,SYM; div.s`
 * (SYM .extern 4) does not. Splitting the load and the division into two
 * statements gives two nops (584 bytes). Unblock: count a relaxed $gp load as one
 * slot in the assembler's label distance (toolchain change), then recheck.
 * The function pointer is func_L05_0041A228 (its catalogue places 05:0041A230,
 * 10:0041C058, 15:00423208, 25:00412230 equal the lui/addiu values).
 */

#include "common.h"

extern char *func_0029EFD0(int);
extern int func_00283CF0(float);
extern float func_002A7940(void);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L05_0041A228(char *);
extern float D_L05_001B1030 __attribute__((sda));
extern float D_L05_001B1034 __attribute__((sda));
extern float D_L05_001B1038 __attribute__((sda));
extern float D_L05_001B1054 __attribute__((sda));
extern float D_L05_001B1058 __attribute__((sda));
typedef int EffectVector __attribute__((mode(TI)));

char *func_L05_00419CC8(char *owner, void *pos, void *dir, int color1, int color2, int orient, int kind, int value, float scale)
{
    char *obj = func_0029EFD0(0xFFA);
    float up[4];
    char *st;
    float speed;
    *(EffectVector *)up = 0;
    up[2] = 1.0f;
    if (obj) {
        float initial = D_L05_001B1030;
        int life;
        float start, end;
        st = *(char **)(obj + 0x68);
        *(int *)(st+0x30) = kind;
        speed = initial * (1.0f / 60.0f);
        if (kind) speed = D_L05_001B1034 * (1.0f / 60.0f);
        obj[0x20] = 0;
        *(unsigned char *)(obj+0x30) = 0xFF;
        life = func_00283CF0(D_L05_001B1038 / speed);
        end = D_L05_001B1058;
        start = D_L05_001B1054;
        *(char **)(st+4) = owner;
        *(int *)st = life;
        *(float *)(st+0x3c) = start;
        *(float *)(st+0x40) = (end-start)/(float)life;
        *(float *)(st+8) = func_002A7940();
        *(float *)(st+0xc) = scale;
        *(int *)(st+0x38) = value;
        if (*(int *)(st+0x30)) {
            *(int *)(st+0x20)=0x00FF2020;
            *(int *)(st+0x24)=0x7FEF2020;
            *(int *)(st+0x34)=0;
        } else {
            *(int *)(st+0x20)=color1;
            *(int *)(st+0x24)=color2 | 0x7F000000;
        }
        if (!orient) {
            qcopy(obj+0xc0,owner+0xc0);
            qcopy(obj+0xd0,owner+0xd0);
            qcopy(obj+0xe0,owner+0xe0);
            func_00282F20(st+0x10,dir,speed);
        } else {
            func_00282F20(obj+0xc0,dir,1.0f);
            func_00282DD8(obj+0xd0,obj+0xc0,up);
            func_00282F20(obj+0xd0,obj+0xd0,1.0f);
            func_00282DD8(obj+0xe0,obj+0xd0,obj+0xc0);
            qcopy(st+0x10,dir);
        }
        qcopy(obj+0x10,pos);
        func_L00_002E6EF8(func_L05_0041A228,obj);
    }
    return obj;
}
