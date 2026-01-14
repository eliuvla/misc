#pragma once


#include <complex>
#include "function.h"

struct Geometric{
	int width = 800;
	int height = 800;
	Image result = GenImageColor(width, height, BLACK);
	Texture2D texture;
	
	int iterations = 30;

	Color (* Intersect)(std::complex<double>, int) = Geo_inter_mod; //Geo_inter;
	


	
	void Init();
	void Draw();


};	

void Geometric::Init(){
	
	std::complex<double> w;
	float scale = 4;
	
	Color color;
	
	for(int i=0; i<width; i++){
		
		for(int j=0; j<height; j++){
			w = std::complex<double> (scale*2*(i/float(width)-.5), scale*2*(j/float(height)-.5));
			
			color = Intersect(w, iterations);
			ImageDrawPixel(&result, i, j,color);
			
			
		}
		
		
	}
	
	
	texture = LoadTextureFromImage(result);
	
	
}



void Geometric::Draw(){
	
	DrawTexture(texture, 0, 0, WHITE);
	
}