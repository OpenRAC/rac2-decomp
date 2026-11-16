#include "include_asm.h"
#include "names.h"

typedef void *V;

extern int g_hero_height_zone_active;

extern void vec_copy_helper_a(V);

extern void cam_compute_view_direction(V,V,int);

/* Clears the vector, or computes it from the object when the global switch is set. */
void vec_clear_or_compute(V object,V vector) {
 if(g_hero_height_zone_active==0) {
  vec_copy_helper_a(vector);
  return;
 }
 cam_compute_view_direction(object,vector,1);
}
