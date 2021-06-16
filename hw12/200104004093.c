#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX_LEN 300


typedef struct Synonym{
    char *word_name;
    char (*synonyms)[MAX_LEN];
    int synonym_count;
    int correct;
    int incorrect;
    struct Synonym *next;
}Synonym;


typedef struct Antonym{
  char *word_name;
  char (*antonyms)[MAX_LEN];
  int antonym_count;
  int correct;
  int incorrect;
  struct Antonym* next;
}Antonym;

typedef struct User{
    char *user_name;
    struct User* next;

}User;


Synonym* read_initial_synonyms(char *text, int *synonym_count);
Antonym* read_initial_antonyms(char *text, int *antonym_count);
User* create_new_user(Synonym *head_s, Antonym *head_a, User **head_ref);
Synonym* read_user_synonym(Synonym *head_ref,char *filename, int read_stop_condition);
Antonym* read_user_antonym(Antonym *head_ref,char *filename, int read_start_condition);

void registrated_user_enter(User* head_ref,Synonym *head_s, Antonym *head_a,int synonym_count);
void user_game_screen(Synonym *user_s, Antonym *user_a, Synonym *initial_s, Antonym *initial_a,char *user_name);
void add_new_word(Synonym *head_synonym, Antonym* head_antonym, Synonym *initial_s, Antonym *initial_a);
void ask_random_question(Synonym *user_s, Antonym *user_a, Synonym *head_synonym, Antonym *head_antonym);
void ask_first_question(Synonym *user_s, Antonym *user_a, Synonym *head_synonym, Antonym *head_antonym);
void write_user_data(Synonym *head_s,Antonym *head_a,char *user_name);
void create_synonym_list(char *string, Synonym **head_ref);
void create_antonym_list(char *string, Antonym **head_ref);
void add_antonym_to_list(Antonym *initial_a, Antonym *head_antonym,char* word2, char *new_antonym);
void add_synonym_to_list(Synonym *initial_s, Synonym *head_synonym, char* word, char* new_synonym);
void delete_current_synonym(Synonym **head_ref);
void delete_current_antonym(Antonym **head_ref);
void rewrite_synonyms(Synonym *head_ref, char* synonym_text);
void rewrite_antonyms(Antonym *head_ref, char *antonym_text);

int how_many_words(char* string);
int main_screen(char *synonym_text, char *antonym_text);
int synonym_node_count(Synonym *head_ref);
int antonym_node_count(Antonym *head_ref);
int check_start_condition(Synonym *user_s, Antonym  *user_a);



int main(){
    char *synonyms_text="synonym.txt";
    char *antonyms_text="anytonyms.txt";
    
    while(1){
        if(main_screen(synonyms_text,antonyms_text)==1)
            break;
    }
    

    return 0;
}
int main_screen(char *synonyms_text, char *antonyms_text){
    int option=0, stop_condition=0, synonym_count=0, antonym_count=0, i=0;
    Synonym *synonyms;
    Antonym *antonyms;
    User *head_ref=NULL;
    synonyms=read_initial_synonyms(synonyms_text, &synonym_count); /* Read initial synonyms text */
    antonyms=read_initial_antonyms(antonyms_text, &antonym_count); /* Read initial antonyms text */
  
    
    while(stop_condition!=1){
        printf("1-)New User\n");
        printf("2-)User Login(Set of existing users)\n");
        printf("3-)Exit\n");
        printf("Select an option: ");
        scanf("%d",&option);
        
        switch(option){
            case 1: /* New user registration */
                create_new_user(synonyms,antonyms,&head_ref);
                stop_condition=0;
                break;
            case 2:  /* User enterance */
                registrated_user_enter(head_ref,synonyms,antonyms,synonym_count);
                stop_condition=0;
                break;
            case 3: /* End of the programme */
                rewrite_synonyms(synonyms,synonyms_text); /* Update the initial synonym text */
                rewrite_antonyms(antonyms,antonyms_text); /* Update the initial antonym text */
                delete_current_antonym(&antonyms);
                delete_current_synonym(&synonyms);
                printf("The programme has terminated succesfully..."); 
                stop_condition=1;
                break;
        }

    }
    
    return stop_condition;
}

User* create_new_user(Synonym *head_s, Antonym *head_a, User **head_ref){
    char *name; 
    User *new_user;
    name=(char*)malloc(MAX_LEN*sizeof(char));
    
    printf("New User Registration\n");
    printf("Please enter your name: ");
    scanf(" %[^\n]%*c",name); /* Get the user's name */

    new_user=(User*)malloc(sizeof(User));
    new_user->user_name=(char*)malloc(MAX_LEN*sizeof(char));
    new_user->next=NULL;
    strcpy(new_user->user_name,name);
    new_user->next=(*head_ref);
    (*head_ref)=new_user;

    write_user_data(head_s,head_a,new_user->user_name); /* This function is going to write initial data */

    free(name);
}



