#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN_STRING 200 

struct Movie_Budget{
    int budget;
    int years;
    char *name;
    struct Movie_Budget* next;
};
struct Movie_Name{
    char* genre;
    char* name;
    double score;
    struct Movie_Name* next;
};

int check_exact_match(struct Movie_Name* head_ref, char* movie_name);
int node_count_name(struct Movie_Name* head_ref);      /* This Function returns current node count for Movie_Name */
int node_count_budget(struct Movie_Budget* head_ref); /* This Function returns current node count for Movie_Budget */
int seperate_string(char *string, struct Movie_Name **name_head_ref, struct Movie_Budget** budget_head_ref); /* Seperate string by using strtod (extract "," character ) */

void seperate_file(char *text, struct Movie_Name** head_name, struct Movie_Budget** head_budget);
void update_repeated_data(struct Movie_Name**head_name, struct Movie_Budget** head_budget);/* Replace old data with  the new one */
void update_movie(struct Movie_Name** head_ref,struct Movie_Budget** budget_head_ref,char *movie_name); /* Main update function */
void delete_old_data(struct Movie_Name** head_ref,struct Movie_Name** temp,struct Movie_Budget** budget_head_ref,struct Movie_Budget** temp2);/* Delete old data */


void push(struct Movie_Budget **head_ref, int years, int budget, char* movie_name);   /* Insert a new node as a head of linked list */
void delete_node(struct Movie_Budget** head_ref,struct Movie_Budget* temp);          /* Delete a random node from Movie_Budget list */
void push_name_list(struct Movie_Name **head_ref, double score, char* genre, char* movie_name); /* Insert a new node as a head of linked list */
void delete_node_name(struct Movie_Name **head_ref, struct Movie_Name *n); /* Delete a nod from Movie_Name linked list */
void free_name_list(struct Movie_Name** head_ref); /* Free namelist to avoid memory leak */
void free_budget_list(struct Movie_Budget** head_ref); /* Free budget list to avoid memort leak */
/* MENU FUNCTIONS */
int main_screen(struct Movie_Name* head_name, struct Movie_Budget* head_budget);
void sorting_function(struct Movie_Name* head_name, struct Movie_Budget* head_budget, int operation);
void print_single(struct Movie_Name *head_name, struct Movie_Budget *head_budget, int operation, int movie_sequence);
void print_multiple(struct Movie_Name* head_name, struct Movie_Budget* head_budget, int operation);
void list_of_genres(struct Movie_Name* head_name);
void movie_through_years(struct Movie_Budget* head_budget);
void movie_through_scores(struct Movie_Name* head_name);
void delete_multiple_node(struct Movie_Name** head_name, char *genre);
void single_movie_info(struct Movie_Name* head_name,struct Movie_Budget* head_budget);
void average_imdb(struct Movie_Name* head_name);
void frequence_of_genres(struct Movie_Name* head_name);
/* -------------------------- END OF MENU FUNCTIONS --------------*/
struct Movie_Name* copy_name_list(struct Movie_Name* head_ref); /* Creates a copy linked list to modify after the modification process is done, freed copy linked list data */
struct Movie_Budget* copy_budget_list(struct Movie_Budget* head_ref);
struct Movie_Budget* sort_descending(struct Movie_Budget* head_ref);

