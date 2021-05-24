#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STRING 150
#define MAX_GENRE 50
#define MAX_LINE 150
typedef struct{
    double budget;
    int genre; /* degis */
    char* name;
    double score;
    int year;
}Movie;

typedef struct{
    char *genre_name;
    int genre_no;
}genre;

/* List of sorted data option functions */
void list_of_sorted_data(const Movie* movies,int size_of_movies, const genre *genres, int count_genre);
void sorted_budget(const Movie* movies, int size_of_movies,const genre* genres,int count_genre);
void sorted_genre(const Movie* movies,int size_of_movies,const genre* genres,int count_genre);
void sorted_name(const Movie* movies, int size_of_movies,const genre* genres,int count_genre);
void sorted_score(const Movie* movies, int size_of_movies,const genre* genres, int count_genre);
void sorted_year(const Movie* movies, int size_of_movies,const genre* genres, int count_genre);
/* ---------------------------*/
/* List of throught years option functions */
void list_of_throught_years(const Movie* movies,int size_of_movies);
/* List of genres function */
void print_genres(const genre* genres,int count_genre);
/* List movies throught scores functions */
void list_movies_throught_scores(const Movie* movies,int size_of_movies);
/* Single movie information functions */
void single_movie_informations(const Movie* movies,int size_of_movies,const genre* genres,int count_genre);

void genre_count(char *buffer, genre*gf);
void average_of_imdb(const Movie* movies, int size_of_movies);
void frequence_of_genres(const Movie* movies,int size_of_movies,const genre* genres,int count_genre);
genre* seperate_genres(char *text,int *count);
int find_line_count(char *infid);
void parse_line(char *buffer,Movie *pt, genre*gf,int size_genre);
Movie* set_movies(char *txt, genre *genres,int size_genre,int* fixed_size);
int main_screen(Movie* movies,int size_of_movies,genre* genres,int count_genre);
int main(){
    char text[]="Movies.txt";
    int i=0, count_genre=0, fixed_size, end_condition=0;
    genre *genres;
    Movie *movies;
    genres=seperate_genres(text,&count_genre); 
    movies=set_movies(text,&genres[0],count_genre,&fixed_size); /* Movies dynamical structer has exactly the same amount of element with its size */
    while(1){
        end_condition=main_screen(&movies[0],fixed_size,&genres[0],count_genre);
        if(end_condition==1)
            break;
    }
    free(genres);
    free(movies);
    return 0;
}
void print_genres(const genre* genres,int count_genre){
    int i=0;    
    for(i=0; i<count_genre; i++)
        printf("%s\n",genres[i].genre_name);
}


void list_movies_throught_scores(const Movie* movies,int size_of_movies){
    double score=0.0;
    int i=0, stop_condition=0, contol=0, option=0;;
   
    while(1){
        stop_condition=0;
        printf("Enter a score: ");
        scanf("%lf",&score);
        printf("Less (0) or Greater(1)  %.1f:",score);
        scanf("%d",&option);
        if(option==0){
            for(i=0; i<size_of_movies; i++){
                if(score>movies[i].score){
                    stop_condition=1;
                    printf("%s %.1f\n",movies[i].name,movies[i].score);
                }
            }
        }
        else if(option==1){
            for(i=0; i<size_of_movies; i++){
                if(score<movies[i].score){
                    stop_condition=1;
                    printf("%s\n",movies[i].name);
                }

            }
        }

        if(stop_condition==1)
            break;
        else
            printf("TRY AGAIN\n");
    }   

}
void single_movie_informations(const Movie* movies,int size_of_movies,const genre* genres,int count_genre){
    char *name;
    int i=0,j=0, end_control=0;;
    name=(char*)calloc(150,sizeof(char));
    
    while(1){
        printf("\nPlease enter the name of the movie: ");
        scanf(" %[^\n]%*c",name);
        for(i=0; i<size_of_movies; ++i){
            if(strcmp(movies[i].name,name)==0){
                end_control=1;
                break;
            }
        }
        if(end_control==1)
            break;
        else
            printf("Your input did not math with any Movie in the file Please try again!");
        fflush(stdin);
        }
        if(movies[i].budget==0)
            printf("\nBudget:\tUnknown ");
        else
            printf("\nBudget:\t%.0f ",movies[i].budget);
        for(j=0; j<count_genre; ++j)
            if(movies[i].genre==genres[j].genre_no)
                break;
        printf("\nGenre:\t%s",genres[j].genre_name);
        
        printf("\nName:\t%s",movies[i].name);
        printf("\nScore:\t%.1f",movies[i].score);
        printf("\nYear:\t%d",movies[i].year);
        printf("\n");
}
void average_of_imdb(const Movie* movies, int size_of_movies){
    int i=0;
    double average=0.0;
    for(i=0; i<size_of_movies; ++i){
        average+=movies[i].score;
    }
    average=average/size_of_movies;
    printf("Average: %.2f\n",average);
}
void frequence_of_genres(const Movie* movies,int size_of_movies,const genre* genres,int count_genre){
    int i=0, j=0, counter=0, total=0;
    printf("\n");
    for(i=0; i<count_genre; ++i){
        counter=0;
        for(j=0; j<size_of_movies; ++j){
            if(movies[j].genre==genres[i].genre_no)
                counter++;
        }
        total+=counter;
        printf("%-20s\t%20d",genres[i].genre_name,counter);
        printf("\n");
    }
}