void registrated_user_enter(User* head_ref,Synonym *head_s, Antonym *head_a,int synonym_count){
    Synonym * new_user_synonym=NULL;
    Antonym * new_user_antonym=NULL;
    char *name;
    int i=0, counter=0;
    
    
    name=(char*)malloc(MAX_LEN*sizeof(char));
    if(head_ref!=NULL){
        printf("USER LOGIN\n");
        printf("If your data file(.worddat)is in the folder,the programme will automatically read your data even your name is not in the list below\n");
        printf("Set of existing users\n");
        while(head_ref!=NULL){
            printf("%s\n",head_ref->user_name);
            head_ref=head_ref->next;
        }
    }else{
        printf("\n");
    }

    printf("\n");
    printf("The programme will continue your training from where you left\n");
    printf("User Name: ");
    scanf(" %[^\n]%*c",name);    
    
    new_user_synonym=read_user_synonym(head_s,name, synonym_count); 
    new_user_antonym=read_user_antonym(head_a,name, synonym_count); 

    if(new_user_synonym==NULL && new_user_antonym==NULL)
        printf("There is no user with this name, please make a registration.\n");
    else{
        printf("The user's data found and loaded !\n");
        user_game_screen(new_user_synonym,new_user_antonym,head_s, head_a,name);
    }


    free(name);
}
void user_game_screen(Synonym *user_s, Antonym *user_a, Synonym *initial_s, Antonym *initial_a, char *user_name){
    int option=0, stop_condition=0;
    Synonym *user_synonym, *initial_synonym;
    Antonym *user_antonym, *initial_antonym;

    while(stop_condition!=1){
        user_synonym=user_s;
        user_antonym=user_a;
        initial_synonym=initial_s;
        initial_antonym=initial_a;
        printf("\n1-)Ask a random question");
        printf("\n2-)Add new antonym or synonym to any word in list");
        printf("\n3-)Exit and back to main screen");
        printf("\nSelect an option: ");
        scanf("%d",&option);    
    
        switch(option){
            case 1:
                ask_random_question(user_synonym,user_antonym,initial_synonym,initial_antonym); /* Ask a random question */
                stop_condition=0;
                break;

            case 2:
                add_new_word(user_synonym,user_antonym,initial_synonym,initial_antonym); /* Add a new word for either synonyms or antonyms */
                stop_condition=0;
                break;
                

            case 3:                
                write_user_data(user_synonym,user_antonym,user_name);  /* Save user's current data to the binary file */
                delete_current_synonym(&user_synonym);                 /* Delete user's the synonym node list to avoid memory leak */
                delete_current_antonym(&user_antonym);                 /* Delete user's the antonym node list to avoid memory leak */
                stop_condition=1;                                      /* Note that the main synonym and antonym list will not affect after this process */
                break;                                                 /* The main node lists for both synonym and antoynm will not be deleted till the end of the programme */
                                                                        /* At the end of the programme the updated list will be reflected in the initial files */
        }
        
    }   
}

void add_new_word(Synonym *head_synonym, Antonym* head_antonym, Synonym *initial_s, Antonym *initial_a){ /* To add a new synonym or antonym to the list */
    int option=0, control=0, i=0;                                                                       
    char *word,*word2, *new_synonym, *new_antonym;
    
    word=(char*)malloc(MAX_LEN*sizeof(char));
    word2=(char*)malloc(MAX_LEN*sizeof(char));
    new_synonym=(char*)malloc(MAX_LEN*sizeof(char));
    new_antonym=(char*)malloc(MAX_LEN*sizeof(char));

    printf("1-)Add word to synonyms\n");
    printf("2-)Add word to antonyms\n");
    printf("Select an option: ");
    scanf("%d",&option);

    if(option==1){
        printf("Enter the name of word that you want to add a new synonym for it:");
        scanf(" %[^\n]%*c",word);
        fflush(stdin);

        while(head_synonym!=NULL){
            if(strcmp(head_synonym->word_name,word)==0){ /* Check matching */
               control=1;
               break; 
            }            
            head_synonym=head_synonym->next;
            initial_s=initial_s->next;
        }
        if(control==1){
            printf("Enter a new synonym for %s:",head_synonym->word_name);
            scanf(" %[^\n]%*c",new_synonym);
            add_synonym_to_list(initial_s,head_synonym,word,new_synonym); 
        }
        else
            printf("\nThe word you entered is not exist in the synonym text, please enter a valid word name");

    }
    else if(option==2){
       
        printf("Enter the name of word that you want to add a new antonym for it:");
        scanf(" %[^\n]%*c",word2);

        while(head_antonym!=NULL){
            if(strcmp(head_antonym->word_name,word2)==0){ 
               control=1;
               break; 
            }            
            head_antonym=head_antonym->next;
            initial_a=initial_a->next;
        }
        if(control==1){
            printf("Enter a new antonym for %s:",head_antonym->word_name);
            scanf(" %[^\n]%*c",new_antonym);       
            add_antonym_to_list(initial_a,head_antonym,word2,new_antonym);

        }
        else
            printf("The word you entered is not exist in the antonym text, please enter a valid word name\n");
    
    }
    
    free(word);
    free(word2);
    free(new_synonym);
    free(new_antonym);
}

