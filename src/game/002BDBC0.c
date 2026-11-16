#include "include_asm.h"
#include "common.h"


typedef struct {
    u8 dir[12];
    f32 decay;
    u32 color;
    s32 flags;
    s16 frames;
    s16 pad1A;
    f32 fade;
} Puff2BDBC0;

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u32 color;
    u8 f8;
    u8 f9;
    s16 frames;
    f32 size;
    f32 pos[4];
    Puff2BDBC0 p;
} Effect2BDBC0;

extern u8 *g_part_tex_growing_puff_table[];

extern Effect2BDBC0 *part_alloc(int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern int func_001163B0(void);

/* Creates a puff of smoke that starts small and grows to the given size over its life. */
void part_spawn_growing_puff(void *pos, void *dir, u32 color, s32 flags, s32 frames, f32 size) {
    Puff2BDBC0 *puff;
    Effect2BDBC0 *effect;
    f32 life_frames;
    f32 size_growth;

    effect = part_alloc(0x16);
    if (effect != 0) {
        puff = &effect->p;
        effect->color = color;
        effect->f9 = FloatToInt(4.0f) + 0x70;
        effect->f1 = 0;
        effect->f3 = 0x44;
        effect->size = size * 0.2f;
        effect->f8 = func_001163B0();
        effect->f2 = *g_part_tex_growing_puff_table[0];
        effect->frames = frames;
        puff->frames = frames;
        life_frames = IntToFloat(frames);
        size_growth = size - effect->size;
        puff->color = color;
        puff->flags = flags;
        puff->fade = size_growth / life_frames;
        qcopy(puff, dir);
        qcopy(effect->pos, pos);
        puff->decay = 0.00034444444f;
    }
}
