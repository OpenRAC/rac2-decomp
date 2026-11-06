/* 6 November 2026, Codex follow-up: 190 valid source variants, no improvement
 * over the retained 868-byte / 3-position / USA 0-of-27 result. Fifteen genuine
 * multi-field position/camera/UV/color layout combinations tie exactly. A
 * dependency-checked 56-check hill-climb extending the previous store-only
 * search to the color packing and first atan's two delta operands also ties.
 * Fifty-two packing-to-store one-pass groups yield at least 68 differing
 * positions; grouping the second tint update/broadcast as well gives at least
 * 75, rather than restoring the changed allocation. Fifteen two-component UV
 * aggregate-assignment combinations grow to 884-932 bytes. No candidate uses
 * volatile, inline asm, dummy operations or one-field allocation wrappers.
 * Final check.py --diff reproduces only +0x108/+0x10c/+0x110; original C and
 * source marker restored. No alternate-release check or linked build run.
 */
/* 6 November 2026, round 9: sched1 trace (-fsched-verbose-5): all stores have priority 77, the colour ops 78+; the 18 load/colour/address insns fill both issue slots from the rand call to t=31, so no store issues before the color[0] store is ready at t=32, where its REG_DEAD weight -1 wins; sched2 then keeps that order (equal priority and depend count, luid). 120-step hill-climb over the 13 uv/color/rotation[3] stores: no better than 3 positions. Hoisting the camera pointer to the top frees a slot (zeros follow color[0] directly) but sched2 moves its lui before the calls (55 rows); a target float pointer is 864 bytes; four colour-packing forms give 3-21 rows. Reopen only on a form that delays color[0]'s readiness by two issue slots or gives the zero stores a real later dependent. */
/* 6 November 2026, lead: the 2 real rows are sched1's register-weight tie-break: the store where `color` dies is issued first (writing color[1] last moves 0x44 first instead; color[0] last moves 0x40 first). Retail issues the uv[0] zero stores first, i.e. in retail `color` is still live after these stores or the zero stores outrank them; nothing in the current body keeps color live (it is reassigned before the second draw). */
/* 6 November 2026: retained near miss, not linked or counted.
 * USA v1.01: 868/868 bytes, 0/27 places, first mismatch +0x108.
 * Reproduction unit: src/levels/shared/L00_002EC608-glow.c, default
 * -O2 -G0 -ffunction-sections. Three instruction positions remain:
 * +0x108/+0x10c/+0x110 emit color[0], uv[0][0], uv[0][1]; retail emits
 * uv[0][0], uv[0][1], color[0]. All other non-relocation instructions agree.
 * Rotate the initial vertex stores and color broadcasts as below to account
 * for sched1 selecting the last use first. Updating tint at the second random
 * alpha fixes its s3/matrix-s4 roles. A separate final white color fixes the
 * first/final color registers and packing. Put the last two zero UV stores
 * after colors.
 * New negative results: integer-bit union UV zeros and an inline color-broadcast
 * helper tie at three; reading the first color for the other colors changes
 * which store moves early; one-pass groups around the real zero stores or first
 * color store disrupt scheduling/allocation; measured volatile UV/color views
 * worsen the result; a real descending broadcast loop with -funroll-loops is
 * 912 bytes. No flags from these trials are retained. Private sched1/sched2
 * dumps locate the early color store in sched1, before the UV stores.
 * Reopen on a real lifetime/dependency that puts the two zero UV stores first.
 * No alternate-release checks or linked builds were run for this attempt.
 */
/* Historical reconstruction notes below; the current source fixes the
 * saved-register and packing differences described there.
 */
/* Nonmatching reconstruction, 2 November 2026. Replaces the old opcode screen.
 * Default -O2 -G0 -ffunction-sections: 868/868 bytes, 0/27 USA places,
 * first mismatch +0x1C. The real 0x130 frame and complete call sequence agree;
 * tint/matrix saved-register assignment, initial vertex/UV store scheduling,
 * colour packing and first atan argument register choices remain different.
 * Five bounded checks: retail-ordered versus per-vertex initializers, chained
 * colour packing, incomplete camera array and -G8. G8 ties the default;
 * the natural vertex grouping changes the early FP/store order. No flags kept.
 * Matrix storage is three basis vectors plus its real position vector;
 * rotation and offset are real 16-byte helper buffers, with rotation W zero.
 * Reopen on a source/allocator explanation for tint versus matrix lifetimes.
 * No alternate-release or linked build was run for these failed candidates.
 */
