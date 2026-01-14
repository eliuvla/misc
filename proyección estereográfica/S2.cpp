

#include "raylib.h"
#include "rlgl.h"

#include "sphere.h"

int main(){
	
	
	int height = 768;
	int width = 1366;
	
	bool pause = 0;
	
	SetConfigFlags(FLAG_VSYNC_HINT|FLAG_MSAA_4X_HINT); 
	
	InitWindow(width, height, "S2");
	
	MaximizeWindow();
	
	SetTargetFPS(60);
	ToggleFullscreen();
	
	Camera camera = { 0 };
	camera.position = (Vector3){3.0f, 3.0f, 3.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
	camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };     
	camera.fovy = 60.0f;                           
	camera.projection = CAMERA_PERSPECTIVE; //CAMERA_ORTHOGRAPHIC
	
	//rlDisableBackfaceCulling();
	DisableCursor();
	
	Sphere esfera;
	esfera.Init();
	
	while(!WindowShouldClose()){
		
		
		if(IsKeyPressed(KEY_P)){
			pause = !pause;
		}
		
		if(!pause){
			esfera.Update();
		}

		
		UpdateCamera(&camera, CAMERA_FREE);
		
		
		
		BeginDrawing();
		
			
			ClearBackground({255,205,255,255});
			DrawFPS(10,10);

			
			
			BeginMode3D(camera);
			
				
				//DrawLine3D(Vector3{0,0,0}, Vector3{10,0,0}, RED);
				//DrawLine3D(Vector3{0,0,0}, Vector3{0,10,0}, GREEN);
				//DrawLine3D(Vector3{0,0,0}, Vector3{0,0,10}, BLUE);	
				

				esfera.Draw();
				
				
			EndMode3D();
		
		
		EndDrawing();
		
		
		
		
		
		
	}
	
	
	
	
	
	
	CloseWindow();
	
	
	return 0;
	
	
	
	
}