/* When you choose Multiple budget sorting option on List sorted menu, the unknown budget movies are going to take the first priority */
/* Example           
                unknown
                unknown
                300
                400
                .... 
*/
int main(){
    int end_control=0, i=0;
    struct Movie_Name *head_name; 
    struct Movie_Budget *head_budget;
    char file[] = "Movies.txt";    /* Name of the text file */
    head_name=NULL;
    head_budget=NULL;
    seperate_file(file,&head_name,&head_budget);
    update_repeated_data(&head_name,&head_budget); /* All the data in text has been read and the repeated movies has been updated */
    head_budget=sort_descending(head_budget); /* The sort descending function is going to create a new linked list, In this linked list 
                                              the movies are going to be inserted and kept in descending order by year and budget(when year is the same) */
    while(1){
        if(main_screen(head_name,head_budget)==1){  /* When user enters "8" in the main_screen function the function is going to return "1" and the programme will end */
            printf("The programme has terminated succesfully...");
            break;
        }
    
    }
    free(head_name);
    free(head_budget);
    return 0;
}
 
 /* LIST SORTED FUNCTIONS */
 void print_single(struct Movie_Name *head_name, struct Movie_Budget *head_budget, int operation, int movie_sequence){
     struct Movie_Name* head=head_name;
     struct Movie_Budget* head2=head_budget;
     int counter=0;
    if(operation==1 || operation==5){ /* Movie_Budget will be used */
        while(head2->next!=NULL){          /* Single film print for Budget and Year */
            if(movie_sequence==counter+1){
                break;
            }
            head2=head2->next;
            counter++;
        }
        while(head->next!=NULL){
            if(strcmp(head->name,head2->name)==0)
                break;
            
            head=head->next;
        }
        if(head2->budget==0){
            printf("%-34s%-25s%-94s%-15.1f%-15d\n","unknown",head->genre,head->name,head->score,head2->years);
        }
        else
            printf("%-34d%-25s%-94s%-15.1f%-15d\n",head2->budget,head->genre,head->name,head->score,head2->years);

    }
    else if(operation==2 || operation==3 || operation==4){ /* Movie_Name will be used */
        while(head->next!=NULL){                           /* Single film print for Genre and Name and Score*/
            if(movie_sequence==counter+1){
                    break;
                }
                head=head->next;
                counter++;
            }
            while(head2->next!=NULL){
                if(strcmp(head->name,head2->name)==0)
                    break;
                
                head2=head2->next;
            }
            if(head2->budget==0)
                printf("%-34s%-25s%-94s%15.1f%-15d\n","unknown",head->genre,head->name,head->score,head2->years);
            
            else
                printf("%-34d%-25s%-94s%-15.1f%-15d\n",head2->budget,head->genre,head->name,head->score,head2->years);

    }        

}
void  print_multiple(struct Movie_Name* head_name,struct Movie_Budget* head_budget, int operation){
    int upper_year, lower_year, upper_budget, lower_budget, validity_check=0, lower_seq=0, upper_seq=0, node_count;
    int counter=0;
    double upper_score, lower_score;
    struct Movie_Name *pt_name,  *initial_name=head_name;
    struct Movie_Budget*pt_budget, *initial_budget=head_budget;
    node_count=node_count_budget(head_budget);
    if(operation==1){                           /* Multiple film print function for Budget */
        while(1){
            validity_check=0;
            pt_budget=initial_budget;
            printf("Enter upper budget limit:");
            scanf("%d",&upper_budget);
            printf("Enter lower budget limit:");
            scanf("%d",&lower_budget);
        
            while(pt_budget->next!=NULL){
                if(pt_budget->budget>=lower_budget && pt_budget->budget<=upper_budget && lower_budget<upper_budget){
                        head_name=initial_name;
                        while(head_name->next!=NULL){
                            if(strcmp(head_name->name,pt_budget->name)==0){
                                if(pt_budget->budget==0)
                                    printf("%-34s%-25s%-94s%-15.1f%-15d\n","unknown",head_name->genre,pt_budget->name,head_name->score,pt_budget->years);
                                else
                                    printf("%-34d%-25s%-94s%-15.1f%-15d\n",pt_budget->budget,head_name->genre,pt_budget->name,head_name->score,pt_budget->years);
                                    
                                break;
                            }
                            head_name=head_name->next;
                        }
                        
                        validity_check=1;
                    
                }
                pt_budget=pt_budget->next;
            }
            if(validity_check==1)
                break;
            else 
                printf("\nIncorrect upper or lower limit value, please try again!\n");
        }
    }
    else if(operation==2 || operation==3){ /* Multiple film print function for Genre and Name */
        
        while(1){
            counter =0;    
            pt_name=initial_name;
            printf("Enter lower limit:");
            scanf("%d",&lower_seq);
            printf("Enter upper limit:");
            scanf("%d",&upper_seq);
            if(lower_seq>=1 && upper_seq<=node_count && lower_seq<upper_seq)
                break;
            else
                printf("\nYour input is not valid, TRY AGAIN [Your input must be in between 1 to Total Film Count !\n");
        }
            while(pt_name->next!=NULL){
                if(counter>=(lower_seq-1) && counter<=(upper_seq-1)){
                    head_budget=initial_budget;
                    while(head_budget->next!=NULL){
                        if(strcmp(head_budget->name,pt_name->name)==0)
                            break;
                    
                        head_budget=head_budget->next;
                    }
                     if(head_budget->budget==0)
                            printf("%-34s%-25s%-94s%-15.1f%-15d\n","unknown",pt_name->genre,head_budget->name,pt_name->score,head_budget->years);
                     else
                            printf("%-34d%-25s%-94s%-15.1f%-15d\n",head_budget->budget,pt_name->genre,head_budget->name,pt_name->score,head_budget->years);
                        
                }
                counter++;
                pt_name=pt_name->next;
            }

    }    
    else if(operation==4){                      /* Multiple film print function for Score */
            while(1){
            pt_name=initial_name;
            validity_check=0;
            printf("Enter upper Score limit:");
            scanf("%lf",&upper_score);
            printf("Enter lower Score limit:");
            scanf("%lf",&lower_score);
        
            while(pt_name->next!=NULL){
                if(pt_name->score>=lower_score && pt_name->score<=upper_score){
                        head_budget=initial_budget;
                        while(head_budget->next!=NULL){
                            if(strcmp(pt_name->name,head_budget->name)==0){
                                 if(pt_budget->budget==0)
                                     printf("%-34s%-25s%-94s%-15.1f%-15d\n","unknown",pt_name->genre,pt_name->name,pt_name->score,head_budget->years);
                                else
                                     printf("%-34d%-25s%-94s%-15.1f%-15d\n",head_budget->budget,pt_name->genre,pt_name->name,pt_name->score,head_budget->years);
                                break;
                            }
                            head_budget=head_budget->next;
                        }
                        
                        validity_check=1;
                    
                }
                pt_name=pt_name->next;
            }
            if(validity_check==1)
                break;
            else 
                printf("\nIncorrect upper or lower limit value, please try again!\n");
        }
    }
    else if(operation==5){          /* Multiple film print function for Year */
        while(1){
            validity_check=0;
            pt_budget=initial_budget;
            printf("Enter upper year limit:");
            scanf("%d",&upper_year);
            printf("Enter lower year limit:");
            scanf("%d",&lower_year);
            while(pt_budget->next!=NULL){
                if(pt_budget->years>=lower_year && pt_budget->years<=upper_year && lower_year<upper_year){       
                     head_name=initial_name;
                     while(head_name->next!=NULL){
                        if(strcmp(head_name->name,pt_budget->name)==0){
                            if(pt_budget->budget==0)
                                printf("%-34s%-25s%-94s%-15.1f%-15d\n","unknown",head_name->genre,pt_budget->name,head_name->score,pt_budget->years);
                            else
                                printf("%-34d%-25s%-94s%-15.1f%-15d\n",pt_budget->budget,head_name->genre,pt_budget->name,head_name->score,pt_budget->years);
                            break;
                        
                        }       
                        head_name=head_name->next;        
                    }
                    validity_check=1;
                }
                
                pt_budget=pt_budget->next;
            }
            if(validity_check==1)
                break;
            else 
                printf("\nIncorrect upper or lower limit value, please try again!\n");
          }
    }

}

