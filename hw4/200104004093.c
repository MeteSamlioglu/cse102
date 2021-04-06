#include<stdio.h>
#include<math.h>
#define ACCURACY 5000 
/* -------Declaration of Part 1 functions---------*/
void write_function();
float write_coefficient(float coeff);
/* ----- End of Part 1 function declarations */
/*------Declaration of Part 2 Functions ------ */
void palindrome_armstrong_numbers();
/* -------Declaration of Part 3 functions---------* */
void sum_of_prime_numbers();
/*------------- End of Part 3 function declaration----- */
/* Common function to check input */
double check_input(float number);
int check_integer(float number);
/* --------------------------- */

int main(){
write_function(); /* Part 1 */
printf("\n");
palindrome_armstrong_numbers();/* Part2 */
printf("\n");
sum_of_prime_numbers(); /* Part 3 */
printf("\n");

return 0;
}

/*--------- Part 1 -----------------*/
float write_coefficient(float coeff){
    float check_integer=0.0, decimal_part=0.0, accuracy=0.050;
    int check_decimal_part=0;
    check_integer=fmod(coeff,1);
    if(check_integer==0.00000)       /* Checking given float number is whether integer or not */
    return coeff;
    else{
        decimal_part=fmod(coeff,0.1);
        check_decimal_part=pow(10,5)*decimal_part;  /* Convert decimal part's first 5 digit to make comparission */
        if(fabs(check_decimal_part)<=ACCURACY){     /*Comparing float numbers in if statment is not give the true outputs*/
            if(coeff>0)                            /* Therfore,I converted decimal part into an integer variable to get correct inputs */
                coeff-=decimal_part;
            else if(coeff<0)
                coeff+=fabs(decimal_part);
        
        }
        else if(fabs(check_decimal_part)>ACCURACY){
            if(coeff>0)
            {
                coeff-=decimal_part;
                coeff+=0.1;
            }
            else if(coeff<0){
                coeff+=fabs(decimal_part);
                coeff+=-0.1;
            }
        }
        
        return coeff;
    }             
}

void write_function(){
    float i=0;
    float coeff_count=0, counter=0;
    float n, coeff, degree;
    char empty='\0'; /* Null char */
    printf("Enter your polynomial [n a_n a_n-1 a_n-2 ... a_0]: ");
    scanf("%f",&n);                       
    degree=n;
    while(1){
       
        scanf("%f",&coeff);
        if(degree>1){
            if(write_coefficient(coeff)>0){
                if(degree==n)
                    if(write_coefficient(coeff)==1)
                        printf("x^%1.f",degree);
                    else
                        printf("%.1fx^%1.f",write_coefficient(coeff),degree);
                else{ /* degree != n(highest power) */                           
                    if(coeff_count==counter){  /*To determine this positive coefficient whether leading coefficient or not*/
                        if(write_coefficient(coeff)==1)           /* 1*x^n condition */
                            printf("x^%1.f",degree);
                        else
                            printf("%.1fx^%1.f",write_coefficient(coeff),degree);
                    }
                    else{                /* Positive coefficient is not leading coefficient.Therefore there must be"+" before the coefficient */
                        if(write_coefficient(coeff)==1)
                            printf("+x^%1.f",degree);
                        else
                            printf("+%.1fx^%1.f",write_coefficient(coeff),degree);
                    }
                }
            }
            else if(write_coefficient(coeff)<0){ /* There is no need to search "leading coefficient condition" for negative coefficients */
                if(write_coefficient(coeff)==-1)  /* -1*x condition */
                    printf("-x^%1.f",degree);  
                else
                    printf("%.1fx^%1.f",write_coefficient(coeff),degree);
            }
            else{         /* To avoid printing 0*x^n */
                printf("%c",empty);
                coeff_count++;
            }
        }
        if(degree==1){ /* To avoid printing x^1  */
            if(write_coefficient(coeff)>0)
                if(degree==n){ /* Highest power condition for x^1*/
                    if(write_coefficient(coeff)==1)  /* To avoid printing 1*x */
                        printf("x");
                    else
                        printf("%.1fx",write_coefficient(coeff));
                }
                else /* Highest power is not 1 */
                {
                    if(coeff_count==counter){  /*To determine the coefficient of x^1 whether leading coefficient or not*/
                        if(write_coefficient(coeff)==1)
                            printf("x");
                        else
                            printf("%.1fx",write_coefficient(coeff));
                    }
                    else{ /* Leading coefficient is not the coefficient of x^1 */
                        if(write_coefficient(coeff)==1)
                            printf("+x");
                        else
                            printf("+%.1fx",write_coefficient(coeff));                
                    }
                }
            else if(write_coefficient(coeff)<0){
                if(write_coefficient(coeff)==-1)    /* No need to search negative coefficient's conditions */
                    printf("-x");
                else
                    printf("%.1fx",write_coefficient(coeff));
            }
            else{                       /* a_n x^1 a_n==0 */
                printf("%c",empty);
                coeff_count++;        
            }
        }
        
        if(degree==0)   /* Constant coefficient condition */
        {
            if(write_coefficient(coeff)>0){
                if(coeff_count==counter)
                    printf("%.1f",write_coefficient(coeff));
                else
                    printf("+%.1f",write_coefficient(coeff));    
            }
            else if(write_coefficient(coeff)<0)
                printf("%.1f",write_coefficient(coeff));
            else
                printf("%c",empty);
            break;
         }
    counter++;  /* it stores the index of coefficient */
    degree--;   /* Degree of coefficients */
    }
}
/*----------------- End of Part 1 --------------*/
/* -----------Part 2 ------------------ */
int check_integer(float number){
    float integer_part=0, res=0;
    integer_part=(int)number;
    res=fabs(number-integer_part);
    if(res==0){ /* given number is integer */
        return 1; 
    }
    else      /* given number is not integer */
        return 0; 

}
double check_input(float number){
    while(1){
    if(scanf("%f",&number)==1){ 
        if(check_integer(number)==1){ /* Check given input is whether integer or not */
            if(number>=0)            /* Check given integer number positive or not */
                break;
            else{
                printf("Error: Input number cannot be negative !\n"); /* Negative input error message */
                printf("Please enter an integer number :");
            }
        }
        else{               /* Float intput Error message */
        printf("Error: Input number cannot be Float!\n");
        printf("Please enter a integer number :");
        }
    }
    else{
        printf("Error : Input number must be Numeric !\n");  /* Char input Error message */
        printf("Please enter an integer number :");
    }
    getchar();
    }

    return number;
}

