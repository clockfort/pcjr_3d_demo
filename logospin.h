#include <Math.h>
#include <Graphics.h>

#define recenter_x 160
#define recenter_y 120
#define rezoom 2

typedef struct point {
	float x;
	float y;
	float z;
} point;

typedef struct line {
	struct point start;
	struct point finish;
} line_t;

typedef struct premath {
	float cos_theta;
	float sin_theta;
} premath_t;

typedef struct object {
	line_t lines[32];
	int num_lines;
} object_t;

void buildcube();
void main();
void rotate_around_y_axis(point *p, premath_t *theta);
void rotate_line_around_y_axis(line_t *l, premath_t *theta);
void rotate_object_around_y_axis(object_t *obj, premath_t *theta);
void display(object_t *obj);

/* vim:set ff=dos: */
