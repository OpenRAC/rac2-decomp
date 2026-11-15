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
extern float IntToFloat(int);
extern void euler_to_matrix(void *, void *);
extern void copy_matrix_rotation(void *, void *);
extern void transform_vector(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern void multiply_matrix(void *, void *, void *);
extern void func_L03_002EFB60(void *, void *, float);
extern void FillQuadPacket(void *, int, int, void *, void *, int);
extern void vec_clear_128(Quad *);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);

/* Draws alternating rotated packet pairs for the visible members of the object group. */
/* Draws alternating rotated packet pairs for the visible members of the object group. */
void DrawRotatingGroupInstances(u8 *object)
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
    phase = IntToFloat(D_L16_001B2648 % 1200) * 0.00083333335f;
    projected[2] = (phase + phase) * 3.1415927f - 3.1415927f;
    *(Quad *)angles = *(Quad *)projected;
    euler_to_matrix(rotation, angles);
    list = D_L16_001FB660[object[0x21]];
    while (object[0x21] != 255 && object[0x21] <= D_L16_001B2B38 && list &&
            ((list && (s16)list[-1] >= 0) || list == D_L16_001FB660[object[0x21]])) {
        other = D_L16_001B2B1C[0] + ((*list & 0x7FFF) << 8);
        if (!other)
            break;
        if (other[0x20] == 1) {
            float *matrix = matrices[count];
            copy_matrix_rotation(matrix, other + 0xC0);
            qcopy(matrix + 12, other + 0x10);
            matrix[15] = 1.0f;
            transform_vector(projected, sphere, matrix);
            projected[3] = 30.0f;
            if (math_fast_helper_a(projected, 512.0f) != -1) {
                multiply_matrix(matrix, matrix, rotation);
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
    FillQuadPacket(&packets[0], D_L16_001B02D8, D_L16_001B0308, D_L16_001B02E8, D_L16_001B0320, 1);
    FillQuadPacket(&packets[1], D_L16_001B02DC[0], D_L16_001B0310[0], D_L16_001B02E8, D_L16_001B0360, 1);
    *(int *)(packets[0].attributes + 12) = D_L16_001B030C[0];
    *(int *)(packets[1].attributes + 12) = D_L16_001B0314[0];
    *(int *)(packets[0].attributes + 4) = D_L16_001B030C[0];
    *(int *)(packets[1].attributes + 4) = D_L16_001B0314[0];
    vec_clear_128((Quad *)angles);
    angles[2] = 0.3926991f;
    euler_rotation_basis(localRotation, angles);
    for (k = 0; k < 2; k++) {
        matrix_mul_vec3(packets[k].vertices[2], packets[k].vertices[2], localRotation);
        matrix_mul_vec3(packets[k].vertices[3], packets[k].vertices[3], localRotation);
    }
    multiply_matrix3x3(combined, localRotation, localRotation);
    for (pass = 0; pass < 16; pass++) {
        pair = (pass & 1) ? 2 : 0;
        for (i = 0; i < 2; i++) {
            matrix_mul_vec3(packets[i].vertices[pair], packets[i].vertices[pair], combined);
            matrix_mul_vec3(packets[i].vertices[pair + 1], packets[i].vertices[pair + 1], combined);
            if (count > 0) {
                float (*matrix)[16] = matrices;
                j = count;
                do {
                    draw_world_quad(&packets[i], matrix++, 1);
                } while (--j);
            }
        }
    }
}
