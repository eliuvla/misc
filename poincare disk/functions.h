#pragma once


#include <complex.h>

std::complex<double> dinamic_test(std::complex<double> z);
std::complex<double> mobius_t(std::complex<double> z,std::complex<double> a, std::complex<double> b, std::complex<double>c , std::complex<double> d);

std::complex<double> dinamic_test(std::complex<double> z,std::complex<double> w, std::complex<double> r){


	std::complex<double> a = r;
	std::complex<double> b = -r*w;
	std::complex<double> c = -std::conj(w);
	std::complex<double> d = 1;


	return mobius_t(z,a,b,c,d);


}





std::complex<double> mobius_t(std::complex<double> z,std::complex<double> a, std::complex<double> b, std::complex<double>c , std::complex<double> d){
	
	
	if (c*z+d != std::complex<double>(0,0)){
		z = (a*z+b)/(c*z+d);
	}
	else{
	z = std::complex<double>(0,0);
	}
	return z;


}