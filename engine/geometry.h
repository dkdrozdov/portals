#include "store.h"

typedef struct segment{
	double x[2];
	double y[2];
}SEGMENT;

bool segments_collision(SEGMENT s1, SEGMENT s2, double *crosspoint);
double segment_length(SEGMENT v);
SEGMENT change_vector_length(SEGMENT v, double l);
bool circle_segment_collision(SEGMENT s, double cx, double cy, double r);
bool circles_collision(double cx1, double cy1, double cr1, double cx2, double cy2, double cr2);

