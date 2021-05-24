#ifndef __COMPARE_H__
#define __COMPARE_H__
#include <simplecpp>

// This utility function simply calculates the minimum of the three double type values
// This is required in comparison of the distance of three coins so as to catch only one

double minimum_three(double a, double b, double c){
    double arr[10];
    arr[0]=a;
    arr[1]=b;
    arr[2]=c;
    // bubble sort
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                }
            }
        }
    return arr[0];
}
#endif
