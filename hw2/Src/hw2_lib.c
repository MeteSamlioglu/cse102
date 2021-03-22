/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include "hw2_lib.h"
#include<math.h>



/*---- First part of homework find_weekday_of_data and count_day_between_dates functions -----*/

int check_leap_year(int year){  /* I created this function to calculate leap years more clearly */
    int number_of_days;  /* Febuary's condition */

        if((year%400 == 0)||((year % 4 == 0) && (year % 100!= 0))) /* leap year condition */
            number_of_days=29;        
        else
            number_of_days=28;

    return number_of_days; 
}

int check_error(int month_day_count,int given_day,int given_month,int given_year){  
    
    int control=0;              /* Control conditions for valid date inputs */
    
    if(given_month==2) {
        month_day_count=check_leap_year(given_year); /* Leap years condition */ 
    }
    if( (given_month>12) || (given_month<=0)){
        control=1;
    }
    if((given_day>month_day_count) || (given_day<=0)){
        control=1;
    }
    if(given_year<=0){
        control=1;     
    }
    return control;
}

int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
    int arr[]={0,31,28,31,30,31,30,31,31,30,31,30,31}; /* I assigned zero to arr[0] to place january to arr[1] */
    int sum=0, day_count=0, month_days=0, i=0;
    int first_error_condition=check_error(arr[start_month],start_day,start_month,start_year);  
    int second_error_condition=check_error(arr[end_month],end_day,end_month,end_year);          
    if((first_error_condition==1)||(second_error_condition==1)){
        printf("ERROR: Given input date does not exist...!\n ");
         return -1;
    }
    else{    
        if(start_year==end_year){            
            if(start_month==end_month)
                sum=end_day-start_day;            /* Max day differences might be 7 */
            else{
                arr[2]=check_leap_year(start_year);      
                day_count=arr[start_month]-start_day;
                day_count+=end_day;
                start_month+=1;
                for(i=start_month;i<end_month;i++)
                    sum+=arr[i];
                sum+=day_count;
            }
        return sum;
        }

        else{
            arr[2]=check_leap_year(start_year); /* Check leap year condition of start_year */

            day_count=arr[start_month]-start_day;    
            day_count+=end_day; 

            arr[2]=check_leap_year(start_year); /* Leap year condition return value will be 29 or 28 */

            start_month+=1;       /* I've already calculated start_month's condition.Therefore, I'll start with (start_month+1)*/

                for(i=start_month;i<=12;i++)
                    month_days+=arr[i];

            arr[2]=check_leap_year(end_year); /* Check leap year condition of end_year */

            end_month=end_month-1; /*I've already calculated given end month's days condition in above*/

                for(i=1;i<=end_month;i++)
                month_days+=arr[i];

            start_year++; /* I've calculated all the conditions in above.Therefore I'll start with (start_year+1).*/
                while(start_year!=end_year){

                    arr[2]=check_leap_year(start_year);

                        for(i=1;i<=12;i++)
                            sum+=arr[i];
                    start_year++;
                }
            sum+=month_days+day_count;
            return sum;
        }
    }
}

int find_old_weekday(int total_days,int determined_week_day){ 
    int mod=0, i=0;                    /* This function finds the corresponding weekday of old date according to given inputs */             
    mod=total_days%7;                     
       for(i=0;i<mod;i++){    
            determined_week_day--;
            if(determined_week_day==0)
                determined_week_day=7;
        }    
    return determined_week_day;
}
int find_future_weekday(int total_days,int determined_week_day){
    int mod=0, i=0;                  /* This function finds the corresponding weekday of future date according to given inputs */
    mod=total_days%7;
        for(i=0;i<mod;i++){
            determined_week_day++;
            if(determined_week_day>7)
                determined_week_day%=7;
        }

       return determined_week_day;   
}

