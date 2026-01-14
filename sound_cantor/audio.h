#pragma once


#include <cstdio>
#include <cmath>


float index_time = 0;
int index_frame = 0;


bool percusion[44100];




void SoundMaker(void * buffer, unsigned int frames){
	short * samples = (short *)buffer;
	short max = 32767/2;
	
	
	float sampleRate = 44100.0;
	
	float A4 = 440.0;
	
	int iterations = 5; // 9<log_3(44100) <10 
	
	
	for(unsigned int i = 0; i<frames; i++){
		
		samples[i] = 0;
		
		if(percusion[i] == 1){
			samples[i] = max;
		}
		
		
		//samples[i] = (short) max*sin(A4*index_time*2*PI);
		
		index_frame +=1;
		index_time += (1/sampleRate);
		
		
		if(index_frame>sampleRate){
			index_frame -= 44100;
		}
		
		if(index_time>1){
			index_time -= 1;
		}
		
	}
	
	
	
}




struct Audinamic{
	unsigned int sampleRate;
	unsigned int sampleSize;
	unsigned int channels;
	short * data;
	AudioStream stream; 
	
	int samples_size;
	
	
	
	
	Audinamic();
	void Play();
	
	
};



Audinamic::Audinamic(){
	sampleRate = 44100;
	sampleSize = 16;
	channels = 1;
	samples_size = 512;
	data = new short[samples_size];
	stream = LoadAudioStream(sampleRate, sampleSize, channels);
	
	SetAudioStreamCallback(stream, SoundMaker);
	
	
	for(int i=0; i<44100; i++){
		percusion[i] = 1;
	}
	
	for(int i=0; i<44100; i++){
		for(int j=0; j<1; j++){
			if((i/int(pow(3,j)))%3==1){
				percusion[i] = 0;
			}
		}
	}
	
	
}

void Audinamic::Play(){
	PlayAudioStream(stream); 
	
}