void list_of_throught_years(const Movie* movies,int size_of_movies){
    int year, option=0,i=0, check=0, end_condition=0;
    while(1){
    end_condition=0;
    check=0;
    printf("Enter a year: ");
    scanf("%d",&year);
    printf("Until (0) or Since(1) %d:",year);
    scanf("%d",&option);
    
    check=0;
    switch(option){
        case 0:
            for(i=0; i<size_of_movies; i++){
                if(movies[i].year<=year){
                    check=1;
                    break;
                }
            }
        if(check==1){ 
            for(i=0;i<size_of_movies;i++)
                if(movies[i].year<=year)
                    printf("%s\n",movies[i].name);
            
            end_condition=1;
        }
        else{
            printf("TRY AGAIN\n");
            end_condition=0;
        }
        break;
        case 1:
            for(i=0; i<size_of_movies; i++){
                if(movies[i].year>=year){
                    check=1;
                    break;
                }
            }
        if(check==1){ 
            for(i=0;i<size_of_movies;i++)
                if(movies[i].year>=year)
                    printf("%s\n",movies[i].name);
            
            end_condition=1;
        }
        else{
            printf("TRY AGAIN\n");
            end_condition=0;
        }
        break;
        default:
            end_condition=0;
            printf("TRY AGAIN\n");
        break;

    }
        if(end_condition==1)
            break;
    }


}

