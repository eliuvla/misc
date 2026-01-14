#pragma once


#include <cmath>
#include "raylib.h"

struct Sphere{
	float radius = 1;
	Vector3 center = (Vector3){0,0,1};
	Vector3 ps;
	Vector3 pc;
	Color color = {255,255,180,200};
	
	int orbit_size = 300;
	
	Color ps_color = {255,255,0,255};
	Color pc_color = {0,255,255,255};
	Color line_color = {255,255,255,255};
	float point_radius = .05;
	
	Color plane_color = {255,255,180,255};
	float plane_size = 4;
	
	
	Vector3 * orbit_ps = new Vector3[orbit_size];
	Vector3 * orbit_pc = new Vector3[orbit_size];
	
	int rings = 30;
	int slices = 30;
	int sides = 10;
	
	
	float time;
	float velocity = 1;
	
	void Init();
	void Draw();
	void Update();
	
};




void Sphere::Init(){
	pc = {1,0,0};
	
	ps.x = (2*pc.x)/(1+pc.x*pc.x+pc.y*pc.y);
	ps.y = (2*pc.y)/(1+pc.x*pc.x+pc.y*pc.y);
	ps.z = 1+(-1+pc.x*pc.x+pc.y*pc.y)/(1+pc.x*pc.x+pc.y*pc.y);
	
	for(int i = 0; i<orbit_size; i++){
		orbit_ps[i] = ps;
		orbit_pc[i] = pc;
		
	}
	
	
	
}

void Sphere::Update(){
	time = GetTime();
	
	pc = {cos(time*velocity), 2*sin(time*velocity),0};
	pc = {1/cos(time*velocity), 1/sin(time*velocity),0};
	
	ps.x = (2*pc.x)/(1+pc.x*pc.x+pc.y*pc.y);
	ps.y = (2*pc.y)/(1+pc.x*pc.x+pc.y*pc.y);
	ps.z = 1+(-1+pc.x*pc.x+pc.y*pc.y)/(1+pc.x*pc.x+pc.y*pc.y);
	
	for(int i = 0; i<orbit_size-1; i++){
		orbit_ps[i] = orbit_ps[i+1];
		orbit_pc[i] = orbit_pc[i+1];
		
	}
	
	orbit_ps[orbit_size-1] = ps;
	orbit_pc[orbit_size-1] = pc;
	
	
	
}


void Sphere::Draw(){
	
	Color ipc_color, ips_color;
	ipc_color = pc_color;
	ips_color = ps_color;
	
	
	DrawSphereEx(ps, point_radius, rings, slices, ps_color );
	
	DrawSphereEx(pc, point_radius, rings, slices, pc_color );
	
	//DrawLine3D(ps, {pc.x, pc.y, 0}, line_color); 
	DrawCylinderEx(ps, pc, point_radius/10, point_radius/10, sides, line_color);
	
	
	DrawCircle3D(center, radius+.01, {1,0,0}, 0, RED);
	DrawCircle3D(center, radius+.01, {0,1,0}, 90, GREEN);
	
	
	//DrawSphereWires(center, radius, rings, slices, color); 
	DrawSphereEx(center, radius, rings, slices, color);
	
	
	DrawTriangle3D({plane_size,-plane_size,0}, {plane_size,plane_size,0}, {-plane_size,plane_size,0}, plane_color);
	DrawTriangle3D({-plane_size,plane_size,0}, {-plane_size,-plane_size,0}, {plane_size,-plane_size,0}, plane_color);
	
	for(int i=0; i<orbit_size-1; i++){
		
		ipc_color.a = int( float(255*i/orbit_size));
		ips_color.a = int( float(255*i/orbit_size));
		
		//DrawLine3D(orbit_pc[i], orbit_pc[i+1], ipc_color);
		//DrawLine3D(orbit_ps[i], orbit_ps[i+1], ips_color);
		
		DrawCylinderEx(orbit_pc[i], orbit_pc[i+1], point_radius/4, point_radius/4, sides, ipc_color);
		DrawCylinderEx(orbit_ps[i], orbit_ps[i+1], point_radius/4, point_radius/4, sides, ips_color);
		
	}
	
	
	
	
	
}

