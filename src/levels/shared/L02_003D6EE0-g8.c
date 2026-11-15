#include "common.h"
extern void func_002833F0(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00283678(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00283738(void *, void *, void *);
extern int D_L02_001A9018 MACRO_ADDR;
extern unsigned short **D_L02_001A9014 MACRO_ADDR;
extern char *D_L02_001B3C1C[] __attribute__((sda));
/* Looks through the nearby records for one very close to the object and, if found, remembers it and its position relative to the object. */
void func_L02_003D6EE0(char *object)
{
    struct {
        float inverse[12];
        float rotation[12];
        float transposed[16];
    } frame __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    int index;
    unsigned short *entry;
    unsigned short *list;
    euler_rotation_basis(frame.rotation, object + 0xf0);
    matrix_from_basis_rows(frame.transposed, frame.rotation);
    copy_matrix3x4(frame.inverse, frame.transposed);
    index = *(int *)(state + 0xb0);
    if (index != -1 && index < D_L02_001A9018) {
        list = D_L02_001A9014[index];
        if (list) {
            entry = list;
            do {
                int key = *entry & 0x7fff;
                char *record = D_L02_001B3C1C[0] + key * 64;
                if (fast_vec_dist(object + 0x10, record + 0x30) < 1.0f) {
                    *(short *)(state + 0x78) = key;
                    state[0x7c] = 1;
                    state[0x7a] = 1;
                    *(int *)(state + 0x70) = 0;
                    FastVecSub(state + 0x60, record + 0x30, object + 0x10);
                    matrix_mul_vec3(state + 0x60, state + 0x60, frame.inverse);
                    multiply_matrix3x3(state + 0x30, frame.inverse, record);
                    break;
                }
            } while (*(short *)entry++ >= 0);
        }
    }
}
