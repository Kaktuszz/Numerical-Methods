// Assume that the determinant A != 0

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void writeToFile(std::vector<long double>& result){
    std::ofstream file("output.csv");
    if (!file) {
        std::cerr << "Error: Cannot open file for writing!" << std::endl;
        return;
    }
    for (size_t i = 0; i < result.size(); i++) {
        file << "x[" << i << "] = " << result[i] << std::endl;
    }
    file.close();
}

int main(){
    // static
    std::vector<std::vector<long double>> a = {{1,9,-5},{-3,-5,-5},{-2,-7,1}};
    std::vector<long double> b = {-32,-10,13};

    // random matrix
    // std::srand(std::time(0));
    // int k = (std::rand() % 30);

    // std::vector<std::vector<long double>> a(k, std::vector<long double>(k));
    // std::vector<long double> b(k);

    //  for (int i = 0; i < k; i++) {
    //     for (int j = 0; j < k; j++) {
    //         a[i][j] = (std::rand() % 20) - 10; // Losowe liczby od -10 do 9
    //     }
    //     b[i] = (std::rand() % 20) - 10;
    // }

    int n = a.size();

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) {
                continue;
            }
            for(int k = 0; k < n; k++) {
                if(k == i) {
                    continue;
                }
                a[j][k] = a[i][i] * a[j][k] - a[j][i] * a[i][k];
            }
            b[j] = a[i][i]*b[j] - a[j][i]*b[i]; 
            a[j][i] = 0;
        }
}

// backsubstitution
std::vector<long double> result(n);
    for(int i = n-1; i>=0; i--){
        result[i] = b[i];
        for(int j = i+1; j<n; j++){
            result[i] -= a[i][j]*result[j];
        }
        result[i] /= a[i][i];
}
    
    writeToFile(result);
    
    return 0;
}
