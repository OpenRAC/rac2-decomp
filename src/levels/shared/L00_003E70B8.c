#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector g_scalar_transition_state;

/* The two bodies below have more than one copy in the levels, and which copy this
   program calls changes from one program to the next: the retail's call is read from
   the bytes, so the name carries no address. */
extern void ref_L00_003E70B8_00(char *p);

extern void ref_L00_003E70B8_01(char *p, float scale);

extern long long GetEffectTextureDescriptor(char *p);

extern float mat_fast_helper_a(float, float);

extern float vec_distance_xy(char *p, float *v);

extern void euler_to_matrix(float *matrix, float *quat);

extern void FastVecSub(char *dst, char *src, char *arg);

extern void vec_scale_to_length(char *dst, char *src, float scale);

extern void draw_world_quad(char *pkt, float *matrix, int mode);

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet.
   Its own unit: the two bodies it calls are C in L00_003E3258.c, and a call inside one
   object fixes the distance between the two, which the retail does not keep in every
   level.  From here both calls are global and the linker places them per program. */
/* Draws one glowing sprite at a position, turned to face the aim point, with the given colour, size and blend. */
void gfx_draw_aimed_sprite(char *position, int colorRgb, int alpha, char *texture, int blendFlags,
                       float sizeScale, float roll, float offsetScale)
{
    char drawPacket[144];
    float orientation[16];
    float aim[4];
    float towardAim[4];
    long long textureReg;

    ref_L00_003E70B8_00(drawPacket);
    textureReg = GetEffectTextureDescriptor(texture);

    *(long long *)(drawPacket + 136) = ((long long)blendFlags << 2) | 0x8000000040LL;
    *(long long *)(drawPacket + 128) = 280993940374112LL;
    *(int *)(drawPacket + 76) = colorRgb + (alpha << 24);
    *(int *)(drawPacket + 72) = colorRgb + (alpha << 24);
    *(int *)(drawPacket + 68) = colorRgb + (alpha << 24);
    *(int *)(drawPacket + 64) = colorRgb + (alpha << 24);
    *(long long *)(drawPacket + 112) = 0LL;
    *(long long *)(drawPacket + 120) = textureReg;

    aim[3] = 0.0f;
    aim[2] = mat_fast_helper_a(g_scalar_transition_state.x_140 - *(float *)(position + 0),
                            g_scalar_transition_state.y_144 - *(float *)(position + 4));
    aim[1] = -mat_fast_helper_a(vec_distance_xy(position, &g_scalar_transition_state.x_140),
                             g_scalar_transition_state.z_148 - *(float *)(position + 8));
    aim[0] = roll;

    euler_to_matrix(orientation, aim);
    FastVecSub(towardAim, &g_scalar_transition_state.x_140, position);
    vec_scale_to_length(towardAim, towardAim, offsetScale);

    orientation[12] = *(float *)(position + 0) + towardAim[0];
    orientation[13] = *(float *)(position + 4) + towardAim[1];
    orientation[14] = *(float *)(position + 8) + towardAim[2];
    orientation[15] = 1.0f;

    ref_L00_003E70B8_01(drawPacket, sizeScale);
    draw_world_quad(drawPacket, orientation, 0);
}
