#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    float vertices[4][4];
    u8 attributes[0x50];
} L16DrawPacket;
extern int D_L16_001B2648 MACRO_ADDR;
extern u16 *D_L16_001FB660[];
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern int D_L16_001B2B38 __attribute__((sda));
extern int D_L16_001B02D8 __attribute__((sda));
extern int D_L16_001B0308 __attribute__((sda));
extern float D_L16_001B02E8[8] __attribute__((sda));
extern float D_L16_001B0320[16] __attribute__((sda));
extern float D_L16_001B0360[16] __attribute__((sda));
extern int D_L16_001B02DC[] __attribute__((sda));
extern int D_L16_001B0310[] __attribute__((sda));
extern int D_L16_001B030C[] __attribute__((sda));
extern int D_L16_001B0314[] __attribute__((sda));
extern float func_00283CE0(int);
extern void func_00283410(void *, void *);
extern void func_00283658(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern void func_00283788(void *, void *, void *);
extern void func_L03_002EFB60(void *, void *, float);
extern void func_L02_002EF968(void *, int, int, void *, void *, int);
extern void func_00282C88(Quad *);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00280B90(void *, void *, int);

/* Draws alternating rotated packet pairs for the visible members of the object group. */
void func_PAL_L16_003C70F0(u8 *object)
{
    float matrices[32][16], rotation[16], localRotation[12], sphere[4];
    L16DrawPacket packets[2];
    float angles[4], projected[4], combined[12];
    u16 *list;
    u8 *other;
    float phase;
    int count = 0, pass, pair, i, j, k;
    *(Quad *)sphere = 0;
    sphere[0] = 30.0f;
    sphere[3] = 1.0f;
    *(Quad *)projected = 0;
    phase = func_00283CE0(D_L16_001B2648 % 1000) * 0.00083333335f;
    projected[2] = (phase + phase) * 3.1415927f - 3.1415927f;
    *(Quad *)angles = *(Quad *)projected;
    func_00283410(rotation, angles);
    list = D_L16_001FB660[object[0x21]];
    while (object[0x21] != 255 && object[0x21] <= D_L16_001B2B38 && list &&
            ((list && (s16)list[-1] >= 0) || list == D_L16_001FB660[object[0x21]])) {
        other = D_L16_001B2B1C[0] + ((*list & 0x7FFF) << 8);
        if (!other)
            break;
        if (other[0x20] == 1) {
            float *matrix = matrices[count];
            func_00283658(matrix, other + 0xC0);
            qcopy(matrix + 12, other + 0x10);
            matrix[15] = 1.0f;
            func_002830C0(projected, sphere, matrix);
            projected[3] = 30.0f;
            if (func_00283DB8(projected, 512.0f) != -1) {
                func_00283788(matrix, matrix, rotation);
                {
                    float scale = *(float *)(other + 0x2C) / (*(float **)(other + 0x24))[9];
                    func_L03_002EFB60(matrix, matrix, scale);
                }
                qcopy(matrix + 12, other + 0x10);
                matrix[15] = 1.0f;
                count++;
            }
        }
        list++;
    }
    func_L02_002EF968(&packets[0], D_L16_001B02D8, D_L16_001B0308, D_L16_001B02E8, D_L16_001B0320, 1);
    func_L02_002EF968(&packets[1], D_L16_001B02DC[0], D_L16_001B0310[0], D_L16_001B02E8, D_L16_001B0360, 1);
    *(int *)(packets[0].attributes + 12) = D_L16_001B030C[0];
    *(int *)(packets[1].attributes + 12) = D_L16_001B0314[0];
    *(int *)(packets[0].attributes + 4) = D_L16_001B030C[0];
    *(int *)(packets[1].attributes + 4) = D_L16_001B0314[0];
    func_00282C88((Quad *)angles);
    angles[2] = 0.3926991f;
    func_002833F0(localRotation, angles);
    for (k = 0; k < 2; k++) {
        func_00283098(packets[k].vertices[2], packets[k].vertices[2], localRotation);
        func_00283098(packets[k].vertices[3], packets[k].vertices[3], localRotation);
    }
    func_00283738(combined, localRotation, localRotation);
    for (pass = 0; pass < 16; pass++) {
        pair = (pass & 1) ? 2 : 0;
        for (i = 0; i < 2; i++) {
            func_00283098(packets[i].vertices[pair], packets[i].vertices[pair], combined);
            func_00283098(packets[i].vertices[pair + 1], packets[i].vertices[pair + 1], combined);
            if (count > 0) {
                float (*matrix)[16] = matrices;
                j = count;
                do {
                    func_00280B90(&packets[i], matrix++, 1);
                } while (--j);
            }
        }
    }
}
