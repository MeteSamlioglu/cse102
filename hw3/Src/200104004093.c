#include<stdio.h>
#include<math.h>

/* Part 1 functions */
void calculate_fibonacci_sequence();
int check_integer(float num);
/* ------------------ */
/* Part 2 */
int is_perfect_number(float number);
int is_harmonic_divisor_number(float number);
void decide_perfect_harmonic_number();
/* -------------------- */
/* Part 3 */
void difference_max_min ();
/* ---------------------- */
/* Part 4 */
 void bmi_calculation ();
/* --------------------- */

int main(){
calculate_fibonacci_sequence();
decide_perfect_harmonic_number();
difference_max_min ();
bmi_calculation (); 
return 0;
}

/* First part of homework */

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

void calculate_fibonacci_sequence(){
    float num=0.0, control=0;
    int counter=0, i=0;
    unsigned long long int a, b, c;  /* To reach 93.terms of fibonacci sequence, I declare my variables as unsigned long long */
                                     /* Term number can not exceed 93(It may exceed but calculation is going to be incorrect) */
    char end_condition='\0'; /* NULL */

    while(1){
        a=1;
        b=1;
        c=0;
        printf("Please enter a positive integer number : ");
        while(1)         /* Infinite loop */
            {
                if(scanf("%f",&num)==1){ /* Numeric value checking */
                    if(check_integer(num)==1){  /* Integer value checking */
                        if(num>0)               /* Positive value checking */
                            break;           /*We know that given value is Numeric positive integer value.Therefore, break the infinite loop */                     
                        else
                            printf("Please enter a positive number :");
                    }
                    else
                        printf("Please enter an integer number :");
                    
                getchar();    /* To avoid errors caused from repeatedly scanf using */
                }           
                
                else{
                    end_condition=getchar();
                    if(end_condition=='*')  
                        break; /* Break out loop and move to Part 2 functions*/ 
                    else    
                        printf("Please enter Numeric value : ");
                    
                }
            }
            if(end_condition=='*')
                break;
            else{
                counter=(int)num;                 /* converting float to integer */
                if(counter==1)
                    printf("%llu\n",a);
                else if(counter==2)
                    printf("%llu\n%llu\n",a,b);
                else if(counter>2){
                    printf("%llu\n%llu\n",a,b);       /* Printing first two fibonacci term manually */
                    counter-=2;                      /* First two term has already printed. Therefore, we're searching for (counter-2).term */
                    for(i=0;i<counter;i++){
                        c=a+b;                      /* Lets assume a b c variables terms of Fibonacci Sequence elements */
                        printf("%llu\n",c);           /* In each steps c must be equal to sum of previous two terms */
                        a=b;                        /* a is going to take place of b,and b is going to take place of c(sum)*/
                        b=c;
                    }
                }
            }

    }
}

/* End of first part of homework */
/*----- Part 2 ------ */

int is_perfect_number(float number){  /* This function checks given float number is perfect number or not */
    int i=1, sum=0, num=0;
    num=(int)number; /* Type casting */
    printf("Natural Number Divisors: ");
    while(i!=num){  
        if(num%i==0){      /* Finding natural divisors */ 
            printf("%d, ",i);
            sum+=i;        /* Sum of all natural divisors */
        }

        i++;
    }
    printf("%d\n",num); /* (num/num)%=0 there is no need to check this condition*/
    if(sum==num)     /* Perfect Num condition */
        return 1; 
    else
        return 0;    
}