void sorting_function(struct Movie_Name* head_name, struct Movie_Budget* head_budget, int operation){
    
    struct Movie_Name*copy_head,*initial_header,*temp, *modified_list;
    struct Movie_Budget*copy_budget, *initial_budget, *temp2, *modified_budget;
    int node_count, i=0,valid=0, option=0, end_condition=0, budget=0, years=0, counter=0;
    double score;
    char *buffer, *buffer2, *genre, *movie_name;
    
    
    node_count=node_count_name(head_name);  /* Node count is constant for these two list */
    copy_head=copy_name_list(head_name);    /* Copy linked lists has created to make modifications */ 
    initial_header=copy_head;                /* Keep the Movie_Name's  header addres*/
    copy_budget=copy_budget_list(head_budget); /* Copy linked list for Movie_Budget */
    initial_budget=copy_budget;                
    
    buffer=(char*)malloc(LEN_STRING*sizeof(char));
    buffer2=(char*)malloc(LEN_STRING*sizeof(char));
    genre=(char*)malloc(LEN_STRING*sizeof(char));
    movie_name=(char*)malloc(LEN_STRING*sizeof(char));
    modified_list=(struct Movie_Name*)malloc(sizeof(struct Movie_Name));   /* Empty list will be modified */
    modified_budget=(struct Movie_Budget*)malloc(sizeof(struct Movie_Budget)); /*  Empty list will be modified */
    
    while(1){
        printf("1-) Single selection\n");
        printf("2-) Multiple selection\n");
        printf("Please select an operation:");
        if(scanf("%d",&option)==1){
            if(option==1 || option==2)
                break;
        }
        else{
            printf("\nTRY AGAIN!\n");
            getchar();
        }

    }
    if(modified_list==NULL || modified_budget==NULL){
        printf("The Heap doesn't have enough memory to allocate new list!\n");
        return;
    }
    switch(operation){
        case 1:          /* Sorting Budget  in ascending order */
            for(i=0; i<node_count; ++i){                  
                budget=copy_budget->budget;
                while(copy_budget!=NULL){
                    if(copy_budget->budget>budget){
                        temp2=copy_budget;
                        budget=copy_budget->budget; 
                    }
                    else if(copy_budget->budget==budget){
                        temp2=copy_budget;
                        budget=temp2->budget;
                    }

                    copy_budget=copy_budget->next;
                }
                
                strcpy(buffer,temp2->name);            
                push(&modified_budget,temp2->years,temp2->budget,buffer); /* Add found node to our empty modified list */
                delete_node(&initial_budget,temp2);   /* Delete the node we pushed and get a new header */
                copy_budget=initial_budget;          /* Assign new header to copy_budget */
            
            }                     
                                   
        break;                                        /* The sorting algorithm will be exactly the same through the end of this switch block */
        case 2:                                        /* Sorting Genre  in ascending order */
            for(i=0; i<node_count; ++i){           
                strcpy(genre,copy_head->genre);
                while(copy_head!=NULL){
                    if(strcmp(copy_head->genre,genre)>0){
                        temp=copy_head;
                        strcpy(genre,copy_head->genre);
                    }
                   
                    else if(strcmp(copy_head->genre,genre)==0){
                        temp=copy_head; 
                        strcpy(genre,temp->genre);
                    }
                    
                    copy_head=copy_head->next;
                }
                    
                    strcpy(buffer,temp->name);            
                    strcpy(buffer2,temp->genre);
                    push_name_list(&modified_list,temp->score,buffer2,buffer);
                    delete_node_name(&initial_header,temp);
                    copy_head=initial_header;
            }   
                
            break;
        case 3:                                          /* Sorting Movie Name  in ascending order */
                for(i=0; i<node_count; ++i){          
                strcpy(movie_name,copy_head->name); 
                while(copy_head!=NULL){
                    if(strcmp(copy_head->name,movie_name)>0){
                        temp=copy_head;
                        strcpy(movie_name,copy_head->name);
                    }
                   
                    else if(strcmp(copy_head->name,movie_name)==0){
                        temp=copy_head; 
                        strcpy(movie_name,temp->name);
                    }
                    
                    copy_head=copy_head->next;
                }
                    
                    strcpy(buffer,temp->name);            
                    strcpy(buffer2,temp->genre);
                    push_name_list(&modified_list,temp->score,buffer2,buffer);
                    delete_node_name(&initial_header,temp);
                    copy_head=initial_header;
            }   

            break;
         case 4:                            /* Sorting Scores in ascending order */
            for(i=0; i<node_count; ++i){            
            score=copy_head->score;
                while(copy_head!=NULL){
                    if(copy_head->score>score){
                        temp=copy_head;
                        score=copy_head->score; 
                    }
                    else if(copy_head->score==score){
                        temp=copy_head;
                        score=temp->score; 
                    }

                copy_head=copy_head->next; 
            }
                
                strcpy(buffer,temp->name);            
                strcpy(buffer2,temp->genre);
                push_name_list(&modified_list,temp->score,buffer2,buffer);
                delete_node_name(&initial_header,temp);
                copy_head=initial_header;
        }   
        break;
        case 5:                         /* Sorting Years in ascending order */
            
            for(i=0; i<node_count; ++i){       
                years=copy_budget->years;
                while(copy_budget!=NULL){
                    if(copy_budget->years>years){
                        temp2=copy_budget;
                        years=copy_budget->years; 
                    }
                    
                    else if(copy_budget->years==years){
                        temp2=copy_budget;
                        years=temp2->years;
                    }
                    
                    copy_budget=copy_budget->next;
                }
                
                strcpy(buffer,temp2->name);            
                push(&modified_budget,temp2->years,temp2->budget,buffer);
                delete_node(&initial_budget,temp2);
                copy_budget=initial_budget;
            }
            break;
        
        
        default:
            printf("Invalid input !");
        break;
    
    }
  

    if(operation==1 || operation==5){   /* We will use modified budget list to print sorted elements */
        initial_budget=modified_budget;
        if(option==1){
            while(1){
                printf("Enter the value (sequence of movie): "); 
                if(scanf("%d",&counter)==1 && (counter>0 &&counter<node_count))
                    break;
                else
                    printf("\nYour input must be in between 0 to node count, TRY AGAIN!\n");
            
            }
            print_single(head_name,modified_budget,option,counter); /* Single Print */
        }
        else if(option==2){                       /* Multiple Print */
            print_multiple(head_name,modified_budget,operation);
        }
        
        
    }
    else if(operation==2 || operation==3 || operation==4){  /* We will use Modified Name list to print sorted elements */
        initial_header=modified_list;
         if(option==1){                                      /* Single Print */
            while(1){
                printf("Enter the value (sequence of movie): ");
                if(scanf("%d",&counter)==1 && (counter>0 &&  counter<node_count))
                    break;
                else
                    printf("\nYour input must be in between 0 to node count, TRY AGAIN!\n");
            }
            print_single(modified_list,head_budget,option,counter);
         }
        else if(option==2){                            /* Multiple print */
            print_multiple(modified_list,head_budget,operation);
        }
        
    }
    free(copy_budget);
    free(copy_head);
    free(modified_list);
    free(modified_budget);
    
    free(buffer);
    free(buffer2);
    free(genre);
    free(movie_name);
}


