#pragma once

#include <complex>
#include "functions.h"




/*

    
positions[0] = INITIAL_POSITION;
float epsilon = EPSILON;
float x,y,z;
float vx,vy,vz,wx,wy,wz;
float module;
int t = 0;


//t = (t+100)%(MAX_POINTS);

vx = positions[MAX_POINTS-1].x-positions[MAX_POINTS-50].x;
vy = positions[MAX_POINTS-1].y-positions[MAX_POINTS-50].y;
vz = positions[MAX_POINTS-1].z-positions[MAX_POINTS-50].z;
wx = -positions[MAX_POINTS-100].x+positions[MAX_POINTS-50].x;
wy = -positions[MAX_POINTS-100].y+positions[MAX_POINTS-50].y;
wz = -positions[MAX_POINTS-100].z+positions[MAX_POINTS-50].z;
x = (vy*wz-wy*vz);
y = (wx*vy-vx*wy);
z = (vx*wy-wx*vy);

module = pow(x*x+y*y+z*z,.5);
x = x/module;
y = y/module;
z = z/module;
		
		
*/


struct Flow{
	int max_points = 40000;
	float delta = .01;
	Vector3 initial_position = {10.0001,10.00001,1.1000};
	int size = 10;
	float scale = .1;
	
	int num_dust = 10000;
	
	float z_value = 0;

	
	//puntero a la dinámica del sistema, pide un vector,delta y regresa otrovector
	Vector3 (* dinamic)(Vector3, float) = dinamic_m;
	
	Vector3* positions = new Vector3[max_points];
    Color* colors = new Color[max_points];
	
	Vector3* dust = new Vector3[num_dust];
	
	Vector3* field_start = new Vector3[size*size*size];
	Vector3* field_end = new Vector3[size*size*size];
	
	void Init();
	void Update();
	void Draw();
	void DrawCampo();
	void DrawDust();
	
	
};

void Flow::DrawDust(){
	
	for(int i = 0; i<num_dust; i++){
		//DrawSphere(dust[i], .1, (Color){100,100,100,100});
		//DrawPoint3D(dust[i], WHITE);
		DrawCube(dust[i], .01, .01, .01, {200,200,200,100});
	}
	
	
}

void Flow::DrawCampo(){
	
	
	//DrawCylinderEx(Vector3{i,j,k}, dinamic(Vector3{i,j,k},delta), .1, 0, 10, (Color){100,100,100,255});
	//DrawLine3D(p_start, p_end,WHITE);
	
	for(int i =0; i<size*size*size; i++){
		//DrawLine3D(field_start[i], field_end[i],(Color){i%255,10,10,255});
		DrawCylinderEx(field_start[i], field_end[i], .01, 0, .1, (Color){100,100,100,255});
		
	}
	
	
}


void Flow::Draw(){
	
	std::complex<double> a(1,0);
	std::complex<double> b(0,0);
	std::complex<double> c(1,0);
	std::complex<double> d(-1,0);
	
	Vector3 p_end;
	Vector3 p_start;

	
	
	for(int i=0; i < max_points-1; i++){
		p_start = positions[i];
		p_end = positions[i+1];
		
		//DrawLine3D(p_start, p_end, colors[i]);
		
		p_start = mobius_t(positions[i],a,b,c,d);
		p_end = mobius_t(positions[i+1],a,b,c,d);
		
		p_start = positions[i];
		p_end = positions[i+1];
		
		//p_start = inversion(p_start);
		//p_end = inversion(p_end);
		
		
		DrawLine3D(p_start, p_end, (Color){100,100,0,255});
		
		//DrawSphere(p_start, .1, (Color){100,100,100,100});
		

		//printf("%f %f %f  :)" , p_start.x,p_start.y,p_start.z);
		//p_start = positions[i];
		//printf("%f %f %f   \n" , p_start.x,p_start.y,p_start.z);

		
		
		
		
		
	}
}


void Flow::Update(){
	
	float distance = 0;
	z_value += .01;
	float dust_scale = 2;
	
	
	for (int i = 0; i < max_points-1; i++)
	{
	    positions[i] = positions[i+1];     
	}
	
	positions[max_points-1] =  dinamic(positions[max_points-2], delta);
	
	
	
	
	for(int i=0; i<num_dust; i++){
		distance = pow(pow( pow(dust[i].x-1,2)+pow(dust[i].y,2)+pow(dust[i].z,2),2),.5);
		
		if(distance < .01){
			float x,y,z;
		
			x = dust_scale*(rand()/float(RAND_MAX))-dust_scale/2+1;
			y = dust_scale*(rand()/float(RAND_MAX))-dust_scale/2;
			//z = 0*1*(rand()/float(RAND_MAX));
			//z = cos(z_value)+1;
			z = dust_scale*(rand()/float(RAND_MAX));
		
			dust[i] = Vector3{x,y,z};
		}
		
	}
	
	for(int i =0; i<num_dust; i++){
		dust[i] = dinamic(dust[i], delta);
	}
	
	
	
	
}

void Flow::Init(){
	std::complex<double> a(1,0);
	std::complex<double> b(0,0);
	std::complex<double> c(1,0);
	std::complex<double> d(-1,0);
	
	positions[0] = initial_position;
	
	for (int i = 1; i < max_points; i++){
		positions[i] = dinamic(positions[i-1], delta);
		colors[i] = (Color){ 255, 100, 150, (255*i)/max_points };
		colors[i] = (Color) {255,255,255,255};
		}
		
		
	
	for(int i = 1; i<size*size*size; i++){
		field_start[i] = (Vector3){scale*(i/(size*size)-size/2),scale*((i/(size))%size -size/2), scale*(i%size)};
		field_end[i] = dinamic(field_start[i],delta);
		//field_start[i] = mobius_t(field_start[i],a,b,c,d);
		//field_end[i] = mobius_t(field_end[i],a,b,c,d);
	}
	
	for(int i=0; i<num_dust; i++){
		float x,y,z;
		
		x = 1;
		y = 0;
		z = 0;
		
		dust[i] = Vector3{x,y,z};
	}
	
	
}












