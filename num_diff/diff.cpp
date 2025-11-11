#include <iostream>
#include <cmath>
using namespace std;

typedef float real;

real f(real x){
	return exp(log(2)*sin(x));
	//return x*x;
}

real r_diff(real x_i, real x_i1, real y_i, real y_i1){
	if(x_i != x_i1){
		return (y_i1 - y_i)/(x_i1 - y_i);
	}
	cout << "Err" << endl;
}

real c_diff(real x_1i, real x_i1, real y_1i, real y_i1){
	if(x_1i != x_i1){
		return (y_i1 - y_1i)/(x_i1 - x_1i);
	}
	cout << "Err" << endl;
}

real uniform_diff(int i, real h, real* y, int N, int order){
	if(order >= N){
		cout << "Sorry, it's impossible" << endl;
		exit(1);
	}
	int low = i - order/2;
	int hight = i + (order+1)/2 + 1;
	if(hight >= N){
		low = N  - order - 1;
		hight = N;
	}
	if(low < 0){
		low = 0;
		hight = order + 1;
	}
	//cout << low << " : " << hight << endl;
	real ans = 0.0;
	real sum = 0.0;
	real prod = 1.0;
	for(int k = low; k < hight; k++){
		for(int j = low; j < hight; j++){
			if(j == k){continue;}
			for(int l = low; l < hight; l++){
				if((l==k)||(l==j)){continue;}
				prod = prod*((real)(i-l))/((real)(k-l));
			}
			sum = sum + prod/((real) (k-j));
			prod = 1.0;
		}
		ans = ans + y[k]*sum;
		sum = 0.0;
	}
	return ans/h;
}

int main(){
	int N = 20;
	real a = -1.5;
	real b = 1.5;
	real x[N];
	real y[N];
	for(int i = 0; i < N; i++){
		x[i] = a + (b-a)*((real)i / (real) N);
		y[i] = f(x[i]);
		//cout << x[i] << "   " << y[i] << endl;
	}
	real d = uniform_diff(3, (b-a)/((real)N), y, N, 5);
	cout <<x[3] << ": " << d << endl;
}
