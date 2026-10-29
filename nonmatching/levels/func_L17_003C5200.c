/* Bounded near miss, 2026-10-28: 692/692 bytes with the default profile.
 * Five forms restore retail0x160 frame and its two FPR roles by giving the
 * real travelled distance its lifetime after the direction setup. The
 * clamped localamount defaults to0.3 and is replaced by remaining distance,
 * avoiding an artificial persistent third FPR. All later ribbon math aligns.
 * Remaining first+0x94 is packet-store ordering and a qzero address coalesced
 * with the following rotated-step address. Keep the default memory-clobber
 * qzero: its followingZ store is a real dependency, so NC is inappropriate.
 * Ordinary TI copy preserves the real displaced input16-byte copy. The
 * supported zero-TI barrier profile does not select this displaced zero;
 * -fno-regmove ties. Neither control is retained. Reopen on a genuine step
 * pointer lifetime witness or supported matching displaced-zero method.
 * Full packet144 and sevenvector16 locals are initialized before any render.
 * The original-frame origin slot is written by its real helper even though
 * subsequent ribbon geometry uses the rotated step slot, as retail records.
 */
#include "common.h"

typedef int QuadWord __attribute__((mode(TI)));

struct RibbonStyle { int flags[5]; unsigned char unknown14[0x24]; unsigned int color; };
extern struct RibbonStyle D_L17_001B02D8[];
extern struct RibbonStyle D_L17_001B02D8_gp[] SDATA(D_L17_001B02D8);
extern float D_L17_001B0290 SDATA(D_L17_001B0290);
extern unsigned char *D_L17_001B2C1C __attribute__((sda));
extern unsigned char D_L17_001B9BC0[];
struct RibbonPacket { float vertex[4][4]; unsigned int color[4]; float uv[8]; u64 state[4]; };
struct RibbonFrame {
    struct RibbonPacket packet;
    float previous[4], current[4], step[4], direction[4], camera[4], width[4], origin[4];
};
extern unsigned long func_0027C878(int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
#define STYLE (D_L17_001B02D8_gp[0])

/* Full144-byte packet and seven16-byte vectors. Every rendered vertex,
 * UV, color and state byte is initialized before its first consumption. */
void func_L17_003C5200(unsigned char *object)
{
    struct RibbonFrame f;
    unsigned char *data = *(unsigned char **)(object + 0x68);
    unsigned long texture = func_0027C878(15), flags;
    unsigned char *target;
    float length, travelled;
    flags = (u64)STYLE.flags[0];
    flags |= (u64)STYLE.flags[1] << 2;
    flags |= (u64)STYLE.flags[2] << 4;
    flags |= (u64)STYLE.flags[3] << 6;
    flags |= (u64)STYLE.flags[4] << 32;
    f.packet.state[2] = 0xFF9000000260UL;
    f.packet.state[0] = 5;
    f.packet.state[3] = flags;
    f.packet.color[3] = STYLE.color;
    f.packet.color[2] = STYLE.color;
    f.packet.color[1] = STYLE.color;
    f.packet.color[0] = STYLE.color;
    f.packet.uv[2] = 1.0f;
    f.packet.uv[5] = 1.0f;
    f.packet.uv[6] = 1.0f;
    f.packet.uv[7] = 1.0f;
    f.packet.state[1] = texture;
    f.packet.uv[0] = 0.0f;
    f.packet.uv[1] = 0.0f;
    f.packet.uv[3] = 0.0f;
    f.packet.uv[4] = 0.0f;
    qzero(f.step);
    f.step[2] = D_L17_001B0290;
    {
    float *rotated = f.step;
    func_00283098(rotated, rotated, object + 0xc0);
    func_00282CD8(f.origin, rotated, object + 0x10);
    target = (*(int *)(data + 0x10) << 8) + D_L17_001B2C1C;
    *(QuadWord *)f.previous = *(QuadWord *)(target + 0x10);
    qcopy(f.current, f.previous);
    func_00282CF0(f.direction, rotated, f.previous);
    }
    travelled = 0.0f;
    length = func_00282DF0(f.direction);
    qcopy(f.packet.vertex[0], f.previous);
    qcopy(f.packet.vertex[2], f.previous);
    while (travelled < length) {
        float remaining = length - travelled;
        float amount = 0.3f;
        if (remaining < amount) amount = remaining;
        travelled += amount;
        func_00282F20(f.direction, f.direction, amount);
        func_00282CC0(f.current, f.current, f.direction);
        qcopy(f.packet.vertex[1], f.current);
        qcopy(f.packet.vertex[3], f.current);
        func_00282CF0(f.camera, D_L17_001B9BC0, f.current);
        func_00282DD8(f.width, f.camera, f.direction);
        func_00282F20(f.width, f.width, 0.1f);
        func_00282CC0(f.packet.vertex[1], f.packet.vertex[1], f.width);
        func_00282CF0(f.packet.vertex[3], f.packet.vertex[3], f.width);
        func_00280B90(&f.packet, 0, 1);
        qcopy(f.previous, f.current);
        qcopy(f.packet.vertex[0], f.packet.vertex[1]);
        qcopy(f.packet.vertex[2], f.packet.vertex[3]);
    }
}
