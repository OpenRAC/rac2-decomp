/* Retained route selection, 2026-10-28: 620/620 bytes, 0/2 US.
 * Four bounded trials. Reusing the first scan index for the final half-count
 * and an explicit entry guard improves the allocation toward retail, but the
 * compiler hoists object+0x10 into a saved pointer (retail rebuilds per call).
 * Converting the second scan to a guarded do-loop gives648B; rejected.
 * Narrow -fno-rerun-loop-opt ties620 with the same allocation gap; no flag needed.
 * Full helper0040F8F0 disassembly proves its float return F0, saved to result;
 * local delta is16B and vector input reads are bounded to one complete point.
 * Settings minimum1BC: primary route at1A8 and exactly4 links at1AC..1B8.
 * Route is a variable-sized16B header +count*16; no invented one-element bound.
 */
#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float func_L04_0040F8F0(u8 *, u8 *, int, int, int, int);
extern u8 *D_L04_001FE340[];

/* Routes have a 16-byte header followed by count complete 16-byte points.
 * The scans stop before the terminal point; settings hold four link indices.
 * Only the caller-owned output words are initialized, as in retail. */
void func_L04_00410518(u8 *object, u8 *settings, int *link, int *point, float *result, int mode)
{
    float delta[4] __attribute__((aligned(16)));
    float best = 9999.0f, distance;
    int old_point = *point, old_link = *link;
    int i, j;
    u8 *route, *cursor;
    int *links;
    *link = -1;
    *point = 0;
    *result = 0.0f;
    route = D_L04_001FE340[*(int *)(settings + 0x1A8)];
    i = 0;
    if (*(int *)route - 1 > 0) {
        cursor = route + 0x10;
        do {
        func_00282CF0(delta, object + 0x10, cursor);
        distance = func_L00_002EE290(delta);
        if (distance < best) {
            *point = i;
            best = distance;
        }
        cursor += 0x10;
        } while (++i < *(int *)route - 1);
    }
    links = (int *)(settings + 0x1AC);
    for (i = 0; i < 4; i++) {
        if (links[i] != -1) {
            route = D_L04_001FE340[links[i]];
            cursor = route + 0x10;
            for (j = 0; j < *(int *)route - 1; j++) {
                func_00282CF0(delta, object + 0x10, cursor);
                distance = func_L00_002EE290(delta);
                if (distance < best) {
                    *point = j;
                    best = distance;
                    *link = i;
                }
                cursor += 0x10;
            }
        }
    }
    route = D_L04_001FE340[*(int *)(settings + 0x1A8)];
    i = (int)((float)*(int *)route * 0.5f);
    if (old_link == -1 && old_point == 0 && *link == old_link && i < *point)
        *point = 0;
    *result = func_L04_0040F8F0(object, settings, *link, *point, mode, *(s16 *)(object + 0xAA) == 0xBBC);
}
