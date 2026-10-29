/* Retained meaningful draft, 2026-10-28: 716/756 bytes, one C trial.
 * CONTRACT BLOCKER: retailbankS3 is defined only after typeflagsbit8 succeeds
 * (+0x88 delay); the false edge bypasses all definitions yet can syntactically
 * reach bank*0x770 after independent object gates. Keep a defined localbank0
 * in this provisional draft rather than inventing an uninitialized value for
 * allocation. This default is not claimed equivalent outside a proven valid
 * type/object domain. Reopen after the runtime type-table/object invariant is
 * independently established. Initial boot table bytes for known caller kinds
 * are zero and writable core.lit, so that snapshot alone is not such proof.
 * The actual return isint0onallocation/1onrejection; many old callers declare
 * void, which must be audited by lead before any candidate qualification.
 * Full224-byte class rows,119*16-byte settings bank stride0x770,30*32 pool,
 * real threeint12-byte color outputs and opaque32-bit tag are retained.
 * Canonical AB1F0 integer stored-address return is explicitly cast, not
 * redeclaredpointer. Color getterwrites allthree outputs on fallback path.
 */
#include "common.h"

struct EffectClass {
    int active; unsigned char kind, unknown05[0x47];
    short redirect; unsigned char unknown4e[0x92];
};
struct EffectSetting { float rate; int seconds; unsigned int unknown08[2]; };
struct EffectSlot {
    int remaining; unsigned int color, flags; int elapsed;
    float rate; unsigned char *object; unsigned int tag; int active;
};
extern struct EffectClass D_00239BA0[];
extern unsigned char D_00139568[], D_001A7A80[];
extern struct EffectSetting D_00236510[][119];
extern struct EffectSlot D_00236150[];
extern int func_002AB1F0(unsigned char *);
extern int func_0032D700(void *);
extern void func_002A04B8(unsigned char *, int *, int *, int *);

/* Complete224-byte class rows,16-byte settings and thirty32-byte output
 * records. The third argument is an opaque32-bit stored tag, used by current
 * callers both for integer fields and stored object addresses. */
int func_0032D758(unsigned char *object, int kind, unsigned int tag)
{
    int original = kind, bank = 0, result = 1, i;
    int r, g, b;
    unsigned char *definition;
    struct EffectClass *entry;
    if (D_00239BA0[kind].redirect) kind = D_00239BA0[kind].redirect;
    if (D_001A7A80[kind] & 8) {
        int accepts = 0;
        entry = &D_00239BA0[D_00139568[kind]];
        if (entry->active) {
            if (entry->kind == 2) accepts = 1;
            else if (entry->kind == 1) {
                int selected = 0;
                switch (kind) {
                case 12: case 14: case 17: case 18: case 53: selected = 1; break;
                }
                if (selected) accepts = 1;
                else accepts = 0;
            }
        }
        if (accepts) bank = 1;
        else {
            entry = &D_00239BA0[D_00139568[kind]];
            if (entry->active && entry->kind == 3) bank = 1;
        }
    }
    if (*(short *)(*(unsigned char **)(object + 0x24) + 0x46) != 5) return 1;
    if (!(*(unsigned short *)(object + 0x34) & 0x1000)) return 1;
    if (*(signed char *)(object + 0x20) < 0) return 1;
    if (!*(void **)(object + 0x98)) return 1;
    definition = (unsigned char *)func_002AB1F0(object);
    if (!definition || *(float *)definition <= 0.0f) return 1;
    if (func_0032D700(object) != -1) return 1;
    for (i = 0; i < 30; ++i) {
        struct EffectSlot *slot = &D_00236150[i];
        if (!slot->object) {
            int supplied = 0;
            slot->object = object;
            slot->remaining = D_00236510[bank][original].seconds * 60;
            slot->rate = D_00236510[bank][original].rate * 0.01666667f;
            if (*(unsigned short *)(object + 0x34) & 0x20) {
                unsigned char *class_data = *(unsigned char **)(*(unsigned char **)(object + 0x68) + 0x10);
                if (class_data && *(short *)class_data) {
                    r = class_data[4];
                    g = class_data[5];
                    b = class_data[6];
                    supplied = 1;
                }
            }
            if (!supplied) func_002A04B8(slot->object, &r, &g, &b);
            slot->active = 1;
            slot->flags = 0x8000;
            slot->tag = tag;
            slot->color = ((unsigned int)b << 16) + ((unsigned int)g << 8) + (unsigned int)r;
            result = 0;
            slot->elapsed = 0;
            break;
        }
    }
    return result;
}
