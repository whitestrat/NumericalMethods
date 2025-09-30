#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void write_float_array_to_csv(float *array, int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла %s!\n", filename);
        return;
    }
    
    fprintf(file, "Index,Value\n");
    
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d,%.7f\n", i, array[i]);
    }
    
    fclose(file);
    printf("Массив записан в %s\n", filename);
}

float f(float x){
    float tmp = pow(sin(x/5), 2);
    return 0.5*(exp(tmp) - exp(-tmp));
}

void make_points_evenly(float (*f)(float), float a, float b, float* points, int N){
    float dx = (b-a)/(N-1);
    float x;
    for(int i = 0; i < N; i++){
        x = a + ((float) i)*dx;
        points[i] = x;
        points[N + i] = f(x); 
    }
}

void make_points_Chebishev(float (*f)(float), float a, float b, float* points, int N){
    //Tn(x) = cos(n*arccos(x)) = 0 => x = cos(pi/2 * (2k-1)/n); x \in [-1, 1]
    float center = (a+b)/2.0f;
    float width_cof = (b-a)/2.0f;
    for(int i = 1; i <= N; i++){
        float k = (float) (i);
        float n = (float) N;
        points[N - i] = center + cos(M_PI*(2.0f*k - 1.0f)/(2.0f*n))*width_cof;
        points[2*N - i] = f(points[N - i]);
    } 
}

float interpolate_L(float x, float *points, int N){
    float L_x = 0;
    for(int i = 0; i < N; i++){
        float P = 1;
        for(int j = 0; j < N; j++){
            if(i != j){
                P = P * (x - points[j])/(points[i] - points[j]);
            }
        }
    L_x = L_x + points[i+N]*P;
    }
    return L_x;
}

float divided_diff(float *div_diff, float *points, int N){
    float tmp[N-1];
    int tmp_ind = 0;
    for(int i = 0; i < N-1; i++){
        tmp[i] = (points[i + 1 + N] - points[i+N])/(points[i+1] - points[i]);
    }
    div_diff[0] = tmp[0];
    for(int i = 1; i < N; i++){    //порядок разности
        for(int j = 0; j < N - i - 1; j++){ //перебор элементов
            tmp[j] = (tmp[j+1] - tmp[j])/(points[i+j+1] - points[j]);
        }
        div_diff[i] = tmp[0];
    }
   //for(int i = 0; i < N-1; i++){
        //printf("%.2f ", tmp[i]);
    //}
    //printf("\n");

}

float Gorner(float x, float *a, int N){
    float tmp = a[N-1];
    for(int i = N - 2; i >= 0; i--){
        tmp = tmp*x + a[i];
    }
    return tmp;
}

float interpolate_N(float x, float *points, int N){
    float div_diff[N];
    divided_diff(div_diff, points, N);
    return Gorner(x, div_diff, N);
}
int main(){
    int N;
    scanf("%d", &N);
    int Nx = 20;
    float a = 0;
    float b = 10;

    float points[2*N];

    float origin[2*Nx];
    float inter_L[2*Nx];
    float inter_N[2*Nx];
    make_points_evenly(f, a, b, origin, Nx);

    float diff[N-1];

    make_points_Chebishev(f, a, b, points, N);
    divided_diff(diff, points, N);
    for(int i = 0; i < Nx; i++){
        inter_N[i] = origin[i];
        inter_N[N+i] = Gorner(origin[i], diff, N);
    }

    for(int i = 0; i < Nx; i++){
        inter_L[i] = origin[i];
        inter_N[N+i] = interpolate_L(origin[i], points, N);
    }
    
    FILE *file = fopen("Chebishev.csv", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла %s!\n", "Chebishev.csv");
    
    }
    else{
    //fprintf(file, "Point_x,Point_y,Origin_x,Origin_y,Newton_x,Newton_y,Lagr_x,Lagr_y\n");
    
    for(int i = 0; i < N; i++){
        fprintf(file, "%f,%f,%f,%f,%f,%f,%f,%f\n", points[i], points[N+i], origin[i], origin[Nx+i], inter_N[i], inter_N[Nx+i], inter_L[i], inter_L[Nx+i]);
    }

    for(int i = N; i < Nx; i++){ 
        fprintf(file, ",,%f,%f,%f,%f,%f,%f\n", origin[i], origin[Nx+i], inter_N[i], inter_N[Nx+i], inter_L[i], inter_L[Nx+i]);
    }
    
    fclose(file);
    printf("Массив записан в %s\n", "Chebishev.csv");
    }
    //printf("\n");
    //for(int i = 0; i < N; i++){
    //    printf("%.2f ", points[i]);
    //}
    //printf("\n");
    return 0;
}