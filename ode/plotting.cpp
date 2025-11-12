#include "matplotlibcpp.h"
#include <vector>

namespace plt = matplotlibcpp;

int main() {
    // Создание данных
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {1, 4, 9, 16, 25};
    
    // Построение графика
    plt::plot(x, y);
    plt::title("Пример графика");
    plt::xlabel("X");
    plt::ylabel("Y");
    plt::show();
    
    return 0;
}