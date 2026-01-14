#pragma once

#include <complex>

#include "functions.h"

struct DiscreteDynamic{
	int width = 2000;
	int height = 2000;
	int max_points = 40000;
	//std::complex<double> initial_position(1,1);
	int iterations = 1;
	float max_criterio = 10;
	float zoom = width/8;
	
	
	std::complex<double> (* dinamic)(std::complex<double>, int) = dinamic_test;
	
	Image fractal = GenImageColor(width,height, BLACK); 
	Texture2D fractal_texture;


	
	void Init();
	void Update();
	void Draw();
	void GenerateFractal();
	void DrawFractal();
	void DrawFractalS2();
	
};



void DiscreteDynamic::DrawFractalS2(){
	Vector2 p,p2,p3,p4;
	Vector3 v,v2,v3,v4;
	
	for(int i=1; i<width; i++){
		for(int j =1; j<height; j++){
			p = (Vector2){(i-width/2)/zoom,(j-height/2)/zoom };
			p2 = (Vector2){(i-1-width/2)/zoom,(j-height/2)/zoom };
			p3 = (Vector2){(i-width/2)/zoom,(j-1-height/2)/zoom };
			p4 = (Vector2){(i-1-width/2)/zoom,(j-1-height/2)/zoom };
			
			v.x = (2*p.x)/(1+p.x*p.x+p.y*p.y);
			v.y = (2*p.y)/(1+p.x*p.x+p.y*p.y);
			v.z = (-1+p.x*p.x+p.y*p.y)/(1+p.x*p.x+p.y*p.y);
			
			v3.x = (2*p3.x)/(1+p3.x*p3.x+p3.y*p3.y);
			v3.y = (2*p3.y)/(1+p3.x*p3.x+p3.y*p3.y);
			v3.z = (-1+p3.x*p3.x+p3.y*p3.y)/(1+p3.x*p3.x+p3.y*p3.y);
			
			v2.x = (2*p2.x)/(1+p2.x*p2.x+p2.y*p2.y);
			v2.y = (2*p2.y)/(1+p2.x*p2.x+p2.y*p2.y);
			v2.z = (-1+p2.x*p2.x+p2.y*p2.y)/(1+p2.x*p2.x+p2.y*p2.y);
			
			v4.x = (2*p4.x)/(1+p4.x*p4.x+p4.y*p4.y);
			v4.y = (2*p4.y)/(1+p4.x*p4.x+p4.y*p4.y);
			v4.z = (-1+p4.x*p4.x+p4.y*p4.y)/(1+p4.x*p4.x+p4.y*p4.y);
			
			
			
			if(GetImageColor(fractal, i, j).g != 0){
				DrawTriangle3D(v3, v2, v, GetImageColor(fractal, i, j));
				DrawTriangle3D(v2, v3, v4, GetImageColor(fractal, i, j));
			}
			
			    
			
			//DrawPoint3D(v, GetImageColor(fractal, i, j) );
			//DrawCubeWires(v,.01,.01,.01, GetImageColor(fractal, i, j)); 
			//DrawSphere(v, .10, GetImageColor(fractal, i, j));
			
		}
	}
	
	//DrawPoint3D(Vector3 position, Color color);
	
}

void DiscreteDynamic::Update(){
	iterations += 1;
	GenerateFractal();
	
}



void DiscreteDynamic::GenerateFractal(){
	
	UnloadTexture(fractal_texture); //ver si la necesito unloadearla ??
	
	std::complex<double> z(0,0);
	std::complex<double> w(0,0);
	
	for(int i = 0; i<width; i++){
		for(int j=0; j<height; j++){
			
			z = std::complex<double> ((i-width/2)/zoom,(j-height/2)/zoom);
			
			w = dinamic_test(z,iterations);
			
			if(abs(w)>max_criterio){
				ImageDrawPixel(&fractal, i, j, (Color){0,0,0,255});
			}else{
				ImageDrawPixel(&fractal, i, j, (Color){0,255,0,255});
			}
			
			
			
		}
		
	}
	fractal_texture = LoadTextureFromImage(fractal);
}


void DiscreteDynamic::DrawFractal(){
	DrawTexture(fractal_texture, 0, 0, WHITE);
}


void DiscreteDynamic::Init(){
	GenerateFractal();
	
}