#pragma once


#include <complex>



Color Test(std::complex<double> z, int iterations){
	if(std::real(z)<0){
		return RED;
	}else{
		return BLUE;
	}
	
}


Color Scale(std::complex<double> z, int iterations){
	bool self_intersect = 0;
	
	
	std::complex<double> w(0,0);
	
	
	std::complex<double> *segments = new std::complex<double>[iterations+1];
	
	segments[0] = std::complex<double>(0,0);
	
	for(int i =1; i<iterations+1; i++){
		w += pow(z,i);
		segments[i] = w;
	}
	
	
	//return Color{255*std::arg(w)/(2*PI),255*std::arg(w)/(2*PI),255*std::arg(w)/(2*PI),255};
	
	//return Color{100*abs(w),100*abs(w),100*abs(w),255};
	
	if(std::abs(w) >1.01){
		return RED;
	}else{
		return BLUE;
	}
	
	
}


Color Geo_inter(std::complex<double> z, int iterations){
	bool self_intersect = 0;
	
	
	std::complex<double> w(0,0);
	
	
	std::complex<double> *segments = new std::complex<double>[iterations+1];
	
	segments[0] = std::complex<double>(0,0);
	
	for(int i =1; i<iterations+1; i++){
		w += pow(z,i-1);
		segments[i] = w;
	}
	
	
	std::complex<double> a,b,c;
	
	for(int i=1; i<iterations+1; i++){
		for(int j=i+1; j<iterations+1; j++){
			a = segments[i]-segments[i-1];
			b = segments[j-1]-segments[i-1];
			c = segments[j]-segments[i-1];
			
			a = a*std::conj(a);
			
			if(0 <= std::real(b) && std::real(b) <= std::real(a) ){
				if(0 <= std::real(c) && std::real(c) <= std::real(a)){
					if(std::imag(b)*std::imag(c) <0){
						self_intersect = 1;
					}
				}
			}
			
			
		}
	}
	
	
	if(self_intersect){
		return RED;
	}else{
		return BLUE;
	}
	
	
	
}


Color Geo_inter_mod(std::complex<double> z, int iterations){
	bool self_intersect = 0;
	
	
	std::complex<double> w(0,0);
	
	std::complex<double> x(.5,.5);
	
	
	std::complex<double> *segments = new std::complex<double>[iterations+1];
	
	segments[0] = std::complex<double>(0,0);
	
	for(int i =1; i<iterations+1; i++){
		w += pow(z*x,pow(x,i-1));
		segments[i] = w;
	}
	
	
	std::complex<double> a,b,c;
	
	for(int i=1; i<iterations+1; i++){
		for(int j=i+1; j<iterations+1; j++){
			a = segments[i]-segments[i-1];
			b = segments[j-1]-segments[i-1];
			c = segments[j]-segments[i-1];
			
			a = a*std::conj(a);
			
			if(0 <= std::real(b) && std::real(b) <= std::real(a) ){
				if(0 <= std::real(c) && std::real(c) <= std::real(a)){
					if(std::imag(b)*std::imag(c) <0){
						self_intersect = 1;
					}
				}
			}
			
			
		}
	}
	
	
	if(self_intersect){
		return RED;
	}else{
		return BLUE;
	}
	
	
	
}