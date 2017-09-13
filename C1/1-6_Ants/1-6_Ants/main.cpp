//
//  main.cpp
//  1-6_Ants
//
//  Created by jameskrauser on 2017/9/13.
//  Copyright © 2017年 jameskrauser. All rights reserved.
//  page 017
//

#include <iostream>
using namespace std;
const int max_n = 20;

int  Long_stick = 10 ;
int  n =   3 ; //count of ants
int x[max_n] = { 2 , 6 , 7 }; // original position


int main(int argc, const char * argv[]) {
    
    int min_t = 0 ;
    for (int i = 0 ; i < n ; i++ ) {
        min_t = max( min_t , min(x[i] , Long_stick - x[i]) );
    }
    
    int max_t = 0;
    for ( int i = 0 ; i < n ;  i++  ) {
        max_t  = max( max_t , max( x[i] , Long_stick - x[i] )  );
    }
    printf("min_time=%d  \nmax_time=%d \n" , min_t, max_t);
    
    return 0;
}
