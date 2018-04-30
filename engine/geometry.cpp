#include "geometry.h"

bool segments_collision(SEGMENT s1, SEGMENT s2, double *crosspoint){
	float s1_x, s1_y, s2_x, s2_y;
	s1_x=s1.x[1]-s1.x[0];
	s1_y=s1.y[1]-s1.y[0];
	s2_x=s2.x[1]-s2.x[0];
	s2_y=s2.y[1]-s2.y[0];

	float s, t;
	s=(-s1_y*(s1.x[0]-s2.x[0])+s1_x*(s1.y[0]-s2.y[0]))/(-s2_x*s1_y+s1_x*s2_y);
	t=(s2_x*(s1.y[0]-s2.y[0])-s2_y*(s1.x[0]-s2.x[0]))/(-s2_x*s1_y+s1_x*s2_y);

	if(s>=0 && s<=1 && t>=0 && t<=1)
	{
		//Collision detected
		crosspoint[0]=s1.x[0]+(t*s1_x);
		crosspoint[1]=s1.y[0]+(t*s1_y);
		return true;
	}

	return false; //No collision
}

double segment_length(SEGMENT v){
	return sqrt((v.x[1]-v.x[0])*(v.x[1]-v.x[0]) + (v.y[1]-v.y[0])*(v.y[1]-v.y[0]));
}

SEGMENT change_vector_length(SEGMENT v, double l){
	double d=segment_length(v);

	v.x[1]-=v.x[0];
	v.y[1]-=v.y[0];

	v.x[1]/=d;
	v.y[1]/=d;

	v.x[1]*=l;
	v.y[1]*=l;

	SEGMENT v2;
	v2.x[0]=v.x[0];
	v2.y[0]=v.y[0];
	v2.x[1]=v.x[1]+v.x[0];
	v2.y[1]=v.y[1]+v.y[0];

	return v2;
}

bool circle_segment_collision(SEGMENT s, double cx, double cy, double r){
	s.x[0]-=cx;
	s.x[1]-=cx;
	s.y[0]-=cy;
	s.y[1]-=cy;

	double dx=s.x[1]-s.x[0];
	double dy=s.y[1]-s.y[0];

	double a=dx*dx+dy*dy;
	double b=2*(s.x[0]*dx+s.y[0]*dy);
	double c=s.x[0]*s.x[0] + s.y[0]*s.y[0] - r*r;

	if(-b<0){
		return (c<0);
	}
	if(-b<(2.*a)){
		return ((4.*a*c - b*b)<0);
	}

	return ((a+b+c)<0);
}

bool circles_collision(double cx1, double cy1, double cr1, double cx2, double cy2, double cr2){
	cx2-=cx1;
	cy2-=cy1;

	double d=sqrt((cx2*cx2)+(cy2*cy2));

	if(((cr1-cr2)<=d)&&((cr1+cr2)>=d)){
		return true;
	}

	return false;
}

