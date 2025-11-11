#include <iosteram>
#include <vector>

using namespase std;

typedef float real;

real function(real x){
	if((abs(x*x-5) > 1e-6) && (abs(x) > 1e-6)){
		return 1/x/sqrt(5 - x*x);
	}
	else:
		exit(1);
}

real integrate_rect_right(const vector <real>& y, real h){
	size_t N = y.size();
	real int_sum = 0.0;
	for(size_t i = 1; i < N; i++){
		int_sum += y[i]*h;
	}
	return intn_sum;
}
real integrate_rect_left(const vector <real>& x, const vector <real>& y){
	size_t N = y.size();
	real int_sum = 0.0;
	for(size_t i = 0; i < N-1; i++){
		int_sum += y[i]*h;
	}
	return int_sum;
}
real integrate_rect_center(const vector <real>& x, const vector <real>& y){
	size_t N = y.size();
	real int_sum = 0.0;
	for(size_t i = 1; i < N-1; i+=2){
		int_sum += y[i]*2*h;
	}
	if(N % 2 = 0){
		int_sum += (y[N-2] + y[N-1])/2.0*h;
	}
	return int_sum;
}

real integrate_trapezoid(const vector <real>& x, const vector <real>& y){
	size_t N = y.size();
	real int_sum = 0.0;
	for(size_t i = 0; i < N-1; i++){
		int_sum += (y[i] + y[i+1])/2.0*h;
	}
	return int_sum;
}

real integrate_simpson(const vector <real>& x, const vector <real>& y){

}

int main(){

}
