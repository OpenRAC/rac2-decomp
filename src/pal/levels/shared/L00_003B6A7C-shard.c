#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_3B3158;
typedef struct {
    char pad00[0x14];
    float life;
    float fade;
    char pad1C[0x26 - 0x1C];
    s16 timer;
    char pad28[0x34 - 0x28];
    s32 stuck;
} Shard_3B3158;
extern char D_00189E20[];
extern char D_L00_001BF220[];
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_L00_003B3090(void *, void *, void *);
extern int func_00282978(void *);
extern void func_0029F338(void *);
extern void func_002A9288(void *, float);

void func_PAL_L00_003B6A7C(char *obj)
{
    Shard_3B3158 *st;
    V4_3B3158 from, dir, at;
    char *game;

    st = *(Shard_3B3158 **)(obj + 0x68);
    dir.q = 0;
    dir.f[2] = 0.16000001f;
    qcopy(&from, obj + 0x10);
    func_002AF000(st, st->fade, *(float *)(obj + 0xF8), -*(float *)(obj + 0xF4));
    func_00282CC0(obj + 0x10, obj + 0x10, st);
    game = D_00189E20;
    if (func_002761F8(&from, obj + 0x10, 0, *(void **)(game + 0x2290), 0)
        || func_00277258(obj + 0x10, 1, *(void **)(game + 0x2290), 0.3f)) {
        qcopy(&at, D_L00_001BF220);
        func_00283028(&dir, st, D_L00_001BF220 + 0x20);
        func_00282F20(&dir, &dir, 0.040000003f);
        func_PAL_002AC718(obj, &dir, &at, 0.0f, 0.0f, 0, 0, 4, 0.0f, 0.0f, 9.0f, 0.4f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        func_L00_003B3090(obj, st, &at);
        func_0029F338(obj);
        return;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f
        || *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f
        || *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
        func_0029F338(obj);
        return;
    }
    if (st->stuck == 0 && (func_00282978(&st->timer) || st->life < 0.0f)) {
        func_PAL_002AC718(obj, &dir, 0, 0.0f, 0.0f, 0, 0, 4, 0.0f, 0.0f, 9.0f, 0.4f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        func_0029F338(obj);
        return;
    }
    {
        float fade = st->fade;
        st->life -= fade;
    }
    func_002A9288(obj, 0.2f);
}
