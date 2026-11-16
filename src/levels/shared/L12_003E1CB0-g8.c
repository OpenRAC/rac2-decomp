#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u16 g_moby_init_state_value __attribute__((sda));

/* Sets the object's byte at +0x95 to 9 and copies a level-wide halfword into its private data. */
void moby_init_state_byte(u8 *moby) {
    *(u8 *)(moby + 0x95) = 9;
    *(u16 *)(*(u32 *)(moby + 0x68) + 0x29E) = g_moby_init_state_value;
}

extern float FastAddRotations(float, float);

extern float math_fast_sin_or_cos_b(float);

extern int FastTweenColor(int, int, float);

extern void moby_transform_joint_point(char *, int, void *);

extern void gfx_add_draw_callback_first(void *, void *);

extern void group_draw_entity_glows(u8 *);

/* The entity base and the frame counter are read bare (`lui`/`lw` in one register: `sda` sized
   over 8 bytes in a -G8 unit); the group count is a $gp scalar and the group table an ordinary
   array. The frame counter is read twice, once as the compare and once as the store: the array declaration gives
   the bare form for both, and a scalar declaration under the same assembler name for the compare
   lets cc1 keep retail's order of its load and of the member load before it (with the array
   element cc1 loads the member first). The pair at D_L12_001B21D0 is copied as one 8-byte
   block (`ldl`/`ldr`/`sdl`/`sdr`). */
extern unsigned short *g_moby_l12_group_lists[];
extern int g_moby_l12_group_count __attribute__((sda));
extern u8 *g_moby_list_start[3] __attribute__((sda));
extern int g_frame_l12_counter[3] __attribute__((sda));
extern int D_L12_001B29C8_s __asm__("D_L12_001B29C8") __attribute__((sda));

struct L12PairWord {
    int a;
    int b;
};

extern struct L12PairWord g_pulsing_group_color_pair __attribute__((nosda));

/* The kind's private block at +0x68 of the object and of each entity. */
struct L12Kind348 {
    char pad[0x348];
    float f348;
    float f34C;
    int f350;
};

struct L12Kind348Entity {
    char pad0[0x20];
    u8 state;
    char pad1[0x10];
    u8 f31;
    char pad2[0x36];
    struct L12Kind348 *obj;
    char pad3[0x3E];
    short type;
};

struct L12Kind348Object {
    char pad0[0x21];
    u8 group;
    char pad1[0x46];
    struct L12Kind348 *obj;
    char pad2[0x0C];
    int f78;
};

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L12_001B29C8 differs from the object's word at +0x350, walks the object's group
   and refreshes every live entity of kind 0x11EB, then registers func_L12_004281D8. */
void pulsing_group_update(struct L12Kind348Object *moby) {
    struct L12Kind348 *vars = moby->obj;
    struct L12PairWord colorPair = g_pulsing_group_color_pair;
    float wave;
    unsigned short *groupEntry;
    struct L12Kind348Entity *entity;
    struct L12Kind348 *entityVars;

    wave = FastAddRotations(vars->f348, 0.2094395458f);
    vars->f348 = wave;
    wave = math_fast_sin_or_cos_b(wave);
    vars->f34C = wave * 0.5f + 0.5f;
    moby->f78 = FastTweenColor(colorPair.a, colorPair.b, vars->f34C);
    if (vars->f350 != D_L12_001B29C8_s) {
        for (groupEntry = g_moby_l12_group_lists[moby->group];
             moby->group != 0xFF && moby->group <= g_moby_l12_group_count && groupEntry != 0 &&
             ((groupEntry != 0 && (short)groupEntry[-1] >= 0) || groupEntry == g_moby_l12_group_lists[moby->group]);
             groupEntry++) {
            entity = (struct L12Kind348Entity *)(g_moby_list_start[0] + ((*groupEntry & 0x7FFF) << 8));
            if (entity == 0)
                break;
            if (entity->f31 != 0 && entity->type == 0x11EB && entity->state != 0xFE && entity->state != 0xFD) {
                entityVars = entity->obj;
                moby_transform_joint_point((char *)entity, 0, (char *)entityVars + 0x240);
                entityVars->f350 = g_frame_l12_counter[0];
            }
        }
        gfx_add_draw_callback_first((void *)group_draw_entity_glows, moby);
    }
}

