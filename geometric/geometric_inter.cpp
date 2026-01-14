

#include "raylib.h"
#include "rlgl.h"



#include <complex>

#include "geometric.h"



int main(){
	
	
	int height = 800;
	int width = 800;
	
	bool pause = 0;
	
	InitWindow(width, height, "Geometric intersection");
	
	//MaximizeWindow();
	
	SetTargetFPS(60);
	
	Geometric geo;
	geo.Init();
	
	
	
	//DisableCursor();
	
	while(!WindowShouldClose()){
		
		
		if(IsKeyPressed(KEY_P)){
			pause = !pause;
		}
		
		if(pause != 1){
			
		}
		
		
		
		
		
		BeginDrawing();
		
			
			ClearBackground(GREEN);
			geo.Draw();
		
		
		EndDrawing();
		
		
		
		
		
		
	}
	
	
	
	
	
	
	CloseWindow();
	
	
	return 0;
	
	
	
	
}