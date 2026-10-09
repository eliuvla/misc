
#include <stdlib.h>
#include "raylib.h"

#include "dinamic.h"

int main(){
	
	
	int height = 768;
	int width = 1366;
	
	bool pause = 0;
	SetConfigFlags(FLAG_WINDOW_TOPMOST | FLAG_WINDOW_TRANSPARENT);
	
	InitWindow(width, height, "Poncaire Disk");
	
	SetWindowState(FLAG_WINDOW_UNDECORATED);
	SetWindowState(FLAG_WINDOW_ALWAYS_RUN);

	MaximizeWindow();
	
	SetTargetFPS(60);
	
	
	Camera2D camera = { 0 };
	camera.offset = {(float)width/2,(float) height/2};
	camera.zoom = 300;
	
	//DisableCursor();


	DiscreteDynamic test;
	test.Init();
	test.zoom = camera.zoom;
	test.offset = camera.offset;
	int counter = 0;
	
	while(!WindowShouldClose()){
		
		
		if(IsKeyPressed(KEY_P)){
			pause = !pause;
		}
		
		if(pause != 1){
			test.Update();
		}
		
		counter ++;
		counter = 100;
		
		
		BeginDrawing();
		
			if(counter>=60){
				ClearBackground({0,0,0,0});
				counter = 0;
			}
			
			
			
			BeginMode2D(camera);

			test.Draw();

				
			EndMode2D();
		
			DrawFPS(10,10);
		
		EndDrawing();
		
		
		
		
		
		
	}
	
	
	
	
	
	
	CloseWindow();
	
	
	return 0;
	
	
	
	
}