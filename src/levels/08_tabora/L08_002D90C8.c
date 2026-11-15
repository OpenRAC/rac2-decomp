#include "include_asm.h"
#include "names.h"

typedef unsigned int ti_word __attribute__((mode(TI)));

typedef float f32;

extern void func_2F9E60(void *, void *, f32);

extern void func_2F9DF0(void *, void *, void *);

extern f32 func_2F9FD0(void *, void *);

extern int *D_L08_001FE7C0[];

extern float vec_distance_xy(void *, void *);

extern float coll_box_max_depth_all(ti_word *, int, float);

extern float coll_box_max_depth_faces(ti_word *, int, float);

extern float coll_box_max_depth_edges(ti_word *, int, float);

extern char D_L08_002A0D00[];

extern char *D_L08_001B2ACC __attribute__((sda));

extern char *D_L08_001B2AD4 __attribute__((sda));

extern char *D_L08_001B2ADC __attribute__((sda));

extern void render_water_grids(void *, int);

extern void water_start_ripple_patch(void *, int);

extern void moby_transform_joint_to_world(void *, int, void *);


/* Sets the object to ease toward a target height and resets its blend to 0.2. */
void moby_set_ease_target_height(float value, float *object) {
    object[29] = 0.2f;
    object[28] = value - object[6];
}

/* Measures how far a point is from one corner of a box and keeps the larger of that and the running minimum. */
f32 coll_box_corner_max_dist(char *point, char *basis, char *origin, f32 minimum, f32 scaleX, f32 scaleY, f32 scaleZ) {
    f32 corner[4];
    f32 scaled[4];
    f32 distance;

    func_2F9E60(scaled, basis, scaleX);
    func_2F9DF0(corner, origin, scaled);
    func_2F9E60(scaled, basis + 0x10, scaleY);
    func_2F9DF0(corner, corner, scaled);
    func_2F9E60(scaled, basis + 0x20, scaleZ);
    func_2F9DF0(corner, corner, scaled);
    distance = func_2F9FD0(point, corner);
    if (minimum < distance) minimum = distance;
    return minimum;
}

/* Checks a point against all 27 corner, edge and face samples of a box and keeps the largest result. */
float coll_box_max_depth_all(ti_word *object, int index, float minimum) {
    char *entry;
    float stepX, stepY, stepZ;

    if (index == -1) return minimum;
    entry = (char *)D_L08_001B2ACC + index * 128;
    for (stepZ = -1.0f; stepZ <= 1.0f; stepZ += 1.0f)
        for (stepY = -1.0f; stepY <= 1.0f; stepY += 1.0f)
            for (stepX = -1.0f; stepX <= 1.0f; stepX += 1.0f)
                minimum = coll_box_corner_max_dist((char *)object, entry, entry + 0x30, minimum, stepX, stepY, stepZ);
    return minimum;
}

/* Checks a point against the six face centres of a box and keeps the largest result. */
float coll_box_max_depth_faces(ti_word *object, int index, float minimum) {
    char *entry;
    float sign;

    if (index == -1) return minimum;
    entry = (char *)D_L08_001B2AD4 + index * 128;
    for (sign = -1.0f; sign <= 1.0f; sign += 2.0f)
        minimum = coll_box_corner_max_dist((char *)object, entry, entry + 0x30, minimum, 0.0f, 0.0f, sign);
    for (sign = -1.0f; sign <= 1.0f; sign += 2.0f)
        minimum = coll_box_corner_max_dist((char *)object, entry, entry + 0x30, minimum, 0.0f, sign, 0.0f);
    for (sign = -1.0f; sign <= 1.0f; sign += 2.0f)
        minimum = coll_box_corner_max_dist((char *)object, entry, entry + 0x30, minimum, sign, 0.0f, 0.0f);
    return minimum;
}

/* Checks a point against the edge samples of a box and keeps the largest result. */
float coll_box_max_depth_edges(ti_word *object, int index, float minimum) {
    char *entry;
    float stepX, stepY, stepZ;

    if (index == -1) return minimum;
    entry = (char *)D_L08_001B2ADC + index * 128;
    for (stepZ = -1.0f; stepZ <= 1.0f; stepZ += 1.0f) {
        for (stepX = -1.0f; stepX <= 1.0f; stepX += 2.0f)
            minimum = coll_box_corner_max_dist((char *)object, entry, entry + 0x30, minimum, 0.0f, stepX, stepZ);
        for (stepY = -1.0f; stepY <= 1.0f; stepY += 2.0f)
            minimum = coll_box_corner_max_dist((char *)object, entry, entry + 0x30, minimum, stepY, 0.0f, stepZ);
    }
    return minimum;
}

