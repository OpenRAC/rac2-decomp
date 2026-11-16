#include "names.h"
/* func_US2_002E91C0, the USA v2.00 copy of func_002E8368: the same C, where rename func_002EC1C0 becomes func_US2_002ED018; rename func_002E64A0 becomes func_US2_002E72D8; rename func_00132A10 becomes func_001329F0; rename func_00132AC8 becomes func_00132AA0; rename func_00132828 becomes func_00132818. */
#include "common.h"
#define W(p, o)  (*(int *)((char *)(p) + (o)))
#define H(p, o)  (*(short *)((char *)(p) + (o)))
#define B(p, o)  (*(unsigned char *)((char *)(p) + (o)))
#define F(p, o)  (*(float *)((char *)(p) + (o)))

extern void game_reset_frame_counters(void);
extern void game_update_idle_frame_counters(void);
extern void snd_set_current_buffer_flag(void);
extern void snd_clear_flag_and_update(void);
extern int snd_Pump(void);
extern void snd_send_cmd11_six_values_callback(int, int, int, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern void update_moby_animation_state(void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void func_002A0F48(void *);
extern void func_002A10E8(void *);
extern void scene_start_sequence_for_state_us2(void);
extern char g_effect_record_table_2[];
extern void part_init_effect_table(void *);
extern void snd_send_cmd18(void);
extern int func_001163B0(void);
extern void snd_send_cmd6(int);
extern void snd_send_cmd8(void);
extern void scene_load_texture_block(void);
extern void mem_clear(void *, int, int);
extern void load_select_segment_update_world(int);
extern int cam_set_from_selected_record(void);
extern void UpdateViewContext(void);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern void UpdateEquipmentPieces_us2(int);

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

extern int g_scene_sound_block_a[] MACRO_ADDR __attribute__((sda));         /* [0] +0, [1] +4, [3] +0xC */
extern int g_transition_effect_list[] __attribute__((sda));
extern int D_001B2148_first[] __asm__("D_001B2148") __attribute__((sda));         /* null-terminated entity list */
typedef struct { char pad[0x24]; float scale; } ScaleClass;
typedef struct { char pad[0x24]; ScaleClass *definition; int pad28; float scale; } ScaleEntity;
extern ScaleEntity *g_equipment_pieces[];         /* null-terminated entity list */
extern int g_transition_pending_sound __attribute__((sda));
extern int g_loader_archives;
extern int D_001A7280_block[] __asm__("D_001A7280") MACRO_ADDR __attribute__((sda));
extern int g_packet_buffer_size;
typedef struct { int pad, data_offset; char gap[0x48]; int scenes[5]; } TransitionHeader;
typedef struct { int offset, size; } TransitionChunk;
typedef struct { char pad[12]; int start, end, pad14; TransitionHeader *data; } TransitionArchive;
extern TransitionArchive g_loader_memory;
extern int g_transition_sound_table[];
extern char g_transition_vec_table[];        /* 16-byte entries */
typedef struct { float x, y, z, w; } TransitionVector;
typedef struct { char pad[0xc0]; TransitionVector basis[3]; } MatrixEntity;
extern TransitionVector g_transition_vector MACRO_ADDR;
extern char g_transition_vec_a[] SDATA(D_001AC0C0);
extern char g_transition_vec_b[] SDATA(D_001AC0D0);
extern char g_transition_fade_vec[] SDATA(D_001AC120);
extern float g_transition_fov_table[] SDATA(D_001AC150);
extern float g_transition_min_fov_table[] SDATA(D_001AC168);
extern float g_transition_fov_scale MACRO_ADDR;
extern float g_transition_scale_factor __attribute__((sda));
typedef struct { char pad[0xb0]; float fov; } TransitionView;
extern TransitionView g_view_params;        /* view: +0xB0 float */

/* Runs one frame of the transition scene: moves each object along its path and starts the next scene part when one ends (USA v2.00). */
int transition_update_scene_us2(void)
{
    float vec_a[4], vec_b[4], joint_matrix[16];
    float fade_ratio;
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
        snd_send_cmd11_six_values_callback(g_scene_sound_block_a[n], 0, 0x400, 0, 0, 0, 0, (int)g_transition_sound_table + n * 0x70);
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
    if (g_transition_pending_sound != 0) {
        scene_start_sequence_for_state_us2();
        g_transition_pending_sound = 0;
    }
    part_init_effect_table(g_effect_record_table_2);
    if (g_loader_archives < 2)
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
            snd_send_cmd6(g_scene_sound_block_a[1]);
            snd_send_cmd6(g_scene_sound_block_a[3]);
            snd_clear_flag_and_update();
            while (snd_Pump() != 0)
                ;
            snd_send_cmd8();
            D_001A7280_block[1] = 0;
            scene_load_texture_block();
        }
        g_hero_moby_default.phase = g_hero_moby_default.phase + 1;
        qcopy(g_transition_vec_b, g_transition_vec_a);
        mem_clear(&g_scene_playback_state, 0, 0x1D0);
        {
            int workspace_offset = g_packet_buffer_size;
            TransitionHeader *header;
            TransitionChunk *chunk;
            int data_base;
            int k;
            g_scene_playback_state.start = g_loader_memory.start + workspace_offset;
            g_scene_playback_state.end = g_loader_memory.end + workspace_offset;
            header = g_loader_memory.data;
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
    if (!(g_scene_playback_state.tick < 0x60)) {
        g_scene_playback_state.page = g_scene_playback_state.page + 1;
        load_select_segment_update_world(g_scene_playback_state.page);
    }
after:
    cam_set_from_selected_record();
    {
        float current = g_view_params.fov;
        float t = g_transition_min_fov_table[g_hero_moby_default.index];
        if (current < t)
            g_view_params.fov = t;
    }
    UpdateViewContext();
    fade_ratio = 1.0f;
    if (g_hero_moby_default.index == 4) {
        fade_ratio = (float)(g_scene_playback_state.duration - g_scene_playback_state.frame) / (float)g_scene_playback_state.duration;
        FastVecScale(vec_a, g_transition_fade_vec, fade_ratio);
        FastVecAdd(g_transition_vec_b, g_transition_vec_b, vec_a);
    }
    FastVecScale(&g_transition_vector, g_transition_vec_table + g_hero_moby_default.index * 16, (float)(g_scene_playback_state.frame - 0x78) * (fade_ratio * 20.0f));
    g_transition_fov_scale = g_transition_fov_table[g_hero_moby_default.index];
    for (i = 0; i < g_scene_playback_state.count; i = fp) {
        TransitionActor *o;
        int key_index, next_index;
        float r;
        char *s0m;
        key_index = g_scene_playback_state.tick >> 1;
        o = (TransitionActor *)g_scene_playback_state.objects[i];
        fp = i + 1;
        r = IntToFloat(g_scene_playback_state.tick & 1);
        next_index = key_index + 1;
        o->blend = r * 0.5f;
        s0m = (char *)o->keys;
        FastVecScale(vec_a, s0m + key_index * 16, 1.0f - o->blend);
        FastVecScale(vec_b, s0m + next_index * 16, o->blend);
        FastVecAdd(o->position, vec_a, vec_b);
        {
            char *d = (char *)o->definition;
            o->current_anim = B(d, 0xC) - 1;
            o->next_anim = B(d, 0xC) - 1;
            o->key = key_index;
            o->next_key = next_index;
        }
        update_moby_animation_state(o);
        o->draw_flags = 0x1FF;
        if (o->type == 0xD54) {
            if (D_001B2148_first[0] != 0) {
                moby_transform_joint_point(o, 0, joint_matrix);
                {
                    int effect_index = 0;
                    o->flags = 0;
                    o->draw_flags = 0;
                    if (D_001B2148_first[0] != 0) {
                        do {
                            int k;
                            B((char *)g_transition_effect_list[effect_index], 0x63) = 0;
                            H((char *)g_transition_effect_list[effect_index], 0x32) = 0x1FF;
                            qcopy((char *)g_transition_effect_list[effect_index] + 0x10, o->position);
                            for (k = 0; k < 3; k++) {
                                ((MatrixEntity *)g_transition_effect_list[effect_index])->basis[k].x = joint_matrix[k * 4];
                                ((MatrixEntity *)g_transition_effect_list[effect_index])->basis[k].y = joint_matrix[k * 4 + 1];
                                ((MatrixEntity *)g_transition_effect_list[effect_index])->basis[k].z = joint_matrix[k * 4 + 2];
                            }
                            func_002A10E8((void *)g_transition_effect_list[effect_index]);
                            effect_index = effect_index + 1;
                        } while (g_transition_effect_list[effect_index] != 0);
                    }
                }
            } else {
                UpdateEquipmentPieces_us2(g_scene_playback_state.id);
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
                int scene_duration = g_scene_playback_state.duration;
                int scene_frame = g_scene_playback_state.frame;
                if (scene_duration - 0x28 < scene_frame) {
                    float fade_scale = (float)(scene_duration - scene_frame - 4) * 0.027777778f;
                    if (fade_scale < 0.0f)
                        fade_scale = 0.0f;
                    o->scale = F(d, 0x24) * fade_scale;
                    g_transition_scale_factor = fade_scale;
                    if (D_001B2148_first[0] != 0) {
                        char *e = (char *)D_001B2148_first[0];
                        F(e, 0x2C) = F((char *)W(e, 0x24), 0x24) * fade_scale;
                    }
                    o->opacity = (int)(fade_scale * 232.0f);
                    if (o->type == 0xD54) {
                        if (D_001B2148_first[0] == 0) {
                            int j;
                            g_hero_moby_default.flag = 1;
                            if (g_equipment_pieces[0] != 0) {
                                j = 0;
                                do {
                                    ScaleEntity *e = g_equipment_pieces[j];
                                    j++;
                                    e->scale = e->definition->scale * fade_scale;
                                } while (g_equipment_pieces[j] != 0);
                            }
                        }
                    }
                }
            }
        }
    }
    game_update_idle_frame_counters();
    return 0;
}