void ask_random_question(Synonym *user_s, Antonym * user_a, Synonym *head_synonym, Antonym *head_antonym){
    int check_probability=0,random_node_synonym=0, random_node_antonym=0, question_type=0, synonym_count=0, antonym_count=0;
    int counter=0, i=0, j=0, probability_denaminator=0, x=0, control=0, save_option=0, control2=0;
    char *synonym_guess, *antonym_guess;
    Synonym *user_synonym=user_s, *initial_synonym=head_synonym;
    Antonym *user_antonym=user_a, *initial_antonym=head_antonym;

    synonym_guess=(char*)malloc(MAX_LEN*sizeof(char));
    antonym_guess=(char*)malloc(MAX_LEN*sizeof(char));


    if(check_start_condition(user_s,user_a)==1) /* The user has not data which means user never trained before */
        ask_first_question(user_s,user_a,head_synonym,head_antonym); /* First question*/
    
    else{
        /* First of all since we have two node list, first we need to choose one of them randomly to start searching for the question */
        /* According to pdf rules this question type may change later, but to start from somewhere first we need to know question type */
            synonym_count=synonym_node_count(head_synonym);
            antonym_count=antonym_node_count(head_antonym);
            srand(time(NULL));
            question_type=rand()%2+1; /* it will return 1 or 2 */
                
            if(question_type==1){ /* Use synonym list */
                while(1){                                             /* Get random node */
                    srand(time(NULL));                                /* Now the possibility is 1/(curret_synonym_count) */
                    counter=0;
                    random_node_synonym=rand() % synonym_count + 1;   /* We get our random node which is selected randomly */             
            
                    while(user_synonym!=NULL){
                        if(random_node_synonym==counter+1)      /* Find the chosen node */
                            break;                            
                        
                        initial_synonym=initial_synonym->next;
                        user_synonym=user_synonym->next; 
                        counter++;
                    }
                        
                        if(user_synonym->incorrect==0 && user_synonym->correct==0){  /* The highest probability for not seletcted words*/
                                break;                                               /* At the beginnig every node has equal probability, but later on */
                        }                                                           /* not selected words will have higher probability. Therefore this if block represents*/
                                                                                     /* 1/(current_synonym_count) probability which is the higher one */   

                        else{
                            while(1){                         /* For the selected words, if one of them has more incorrect answer it has a higher probabilty to be picked */
                                initial_synonym=head_synonym; /* This else block is for the words which are already asked */
                                user_synonym=user_s;           /* PDF 4.c */ 
                                control=0;
                                while(user_synonym!=NULL){
                                    if(user_synonym->correct!=0 && user_synonym->incorrect!=0){
                                        srand(time(NULL));
                                        x=rand() % 9 + 1;
                                        if(user_synonym->incorrect>user_synonym->correct){   /* In this case the words which have more incorrect answers has 7/10 probability*/
                                            if(x>=4 && x<=10){                               /* And the words which has more or equal correct answer has 3/10 probability */
                                                control=1;                                 
                                                break;
                                            }
                                        }
                                        else{
                                            if(x>=1 && x<4){
                                                control=1;
                                                break;
                                            }
                                        }    

                                    }

                                initial_synonym=initial_synonym->next; 
                                user_synonym=user_synonym->next;
                                }
                                if(control==1)
                                    break;
                            }
                            
                            probability_denaminator=user_synonym->correct+user_synonym->incorrect; /* PDF 4.b */
                            srand(time(NULL));                                  /* At the end of above process the current probability will be 1/current_synonym_count */
                            x = rand()%probability_denaminator+1;               /* But in here it will multiply with 1/(occurance_time) */        
                            if(x==1)  /*1/probability_demaninator*/           /* Lets say this question already asked four times it will multiply with 1/4 */
                                break;                                          /* And the total probability for selected word is going to be */
                                                                                /* (1/occurance_time)*(1/current_synonym_count) */
                            x=0;                        
                            probability_denaminator=0;
                        }
                      
                      initial_synonym=head_synonym;             /* If conditions are not provided continue to the process */
                      user_synonym=user_s;
                }
                
                control=0; 
                
                printf("What is the synonym of %s:",user_synonym->word_name);       /* Ask to related question after the probability calculation */
                scanf(" %[^\n]%*c",synonym_guess);
                                                                                    
                for(i=0; i<user_synonym->synonym_count; ++i)
                    if(strcmp(user_synonym->synonyms[i], synonym_guess)==0){
                        control=1;
                        break;
                    }
                if(control==1){
                    printf("Your answer is correct ! Correct answer is added to your data.\n");
                    user_synonym->correct=1;
                }
                else if(control==0){                                        /* Add question and its answers to user's data */
                    printf("Your anser is incorrect!\n");
                    printf("Would you like to save %s as a new synonym Yes(1)| No(2) :",synonym_guess);
                    scanf("%d",&save_option);
                
                    if(save_option==1){
                        user_synonym->incorrect=1;
                        add_synonym_to_list(head_synonym,user_s,user_synonym->word_name, synonym_guess); /* Add user's word to the list */
                        
                    }
                    else
                        user_synonym->incorrect=1;    
                }  
            
            }
            
            else if(question_type==2){ /* Antonym Question  */
                
                while(1){                                             /* Get random node */
                    srand(time(NULL));
                    counter=0;                                     /* Exactly the same algorithm with synoynm the diffrences between them will be after the probability calculation*/
                    random_node_antonym=rand() % antonym_count + 1;                
            
                    while(user_antonym!=NULL){
                        if(random_node_antonym==counter+1)
                            break;                            
                        
                        initial_antonym=initial_antonym->next;
                        user_antonym=user_antonym->next; 
                        counter++;
                    }
                        
                        if(user_antonym->incorrect==0 && user_antonym->correct==0){  /* The highest probability for not seletcted words*/
                                break;
                        }
                        else{
                            while(1){                         /* For the selected words, if one of them has more incorrect answer it has a higher probabilty to be picked */
                                initial_antonym=head_antonym; /* This else block is for the words which are already asked */
                                user_antonym=user_a;           /* PDF 4.c */ 
                                control=0;
                                while(user_antonym!=NULL){
                                    if(user_antonym->correct!=0 && user_antonym->incorrect!=0){
                                        srand(time(NULL));
                                        x=rand() % 9 + 1;
                                        if(user_antonym->incorrect>user_antonym->correct){
                                            if(x>=4 && x<=10){ /* 7/10 probability */
                                                control=1;
                                                break;
                                            }
                                        }
                                        else{
                                            if(x>=1 && x<4){ /* 3/10 probability */
                                                control=1;
                                                break;
                                            }
                                        }    

                                    }

                                initial_antonym=initial_antonym->next; 
                                user_antonym=user_antonym->next;
                                }
                                if(control==1)
                                    break;
                            }
                            
                            probability_denaminator=user_antonym->correct+user_antonym->incorrect; /* PDF 4.b */
                            srand(time(NULL));
                            x = rand()%probability_denaminator+1;
                            if(x==1)
                                break;
                           
                            x=0;                        
                            probability_denaminator=0;
                        }
                      
                      initial_antonym=head_antonym;
                      user_antonym=user_a;
                }
        /* Special condition for antonym (PDF 4.b) : If one word is asked twice for antonyms, 
        then this word will have twice the probability to be selected for a synonym questions compared to the antonym question. */
                
                x=0;
                control=0;
                user_synonym=user_s;
                initial_synonym=head_synonym;
                while(user_synonym!=NULL){                       /* Condition 1-) The synonym list must have this word (Must be a commonw word for both */
                    if(strcmp(user_synonym->word_name,user_antonym->word_name)==0){ 
                        control=1;        
                        break;
                    }

                    user_synonym=user_synonym->next;
                    initial_synonym=initial_synonym->next;
                }                                                       /* Condition 2 */
                if((user_antonym->correct+user_antonym->incorrect)==2) /* This word must have been selected 2 times */
                    control2=1;
               
                x=rand()%2+1; /* Condition 3-) If this word provides the conditions above, it will have twice probability to be selected */

                
                if(control2==1 && control==1 && (x==2 || x==3)){ /* All the conditions are provided, This word is going to be asked for synonyms*/
                        control=0;
                        printf("What is the synonym of %s:",user_synonym->word_name);
                        scanf(" %[^\n]%*c",synonym_guess);
                    
                    for(i=0; i<user_synonym->synonym_count; ++i)
                        if(strcmp(user_synonym->synonyms[i], synonym_guess)==0){
                            control=1;
                            break;
                        }
                    if(control==1){
                        printf("Your answer is correct ! Correct answer is added to your data.\n");
                        user_synonym->correct=1;
                    }
                    else if(control==0){
                        printf("Your answer is incorrect!\n");
                        printf("Would you like to save %s as a new synonym Yes(1)| No(2) :",synonym_guess);
                        scanf("%d",&save_option);
                    
                        if(save_option==1){
                            user_synonym->incorrect=1;
                            add_synonym_to_list(head_synonym,user_s,user_synonym->word_name, synonym_guess);
                            
                        }
                        else
                            user_synonym->incorrect=1;                        } 

                }
                else{   /* Otherwise continue to the normal process */
                    control=0;
                   
                    printf("What is the antonym of %s:",user_antonym->word_name);
                    scanf(" %[^\n]%*c",antonym_guess);
                    
                    for(i=0; i<user_antonym->antonym_count; ++i)
                        if(strcmp(user_antonym->antonyms[i], antonym_guess)==0){  /* Check correct condition */
                            control=1;
                            break;
                        }
                    if(control==1){
                        printf("Your answer is correct ! Correct answer is added to your data.\n"); /* Save data for user */
                        user_antonym->correct=1; 
                    }
                    else if(control==0){
                        printf("Your answer is incorrect!\n");
                        printf("Would you like to save %s as a new antonym Yes(1)| No(2) :",antonym_guess);
                        scanf("%d",&save_option);
                    
                        if(save_option==1){
                            user_antonym->incorrect=1;
                            add_antonym_to_list(head_antonym,user_a,user_antonym->word_name, antonym_guess); /* Add word to the list */
                        }
                        else
                            user_antonym->incorrect=1;    
                    }  
                
                }
            }
    }

    free(synonym_guess);
    free(antonym_guess);
}