void list_sorted(struct Movie_Name* head_name, struct Movie_Budget* head_budget){
    int operation=0, end_control=0;
    while(end_control!=1){
        printf("1-)Budget\n");
        printf("2-)Genre\n");
        printf("3-)Name\n");
        printf("4-)Score\n");
        printf("5-)Year\n");
        printf("Please select an operation: ");
        if(scanf("%d",&operation)==1){
            switch(operation){           /* If input is not valid , repeatedly ask for valid input */
                case 1:
                    sorting_function(head_name,head_budget,operation); /* Budget */
                    end_control=1;
                break;
                case 2:
                    sorting_function(head_name,head_budget,operation); /* Genre */
                    end_control=1;
                break;
                case 3:
                    sorting_function(head_name,head_budget,operation); /* Name */
                    end_control=1;
                break;
                case 4:
                    sorting_function(head_name,head_budget,operation); /* Score */
                    end_control=1;
                break;
                case 5:
                    sorting_function(head_name,head_budget,operation); /* Year */
                    end_control=1;
                break;
                default:
                    printf("TRY AGAIN!\n"); /* ERROR */
                    end_control=0;
                break;
            }      
        }
        else{
                printf("TRY AGAIN!\n");
                getchar();
                end_control=0;
            }
    }

}
/* --------------------------------------------------*/
/* END OF LIST SORTED FUNCTIONS */
/* --------------LIST OF GENRES------------------- */

void delete_multiple_node(struct Movie_Name** head_name, char *genre) /* This function deletes multiple nodes in given linked list which includes the given genre name */
{
    struct Movie_Name *head = *head_name ;
    struct Movie_Name *previous_node;

    while(1){
        if(head!=NULL && strcmp(head->genre,genre)==0){
            *head_name=head->next;
            free(head);
            head=*head_name;
        }
        else
            break;
    }
    do
    {
        while (head != NULL && strcmp(head->genre,genre)!=0)
        {
            previous_node = head;
            head = head->next;
        }
        if (head == NULL) /*End of the linked list, last node condition*/
            break;
        else{ 
        previous_node->next = head->next;
        free(head);
        head = previous_node->next;
        }
    }while(1); 
}