extern void FastVecScale(void *dst, void *src, float value);

extern void transform_vector(void *, void *, void *);

extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

/* Here the group count is read bare, so it takes a second name sized over 8 bytes (its .extern
   re-sizes the symbol after func_L12_00428040's $gp reads). The vector's address is $gp-relative.
   The colour pair is one plain 8-byte object, read as two members: cc1 counts `lw $4,D` (a small
   symbol) as one instruction, but `lw $5,D+4` as two (mips.c's simple_memory_operand has no case
   for a symbol plus an offset), so the delay-slot filler passes over the second argument's load
   and takes the first's. In the slot the assembler gives that load the $gp form; outside it,
   with a plain declaration's .extern only at the end of the file, `lw $5,D+4` becomes retail's
   `lui $a1` / `lw $a1`. With `sda` both words come through $gp (380 bytes); as two separate
   words each load is one instruction and the second argument's takes the slot. */
extern int D_L12_001B2EB8_a[3] __asm__("D_L12_001B2EB8") __attribute__((sda));
extern char g_pulsing_group_glow_vector[8] __attribute__((sda));
extern struct L12PairWord g_pulsing_group_tween_colors;

/* Turns the entities of the object's group that are kind 0x11EB and in use (flag byte at +0x31
   set, state byte at +0x20 not 0xFE or 0xFD): the vector at D_L12_001B21E0 is turned by the
   angle at +0x344 of the entity's private block and then by its matrix at +0x240, the colour
   pair at D_L12_001B21F0 is mixed by the fraction at +0x34C, and both go to func_L00_00325AE8. */
void group_draw_entity_glows(u8 *moby) {
    u16 *q;
    u16 *p;
    u8 *e;
    u8 *priv;
    float buf[4];
    int r;

    if (moby[0x21] == 0xFF)
        return;
    q = g_moby_l12_group_lists[moby[0x21]];
    if (q == 0)
        return;
    for (p = q; moby[0x21] != 0xFF && moby[0x21] <= D_L12_001B2EB8_a[0] && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == g_moby_l12_group_lists[moby[0x21]]);
         p++) {
        e = g_moby_list_start[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x31] != 0 && *(s16 *)(e + 0xAA) == 0x11EB /* moby class 4587 */ && e[0x20] != 0xFE && e[0x20] != 0xFD) {
            priv = *(u8 **)(e + 0x68);
            FastVecScale(buf, g_pulsing_group_glow_vector, *(float *)(priv + 0x344));
            transform_vector(buf, buf, priv + 0x240);
            r = FastTweenColor(g_pulsing_group_tween_colors.a, g_pulsing_group_tween_colors.b, *(float *)(priv + 0x34C));
            gfx_l00_draw_billboard_quad(buf, r, *(float *)(priv + 0x344) * 0.2f, 0.08f);
        }
    }
}

extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void ref_L12_00429D60_00(void *, int, float, int, float, float, int, int, void *);
extern float g_flare_scale __attribute__((sda));
extern float g_flare_far_scale_mult __attribute__((sda));
extern int g_laser_quad_state_a __attribute__((sda));
extern int g_laser_quad_state_b __attribute__((sda));
extern int g_flare_texture_near __attribute__((sda));
extern int g_flare_texture_far __attribute__((sda));

/* Draws two glow effects at the object's position, each with a random brightness and its own scale and colour. */
void part_spawn_two_flare_effects(char *object) {
    int flareAlpha;
    int flareAlpha2;
    float scale;
    float scale2;
    float random;
    scale = g_flare_scale;
    scale *= *(float *)(object + 0x2C);
    flareAlpha = math_random_int_range(95, 111);
    random = math_random_angle();
    ref_L12_00429D60_00(object + 0x10, g_flare_texture_near, scale, flareAlpha, random, 1.0f, g_laser_quad_state_a, 2, object);
    scale2 = g_flare_scale;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= g_flare_far_scale_mult;
    flareAlpha2 = math_random_int_range(111, 127);
    random = math_random_angle();
    ref_L12_00429D60_00(object + 0x10, g_flare_texture_far, scale2, flareAlpha2, random, 1.0f, g_laser_quad_state_b, 2, object);
}
