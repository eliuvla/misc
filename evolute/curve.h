#pragma once


#include "functions.h"
#include "raylib.h"

struct Curve{
	Color color = {100,100,100,100};
	int num_points = 1000;
	Vector2 * points;
	float a = 0;
	float b = 100;

	Vector2 (* curve_parametrization)(float t) = test_curve;

	void Init(Color c, int num_points_i);
	void Update();
	void Draw();
	Curve MakeEvolute();

};


void Curve::Init(Color c, int num_points_i){
	float t = 0;
	color = c;
	num_points = num_points_i;
	points = new Vector2[num_points];
	for(int i =0; i<num_points; i++){
		t =  (b-a)*((float) i/num_points)+a;
		points[i] = curve_parametrization(t);
	}
}

void Curve::Draw(){
	for(int i=0; i<num_points-1; i++){
		//DrawLineEx(points[i], points[i+1], 2,color); 
	}

	DrawLineStrip(points, num_points, color); 
}


Curve Curve::MakeEvolute(){
	Curve evolute;

	evolute.Init(color, num_points);

	


	return evolute;

}