void list_of_genres(struct Movie_Name* head_name){
    struct Movie_Name *copy_head, *current_head;
    char *genre;
    copy_head=copy_name_list(head_name);
    genre=(char*)malloc(LEN_STRING*sizeof(char));
    
    
    while(copy_head!=NULL){
        strcpy(genre,copy_head->genre);
        printf("%s\n",genre);             /* Print the genre name */
        delete_multiple_node(&copy_head,genre); /* Delete all the occurrences in copy linked list*/
    }                                         /* Do that until all the nodes have been deleted */
    
    /* free(copy_head); */
    free_name_list(&copy_head);
    free(genre);
}
/* -------- END LIST OF GENRES -----------------*/
/* ---------LIST OF MOVIE THROUGH THE YEARS -----------*/
void movie_through_years(struct Movie_Budget* head_budget){
    struct Movie_Budget* temp=head_budget; /* In initial movie budget list years are sorted descending, Therfore ill use this linked list */
    int option=0, valid_option=0; /* For two option (since and until) */
    int years=0;
    while(1){
        valid_option=0;
        temp=head_budget;
        printf("Enter a year:");
        scanf("%d",&years);    
        printf("Until(0) or Since(1) %d:",years);
        scanf("%d",&option);
            if(option==0){
                while(temp!=NULL){
                    if(temp->years<=years){  /* Prints all the films which released until given year */
                        printf("%s\n",temp->name); 
                        valid_option=1; /* Valid check */
                    }
                    temp=temp->next;
                }

            }
            else if(option==1){
                while(temp!=NULL){
                    if(temp->years>=years){
                        printf("%s\n",temp->name); /* Prints all the films which released since given year */
                        valid_option=1; /* Valid check */
                    }
                    temp=temp->next;
                }
            }
        
        if(valid_option==0){ /* Check valid input, repeadetaly ask for it ! */
            printf("TRY AGAIN!\n");
        }
        else if(valid_option==1)
            break;
    
    }
}
void movie_through_scores(struct Movie_Name* head_name){
    struct Movie_Name* temp=head_name;
    int option=0, valid_option=0;    
    double score;
    while(1){
        valid_option=0;
        temp=head_name;
        printf("Enter a score:");
        scanf("%lf",&score);    
        printf("Less(0) or Greater(1) %.1f:",score);
        scanf("%d",&option);
            if(option==0){
                while(temp!=NULL){
                    if(temp->score<=score){  /* Prints all the films which has lower imdb score  */
                        printf("%s\n",temp->name); 
                        valid_option=1; /* Valid check */
                    }
                    temp=temp->next;
                }

            }
            else if(option==1){
                while(temp!=NULL){
                    if(temp->score>=score){
                        printf("%s\n",temp->name); /* Prints all the films which has greater imdb score */
                        valid_option=1; /* Valid check */
                    }
                    temp=temp->next;
                }
            }
        
        if(valid_option==0){ /* Check valid input, repeadetaly ask for it ! */
            printf("TRY AGAIN!\n");
        }
        else if(valid_option==1)
            break;
    }
}

/* All informations about single movie */
void single_movie_info(struct Movie_Name* head_name,struct Movie_Budget* head_budget){
    int validity_check=0;
    char *name;
    struct Movie_Name* temp=head_name;
    struct Movie_Budget* temp2=head_budget;
    
    name=(char*)malloc(LEN_STRING*sizeof(char));
    while(1){
        temp=head_name;
        temp2=head_budget;
        printf("Please enter the name of movie:");
        scanf(" %[^\n]%*c",name); /* Get movie name */
        
        while(temp!=NULL){
            
            if(strcmp(temp->name,name)==0){ /* Find the input name in linked list */
                validity_check=1;
                while(temp2!=NULL){
                    if(strcmp(temp->name,temp2->name)==0) /* Find the input name other informations in Budget list */
                        break;
                    temp2=temp2->next;
                }
                if(temp2->budget==0){              /* If budget is 0 it means that unknown */
                    printf("\nBudget: Unknown");
                    printf("\nGenre: %s",temp->genre);
                    printf("\nName: %s",temp->name);
                    printf("\nScore: %.1f",temp->score);
                    printf("\nYear: %d",temp2->years);
                }
                else{
                    printf("\nBudget: %d",temp2->budget);
                    printf("\nGenre: %s",temp->genre);
                    printf("\nName: %s",temp->name);
                    printf("\nScore: %.1f",temp->score);
                    printf("\nYear: %d",temp2->years);
                }

                break;
            }
            temp=temp->next;
        }
        if(validity_check==1)
            break;
        else{
            printf("\nYour input doesn't matched with any film in the list, Please Try Again !\n");

        }
    
    }
    
    printf("\n\n");
    free(name);
}

/* END */
/* AVERAGE IMDB FUNCTION */

void average_imdb(struct Movie_Name* head_name){   
    struct Movie_Name* temp=head_name;
    double average=0.0;
    int node_count;
    node_count=node_count_name(head_name);
    while(temp!=NULL){
        average+=temp->score;
        temp=temp->next;
    }
    average=average/node_count;
    printf("\nAverage: %f",average);
    printf("\n\n");

}
/* END */
/* FREQUENCE OF GENRES */
void frequence_of_genres(struct Movie_Name* head_name){
    struct Movie_Name *copy_head, *current_head;
    int counter=0;
    char *genre;
    copy_head=copy_name_list(head_name);
    current_head=head_name;
    genre=(char*)malloc(LEN_STRING*sizeof(char));
    
    
    while(copy_head!=NULL){
        counter=0;
        strcpy(genre,copy_head->genre);
        current_head=copy_head;
        while(current_head!=NULL){
            if(strcmp(current_head->genre,genre)==0)
                 counter++;
            current_head=current_head->next;
        }
        
        printf("%-30s\t%-30d\n",genre,counter);         /* Print the genre name */
        delete_multiple_node(&copy_head,genre);  /* Delete all the occurrences in copy linked list*/
    }                                           /* Do that until all the nodes have been deleted */
    
    /* free(copy_head); */
    free_name_list(&copy_head);
    free(genre);

}


/* ------------------ END ----------------------- */

int main_screen(struct Movie_Name* head_name, struct Movie_Budget* head_budget){
    int operation=0, end_control=0;
    
    while(end_control!=1){
        
        printf("1-)List of the Sorted Data\n");
        printf("2-)List of the Genres\n");
        printf("3-)List of the Movie Through the Years\n");
        printf("4-)List of the Movie Through the Scores\n");
        printf("5-)All Informations of a Single Movie\n");
        printf("6-)Average of IMDB Scores\n");
        printf("7-)Frequence of the Genres\n");
        printf("8-)Exit\n");
        printf("Please select an operation: ");
        if(scanf("%d",&operation)==1){
            switch(operation){
                case 1:
                    list_sorted(head_name,head_budget); /* Sorted data functions */
                    end_control=0;
                break;
                case 2:
                    list_of_genres(head_name);  /* Genre list function */
                    end_control=0;
                break;
                case 3:
                     movie_through_years(head_budget); /* Print movies according to given year and input(until/since )*/
                    end_control=0;
                break;
                case 4:
                    movie_through_scores(head_name); /* Print movies according to given score and input(Less/Greater )*/
                    end_control=0;
                break;
                case 5:
                    single_movie_info(head_name,head_budget); /* All informations about single movie */
                    end_control=0;
                break;
                case 6:
                    average_imdb(head_name);   /* Average of imdb scores */
                    end_control=0;
                break;
                case 7:   
                    frequence_of_genres(head_name); /* Freqeucen of all genres */
                    end_control=0;
                break;
                case 8:
                    end_control=1; /* EXIT */
                break;
                default:
                    printf("TRY AGAIN!\n");
                    end_control=0;
                break;
            }      
        }
        else{
                printf("TRY AGAIN!\n");
                getchar();
                end_control=0;
            }
    }

    return end_control;
}

