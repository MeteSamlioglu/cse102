#include<stdio.h>
#include<string.h>
#define SIZE 30  /* Max word size */
void fix_spelling_error(char filename1[SIZE],char filename2[SIZE]); /* Main fixing function */
void find_best_correction(char string[SIZE],char filename2[SIZE]); /* This function checks dictionary to find best matching word */
void fix_one_letter_errors(char string[SIZE],char (*word)[SIZE], int word_count); /* This function fixes one letter misspelling */
void fix_spelling_error2(char string[SIZE],char (*word)[SIZE], int word_count);   /* This function fixes two letters misspelling */
void upper_to_lower(char string[],int size); /* This function turns upper letters into lower letters */
void lower_to_upper(char string[SIZE],int upper_indexes[],int upper_index_count);/* This function turns lower letters into upper letters */
int get_upper_indexes(char string[],int upper_indexes[], int size); /* This function gets string index of upper letters */
int check_exact_word(char string[SIZE],char filename2[SIZE]); /* This function checks given string's exact version in dictionary.txt */
int check_vowel_letter(char letter); /* This function checks given string's elements to find vowel letters */

int main(){       /* First argument is for text and the second one is for dictionary */
fix_spelling_error("text.txt","dictionary.txt");/* fix_spelling2 function works inside of find_best_correction function */
}                        /* If given text has two letter misspelled words fix_spelling_error2 function automatically works and corrects them */
                        /* If there is no two letter misspelled words it will only fix one letter misspelled word */
/* If you don't want to fix two letter misspelled mistakes go to find_best_correction function and extract the fix_spelling_error2 function inside of it*/

void upper_to_lower(char string[],int size)
{                 /* This function turns upper letters in given string into lower letters */
   int i=0;
   for(i=0; i<size; ++i)
   {
       if ( string[i] >= 'A' && string[i] <= 'Z' )
       {
          string[i] = string[i] + 32;
       }
    
   }
}

int get_upper_indexes(char string[],int upper_indexes[], int size){
    int i=0;         /* This function finds upper letter indexes in given and keeps them in upper_indexes array */
    int index_counter=0;
   for(i=0; i<size; ++i)
   {
       if ( string[i] >= 'A' && string[i] <= 'Z' )
       {
            upper_indexes[index_counter]=i;
            index_counter++;
       }  
   }
    return index_counter; /* Returns Upper letter count */
}
void lower_to_upper(char string[SIZE],int upper_indexes[],int upper_index_count){
    int i=0, j=0, size;  /* This function turns lower letters in given string into upper letters */
    int counter=0;
    size=strlen(string);
 
    for(i=0; i<size && counter<upper_index_count; ++i){
        if(i==upper_indexes[counter]){
            string[i]=string[i]-32;
            counter++;
        }
    
    }
}

int check_exact_word(char string[SIZE],char filename2[SIZE]){
    FILE *fp;
    int i=0, exact_word_control=0;   /* This function checks all the words in dictionary.txt and finds whether given word misspelled or not*/
    char dictionary[SIZE];              
    fp=fopen(("%s",filename2),"r");
    if (fp == NULL)
        printf("Couldn't open file\n");
    while(fscanf(fp,"%s",dictionary)==1){
        upper_to_lower(dictionary,strlen(dictionary));
        if(strcmp(string,dictionary)==0) 
            exact_word_control=1; 
    }
    fclose(fp);
    return exact_word_control;
}
int check_vowel_letter(char letter){ /* This function checks given character is whether vowel letter or not */
    int vowel_control=0;
    if(letter=='a' || letter=='e' || letter=='i' || letter=='o' 
        || letter=='u')
        vowel_control=1;
    else
        vowel_control=0;

    return vowel_control;
}