void sorted_name(const Movie* movies, int size_of_movies,const genre* genres,int count_genre){
    int i=0, j=0, index=0, control=0, operation=0, start_value=0, end_value=0, end_condition=0;
    double ind, max;
    Movie *copy;
    Movie temp;
    temp.name=(char*)malloc(MAX_STRING*sizeof(char));
    copy=(Movie*)calloc(size_of_movies,sizeof(Movie));
    for(i=0; i<size_of_movies; ++i)
        copy[i].name=(char*)malloc(MAX_STRING*sizeof(char));

    for(i=0; i<size_of_movies; i++){
        strcpy(copy[i].name,movies[i].name);
        copy[i].budget=movies[i].budget;
        copy[i].genre=movies[i].genre;
        copy[i].score=movies[i].score;
        copy[i].year=movies[i].year;
    }
    /* Copied all the datas into copy structer */    
    for(i=0; i<size_of_movies; ++i){
        for(j=i+1; j<size_of_movies; ++j){
            if(strcmp(copy[j].name,copy[i].name)<0)
                {
                    temp.budget=copy[i].budget;
                    temp.genre=copy[i].genre;
                    temp.score=copy[i].score;
                    temp.year=copy[i].year;
                    strcpy(temp.name,copy[i].name);
                    copy[i].budget= copy[j].budget;
                    copy[i].genre= copy[j].genre;
                    copy[i].score= copy[j].score;
                    copy[i].year=copy[j].year;
                    strcpy(copy[i].name,copy[j].name);
                    copy[j].budget= temp.budget;
                    copy[j].genre= temp.genre;
                    copy[j].score= temp.score;
                    copy[j].year=temp.year;
                    strcpy(copy[j].name,temp.name);
        
            }
        }
    }
    
    while(1){
        printf("1-) Single selection: \n");
        printf("2-)Multiple selection: \n");
        printf("Please Select an Operation: ");
        scanf("%d",&operation);
        switch(operation){
            case 1:
                printf("Enter the value: ");
                scanf("%d",&start_value);
                printf("%d.Movie: \n",start_value);
                start_value=start_value-1;
                printf("%0.f",copy[start_value].budget);
                for(j=0; j<count_genre; ++j)
                        if(copy[start_value].genre==genres[j].genre_no)
                            break;
                printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[start_value].name,copy[start_value].score,copy[start_value].year);
                end_condition=1;
                break;
            case 2:
                printf("Enter start value: ");
                scanf("%d",&start_value);
                printf("Enter end value: ");
                scanf("%d",&end_value);
                start_value=start_value-1;
                end_value=end_value-1;

                for(i=start_value; i<=end_value; i++){
                    printf("%0.f",copy[i].budget);
                    for(j=0; j<count_genre; ++j)
                        if(copy[i].genre==genres[j].genre_no)
                            break;
                    printf("\t%-20s\t%-20s\t%.1f%20d\n",genres[j].genre_name,copy[i].name,copy[i].score,copy[i].year);
                }
                end_condition=1;
                break;
            
            default:
                printf("TRY AGAIN!");
                end_condition=0;
                break;
        }
        if(end_condition==1)
            break;
    }
    free(copy);
}

void sorted_year(const Movie* movies, int size_of_movies,const genre* genres, int count_genre){
 int i=0, j=0, index=0, control=0, operation=0, start_value=0, end_value=0, end_condition=0;
    double ind, max;
    Movie *copy;
    Movie temp;
    temp.name=(char*)malloc(MAX_STRING*sizeof(char));
    copy=(Movie*)calloc(size_of_movies,sizeof(Movie));
    for(i=0; i<size_of_movies; ++i)
        copy[i].name=(char*)malloc(MAX_STRING*sizeof(char));

    for(i=0; i<size_of_movies; i++){
        strcpy(copy[i].name,movies[i].name);
        copy[i].budget=movies[i].budget;
        copy[i].genre=movies[i].genre;
        copy[i].score=movies[i].score;
        copy[i].year=movies[i].year;
    }
    /* Copied all the datas into copy structer */    
    for(i=0; i<size_of_movies; ++i){
        for(j=i+1; j<size_of_movies; ++j){
            if(copy[j].year<copy[i].year)
                {
                    temp.budget=copy[i].budget;
                    temp.genre=copy[i].genre;
                    temp.score=copy[i].score;
                    temp.year=copy[i].year;
                    strcpy(temp.name,copy[i].name);
                    copy[i].budget= copy[j].budget;
                    copy[i].genre= copy[j].genre;
                    copy[i].score= copy[j].score;
                    copy[i].year=copy[j].year;
                    strcpy(copy[i].name,copy[j].name);
                    copy[j].budget= temp.budget;
                    copy[j].genre= temp.genre;
                    copy[j].score= temp.score;
                    copy[j].year=temp.year;
                    strcpy(copy[j].name,temp.name);
        
            }
        }
    }
    
    while(1){
        printf("1-) Single selection: \n");
        printf("2-)Multiple selection: \n");
        printf("Please Select an Operation: ");
        scanf("%d",&operation);
        switch(operation){
            case 1:
                printf("Enter the value: ");
                scanf("%d",&start_value);
                printf("%d.Movie: \n",start_value);
                start_value=start_value-1;
                printf("%0.f",copy[start_value].budget);
                for(j=0; j<count_genre; ++j)
                        if(copy[start_value].genre==genres[j].genre_no)
                            break;
                printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[start_value].name,copy[start_value].score,copy[start_value].year);
                end_condition=1;
                break;
            case 2:
                printf("Enter start value: ");
                scanf("%d",&start_value);
                printf("Enter end value: ");
                scanf("%d",&end_value);
                start_value=start_value-1;
                end_value=end_value-1;

                for(i=start_value; i<=end_value; i++){
                    printf("%0.f",copy[i].budget);
                    for(j=0; j<count_genre; ++j)
                        if(copy[i].genre==genres[j].genre_no)
                            break;
                    printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[i].name,copy[i].score,copy[i].year);
                }
                end_condition=1;
                break;
            
            default:
                printf("TRY AGAIN!");
                end_condition=0;
                break;
        }
        if(end_condition==1)
            break;
    }
    free(copy);
}