int is_harmonic_divisor_number(float number){
    float denominator=0.0, divisor=0, harmonic_mean=0.0, check_decimal_part=0.0;
    int i=1, num=0;
    num=(int)number; /* Type Casting */
    while(1){
        if(num%i==0){
            denominator+=(float)1/i; /*I separated calculation into two part.In first I calculated denominator part of harmonic mean calculation*/
            divisor++;               /*Natural divisor count */
            if(num==i)              
                break;
        }
    i++;
    }
    harmonic_mean=divisor/denominator; /* harmonic mean calculation */
    check_decimal_part=fmod(harmonic_mean,1); /* Checking harmonic mean value integer or not check_integer function is not enough to determine */
                                     /* If harmonic mean value is an integer it means that given number is Ore Number */
    if(check_decimal_part==0.000000) /* Check decimal part of harmonic mean */
        return 1;                                                             
    else if(check_decimal_part<=0.000002 || check_decimal_part>=0.999999)/*If decimal part of harmonic mean less or equal than 0.000002 */
        return 1;                                                      /* or  bigger or equal than 0.999999 it means that harmonic mean is integer*/
    else 
        return 0;    

}



void decide_perfect_harmonic_number()
{
    float num=0;
    int perfect_number_control=0, ore_number_control=0;      
    char end_condition='\0';
    while(1){                       /* I used the same control algorithm with part 1 because we're searching the same conditions*/
        perfect_number_control=0;
        ore_number_control=0;
        printf("Please enter input number(Natural Number except 0): ");
        while(1)         /* Infinite loop */
            {
                if(scanf("%f",&num)==1){ /* Numeric value checking */
                    if(check_integer(num)==1){  /* Integer value checking */
                        if(num>0)   
                            break;               /* Positive value checking */
                        else                 /*We know that given value is Numeric positive integer value.Therefore, break the infinite loop */                     
                            printf("Please enter a input number(Natural number must be positive) :");
                    }
                    else
                        printf("Please enter  input number(Natural Number not Float) :");
                    
                getchar();    /* To avoid errors caused from repeatedly scanf using */
                }           
                
                else{
                    end_condition=getchar();
                    if(end_condition=='*')
                        break;
                    else    
                        printf("Please enter a  Natural number : ");
                    
                }
            }
    if(end_condition=='*')
        break;    
    else{
        perfect_number_control=is_perfect_number(num); /* If return value is  1 it means that given number is Perfect Number else it is not */
        printf("Is Perfect Number? :");
        if(perfect_number_control==1)
            printf("Yes");
        else
            printf("No");

        printf("\n");
        ore_number_control=is_harmonic_divisor_number(num);
        printf("Is Harmonic Divisor Number? :");
        if(ore_number_control==1)
            printf("Yes");
        else if(ore_number_control==0)
            printf("No");
        
        printf("\n");
        }
    }
}
/* ------ End of Part 2  ------ */
 /* ----- Part 3 ---------- */
 
 void difference_max_min ()
 {
    float coeff=0.0, max=0.0, min=0.0, diffrence=0.0;
    int i=0;
    printf("Enter five number :");
    for(i=0;i<5;i++){
    scanf("%f",&coeff); /* read five number */
        if(i==0){
            max=coeff;   /* initial assignments */
            min=coeff;   
        }
        else{               
            if(coeff>=max)   
                max=coeff;      
            else if(coeff<=min)
                min=coeff;
        }
    }
    diffrence=max-min;     
    printf("Maximum number is :%.1f\n",max);
    printf("Minimum number is :%.1f\n",min);
    printf("Difference between maximum and minimum is %.1f\n",diffrence);
 }
 /* end of part 3 */

 /* ------ Part 4 ------------ */

void bmi_calculation ()
{
    float weight=0.0, height=0.0, bmi=0.0; 
    printf("Please enter weight(kg) :");
    scanf("%f",&weight);
    printf("\nPlease enter height(m) :");
    scanf("%f",&height);
    bmi=(weight)/(height*height);  /* BMI calculation */
    if(bmi<16.0)     /* BMI category control statements */ 
        printf("Your category: Severely Underweight");
    else if(bmi>=16.0 && bmi<18.5)
        printf("Your category: Underweight");
    else if(bmi>=18.5 && bmi<25)
        printf("Your category: Normal");
    else if(bmi>=25.0 && bmi<30)
        printf("Your category: Owerweight");
    else if(bmi>=30)
        printf("Your category: Obese");

printf("\n");
}

/* Mehmet Mete Şamlıoğlu */
/*200104004093 */