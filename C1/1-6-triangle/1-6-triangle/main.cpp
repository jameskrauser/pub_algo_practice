//
//  main.cpp
//  1-6-triangle
//
//  Created by jameskrauser on 2017/9/13.
//  Copyright © 2017年 jameskrauser. All rights reserved.
//   C1-6

#include <iostream>
using namespace std;

const int max_n = 5;
int n = 4;
int a[max_n] = { 4 , 5 , 10 , 2 , 3 } ;


void solve() {
    int ans = 0 ;
    for (int i = 0 ; i < n ; i++) {
        for(int j = i+1 ; j < n ; j++ ) {
            for(int k = j+1 ; k < n ; k++ ){
                int len = a[i] + a[j] + a[k];
                int ma = max(a[i] , max( a[j] , a[k] ) );
                int rest = len - ma;
                if ( ma < rest ) {
                    ans = max(ans, len );
                }
            }
        }
    }
    printf("ans is %d\n",ans);
}

int main(int argc, const char * argv[]) {
    
    solve();
    printf("---  end  ----");
    return 0;
}