void sorted_score(const Movie* movies, int size_of_movies,const genre* genres, int count_genre){
    int i=0, j=0, index=0, control=0, operation=0, start_value=0, end_value=0, end_condition=0;
    double ind, max;
    Movie *copy;
    Movie temp;
    temp.name=(char*)malloc(MAX_STRING*sizeof(char));
    copy=(Movie*)calloc(size_of_movies,sizeof(Movie));
    for(i=0; i<size_of_movies; ++i)
        copy[i].name=(char*)malloc(MAX_STRING*sizeof(char));

    for(i=0; i<size_of_movies; i++){
        strcpy(copy[i].name,movies[i].name);
        copy[i].budget=movies[i].budget;
        copy[i].genre=movies[i].genre;
        copy[i].score=movies[i].score;
        copy[i].year=movies[i].year;
    }
    /* Copied all the datas into copy structer */    
 
    for(i=0; i<size_of_movies; ++i){
        for(j=i+1; j<size_of_movies; ++j){
            if(copy[j].score<copy[i].score)
                {
                    temp.budget=copy[i].budget;
                    temp.genre=copy[i].genre;
                    temp.score=copy[i].score;
                    temp.year=copy[i].year;
                    strcpy(temp.name,copy[i].name);
                    copy[i].budget= copy[j].budget;
                    copy[i].genre= copy[j].genre;
                    copy[i].score= copy[j].score;
                    copy[i].year=copy[j].year;
                    strcpy(copy[i].name,copy[j].name);
                    copy[j].budget= temp.budget;
                    copy[j].genre= temp.genre;
                    copy[j].score= temp.score;
                    copy[j].year=temp.year;
                    strcpy(copy[j].name,temp.name);
        
            }
        }
    }
    
    while(1){
        printf("1-) Single selection: \n");
        printf("2-)Multiple selection: \n");
        printf("Please Select an Operation: ");
        scanf("%d",&operation);
        switch(operation){
            case 1:
                printf("Enter the value: ");
                scanf("%d",&start_value);
                printf("%d.Movie: \n",start_value);
                start_value=start_value-1;
                printf("%0.f",copy[start_value].budget);
                for(j=0; j<count_genre; ++j)
                        if(copy[start_value].genre==genres[j].genre_no)
                            break;
                printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[start_value].name,copy[start_value].score,copy[start_value].year);
                end_condition=1;
                break;
            case 2:
                printf("Enter start value: ");
                scanf("%d",&start_value);
                printf("Enter end value: ");
                scanf("%d",&end_value);
                start_value=start_value-1;
                end_value=end_value-1;

                for(i=start_value; i<=end_value; i++){
                    printf("%0.f",copy[i].budget);
                    for(j=0; j<count_genre; ++j)
                        if(copy[i].genre==genres[j].genre_no)
                            break;
                    printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[i].name,copy[i].score,copy[i].year);
                }
                end_condition=1;
                break;
            
            default:
                printf("TRY AGAIN!");
                end_condition=0;
                break;
        }
        if(end_condition==1)
            break;
    }

    free(copy);
}



