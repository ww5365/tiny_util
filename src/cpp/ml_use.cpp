/*
 * ml_use.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: wangwei69
 */

#include <vector>
#include <iostream>
using namespace std;



void cart_tree(){

    vector<float> vec = {-0.68,-0.54,-0.33,0.16,0.56,0.81,-0.01,-0.21,0.09,0.14};



    for(size_t i = 0; i < vec.size() - 1; i++){
        float aver1 = 0.0,aver2 = 0.0;
        float sum1 = 0.0,sum2 = 0;

        float e1 = 0, e2 = 0;

        size_t j;
        for (j = 0;j <= i;j++){
            sum1 += vec[j];
        }
        aver1 = sum1 / j;

        for (j = i + 1; j < vec.size(); j++){
            sum2 += vec[j];
        }

        aver2 = sum2 / (j - i -1);

        for (j = 0; j <= i; j++){
            e1 += ((vec[j] - aver1) * (vec[j] - aver1));
        }

        for (j = i + 1; j < vec.size(); j++){
            e2 += ((vec[j] - aver2) * (vec[j] - aver2));
        }

        cout << "i:" << i << ":" << aver1 << ":" << e1 << ":" << aver2 << ":" << e2 << ":" << e1 + e2 << endl;
    }
}






void ml_use_test(){


    cart_tree();


}