void ask_first_question(Synonym *user_s, Antonym *user_a, Synonym *head_synonym, Antonym *head_antonym){
/* Start with initial condition, No word has been selected yet check this condition */
    Synonym *user_synonym=user_s, *head_s=head_synonym;
    Antonym *user_antonym=user_a, *head_a=head_antonym;

    int i=0, j=0, counter=0;
    int question_type=0, synonym_count=0, antonym_count=0, random_node=0, control=0, save_option=0;
    char *synonym_guess, *antonym_guess;

    synonym_count=synonym_node_count(head_s);
    antonym_count=antonym_node_count(head_a);
    synonym_guess=(char*)malloc(MAX_LEN*sizeof(char));
    antonym_guess=(char*)malloc(MAX_LEN*sizeof(char));
        /* User just started to play, he/she has no correct or incorrect answer */
       /* Choose random type question for new user */
        srand(time(NULL));
        question_type=rand()%2+1; /* it will return 1 or 2 randomly */
        if(question_type==1){ /* Ask synonym as a first qeustion */
            random_node=rand()% synonym_count +1;
            while(head_s!=NULL){
                if(random_node==counter+1)
                    break;
                user_s=user_s->next;
                head_s=head_s->next;  
                counter++;
            }
            printf("What is the synonym of %s:",user_s->word_name);
            scanf(" %[^\n]%*c",synonym_guess);

            for(i=0; i<user_s->synonym_count; ++i)
                if(strcmp(user_s->synonyms[i], synonym_guess)==0){
                    control=1;
                    break;
                }

            if(control==1){
                printf("Your answer is correct ! Correct answer was added to your data.\n");
                user_s->correct=1;
            }
            else if(control==0){
                printf("Your anser is incorrect!\n");
                printf("Would you like to save %s as a new synonym Yes(1)| No(2) :",synonym_guess);
                scanf("%d",&save_option);

                if(save_option==1){
                    add_synonym_to_list(head_synonym,user_synonym,user_s->word_name, synonym_guess);
                    user_s->incorrect=1;
                }
                else
                    user_s->incorrect=1;
                
            }
        }
        else if(question_type==2){ /* Antonym question random */
            random_node=rand()% antonym_count+1;
            while(head_a!=NULL){
                if(random_node==counter+1)
                    break;
                user_a=user_a->next;
                head_a=head_a->next;  
                counter++;
            }
            printf("What is the antonym of %s:",user_a->word_name);
            scanf(" %[^\n]%*c",antonym_guess);

            for(i=0; i<user_a->antonym_count; ++i)
                if(strcmp(user_a->antonyms[i], antonym_guess)==0){
                    control=1;
                    break;
                }

            if(control==1){
                printf("Your answer is correct ! Correct answer was added to your data.\n");
                user_s->correct=1;
                user_a->correct=1;
            }
            else if(control==0){
                printf("Your answer is incorrect!\n");
                printf("Would you like to save %s as a new antonym Yes(1)|No(2) :",antonym_guess);
                scanf("%d",&save_option);

                if(save_option==1){
                    add_antonym_to_list(head_antonym,user_antonym,user_a->word_name,antonym_guess);
                    user_s->incorrect=1;
                }
                else
                    user_s->incorrect=1;
            
            }        
        }
    


    free(antonym_guess);
    free(synonym_guess);
}

