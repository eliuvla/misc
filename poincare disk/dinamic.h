#pragma once

#include "functions.h"
#include "raylib.h"




struct DiscreteDynamic{
	float radius = 1;
	int max_points = 10000;

	int num_lines = 20;
	int long_line = 10;

	//std::complex<double> initial_position(1,1);
	float size = .01;
	float p = .01;
	float zoom = 1;
	Vector2 offset;

	std::complex<double> w0 = std::complex<double>(0,0);
	std::complex<double> r0 = std::complex<double>(cos(0),sin(0));
	
	
	std::complex<double> (* dinamic)(std::complex<double> z, std::complex<double> w, std::complex<double> r) = dinamic_test;
	std::complex<double>* positions = new std::complex<double>[max_points];

	std::complex<double>** paths = new std::complex<double>*[num_lines];

	Vector2 ** vec_paths = new Vector2 * [num_lines];

	Color* colors = new Color[max_points];
	
	void Init();
	void Update();
	void Draw();
	
};


void DiscreteDynamic::Init(){
	double r;
	double theta;
	for(int i =0; i<max_points; i++){
		r = (double)rand()/RAND_MAX;
		theta = (double)(2*PI)*rand()/RAND_MAX;
		positions[i] = std::polar(r, theta);
	}

	for(int i=0; i<num_lines; i++){
		paths[i] = new std::complex<double>[long_line];
		vec_paths[i] = new Vector2[long_line];
	}

	for(int i=0; i<num_lines; i++){
		r = (double)rand()/RAND_MAX;
		theta = (double)(2*PI)*rand()/RAND_MAX;
		paths[i][0] = std::polar(r, theta);
		for(int j=1; j<long_line; j++){
			paths[i][j] = dinamic(paths[i][j-1],w0,r0);
		}
	}

	for(int i=0; i<num_lines; i++){
		for(int j=1; j<long_line; j++){
			vec_paths[i][j] = {real(paths[i][j]), imag(paths[i][j])};
		}
	}



}

void DiscreteDynamic::Update(){
	double r;
	double theta;
	Vector2 mouse;
	std::complex<double> temp;

	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
		mouse = GetMousePosition();
		temp = std::complex<double>((mouse.x-offset.x)/zoom, (mouse.y-offset.y)/zoom);
		if(std::abs(temp)<1){
			w0 = temp;
		}else{
			r0 = temp/std::abs(temp);
		}
		printf("%f,%f \n",real(w0), imag(w0));

	}

	for(int i = 0; i<max_points; i++){
		positions[i] = dinamic(positions[i],w0,r0);
		if((double)rand()/RAND_MAX<p){
			r = (double)rand()/RAND_MAX;
			theta = (double)(2*PI)*rand()/RAND_MAX;
			positions[i] = std::polar(r, theta);
		}
	}

	for(int i=0; i<num_lines; i++){
		r = (double)rand()/RAND_MAX;
		theta = (double)(2*PI)*rand()/RAND_MAX;
		paths[i][0] = std::polar(r, theta);
		for(int j=1; j<long_line; j++){
			paths[i][j] = dinamic(paths[i][j-1],w0,r0);
		}
	}

	for(int i=0; i<num_lines; i++){
		for(int j=0; j<long_line; j++){
			vec_paths[i][j] = {real(paths[i][j]), imag(paths[i][j])};
		}
	}
	

}

void DiscreteDynamic::Draw(){
	//DrawCircle(0, 0, radius, WHITE);
	DrawCircleSector({0,0}, radius, 0, 360, 200, {0,0,0,200});

	for(int i=0; i<max_points; i++){
		//DrawCircleV({real(positions[i]),imag(positions[i])}, size, GREEN);
		DrawRectangleV({real(positions[i]),imag(positions[i])}, {size,size}, {0,255,0,255*.5*pow(1-std::abs(positions[i]),2)+255*.5});
	}
	for(int i=0; i<num_lines; i++){
		//DrawSplineLinear(vec_paths[i], long_line, size, {255,255,255,100});
	}

	DrawCircleV({real(w0),imag(w0)}, 3*size, {255,0,0,100});
	DrawCircleV({real(r0),imag(r0)}, 3*size, {0,0,255,100});
}