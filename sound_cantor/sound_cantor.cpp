#include "raylib.h"


#include <cstdio>


#include "audio.h"
#include "rhythmic.h"




int main(){
	
	int width = 640;
	int height = 480;
	
	
	
	InitWindow(width, height, "sound cantor");
	
	InitAudioDevice();
	
	//Audinamic audio;
	//audio.Play();
	
	Rhythmic ritmo;
	
	ritmo.width = width;
	ritmo.height = height;
	
	
	
	
	
	
	SetTargetFPS(100);
	
	while(!WindowShouldClose()){
		
		ritmo.Update();
		ritmo.Play();
		
		BeginDrawing();
		
			ClearBackground(BLACK);
			DrawFPS(10, 10);
			ritmo.Draw();
		
		EndDrawing();
		
		
		
		
	}
	
	

	CloseAudioDevice();
	
	CloseWindow();
	
}