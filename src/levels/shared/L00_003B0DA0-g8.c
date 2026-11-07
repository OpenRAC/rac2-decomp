#include "include_asm.h"
#include "common.h"

/* Small-data unit of func_L00_003B0DA0. Its flags (config/cflags.txt) are its own:
   -frac2-hazard-labels keeps the k loop's guard label on the padding before the first
   division, and -frac2-gcse-unsplit-edges lets PRE set the node table's %hi once, at the
   end of the entry block, so both later uses rematerialize it. */

extern unsigned char D_L00_001AF810 __attribute__((sda));
extern unsigned char D_L00_001AF811 __attribute__((sda));
extern int D_L00_001B19C8 MACRO_ADDR;
/* The hero record: its position at 0x80, the pad buttons word at 0x1230 and the hero moby at 0x2290. */
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x11A0];
    int buttons;
    char pad1234[0x105C];
    char *moby;
} HeroL00;
extern HeroL00 D_00189E20;
extern void func_L00_003B0CE8(int);
typedef struct { float xyz[3]; int used; int particle; u8 links[8]; } TrailNode;
extern TrailNode D_L00_0023BB78[];
extern u8 D_L00_0023BA78[];
extern u8 D_L00_001AF818 __attribute__((sda));
extern float D_L00_001AF81C __attribute__((sda));
extern float D_L00_001AF820 __attribute__((sda));
extern int D_L00_001AF824 __attribute__((sda));
extern float D_L00_001AF828 __attribute__((sda));
extern float func_00282E48(void *, void *);
extern void func_L00_003B0AB0(int);
extern int func_L00_003B0B20(unsigned char, unsigned char, unsigned char *);
extern void func_L00_003B14D0(float, float, float);
char *func_L00_003B0DA0(void *unused)
{
    u8 joined[32];
    float previous[4];
    TrailNode *node;
    u8 cursor;
    int count = 0;
    int i, j, k, n;
    float x, y, z, divisor;

    if (D_L00_001AF811 != D_L00_001AF810) {
        TrailNode *last = &D_L00_0023BB78[D_L00_001AF810 - 1];
        float gap;
        previous[0] = last->xyz[0];
        previous[1] = last->xyz[1];
        previous[2] = last->xyz[2];
        gap = func_00282E48(D_00189E20.position, previous);
        if (gap < D_L00_001AF81C) return 0;
    }
    node = &D_L00_0023BB78[D_L00_001AF810];
    node->used = D_L00_001B19C8;
    node->xyz[0] = D_00189E20.position[0];
    node->xyz[1] = D_00189E20.position[1];
    node->xyz[2] = D_00189E20.position[2];
    {
        int l;
        u8 *link = &node->links[7];
        for (l = 7; l >= 0; --l) *link-- = D_L00_001AF810;
    }
    for (cursor = D_L00_001AF810 - 1; cursor != (u8)(D_L00_001AF811 - 1); --cursor) {
        float dx, dy, dz, distance;
        u8 entry;
        int a, already;
        if (!D_L00_0023BB78[cursor].used) continue;
        dx = node->xyz[0] - D_L00_0023BB78[cursor].xyz[0];
        dy = node->xyz[1] - D_L00_0023BB78[cursor].xyz[1];
        dz = node->xyz[2] - D_L00_0023BB78[cursor].xyz[2];
        distance = dx * dx + dy * dy + dz * dz;
        if (distance < D_L00_001AF828 * D_L00_001AF828) {
            for (entry = D_L00_001AF811; entry != D_L00_001AF810; ++entry) {
                int b;
                if (entry == cursor) continue;
                for (b = 0; b < 8; ++b)
                    if (D_L00_0023BB78[entry].links[b] == cursor)
                        D_L00_0023BB78[entry].links[b] = D_L00_001AF810;
            }
            func_L00_003B0AB0(cursor);
            func_L00_003B0CE8(cursor);
        } else {
            float limit;
            /* cse1 ends its block at this group's loop-end note, so row's multiply below
               survives until cse2 makes it the copy of the loop-top product. */
            do { limit = D_L00_001AF820; } while (0);
            if (distance < limit) {
                int row = cursor * sizeof(TrailNode);
                already = 0;
                for (a = 0; a < 8; ++a) {
                    u8 linked = D_L00_0023BB78[0].links[a + row];
                    int b;
                    if (linked == cursor) continue;
                    for (b = 0; b < 8; ++b)
                        if (D_L00_0023BB78[linked].links[b] == D_L00_001AF810) already = 1;
                }
                if (!already) {
                    u8 *p = D_L00_0023BB78[cursor].links;
                    u8 head;
                    int free = 0;
                    head = D_L00_001AF810;
                    for (; free < 8; free++, p++) {
                        if (*p == cursor) {
                            *p = head;
                            joined[count++] = cursor;
                            break;
                        }
                    }
                }
            }
        }
    }
    if (++D_L00_001AF810 == D_L00_001AF811) func_L00_003B0CE8(D_L00_001AF811);
    for (i = 0; i < count; ++i) {
        for (j = i + 1; j < count; ++j) {
            n = func_L00_003B0B20(joined[j], joined[i], D_L00_0023BA78);
            D_L00_0023BA78[n++] = D_L00_001AF810 - 1;
            if (n > D_L00_001AF824) {
                D_L00_001AF818 = n;
                z = x = y = 0.0f;
                divisor = n;
                for (k = 0; k < n; ++k) {
                    func_L00_003B0AB0(D_L00_0023BA78[k]);
                    x += D_L00_0023BB78[D_L00_0023BA78[k]].xyz[0];
                    y += D_L00_0023BB78[D_L00_0023BA78[k]].xyz[1];
                    z += D_L00_0023BB78[D_L00_0023BA78[k]].xyz[2];
                    func_L00_003B0CE8(D_L00_0023BA78[k]);
                }
                func_L00_003B14D0(x / divisor, y / divisor, z / divisor);
            }
        }
    }
    return (char *)&D_L00_0023BB78[D_L00_001AF810 - 1];
}
