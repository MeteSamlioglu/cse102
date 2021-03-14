/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/

#include <stdio.h>
#include<math.h>
#include "hw1_lib.h"
#define ACCURACY 0.0001
#define MAX_ITERATION 1000
double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{
                             /*I used Trapezoidal Rule to calculate Numeric calculation of the integral */
    int i;
    double width=0.0, xi=0.0, sum=0.0, numeric_integral=0.0, y_xe=0.0, y_xs=0.0;  
    width=fabs(xe-xs)/delta;    /*We divided [xs,xe] interval into delta times equal subintervals and 
                            each of width is equal (xe-xs)/delta we assign this value to double width variable*/
                              
    for(i=1;i<delta;i++){                           /* Integral Value = (width/2)*[f(xs)+2*f(x1)+2*f(x2).....+f(xe)]*/ 
     xi=xs+i*width;                               /* In this method f(xs) value and the f(xe) value should not multiply with 2 
                                                       it is the condition that we need to handle */        
    sum+=((a0*xi+a1)*xi+a2)*xi+a3;           /* sum=sum+a0*xi^3+a1*xi^2+a2*xi+a3 */
     }
           
   y_xe=((a0*xe+a1)*xe+a2)*xe+a3; /* f(xe)  */           /* According to Trapezoidal Rule f(xs) and f(xe) should not multiply with 2 */
   y_xs=((a0*xs+a1)*xs+a2)*xs+a3; /* f(xs)  */           /* We handled the condition out of the for-loop */
   numeric_integral=(width/2)*(2*sum+y_xs+y_xe);      /* integral_value=(width/2)(2*sum+f(xe)+f(xs)) */
    
   /* printf("The value of Numeric Integral Calculation is %lf\n", numeric_integral); */
   return numeric_integral;
}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{                               /*If you choose the trapezoidal Rule to calculate Numeric calculation of integral,
                                there is no diffrences between degree-3 polynomial and degree-4 polynomial function. Therefore, I made 
                                small changes in this function.*/
                                   
    
    int i;
    double width=0.0, xi=0.0, sum=0.0, numeric_integral=0.0, y_xe=0.0, y_xs=0.0;  
    width=fabs(xe-xs)/delta;    /*We divided [xs,xe] interval into delta times equal subintervals and 
                              each of width is equal to width variable */
                              
    for(i=1;i<delta;i++){                           /* Integral Value = (width/2)*[f(x0)+2*f(x1)+2*f(x2).....+f(x_delta)]*/
     xi=xs+i*width;                               
                                                     /*  it is the condition that we must handle */
     sum+=(((a0*xi+a1)*xi+a2)*xi+a3)*xi+a4;        /* sum=sum+a0*xi^4+a1*xi^3+a2*xi^2+a3*xi+a4 */ 
     }
     y_xe=(((a0*xe+a1)*xe+a2)*xe+a3)*xe+a4;       
     y_xs=(((a0*xs+a1)*xs+a2)*xs+a3)*xs+a4; 
    numeric_integral=(width/2)*(2*sum+y_xe+y_xs);
   /* printf("The value of Numeric Integral Calculation is %lf\n",numeric_integral);   */
    return numeric_integral; 
}


/* a0*x^3+a1*x^2+a2*x+a3=((a0*x+a1)*x+a2)*x+a3; */
/* I used Bisection Method to find root in given interval */ 
/* This function assume that,there is a root in the given range. */

double root3(double a0, double a1, double a2, double a3, double xs, double xe){
double xm; /*mid point of interval */
double y=0, ym=0; /* assign 0 as a initial value to f(xs) and f(xm) */
int i=0;  
xm=(xs+xe)/2;                  /*Calculation of midpoint of given interval, assign that value to xm */
ym=((a0*xm+a1)*xm+a2)*xm+a3;   /* f(xm)=a0*xm^3+a1*xm^2+a2*xm^1+a3 */
if(ym==0)                      /*If f(xm) is equal to zero, xm is our root in given interval */
return xm;
else{
while((i<=MAX_ITERATION) && (fabs(ym)>ACCURACY)){ /* When |f(xm)>0.0001| and i<=MAX_ITERATION condition is provided, break while loop. */
y=((a0*xs+a1)*xs+a2)*xs+a3;                       /* if f(xm)*f(xs)<0 it shows that there is a root between them */
ym=((a0*xm+a1)*xm+a2)*xm+a3;                      /* Assign xm(middle point value) to xe(upper limit)     */ 
if(ym*y<0){                                       /* else  Assign xm to xs(lower limit) */
xe=xm;                                    /* After this calculation the distance between boundries will decrease in each step of loop*/
}                                         /* When desired accuracy and max iteration number are provided, the return value will be our root */
else{                                           
xs=xm;
}
xm=(xs+xe)/2;                           /*  Find the new mid point of new interval */
i++;                                    /* iteration++ */
}
}
return xm;                 
}

/* I used exactly the same algorithm in this function the only difference is function's prototype(coefficients,degree) */
/* a0*x^4+a1*x^3+a2*x^2+a3*x+a4=(((a0*x+a1)*x+a2)*x+a3)*x+a4 */
double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe){
double xm=0, ym=0.0, y=0.0;
int i=0;
xm=(xs+xe)/2;
ym=(((a0*xm+a1)*xm+a2)*xm+a3)*xm+a4;  /* f(xm)=a0*xm^4+a1*xm^3+a2*xm^2+a3*xm+a4 */
if(ym==0)
return xm;
else{
while((i<=MAX_ITERATION) && (fabs(ym)>ACCURACY)){     
y=(((a0*xs+a1)*xs+a2)*xs+a3)*xs+a4;
ym=(((a0*xm+a1)*xm+a2)*xm+a3)*xm+a4;
if(ym*y<0){   /* if(f(xm)*f(xs)<0) */ 
xe=xm;  
}
else{
xs=xm;
}
xm=(xs+xe)/2;
i++;
}
}
return xm;
}





