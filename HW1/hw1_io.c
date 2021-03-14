/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/                                     


#include <stdio.h>
#include "hw1_io.h"


void write_polynomial3(double a0, double a1, double a2, double a3)
{                                           
int degree=3, i=0;                 /* In this function,my first problem was how to write first coefficient */
char plus='+', minus='-', x='x';  /*First coefficient's condition was different than other coefficients  */
double arr[4];                 /* There were other output problems. For example, output coefficient can not be 1x -1x or 0x */
arr[0]=0;                     /* To write all the coefficient in one algorithm ,I assign zero to arr[0]. */ 
arr[1]=a0;                  /* Assigning zero to arr[0] is gave me the opportunity to print all the coefficients(except a3) in the same for loop */
arr[2]=a1;                         
arr[3]=a2;                                                    
for(i=0;i<3;i++){                  
if(arr[i]==0){                      /* This if block prevents all the 0*x^n conditions */
if(arr[i+1]>0 && arr[i+1]!=1 && i==0)     /*Printing condition for first positive coefficient */
printf("%.1f%c^%d",arr[i+1],x,degree);  
else if(arr[i+1]>0 && arr[i+1]!=1 && i!=0)   /* Printing condition for other positive cofficients */
printf("%c%.1f%c^%d",plus,arr[i+1],x,degree);
else if(arr[i+1]>0 && arr[i+1]==1 && i==0)  /*The prevention of +1x^n condition for first coefficient */
printf("%c^%d",x,degree);
else if(arr[i+1]>0 && arr[i+1]==1 && i!=0)  /*The prevention of +1x^n condition for other coefficients */
printf("%c%.1f%c^%d",plus,arr[i+1],x,degree);
if(arr[i+1]<0 && arr[i+1]!=-1)            /* The prevention of -1x condition */
printf("%.1f%c^%d",arr[i+1],x,degree);
else if(arr[i+1]<0 && arr[i+1]==-1)          
printf("%c%c^%d",minus,x,degree);      /* print -x instead of -1x */
degree--;
}                         /* If the previous coefficient is not 0,Else block starts printing */ 
else{                    /* This else block's printing conditions are the same with  if-block.*/
if(arr[i+1]>0 && arr[i+1]!=1)                
printf("%c%.1f%c^%d",plus,arr[i+1],x,degree);
else if(arr[i+1]>0 && arr[i+1]==1)
printf("%c%c^%d",plus,x,degree);
else if(arr[i+1]<0 && arr[i+1]!=-1)
printf("%.1f%c^%d",arr[i+1],x,degree);
else if(arr[i+1]<0 && arr[i+1]==-1)
printf("%c%c^%d",minus,x,degree);
degree--;
}
}
if(a3>0)                  /*The Coefficient of constant did not implement in the algorithm, I could've implemented but the output would be C*x^0 */
printf("%c%.1f",plus,a3);/* I figured it out the appropriate output condition of constant a3 by using one simple if-else block */
else if(a3<0)
printf("%.1f",a3);
else
printf(" ");
puts("\n");
}

void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{                                      /* I used exactly the same algorithm in this function but i made small changes */    
int degree=4, i=0;                    /* The diffrences between these functions are size of array(coefficient number increased), */
char plus='+', minus='-', x='x';     /* stop condition in the for loop, and the new constant element(a4) */
double arr[5];                      /*This algorithm can be implemented to write all degree Polynomials.(for example degree-20 degree 30)*/
arr[0]=0;                                   
arr[1]=a0;                                       
arr[2]=a1;
arr[3]=a2;
arr[4]=a3;
for(i=0;i<4;i++){                     
if(arr[i]==0){                        
if(arr[i+1]>0 && arr[i+1]!=1 && i==0)
printf("%.1f%c^%d",arr[i+1],x,degree);
else if(arr[i+1]>0 && arr[i+1]!=1 && i!=0)
printf("%c%.1f%c^%d",plus,arr[i+1],x,degree);
else if(arr[i+1]>0 && arr[i+1]==1 && i==0)
printf("%c^%d",x,degree);
else if(arr[i+1]>0 && arr[i+1]==1 && i!=0)
printf("%c%c^%d",plus,x,degree);
if(arr[i+1]<0 && arr[i+1]!=-1)
printf("%.1f%c^%d",arr[i+1],x,degree);
else if(arr[i+1]<0 && arr[i+1]==-1)
printf("%c%c^%d",minus,x,degree);
degree--;
}
else{
if(arr[i+1]>0 && arr[i+1]!=1)
printf("%c%.1f%c^%d",plus,arr[i+1],x,degree);
else if(arr[i+1]>0 && arr[i+1]==1)
printf("%c%c^%d",plus,x,degree);
else if(arr[i+1]<0 && arr[i+1]!=-1)
printf("%.1f%c^%d",arr[i+1],x,degree);
else if(arr[i+1]<0 && arr[i+1]==-1)
printf("%c%c^%d",minus,x,degree);
degree--;
}
}
if(a4>0)
printf("%c%.1f",plus,a4);
else if(a4<0)
printf("%.1f",a4);
else
printf(" ");
puts("\n");
}



















