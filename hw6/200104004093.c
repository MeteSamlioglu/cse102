#include<stdio.h>
#include<stdlib.h>
/*#include<time.h>*//* to randomize game board everytime by using srand(time(NULL)) in create_random_puzzle function */
#define N 8        /* NxN matrix constant */

typedef enum{EMPTY}SetGame;
typedef enum{RIGHT, LEFT, UP, DOWN}game_direction;
void create_random_puzzle(SetGame (*game_array)[N]);
void print_puzzle(SetGame (*game_array)[N]);
void print_horizantonal_line();
int make_move(int direction, int row, int column, SetGame(*game_array)[N]);
void set_move(game_direction direction, int row,int column, SetGame(*game_array)[N]);
int check_game_end(SetGame(*game_array)[N]);
int check_unsolvable(SetGame(*game_array)[N]);

int main(){
    SetGame game[N][N];
    int row, column, direction, check_win=0, start_control=0;
    printf("THE GAME HAS STARTED...\nPlease enter the number that related with your movement\n");
    create_random_puzzle(game); 
    print_puzzle(game);
    if(check_game_end(game)==1){  /* Check start with solved puzzle condition */
        printf("What a coincidence, the Puzzle is randomized solved !.Please restart the game...\n");
        start_control=1;
    }
    if(check_unsolvable(game)==0){ /* Unsolvable puzzle condition */
        printf("This puzzle is unsolvable..\n");
        start_control=1;
    }
    while(start_control!=1){ /* If puzzle is randomized solved do not get input from user ignore this block finish the programme */
        printf("Enter the  movement start location[row column]: ");
        scanf("%d%d",&row,&column);
        printf("The direction of the movement[1-)RIGHT 2-)LEFT 3-)UP 4-)DOWN  5-)Give up]: ");
        scanf("%d",&direction);
        if(direction==5){
            printf("The game is terminated...\n");
            printf("Better luck next time !\n");
            break;
            }
        check_win=make_move(direction, row, column,game);
        if(check_win==1){ /* Check win condition according to return value of int make_move function */ 
            printf("CONGRATULATIONS YOU WIN !...");     
            break;
        }
    }
    
    return 0;    
}

void create_random_puzzle(SetGame(*game_array)[N]){ /* This function creates a number game puzzle matrix */
    char empty[]="\0";
    int i=0, j=0,counter=0,  element=0, random_index=0;
    int size=N*N; 
    SetGame set_array[N*N];   /* In first, define a 1D array to keep our generated numbers 1 to (N*N-1) */
    for(i=0; i<size; i++){   /* Generate all the numbers 1 to (N*N-1) and keep them in 1D array*/
        set_array[i]=i+1;
    }
    set_array[size-1]=EMPTY; /* Assign blank space as an element of our game matrix */
    /* srand(time(NULL)); */ /* To get a diffrent set every in every compile */
    for (i = 0; i < size; i++) {    /* I used this block to randomize all the generated numbers 1 to (N*N-1) without repetition of numbers*/
        element = set_array[i];        
        random_index = rand() %size;  /* Generate random index value by using rand() function*/          
        set_array[i]=set_array[random_index];     
        set_array[random_index] = element;   
    }                                /* We sorted 1D array(set_array) elements randomly */

    for(i=0; i<N; i++){            /* Assigning these 1 to (N*N-1) randomize numbers into our game matrix properly */
        for(j=0;j<N;j++){         
        game_array[i][j]=set_array[counter]; 
            counter++;
        }
    }
   printf("\n");
     /* At the end of this process, 2D number puzzle matrix which includes 1 to N*N-1 randomized sorted numbers is created */
}


void print_horizantonal_line(){       /* This function prints horizantonal lines for print_puzzle function*/
    int horizantonal_line, i=0;            
    horizantonal_line=N*16;
    for(i=0;i<horizantonal_line;i++)
        printf("*");
        
}

void print_puzzle(SetGame(*game_array)[N]){
    int i=0, j=0;
    char empty[]="\0"; /* Represent blank space with NULL string */
    for(i=0;i<N;i++){
    printf("*");                     
    print_horizantonal_line(); 
    printf("\n");
        for(j=0;j<N;j++){     /* Printing the number puzzle matrix properly */
            if(j==0){
                if(game_array[i][j]==EMPTY)
                    printf("*%8s%8s",empty,"*");
                else
                    printf("*%8d%8s",game_array[i][j],"*");
            }
            else{
                if(game_array[i][j]==EMPTY)
                    printf("%8s%8s",empty,"*");
                else
                    printf("%8d%8s",game_array[i][j],"*");
            }
        }

    printf("\n");
    }
    print_horizantonal_line();
    printf("*\n");

}


int check_game_end(SetGame(*game_array)[N]){
    int i=0, j=0, counter=1, check_win=1; 
    char empty[]="\0";
    SetGame win_condition[N][N];

    for(i=0;i<N;i++){            /* Create a solved matrix to compare with our number puzzle matrix */
        for(j=0;j<N;j++){
            if(j==(N-1) && i==(N-1)) 
                win_condition[i][j]=EMPTY;
            else{
            win_condition[i][j]=counter;
            counter++;
            }
        }
    }
    

    for(i=0;i<N;i++){           /* Compare matrices, if they are not exactly the same the game has to continue */
        for(j=0;j<N;j++){                   
            if(win_condition[i][j]!=game_array[i][j]){
                check_win=0;  
                break;
            }
        }
    }

    return check_win;  /* Return the check_win to check win condition in other functions */
}