int find_weekday_of_data(int day, int month, int year) 
{
/* Determined date is 18-03-2021 Thursday */
    int determined_day=18, determined_month=3, determined_year=2021, determined_week_day=4, total_days=0.0, mod=0.0, i=0;    
    if(year<determined_year){  /* 2020 to any old date (including 2020)*/
        total_days=count_day_between_dates(day,month,year,determined_day,determined_month,determined_year);
        if(total_days==-1)  /*If return value of count_day_between_dates function is equal to -1 it means that given date is not valid */
            return -1;    /* Return -1 to print error message in hw2_main.c test functions  */
        else{
            determined_week_day=find_old_weekday(total_days,determined_week_day);
            return determined_week_day;
        }
    }    
    else if(year==determined_year){
        if(month==determined_month){  
            if(day<=18){  /* between 01.03.2021 and 18.03.2021(including 18th day of month) */
                total_days=count_day_between_dates(day,month,year,determined_day,determined_month,determined_year);
                if(total_days==-1)  
                    return -1;
                else{
                    determined_week_day=find_old_weekday(total_days,determined_week_day);
                    return determined_week_day;
                }
            }
            else{  /* between 18.03.2021 and 31-03-2021 (including 31th day of month)  */
                total_days=count_day_between_dates(determined_day,determined_month,determined_year,day,month,year);
                if(total_days==-1)
                    return -1;
                else{
                    determined_week_day=find_future_weekday(total_days,determined_week_day);
                    return determined_week_day;
                }
            }   
        }
        else if(month<determined_month){ /* between 01.01.2021 and 28.02.2021(including both borders) */
            total_days=count_day_between_dates(day,month,year,determined_day,determined_month,determined_year);
            if(total_days==-1)
                return -1;
            else{
                determined_week_day=find_old_weekday(total_days,determined_week_day);
                return determined_week_day;
            }
        }
        else{   /* between 01.04.2021 and 31.12.2021(including both borders) */
            total_days=count_day_between_dates(determined_day,determined_month,determined_year,day,month,year);
            if(total_days==-1)
                return -1;
            else{
                determined_week_day=find_future_weekday(total_days,determined_week_day);
                return determined_week_day;   
            }
        }
    }
    else{  /* 2022 to any future date (including 2022) */      
        total_days=count_day_between_dates(determined_day,determined_month,determined_year,day,month,year);
        if(total_days==-1)
            return -1;
        else{
            determined_week_day=find_future_weekday(total_days,determined_week_day);
            return determined_week_day;
        }
    }
}




/* ----- End of the first part of homework ----- */
/* Second part(find_angle) of Homework2  */

double find_angle(double a, double b, double c)
{
    double  median_c=0.0, median_b=0.0, gc=0.0,  gb=0.0, angle=0.0;  /* Variable names represents related length */ 
    median_c=(0.5)*sqrt(2*b*b+2*a*a-(c*c));
    median_b=(0.5)*sqrt(2*c*c+2*a*a-(b*b));
    gc=(2*median_c)/3;                                          /*double gc variable represents GC side of  triangle */
    gb=(2*median_b)/3;                                         /* double ga variable represents GA side of  triangle */
                                                        /*Now we have a new triangle and its sides are GA,GC and a */                            
                                                        /*cos(angle)=(GB^2+GC^2-a^2)/(2*GC*GB) */                                               
    angle=acos((gb*gb+gc*gc-(a*a))/(2*gc*gb));         /*angle=cos^-1(cos(angle)) */
    return angle;

}
/* End of second part of Homework2 */

/* ------- The last part of homework2 (Print tabulated)  ---------- */

void draw_top_borders(char border){ /*This function draws top border of tabulate */
    int i=0;
    printf("┌");
    for(i=1;i<35;i++)               
        printf("%c",border);
    printf("┐");
}

void draw_bottom_borders(char border){ /* This function draws bottom borders of tabulate */
    int i=0;
    printf("└"); 
    for(i=1;i<35;i++)               
        printf("%c",border);
    printf("┘");
}

void draw_horizantonal(char border){ /* This function draws horizontal line according to given input by user */
    int i=0;
    printf("|");          /* Print right vertical border */
        for(i=2;i<36;i++){
            printf("%c",border);
        }
    printf("|\n");       /* Print left vertical border */
}

void write_strings(){ /* This function writes strings as expected */
    char str1[]="ROW 101";
    char str2[]="ROW ABCDEFG";
    char str3[]="ROW XYZ123";
    printf("  %s  |%s|%s",str1,str2,str3); /*The position of strings is predetermined.Therefore,I put them into proper positions manually */
}

int integer_digits_count(double number){  /*This function returns how many integer digits needed to print given(number)value*/
                                          /* It seperates double value into integer and decimal part */
    int counter=0;                                                 
    int integer_part=0;              
    integer_part = (int)number; 
    do
        {
            /* Increments digit count of integer part */
            counter++;

            
            integer_part /= 10;
        } while(integer_part != 0);

    return counter;       /* It returns the integer digits count of given double variable */
}


int how_many_digits(double number){ /*This function returns the sum of integer and decimal count of given double variable */     

    double decimal=0.0;
    int total_digits=0, integer=0, counter=0,new_decimal=0;                                                
    integer = (int)number;                 
    decimal = (10 * number - 10 * integer)/10;
    new_decimal=100*decimal;  /* I've converted decimal value into integer value to make if-else comparisons*/ 

    counter=integer_digits_count(number); /*Integer counter variable stores integer digits count of given double variable(double number) */

    /* We know how many integer digits needed,now we have to calculate the count of decimal digits */
    if(number==0.0 && decimal==0.0) /* Print 0 */
            total_digits=1;
    else if(number>0.0 && decimal!=0.0){
        if(new_decimal%10!=0.0)
            total_digits=counter+3;      /* integer digits+comma+decimal digits(0.ab) */
        else
            total_digits=counter+2;       /*integer digits+comma+decimal +digits(0.a) */
    }
    else if(number>0 && decimal==0.0)
            total_digits=counter;      /* positive integer digits */
    else if(number<0 && decimal!=0.0){
            if(new_decimal%10!=0.0)
                total_digits=counter+4;  /* sign(-)digit + integer digits + comma + decimal digits(0.ab) */ 
            else
                total_digits=counter+3;  /* sign(-)digit+ integer digits + comma + decimal digits(0.a) */
    }
    else if(number<0 && decimal==0.0)
            total_digits=counter+1; /* sign digit(-) + integer digit */


    return total_digits;
}