void free_name_list(struct Movie_Name** head_ref){
    struct Movie_Name*temp=*head_ref;
    struct Movie_Name*next_node;
    while(temp!=NULL){
        next_node=temp->next; /* Keep next node's addres to assign later on */
                             /* Delete alloacated string */
        free(temp);       /* Delete node */
        temp=next_node;  /* Move to next node */
    }
    *head_ref=NULL; /* Lastly make header node free and the given linked list is deleted */
}
void free_budget_list(struct Movie_Budget** head_ref){
    struct Movie_Budget*temp=*head_ref;
    struct Movie_Budget*next_node;
    while(temp!=NULL){
        next_node=temp->next; /* Keep next node's addres to assign later on */
                             /* Delete alloacated string */
        free(temp);       /* Delete node */
        temp=next_node;  /* Move to next node */
    }
    *head_ref=NULL; /* Lastly make header node free and the given linked list is deleted */
}

void push_name_list(struct Movie_Name **head_ref, double score, char* genre, char* movie_name) /* Push Function for Movie_Budget list */
{   /* Push node function for Movie_Budget Linked list*/
 	struct Movie_Name *new_node =(struct Movie_Name *)malloc(sizeof(struct Movie_Name));
    new_node->name=(char*)calloc(LEN_STRING,sizeof(char));
    new_node->genre=(char*)calloc(LEN_STRING,sizeof(char));
    new_node->score = score;
 	strcpy(new_node->genre,genre);
    strcpy(new_node->name,movie_name);
    new_node->next = *head_ref;
 	*head_ref = new_node;
}

void push(struct Movie_Budget **head_ref, int years, int budget, char* movie_name) /* Push Function for Movie_Budget list */
{   /* Push node function for Movie_Budget Linked list*/                           /* This function add node to linked list as a head  and pushes to other elements to end*/
 	struct Movie_Budget *new_node =(struct Movie_Budget *)malloc(sizeof(struct Movie_Budget)); 
    new_node->name=(char*)calloc(LEN_STRING,sizeof(char));
    new_node->years = years;
 	new_node->budget= budget;
    strcpy(new_node->name,movie_name);
    new_node->next = *head_ref;
 	*head_ref = new_node;
}

void delete_node_name(struct Movie_Name **head_ref, struct Movie_Name *deleted_node) /* Delete node function for Movie_Budget list */
{   
    struct Movie_Name *head=*head_ref;
    struct Movie_Name *prev_node=*head_ref;
	
    if(head == deleted_node) /* If to be deleted node is header node */
	{
        if(head->next!=NULL){ /* Otherwise there is only one node in given linked list, last node can be freed in the function that is called from */ 
            strcpy(head->name,head->next->name);            
            strcpy(head->genre,head->next->genre);
            head->score=head->next->score;
            deleted_node = head->next;
            head->next = head->next->next;
            free(deleted_node);
        }

	}
    else{
        while(prev_node->next != NULL && prev_node->next!=deleted_node){
            prev_node = prev_node->next;                  /* Find the deleted node's position in linked list */
        }
        prev_node->next = prev_node->next->next;         /* Linked the previous node next componenet with one later node from deleted_node */
        free(deleted_node);                             /* Free the node */
    }
}


void delete_node(struct Movie_Budget **head_ref, struct Movie_Budget *deleted_node) /* Delete node function for Movie_Budget list */
{   
    struct Movie_Budget *head=*head_ref;
    struct Movie_Budget *prev_node=*head_ref;
	
    if(head == deleted_node)
	{
        if(head->next!=NULL){
            strcpy(head->name,head->next->name);
            head->years=head->next->years;
            head->budget=head->next->budget;
            deleted_node = head->next;
            head->next = head->next->next;
            free(deleted_node); 
        }
	}
    
    else{
        while(prev_node->next != NULL && prev_node->next!=deleted_node){
            prev_node = prev_node->next;
        }
        
        prev_node->next = prev_node->next->next;
        free(deleted_node); /* Delete the given to be deleted node */
    }
	
}




struct Movie_Budget* sort_descending(struct Movie_Budget* head_ref){ /* Rearrange Movie_Budget Linked list in descending order (Year and budget )*/
    struct Movie_Budget* copy_head,*initial_header,*temp, *modified_list;
    int year=0, budget=0, node_count, i=0, counter=0, counter2=0;
    double score;
    char *buffer;
    copy_head=copy_budget_list(head_ref); /* Copy linked list created to make modifications */
    node_count=node_count_budget(copy_head);
    initial_header=copy_head; /* Keep the linked list's header addres*/
    
    buffer=(char*)malloc(LEN_STRING*sizeof(char));
    modified_list=(struct Movie_Budget*)malloc(sizeof(struct Movie_Budget));
    
