#include <stdlib.h>
#include <cstdio>
#include "raylib.h"

#include "functions.h"
#include "curve.h"

int main(){
	
	
	int height = 768;
	int width = 1366;
	
	bool pause = 0;
	//SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_TRANSPARENT);
	
	InitWindow(width, height, "Evolute");
	


	MaximizeWindow();
	
	SetTargetFPS(60);
	
	
	Camera2D camera = { 0 };
	camera.offset = {(float)width/2,(float) height/2};
	camera.zoom = 1;
	
	//DisableCursor();

	Curve curva_test;

	curva_test.Init(WHITE, 1000);
	
	
	
	while(!WindowShouldClose()){
		
		
		if(IsKeyPressed(KEY_P)){
			pause = !pause;
		}
		
		if(pause != 1){

		}

		
		
		BeginDrawing();
		
			
			ClearBackground(BLACK);
			
			
			BeginMode2D(camera);
			curva_test.Draw();
			
				
			EndMode2D();
		
			DrawFPS(10,10);
		
		EndDrawing();
		
		
		
		
		
		
	}
	
	
	
	
	
	
	CloseWindow();
	
	
	return 0;
	
	
	
	
}