int check_start_condition(Synonym *user_s, Antonym  *user_a){ /* This function checks that if user made any training before */
    
    int first_control=0, second_control=0, check_start_condition=0;
    
    while(user_s!=NULL){
        if(user_s->correct!=0 || user_s->incorrect!=0){
            first_control=1;
            break;
        }
        user_s=user_s->next;
        
    }    

    while(user_a!=NULL){
        if(user_a->correct!=0 || user_a->incorrect!=0){
            second_control=1;
            break;
        }
        user_a=user_a->next;    
    }
    
    if(first_control==0 && second_control==0)
        check_start_condition=1;
    
    else
        check_start_condition=0;


    return check_start_condition;

}

void add_synonym_to_list(Synonym *initial_s, Synonym *head_synonym, char* word, char* new_synonym){ /* To add a new entry for current synonyms */
    int i=0;
    
    while(head_synonym!=NULL){
            if(strcmp(head_synonym->word_name,word)==0){
               break; 
            }            
            head_synonym=head_synonym->next;
            initial_s=initial_s->next;
    }
    head_synonym->synonym_count=head_synonym->synonym_count+1; /* size + 1 */
    head_synonym->synonyms=calloc(head_synonym->synonym_count,sizeof(*head_synonym->synonyms)); /* Rearrange 2D array */
    for(i=0; i<initial_s->synonym_count; ++i)
        strcpy(head_synonym->synonyms[i],initial_s->synonyms[i]);
        strcpy(head_synonym->synonyms[initial_s->synonym_count], new_synonym);
        /* We are done with copying into user linked list */   
        /* Now modify the rest initial linked list */
        initial_s->synonym_count=initial_s->synonym_count+1;
        initial_s->synonyms=calloc(initial_s->synonym_count,sizeof(*initial_s->synonyms)); 

    for(i=0; i<initial_s->synonym_count; ++i)
        strcpy(initial_s->synonyms[i],head_synonym->synonyms[i]);


}

