#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <math.h>

std::vector < std::vector < std::string >> signal_status(100000, std::vector <std::string>(100)); //signal_statusのデータを格納する変数
int countcolumns[1000000] = { 0 }; //countcolumns[i]=jのとき、i行目の列数はj

int main() {

    //signal_status読み込み
    std::ifstream ifs("signal_status.txt");
    std::string str = "";

    if (!ifs) {
        std::cout << "Error! File can not be opened" << std::endl;
        return -1;
    }

    int i = 0;
    int j = 0;

    while (getline(ifs, str)) {
        std::string tmp = "";
        std::istringstream stream(str);

        while (getline(stream, tmp, ',')) {
            signal_status[i][j] = tmp;
            j++;
        }

        countcolumns[i] = j - 1;

        j = 0;
        i++;
    }

    std::ofstream output("NLOS_LOS percentage.txt");

    int k = 0;
    int l = 0;
    int NLOS = 0;
    int LOS = 0;
    double per = 0.0;

    for (k = 0; k < 23767; k++) {

        NLOS = 0;
        LOS = 0;

        for (l = 2; l < countcolumns[k] + 1; l = l + 2) {

            /*if (l == 0) {
                output << signal_status[k][0] << ",";
            }*/
            if (countcolumns[k] / 2 <= 6) {

               if (stoi(signal_status[k][l]) == 0) {
                   NLOS++;
               }
               else if(stoi(signal_status[k][l]) == 1) {
                   LOS++;
               }

            }

            per = (double)NLOS / ((double)LOS + (double)NLOS);
        }
        if (countcolumns[k] / 2 <= 6 && NLOS != 0) {
            output << signal_status[k][0] << ",";
            output << NLOS << ",";
            output << LOS << ",";
            output << per << std::endl;
        }
        if (countcolumns[k] / 2 <= 6 && NLOS == 0) {
            output << signal_status[k][0] << ",";
            output << NLOS << ",";
            output << LOS << ",";
            output << 0 << std::endl;
        }

     }

    return 0;

}