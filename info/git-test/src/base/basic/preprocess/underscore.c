/*
 * file_proprcs.c
 *
 *  Created on: Dec 16, 2012
 *      Author: caoj7
 */
#define c_plusplus

#if !defined(c_plusplus)     //equals to #ifndef
#error C++ compiler required
#endif

#define DEBUG

#ifdef DEBUG
#pragma message ("DEBUG IS DEFINED!") //#pragma is used to direct compiler
#endif

#ifndef DEBUG
#error DEBUG IS NOT DEFINED    //#error is reported during compiling phase
#endif

#include<stdio.h>

//#line 100 "newfile.c"  //can change the value of real __LINE__ and __FILE__

#define mkstr(s)  #s        // # is used to add " " to s
#define concat(X,Y) X ## Y  //## is used to concat two identifiers
int main(){
    printf("line = %d, FILE = %s, DATE = %s, TIME = %s\n", __LINE__, __FILE__, __DATE__, __TIME__);
    printf("C standard (__STDC__) = %d\n", __STDC__);
    printf("C hosted (__STDC__) = %d\n", __STDC_HOSTED__);
    printf(mkstr(I like c programming \n));

    int xy = 10;
    printf("xy = %d\n", concat(x,y));

    return 0;
}

