#include "include_asm.h"
#include "common.h"

/* Per-frame update of an object's controller record (func_L00_0032C638): runs at most once per
   frame counter value, keeps the record's previous result at +0x98, resets the record when a
   frame was skipped, then calls the three update steps with the object's inverse matrix.
   Built with -mno-split-addresses under -G0: the counter is small data, so only the copy reorg
   places in a delay slot is gp-relative. The matrix pointer m is set from the frame-offset-0
   array in a later extended basic block than its first use, so cse cannot turn it back into
   the frame pointer and it lives in a saved register across the calls, as in retail. */
extern void *moby_get_vars_word_18(char *);
extern void timer_update_ticks_per_frame(void);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(char *, char *, int);
extern void vec_negate_and_forward(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void moby_start_attachment(char *, char *);
extern void coll_probe_ground_ahead(char *, char *);
extern void moby_l02_steer_toward_target(char *, char *, void *, void *, void *, void *, void *);
extern void coll_move_resolve_collisions(char *, char *, void *, void *, void *);
extern void coll_update_ground_contact(char *, char *, void *, void *, void *);
extern int g_frame_l02_counter __attribute__((sda));

/* Updates one object's controller record once per frame. It resets the record when frames were skipped, then runs the move, collision and ground-check steps. Returns the record's status flags. */
int coll_update_controller(char *object, void *target, void *input) {
    float inverse[16], direction[4], rotated[12];
    float previous[4], output0[4], output1[4];
    float *m;
    char *data = (char *)moby_get_vars_word_18(object);
    if (!data)
        return 8;
    if (g_frame_l02_counter == *(int *)(data + 0xBC))
        return *(int *)(data + 0x94);
    timer_update_ticks_per_frame();
    matrix_from_basis_rows(inverse, object + 0xC0);
    m = inverse;
    cam_compute_view_direction(object + 0x10, (char *)direction, 0);
    vec_negate_and_forward(object + 0xC0, direction, rotated);
    matrix_mul_vec3(data + 0xA0, data + 0xA0, rotated);
    *(int *)(data + 0x98) = *(int *)(data + 0x94);
    *(int *)(data + 0x94) = 0;
    moby_start_attachment(object, data);
    qcopy_nc(previous, object + 0x10);
    if (g_frame_l02_counter - *(int *)(data + 0xBC) >= 2 || *(int *)(data + 0xBC) == 0) {
        coll_probe_ground_ahead(object, data);
        *(int *)(data + 0x80) = 0;
        *(unsigned char *)(data + 0xEA) = 0xFF;
        *(int *)(data + 0x9C) &= ~2;
        *(int *)(data + 0xB4) = 0;
        qzero_nc(data + 0xA0);
    }
    *(int *)(data + 0xBC) = g_frame_l02_counter;
    moby_l02_steer_toward_target(object, data, target, input, &output0, &output1, m);
    coll_move_resolve_collisions(object, data, &previous, &output1, m);
    coll_update_ground_contact(object, data, target, &previous, m);
    return *(int *)(data + 0x94);
}
