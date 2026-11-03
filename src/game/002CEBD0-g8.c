#include "common.h"
extern int D_001B23A0;
extern float D_001B23A4;
extern float D_001AB9E4 __attribute__((sda));
extern float D_001AB9E8 __attribute__((sda));
extern float D_001B23A8;
extern char *D_001A8CFC;
extern int D_00138180[];
extern int func_00336D50(void *, int);
extern int func_002A9588(int, int, int, int, int);
extern void func_00283388(void *);
extern void func_00282D30(void *, void *, float);
extern void func_0028FC48(int, int, int, int, u64, int);
extern void func_00300AA8(int, int, void *, float, float, float);
static __inline__ float menu_vector_offset(float value, float offset)
{
    if (D_001B23A0 == 1) value += offset;
    return value;
}

static __inline__ int menu_screen_y(float value, float offset)
{
    float y = value * D_001B23A4 + 0.5f;
    if (D_001B23A0 == 1) return (int)(y + offset);
    return (int)y;
}

void func_002CEBD0(void) {
    float vectors[16];
    int text, color, selected, y0, y1;
    text = func_00336D50(D_001A8CFC + 0x8710, 74);
    color = func_002A9588(0x60442D00, 0x55F0C070, 25, 0, 0);
    func_00283388(vectors);
    vectors[0] = 0.0f;
    vectors[2] = menu_vector_offset(D_001B23A8, 0.07f);
    vectors[8] = menu_vector_offset(D_001B23A8, 0.07f);
    vectors[10] = 0.0f;
    func_00282D30(vectors, vectors, *(float *)((char *)text + 12));
    func_00282D30(vectors+8, vectors+8, *(float *)((char *)text + 12));
    selected = D_00138180[0x1c0/4] & 0x1000 ? 0x80F0F0F0 : color;
    func_00300AA8(text, selected, vectors, 58.0f, (float)menu_screen_y(457.0f, D_001AB9E4), 0.0f);
    vectors[0] = 0.0f;
    vectors[2] = menu_vector_offset(-D_001B23A8, -0.07f);
    vectors[8] = menu_vector_offset(-D_001B23A8, -0.07f);
    vectors[10] = 0.0f;
    func_00282D30(vectors, vectors, *(float *)((char *)text + 12));
    func_00282D30(vectors+8, vectors+8, *(float *)((char *)text + 12));
    selected = D_00138180[0x1c0/4] & 0x4000 ? 0x80F0F0F0 : color;
    func_00300AA8(text, selected, vectors, 44.0f, (float)menu_screen_y(187.0f, D_001AB9E4), 0.0f);
    y0 = menu_screen_y(278.0f, D_001AB9E8);
    y1 = menu_screen_y(369.0f, D_001AB9E8);
    func_0028FC48(39, y0, 41, y1, 0x55F0C070, 0);
    y0 = menu_screen_y(278.0f, D_001AB9E8);
    y1 = menu_screen_y(369.0f, D_001AB9E8);
    func_0028FC48(63, y0, 65, y1, 0x55F0C070, 0);
    y0 = menu_screen_y(277.0f, D_001AB9E8);
    y1 = menu_screen_y(279.0f, D_001AB9E8);
    func_0028FC48(39, y0, 65, y1, 0x55F0C070, 0);
    y0 = menu_screen_y(368.0f, D_001AB9E8);
    y1 = menu_screen_y(370.0f, D_001AB9E8);
    func_0028FC48(39, y0, 65, y1, 0x55F0C070, 0);
}