void sorted_genre(const Movie* movies,int size_of_movies,const genre* genres,int count_genre){
    int i=0, j=0, index=0, control=0, operation=0, start_value=0, end_value=0, end_condition=0;
    double ind, max;
    Movie *copy;
    Movie temp;
    temp.name=(char*)malloc(MAX_STRING*sizeof(char));
    copy=(Movie*)calloc(size_of_movies,sizeof(Movie));
    for(i=0; i<size_of_movies; ++i)
        copy[i].name=(char*)malloc(MAX_STRING*sizeof(char));

    for(i=0; i<size_of_movies; i++){
        strcpy(copy[i].name,movies[i].name);
        copy[i].budget=movies[i].budget;
        copy[i].genre=movies[i].genre;
        copy[i].score=movies[i].score;
        copy[i].year=movies[i].year;
    }
    /* Copied all the datas into copy structer */    
 
    for(i=0; i<size_of_movies; ++i){
        for(j=i+1; j<size_of_movies; ++j){
            if(copy[j].genre<copy[i].genre)
                {
                    temp.budget=copy[i].budget;
                    temp.genre=copy[i].genre;
                    temp.score=copy[i].score;
                    temp.year=copy[i].year;
                    strcpy(temp.name,copy[i].name);
                    copy[i].budget= copy[j].budget;
                    copy[i].genre= copy[j].genre;
                    copy[i].score= copy[j].score;
                    copy[i].year=copy[j].year;
                    strcpy(copy[i].name,copy[j].name);
                    copy[j].budget= temp.budget;
                    copy[j].genre= temp.genre;
                    copy[j].score= temp.score;
                    copy[j].year=temp.year;
                    strcpy(copy[j].name,temp.name);
        
            }
        }
    }
    
    while(1){
        printf("1-) Single selection: \n");
        printf("2-)Multiple selection: \n");
        printf("Please Select an Operation: ");
        scanf("%d",&operation);
        switch(operation){
            case 1:
                printf("Enter the value: ");
                scanf("%d",&start_value);
                printf("%d.Movie: \n",start_value);
                start_value=start_value-1;
                printf("%0.f",copy[start_value].budget);
                for(j=0; j<count_genre; ++j)
                        if(copy[start_value].genre==genres[j].genre_no)
                            break;
                printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[start_value].name,copy[start_value].score,copy[start_value].year);
                end_condition=1;
                break;
            case 2:
                printf("Enter start value: ");
                scanf("%d",&start_value);
                printf("Enter end value: ");
                scanf("%d",&end_value);
                start_value=start_value-1;
                end_value=end_value-1;
                for(i=start_value; i<=end_value; i++){
                    printf("%0.f",copy[i].budget);
                    for(j=0; j<count_genre; ++j)
                        if(copy[i].genre==genres[j].genre_no)
                            break;
                    printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[i].name,copy[i].score,copy[i].year);
                }
                end_condition=1;
                break;
            
            default:
                printf("TRY AGAIN!");
                end_condition=0;
                break;
        }
        if(end_condition==1)
            break;
    
    
    }
    free(copy);
}
/* This function does not work as expected */
void sorted_budget(const Movie* movies, int size_of_movies,const genre* genres,int count_genre){
    int i=0, j=0, index=0, control=0, operation=0, start_value=0, end_value=0, end_condition=0;
    double ind, max;
    Movie *copy;
    Movie temp;
    temp.name=(char*)malloc(MAX_STRING*sizeof(char));
    copy=(Movie*)calloc(size_of_movies,sizeof(Movie));
    for(i=0; i<size_of_movies; ++i)
        copy[i].name=(char*)malloc(MAX_STRING*sizeof(char));

    for(i=0; i<size_of_movies; i++){
        strcpy(copy[i].name,movies[i].name);
        copy[i].budget=movies[i].budget;
        copy[i].genre=movies[i].genre;
        copy[i].score=movies[i].score;
        copy[i].year=movies[i].year;
    }
    /* Copied all the datas into copy structer */    
 

for(i=0; i<size_of_movies; ++i){
    for(j=i+1; j<size_of_movies; ++j){
        if(copy[j].budget<copy[i].budget)
            {
                temp.budget=copy[i].budget;
                temp.genre=copy[i].genre;
                temp.score=copy[i].score;
                temp.year=copy[i].year;
                strcpy(temp.name,copy[i].name);
                copy[i].budget= copy[j].budget;
                copy[i].genre= copy[j].genre;
                copy[i].score= copy[j].score;
                copy[i].year=copy[j].year;
                strcpy(copy[i].name,copy[j].name);
                copy[j].budget= temp.budget;
                copy[j].genre= temp.genre;
                copy[j].score= temp.score;
                copy[j].year=temp.year;
                strcpy(copy[j].name,temp.name);
    
          }
    }
}
while(end_condition!=1){
    control=0;
    printf("1-) Single selection: \n");
    printf("2-)Multiple selection: \n");
    printf("Please Select an Operation: ");
    scanf("%d",&operation);
        if(operation==1){
            printf("Enter a value: ");
            scanf("%d",&start_value);
            start_value--;
            if(copy[i].budget!=0){
            printf("%d.Movie\n",start_value);
            printf("%0.f",copy[start_value].budget);
            for(j=0; j<count_genre; ++j)
                if(copy[start_value].genre==genres[j].genre_no)
                    break;
            printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[start_value].name,copy[start_value].score,copy[start_value].year);
            end_condition=1;
        }
        else{
            printf("The given value's budget is unknown please enter a valid value!\n");
            end_condition=0;
        }
    }
    else if(operation==2){
        printf("Enter a start value: ");
        scanf("%d",&start_value);
        printf("Enter an End value: ");
        scanf("%d",&end_value);
        start_value--;
        end_value--;
        /*
        if(copy[start_value].budget==0.000){
            for(i=start_value; i<size_of_movies; ++i)
                if(copy[start_value].budget>0)
                    break;
        }
         if(copy[end_value].budget==0.000){
            for(i=end_value; i>start_value; i--)
                if(copy[start_value].budget>0)
                    break;
        }
        */
        for(i=start_value; i<end_value; i++){
            if(copy[i].budget){
                printf("%0.f",copy[i].budget);
                for(j=0; j<count_genre; ++j)
                    if(copy[i].genre==genres[j].genre_no)
                        break;
                printf("\t%-20s\t%-20s\t%.1f\t%20d\n",genres[j].genre_name,copy[i].name,copy[i].score,copy[i].year);
            }

        } 
        end_condition=1;
    }
    else{
        printf("Try Again! ");
        end_condition=0;

    }
}
    
    
    
    printf("\n");
    free(copy);

}

 void list_of_sorted_data(const Movie* movies,int size_of_movies, const genre *genres, int count_genre){
     int operation=0, end_condition=0, i=0, j=0;
     printf("\n1. Budget");
     printf("\n2. Genre");
     printf("\n3. Name");
     printf("\n4. Score");
     printf("\n5. Year\n");
    printf("Please Select an operation: ");
    scanf("%d",&operation);
    printf("\n");
    while(end_condition!=1){
        end_condition=0;
        switch(operation){
            case 1:
                sorted_budget(&movies[0],size_of_movies,&genres[0],count_genre);
                end_condition=1;
                break;
            case 2:
                sorted_genre(&movies[0],size_of_movies,&genres[0],count_genre);
                end_condition=1;
                break;
            
            case 3:
                sorted_name(&movies[0],size_of_movies,&genres[0],count_genre);
                end_condition=1;
                break;
            case 4:
                sorted_score(&movies[0],size_of_movies,&genres[0],count_genre);
                end_condition=1;
                break;
            case 5:
                sorted_year(&movies[0],size_of_movies,&genres[0],count_genre);
                end_condition=1;
                break;
            default:
                printf("Please Select a valid operation !\n");
                end_condition=0;
                break;
        }

    }

 }



