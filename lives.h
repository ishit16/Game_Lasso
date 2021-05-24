#ifndef __LIVES_H__
#define __LIVES_H__
#include <simplecpp>


// here i use the fact that all prime numbers are of the form 6k+1 or 6k-1;
// increases the program efficiency
//check all such numbers till sqrt(n)
// only after reaching prime number of coins player gets an extra life
bool primes(int n){
    if(n%2==0 || n%3==0 || n==1){
        return false;
        }
    for(int i=5;i*i<=n;i+=6){
        if(n%i==0 || n%(i+2)==0){
            return false;
            }
        }
    return true;

}
#endif
