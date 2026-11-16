/* Camera activation priority check; corresponds to RAC1 Camera_ActivationCheckPriority. */
#include "common.h"
typedef struct {
    int (*entry[5])(char *, char *);
}
Dispatch70838;
extern Dispatch70838 g_object_dispatch_table[];
typedef struct {
    char pad[12];
    int clip;
    char rest[20];
    int index;
}
Info70838;
typedef struct {
    char pad[28];
    Info70838 *info;
}
Def70838;
extern Def70838 *g_camera_definition_table __attribute__((section(".sdata")));
extern char *g_camera_group_table __attribute__((section(".sdata")));
extern char g_hero_state[], g_hero_position[];
extern int IsPointInCuboid(void *, int);
int Camera_ActivationCheckPriority(unsigned char *cur, unsigned char *other) {
    unsigned char *state = (unsigned char *)cur+0x74;
    if ((unsigned char)cur[0x7c]==0) return 0;
    {
        int (*fn)(char *, char *) = g_object_dispatch_table[*(short *)(cur+0x8c)].entry[1];
        if (fn) {
            switch (fn(cur, other)){
                case -1:return 0;
                case 1:return 1;
            }
        }
    }
    switch (*(int *)state) {
        case 1:case 2:
        if (state[9]==0) return 0;
        case 0:
        if (!other) return 1;
        if (*(short *)(other+0x7e)!=0) return 1;
        if (state[8]>(unsigned char)other[0x7c]) return 1;
        break;
        case 4: {
            Info70838 *info = g_camera_definition_table[*(short *)(cur+0x84)].info;
            if (other && *(short *)(other+0x7e)==0 && !(state[8]>(unsigned char)other[0x7c])) return 0;
            if (IsPointInCuboid(g_hero_position, info->clip)) return 1;
            break;
        }
        case 7: {
            char *base = g_hero_state;
            short e = *(short *)(cur+0x86);
            if (e!=*(int *)(base+0x24a0)) return 0;
            if (*(short *)(other+0x7e)==0 && !(state[8]>(unsigned char)other[0x7c])) return 0;
            if (e!=3) return 1;
            {
                Def70838 *rec = &g_camera_definition_table[*(short *)(cur+0x84)];
                int g = rec->info->index;
                if (g<0 || (*(int *)(base+0x630)==*(int *)(g_camera_group_table+g*32+0x10) && *(int *)(base+0x640)==0)) return 1;
            }
            break;
        }
    }
    return 0;
}
