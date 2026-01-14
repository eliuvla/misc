#pragma once

#include <complex>

Vector3 inversion(Vector3 v){
	float x,y,z;
	
	float norm = pow(v.x*v.x+v.y*v.y+v.z*v.z,.5);
	
	if(norm == 0){
		x = v.x;
		y = v.y;
		z = v.z;
	}else{
		x = v.x/(norm*norm);
		y = -v.y/(norm*norm);
		z = v.z/(norm*norm);
		
	}
	
	return (Vector3){x,y,z};
	
	
}

Vector3 rotate(Vector3 v, Vector2 w){
	float x,y,z;
	
	float theta = atan2(w.y,w.x);
	
	x = v.x*cos(theta)-v.y*sin(theta);
	y = v.x*sin(theta)+v.y*cos(theta);
	z = v.z;
	
	return (Vector3){x,y,z};
}


Vector3 mult(Vector3 v, Vector2 w){
	float x,y,z;
		
	float norm = pow(w.x*w.x+w.y*w.y,.5);
		
	x = v.x*norm;
	y = v.y*norm;
	z = v.z*norm;
	
	return (Vector3){x,y,z};
	
	
}

Vector3 add(Vector3 v, Vector2 w){
	float x,y,z;
	
	x = v.x+w.x;
	y = v.y+w.y;
	z = v.z;
	
	return (Vector3){x,y,z};
}











Vector3 mobius_t(Vector3 v, std::complex<double> a, std::complex<double> b, std::complex<double>c , std::complex<double> d){
	Vector3 u;
	Vector2 w;
	
	if(real(c) == 0 && imag(c)==0){
		
		w.x = real( a/d);
		w.y = imag( a/d);
		
		u = rotate(v,w);
		u = mult(u,w);
		
		w.x = real(b/d);
		w.y = imag(b/d);
		
		u = add(u,w);
		
	}else{
		
		w.x = real((c*c)/(c*b-a*d));
		w.y = imag((c*c)/(c*b-a*d));
		
		u = mult(v,w);
		u = rotate(u,w);
		
		w.x = real((c*d)/(c*b-a*d));
		w.y = imag((c*d)/(c*b-a*d));
		
		u = add(u,w);
		
		u = inversion(u);
		
		w.x = real(a/c);
		w.y = imag(a/c);
		
		u = add(u,w);
		
		
	}
	
	
	return u;
}




Vector3 dinamic_m(Vector3 v, float delta){
	Vector3 u;
	Vector2 w;
	float scale = 0;
	
	float x,y,z;
	
	
	
	std::complex<double> e(1,0);
	std::complex<double> f(0,0);
	std::complex<double> h(1,0);
	std::complex<double> i(-1,0);
	
	
	std::complex<double> a(1.01*cos(.05), 1.01*sin(.05));
	std::complex<double> b(0, 0);
	std::complex<double> c(0, 0);
	std::complex<double> d(1, 0);
	
	
	
	u = mobius_t(v, e,f,h,i);
	u = mobius_t(u, a,b,c,d);
	u = mobius_t(u, e,f,h,i);
	
	
	//u.x -= v.x;
	//u.y -= v.y;
	//u.z -= v.z;
	
	
	//x = v.x+delta*u.x;
	//y = v.y+delta*u.y;
	//z = v.z+delta*u.z;
	
	x = u.x;
	y = u.y;
	z = u.z;
	
	u = (Vector3){x,y,z};
	

	
	return u;
	
	
}








Vector3 dinamic_test(Vector3 v, float delta){
	float x,y,z;
	
	x = v.x+delta*(v.y);
	y = v.y+delta*(-v.x+(1-v.x*v.x)*v.y);
	z = v.z;
	

	
	return (Vector3){x,y,z};
}


