//
//  main.cpp
//  1-1
//
//  Created by jameskrauser on 2017/9/13.
//  Copyright © 2017年 jameskrauser. All rights reserved.
//
/* 
input: n = 3 , m = 10 , k = { 1 , 3 , 5 }
 
problem:dran lots
time complexity ＝ n的4次方
 
*/

#include <iostream>
using namespace std;
const int max_n = 50;

void solve1() {
    //time complexity ＝ n的4次方
    
    int n ;
    int m ;
    int k [max_n ] ;
    printf("input 2 value ");
    scanf("%d %d", &n , &m );
    for (int i = 0 ; i < n ; i++) {
        printf("input value[%d] " , i);
        scanf("%d" , &k[i]);
    }
    
    bool f = false;
    
    for (int a = 0 ; a < n ; a++ ) {
        for(int b = 0 ; b < n; b++ ) {
            for(int c = 0 ; c < n ; c++ ){
                for(int d = 0 ; d < n ; d++ ){
                    if (k[a] + k[b] + k[c] + k[d] == n ) {
                        f = true;
                    }
                }
            }
        }
    }
    
    if (f) puts ("Yes");
    else puts("no") ;
}



int main(int argc, const char * argv[]) {
    
    solve1();
    
    printf("++++   end of program ++++ ");
    return 0;
}