void write_numbers(unsigned int r1,double r2,int r3){
    int total_space=11, how_many_space=0, i=0, integer=0,new_decimal=0;
    double decimal=0.0;
    char space=' ';
    /* First column's condition: Positive integer numbers printed centered(Max 5 digit) */
    if(r1>0 && r1<10)                
        printf("%6u     |",r1);       /* Print one digit integer value */
    else if(r1>=10 && r1<100)        
        printf("%6u     |",r1);      /* Print two digits integer value */
    else if(r1>=100 && r1<1000)
        printf("%7u    |",r1);      /* Print three digits integer value */    
    else if(r1>=1000 && r1<10000)
        printf("%7u    |",r1);      /* Print four digits integer value */
    else if(r1>=10000 && r1<100000)    
        printf("%8u   |",r1);       /* Print five digits integer value */
    /* end of first column condition */
    
    /*The second column's condition: 
    Double numbers aligned to the left with 2 decimal digits without trailing zeros. */
    integer = (int)r2;
    decimal = (10 * r2 - 10 * integer)/10;  /* Finding the integer part of decimal number */
    new_decimal=100*decimal;               /*Double variable cannot divisible(%) by integer. Therefore,I multiply decimal part with 10 */
    if(new_decimal%10==0 && decimal!=0)  /* This if-else block works like %g. I've created it because it works more clear than %g */
        printf("%.1f",r2); 
    else if(decimal==0)
        printf("%d",integer);
    else    
        printf("%.2f",r2);

    how_many_space=total_space-how_many_digits(r2); /*To determine how many space needed before print vertical border character "|" */

    for(i=0;i<how_many_space;i++)  /* Put spaces till reach end of the column */
        printf("%c",space);

    printf("|");             /* Print vertical border character */
    /*----- End of second column condition  ------ */
    /* Third column's condition: Signed integers printed left-aligned (can not exceed 6 digits)*/
    if(r3==0)
        printf("%d         ",r3);/*There is no need to calculate print "0" condition in function.Therefore,I calculated it manually */
    else if(r3>0){
        printf("%+d",r3);
        how_many_space=9-integer_digits_count(r3);  /*Third column has nine spaces*/     
        for(i=0;i<how_many_space;i++)            /* Put spaces till reach end of the column */
            printf("%c",space);
    }
    else if(r3<0){               /* Do the same thing but take into account the negative sign condition */
        printf("%d",r3);
        how_many_space=9-integer_digits_count(r3);
        for(i=0;i<how_many_space;i++)
            printf("%c",space);
    }

} /* end of the write_numbers function */


void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{
    int i=0,j=0;
    draw_top_borders(border); /* Draw top borders */
    printf("\n");
    for(i=1;i<28;i++){   
        printf("|");    /* Print "|"  for first column's left vertical border */
        for(j=1;j<36;j++){      /* The conditions of Printing Row elements Properly */
            if(i==4){                    
                write_strings();     /* Put strings into first row(Header row) as expected */
                printf("|"); /* Print "|" for third column vertical border */ 
            break;
            }        
            else if(i==11){
                write_numbers(r11,r12,r13); /* Put the values into given row and column on the tabulate as expected */ 
                printf("|");   /* Print "|" for third column vertical border */
            break;
            }                      /* Do the same thing for other rows */ 
            else if(i==18){
                write_numbers(r21,r22,r23);       
                printf("|"); 
                break;
            }
            else if(i==25){
                write_numbers(r31,r32,r33);
                printf("|");
                break;
            }                   /* End of the condition of Printing Row elements properly */
            else if(j==35)  
                printf("|"); /* Print "|" for  third column vertical borders.*/  
            else{
            if(j%12==0 && j!=0) 
                printf("|");    /* Print "|" for second column vertical lines*/
            else
                printf(" ");    /* Put 11 spaces to first and second columns third column has 9 spaces*/
            }

        }   
        printf("\n");
        if(i%7==0 && i!=0){             
            draw_horizantonal(border);   /* This if-block draws rows in each seven space by calling draw_horizantonal function*/
        }
    }
    draw_bottom_borders(border);      /* This function draws bottom borders  */ 
}
