#include "names.h"
typedef void (*ObjectDispatch)(void *);
typedef struct { ObjectDispatch entries[5]; } ObjectDispatchRecord;
extern ObjectDispatchRecord g_object_dispatch_table[];
extern char *g_camera_state_ptr;
extern char g_camera_records[];
extern void moby_call_handler_fourth(char *);
typedef struct {
    char pad00[0x30];
    float pos[3];
    char pad3C[0x64 - 0x3C];
    float last[3];
    char pad70[0x8C - 0x70];
    short kind;
    char pad8E[0xA0 - 0x8E];
} Obj_270A48;
extern int g_camera_active_flags[];
extern int Camera_ActivationCheckPriority(void *, void *);
extern void cam_switch_active(void *);
extern void moby_toggle_effect(char *);
extern void script_run_delayed_call_list(void);

/* Pick the best live object over the current one, then refresh and dispatch it. */
int cam_update_active(void)
{
    Obj_270A48 *best = (Obj_270A48 *)g_camera_state_ptr;
    int changed;
    int i;
    ObjectDispatch callback;
    moby_call_handler_fourth((char *)best);
    changed = 0;
    for (i = 0; i < 48; i++) {
        if (g_camera_active_flags[i] != 0 && &((Obj_270A48 *)g_camera_records)[i] != best && Camera_ActivationCheckPriority(&((Obj_270A48 *)g_camera_records)[i], best)) {
            best = &((Obj_270A48 *)g_camera_records)[i];
            changed = 1;
        }
    }
    if (changed) cam_switch_active(best);
    callback = g_object_dispatch_table[best->kind].entries[3];
    moby_toggle_effect((char *)best);
    if (callback != 0) callback(best);
    {
        float *src = best->pos;
        float *dst = best->last;
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
    }
    script_run_delayed_call_list();
    return -1;
}