void fix_spelling_error2(char string[SIZE],char (*word)[SIZE], int word_count){
int i=0, j=0,incorrect_letter_counter=0, word_counter=0, vowel_counter=0, first_index=0, second_index=0;
int double_vowel_counter=0, one_vowel_counter=0, consonant_counter=0;
char misspelled_letters[100][2], double_vowel[3][2], one_vowel[3][2], consonant[3][2];
  
  for(i=0;i<word_count;++i){             /* Keep all the best matching letters into two dimensional array */
        for(j=0;word[i][j]!='\0';++j){   /* And keep the indexes of misspelled letters */
            if(string[j]!=word[i][j]){
                if(incorrect_letter_counter==0){
                    first_index=j;
                    misspelled_letters[i][0]=word[i][j];
                    incorrect_letter_counter++;
                }
                else if(incorrect_letter_counter==1){
                    second_index=j;
                    misspelled_letters[i][1]=word[i][j];
                    incorrect_letter_counter=0;
                }
            }
        }   
    }
    
    for(i=0; i<word_count; ++i){                             /* Check best matching condition for double vowel letters */
        if(check_vowel_letter(misspelled_letters[i][0])==1)  /* Get first three of them and keep them in two dimensional double_vowel array */
                if(check_vowel_letter(misspelled_letters[i][1])==1){
                    double_vowel[double_vowel_counter][0]=misspelled_letters[i][0];
                    double_vowel[double_vowel_counter][1]=misspelled_letters[i][1];
                    double_vowel_counter++;
                }
        if(double_vowel_counter==3)
            break;
    }
                                                        
    for(i=0; i<word_count; ++i){                              /* Check best matching condition for double vowel letters */
        if(check_vowel_letter(misspelled_letters[i][0])==1){ /* Get first three of them and keep them in two dimensional one_vowel array */
            if(check_vowel_letter(misspelled_letters[i][1])==0){
                one_vowel[one_vowel_counter][0]=misspelled_letters[i][0];
                one_vowel[one_vowel_counter][1]=misspelled_letters[i][1];
                one_vowel_counter++;
            }
        }
        else if(check_vowel_letter(misspelled_letters[i][0])==0){
            if(check_vowel_letter(misspelled_letters[i][1])==1){
                one_vowel[one_vowel_counter][0]=misspelled_letters[i][0];
                one_vowel[one_vowel_counter][1]=misspelled_letters[i][1];
                one_vowel_counter++;
            }
        }
        if(one_vowel_counter==3)
            break;
    }
    
   
    for(i=0; i<word_count; ++i){                              /* Check best matching condition for consonant letters */
        if(check_vowel_letter(misspelled_letters[i][0])==0){ /* Get first three of them and keep them in two dimensional consonant array */ 
            if(check_vowel_letter(misspelled_letters[i][1])==0){
                consonant[consonant_counter][0]=misspelled_letters[i][0];
                consonant[consonant_counter][1]=misspelled_letters[i][1];
                consonant_counter++;
            }
        }
        if(consonant_counter==3)
            break;
    }
    
    
    if(double_vowel_counter>0){   /* Double vowel letters has first a priority, they will be choosen first to fix misspelling*/
        if(double_vowel_counter==1){  /* If there is only one double vowel matching replace misspelled letter with them */
            string[first_index]=double_vowel[0][0];
            string[second_index]=double_vowel[0][1]; /*If there are more than one double vowel matching choose the second occurrence. */
        }
        else{
            string[first_index]=double_vowel[1][0];   /* Replacing letters */
            string[second_index]=double_vowel[1][1];
        }
    }
    else if(one_vowel_counter>0){  /* One vowel and one consonant letters has second a priority, they will be choosen second to fix misspelling*/
        if(one_vowel_counter==1){  /* If there is only one vowel letter and one consonant letter matching, replace misspelled letter with them */
            string[first_index]=one_vowel[0][0];
            string[second_index]=one_vowel[0][1];
        }
        else{     /*If there are more than one couple choose the second occurrence. */
            string[first_index]=one_vowel[1][0];
            string[second_index]=one_vowel[1][1]; /* Replacing letters */
        }
    } 
    else if(consonant_counter>0){ /* Double consonant letters has last priority, they will be choosen thirth to fix misspelling */
        if(consonant_counter==1){  /* If there is only one couple of consonant matching, replace misspelled letter with them */
            string[first_index]=consonant[0][0];
            string[second_index]=consonant[0][1];
        }
        else{ /*If there are more than one couple choose the second occurrence. */
            string[first_index]=consonant[1][0];
            string[second_index]=consonant[1][1]; /* Replacing letters */
        }
    }
}

void fix_one_letter_errors(char string[SIZE],char (*word)[SIZE], int word_count){
    
    int i=0, j=0, word_counter=0, vowel_counter=0,consonant_counter=0, index=0;
    char misspelled_letters[100], vowel_letters[100], consonant_letters[100] ;
 
    for(i=0;i<word_count;++i){         /* Keep best matching words letters which has a same index with misspeled letter */
        for(j=0;word[i][j]!='\0';++j){
            if(string[j]!=word[i][j]){
                index=j;
                misspelled_letters[i]=word[i][j];
            }
        }   
    }
    misspelled_letters[word_count]='\0';

                                          /* Checking which best matching letters are vowel letter */
for(i=0;misspelled_letters[i]!='\0';i++){  
    if(misspelled_letters[i]=='a' || misspelled_letters[i]=='e' || misspelled_letters[i]=='i' || misspelled_letters[i]=='o' 
        || misspelled_letters[i]=='u'){
            vowel_letters[vowel_counter]=misspelled_letters[i];
            vowel_counter++;
        }
    else{ 
            consonant_letters[consonant_counter]=misspelled_letters[i];
            consonant_counter++;
        }
}

    if(vowel_counter==0)       /* Replacing misspeled letter with best matched vowel letter has a priority */
        if(word_count==1)
            string[index]=consonant_letters[0]; /* There is only one matching */

        else 
            string[index]=consonant_letters[1]; /*There is more than one matching, Therefore, second occurence has a priority*/

    else if(vowel_counter==1)   /* There is only one matching */
            string[index]=vowel_letters[0];

    else if(vowel_counter>0)
            string[index]=vowel_letters[1]; /*There is more than one matching, Therefore, second occurence has a priority*/

}