int main_screen(Movie* movies,int size_of_movies,genre* genres,int count_genre){
    int operation=0, end_condition=0;
    printf("1-)List of the Sorted Data\n");
    printf("2-)List of the Genres\n");
    printf("3-)List of the Movie Through the Years\n");
    printf("4-)List of the Movie Through the Scores\n");
    printf("5-)All Informations of a Single Movie\n");
    printf("6-)Average of IMDB Scores\n");
    printf("7-)Frequence of the Genres\n");
    printf("8-)Exit\n");
    printf("Please select an operation: ");

    scanf("%d",&operation);

    switch(operation){
        case 1:
            list_of_sorted_data(&movies[0],size_of_movies,&genres[0],count_genre);
            end_condition=0;
            break;
        case 2:
            print_genres(&genres[0],count_genre);
            printf("\n");
            end_condition=0;
            break;
        case 3:
            list_of_throught_years(&movies[0],size_of_movies);
            end_condition=0;
            break;
        case 4:
            list_movies_throught_scores(&movies[0],size_of_movies);
            end_condition=0;
            break;
        case 5:
            single_movie_informations(&movies[0],size_of_movies,&genres[0],count_genre);
            end_condition=0;
            break;
        case 6:
            average_of_imdb(&movies[0],size_of_movies);
            end_condition=0;
            break;
        case 7:
            frequence_of_genres(&movies[0],size_of_movies,&genres[0],count_genre);
            end_condition=0;
            break;
        case 8:
            printf("The programme is terminated succesfully...\n");
            end_condition=1;
            break;
        default:
            printf("TRY AGAIN.");
            break;
    }
    return end_condition;
}


