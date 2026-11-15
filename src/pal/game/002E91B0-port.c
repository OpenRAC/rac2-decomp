#include "common.h"
#define W(p, o)  (*(int *)((char *)(p) + (o)))
#define H(p, o)  (*(short *)((char *)(p) + (o)))
#define B(p, o)  (*(unsigned char *)((char *)(p) + (o)))
#define F(p, o)  (*(float *)((char *)(p) + (o)))

extern void game_reset_frame_counters(void);
extern void func_PAL_002F6208(void);
extern void snd_set_current_buffer_flag(void);
extern void snd_clear_flag_and_update(void);
extern int snd_Pump(void);
extern void snd_send_cmd11_six_values_callback(int, int, int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void update_moby_animation_state(void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void func_002A0F48(void *);
extern void func_002A10E8(void *);
extern void func_PAL_002ED0D8(void);
extern char D_00240450[];
extern void part_init_effect_table(void *);
extern void snd_send_cmd18(void);
extern int func_001163B0(void);
extern void snd_send_cmd6(int);
extern void snd_send_cmd8(void);
extern void scene_load_texture_block(void);
extern void mem_clear(void *, int, int);
extern void load_select_segment_update_world(int);
extern void cam_set_from_selected_record(void);
extern void UpdateViewContext(void);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern void func_PAL_002E7270(int);

typedef struct {
 char pad0[0x10]; float position[4]; char pad20[4]; char *definition;
 char pad28[4]; float scale; char pad30[2]; short draw_flags; char pad34[12];
 unsigned char key, next_key, current_anim, next_anim; float blend;
 char pad48[0x19]; unsigned char alpha, cached_frame, flags; char pad64[4];
 char *keys; char pad6c[0x29]; unsigned char opacity; char pad96[0x14]; short type;
} TransitionActor;
extern float g_screen_fade MACRO_ADDR;
typedef struct {
 char pad[0xc]; unsigned char count; char gap[0x3b]; void *animations[1];
} AnimationClass;
typedef struct { char pad[0x24]; AnimationClass *definition; } AnimationObject;
typedef struct {
 char pad[0x34]; int frame, tick, page; short duration, pad42, count;
 char pad46[0xe]; int id; char pad58[0x14]; int start, end;
 int entries[70]; char *objects[17];
} TransitionScene;
extern TransitionScene g_scene_playback_state;        /* controller state */
typedef struct {
 char pad[0x2c]; short flag; char pad2e[0x36]; int index, phase;
} TransitionMenu;
extern TransitionMenu g_hero_moby_default;        /* mode block: +0x64 index, +0x68 phase */
extern int D_001B2130_first SDATA(D_001B2130);


extern int D_001B2130[] MACRO_ADDR __attribute__((sda));         /* [0] +0, [1] +4, [3] +0xC */
extern int D_001B2148[] __attribute__((sda));
extern int D_001B2148_first[] __asm__("D_001B2148") __attribute__((sda));         /* null-terminated entity list */
typedef struct { char pad[0x24]; float scale; } ScaleClass;
typedef struct { char pad[0x24]; ScaleClass *definition; int pad28; float scale; } ScaleEntity;
extern ScaleEntity *g_equipment_pieces[];         /* null-terminated entity list */
extern int D_001ABEB0 __attribute__((sda));
extern int D_001A7280;
extern int D_001A7280_block[] __asm__("D_001A7280") MACRO_ADDR __attribute__((sda));
extern int D_001B22B0;
typedef struct { int pad, data_offset; char gap[0x48]; int scenes[5]; } TransitionHeader;
typedef struct { int offset, size; } TransitionChunk;
typedef struct { char pad[12]; int start, end, pad14; TransitionHeader *data; } TransitionArchive;
extern TransitionArchive D_001BAEC0;
extern int D_001886D0[];
extern char D_00261F30[];        /* 16-byte entries */
typedef struct { float x, y, z, w; } TransitionVector;
typedef struct { char pad[0xc0]; TransitionVector basis[3]; } MatrixEntity;
extern TransitionVector D_001B20D0 MACRO_ADDR;
extern char D_001AC0C0[] SDATA(D_001AC0C0);
extern char D_001AC0D0[] SDATA(D_001AC0D0);
extern char D_001AC120[] SDATA(D_001AC120);
extern float D_001AC150[] SDATA(D_001AC150);
extern float D_001AC168[] SDATA(D_001AC168);
extern float D_001ABDD4 MACRO_ADDR;
extern float D_001ABF10 __attribute__((sda));
typedef struct { char pad[0xb0]; float fov; } TransitionView;
extern TransitionView D_001B9040;        /* view: +0xB0 float */

int func_PAL_002E91B0(void)
{
    float sp0[4], sp10[4], sp20[16];
    float f20;
    int i, fp;

    game_reset_frame_counters();
    {
        float v = g_screen_fade - 0.25f;
        g_scene_playback_state.tick = g_scene_playback_state.tick + 1;
        g_scene_playback_state.frame = g_scene_playback_state.frame + 1;
        g_screen_fade = v;
        if (v < 0.0f)
            g_screen_fade = 0.0f;
    }
    if (g_scene_playback_state.frame == 1) {
        int n;
        snd_set_current_buffer_flag();
        n = g_hero_moby_default.index;
        snd_send_cmd11_six_values_callback(D_001B2130[n], 0, 0x400, 0, 0, 0, 0, (int)D_001886D0 + n * 0x70);
        snd_clear_flag_and_update();
        snd_Pump();
    }
    if (g_scene_playback_state.frame < g_scene_playback_state.duration) {
        goto running;
    }
    /* the phase has ended */
    for (i = 0; i < g_scene_playback_state.count; i++) {
        AnimationObject *p = (AnimationObject *)g_scene_playback_state.objects[i];
        if (p != 0) {
            p->definition->count--;
            p->definition->animations[p->definition->count] = 0;
            moby_mark_spawned(p);
        }
    }
    if (D_001ABEB0 != 0) {
        func_PAL_002ED0D8();
        D_001ABEB0 = 0;
    }
    part_init_effect_table(D_00240450);
    if (D_001A7280 < 2)
        g_hero_moby_default.phase = 0;
    if (g_hero_moby_default.phase < 2) {
        if (g_hero_moby_default.index != 2) {
            snd_send_cmd18();
            while (snd_Pump() != 0)
                ;
        }
        if (g_hero_moby_default.phase == 0) {
            int r = ((func_001163B0() >> 16) % 3) + 1;
            g_hero_moby_default.index = (g_hero_moby_default.index + r) & 3;
        } else {
            g_hero_moby_default.index = 4;
            snd_set_current_buffer_flag();
            snd_send_cmd6(D_001B2130_first);
            snd_send_cmd6(D_001B2130[1]);
            snd_send_cmd6(D_001B2130[3]);
            snd_clear_flag_and_update();
            while (snd_Pump() != 0)
                ;
            snd_send_cmd8();
            D_001A7280_block[1] = 0;
            scene_load_texture_block();
        }
        g_hero_moby_default.phase = g_hero_moby_default.phase + 1;
        qcopy(D_001AC0D0, D_001AC0C0);
        mem_clear(&g_scene_playback_state, 0, 0x1D0);
        {
            int workspace_offset = D_001B22B0;
            TransitionHeader *header;
            TransitionChunk *chunk;
            int data_base;
            int k;
            g_scene_playback_state.start = D_001BAEC0.start + workspace_offset;
            g_scene_playback_state.end = D_001BAEC0.end + workspace_offset;
            header = D_001BAEC0.data;
            data_base = (int)header + header->data_offset;
            chunk = (TransitionChunk *)(data_base + header->scenes[g_hero_moby_default.index]);
            for (k = 0; k < 70 && chunk->size != 0; k++) {
                int offset = chunk->offset + 0x800;
                g_scene_playback_state.entries[k] = data_base + header->scenes[g_hero_moby_default.index] + offset;
                chunk++;
            }
        }
        load_select_segment_update_world(0);
        goto after;
    } else {
        if (D_001A7280_block[1] == 0)
            return 1;
        D_001A7280_block[1] = 0;
        return 1;
    }

running:
    if (!(g_scene_playback_state.tick < 0x50)) {
        g_scene_playback_state.page = g_scene_playback_state.page + 1;
        load_select_segment_update_world(g_scene_playback_state.page);
    }
after:
    cam_set_from_selected_record();
    {
        float current = D_001B9040.fov;
        float t = D_001AC168[g_hero_moby_default.index];
        if (current < t)
            D_001B9040.fov = t;
    }
    UpdateViewContext();
    f20 = 1.0f;
    if (g_hero_moby_default.index == 4) {
        f20 = (float)(g_scene_playback_state.duration - g_scene_playback_state.frame) / (float)g_scene_playback_state.duration;
        FastVecScale(sp0, D_001AC120, f20);
        FastVecAdd(D_001AC0D0, D_001AC0D0, sp0);
    }
    FastVecScale(&D_001B20D0, D_00261F30 + g_hero_moby_default.index * 16, (float)(g_scene_playback_state.frame - 0x64) * (f20 * 20.0f));
    D_001ABDD4 = D_001AC150[g_hero_moby_default.index];
    for (i = 0; i < g_scene_playback_state.count; i = fp) {
        TransitionActor *o;
        int s1, s2;
        float r;
        char *s0m;
        s1 = g_scene_playback_state.tick >> 1;
        o = (TransitionActor *)g_scene_playback_state.objects[i];
        fp = i + 1;
        r = IntToFloat(g_scene_playback_state.tick & 1);
        s2 = s1 + 1;
        o->blend = r * 0.5f;
        s0m = (char *)o->keys;
        FastVecScale(sp0, s0m + s1 * 16, 1.0f - o->blend);
        FastVecScale(sp10, s0m + s2 * 16, o->blend);
        FastVecAdd(o->position, sp0, sp10);
        {
            char *d = (char *)o->definition;
            o->current_anim = B(d, 0xC) - 1;
            o->next_anim = B(d, 0xC) - 1;
            o->key = s1;
            o->next_key = s2;
        }
        update_moby_animation_state(o);
        o->draw_flags = 0x1FF;
        if (o->type == 0xD54) {
            if (D_001B2148_first[0] != 0) {
                moby_transform_joint_point(o, 0, sp20);
                {
                    int a3 = 0;
                    o->flags = 0;
                    o->draw_flags = 0;
                    if (D_001B2148_first[0] != 0) {
                        do {
                            int k;
                            B((char *)D_001B2148[a3], 0x63) = 0;
                            H((char *)D_001B2148[a3], 0x32) = 0x1FF;
                            qcopy((char *)D_001B2148[a3] + 0x10, o->position);
                            for (k = 0; k < 3; k++) {
                                ((MatrixEntity *)D_001B2148[a3])->basis[k].x = sp20[k * 4];
                                ((MatrixEntity *)D_001B2148[a3])->basis[k].y = sp20[k * 4 + 1];
                                ((MatrixEntity *)D_001B2148[a3])->basis[k].z = sp20[k * 4 + 2];
                            }
                            func_002A10E8((void *)D_001B2148[a3]);
                            a3 = a3 + 1;
                        } while (D_001B2148[a3] != 0);
                    }
                }
            } else {
                func_PAL_002E7270(g_scene_playback_state.id);
            }
            o->opacity = 0xE8;
        }
        o->cached_frame = 0xFF;
        {
            {
                o->alpha = 0xFF;
            }
        }
        func_002A0F48(o);
        {
            char *d = (char *)o->definition;
            o->current_anim = B(d, 0xC) - 1;
            o->next_anim = B(d, 0xC) - 1;
            if (g_hero_moby_default.index == 4) {
                int a0 = g_scene_playback_state.duration;
                int v1 = g_scene_playback_state.frame;
                if (a0 - 0x28 < v1) {
                    float f1 = (float)(a0 - v1 - 4) * 0.027777778f;
                    if (f1 < 0.0f)
                        f1 = 0.0f;
                    o->scale = F(d, 0x24) * f1;
                    D_001ABF10 = f1;
                    if (D_001B2148_first[0] != 0) {
                        char *e = (char *)D_001B2148_first[0];
                        F(e, 0x2C) = F((char *)W(e, 0x24), 0x24) * f1;
                    }
                    o->opacity = (int)(f1 * 232.0f);
                    if (o->type == 0xD54) {
                        if (D_001B2148_first[0] == 0) {
                            int j;
                            g_hero_moby_default.flag = 1;
                            if (g_equipment_pieces[0] != 0) {
                                j = 0;
                                do {
                                    ScaleEntity *e = g_equipment_pieces[j];
                                    j++;
                                    e->scale = e->definition->scale * f1;
                                } while (g_equipment_pieces[j] != 0);
                            }
                        }
                    }
                }
            }
        }
    }
    func_PAL_002F6208();
    return 0;
}