#include "common.h"

typedef struct {
    float point[4][4];
    u32 color[4];
    float uv[4][2];
    u64 state[4];
} GlowQuad;
typedef struct { float basis[3][4], position[4]; } GlowTransform;
typedef struct { char pad[0x140]; float position[4]; } GlowCamera;
extern GlowCamera D_L00_001B8C80[];
extern void func_00281DE8(void *, int, int, int);
extern int func_002A7820(int, int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern void func_00283410(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

void func_L00_002EC608(float *position, int tint)
{
    GlowQuad quad;
    GlowTransform transform;
    float rotation[4];
    float offset[4];
    u32 color, white;
    float scale;

    quad.point[0][2] = -2.0f;
    quad.point[1][2] = 2.0f;
    quad.point[2][2] = -2.0f;
    quad.point[3][2] = 2.0f;
    quad.point[0][1] = -2.0f;
    quad.point[2][1] = 2.0f;
    quad.point[1][1] = -2.0f;
    quad.point[3][1] = 2.0f;
    quad.point[0][3] = 1.0f;
    quad.point[1][3] = 1.0f;
    quad.point[2][3] = 1.0f;
    quad.point[3][3] = 1.0f;
    quad.point[0][0] = 0;
    quad.point[1][0] = 0;
    quad.point[2][0] = 0;
    quad.point[3][0] = 0;
    func_00281DE8(&quad, 44, 1, 128);
    color = (u32)func_002A7820(48, 64) << 24;
    color |= (u32)(tint >> 17) << 16;
    color |= (tint >> 9) & 0xFF00;
    color |= (tint >> 1) & 0xFF;
    quad.uv[1][1] = 1; quad.uv[2][0] = 1;
    quad.uv[3][0] = 1; quad.uv[3][1] = 1;
    quad.uv[0][0] = 0; quad.uv[0][1] = 0;
    quad.color[3] = color; quad.color[2] = color;
    quad.color[1] = color; quad.color[0] = color;
    quad.uv[1][0] = 0; quad.uv[2][1] = 0;
    rotation[3] = 0;
    rotation[2] = func_00283248(D_L00_001B8C80[0].position[0] - position[0],
                               D_L00_001B8C80[0].position[1] - position[1]);
    rotation[1] = -func_00283248(func_00282E80(position, D_L00_001B8C80[0].position),
                                D_L00_001B8C80[0].position[2] - position[2]);
    rotation[0] = func_002A7940();
    func_00283410(&transform, rotation);
    func_00282CF0(offset, D_L00_001B8C80[0].position, position);
    func_00282F20(offset, offset, 0.25f);
    transform.position[0] = position[0] + offset[0];
    transform.position[1] = position[1] + offset[1];
    transform.position[2] = position[2] + offset[2];
    transform.position[3] = 1.0f;
    scale = func_002A7878(0.3f, 0.4f);
    func_00282D30(quad.point[0], quad.point[0], scale);
    func_00282D30(quad.point[1], quad.point[1], scale);
    func_00282D30(quad.point[2], quad.point[2], scale);
    func_00282D30(quad.point[3], quad.point[3], scale);
    func_00280B90(&quad, &transform, 0);
    func_00282D30(quad.point[0], quad.point[0], 0.5f);
    func_00282D30(quad.point[1], quad.point[1], 0.5f);
    func_00282D30(quad.point[2], quad.point[2], 0.5f);
    func_00282D30(quad.point[3], quad.point[3], 0.5f);
    tint += (u32)func_002A7820(64, 127) << 24;
    color = tint;
    quad.color[3] = color; quad.color[2] = color;
    quad.color[1] = color; quad.color[0] = color;
    func_00280B90(&quad, &transform, 0);
    func_00282D30(quad.point[0], quad.point[0], 0.5f);
    func_00282D30(quad.point[1], quad.point[1], 0.5f);
    func_00282D30(quad.point[2], quad.point[2], 0.5f);
    func_00282D30(quad.point[3], quad.point[3], 0.5f);
    white = ((u32)func_002A7820(64, 127) << 24) + 0x7F7F7F;
    quad.color[3] = white; quad.color[2] = white;
    quad.color[1] = white; quad.color[0] = white;
    func_00280B90(&quad, &transform, 0);
}
