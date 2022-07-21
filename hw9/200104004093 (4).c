#include<stdio.h>
#include<string.h>

#define NAME_LEN 30
#define CUSTOMER_SIZE 50

typedef enum{employee=0, retired=1, student=2,unemployed=3 ,other=4, empty=5}Label;

typedef struct{         /* Struct for keeping information of customers */
    char name[NAME_LEN];
    Label label;
    int age;
}Bank;

int main_screen(Bank* user); /* Main page of banking system */
void new_user(Bank* user,Bank copy_customer); /* New user creation function */
void print_user(Bank* user);   /* This function print the informations of proceeded customer */
void set_initial_bank(Bank* user); /* This function is to setting initial bank array (all empty label) */
void print_sequence(Bank* user);  /* This function is printing sequence after every operation */
void rearrange_proceed(Bank* user); /* This function rearranges sequence */
 /* Sorting functions */
void sort_customers(Bank* user,Bank copy_customer); /* SORTING FUNCTIONS */
void rearrange_sequence(Bank* user,int array_index); /* This function rearranges sequence after every sorting */
int check_limit(Bank* user,int initial_index); /* Check the current sequences initial index for entered label */
int check_label(Bank pt,Bank copy_customer);   /* It checks the priority */
int get_label_limit(Bank copy_customer); /* It takes the join limitation of user's label */

/* Read me */
/* I assumed that if the given sequence is 0-0-0-0-0-1-2-3-1 and if the new label is 0 the sequence is going to be  0-0-0-0-0-1-2-3-0-1 */ 
/* If given row is 0-0-0-0-0-1-1-1-2-2-3, lets say six user entered the sequence with labelled 0 then the sequence is going to be 
 0-0-0-0-0-1-1-1-2-2-3-0-0-0-0-0-0 if one more user joins to the sequence with labelled diffrent than ' 0 ' the sequence is going to be arranged accordingly*/
/* Example current sequence : 0-0-0-0-0-1-1-2-2-3-0-0-0-0-0-0, after one user with labelled 1 sequence is going to be 0-0-0-0-0-1-1-2-2-3-0-0-0-0-0-0-1 the last element going 
to be  the new  initial index for example if one more 0 labelled user joins the sequence is going to be 0-0-0-0-0-1-1-2-2-3-0-0-0-0-0-0-1-0 */
/* The other parts works as expected in pdf.This exception was not mentioned in pdf. Therfore, I found my own solution */

int main(){
    Bank users[CUSTOMER_SIZE]; /* To keep 50 customer information, create structer array with size 50 */
    set_initial_bank(&users[0]); /* Set all the elements of array empty to be sure that array is not include any garbe value */
    while(1){
        if(main_screen(&users[0])==1){ /* Passing structer array into main_screen function and according to return value of it end the programme */
            printf("The programme is terminated succesfully...");
            break;
        }
    }

return 0;
}
void print_sequence(Bank* user){ /* This function prints current sequence in each iteration */
    int i=0;
    for(i=0; i<50; ++i,user++){
       if(i==0 && user->label!=empty)
            printf("%d",user->label);
        else if(user->label!=empty)
            printf("-%d",user->label);
        else{
            printf("%c",'\0');
            break;
        }
    }
    

}
void set_initial_bank(Bank *user){ /* Assigning empty to all the label elements of given structure to avoid keeping garbage value of any index in structure */
    int i=0;
    for(i=0; i<50; ++i){
        user->label=empty;
        user++;
    }
   
}

int main_screen(Bank* user){          /* This is my main bank function to make operations */
    int option, i=0, end_condition=0;   /* After the programme started,this function runs 'till user enter 3 to exit */
    Bank copy_customer;
    printf("Current Sequence: ");
    print_sequence(&user[0]);
    printf("\n1-Add customer");
    printf("\n2-Process customer");
    printf("\n3-EXIT\n");
    scanf("%d",&option);
    
    switch(option){
    case 1:
        new_user(&user[0],copy_customer); 
        end_condition=0;
    break;
    case 2:
        print_user(&user[0]);
        end_condition=0;
        break;
    
    case 3:
        end_condition=1;
        break;
    default:
        break;
    }
    
    return end_condition;
}

void rearrange_proceed(Bank* user){ /* This function rearranges the sequence after the proceed process */
    int i=0, index=0;
    Bank copy_user[CUSTOMER_SIZE]; /* All the data copied into this sturcter */ 
    for(i=0; i<50; ++i){
        strcpy(copy_user[i].name,user[i].name);
        copy_user[i].age=user[i].age;
        copy_user[i].label=user[i].label;
    }
    for(i=50; i>0; i--){
        if(user[i].label!=empty){
            index=i;   
            break;
        }
    }
    for(i=1; i<50; ++i){
        strcpy(user[i-1].name,copy_user[i].name);
        user[i-1].age=copy_user[i].age;
        user[i-1].label=copy_user[i].label;
    }
        user[index].label=empty;
        user[index].age=0;
}

void print_user(Bank* user){
    int i=0, control=0;      /* Get the first customer in current sequence and print informations of him/her */
    for(i=0; i<50; ++i){
        if(user[i].label!=empty){
            control=1;
        }
    }
    if(control==0)    /* If there is no customer in current sequence yet print this message */
        printf("\nThere is not any customer in bank system sequence.\n");
    else if(control==1){
        printf("\nProceed customer is : ");
        printf("%s\n",user[0].name);
        rearrange_proceed(&user[0]);
    }
}

void new_user(Bank* user, Bank copy_customer){        
                                        /* New user registration  */
    
    printf("Please enter the name of the customer :");
    scanf("%s",copy_customer.name);
    printf("Please enter the age of the customer :");
    scanf("%d",&copy_customer.age);
    printf("Please enter the label of the customer :");
    scanf("%u",&copy_customer.label);
    sort_customers(user,copy_customer);   /* Pass the information of new user into sort_users function to find proper position */

}

