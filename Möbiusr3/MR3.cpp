#include <cmath>

#include "raylib.h"
#include "rcamera.h"

#include "flow.h"


int main(void)
{
    const int screenWidth = 1366;
    const int screenHeight = 768;
    int mode = 0;
	
	bool pause = 1;


	//SetConfigFlags(FLAG_VSYNC_HINT|FLAG_MSAA_4X_HINT); 

    SetConfigFlags(FLAG_VSYNC_HINT); 

	InitWindow(screenWidth, screenHeight, "Möbius en R3");
	Camera camera = { 0 };
	camera.position = (Vector3){0.0f, 0.0f, 0.0f };    // Camera position
	camera.target = (Vector3){ 1.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = (Vector3){ 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    
    MaximizeWindow();
    //ToggleFullscreen();
	
	Vector3 v;
	v = (Vector3){10,10,10};
	
	v = inversion(v);
	
	printf("%f %f %f  :)" , v.x,v.y,v.z);


	Flow flujo;
	flujo.Init();

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
                
        
        if (IsKeyPressed(KEY_ZERO)){
            mode = 0;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }
        
        if(IsKeyPressed(KEY_ONE)){
            mode = 1;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        }
        
        if(IsKeyPressed(KEY_TWO)){
            mode = 2;
            camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
            
        }
		
		if(IsKeyPressed(KEY_P)){
			pause = !pause;
		}
        
        
        if(mode == 0){
            UpdateCamera(&camera, CAMERA_FREE);
        }
        
        
        if(mode == 1){
            //camera.position = (Vector3){positions[MAX_POINTS-100].x+x,positions[MAX_POINTS-100].y+y,positions[MAX_POINTS-100].z+z};
            //camera.target = positions[MAX_POINTS-1];
            
        }
        if(mode == 2){
            camera.position = (Vector3){50*cos(GetTime()),50*sin(GetTime()),50};
            camera.target = Vector3{0,0,20};
        }
		
		
		if(pause == 0){
			flujo.Update();
		}
		
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

				//flujo.Draw();
				//flujo.DrawCampo();
				flujo.DrawDust();
				
				DrawLine3D(Vector3{0,0,0}, Vector3{10,0,0}, RED);
				DrawLine3D(Vector3{0,0,0}, Vector3{0,10,0}, GREEN);
				DrawLine3D(Vector3{0,0,0}, Vector3{0,0,10}, BLUE);				
				
				DrawSphere(Vector3{1,0,0}, .1, (Color){100,100,100,100}); 
				


            EndMode3D();



            
            // Draw info boxes

            /*
            DrawRectangle(600, 5, 195, 100, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines(600, 5, 195, 100, BLUE);

            DrawText("Camera status:", 610, 15, 10, BLACK);
            DrawText(TextFormat("- fov: %f", camera.fovy), 610, 30, 10, BLACK);
            DrawText(TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, BLACK);
            DrawText(TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 75, 10, BLACK);
            DrawText(TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, BLACK);
            
            DrawFPS(10, 10);
            */
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