void palindrome_armstrong_numbers(){
int copy_number, divider, digit=0;
int is_armstrong=0, is_palindrome=0, i=0, armstrong_sum=0, palindrome_num=0, digit_count=0;;
float number;
printf("Please enter an integer number :");
number=check_input(number);
copy_number=(int)number;   /*Before the calculation we're copying our input because after seperation number into digits our input value will be 0 */
while(1){
    divider=copy_number;
    digit=divider%10;
    if(copy_number==0) /* It means that there are no more digits, Therefore break the loop*/
        break;
    copy_number=copy_number/10; /* The way of finding how many digits our input have */
    armstrong_sum+=pow(digit,3); /*Armstrong number calculation */
    digit_count++;               /* To determine how many digits our input have */
}
if(armstrong_sum==(int)number)  /* Armstrong number condition */
    is_armstrong=1;
else
    is_armstrong=0;

copy_number=(int)number;     /* Assign initial number to copy_number again */
for(i=--digit_count;i>=0;i--){
    divider=copy_number;
    digit=divider%10;  /* Take the last digit of number */
        if(copy_number==0)
            break;
    copy_number=copy_number/10;
    palindrome_num+=digit*pow(10,i);   /*Lets assume our number is ABC this expression represents ABC=A*100+B*10+C; */
}
if(palindrome_num==(int)number)        /* Checking calculated number whether equal or not to initial number */
    is_palindrome=1;
else
    is_palindrome=0;
                                              /* Print Statements */ 
if(is_palindrome==1 && is_armstrong==1)      /*If control variable equal to 1 it means that given number provides condition */
    printf("This number is both Palindrome and Armstrong number.");
else if(is_palindrome==1 && is_armstrong==0)
    printf("This number is only Palindrome number.");
else if(is_palindrome==0 && is_armstrong==1)
    printf("This number is only Armstrong number.");
else 
    printf("This number does not satisfy any special cases");
}

/*----------------End of Part2 --------------------*/
/*----------Part 3 ------------- */
void sum_of_prime_numbers(){
    int first_number=0, second_number=0, i=0, j=0;
    int is_prime=0, prime_number_sum=0;
    float num1=0.0, num2=0.0;
    printf("Please enter first integer number : ");
    num1=check_input(num1);   /* Get correct input by calling check_input function */
    printf("Please enter second integer number : ");
    num2=check_input(num2);  /* Get correct input by calling check_input function */
    first_number=(int)num1;  /* Typecasting */
    second_number=(int)num2;
    while(1){
        if(second_number<=first_number){  /* Second number must be bigger than the first number ask for the correct input */
            printf("\nError: the second number must be bigger than the first number !");
            printf("\nPlease enter second integer number : ");
            scanf("%d",&second_number);
        }
        else
            break;
     
    }
    for(i=++first_number;i<second_number;i++){ /* Searching for the prime number in (first_number, second_number) interval */
        is_prime=1;
        for(j=2;j<=i-1;j++){
            if(i%j==0){
                is_prime=0;  /* Number is not a prime number */
                break;
            }
         }
        if(is_prime==1 && i!=1){  /* 1 is not a prime number, I handle this condition */
            prime_number_sum+=i;     /* Addition of prime numbers in given interval */
        }
   }
    printf("Sum of prime numbers between %d and %d : %d",first_number,second_number,prime_number_sum);
}


/* Mehmet Mete Şamlıoğlu   */
/* 200104004093 */