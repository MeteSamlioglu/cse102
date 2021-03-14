/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


#include <stdio.h>


#include "hw1_lib.h"
#include "hw1_io.h"



/*
** Testing root finding..
**
*/
void test_root_finder3() 
{
	double root_known = 1.0;
	double root_found;
	root_found = root3(1.2, 1.0, -1.0, -1.2, root_known-0.1, root_known+0.1);
	printf("Ground truth root: %f vs found root: %f\n", root_known, root_found);
}



/*
** main function for testing the functions...
**
*/
int main(void) {
test_root_finder3();
/*
printf("The Numeric Integral result of degree 3 polynomial is %f\n",integral3(1,10,-5,-10,0,5,150));                                          
printf("\n");
printf("The Numeric Integral result of degree 4 polynomial is %f\n",integral4(4,1,10,-5,-10,0,5,150));                                  
printf("\n\n%f",root4(2,3,-11,-9,15,-2.3,-2.6));	                    
printf("\n%f\n",root3(2,-1,-7,2,1,3));
printf("\n");
write_polynomial4(4,2,-2,3,-5); 
printf("\n");
write_polynomial3(0,0,-1,-3); 
printf("\n");
write_polynomial3(1,-1,1,0); 
printf("\n");
write_polynomial4(4,0,0,-1,-2);
*/

	return(0);
} /* end main */

/* //I've tested all the functions,They're working as expected    */
/*    ---Function coefficient representation exist in below---- */
/* degree 4 a0x^4+a1x^3+a2x^2+a3x+a4  or degree-3 a0x^3+a1x^2+a2x+a3  */ 
/* Mehmet Mete Şamlıoğlu   200104004093 */