void parse_line(char *buffer,Movie *pt, genre*gf,int size_genre){
    int index=0, i=0;
    char *token;
    token=strtok(buffer,",");
    while(token!=NULL){
        
        if(index==0)
            pt->budget=atof(token);    
        
        if(index==1){
            for(i=0; i<size_genre; ++i)
                if(strcmp(gf[i].genre_name,token)==0)
                    break;                
            pt->genre=gf[i].genre_no;

        }
        
        else if(index==2){
            strcpy(pt->name,token);
        }
        else if(index==3)
            pt->score=atof(token);
        
        else if(index==4)
            pt->year=atoi(token);
        
        index++;
        token=strtok(NULL,",");
    }   
}

Movie* set_movies(char *txt, genre *genres,int size_genre,int* fixed_size){
    FILE *fp;
    Movie *pt,*pt2,*ap;
    int size=0, i=0, j=0, flag=0, k=0, new_size=0;
    char *status, *buffer;
    fp=fopen(("%s",txt),"r");
    if(fp==NULL)
        printf("The file could not open...");
    size=find_line_count(txt);
    buffer=(char*)calloc(MAX_LINE,sizeof(char));
    pt=(Movie*)calloc(size,sizeof(Movie));
    for(i=0; i<size; ++i)
        pt[i].name=(char*)malloc(MAX_STRING*sizeof(char));

    fgets(buffer,MAX_LINE,fp);
    for(i=0, pt2=&pt[0]; i<size; i++,pt2++){
        status=fgets(buffer,MAX_LINE,fp);
        parse_line(buffer,pt2,&genres[0],size_genre);
        if(status==0)
            break;
    } 
   
  

for(i=0; i<size; i++){
    flag=0;
    for(j=size-1,ap=&pt[size-1]; j>=0; j--,ap--){
        if(strcmp(pt[i].name,ap->name)==0 && j>i){
            flag=1;
            break;
        }
    }
    if(flag==1){
        strcpy(pt[i].name,ap->name);
        pt[i].budget=ap->budget;
        pt[i].genre=ap->genre;
        pt[i].year=ap->year;
        pt[i].score=ap->score;
        for(k=i+1;k<=j; k++)
            if(strcmp(pt[k].name,pt[i].name)==0)
                strcpy(pt[k].name,"\0");
    }

}
    
    for(i=0;i<size; i++)
        if(strcmp(pt[i].name,"\0")!=0){
            new_size++;
        }
    pt2=NULL;
    pt2=(Movie*)calloc(new_size,sizeof(Movie));
    
    for(i=0; i<new_size; i++)
        pt2[i].name=(char*)malloc(MAX_STRING*sizeof(char));
    

    for(i=0, k=0; i<size; i++){
        if(strcmp(pt[i].name,"\0")!=0){

            strcpy(pt2[k].name,pt[i].name);
            pt2[k].budget=pt[i].budget;
            pt2[k].genre=pt[i].genre;
            pt2[k].year=pt[i].year;
            pt2[k].score=pt[i].score;
            k++;
        }
    }

    free(pt);
    free(buffer);
    *fixed_size=new_size;
    return &pt2[0];
}

