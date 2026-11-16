#include "include_asm.h"
#include "names.h"
extern int g_env_preset_count __attribute__((section(".sdata")));
typedef struct {
    int objectValue;
    unsigned short x, y, z;
    short audioMode, musicTrack;
    unsigned char nearIntensity, farIntensity;
    unsigned char r, g, b, audio1, audio2, audio3, audioEnabled;
    unsigned char fogR, fogG, fogB;
    short fogNear, fogFar;
    unsigned short reserved;
} EnvironmentPreset;
extern EnvironmentPreset *g_env_preset_table __attribute__((section(".sdata")));
extern unsigned char g_sound_state[];
extern unsigned char g_fog_color_r[] __attribute__((section(".sdata"))), g_fog_color_g[] __attribute__((section(".sdata"))), g_fog_color_b[] __attribute__((section(".sdata")));
extern float g_fog_near __attribute__((section(".sdata"))), g_fog_far __attribute__((section(".sdata"))), g_fog_near_intensity __attribute__((section(".sdata")));
extern float g_fog_far_intensity __attribute__((section(".sdata")));
extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern void func_L00_00312098(void *, int, int, int, int);
extern void snd_start_music_stream_no_loop(int, int, int);
extern void gfx_apply_display_config(void);

/* Applies the nearest preset within range, including its music and fog settings. */
void level_apply_nearest_env_preset(unsigned char *object)
{
    float position[4], delta[4];
    int i = 0, best = -1;
    float distance = 1000000.0f;
    if (g_env_preset_count > 0) {
        do {
            EnvironmentPreset *row = (EnvironmentPreset *)(i * 32 + (int)g_env_preset_table);
            float d;
            position[0] = row->x * 0.25f;
            position[1] = row->y * 0.25f;
            position[2] = row->z * 0.25f;
            FastVecSub(delta, object + 0x10, position);
            d = func_L00_002EE290(delta);
            if (d < distance) {
                distance = d;
                best = i;
            }
            i++;
        } while (i < g_env_preset_count);
    }
    if (best == -1 || distance > 400.0f)
        return;
    {
        EnvironmentPreset *row = (EnvironmentPreset *)(best * 32 + (int)g_env_preset_table);
        func_L00_00312098(object, ((row->b << 16) + (row->g << 8)) | row->r, 0, 0, 0);
    }
    *(int *)(object + 0x38) = g_env_preset_table[best].objectValue;
    {
        EnvironmentPreset *row = (EnvironmentPreset *)(best * 32 + (int)g_env_preset_table);
        if (row->audioEnabled) {
            unsigned char *sound = g_sound_state;
            *(int *)(sound + 0x64) = row->audioMode;
            sound[0x68] = row->audio1;
            sound[0x69] = row->audio2;
            sound[0x6a] = row->audio3;
            sound[0x6b] |= 7;
        }
    }
    snd_start_music_stream_no_loop(g_env_preset_table[best].musicTrack, 1, 1024);
    {
        EnvironmentPreset *row = (EnvironmentPreset *)(best * 32 + (int)g_env_preset_table);
        if (row->fogNear < row->fogFar) {
            g_fog_color_r[0] = row->fogR;
            g_fog_color_g[0] = row->fogG;
            g_fog_color_b[0] = row->fogB;
            {
                float near = row->fogNear * 1024.0f;
                float far = row->fogFar * 1024.0f;
                g_fog_near = near;
                g_fog_far = far;
            }
            g_fog_near_intensity = row->nearIntensity;
            g_fog_far_intensity = row->farIntensity;
            gfx_apply_display_config();
        }
    }
}
