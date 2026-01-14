

#include "raylib.h"
#include "rlgl.h"

#include "dynamic.h"


int main(){
	
	
	int height = 768;
	int width = 1366;
	
	bool pause = 0;
	
	InitWindow(width, height, "Julia Set");
	
	MaximizeWindow();
	
	SetTargetFPS(60);
	
	
	DiscreteDynamic test;
	
	test.Init();
	
	Camera camera = { 0 };
	camera.position = (Vector3){2.0f, 2.0f, 0.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
	camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };     
	camera.fovy = 60.0f;                           
	camera.projection = CAMERA_PERSPECTIVE;
	
	rlDisableBackfaceCulling();
	DisableCursor();
	
	while(!WindowShouldClose()){
		
		
		if(IsKeyPressed(KEY_P)){
			pause = !pause;
		}
		
		if(pause != 1){
			test.Update();
		}
		
		UpdateCamera(&camera, CAMERA_FREE);
		
		
		
		BeginDrawing();
		
			
			ClearBackground(BLACK);
			//test.DrawFractal();
			
			
			BeginMode3D(camera);
			
				
				//DrawLine3D(Vector3{0,0,0}, Vector3{10,0,0}, RED);
				//DrawLine3D(Vector3{0,0,0}, Vector3{0,10,0}, GREEN);
				//DrawLine3D(Vector3{0,0,0}, Vector3{0,0,10}, BLUE);	
				
				test.DrawFractalS2();
				
				DrawSphere(Vector3{0,0,0}, 1, {255,255,255,100});
				
			EndMode3D();
		
		
		EndDrawing();
		
		
		
		
		
		
	}
	
	
	
	
	
	
	CloseWindow();
	
	
	return 0;
	
	
	
	
}