void rearrange_sequence(Bank* user,int array_index){ /* This function arranges the current sequence after every sorting process of labels */
    int i=0;
    Bank copy_user[CUSTOMER_SIZE]; /* All the datas are going to copy into this structure */ 
    for(i=array_index; i<50; ++i){
        strcpy(copy_user[i].name,user[i].name);
        copy_user[i].age=user[i].age;
        copy_user[i].label=user[i].label;
    }
                                    /* it slides all the elements towards to consecutive index */
    for(i=array_index; i<50; ++i){  /* Rearrange sequence */
        user[i+1].age=copy_user[i].age;
        user[i+1].label=copy_user[i].label;     
        strcpy(user[i+1].name,copy_user[i].name);
    }
}

int check_limit(Bank* user,int initial_index){ /* This function returns the current initial index of sequence for the labels which reached its limitation already */

    int i=0, index=0;
    for(i=49; i>initial_index; i--)
        if(user[i-1].label>user[i].label)
            index=i-1;

    return index;

}
int check_label(Bank pt,Bank copy_customer){ /* This function checks the priority in the given element of sequence */
    Bank i;
    int control=1;
        for(i.label=employee; i.label<=copy_customer.label; ++(i.label)){
            if(pt.label==i.label)
                control=0;
        }               /* If given label's priority more than the previous label of sequence element it returns 1 otherwise it returns 0 */
    return control;
}
int get_label_limit(Bank copy_customer){ /* This function returns the count of join limitations of labels */
    int value;
    if(copy_customer.label==employee)
        value=5;
    else if(copy_customer.label==retired)
        value=3;
    else if(copy_customer.label==student)
        value=3;
    else if(copy_customer.label==unemployed)
        value=2;
    else if(copy_customer.label==other)
        value=2;
    
    return value;
}

void sort_customers(Bank* user, Bank copy_customer){ /* Sorting function for employee(LABEL 0)*/
    int counter=0, i=0, j=0, index=0, initial_index=0, break_condition=0, limitation=0;
    Bank *pt;
    limitation=get_label_limit(copy_customer); /* getting the limitation of given user's labe */
    pt=&user[49];
       
        for(i=49; i>=0; --i,pt--){                /* Findind the repetition time */
            if(pt->label==copy_customer.label){ 
                initial_index=i;
                break_condition=1;
                for(j=i; pt->label==copy_customer.label; --j,pt--) 
                    counter++;
            }
            if(break_condition==1)
                break;
        }
    
    if(counter==0){          /* If counter is zero it means that there is no given labelled user in current sequence */
        pt=&user[0];
        for(i=0; i<50; ++i,pt++){
            if(check_label(*pt,copy_customer)==1){   /* Check the priority and rearrange the sequence accordingly */
                rearrange_sequence(user,i);   
                strcpy(user[i].name,copy_customer.name);
                user[i].age=copy_customer.age;
                user[i].label=copy_customer.label;
                break;
            }
        }
    }
    else if(counter%limitation==0){  /* It means that the reached the consecutive join limitation */
        index=check_limit(&user[0],initial_index); /* Get the current index for the labelled which reached its limitation */
        if(index==0){                        /* If index is zero it means that the new element going to take the place of empty element (end of the sequence)*/
            for(i=0; i<50; ++i){
                if(user[i].label==empty){
                    strcpy(user[i].name,copy_customer.name);
                    user[i].age=copy_customer.age;
                    user[i].label=copy_customer.label;
                    break;
                }
            }
        }
        else{ /* If index is not zero it means that there is more than one users who reached its limitation(in this case the labels of the users are diffrent than each other) */
            pt=&user[index+1];
            for(i=index+1; i<50; ++i,pt++){
                if(check_label(*pt,copy_customer)){ 
                    rearrange_sequence(user,i);
                    strcpy(user[i].name,copy_customer.name);
                    user[i].age=copy_customer.age;
                    user[i].label=copy_customer.label;
                    break;
                }
            }
        }
    }
    else{       /* If given user's consecutive joining limitation is still not reached then this else block will run */
        counter=0;
        pt=&user[49];
        for(i=49; i>=0; --i,pt--){
            counter=0;
            if(pt->label==copy_customer.label){ 
                for(j=i; pt->label==copy_customer.label; j--,pt--) 
                    counter++;   /* Get the count of users in current sequence who has the same labelled(This takes only the last few users who sorted consecutively with the same labelled) */
            
                if(counter<limitation){  /* If user count not reached its limitation then put the new user into proper position in current sequence */
                    index=i;  
                    rearrange_sequence(user,index); /* rearrange the sequence after the process */
                    strcpy(user[index].name,copy_customer.name);
                    user[index].age=copy_customer.age;
                    user[index].label=copy_customer.label;                       
                    break;
                }
                
                 else if(counter>limitation){  /* This is an exception situation for this case */ /* Lets say the current sequence is 0-0-0-0-0-1-1-1 and more than 5 user joined with labelled 0 */
                                              /* It takes the user consecutively till the new user with diffrent labelled than these  and after that new sequence will start*/
                    for(j=49; j>=0; --j)
                        if(user[j].label==employee || user[j].label==retired || user[j].label==student || user[j].label==unemployed || user[j].label==other){
                            index=j;
                            break;
                        }
                    rearrange_sequence(user,index+1);
                    strcpy(user[index+1].name,copy_customer.name);
                    user[index+1].age=copy_customer.age;
                    user[index+1].label=copy_customer.label;    
                    

                }
                
             }   
            
        }
    }
         
}

/* Mehmet Mete Şamlıoğlu */
/* 200104004093 */