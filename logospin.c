#include <Math.h>
#include <Graphics.h>
#include <stdio.h>
#include "logospin.h"

int gd = CGAC1, gm;
object_t square2d;
float t;
premath_t theta;
int DEBUG=0;

void main(){
	buildcube();
	initgraph(&gd, &gm, "C:\\TC\\BGI");

	for(t=0; t<=(M_PI*2); t+=(M_PI/128f)){ 
		cleardevice();
		display(&square2d);
		if(DEBUG){printf("theta=%g\n",t);}
		theta.sin_theta=sin(t);
		theta.cos_theta=cos(t);
		rotate_object_around_y_axis(&square2d, &theta);
		getch();
	}
	closegraph();
}

/*
 * {{Cos[θ], 0, Sin[θ]}, {0, 1, 0}, {-Sin[θ], 0, Cos[θ]}} . {{x}, {y}, {z}}
 *  = {{x Cos[θ] + z Sin[θ]}, {y}, {z Cos[θ] - x Sin[θ]}}
 */
void rotate_around_y_axis(struct point *p, struct premath *theta){
	float x,z;

	x = p->x * theta->cos_theta + p->z * theta->sin_theta;
	z = p->z * theta->cos_theta - p->x * theta->sin_theta;

	p->x = x;
	p->z = z;	
}

void rotate_line_around_y_axis(line_t *l, premath_t *theta){
	rotate_around_y_axis(&(l->start), theta); /* parallelizable on a better box :-( */
	rotate_around_y_axis(&(l->finish), theta);
}

void rotate_object_around_y_axis(object_t *obj, premath_t *theta){
	int i=0;
	for (;i<obj->num_lines; ++i){
		rotate_line_around_y_axis(&obj->lines[i],theta);
	}
}

void display(object_t *obj){
	float start_x,start_y,finish_x,finish_y;
	int i=0;
	struct line l;

	for(;i<obj->num_lines; ++i){
		l = obj->lines[i];

/*
		start_x = (l.start.x / l.start.z * rezoom) + recenter_x;
		start_y = (l.start.y / l.start.z * rezoom) + recenter_y;
	
		finish_x = (l.finish.x / l.finish.z * rezoom) + recenter_x;
		finish_y = (l.finish.y / l.finish.z * rezoom) + recenter_y;
*/
		start_x = l.start.x * rezoom + recenter_x;
		start_y = l.start.y * rezoom + recenter_y;
		finish_x = l.finish.x * rezoom + recenter_x;
		finish_y = l.finish.y * rezoom + recenter_y;

		if(DEBUG){
		printf("L SX=%g SY=%g FX=%g FY=%g\n",l.start.x,l.start.y,l.finish.x,l.finish.y);
		printf("L' SX=%g SY=%g FX=%g FY=%g\n",start_x,start_y,finish_x,finish_y);
		}
		else{
			line(start_x,start_y,finish_x,finish_y);
		}
	}
}

void buildcube(){
	point p1={0,0,1};
	point p2={0,10,1};
	point p3={10,0,1};
	point p4={10,10,1};
	point p5={0,10,11};
	point p6={0,0,11};
	point p7={10,10,11};
	point p8={10,0,11};
	line_t l1,l2,l3,l4;
	line_t l5,l6,l7,l8;
	line_t l9,l10,l11,l12;

	l1.start = p1;
	l1.finish = p2;
	l2.start = p1;
	l2.finish = p3;
	l3.start = p4;
	l3.finish = p2;
	l4.start = p4;
	l4.finish = p3;

	l5.start = p2;
	l5.finish = p5;
	l6.start = p1;
	l6.finish = p6;
	l7.start = p4;
	l7.finish = p7;
	l8.start = p3;
	l8.finish = p8;

	l9.start = p5;
	l9.finish = p6;
	l10.start = p5;
	l10.finish = p7;
	l11.start = p6;
	l11.finish = p8;
	l12.start = p8;
	l12.finish = p7;

	square2d.lines[0]=l1;
	square2d.lines[1]=l2;
	square2d.lines[2]=l3;
	square2d.lines[3]=l4;
	square2d.lines[4]=l5;
	square2d.lines[5]=l6;
	square2d.lines[6]=l7;
	square2d.lines[7]=l8;
	square2d.lines[8]=l9;
	square2d.lines[9]=l10;
	square2d.lines[10]=l11;
	square2d.lines[11]=l12;
	square2d.num_lines = 12;
}

/* vim:set ff=dos: */