/* Checks a point against a list of planes and keeps the largest result. */
float coll_plane_list_max_depth(ti_word *object, int index, float minimum) {
    int *planeList;
    int i;
    if (index == -1) return minimum;
    planeList = D_L08_001FE7C0[index];

    for (i = 0; i < *planeList; i++) {
        float planeValue = vec_distance_xy((char *)(planeList + 4) + i * 0x10, object);
        if (minimum < planeValue) minimum = planeValue;
    }
    return minimum;
}

/* Works out how deep a point is inside a combination of volumes, using the largest of the four checks. */
float coll_point_depth_in_volumes(ti_word *point, int planeListIndex, int cornerBoxIndex, int faceBoxIndex, int edgeBoxIndex) {
    ti_word pointCopy = *point;
    float depth;
    depth = coll_plane_list_max_depth(&pointCopy, planeListIndex, 0.0f);
    depth = coll_box_max_depth_all(&pointCopy, cornerBoxIndex, depth);
    depth = coll_box_max_depth_faces(&pointCopy, faceBoxIndex, depth);
    return coll_box_max_depth_edges(&pointCopy, edgeBoxIndex, depth);
}

/* func_L08_0032F898 is defined in L08_0032F898.c. */

/* func_L08_003CC750 is defined in L08_003CC750-g8.c. */

/* func_L08_003CCC30 is defined in L08_003CCC30-qcopy.c. */

/* func_L08_003CCD80 is defined in L08_003CCD80-g8.c. */

/* func_L08_003CFE68 is in the sibling file L08_002D90C8-g8.c (it uses $gp addresses). */

/* Starts the shared effect with the level effect table. */
void water_start_effect(void) {
    render_water_grids(D_L08_002A0D00, 7);
}

/* Stops the shared effect with the level effect table. */
void water_stop_effect(void) {
    water_start_ripple_patch(D_L08_002A0D00, 7);
}

/* Moves the object's two attached parts to the object. */
void moby_attach_parts(void *object) {
    void **partList = *(void ***)((char *)object + 0x68);
    if (partList[0]) moby_transform_joint_to_world(object, 0, (char *)partList[0] + 0x10);
    if (partList[1]) moby_transform_joint_to_world(object, 1, (char *)partList[1] + 0x10);
}

/* func_L08_003D00C8 is defined in L08_003D00C8-g8.c. */

/* func_L08_003D0508 is defined in L08_003D0508-qcopy.c. */

/* func_L08_003D2F50 is defined in L08_002D90C8-damage-g8.c. */


/* func_L08_003D3EF8 is in the sibling file L08_002D90C8-g8.c (it uses $gp addresses). */

extern f32 func_3279B8(void);

extern f32 func_3278F0(f32, f32);

extern int func_327898(int, int);

extern f32 func_2FA3C8(f32);

extern f32 func_2FA3E0(f32);

extern void func_347A38(void *, int, int, f32, f32, int);

/* five draws of a random point around the object: a random angle and radius,
   the object's own position added, and the height the driver reads as the
   third component; each point goes to func_347A38 */
/* Throws out several small sparks from random points around the object. */
void part_spawn_sparks_around(void *object) {
    f32 point[4];
    f32 yOffset;
    f32 angle, radius, speedMax, speedMin;
    void *state;
    int lifetime;
    int i;

    state = *(void **)((char *)object + 0x68);
    i = 4;
    do {
        i--;
        angle = func_3279B8();
        radius = func_3278F0(0.0f, 0.8f);
        speedMin = func_3278F0(0.0f, 3.5f);
        speedMax = func_3278F0(3.5f, 8.7f);
        lifetime = func_327898(100, 180);
        point[0] = func_2FA3C8(angle) * radius;
        yOffset = func_2FA3E0(angle) * radius;
        point[2] = 0.0f;
        point[1] = yOffset;
        func_2F9DF0(point, point, (f32 *)((char *)object + 0x10));
        point[2] = *(f32 *)((char *)state + 0x434) + 0.025f;
        func_347A38(point, 0x38002028, 0x2020, speedMin, speedMax, lifetime);
    } while (i >= 0);
}


/* func_L08_003D8290 is defined in L08_003D8290-qcopy.c. */

