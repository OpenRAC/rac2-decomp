#include "common.h"
extern unsigned short *g_spawn_list_table[];
extern char *g_feltzin_target_mobys;
extern char *g_feltzin_enemy_table;
extern char *ref_L05_0037CEE0_0 __attribute__((sda));
extern char *ref_L05_0037CEE0_1 __attribute__((sda));
struct CountListCE {
    char pad[0x90];
    int count;
    int pad94, pad98;
    int list[1];
};
extern struct CountListCE g_feltzin_challenge_state;
extern float func_332C18(void);
extern void func_33B330(void *, float, float, float);
extern void func_306630(void *, void *, void *);
extern void func_306660(void *, void *, void *);
extern void func_306AD8(void *, void *, void *);
extern void func_3068F8(void *, void *, float);
extern int func_338168(void *, int);
/* Moves the object's cached pieces by a random nudge and pushes them away from any list
   entries they touch. */
void func_L05_0037CEE0(char *obj, void *matrix, float scale)
{
    float a[4], b[4], c[4];
    int off, i, j;
    unsigned short *p;
    float x, y;
    char *table;
    short t;
    if (!g_spawn_list_table[*(unsigned char *)(obj + 0x21)])
        return;
    p = g_spawn_list_table[*(unsigned char *)(obj + 0x21)];
    do {
        off = *p & 0x7fff;
        x = func_332C18();
        y = func_332C18();
        func_33B330(a, scale, x, y);
        func_306630(g_feltzin_target_mobys + off * 256 + 0x10, a, matrix);
        for (i = 0; i < g_feltzin_challenge_state.count; i++) {
            if (func_338168(g_feltzin_target_mobys + off * 256 + 0x10, g_feltzin_challenge_state.list[i])) {
                table = g_feltzin_enemy_table + g_feltzin_challenge_state.list[i] * 128;
                func_306660(b, ref_L05_0037CEE0_0 + off * 256 + 0x10, table + 0x30);
                b[3] = 0;
                func_306AD8(c, b, table + 0x40);
                func_3068F8(c, c, 1.05f);
                func_306AD8(c, c, table);
                func_306630(g_feltzin_target_mobys + off * 256 + 0x10, c, table + 0x30);
                for (j = 0; j < g_feltzin_challenge_state.count; j++)
                    if (func_338168(g_feltzin_target_mobys + off * 256 + 0x10, g_feltzin_challenge_state.list[j]))
                        qcopy(obj + 0x10, ref_L05_0037CEE0_1 + g_feltzin_challenge_state.list[j] * 128 + 0x30);
            }
        }
        t = *(short *)p;
        p++;
    } while (t >= 0);
}