int make_move(int direct, int row, int column, SetGame(*game_array)[N]){
    game_direction direction;
    int stop_condition;
    if(row>=N || row<0 || column>=N || column<0){   /* Input position validity check */
        stop_condition=0;
        printf("ERROR: Given row and the column must not be bigger than %d or less than 0\n",N);
    }            /* Make your movement according to given direction */
    else{       /* In every case statement, modify the game board and check win condition and print the puzzle,by calling related functions*/
        switch(direct){         
        case 1:                
            direction=RIGHT;      
            set_move(RIGHT,row,column,game_array);
            stop_condition=check_game_end(game_array);
            print_puzzle(game_array);
            break;
        case 2:
            direction=LEFT;
            set_move(LEFT,row,column,game_array);
            stop_condition=check_game_end(game_array);
            print_puzzle(game_array);
            break;
        case 3:
            direction=UP;
            set_move(UP,row,column,game_array);
            stop_condition=check_game_end(game_array);
            print_puzzle(game_array);
            break;
        case 4: 
            direction=DOWN;
            set_move(DOWN,row,column,game_array);
            stop_condition=check_game_end(game_array);
            print_puzzle(game_array);
            break;
    
        default:      /* If given direction is not valid print error message */
            printf("The direction you choosed is not valid. Please Enter a valid direction!\n");
            stop_condition=0;
            break;
        }

    }
    return stop_condition; /* Return the stop_condition value to the main */
}                          /* Main function's while loop continue or break according to the this return value */



void set_move(game_direction direction, int row,int column, SetGame(*game_array)[N]){
    int i=0, j=0, valid_move=0, empty_index; 
    SetGame copyArray[N][N];   /*Define a copy array to make slide movements more effectively */

    for(i=0;i<N;i++)          /* Equalize matrices each other*/
        for(j=0;j<N;j++)
            copyArray[i][j]=game_array[i][j]; 

    switch(direction){                
        case RIGHT:                               /* RIGHT DIRECTION */
            for(i=column+1;i<=N-1;i++)           /* In first, check given movement is valid or not  */
                if(game_array[row][i]==EMPTY){
                    empty_index=i;              /*If the given movement is valid, then take the index of blank space */
                    valid_move=1;               
                }   
            if(valid_move==1){
                game_array[row][column]=copyArray[row][empty_index];/* Change the input's position with blank space's position */
                for(i=column;i<empty_index;i++)
                    game_array[row][i+1]=copyArray[row][i];     /*Slide right every element of given row till reach blank space's initial index */      
            }                                                   
        
        break;
        case LEFT:                           /* LEFT DIRECTION */
            for(i=column-1;i>=0;i--)            /* Check validity of movement by decrementing given index in given row */
                if(game_array[row][i]==EMPTY){  
                    empty_index=i;             /* If the given movement is valid, then take the index of blank space */
                    valid_move=1;
                }
            if(valid_move==1){
                game_array[row][column]=copyArray[row][empty_index];   /* Change the input's position with blank space's position */
                for(i=column;i>empty_index;i--)
                    game_array[row][i-1]=copyArray[row][i];   /* Slide left every element of given row till reach the blank space's initial index*/
            }
        break;
        case UP:
            for(i=row-1;i>=0;i--)              /* UP DIRECTION */
                if(game_array[i][column]==EMPTY){               /* Up movement algorithm is the same with Left movement algorithm*/
                    empty_index=i;                              
                    valid_move=1;             /*The only diffrences are sliding way and constant indexes */                           
                }
            if(valid_move==1){
                game_array[row][column]=copyArray[empty_index][column];
                    for(i=row; i>empty_index; i--)
                        game_array[i-1][column]=copyArray[i][column];
            }
        break;
        case DOWN:                           /* DOWN DIRECTION */
            for(i=row+1; i<=N-1; i++)                     /* Up movement algorithm is the same with Left movement algorithm*/
                if(game_array[i][column]==EMPTY){       
                    empty_index=i;              /*The only diffrences are sliding way and constant indexes */ 
                    valid_move=1;
                }
            if(valid_move==1){
                game_array[row][column]=copyArray[empty_index][column];
                for(i=row; i<empty_index; i++)
                    game_array[i+1][column]=copyArray[i][column];
            }   
        break;

        default:
        break;
    }
}

int check_unsolvable(SetGame(*game_array)[N]){
    int i=0, inversion_count=0, j=0, empty_position, k=0; 

    int array[N*N]; 
    for(i=0;i<N;i++) /* Copy 2D array's elements into 1D (N*N) array */ 
        for(j=0;j<N;j++){
            array[k]=game_array[i][j];
            k++;
        }

    for (i = 0;i < N * N - 1;i++)     /* Finding the inversion count */
            for (j =i+1; j<N*N; j++)
                if (array[j] && array[i] && array[i] > array[j])
                    inversion_count++;
            
        

    if(N%2!=0) /* If N is odd and inversion count is even it means that puzzle solveable  */
        if(inversion_count%2==0)
            return 1;
        else
            return 0; 
    else if(N%2==0){      /* If N is even there are two possibility */
        for (i =N-1; i>=0; i--)     /* From bottom to top we need to find blank space's position */
            for (j =N - 1; j >=0; j--)
                if (game_array[i][j] == EMPTY)
                    empty_position=N-i;
        
        if(empty_position%2!=0) /* If row count of blank space from the bottom is an odd and inversion count is even it means that puzzle is solveable*/
            if(inversion_count%2==0)
                return 1;
            else
                return 0;
        else if(empty_position%2==0)/*If row count of blank space from the bottom is even and inversion count is odd it means that puzzle is solveable*/
        if(inversion_count%2!=0)
                return 1;
            else
                return 0;
    }


}