void genre_count(char *buffer, genre*gf){
    int index=0, j=0, counter=1;
    char *token;
    token=strtok(buffer,",");
    
    while(token!=NULL){
    
        if(index==1){
            gf->genre_name=(char*)malloc(strlen(token)*sizeof(char));
            strcpy(gf->genre_name,token);
            gf->genre_no=0;
        }
        index++;
        token=strtok(NULL,",");
    }   
}


/* This function find genre count and holds the name of genres in a dynamical structer */
genre* seperate_genres(char* text, int *count){
    int size=0, i=0,counter=0, j=0, flag=0, k=0;
    char *buffer,*status;
    FILE *fp;
    genre *g, *gf,*genres, *pt;
    fp=fopen(("%s",text),"r");
    if (fp == NULL) 
            {   
              printf("%s.txt is not opened succesfully \n",text); 
            } 
    

    size=find_line_count(text);
    g=(genre*)calloc(size,sizeof(genre));
    buffer=(char*)calloc(MAX_STRING,sizeof(char));
    fgets(buffer,MAX_STRING,fp);/* get header */   
    for(i=0, gf=&g[0]; i<size; i++,gf++){
        status=fgets(buffer,MAX_STRING,fp);
          genre_count(buffer,gf);
        if(status==0)
            break;
    } 
    gf=(genre*)calloc(MAX_GENRE,sizeof(genre));
    for(i=0; i<MAX_GENRE; i++)
        gf[i].genre_name=(char*)calloc(MAX_STRING,sizeof(char));
    
    counter=0;
    flag=0;
    i=0;
    for(k=0; k<size-1; ++k){
        if(strcmp(g[i].genre_name,"\0")==0)
            i++;
        else{
            for(j=i+1; j<size-1; ++j){
                if(strcmp(g[j].genre_name,g[i].genre_name)==0)
                    strcpy(g[j].genre_name,"\0");
            }
            i++;
        }
    }
    
    counter=0;
    for(i=0; i<size-1; i++){
        if(strcmp(g[i].genre_name,"\0")!=0){
            strcpy(gf[counter].genre_name,g[i].genre_name);
            counter++;
        }
    }
    
 

    for(i=0; i<counter; ++i){
        flag=0;
        for(j=0; j<size;++j){
            if(strcmp(gf[i].genre_name,g[j].genre_name)==0){
                flag=1;
                break;
            }
        }
        if(flag==1)
            gf[i].genre_no=i+1;
        else
            gf[i].genre_no=-1;
    }
    
    
    for(j=0; j<counter; j++){
        for(i=0;i<strlen(gf[j].genre_name);++i){
            if(gf[j].genre_name[i]=='\n'){
                gf[j].genre_no=0;
                strcpy(gf[j].genre_name,"\0");
            }
        }   
    }
    genres=(genre*)calloc(counter,sizeof(genre));
    for(i=0; i<counter; ++i)
        genres[i].genre_name=(char*)calloc(MAX_STRING,sizeof(char));

    for(i=0; i<counter; i++){
        strcpy(genres[i].genre_name,gf[i].genre_name);
        genres[i].genre_no=gf[i].genre_no;
    }
    *count=counter;

free(gf);
free(g);
free(buffer);
fclose(fp);

return genres;
}

int find_line_count(char *infid){
   
    FILE *fp;
    char ch;
    int count=0, i=0;
    fp=fopen(("%s",infid),"r");
    if(fp==NULL)
        printf("The file could not open");
    for(ch=getc(fp); ch!=EOF; ch=getc(fp)){
        if(ch=='\n')
            count++;
    }
    fclose(fp);
    return count;
}
