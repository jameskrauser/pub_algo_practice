//
//  main.cpp
//  C1-6_draw_lots
//
//  Created by jameskrauser on 2017/9/13.
//  Copyright © 2017年 jameskrauser. All rights reserved.
//  page 019

#include <iostream>
using namespace std;

const int max_n = 5;
int n = 0 ;

void solve1() {
    //time complexity ＝ n的4次方
    
    //int n ;
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

int k[max_n] = {1 , 5 , 7 , 9 , 11  };
int m = 7 ; //sum value

//for solve2
bool binary_search2(int search_value) {
    int left_index = 0 , right_index = n;
    
    while( right_index - left_index >= 1  ) {
        int index = ( right_index + left_index  ) / 2 ;
        if ( k[index]  == search_value ) {
            return true;
        } else if ( k[index] < search_value) {
            left_index = index + 1;
        } else {
            right_index = index ;
        }
    }
    return false;
}

void solve2() {
     //time complexity ＝ n的3次方 logN
    //改用先排序，再尋找
    sort( k , k+n  );// O(nlogn)
    bool f2 = false;
    for( int a = 0 ; a < n ; a++ ) { // o(the 3rd root of N + log N )
        for( int b = 0 ; b < n ; b++    ){
            for( int c = 0 ; c < n ; c++  ) {
                if ( binary_search2( m - k[a] - k[b] - k[c] )   ) {
                    f2 = true;
                }
            }
        }
    }
    if (f2) puts("solve2:Yes");
    else puts("solve2:No");
}

const int max_n3 = 10;
int n3  , m3 , k3[max_n3];
int kk3[max_n3 * max_n3 ];

bool binary_search3( int search_value ) {
    int left_index = 0 ;
    int right_index = n3 * n3;
    
    while( right_index - left_index >= 1 ) {
        int index =(right_index + left_index ) / 2 ;
        if ( kk3[index ] ==  search_value ) {
            return true;
        }else if ( search_value > kk3[index]  ) {
            left_index = index ;
        }else {
            right_index = index + 1 ;
        }
    }
    return false;
}




void solve3() {
    for(int c = 0 ; c < n3 ; c++ ) {
        for( int d = 0 ; d < n3 ; d++ )  {
            kk3[c * n + d] = k[c] + k[d];
        }
    }
    
    sort(kk3 , kk3 + n3 * n3 );
    bool f3 = false;
    for( int a = 0 ; a < n; a++ ) {
        for( int b = 0 ; b < n ; b++ ) {
            if( binary_search3( m3 - k3[a] - k3[b] ) ) {
                f3 = true;
            }
        }
    }
    
    if (f3) puts("solve3: Yes");
    else puts("sovle3:No");
}


int main(int argc, const char * argv[]) {
    
    //solve1();
    
    //solve2();
    
    
    
    
    return 0;
}