void add_antonym_to_list(Antonym *initial_a, Antonym *head_antonym,char* word2, char *new_antonym){ /* To add a new entry for current antonyms */
    int i=0;

    while(head_antonym!=NULL){
        if(strcmp(head_antonym->word_name,word2)==0){
            break; 
        }            
        head_antonym=head_antonym->next;
        initial_a=initial_a->next;
    }
    
    
    head_antonym->antonym_count=head_antonym->antonym_count+1;    
    head_antonym->antonyms=calloc(head_antonym->antonym_count,sizeof(*head_antonym->antonyms)); 
    for(i=0; i<initial_a->antonym_count; ++i)
        strcpy(head_antonym->antonyms[i],initial_a->antonyms[i]);

        strcpy(head_antonym->antonyms[initial_a->antonym_count],new_antonym);
        
        initial_a->antonym_count=initial_a->antonym_count+1;
        initial_a->antonyms=calloc(initial_a->antonym_count,sizeof(*initial_a->antonyms));

    for(i=0; i<initial_a->antonym_count; ++i)
        strcpy(initial_a->antonyms[i],head_antonym->antonyms[i]);    
    
    
}



void delete_current_synonym(Synonym **head_ref){ /* It deletes the current synonym node list which is created for user's data, and frees all the data in this node list */
    Synonym *node=*head_ref;
    Synonym *node_next=NULL;

    while(node!=NULL){
        node_next=node->next;
        free(node);
        node=node_next;
    }
    
    *head_ref=NULL;
}



void delete_current_antonym(Antonym **head_ref){ /* It deletes the current antonym node list which is created for user's data, and frees all the data in this node list */
    Antonym *node=*head_ref;
    Antonym *node_next=NULL;

    while(node!=NULL){
        node_next=node->next;
        free(node);
        node=node_next;
    }
    
    *head_ref=NULL;
}


                                                                                         /* It reads the user's worddat binary file and get the data accordingly */
Synonym* read_user_synonym(Synonym *head_ref,char *filename, int read_stop_condition){   /* It builds a synonym node list from the data which is read by the user's binary file */
    FILE* pf;    
    Synonym* head, *previous_node; 
    Synonym *temp, *initial;
    int i=0, counter=0;

    initial=head_ref;
    temp=(Synonym*)malloc(sizeof(Synonym));
    temp->word_name=(char*)malloc(MAX_LEN*sizeof(char));
    
    head = NULL;
    previous_node=NULL;
    pf = fopen (("%s.worddat",filename), "rb");
    
    if (pf == NULL)
    {
        printf("The %s's user's Synonyms data can not be found ! \n",filename);
        head=NULL;
    }
    else{
        
        while(fread(temp, sizeof(Synonym), 1, pf))
        {
            if(head==NULL)
            {
                head = (Synonym*)malloc(sizeof(Synonym));
                head->word_name=(char*)malloc(MAX_LEN*sizeof(char));
                strcpy(head->word_name,initial->word_name);
                head->correct=temp->correct;
                head->incorrect=temp->incorrect;
                head->synonym_count=temp->synonym_count;   
                head->synonyms=calloc(head->synonym_count,sizeof(*head->synonyms));
                for(i=0; i<head->synonym_count; ++i)
                    strcpy(head->synonyms[i],initial->synonyms[i]); 
                
                previous_node=head;
                previous_node->next=NULL;
            }
            else
            {
                previous_node->next=(Synonym*)malloc(sizeof(Synonym));
                previous_node=previous_node->next;
                previous_node->word_name=(char*)malloc(MAX_LEN*sizeof(char));
                strcpy(previous_node->word_name, initial->word_name);
                previous_node->correct=temp->correct;
                previous_node->incorrect=temp->incorrect;
                previous_node->synonym_count=temp->synonym_count;
                
                previous_node->synonyms=calloc(previous_node->synonym_count,sizeof(*previous_node->synonyms));

                for(i=0; i<previous_node->synonym_count; ++i)
                   strcpy(previous_node->synonyms[i],initial->synonyms[i]); 
                

                previous_node->next=NULL;
            }
            
            counter++;
            initial=initial->next;
            
            if(counter==read_stop_condition)
                break;

        }

            fclose(pf);
    }    

        return head;
}