void find_best_correction(char string[SIZE],char filename2[SIZE]){
    int misspelled_letter_counter=0, i=0, counter=0, word_count=0, word_count2=0;
    int upper_index_count=0, size;
    int upper_indexes[SIZE];
    char dictionary[20], words[100][SIZE], words2[100][SIZE]; /* Array to store words in text dictionary */
    FILE *fp;
    fp=fopen(("%s",filename2),"r");
    if (fp == NULL)
            printf("Couldn't open file\n");

    size=strlen(string);
    upper_index_count=get_upper_indexes(string,upper_indexes,size); /* Get index count of  by calling get_upper_indexes function */
    if(upper_index_count!=0)                                        /* And keep this indexes into upper_indexes array */
        upper_to_lower(string,size);     /* Turn upper letters in given string into lower letters to find best matching in dictionary.txt */

    while(fscanf(fp,"%s",dictionary)==1){
        counter=0;
        upper_to_lower(dictionary,strlen(dictionary)); /* To find best matchingn turn every word in dictionary.txt into lower letters*/
        if(strlen(string)==strlen(dictionary)){        /* Searching for same length */
            if(check_exact_word(string,filename2)==0) /* Misspelled word can not be in dictionary.txt */
                for(i=0;i<strlen(string);++i)
                    if(string[i]!=dictionary[i])     /* Finding how many letters misspelled in given string */
                        counter++;
                }
        if(counter==0){ /* Exact match, there will be no changes */
            if(strlen(string)==strlen(dictionary))
                if(check_exact_word(string,filename2)==1)
                    break; 
        }
        else if(counter==1){ /* One letter mistake */
                strcpy(words[word_count],dictionary); /* Keep best matching words for one letter misspelled word in words array */
                word_count++; /*The best matching words count in dictionary.txt count for given one letter misspelled word  */
        }
        else if(counter==2){ /* Two letter mistake */
            strcpy(words2[word_count2],dictionary); /* Keep best matching words for one letter misspelled word in words2 array */
            word_count2++; /*The best matching words count in dictionary.txt count for given two letter misspelled word  */
        }

    }               /*According to misspelled letter count call these functions to fix one letter or two letter misspelled letters */
    if(word_count>0) 
        fix_one_letter_errors(string,words,word_count);

    else if(word_count2>0)                            /* Extract these two lines if you don't want to fix two letter mistakes */
        fix_spelling_error2(string,words2,word_count2);
    
    if(upper_index_count!=0) /* At the end of this process rewrite upper letters the same with its initial version */
        lower_to_upper(string,upper_indexes,upper_index_count);  

    fclose(fp);
}
void fix_spelling_error(char filename1[SIZE],char filename2[SIZE]){
    char string[20], string2[20];
    char pre_punction, post_punction, divider_punction;
    int i=0, punction_counter, option_2=0, divider_punction_index=0, control=0;
    FILE *fp, *fp2;
    fp=fopen(("%s",filename1),"r");    /* fp reads text.txt and gets strings word by word */
    fp2=fopen(("%s",filename1),"r+");  /* fp2 rewrite fixed strings simultaneously */
    if (fp == NULL)
            printf("Couldn't open file\n");   
    if (fp2 == NULL)
            printf("Couldn't open file\n");

    while (fscanf(fp,"%s",string)==1){ /* While blocks gets strings from text.txt and finds this string includes how much punction */
        punction_counter=0;           
        pre_punction='\0';
        post_punction='\0';
        divider_punction='\0';
        divider_punction_index=0;
        option_2=0;                       
        for(i=0; i<strlen(string); ++i){
            if(string[i]==',' || string[i]=='.' || string[i]=='?' || string[i]=='/' || string[i]=='"' || string[i]=='\'' || string[i]=='-'
                || string[i]=='(' || string[i]==')'){
                punction_counter++;
                    if(i==0)
                        pre_punction=string[0];
                    else if(i==strlen(string)-1)
                        post_punction=string[i];
                    else if(i==strlen(string)-2 && string[i]=='\''){ /* Option_2 condition checks "'s" condition for post_punction */
                        post_punction=string[i];
                        option_2=1;
                    }
                    else{
                        divider_punction=string[i];
                        divider_punction_index=i;
                    }
            }
            
        }                    /* This if else blocks works according to punction_counter value,  seperate punctions and strings */
                            /* And after the seperation fixes string by calling find_best_correction function and rewrite it into text.txt */
        
        if(punction_counter==0){  /* If taken string from file includes zero punction this if block starts working */
            find_best_correction(string,filename2); 
            fprintf(fp2,"%s ",string);
        }
        else if(punction_counter==1){  /* If taken string from file includes one punction this else-if block starts working */
            if(pre_punction!='\0'){     /* Only one pre_punction condition */
                strncpy(string,&string[1],strlen(string)-1);
                string[strlen(string)-1]='\0';
                find_best_correction(string,filename2);
                fprintf(fp2,"%c%s ",pre_punction,string);
            }
            else if(post_punction!='\0'){    /* post punction conditions */
                if(option_2==1){        /* 's condition */
                    strncpy(string,string,strlen(string)-2);
                    string[strlen(string)-2]='\0';
                    find_best_correction(string,filename2);
                    fprintf(fp2,"%s%cs ",string,post_punction);
                }
                else{ /* Only one punction after word condition */
                    strncpy(string,string,strlen(string)-1);
                    string[strlen(string)-1]='\0';
                    find_best_correction(string,filename2);
                    fprintf(fp2,"%s%c ",string,post_punction);
                }
            }
            else if(divider_punction!='\0'){
                strncpy(string2,&string[divider_punction_index+1],strlen(string)-1);
                string2[strlen(string)-1]='\0';
                strncpy(string,string,divider_punction_index);
                string[divider_punction_index]='\0';
                find_best_correction(string,filename2);
                find_best_correction(string2,filename2);
                fprintf(fp2,"%s%c%s ",string,divider_punction,string2);
                
            }
        
        }
        else if(punction_counter==2){ /* If taken string from file includes two punction this else-if block starts working */
                if(pre_punction!='\0' && post_punction!='\0'){  /* Rewriting the function which includes pre and post punction*/
                    if(option_2==1){           /* Option 2 condition is "'s" contion for post punction */
                        strncpy(string,&string[1],strlen(string)-1);
                        string[strlen(string)-1]='\0';
                        strncpy(string,string,strlen(string)-2);
                        string[strlen(string)-2]='\0';
                        find_best_correction(string,filename2);
                        fprintf(fp2,"%c%s%cs ",pre_punction,string,post_punction);
                    }
                    else{
                        strncpy(string,&string[1],strlen(string)-1);
                        string[strlen(string)-1]='\0';
                        strncpy(string,string,strlen(string)-1);
                        string[strlen(string)-1]='\0';
                        find_best_correction(string,filename2);
                        fprintf(fp2,"%c%s%c ",pre_punction,string,post_punction);
                    }
                }
                else if(pre_punction!='\0' && divider_punction!='\0'){ /* Rewriting the function which includes pre and divider punction*/
                        strncpy(string,&string[1],strlen(string)-1);
                        string[strlen(string)-1]='\0';                
                        strncpy(string2,&string[divider_punction_index+1],strlen(string)-1);
                        string2[strlen(string)-1]='\0';
                        strncpy(string,string,divider_punction_index);
                        string[divider_punction_index]='\0';
                        find_best_correction(string,filename2);
                        find_best_correction(string2,filename2);
                        fprintf(fp2,"%c%s%c%s ",pre_punction,string,divider_punction,string2);
                    
                    }
                    else if(post_punction!='\0' && divider_punction!='\0'){ /* Rewriting the function which includes post and divider punction*/
                        if(option_2==1){                                    /* option_2==1 example run-time's */
                            strncpy(string,string,strlen(string)-2);
                            string[strlen(string)-2]='\0';
                            strncpy(string2,&string[divider_punction_index+1],strlen(string)-1);
                            string2[strlen(string)-1]='\0';
                            strncpy(string,string,divider_punction_index);
                            string[divider_punction_index]='\0';
                            find_best_correction(string,filename2);
                            find_best_correction(string2,filename2);
                            fprintf(fp2,"%s%c%s%cs ",string,divider_punction,string2,post_punction);
                        }
                        else{                                        /* Rewriting the function which includes post and divider punction*/
                            strncpy(string,string,strlen(string)-1); /* Rewriting without "'s" condition */ 
                            string[strlen(string)-1]='\0';
                            strncpy(string2,&string[divider_punction_index+1],strlen(string)-1);
                            string2[strlen(string)-1]='\0';
                            strncpy(string,string,divider_punction_index);
                            string[divider_punction_index]='\0';
                            find_best_correction(string,filename2);
                            find_best_correction(string2,filename2);
                            fprintf(fp2,"%s%c%s%c ",string,divider_punction,string2,post_punction);

                        
                        }
                    }
                
            }
        }

    fclose(fp);
    fclose(fp2);
}

/* Mehmet Mete Şamlıoğlu */
/* 200104004093 */