/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1292/1232 bytes; ring traversal, links and centroid loop allocation differ.
 * Reopen with measured forward pointer streams and connected-group lifetime evidence, not a flag matrix.
 * ABI/bounds: Incoming a0 is unused. The real hero position is sampled. A preceding-node backing symbol covers byte-cursor zero; joined-list storage is 32 bytes and the separate previous-position vector is 16 bytes.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"

typedef struct { float xyz[3]; int used; int particle; u8 links[8]; } TrailNode;
extern TrailNode D_L00_0023BB78[];
/* Includes the preceding sample accessed when the byte cursor wraps to zero. */
extern TrailNode D_L00_0023BB5C[];
extern u8 D_L00_0023BA78[];
extern u8 D_L00_001AF810 __attribute__((sda));
extern u8 D_L00_001AF811 __attribute__((sda));
extern u8 D_L00_001AF818 __attribute__((sda));
extern float D_L00_001AF81C __attribute__((sda));
extern float D_L00_001AF820 __attribute__((sda));
extern int D_L00_001AF824 __attribute__((sda));
extern float D_L00_001AF828 __attribute__((sda));
extern unsigned char D_00189E20[];
extern int D_L00_001B19C8 NOT_SDA;
extern float func_00282E48(void *, void *);
extern void func_L00_003B0AB0(int);
extern void func_L00_003B0CE8(int);
extern int func_L00_003B0B20(int, int, void *);
extern void func_L00_003B14D0(float, float, float);

/* Inserts a hero-position sample into the circular trail, joins nearby samples,
 * and consumes connected groups when their chain exceeds the configured limit.
 * The incoming a0 is unused in retail; the sampled position is hero + 0x80. */
TrailNode *func_L00_003B0DA0(void *unused)
{
    u8 joined[32];
    float previous[4];
    TrailNode *node;
    u8 cursor, entry;
    int count = 0, i, j, k, already, n;
    float dx, dy, dz, distance, x, y, z, divisor;

    if (D_L00_001AF811 != D_L00_001AF810) {
        previous[0] = D_L00_0023BB5C[D_L00_001AF810].xyz[0];
        previous[1] = D_L00_0023BB5C[D_L00_001AF810].xyz[1];
        previous[2] = D_L00_0023BB5C[D_L00_001AF810].xyz[2];
        if (func_00282E48(D_00189E20 + 0x80, previous) < D_L00_001AF81C) return 0;
    }
    node = &D_L00_0023BB78[D_L00_001AF810];
    node->xyz[0] = *(float *)(D_00189E20 + 0x80);
    node->xyz[1] = *(float *)(D_00189E20 + 0x84);
    node->xyz[2] = *(float *)(D_00189E20 + 0x88);
    node->used = D_L00_001B19C8;
    for (i = 7; i >= 0; --i) node->links[i] = D_L00_001AF810;
    for (cursor = D_L00_001AF810 - 1; cursor != (u8)(D_L00_001AF811 - 1); --cursor) {
        if (!D_L00_0023BB78[cursor].used) continue;
        dx = node->xyz[0] - D_L00_0023BB78[cursor].xyz[0];
        dy = node->xyz[1] - D_L00_0023BB78[cursor].xyz[1];
        dz = node->xyz[2] - D_L00_0023BB78[cursor].xyz[2];
        distance = dx * dx + dy * dy + dz * dz;
        if (distance < D_L00_001AF828 * D_L00_001AF828) {
            for (entry = D_L00_001AF811; entry != D_L00_001AF810; ++entry) {
                if (entry == cursor) continue;
                for (j = 0; j < 8; ++j)
                    if (D_L00_0023BB78[entry].links[j] == cursor)
                        D_L00_0023BB78[entry].links[j] = D_L00_001AF810;
            }
            func_L00_003B0AB0(cursor);
            func_L00_003B0CE8(cursor);
        } else if (distance < D_L00_001AF820) {
            already = 0;
            for (i = 0; i < 8; ++i) {
                entry = D_L00_0023BB78[cursor].links[i];
                if (entry == cursor) continue;
                for (j = 7; j >= 0; --j)
                    if (D_L00_0023BB78[entry].links[j] == D_L00_001AF810) already = 1;
            }
            if (!already) {
                for (i = 0; i < 8; ++i) {
                    if (D_L00_0023BB78[cursor].links[i] == cursor) {
                        D_L00_0023BB78[cursor].links[i] = D_L00_001AF810;
                        joined[count++] = cursor;
                        break;
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
                x = y = z = 0.0f;
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
    return &D_L00_0023BB5C[D_L00_001AF810];
}
