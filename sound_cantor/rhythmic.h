#pragma once





struct Rhythmic{
	Sound kick = LoadSound("resources/meow.mp3");
	Sound clap = LoadSound("resources/gua.mp3");
	
	
	int width = 640;
	int height = 480;
	
	float time = 0;
	int iterations = 4;
	int partition_size = int(pow(3,iterations));
	bool *percusion = new bool[partition_size];
	float *times = new float[partition_size+1];
	
	bool *already_played = new bool[partition_size];
	
	
	float duration = 2.5*pow(3,iterations-2);
	
	int index;
	
	
	Rhythmic();
	void Play();
	void Update();
	void Draw();
	
	
};



Rhythmic::Rhythmic(){
	for(int i = 0; i<partition_size; i++){
		
		times[i] = duration*(float(i)/partition_size);
		already_played[i] = 0;
		
		//printf("%f \n",times[i]);
		
		percusion[i] = 0;
		
		for(int j = 0; j<iterations; j++){
			
			if( int(i/pow(3,j))%3== 1){
				percusion[i] = 1;
				
				//printf("i %d, j %d , cosa %d \n", i, j, int(i/pow(3,j))%3 );
				
			}
			
			
		}
		
	}
	
	times[partition_size] = duration;
	
	
	
	
}



void Rhythmic::Update(){
	time += GetFrameTime();
	
	
	if(time>duration){
		time -= duration;
		
		for(int i = 0; i<partition_size; i++){
			already_played[i] = 0;
		}
		
		
	}
	
	
}


void Rhythmic::Play(){
	
	index = 0;
	
	
	for(int i =0; i<partition_size; i++){
		if(times[i]<=time && time<=times[i+1]){		
			//printf("%f \n", times[i]);
			index = i;
			break;
		}
	}
	
	if(percusion[index] && !already_played[index]){
		//printf("%f \n", times[index]);
		already_played[index] = 1;
		PlaySound(clap);
		
	}
	
	if(!percusion[index] && !already_played[index]){
		already_played[index] = 1;
		PlaySound(kick);
		
		
	}
		
	
}

void Rhythmic::Draw(){
	
	int size = (width+height)/30;
	
	int rad = width/(2*partition_size);
	
	
	Color colores[2];
	colores[0] = GREEN;
	colores[1] = BLUE;
	
	
	DrawRectangleV({0,height/2-size/2}, {width, size}, WHITE);
	DrawCircleV({width*(times[index]/duration)+rad/2,height/2}, rad, RED);
	
	
	for(int i = 0; i<partition_size; i++){
		
		DrawRectangleV({width*(times[i]/duration),height/2}, {2*rad, size}, colores[percusion[i]]);
	}
	
}