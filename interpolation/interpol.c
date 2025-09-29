#include <stdio.h>
#include <math.h>

float f(float x){
    float tmp = pow(sin(x/5), 2);
    return 0.5*(exp(tmp) - exp(-tmp));
}

void make_points_evenly(float (*f)(float), float a, float b, float* points, int N){
    float dx = (b-a)/(N-1);
    float x;
    for(int i = 0; i < N; i++){
        x = a + i*dx;
        points[i] = x;
        points[N + i] = f(x); 
    }
}

void interpolate_L(float **points, int N){
  

}

void interpolate_N(float **points, int N){


}
int main(){
    int N = 10;
    float a = 0;
    float b = 10;
    float points[2*N];

    printf("%.3f \n", exp(-5.0));

    make_points_evenly(f, a, b, points, N);
    for(int i = 0; i < N; i++){
        printf("%.2f ", points[i]);
    }
    printf("\n");
    for(int i = 0; i < N; i++){
        printf("%.2f ", points[i+N]);
    }
    printf("\n");
    return 0;
}