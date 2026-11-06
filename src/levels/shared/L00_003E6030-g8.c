#include "common.h"
typedef float RenderVec6030[4] __attribute__((aligned(16)));
typedef struct {
    RenderVec6030 vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long gs[4];
} Quad6030;
extern int D_L00_001B0620 __attribute__((sda));
extern int D_L00_001B0624 __attribute__((sda));
extern int D_L00_001B0628 __attribute__((sda));
extern int D_L00_001B062C __attribute__((sda));
extern int D_L00_001B0630 __attribute__((sda));
extern int D_L00_001B0634 __attribute__((sda));
extern int D_L00_001B0638 __attribute__((sda));
extern float D_L00_001B063C __attribute__((sda));
extern float D_L00_001B05D8 __attribute__((sda));
extern char *D_L00_001B2B50 __attribute__((sda));
extern int *D_L00_001B2B58 MACRO_ADDR;
extern short D_L00_0029A090[][4][2];
extern RenderVec6030 D_L00_00299830[];
extern float D_L00_0029A990[][2];
extern RenderVec6030 D_L00_001B8DC0;
extern unsigned long func_0027C878(int);
extern void func_00282C88(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_002A7798(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_L00_003E6778(char *, int, float, float, void *);
extern void func_00280B90(void *, int, int);
/* func_L00_003E6030 builds and submits the 143 quads listed in D_L00_0029A090: each corner is
   scaled, pushed along its own z by a ripple, moved to OBJECT and summed for the quad's centre. A
   quad whose normal has a positive dot product with (centre - D_L00_001B8DC0) keeps an effect in
   its table entry, placed at that centre, and is passed to func_00280B90.

   The locals are declared together at the top, the counter and the two pointers last: gcc numbers
   a pseudo at its declaration, and PRE's reaching registers take their stack slots in the order of
   the hash of the base register, so these declarations decide the order of the spill slots. */
void func_L00_003E6030(char *object)
{
    Quad6030 q;
    RenderVec6030 matrix[3];
    RenderVec6030 normal, center, saved_center, edge1, edge2;
    unsigned long tex_reg, alpha_a, alpha_b, alpha_c, alpha_d, alpha_fix, alpha, frame_reg;
    int tex_index, base_colour, colour, brightness;
    float scale_x, scale_y;
    int vertex_index, uv_index;
    float scroll, u, base_v, v;
    float length, height, clamped, amount, swell, ripple, lift;
    float px, py, pz;
    float facing;
    int i;
    char *self = object;
    int index = 0;
    char *data = *(char **)(object + 0x68);
    tex_index = D_L00_001B0634;
    tex_reg = func_0027C878(tex_index);
    q.gs[1] = tex_reg;
    alpha_a = D_L00_001B0620;
    alpha_b = D_L00_001B0624;
    alpha_c = D_L00_001B0628;
    alpha_d = D_L00_001B062C;
    alpha_fix = D_L00_001B0630;
    alpha = alpha_a | (alpha_b << 2);
    alpha |= alpha_c << 4;
    alpha |= alpha_d << 6;
    alpha |= alpha_fix << 32;
    q.gs[3] = alpha;
    frame_reg = 0xFF9000000260UL;
    q.gs[2] = frame_reg;
    q.gs[0] = 0;
    func_00282C88(matrix[0]);
    func_00282C88(matrix[1]);
    func_00282C88(matrix[2]);
    scale_x = *(float *)(data + 16) * 0.0625f + 1.0f;
    matrix[0][0] = scale_x;
    scale_y = *(float *)(data + 16) * 0.0625f + 1.0f;
    matrix[1][1] = scale_y;
    matrix[2][2] = 1.0f;
    brightness = *(int *)(data + 28) << 24;
    base_colour = D_L00_001B0638;
    colour = base_colour + brightness;
    q.colors[0] = q.colors[1] = q.colors[2] = q.colors[3] = colour;
    do {
        char *moby = self;
        for (i = 0; i < 4; i++) {
            vertex_index = D_L00_0029A090[index][i][0];
            uv_index = D_L00_0029A090[index][i][1];
            func_00282D30(q.vertices[i], D_L00_00299830[vertex_index], D_L00_001B063C);
            u = D_L00_0029A990[uv_index][0];
            q.uv[i][0] = u;
            base_v = D_L00_0029A990[uv_index][1];
            scroll = D_L00_001B05D8;
            v = base_v - scroll;
            q.uv[i][1] = v;
        }
        func_00282C88(center);
        for (i = 0; i < 4; i++) {
            func_00283098(q.vertices[i], q.vertices[i], matrix);
            length = func_00282E20(q.vertices[i]);
            height = 1.5f - length * (2.0f / 3.0f);
            clamped = height > 0.0f ? height : 0.0f;
            amount = clamped * (2.0f / 3.0f);
            swell = func_002A7798(amount);
            ripple = *(float *)(data + 16) * 1.5f;
            swell *= ripple;
            swell *= 0.00825f;
            q.vertices[i][2] += swell;
            lift = *(float *)(data + 16) * 0.15f;
            q.vertices[i][2] += lift;
            func_00283098(q.vertices[i], q.vertices[i], moby + 192);
            px = *(float *)(moby + 16);
            q.vertices[i][0] += px;
            py = *(float *)(moby + 20);
            q.vertices[i][1] += py;
            pz = *(float *)(moby + 24);
            q.vertices[i][2] += pz;
            func_00282CC0(center, center, q.vertices[i]);
        }
        func_00282D30(center, center, 0.25f);
        qcopy(saved_center, center);
        func_00282CF0(normal, center, D_L00_001B8DC0);
        func_00282F20(normal, normal, 1.0f);
        func_00282CF0(edge1, q.vertices[2], q.vertices[0]);
        func_00282CF0(edge2, q.vertices[2], q.vertices[1]);
        func_00282DD8(center, edge1, edge2);
        func_00282F20(center, center, 1.0f);
        facing = func_00282DB0(normal, center);
        if (facing > 0.0f) {
            if (D_L00_001B2B58[index] == 0) {
                if (*(unsigned char *)(moby + 32) != 6)
                    D_L00_001B2B58[index] = func_L00_003E6778(D_L00_001B2B50, 1, 0.0f, 0.0f, saved_center);
            } else if (*(int *)(D_L00_001B2B58[index] + 124) == 0) {
                if (*(unsigned char *)(moby + 32) != 6)
                    D_L00_001B2B58[index] = func_L00_003E6778(D_L00_001B2B50, 1, 0.0f, 0.0f, saved_center);
                else
                    D_L00_001B2B58[index] = 0;
            }
            if (D_L00_001B2B58[index])
                qcopy((void *)D_L00_001B2B58[index], saved_center);
            func_00280B90(&q, 0, 0);
        }
    } while (++index < 143);
}
