#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;
typedef double real;

real func(real x, real y0, real y1){
    return (x*y0 - y1 -x*log(1+x))/(1+x);
}
template<typename function>
void Euler(function f, size_t N, real x_min, real x_max, real y00, real y10, vector <real>& y0, 
                                                                   vector <real>& y1){
    real h = (x_max - x_min)/(N-1);
    
    y0[0] = y00;
    y1[0] = y10;
    
    for(size_t i = 0; i < N-1; i++){
        real x = x_min + i * h;
        
        // Вычисляем производные в текущей точке
        real y2 = f(x, y0[i], y1[i]);
        
        // Обновляем y1
        y1[i+1] = y1[i] + y2 * h;
        
        // Для обновления y0 можно использовать УЖЕ обновленную y1[i+1]
        y0[i+1] = y0[i] + y1[i+1] * h;
    }
}

template<typename function>
void RK(function f, size_t N, real x_min, real x_max, real y00, real y10, vector <real>& y0, 
                                                                   vector <real>& y1){
	real l1, l2, l3, l4;
	real k1, k2, k3, k4;
	real x = x_min; real h = (x_max-x_min)/(N-1);
	y1[0] = y10;
	y0[0] = y00;
	for(size_t i = 0; i < N-1; i++){
		k1 = y1[i];
		l1 = f(x_min, y0[i], y1[i]);
		k2 = y1[i] + h/2.0*l1;
		l2 = f(x_min+h/2.0, y0[i]+h/2.0*k1, y1[i]+h/2.0*l1);
		k3 = y1[i] + h/2.0*l2;
		l3 = f(x_min+h/2.0, y0[i]+h/2.0*k2, y1[i]+h/2.0*l2);
		k4 = y1[i] + h*l3;
		l4 = f(x_min+h, y0[i]+h*k3, y1[i]+h*l3);

		y1[i+1] = y1[i] + h*(l1 + 2*l2 + 2*l3 + l4)/6.0;
		y0[i+1] = y0[i] + h*(k1 + 2*k2 + 2*k3 + k4)/6.0;
		x = x+h;
	}
}

template<typename function>
void Adams(function f, size_t N, real x_min, real x_max, real y00, real y10, 
            vector<real>& y0, vector<real>& y1){
    
    real h = (x_max - x_min)/(N-1);
    
    //Используем метод Рунге-Кутты для получения первых 3 точек
    vector<real> y0_start(3), y1_start(3);
    RK(f, 3, x_min, x_min + 2*h, y00, y10, y0_start, y1_start);
    
    y0[0] = y0_start[0];
    y1[0] = y1_start[0];
    y0[1] = y0_start[1];
    y1[1] = y1_start[1];
    y0[2] = y0_start[2];
    y1[2] = y1_start[2];
    
    vector<real> f_prev0(3), f_prev1(3);
    
    for(int i = 0; i < 3; i++){
        real x = x_min + i * h;
        f_prev0[i] = y1[i];
        f_prev1[i] = f(x, y0[i], y1[i]);
    }
   
    for(size_t i = 2; i < N-1; i++){
        real x = x_min + i * h;
        
        y0[i+1] = y0[i] + h/12.0 * (23*f_prev0[2] - 16*f_prev0[1] + 5*f_prev0[0]);
        y1[i+1] = y1[i] + h/12.0 * (23*f_prev1[2] - 16*f_prev1[1] + 5*f_prev1[0]);
        
        f_prev0[0] = f_prev0[1];
        f_prev0[1] = f_prev0[2];
        f_prev0[2] = y1[i+1];

        f_prev1[0] = f_prev1[1];
        f_prev1[1] = f_prev1[2];
        f_prev1[2] = f(x + h, y0[i+1], y1[i+1]);
     }
}
int main(){
    real x_min = 0.0;
    real x_max = 5.0;
    size_t N = 1000;
    vector <real> y0(N);
    vector <real> y1(N);
    
    ofstream file_e("Euler.csv");
    ofstream file_rk("RK.csv");
    ofstream file_a("Addams.csv");
    Euler(func, N, x_min, x_max, 2, 1, y0, y1);
    file_e << "y0,y1" << endl;
    for(int i = 0; i < N; i++){
        file_e << y0[i] << "," << y1[i] << endl;

    }
    RK(func, N, x_min, x_max, 2, 1, y0, y1);
    file_rk << "y0,y1" << endl;
    for(int i = 0; i < N; i++){
        file_rk << y0[i] << "," << y1[i] << endl;

    }
    Adams(func, N, x_min, x_max, 2, 1, y0, y1);
    file_a << "y0,y1" << endl;
    for(int i = 0; i < N; i++){
        file_a << y0[i] << "," << y1[i] << endl;

    }
    return 0;
}