    if(modified_list==NULL){
        printf("The Heap doesn't have enough memory to allocate new list!\n");
    
    }
    /*Our aim is to sort nodes in descending order,This algorithm will push the first value to the end
    Therfore, I will search for the oldest year and the lowest budget. At the end of this pushing process,
    The nodes will be sorted in descending order automatically because of the pushing node process the oldest year will be the last node */
    else{
    
    
        for(i=0; i<node_count; ++i){    
            year=copy_head->years;
            budget=copy_head->budget;
            counter=0;
            counter2=0;
            while(copy_head!=NULL){
                if(copy_head->years<year){
                    temp=copy_head;
                    year=copy_head->years;
                    budget=copy_head->budget; 
                }
                else if(copy_head->years==year ){                 
                     if(copy_head->budget<=budget){
                            counter=1;
                            temp=copy_head;
                            year=temp->years;
                            budget=temp->budget;
                        }
                        else if(counter==0){   
                            year=copy_head->years;
                            budget=copy_head->budget;
                            temp=copy_head;
                        }
                    
                }
            
                copy_head=copy_head->next;
            }
                
                strcpy(buffer,temp->name);            
                push(&modified_list,temp->years,temp->budget,buffer); /* Push found node to new list */
                delete_node(&initial_header,temp); /* Delete node */
                copy_head=initial_header;  /* Get New header node addres */
        }

        initial_header=modified_list;            /* DELETE THE LAST NODE (NULL NODE)*/
        while(initial_header->next!=NULL){       /* Now we have exactly the same list in descending order, return the new list's header */ 
            initial_header=initial_header->next;
        }
        temp=initial_header;
        delete_node(&modified_list,temp);

        free(head_ref);
        free_budget_list(&copy_head); 
        free(buffer);
        return modified_list;
    }
}

struct Movie_Budget* copy_budget_list(struct Movie_Budget* head_ref){ /* Recursive function to copy Movie_Budget linked list */
    struct Movie_Budget* initial_head=head_ref;                     /* At the of the function it returns the addres of header of copied linked list */
    struct Movie_Budget* copy_list;
    if(head_ref==NULL){
        
         /* Empty list, there is nothing for copying */
        /* Stop condition for recursive */
    }
    else{    
        copy_list=(struct Movie_Budget*)malloc(sizeof(struct Movie_Budget));
        copy_list->name=(char*)calloc(LEN_STRING,sizeof(char*));
        
        if(copy_list==NULL)
            printf("Heap doesn't have enough memorty to keep this !");
        else{
            strcpy(copy_list->name,head_ref->name);
            copy_list->budget=head_ref->budget;
            copy_list->years=head_ref->years;
            copy_list->next=copy_budget_list(head_ref->next);
        }
     head_ref=initial_head;
     return copy_list;
    }
}

struct Movie_Name* copy_name_list(struct Movie_Name* head_ref){  /* Recursive function to copy Movie_Name linked list */
    struct Movie_Name* initial_head=head_ref;                   /* At the of the function it returns the addres of header of copied linked list */
    struct Movie_Name* copy_list, *temp;
    if(head_ref==NULL){
        /* Empty list, there is nothing for copying */
    
    }   /* Stop condition for recursive */
    else{
        copy_list=(struct Movie_Name*)malloc(sizeof(struct Movie_Name));
        copy_list->name=(char*)calloc(LEN_STRING,sizeof(char*));
        copy_list->genre=(char*)calloc(LEN_STRING,sizeof(char*));
        if(copy_list==NULL)
            printf("Heap doesn't have enough memorty to keep this !");
            
        else{
            strcpy(copy_list->name,head_ref->name);
            strcpy(copy_list->genre,head_ref->genre);
            copy_list->score=head_ref->score;
            copy_list->next=copy_name_list(head_ref->next); /* Copy all the data recursively */
        }
     head_ref=initial_head;
     return copy_list; /*Return copy_list */
    }
}


int seperate_string(char *string, struct Movie_Name **name_head_ref, struct Movie_Budget** budget_head_ref){
    int year, budget, line_control=1;
    char *p, *token, *genre, *name;
    double score;
    struct Movie_Name *new_node;
    struct Movie_Budget* new_node_2;
    genre=(char*)malloc(LEN_STRING*sizeof(char));
    name=(char*)malloc(LEN_STRING*sizeof(char));
    token=strtok(string,",");
    if(token==NULL)
        line_control=0;
    else
        budget=strtod(token,&p);
    token=strtok(NULL,",");
    if(token==NULL)
        line_control=0;
    else
        strcpy(genre,token);    
    
    token=strtok(NULL,",");
    if(token==NULL)
       line_control=0;
    else
        strcpy(name,token);
    token=strtok(NULL,",");
    if(token==NULL)
        line_control=0;
    else
        score=strtod(token,&p);    
    token=strtok(NULL,",");
    if(token==NULL)
        line_control=0;
    else
        year=strtod(token,&p);
    if(line_control==1){
        new_node=(struct Movie_Name*)malloc(sizeof(struct Movie_Name));
        new_node->genre=(char*)malloc(LEN_STRING*sizeof(char*));
        new_node->name=(char*)malloc(LEN_STRING*sizeof(char*));
        new_node_2=(struct Movie_Budget*)malloc(sizeof(struct Movie_Budget));
        new_node_2->name=(char*)malloc(LEN_STRING*sizeof(char*));
        
        strcpy(new_node->genre,genre);
        strcpy(new_node->name,name);
        strcpy(new_node_2->name,name);
        new_node->score=score;
        new_node_2->budget=budget;
        new_node_2->years=year;
        new_node->next=*name_head_ref;
        *name_head_ref=new_node;
        new_node_2->next=*budget_head_ref;
        *budget_head_ref=new_node_2;
    }

    free(genre);
    free(name);
    return line_control;
}
 

