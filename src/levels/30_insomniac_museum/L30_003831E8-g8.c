#include "common.h"
extern int func_002F5FB0(float);
extern float func_002F4DA0(float);
extern int g_museum_water_current_buffer __attribute__((sda));
extern float g_museum_water_heights[2][24][24];
/* Raises a round bump in the museum water surface around a point. */
void RaiseMuseumHeightFieldDome(int x, int y, float radius, float height) {
    int extent = func_002F5FB0(radius);
    int i,j;
    float rr = 2 * (radius * radius);
    for(j=y-extent;j<=y;j++) {
        for(i=x-extent;i<=x;i++) {
            float d = func_002F4DA0((float)((x-i)*(x-i)+(y-j)*(y-j)));
            float h = height * func_002F4DA0(rr-d*d);
            if(h < g_museum_water_heights[g_museum_water_current_buffer][i][j]) h=g_museum_water_heights[g_museum_water_current_buffer][i][j];
            g_museum_water_heights[g_museum_water_current_buffer][i][j]=h;
            g_museum_water_heights[g_museum_water_current_buffer][x+(x-i)][j]=h;
            g_museum_water_heights[g_museum_water_current_buffer][i][y+(y-j)]=h;
            g_museum_water_heights[g_museum_water_current_buffer][x+(x-i)][y+(y-j)]=h;
        }
    }
}
