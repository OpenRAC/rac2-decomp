typedef int Quad __attribute__((mode(TI)));
typedef struct { char pad[0x10]; float rate, limit; int active; short state; short pad1e; float epsilon; int flags; char pad28[8]; } PathSpring;
typedef struct { char pad[0x40]; int flags; int pad44; float angle; float scale; } PathMotion;
typedef struct { float a, b; char pad[8]; float c; } PathLimits;
typedef struct { int a, b, c, d, enabled; } PathFlags;
/* A fixed sixteen-byte header followed by a variable number of vector records. */
typedef struct { int count; int reserved[3]; float point[0][4]; } CameraPath;
extern char *D_L13_001B22C4;
extern char *D_L13_001B2140;
extern CameraPath *D_L13_001FE580[];
extern void func_00282C88(Quad *);
extern int func_L00_00341FA8(void *, void *, void *, int *, float *, int, float, float, float);
extern int func_00283CF0(float);

void func_L13_004388C8(char *camera) {
    float projected[4];
    int segment;
    float fraction;
    char *status;
    char *settings = *(char **)(D_L13_001B22C4 + *(short *)(camera + 0x84) * 32 + 0x1C);
    CameraPath *first;
    CameraPath *route;
    CameraPath *other;
    CameraPath *other_route;
    int i;
    int j;
    int previous;
    int previous_index;
    int current;
    int steps;
    {
        char *private = *(char **)(camera + 0x70);
        PathMotion *motion = (PathMotion *)(private + 0x80);
        motion->scale = 1.5f;
        motion->flags = 0;
        if (*(int *)(settings + 0x30) == 3) motion->scale = 0.5f;
        motion->angle = 0.20943953f;
    }
    status = camera + 0x74;
    {
        char *private = *(char **)(camera + 0x70);
        PathLimits *limits = (PathLimits *)(private + 0xE0);
        limits->a = 6.0f;
        limits->b = 0.5f;
        limits->c = 2.0f;
    }
    {
        char *private = *(char **)(camera + 0x70);
        PathSpring *spring = (PathSpring *)private;
        spring->limit = 0.175f;
        spring->epsilon = 0.0005f;
        spring->rate = 0.01f;
        spring->active = 0;
        spring->state = 0;
        spring->flags = 0;
        func_00282C88((Quad *)spring);
    }
    {
        char *private = *(char **)(camera + 0x70);
        PathSpring *spring = (PathSpring *)(private + 0x30);
        *(float *)((char *)spring + 0x24) = 0.3f;
        spring->epsilon = 0.01f;
        *(float *)((char *)spring + 0x28) = 0.2f;
        *(short *)((char *)spring + 0x2C) = 0;
        func_00282C88((Quad *)spring);
    }
    {
        char *private = *(char **)(camera + 0x70);
        PathSpring *spring = (PathSpring *)(private + 0x100);
        func_00282C88((Quad *)spring);
        func_00282C88((Quad *)(private + 0x120));
        *(float *)((char *)spring + 0x40) = 3.0f;
        *(float *)((char *)spring + 0x30) = 0.003f;
        *(float *)((char *)spring + 0x34) = 0.1f;
        *(float *)((char *)spring + 0x38) = 0.2f;
        *(int *)((char *)spring + 0x3C) = 0;
    }
    {
        PathFlags *flags = (PathFlags *)(*(char **)(camera + 0x70) + 0x150);
        flags->a = 0;
        flags->b = 0;
        flags->c = 0;
        flags->d = 0;
        flags->enabled = 1;
    }
    if (*(int *)(settings + 0x30) == 2 && *(short *)(settings + 0x34) == 0) {
        route = D_L13_001FE580[*(int *)(settings + 0x20)];
        other_route = *(CameraPath **)(D_L13_001B2140 + *(int *)(settings + 0x24) * 32 + 0x10);
        first = D_L13_001FE580[*(int *)(settings + 0x28)];
        other = D_L13_001FE580[*(int *)(settings + 0x2C)];
        *(short *)(settings + 0x34) = 1;
        for (i = 0; i < first->count; i++) {
            func_L00_00341FA8(route, first->point[i], projected, &segment, &fraction, 0, 20.0f, 5.0f, 0.0f);
            first->point[i][0] = *(float *)((char *)first + ((i) << 4) + 28);
            *(float *)((char *)first + ((i) << 4) + 28) = (float)segment;
        }
        previous_index = first->count - 1;
        for (i = 0; i < first->count; i++) {
            previous = func_00283CF0(*(float *)((char *)first + ((previous_index) << 4) + 28));
            current = func_00283CF0(*(float *)((char *)first + ((i) << 4) + 28));
            steps = current - previous;
            if (steps < 0) steps += route->count;
            fraction = 0.0f;
            for (j = 0; j < steps; j++)
                fraction += *(float *)((char *)route + (((previous + i) % route->count) << 4) + 28);
            *(float *)((char *)first + ((i) << 4) + 20) = fraction;
            previous_index = i;
        }
        for (i = 0; i < other->count; i++) {
            func_L00_00341FA8(other_route, other->point[i], projected, &segment, &fraction, 0, 20.0f, 5.0f, 0.0f);
            other->point[i][0] = *(float *)((char *)other + ((i) << 4) + 28);
            *(float *)((char *)other + ((i) << 4) + 28) = (float)segment;
        }
        previous_index = other->count - 1;
        for (i = 0; i < other->count; i++) {
            previous = func_00283CF0(*(float *)((char *)other + ((previous_index) << 4) + 28));
            current = func_00283CF0(*(float *)((char *)other + ((i) << 4) + 28));
            steps = current - previous;
            if (steps < 0) steps += other_route->count;
            fraction = 0.0f;
            for (j = 0; j < steps; j++)
                fraction += *(float *)((char *)other_route + (((previous + i) % other_route->count) << 4) + 28);
            *(float *)((char *)other + ((i) << 4) + 20) = fraction;
            previous_index = i;
        }
    }
    *(short *)(status + 0xA) = 0;
}