Antonym* read_user_antonym(Antonym *head_ref,char *filename, int read_start_condition){ /* It reads the user's worddat binary file and get the data accordingly */
    FILE* pf;                                                                           /* It builds an antonym node list from the data which is read by the user's binary file */
    Antonym* head, *previous_node; 
    Antonym *temp, *initial;
    int i=0, counter=0;

    initial=head_ref;
    temp=(Antonym*)malloc(sizeof(Antonym));
    temp->word_name=(char*)malloc(MAX_LEN*sizeof(char));

    head = NULL;
    previous_node=NULL;
    pf = fopen (("%s.worddat",filename), "rb");

    if (pf == NULL)
    {
        printf("The %s's user's Antonyms data can not be found ! \n",filename);
        head=NULL;
    }
    else{

        while(fread(temp, sizeof(Antonym), 1, pf))
        {
            if(counter>=read_start_condition){      
                if(head==NULL)
                {
                    head = (Antonym*)malloc(sizeof(Antonym));
                    head->word_name=(char*)malloc(MAX_LEN*sizeof(char));
                    strcpy(head->word_name,initial->word_name);
                    head->antonym_count=temp->antonym_count;
                    head->correct=temp->correct;      /* Check if given antonym question have correct answer */ 
                    head->incorrect=temp->incorrect; /* Check if given antonym question have incorrect answer  */
                    
                    head->antonyms=calloc(head->antonym_count,sizeof(*head->antonyms));
                    for(i=0; i<head->antonym_count; ++i)
                        strcpy(head->antonyms[i],initial->antonyms[i]);
                    
                    previous_node=head;
                    previous_node->next=NULL;
                }
                else
                {
                    previous_node->next=(Antonym*)malloc(sizeof(Antonym));
                    previous_node=previous_node->next;
                    previous_node->word_name=(char*)malloc(MAX_LEN*sizeof(char));
                    strcpy(previous_node->word_name, initial->word_name);
                    previous_node->antonym_count=temp->antonym_count;
                    previous_node->correct=temp->correct;
                    previous_node->incorrect=temp->incorrect;
                    previous_node->antonyms=calloc(previous_node->antonym_count,sizeof(*previous_node->antonyms));

                    for(i=0; i<previous_node->antonym_count; ++i)
                        strcpy(previous_node->antonyms[i],initial->antonyms[i]);

                    previous_node->next=NULL;
                }
                    initial=initial->next;
            }
                 counter++;
        }
        fclose(pf);
    }

        return head;
}


void write_user_data(Synonym *head_s,Antonym *head_a,char *user_name){ /* It writes  the user's data to worddat binary file, after user completed his/her training */
    FILE *fp;
    Synonym *temp=head_s;
    Antonym *temp2=head_a;
    int i=0;
    fp=fopen(("%s.worddat",user_name),"wb");
    if(fp==NULL)
        printf("The user file could not be opened !");
    else{
        while(temp!=NULL){
            fwrite(temp,sizeof(Synonym),1,fp);
            temp=temp->next;
        }
        while(temp2!=NULL){
            fwrite(temp2,sizeof(Antonym),1,fp);
            temp2=temp2->next;
        }

        if(fwrite==0)
            printf("Something went wrong, the writing process did not happen !");
    }
    
    fclose(fp);
}


Synonym *read_initial_synonyms(char *text, int *synonym_count){ /* It reads initial synonym text and seperate it according to data order */
    FILE *fp;
    Synonym *head_ref=NULL;
    char *buffer, *status;
    int counter=0, i=0;
    fp=fopen(("%s",text),"r");
    if(fp==NULL)
        printf("The file could not be opened !");
    buffer=(char*)malloc(MAX_LEN*sizeof(char));
    for(status=fgets(buffer,MAX_LEN,fp); status!=0; status=fgets(buffer,MAX_LEN,fp)){
        create_synonym_list(buffer,&head_ref);       
        counter++;
    }
    
    *synonym_count=counter;
    
    free(buffer);
    return head_ref;
}

Antonym* read_initial_antonyms(char *text, int *antonym_count){ /* It reads initial antonym text and seperate it according to data order */
    FILE *fp;
    Antonym *head_ref=NULL;
    char *buffer, *status;
    int counter=0, i=0;
    fp=fopen(("%s",text),"r");
    if(fp==NULL)
        printf("The file could not be opened !");
    buffer=(char*)malloc(MAX_LEN*sizeof(char));
    for(status=fgets(buffer,MAX_LEN,fp); status!=0; status=fgets(buffer,MAX_LEN,fp)){
        create_antonym_list(buffer,&head_ref);       
        counter++;
    }
    *antonym_count=counter;

    free(buffer);
    return head_ref;
}

