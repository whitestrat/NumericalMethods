#include<stdio.h>

void divided_diff(float *div_diff, float *points, int N){
    float tmp[N-1];
    div_diff[0] = points[N];
    for(int i = 0; i < N-1; i++){
        tmp[i] = (points[i + 1 + N] - points[i+N])/(points[i+1] - points[i]);
    }
    div_diff[1] = tmp[0];
    for(int i = 0; i < N-1; i++){
        printf("%f\n", tmp[i]);
    }
    for(int i = 2; i < N; i++){    //порядок разности
        for(int j = 0; j < N - i; j++){ //перебор элементов
            tmp[j] = (tmp[j+1] - tmp[j])/(points[i+j] - points[j]);
        }
        div_diff[i] = tmp[0];
    }
   //for(int i = 0; i < N-1; i++){
        //printf("%.2f ", tmp[i]);
    //}
    //printf("\n");

}

int main(){
    float p[6];
    p[0] = 0; p[1] = 1; p[2] = 2; p[3] = 1; p[4] = 0; p[5] = 1;
    float d[3];
    divided_diff(d, p, 3);
    printf("\n");
    for(int i = 0; i < 3; i++){
        printf("%f\n", d[i]);
    }
}