int node_count_name(struct Movie_Name* head_ref){ /* This function returns total node count for Name function */
    int node_counter=0;
     if(head_ref==NULL){
        printf("Linked list has no node...");
    }
    else{
        while(head_ref!=NULL){
            head_ref=head_ref->next;
            node_counter++;
        }
    }

    return node_counter;
}
int node_count_budget(struct Movie_Budget* head_ref){ /* This function returns current node count for Budget function */
    int node_counter=0;
     if(head_ref==NULL){
        printf("Linked list has no node...");
    }
    else{
        while(head_ref!=NULL){
            head_ref=head_ref->next;
            node_counter++;
        }
    }

    return node_counter;
}

void seperate_file(char *text, struct Movie_Name** head_name, struct Movie_Budget** head_budget){ /* Read text line by line extract the first line( budget-genre-name-score-year) */
    FILE *fp;
    char *buffer, *stat;
    int file_line_count=0;
    fp=fopen(("%s",text),"r");
    if(fp==NULL)
        printf("The text file can not be open.");
    else{
        buffer=(char*)malloc(LEN_STRING*sizeof(char));
        fgets(buffer,LEN_STRING,fp); /*Extract the header*/
        for(stat=fgets(buffer,LEN_STRING,fp); stat!=0; stat=fgets(buffer,LEN_STRING,fp))
            if(seperate_string(buffer,head_name,head_budget)==1) /* Seperate string by using strtod and get the data accordingly */
                file_line_count++;
        
        
        free(buffer);
    }
    fclose(fp);
}
int check_exact_match(struct Movie_Name* head_ref, char* movie_name){ /* Check if input name matches with any movie in List */
    int exact_match_counter=0; 
    int control=0;
    while(head_ref!=NULL){
        if(strcmp(head_ref->name,movie_name)==0)
            exact_match_counter++;
        
        head_ref=head_ref->next;       
    }
    if(exact_match_counter>1)
        control=1;
    else
        control=0;

    return control;
}

void delete_old_data(struct Movie_Name** head_ref,struct Movie_Name** temp,struct Movie_Budget** budget_head_ref,struct Movie_Budget** temp2)
{   struct Movie_Name *head=*head_ref;                                    /* Delete repeated data, later on it will be replaced with new one */
	struct Movie_Name *previous_node = *head_ref;
    struct Movie_Name *tmp=*temp;
    struct Movie_Budget *head_budget=*budget_head_ref;
    struct Movie_Budget *previous_node_budget=*budget_head_ref;
    struct Movie_Budget *tmp2=*temp2;

    /* If the node which is going to be deleted is header node */
	if(head_ref == temp )
	{
        /* Deleting header node in Movie_Name linked list */
        strcpy(head->name,head->next->name);
        strcpy(head->genre,head->next->genre);
		head->score=head->next->score;
		tmp = head->next; /* Next node is going to be header node. Therfore keep the addres of header node to free it*/
		head->next = head->next->next; 
		free(tmp); /* Free the old head's memory */
	
        /* Deleting header node in Movie_Budget linked list */
        strcpy(head_budget->name,head_budget->next->name);
		head_budget->years=head_budget->next->years;
		head_budget->budget=head_budget->next->budget;
        tmp2 = head_budget->next; 
		head_budget->next = head_budget->next->next; 
		free(tmp2); 
    }
    else{
        /* Deleting a random given Node in Movie_Name linked list */
        
        while(previous_node->next!= tmp && previous_node->next != NULL)
            previous_node = previous_node->next;

        previous_node->next = previous_node->next->next; /* The given node reference is deleted in linked list */

        /* Free the memory of deleted node */
        free(tmp);
            /* Deleting a random given Node in Movie_Budget linked list*/
        while(previous_node_budget->next!= tmp2 && previous_node_budget->next != NULL)
            previous_node_budget = previous_node_budget->next;

        previous_node_budget->next = previous_node_budget->next->next; /* The given node reference is deleted in linked list */

        /* Free the memory of deleted node */
        free(tmp2);
    }

}

void update_movie(struct Movie_Name** head_ref,struct Movie_Budget** budget_head_ref,char *movie_name){
    struct Movie_Name *tmp=*head_ref;
    struct Movie_Budget *tmp2=*budget_head_ref;
    tmp=tmp->next; /* Our starting point is going to be the next element after the newest exact movie name */
    tmp2=tmp2->next;
    while(tmp!=NULL || tmp2!=NULL){
        if(strcmp(tmp->name,movie_name)==0) /* They are reading exactly the same file so that there is no need to compare two times */
            delete_old_data(head_ref,&tmp,budget_head_ref,&tmp2); 
        tmp=tmp->next;
        tmp2=tmp2->next;
    }

}

void update_repeated_data(struct Movie_Name**head_name, struct Movie_Budget** head_budget){ /* Update old data with new one */
    struct Movie_Name* head_ref=*head_name;                                                 
    struct Movie_Budget* budget_head_ref=*head_budget;
    char *buffer; 
    buffer=(char*)malloc(LEN_STRING*sizeof(char));
    while(head_ref!=NULL){
        strcpy(buffer,head_ref->name);
        strcpy(buffer,budget_head_ref->name);
        if(check_exact_match(head_ref,buffer)==1){         
            update_movie(&head_ref,&budget_head_ref,buffer);
        }
        budget_head_ref=budget_head_ref->next;
        head_ref=head_ref->next;
    }

    free(buffer);
}