void create_synonym_list(char *string, Synonym **head_ref){ /* This function seperates the string and creates synonym node list */
    Synonym *new_node, *temp=*head_ref, *initial_head=*head_ref;
    char *buffer, *token;
    int synonyms_count=0, i=0;

    new_node=(Synonym*)malloc(sizeof(Synonym));
    buffer=(char*)malloc(MAX_LEN*sizeof(char));
    strcpy(buffer,string);
    synonyms_count=how_many_words(buffer);
    
    if(string[strlen(string)-1]=='\n'){
        string[strlen(string)-1]='\0';
    }
    
    new_node->synonym_count=synonyms_count;
    new_node->correct=0;
    new_node->incorrect=0;
    new_node->next=NULL;
    new_node->synonyms=calloc(synonyms_count,sizeof(*new_node->synonyms));
    new_node->word_name=(char*)malloc(MAX_LEN*sizeof(char));
    token=strtok(string," |,");
    strcpy(new_node->word_name,string);

    token=strtok(NULL, " |,");
    while(token!=NULL){
        strcpy(new_node->synonyms[i],token);
        token=strtok(NULL, " |,");
        i++;
    }
    
    if(*head_ref==NULL)
        *head_ref=new_node;    
    
    else{
        while(temp->next!=NULL)
            temp=temp->next;       /* Find the last node of current linked list */
        
            temp->next=new_node; /* Make the new node last node of the linked list */
    }

   free(buffer);
}


void create_antonym_list(char *string, Antonym **head_ref){  /* This function seperates the string and creates an antonym node list */
    Antonym *new_node, *temp=*head_ref, *initial_head=*head_ref;
    char *buffer, *token;
    int antonym_count=0, i=0;

    new_node=(Antonym*)malloc(sizeof(Antonym));
    buffer=(char*)malloc(MAX_LEN*sizeof(char));
    strcpy(buffer,string);
    antonym_count=how_many_words(buffer);
    
    if(string[strlen(string)-1]=='\n')
        string[strlen(string)-1]='\0';
    if(string[strlen(string)-1]==13)
        string[strlen(string)-1]=='\0';    
      
    new_node->antonym_count=antonym_count;
    new_node->correct=0;
    new_node->incorrect=0;
    new_node->next=NULL;
    new_node->antonyms=calloc(antonym_count,sizeof(*new_node->antonyms));
    new_node->word_name=(char*)malloc(MAX_LEN*sizeof(char));
    token=strtok(string," |,");
    strcpy(new_node->word_name,string);

    token=strtok(NULL, " |,");
    while(token!=NULL){
        strcpy(new_node->antonyms[i],token);
        token=strtok(NULL, " |,");
        i++;
    }
    
    new_node->antonyms[new_node->antonym_count-1][strlen(new_node->antonyms[new_node->antonym_count-1])-1]='\0'; /* To avoid endless string(without \t)for last element of 2D anonyms array*/
    

    if(*head_ref==NULL)
        *head_ref=new_node;    
    
    else{
        while(temp->next!=NULL)
            temp=temp->next;       /* Find the last node of current linked list */
        
            temp->next=new_node; /* Make the new node last node of the linked list */
    }

   free(buffer);
}

int how_many_words(char *string){ /* Returns given sentence includes how many words (total word -1 )*/
    char *token;
    int word_count=0;
    token = strtok (string," |,");
    while (token != NULL){
        token = strtok (NULL, " |,");
        word_count++;
    }
   word_count--;  
  
  return word_count;

}
int synonym_node_count(Synonym *head_ref){ /* Returns current node count for synonym node list */
    int node_count=0;

    while(head_ref!=NULL){
        node_count++;
        head_ref=head_ref->next;
    }

    return node_count;
}

int antonym_node_count(Antonym *head_ref){ /* Returns current node count for antonym node list */
    int node_count=0;
    while(head_ref!=NULL){
        node_count++;
        head_ref=head_ref->next;

    }
    return node_count;
}

void rewrite_synonyms(Synonym *head_ref, char* synonym_text){ /* To write syonym node list to the initial synonym file */
    FILE *fp;
    int i=0;
    
    fp=fopen(("%s",synonym_text),"w");
    if(fp==NULL)
        printf("The file could not opened ");
    else{
        while(head_ref!=NULL){
            fprintf(fp,"%s|",head_ref->word_name);
            for(i=0; i<head_ref->synonym_count; ++i){
                if(i==head_ref->synonym_count-1)
                    fprintf(fp,"%s\n",head_ref->synonyms[i]);
                else
                    fprintf(fp,"%s,",head_ref->synonyms[i]);

            }
            head_ref=head_ref->next;
        }
    }

    fclose(fp);
}

void rewrite_antonyms(Antonym *head_ref, char *antonym_text){ /* To write antonym node list to the initial antonym file */
    FILE *fp;
    int i=0;
   
    fp=fopen(("%s",antonym_text),"w");
    if(fp==NULL)
        printf("The file could not opened ");
    else{
        while(head_ref!=NULL){
            fprintf(fp,"%s|",head_ref->word_name);
            for(i=0; i<head_ref->antonym_count; ++i){
                if(i==head_ref->antonym_count-1)
                    fprintf(fp,"%s\n",head_ref->antonyms[i]);
                else
                    fprintf(fp,"%s,",head_ref->antonyms[i]);

            }
            head_ref=head_ref->next;
        }
    }
    fclose(fp);
}




