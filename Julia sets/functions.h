#pragma once

#include <complex>


std::complex<double> dinamic_test(std::complex<double> w, int iterations){
	std::complex<double> u(0,-.8);
	
	for(int i=0; i<iterations; i++){
		w = w*w+u;
		if(abs(w)>100){
			break;
		}
		
	}
	
	
	
	return w;
}