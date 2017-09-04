#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define SIZEMOVES 1000

void drawBoard(char board[10][10]);
void pieces(char [10][10]);
void printBoard(char board[10][10]);
void analyzingMoving(char playerturn[] , char board[10][10],int counter[]);
void makingMoving(char board[10][10],int b1,int b2,int b3,int b4);
void takingNames(char player1[],char player2[]);
int Knight(char board[10][10] ,int b1,int b2 ,int b3, int b4);
int rook (char board[10][10], int b1,int b2,int b3,int b4);
int bishop (char board[10][10], int b1,int b2,int b3,int b4);
int pawn (char board[10][10], int b1,int b2,int b3,int b4);
void pawnPromotion(char board[10][10], int b1,int b2,int b3,int b4);
int queen(char board[10][10],int b1,int b2,int b3,int b4);
int king(char board[10][10],int b1, int b2,int b3, int b4);
int king(char board[10][10],int b1, int b2,int b3, int b4);
int checkingForUndo(char playerturn[4]);
int checkingForRedo(char playerturn[4]);
int undo(char board[10][10],int correctMoves[][4],int losesPosition[30][2],int stopAt);
int redo(char board[10][10],int correctMoves[][4],int losesPosition[30][2],int stopAt);
void playerloses(char player1loses[],char player2loses[],char board[10][10],int b3, int b4);
int checkingForSave(char playerturn[4]);
void save(int correctMoves[][4]);
void LP(int losesPosition[30][2],char board[10][10],int b3, int b4);
int checkingForLoad(char playerturn[4]);
int load(char board[10][10]);
int check1(char board[10][10]);
int check2(char board[10][10]);
int removeCheck1(char board[10][10]);
int removeCheck2(char board[10][10]);
int checkmate1(char board[10][10]);
int checkmate2(char board[10][10]);
int stalemate1(char board[10][10]);
int stalemate2(char board[10][10]);

char player1loses[15];



char player2loses[15];
int losesPosition[30][2];
char player1[SIZE],player2[SIZE];

int SavingMode=0;

char piecesPromotiom[16][2];

int main()
{
    takingNames(player1,player2);

    char board[10][10];
    int correctMoves[SIZEMOVES][4]= {{0}};

    int stopAt=0;
    int stopAt2=0;

    drawBoard(board);
    pieces(board);
    printBoard(board);

    char playerturn1[SIZE],playerturn2[SIZE];
    char a1,a2,a3,a4;
    int b1,b2,b3,b4;
    int generalFlag=1,flag,endGame=1;
    int counter[4]= {0};
    while(generalFlag&&endGame)
    {
        flag=1;

        while(flag&&endGame)
        {
            system("cls");
            printBoard(board);
            int checkmate;
            checkmate=checkmate1(board);
            if (checkmate==-1)
                goto DC1;
            else if(checkmate==0)
            {
                printf("Warning .. there's a check !!");
                goto DC1;
            }
            else
            {
                endGame=0;
                break;
            }

DC1:
            if (stalemate1(board)==0);
            else
            {
                printf("STALEMATE.. ");
                endGame=0;
                break;
            }
            system("cls");
            printBoard(board);
            printf("%s Turn:",player1);
            scanf("%s", playerturn1);
            {
                int checkingforUndo=0,checkingforRedo=0;
                checkingforUndo=checkingForUndo(playerturn1);
                checkingforRedo=checkingForRedo(playerturn1);
                if (checkingforUndo==1)
                {
                    int certain;
                    certain=undo(board,correctMoves,losesPosition,stopAt);
                    if (certain==1)
                    {
                        stopAt--;
                        flag=0;
                    }
                    else
                        continue;
                }
                else if (checkingforRedo==1)
                {
                    int certain;
                    certain=redo(board,correctMoves,losesPosition,stopAt);
                    if (certain==1)
                    {
                        stopAt++;
                        flag=0;
                    }
                    else
                        continue;
                }
            }
            int checkingforSave;
            if ((checkingforSave=checkingForSave(playerturn1))==1)

            {
                save(correctMoves);
                printf("Saving done !");
            }

            int checkingforLoad;
            int change;
            if ((checkingforLoad=checkingForLoad(playerturn1))==1)

            {
                SavingMode=1;
                change=load(board);
                printf("loading done !");
                printBoard(board);
                if (change%2==0)
                    continue;
                else
                    flag=0;
            }





            a1=playerturn1[0],a2=playerturn1[1],a3=playerturn1[2],a4=playerturn1[3];
            if (((65<=a1&&a1<=72)||(97<=a1&&a1<=104))&&
                    (49<=a2&&a2<=56)&&
                    ((65<=a3&&a3<=72)||(97<=a3&&a3<=104))&&
                    (49<=a4&&a4<=56))
            {
                analyzingMoving(playerturn1,board,counter);
                b1=counter[1],b2=counter[0],b3=counter[3],b4=counter[2];
                if ((board[b1][b2]=='p'||board[b1][b2]=='r'||
                        board[b1][b2]=='n'||board[b1][b2]=='b'||
                        board[b1][b2]=='q'||board[b1][b2]=='k')&&
                        (board[b3][b4]!='p'&&board[b3][b4]!='r'&&
                         board[b3][b4]!='n'&&board[b3][b4]!='b'&&
                         board[b3][b4]!='q'&&board[b3][b4]!='k'))
                {
                    int checking;
                    if(board[b1][b2]=='n')
                    {
                        checking=Knight(board,b1,b2,b3,b4);
                        if(checking==1)
                            goto D1;
                        else
                            continue;
                    }
                    else if(board[b1][b2]=='r')
                    {
                        checking=rook(board,b1,b2,b3,b4);
                        if(checking==1)
                            goto D1;
                        else
                            continue;
                    }
                    else if(board[b1][b2]=='b')
                    {
                        checking=bishop(board,b1,b2,b3,b4);
                        if(checking==1)
                            goto D1;
                        else
                            continue;
                    }
                    else if(board[b1][b2]=='p')
                    {
                        checking=pawn(board,b1,b2,b3,b4);
                        if(checking==1)
                            goto D1;
                        else
                            continue;
                    }
                    else if(board[b1][b2]=='q')
                    {
                        checking=queen(board,b1,b2,b3,b4);
                        if(checking==1)
                            goto D1;
                        else
                            continue;
                    }
                    else if(board[b1][b2]=='k')
                    {
                        checking=king(board,b1,b2,b3,b4);
                        if(checking==1)
                            goto D1;
                        else
                            continue;
                    }

                    {
D1:
                        playerloses(player1loses,player2loses,board,b3,b4);
                        LP(losesPosition,board,b3,b4);
                        makingMoving(board,b1,b2,b3,b4);
                        if (checkmate==0)
                            if (check1(board)!=0)
                            {
                                makingMoving(board,b3,b4,b1,b2);
                                goto DC1;
                            }
                        correctMoves[stopAt][0]=b1;
                        correctMoves[stopAt][1]=b2;
                        correctMoves[stopAt][2]=b3;
                        correctMoves[stopAt][3]=b4;
                        stopAt++;
                        stopAt2++;
                        if (stopAt2!=stopAt)
                        {
                            for (stopAt2=stopAt2; stopAt2>=stopAt; stopAt2--)
                            {
                                correctMoves[stopAt2][0]=0;
                                correctMoves[stopAt2][1]=0;
                                correctMoves[stopAt2][2]=0;
                                correctMoves[stopAt2][3]=0;
                            }
                        }
                        system("cls");
                        printBoard(board);
                        if(board[b3][b4]=='p')
                        {
                            pawnPromotion(board,b1,b2,b3,b4);
                            system("cls");
                            printBoard(board);
                        }
                        flag=0;
                    }
                }
            }
        }


        flag=1;
        while (flag&&endGame)
        {
            system("cls");
            printBoard(board);
            int checkmate;
            checkmate=checkmate2(board);
            if (checkmate==-1)
                goto DC2;
            else if(checkmate==0)
            {
                printf("Warning .. there's a check !!");
                goto DC2;
            }
            else
            {
                endGame=0;
                break;
            }

DC2:
            if (stalemate2(board)==0);
            else
            {
                printf("STALEMATE.. ");
                endGame=0;
                break;
            }
            system("cls");
            printBoard(board);
            printf("%s Turn:",player2);
            scanf("%s", playerturn2);
            {
                int checkingforUndo=0,checkingforRedo=0;
                checkingforUndo=checkingForUndo(playerturn2);
                checkingforRedo=checkingForRedo(playerturn2);
                if (checkingforUndo==1)
                {
                    int certain;
                    certain=undo(board,correctMoves,losesPosition,stopAt);
                    if (certain==1)
                    {
                        stopAt--;
                        flag=0;
                    }
                    else
                        continue;
                }
                else if (checkingforRedo==1)
                {
                    int certain;
                    certain=redo(board,correctMoves,losesPosition,stopAt);
                    if (certain==1)
                    {
                        stopAt++;
                        flag=0;
                    }
                    else
                        continue;
                }
            }

            int checkingforSave;
            if ((checkingforSave=checkingForSave(playerturn2))==1)
            {
                save(correctMoves);
                printf("loading done !");
            }

            int checkingforLoad;
            int change;
            if ((checkingforLoad=checkingForLoad(playerturn2))==1)
            {
                SavingMode=1;
                change=load(board);
                printf("loading done !");
                printBoard(board);
                if (change%2==0)
                    flag=0;
                else
                    continue;
            }

            printf("%s",playerturn1);
            a1=playerturn2[0],a2=playerturn2[1],a3=playerturn2[2],a4=playerturn2[3];
            if (((65<=a1&&a1<=72)||(97<=a1&&a1<=104))&&
                    (49<=a2&&a2<=56)&&
                    ((65<=a3&&a3<=72)||(97<=a3&&a3<=104))&&
                    (49<=a4&&a4<=56))
            {
                analyzingMoving(playerturn2,board,counter);
                b1=counter[1],b2=counter[0],b3=counter[3],b4=counter[2];
                if ((board[b1][b2]=='P'||board[b1][b2]=='R'||
                        board[b1][b2]=='N'||board[b1][b2]=='B'||
                        board[b1][b2]=='Q'||board[b1][b2]=='K')&&
                        (board[b3][b4]!='P'&&board[b3][b4]!='R'&&
                         board[b3][b4]!='N'&&board[b3][b4]!='B'&&
                         board[b3][b4]!='Q'&&board[b3][b4]!='K'))
                {
                    {
                        int checking;
                        if(board[b1][b2]=='N')
                        {
                            checking=Knight(board,b1,b2,b3,b4);
                            if(checking==1)
                                goto D2;
                            else
                                continue;
                        }
                        else if(board[b1][b2]=='R')
                        {
                            checking=rook(board,b1,b2,b3,b4);
                            if(checking==1)
                                goto D2;
                            else
                                continue;
                        }
                        else if(board[b1][b2]=='B')
                        {
                            checking=bishop(board,b1,b2,b3,b4);
                            if(checking==1)
                                goto D2;
                            else
                                continue;
                        }
                        else if(board[b1][b2]=='P')
                        {
                            checking=pawn(board,b1,b2,b3,b4);
                            if(checking==1)
                                goto D2;
                            else
                                continue;
                        }
                        else if(board[b1][b2]=='Q')
                        {
                            checking=queen(board,b1,b2,b3,b4);
                            if(checking==1)
                                goto D2;
                            else
                                continue;
                        }
                        else if(board[b1][b2]=='K')
                        {
                            checking=king(board,b1,b2,b3,b4);
                            if(checking==1)
                                goto D2;
                            else
                                continue;
                        }

                        {
D2:
                            playerloses(player1loses,player2loses,board,b3,b4);
                            LP(losesPosition,board,b3,b4);
                            makingMoving(board,b1,b2,b3,b4);
                            if (checkmate==0)
                                if (check2(board)!=0)
                                {
                                    makingMoving(board,b3,b4,b1,b2);
                                    goto DC2;
                                }
                            correctMoves[stopAt][0]=b1;
                            correctMoves[stopAt][1]=b2;
                            correctMoves[stopAt][2]=b3;
                            correctMoves[stopAt][3]=b4;
                            stopAt++;
                            stopAt2++;
                            if (stopAt2!=stopAt)
                            {
                                for (stopAt2=stopAt2; stopAt2>=stopAt; stopAt2--)
                                {
                                    correctMoves[stopAt2][0]=0;
                                    correctMoves[stopAt2][1]=0;
                                    correctMoves[stopAt2][2]=0;
                                    correctMoves[stopAt2][3]=0;
                                }
                            }
                            system("cls");
                            printBoard(board);
                            if(board[b3][b4]=='P')
                            {
                                pawnPromotion(board,b1,b2,b3,b4);
                                system("cls");
                                printBoard(board);

                            }
                            flag=0;
                        }
                    }
                }
            }
        }
    }


    return 0;
}

//taking names of players
void takingNames(char player1[],char player2[])
{
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t\tEnter Name for player 1:");
    gets(player1);
    system("cls");
    printf("\n\n\n\n\n\n\n\t\t\tEnter Name for player 2:");
    gets(player2);
    system("cls");
}

//function for drawing boards and guides..
void drawBoard(char board[10][10])
{
    int i=1,j=1;
    char c1='A',c2='8';

    while(j<9)
    {
        board[0][j]=board[9][j]=c1;
        board[i][0]=board[i][9]=c2;
        board[0][0]=board[0][9]=board[9][0]=board[9][9]=' ';
        i++,j++,c1++,c2--;
    }

    for (i=1; i<9; i++)
    {
        for (j=1; j<9; j++)
        {
            if ((i+j)%2==0)

                board[i][j]='-';
            else
                board[i][j]='.';
        }
    }
}

//putting pieces of beginning the game

void pieces(char board[10][10])
{
    int j;
    for (j=1; j<9; j++)
    {
        board[2][j]='P';
        board[7][j]='p';
    }
    board[1][1]=board[1][8]='R';
    board[8][1]=board[8][8]='r';
    board[1][2]=board[1][7]='N';
    board[8][2]=board[8][7]='n';
    board[1][3]=board[1][6]='B';
    board[8][3]=board[8][6]='b';
    board[1][4]='Q';
    board[8][4]='q';
    board[1][5]='K';
    board[8][5]='k';
}


void printBoard(char board[10][10])
{
    int i,j;
    for (i=0; i<10; i++)
    {
        for (j=0; j<10; j++)
        {
            printf(" %c ",board[i][j]);
            if (j==0 || j==8)
                printf("  ");
        }
        if (i==0)
            printf(" %s's ground..",player2);
        if (i==9)
            printf(" %s's ground..",player1);
        if (i==1)
        {
            int i=0 ;
            while(player2loses[i]!=0)
            {
                printf(" %c",player2loses[i++]);
            }
        }
        if (i==8)
        {
            int i=0 ;
            while(player1loses[i]!=0)
            {
                printf(" %c",player1loses[i++]);
            }

        }
        if (i==0 || i==8)
            printf("\n\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
                   196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196
                   ,196,196,196,196,196,196,196,196,196,196,196,196,196,196);
        printf("\n\n");
    }
}


//making a function for general moving

void analyzingMoving(char playerturn[] , char board[10][10],int counter[])
{
    int i;
    for (i=0; i<4; i++)
    {
        if (playerturn[i]=='A'||playerturn[i]=='a')
            counter[i]=1;
        else if (playerturn[i]=='B'||playerturn[i]=='b')
            counter[i]=2;
        else if(playerturn[i]=='C'||playerturn[i]=='c')
            counter[i]=3;
        else if(playerturn[i]=='D'||playerturn[i]=='d')
            counter[i]=4;
        else if(playerturn[i]=='E'||playerturn[i]=='e')
            counter[i]=5;
        else if(playerturn[i]=='F'||playerturn[i]=='f')
            counter[i]=6;
        else if(playerturn[i]=='G'||playerturn[i]=='g')
            counter[i]=7;
        else if(playerturn[i]=='H'||playerturn[i]=='h')
            counter[i]=8;
        else if(playerturn[i]=='1')
            counter[i]=8;
        else if (playerturn[i]=='2')
            counter[i]=7;
        else if(playerturn[i]=='3')
            counter[i]=6;
        else if(playerturn[i]=='4')
            counter[i]=5;
        else if(playerturn[i]=='5')
            counter[i]=4;
        else if(playerturn[i]=='6')
            counter[i]=3;
        else if(playerturn[i]=='7')
            counter[i]=2;
        else if(playerturn[i]=='8')
            counter[i]=1;
        else
            break;
    }
}

void makingMoving(char board[10][10],int b1,int b2,int b3,int b4)
{
    board[b3][b4]=board[b1][b2];

    if ((b1+b2)%2==0)
        board[b1][b2]='-';
    else
        board[b1][b2]='.';
}

//checking on knight moving
int Knight(char board[10][10] ,int b1,int b2 ,int b3, int b4)
{
    int checking;
    if (((((b1+b2)%2==0)&&((b3+b4)%2!=0))||(((b1+b2)%2!=0)&&((b3+b4)%2==0)))&&
            (((abs(b1-b3)==2)&&(abs(b2-b4)==1))||((abs(b1-b3)==1)&&(abs(b2-b4)==2))))
        checking=1;
    else
        checking=0;
    return checking;

}

int rook (char board[10][10], int b1,int b2,int b3,int b4)
{
    int checking=0;
    int i,j;
    if (((b1==b3)&&(b2!=b4))||((b1!=b3)&&(b2==b4)))
    {
        checking=1;
        if (b1!=b3)
        {
            if (b1<b3)
            {
                i=b1+1,j=b3;
                while(i<j)
                {
                    if ((board[i][b2]!='-')&&(board[i][b2]!='.'))
                        checking=0;
                    i++;
                }
            }
            if (b3<b1)
            {
                i=b3+1,j=b1;
                while(i<j)
                {
                    if ((board[i][b2]!='-')&&(board[i][b2]!='.'))
                        checking=0;
                    i++;

                }
            }
        }
        if (b2!=b4)
        {
            if (b2<b4)
            {
                i=b2+1,j=b4;
                while(i<j)
                {
                    if ((board[b1][i]!='-')&&(board[b1][i]!='.'))
                        checking=0;
                    i++;
                }
            }
            if (b4<b2)
            {
                i=b4+1,j=b2;
                while(i<j)
                {
                    if ((board[b1][i]!='-')&&(board[b1][i]!='.'))
                        checking=0;
                    i++;

                }
            }
        }
    }
    return checking;
}


int bishop (char board[10][10], int b1,int b2,int b3,int b4)
{
    int checking=0;
    int i , j;
    if ((abs(b1-b3))==(abs(b2-b4)))
    {
        checking=1;
        {
            if (b3>b1)
            {
                if (b4>b2)
                {
                    i=b1+1,j=b2+1;
                    while(i<b3)
                    {
                        if ((board[i][j]!='-')&&(board[i][j]!='.'))
                            checking=0;
                        i++,j++;
                    }
                }
                else if (b2>b4)
                {
                    i=b1+1,j=b2-1;
                    while(i<b3)
                    {
                        if ((board[i][j]!='-')&&(board[i][j]!='.'))
                            checking=0;
                        i++,j--;
                    }
                }
            }

            if (b1>b3)
            {
                if (b4>b2)
                {
                    i=b1-1,j=b2+1;
                    while(i>b3)
                    {
                        if ((board[i][j]!='-')&&(board[i][j]!='.'))
                            checking=0;
                        i--,j++;
                    }
                }
                else if (b2>b4)
                {
                    i=b1-1,j=b2-1;
                    while(i>b3)
                    {
                        if ((board[i][j]!='-')&&(board[i][j]!='.'))
                            checking=0;
                        i--,j--;
                    }
                }
            }
        }

    }


    return checking;
}

int pawn (char board[10][10], int b1,int b2,int b3,int b4)
{
    int checking=0;
    if ((((b1==2)&&((b3-b1==1)||((b3-b1==2)&&(board[b3-1][b4]=='-'||board[b3-1][b4]=='.')))&&(board[b1][b2]=='P'))||
            ((b1==7)&&((b1-b3==1)||((b1-b3==2)&&(board[b1-1][b4]=='-'||board[b1-1][b4]=='.')))&&(board[b1][b2]=='p')))
            &&(b2==b4)&&((board[b3][b4]=='-')||(board[b3][b4]=='.')))

        checking=1;
    else
    {
        if (board[b1][b2]=='p')
        {
            if (((b1-b3==1)&&(b2==b4)&&((board[b3][b4]=='-')||(board[b3][b4]=='.')))
                    || ((b1-b3==1)&&(abs(b2-b4)==1)&&(board[b3][b4]!='-')&&board[b3][b4]!='.'))
                checking=1;
        }
        else if (board[b1][b2]=='P')
            if (((b3-b1==1)&&(b2==b4)&&((board[b3][b4]=='-')||(board[b3][b4]=='.')))
                    || ((b3-b1==1)&&(abs(b2-b4)==1)&&(board[b3][b4]!='-')&&board[b3][b4]!='.'))
                checking=1;
    }


    return checking;
}

void pawnPromotion(char board[10][10], int b1,int b2,int b3,int b4)
{
    int i;
    for (i=0; i<16; i++)
    {
        if (piecesPromotiom[i][0]==0)
            break;

    }
    if (b3==8 || b3==1)
    {
        if (board[b3][b4]=='p')
        {

            do
            {
                piecesPromotiom[i][0]='p';
                printf("You have a promotion to  q/n/b/r : ");
                scanf(" %c",&board[b3][b4]);
            }
            while((board[b3][b4]!='q')&&(board[b3][b4]!='n')
                    &&(board[b3][b4]!='b')&&(board[b3][b4]!='r'));
            piecesPromotiom[i][1]=board[b3][b4];
        }
        else if (board[b3][b4]=='P')
        {
            do
            {
                piecesPromotiom[i][0]='P';
                printf("You have a promotion to  Q/N/B/R : ");
                scanf(" %c",&board[b3][b4]);
            }
            while((board[b3][b4]!='Q')&&(board[b3][b4]!='N')
                    &&(board[b3][b4]!='B')&&(board[b3][b4]!='R'));
            piecesPromotiom[i][1]=board[b3][b4];

        }
    }
}

int queen(char board[10][10],int b1,int b2,int b3,int b4)
{
    int checking;
    if (rook(board,b1,b2,b3,b4)||bishop(board,b1,b2,b3,b4))
        checking=1;
    else
        checking=0;
    return checking;
}

int king(char board[10][10],int b1, int b2,int b3, int b4)

{
    int checking=0;
    if (((abs(b1-b3)==1)&&(abs(b2-b4)==1))||((abs(b1-b3)==1)&&(b2==b4))||
            ((b1==b3)&&(abs(b2-b4)==1)))
        checking=1;
    else
        checking=0;
    return checking;
}

int checkingForUndo(char playerturn[4])
{
    int checking=0;
    if (((playerturn[0]=='u')||(playerturn[0]=='U'))&&
            ((playerturn[1]=='n')||(playerturn[1]=='n'))&&
            ((playerturn[2]=='d')||(playerturn[2]=='D'))&&
            ((playerturn[3]=='o')||(playerturn[3]=='O')))
        checking=1;
    return checking;
}

int checkingForRedo(char playerturn[4])
{
    int checking=0;
    if (((playerturn[0]=='r')||(playerturn[0]=='R'))&&
            ((playerturn[1]=='e')||(playerturn[1]=='E'))&&
            ((playerturn[2]=='d')||(playerturn[2]=='D'))&&
            ((playerturn[3]=='o')||(playerturn[3]=='O')))
        checking=1;
    return checking;
}

int undo(char board[10][10],int correctMoves[][4],int losesPosition[30][2],int stopAt)
{
    int certain=1;
    int b1,b2,b3,b4;
    stopAt=stopAt-1;
    b1=correctMoves[stopAt][0],b2=correctMoves[stopAt][1];
    b3=correctMoves[stopAt][2],b4=correctMoves[stopAt][3];
    if ((b1!=0)&&(b2!=0)&&(b3!=0)&&(b4!=0))
    {
        if (((abs(b1-b3)==1)&&(b2==b4))&&((b3==1)||(b3==8)))
        {
            int i;
            for (i=0; i<16; i++)
            {
                if (piecesPromotiom[i][0]==0)
                    break;
            }
            if (board[b3][b4]==piecesPromotiom[i-1][1])
            {
                board[b3][b4]=piecesPromotiom[i-1][0];
                piecesPromotiom[i-1][0]=piecesPromotiom[i-1][1]=0;
            }

        }

        makingMoving(board,b3,b4,b1,b2);
        int i=0;
        while (losesPosition[i][0]!=0)
            i++;
        i--;
        {
            if ((losesPosition[i][0]==b3)&&(losesPosition[i][1]==b4))
            {
                losesPosition[i][0]=losesPosition[i][1]=0;
                if ((board[b1][b2]=='p')||(board[b1][b2]=='r')||(board[b1][b2]=='b')||
                        (board[b1][b2]=='q')||(board[b1][b2]=='n'))
                {
                    int i=0;
                    while (player2loses[i]!=0)
                        i++;
                    i--;
                    board[b3][b4]=player2loses[i];
                    player2loses[i]=0;
                }
                if ((board[b1][b2]=='P')||(board[b1][b2]=='R')||(board[b1][b2]=='B')||
                        (board[b1][b2]=='Q')||(board[b1][b2]=='N'))
                {
                    int i=0;
                    while (player1loses[i]!=0)
                        i++;
                    i--;
                    board[b3][b4]=player1loses[i];
                    player1loses[i]=0;
                }
            }
        }

    }

    else
        certain=0;
    return certain;
}

//note that there's a problem in the redo function after several uses

int redo(char board[10][10],int correctMoves[][4],int losesPosition[30][2],int stopAt)
{
    int certain=1;
    int b1,b2,b3,b4;
    stopAt=stopAt;
    b1=correctMoves[stopAt][0],b2=correctMoves[stopAt][1];
    b3=correctMoves[stopAt][2],b4=correctMoves[stopAt][3];
    if ((b1!=0)&&(b2!=0)&&(b3!=0)&&(b4!=0))
    {
        playerloses(player1loses,player2loses,board,b3,b4);
        LP(losesPosition,board,b3,b4);
        makingMoving(board,b1,b2,b3,b4);
        if((board[b3][b4]=='p'||board[b3][b4]=='P')&&((b3==1)||(b3==8)))
        {
            system("cls");
            printBoard(board);
            pawnPromotion(board,b1,b2,b3,b4);
            system("cls");
            printBoard(board);
        }
    }
    else
        certain=0;
    return certain;
}

void playerloses(char player1loses[],char player2loses[],char board[10][10],int b3, int b4)
{
    if ((board[b3][b4]!='-')&&(board[b3][b4]!='.'))
    {
        if (board[b3][b4]=='p' || board[b3][b4]=='r' ||
                board[b3][b4]=='n' || board[b3][b4]=='b' ||
                board[b3][b4]=='q')
        {
            int i=0;
            while(player1loses[i]!=0)
                i++;
            player1loses[i]=board[b3][b4];
        }

        else
        {
            int i=0;
            while(player2loses[i]!=0)
                i++;
            player2loses[i]=board[b3][b4];
        }
    }
}


void LP(int losesPosition[30][2],char board[10][10],int b3, int b4)
{
    int i=0;
    if ((board[b3][b4]!='-')&&(board[b3][b4]!='.'))
    {
        while (losesPosition[i][0]!=0)
            i++;
        losesPosition[i][0]=b3;
        losesPosition[i][1]=b4;
    }
}



int checkingForSave(char playerturn[4])
{
    int checking=0;
    if (((playerturn[0]=='s')||(playerturn[0]=='S'))&&
            ((playerturn[1]=='a')||(playerturn[1]=='A'))&&
            ((playerturn[2]=='v')||(playerturn[2]=='V'))&&
            ((playerturn[3]=='e')||(playerturn[3]=='E')))
        checking=1;
    return checking;
}

void save(int correctMoves[SIZEMOVES][4])
{
    FILE *file;
    int i=0;
    if (SavingMode==0)
    {
        file=fopen("Game_saving","w");
        for (i=0; correctMoves[i][0]!=0; i++)
        {
            putw(correctMoves[i][0],file);
            putw(correctMoves[i][1],file);
            putw(correctMoves[i][2],file);
            putw(correctMoves[i][3],file);
        }
    }
    else if (SavingMode==1)
    {
        file=fopen("Game_saving","a");
        for (i=0; correctMoves[i][0]!=0; i++)
        {
            putw(correctMoves[i][0],file);
            putw(correctMoves[i][1],file);
            putw(correctMoves[i][2],file);
            putw(correctMoves[i][3],file);
        }
    }
    fclose(file);
}

int checkingForLoad(char playerturn[4])
{
    int checking=0;
    if (((playerturn[0]=='l')||(playerturn[0]=='L'))&&
            ((playerturn[1]=='o')||(playerturn[1]=='O'))&&
            ((playerturn[2]=='a')||(playerturn[2]=='A'))&&
            ((playerturn[3]=='d')||(playerturn[3]=='D')))
        checking=1;
    return checking;
}

int load(char board[10][10])
{
    system("cls");
    drawBoard(board);
    pieces(board);
    int arr[SIZEMOVES]= {0};
    FILE *file;
    file=fopen("Game_saving","r");
    int i=0,x;
    while((x=getw(file))!=EOF)
        arr[i++]=x;
    fclose(file);
    int b1,b2,b3,b4;
    for (i=0; arr[i]!=0; i=i)
    {
        b1=arr[i++];
        b2=arr[i++];
        b3=arr[i++];
        b4=arr[i++];
        makingMoving(board,b1,b2,b3,b4);
        if(board[b3][b4]=='p'||board[b3][b4]=='P')
        {
            system("cls");
            printBoard(board);
            pawnPromotion(board,b1,b2,b3,b4);
            system("cls");
            printBoard(board);
        }
    }
    return i/4;
}

int check1(char board[10][10])
{
    int k1,k2,i,j,count=0,p1,p2;
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='k')
                k1=i,k2=j;
        }
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='P' || board[i][j]=='R' ||
                    board[i][j]=='N' || board[i][j]=='B' ||
                    board[i][j]=='Q')
            {
                p1=i,p2=j;
                if (board[i][j]=='P')
                {
                    count+=pawn(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='R')
                {
                    count+=rook(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='N')
                {
                    count+=Knight(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='B')
                {
                    count+=bishop(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='Q')
                {
                    count+=queen(board,p1,p2,k1,k2);
                }

            }
        }
    return count;
}


int check2(char board[10][10])
{
    int k1,k2,i,j,count=0,p1,p2;
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='K')
                k1=i,k2=j;
        }
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='p' || board[i][j]=='r' ||
                    board[i][j]=='n' || board[i][j]=='b' ||
                    board[i][j]=='q')
            {
                p1=i,p2=j;
                if (board[i][j]=='p')
                {
                    count+=pawn(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='r')
                {
                    count+=rook(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='n')
                {
                    count+=Knight(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='b')
                {
                    count+=bishop(board,p1,p2,k1,k2);
                }
                else if (board[i][j]=='q')
                {
                    count+=queen(board,p1,p2,k1,k2);
                }

            }
        }
    return count;
}

int removeCheck1(char board[10][10])
{
    int state=1;
    char c;
    int k1,k2,i,j,k,m,p1,p2,checking;
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='k')
            {
                k1=i,k2=j;
                break;
            }
        }
    {
        int arr[8][2];
        p1=k1+1,p2=k2;
        arr[0][0]=p1;
        arr[0][1]=p2;
        p1=k1+1,p2=k2+1;
        arr[1][0]=p1;
        arr[1][1]=p2;
        p1=k1+1,p2=k2-1;
        arr[2][0]=p1;
        arr[2][1]=p2;
        p1=k1,p2=k2+1;
        arr[3][0]=p1;
        arr[3][1]=p2;
        p1=k1,p2=k2-1;
        arr[4][0]=p1;
        arr[4][1]=p2;
        p1=k1-1,p2=k2;
        arr[5][0]=p1;
        arr[5][1]=p2;
        p1=k1-1,p2=k2+1;
        arr[6][0]=p1;
        arr[6][1]=p2;
        p1=k1-1,p2=k2-1;
        arr[7][0]=p1;
        arr[7][1]=p2;
        for (i=0; i<8; i++)
        {
            p1=arr[i][0];
            p2=arr[i][1];
            if(((p1<=8 && p1>=1)&&(p2<=8 && p2>=1))&&(board[p1][p2]!='p'&&board[p1][p2]!='r'&&
                    board[p1][p2]!='b'&&board[p1][p2]!='n'&&board[p1][p2]!='q'))
            {
                checking=king(board,k1,k2,p1,p2);
                if (checking==1)
                {
                    c=board[p1][p2];
                    makingMoving(board,k1,k2,p1,p2);
                    state=check1(board);
                    makingMoving(board,p1,p2,k1,k2);
                    if (c!='-'&&c!='.')
                        board[p1][p2]=c;
                    if (state==0)
                        goto DT;

                }
            }
        }
    }
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='p' || board[i][j]=='r' ||
                    board[i][j]=='n' || board[i][j]=='b' ||
                    board[i][j]=='q')
            {
                for (k=1; k<=8; k++)
                    for (m=1; m<=8; m++)
                    {
                        if ((board[i][j]=='p')&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                                 board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=pawn(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='r')&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                                 board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=rook(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='n')&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                                 board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=Knight(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='b')&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                                 board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=bishop(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='q')&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                                 board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=queen(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                    }
            }
        }

    return state;
DT:
    return state;
}


int checkmate1(char board[10][10])
{
    int checking,checking2=-1;
    checking=check1(board);
    if(checking!=0)
    {
        checking2=removeCheck1(board);
        if (checking2!=0)
        {
            printf("It's a checkmate , player1 lose !");
            return checking2;
        }
        else if (checking2==0)
            return checking2;
    }
    return checking2;
}

int removeCheck2(char board[10][10])
{
    int state=1;
    char c;
    int k1,k2,i,j,k,m,p1,p2,checking;
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='K')
            {
                k1=i,k2=j;
                break;
            }
        }
    {
        int arr[8][2];
        p1=k1+1,p2=k2;
        arr[0][0]=p1;
        arr[0][1]=p2;
        p1=k1+1,p2=k2+1;
        arr[1][0]=p1;
        arr[1][1]=p2;
        p1=k1+1,p2=k2-1;
        arr[2][0]=p1;
        arr[2][1]=p2;
        p1=k1,p2=k2+1;
        arr[3][0]=p1;
        arr[3][1]=p2;
        p1=k1,p2=k2-1;
        arr[4][0]=p1;
        arr[4][1]=p2;
        p1=k1-1,p2=k2;
        arr[5][0]=p1;
        arr[5][1]=p2;
        p1=k1-1,p2=k2+1;
        arr[6][0]=p1;
        arr[6][1]=p2;
        p1=k1-1,p2=k2-1;
        arr[7][0]=p1;
        arr[7][1]=p2;
        for (i=0; i<8; i++)
        {
            p1=arr[i][0];
            p2=arr[i][1];
            if(((p1<=8 && p1>=1)&&(p2<=8 && p2>=1))&&(board[p1][p2]!='P'&&board[p1][p2]!='R'&&
                    board[p1][p2]!='B'&&board[p1][p2]!='N'&&board[p1][p2]!='Q'))
            {
                checking=king(board,k1,k2,p1,p2);
                if (checking==1)
                {
                    c=board[p1][p2];
                    makingMoving(board,k1,k2,p1,p2);
                    state=check2(board);
                    makingMoving(board,p1,p2,k1,k2);
                    if (c!='-'&&c!='.')
                        board[p1][p2]=c;
                    if (state==0)
                        goto DT;

                }
            }
        }
    }
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='P' || board[i][j]=='R' ||
                    board[i][j]=='N' || board[i][j]=='B' ||
                    board[i][j]=='Q')
            {
                for (k=1; k<=8; k++)
                    for (m=1; m<=8; m++)
                    {
                        if ((board[i][j]=='P')&&(board[k][m]!='P'&&board[k][m]!='R'&&
                                                 board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                        {
                            checking=pawn(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check2(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='R')&&(board[k][m]!='P'&&board[k][m]!='R'&&
                                                 board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                        {
                            checking=rook(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check2(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='N')&&(board[k][m]!='P'&&board[k][m]!='R'&&
                                                 board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                        {
                            checking=Knight(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check2(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='B')&&(board[k][m]!='P'&&board[k][m]!='R'&&
                                                 board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                        {
                            checking=bishop(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check2(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                        if ((board[i][j]=='Q')&&(board[k][m]!='P'&&board[k][m]!='R'&&
                                                 board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                        {
                            checking=queen(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check2(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                    goto DT;
                            }
                        }
                    }
            }
        }
    return state;
DT:
    return state;
}


int checkmate2(char board[10][10])
{
    int checking,checking2=-1;
    checking=check2(board);
    if(checking!=0)
    {
        checking2=removeCheck2(board);
        if (checking2!=0)
        {
            printf("It's a checkmate , player2 lose !");
            return checking2;
        }
        else if (checking2==0)
            return checking2;
    }
    return checking2;
}

int stalemate1(char board[10][10])
{
    int k1,k2,i,j,k,m,p1,p2,checking,state;
    char c;
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='k')
                k1=i,k2=j;
        }
    int arr[8][2];
    p1=k1+1,p2=k2;
    arr[0][0]=p1;
    arr[0][1]=p2;
    p1=k1+1,p2=k2+1;
    arr[1][0]=p1;
    arr[1][1]=p2;
    p1=k1+1,p2=k2-1;
    arr[2][0]=p1;
    arr[2][1]=p2;
    p1=k1,p2=k2+1;
    arr[3][0]=p1;
    arr[3][1]=p2;
    p1=k1,p2=k2-1;
    arr[4][0]=p1;
    arr[4][1]=p2;
    p1=k1-1,p2=k2;
    arr[5][0]=p1;
    arr[5][1]=p2;
    p1=k1-1,p2=k2+1;
    arr[6][0]=p1;
    arr[6][1]=p2;
    p1=k1-1,p2=k2-1;
    arr[7][0]=p1;
    arr[7][1]=p2;
    for (i=0; i<8; i++)
    {
        p1=arr[i][0];
        p2=arr[i][1];
        if(((p1<=8 && p1>=1)&&(p2<=8 && p2>=1))&&(board[p1][p2]!='p'&&board[p1][p2]!='r'&&
                board[p1][p2]!='b'&&board[p1][p2]!='n'&&board[p1][p2]!='q'))
        {
            checking=king(board,k1,k2,p1,p2);
            if (checking==1)
            {
                c=board[p1][p2];
                makingMoving(board,k1,k2,p1,p2);
                checking=check1(board);
                makingMoving(board,p1,p2,k1,k2);
                if (c!='-'&&c!='.')
                    board[p1][p2]=c;
                if (checking==0)
                    return checking;
            }
        }
    }
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='p' || board[i][j]=='r' ||
                    board[i][j]=='n' || board[i][j]=='b' ||
                    board[i][j]=='q')
            {
                for (k=1; k<=8; k++)
                    for (m=1; m<=8; m++)
                    {
                        if ((board[i][j]=='p'&&((i!=k)||(j!=m)))&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=pawn(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                {
                                    printf("p %d %d %d %d",i,j,k,m);
                                    return state;
                                }
                            }
                        }
                        if ((board[i][j]=='r'&&((i!=k)||(j!=m)))&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=rook(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                {
                                    printf("p %d %d %d %d",i,j,k,m);
                                    return state;
                                }
                            }
                        }
                        if ((board[i][j]=='n'&&((i!=k)||(j!=m)))&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=Knight(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                {
                                    printf("p %d %d %d %d",i,j,k,m);
                                    return state;
                                }
                            }
                        }
                        if ((board[i][j]=='b'&&((i!=k)||(j!=m)))&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=bishop(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                {
                                    printf("p %d %d %d %d",i,j,k,m);
                                    return state;
                                }
                            }
                        }
                        if ((board[i][j]=='q'&&((i!=k)||(j!=m)))&&(board[k][m]!='p'&&board[k][m]!='r'&&
                                board[k][m]!='n'&&board[k][m]!='b'&&board[k][m]!='q'&&board[k][m]!='k'))
                        {
                            checking=queen(board,i,j,k,m);
                            if (checking==1)
                            {
                                c=board[k][m];
                                makingMoving(board,i,j,k,m);
                                state=check1(board);
                                makingMoving(board,k,m,i,j);
                                if(c!='-'&&c!='.')
                                    board[k][m]=c;
                                if (state==0)
                                {
                                    printf("p %d %d %d %d",i,j,k,m);
                                    return state;
                                }
                            }
                        }
                    }
            }
        }
    state=1;
    return state;
}
int stalemate2(char board[10][10])
{
    int k1,k2,i,j,k,m,p1,p2,checking,state;
    char c;
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='K')
                k1=i,k2=j;
        }
    int arr[8][2];
    p1=k1+1,p2=k2;
    arr[0][0]=p1;
    arr[0][1]=p2;
    p1=k1+1,p2=k2+1;
    arr[1][0]=p1;
    arr[1][1]=p2;
    p1=k1+1,p2=k2-1;
    arr[2][0]=p1;
    arr[2][1]=p2;
    p1=k1,p2=k2+1;
    arr[3][0]=p1;
    arr[3][1]=p2;
    p1=k1,p2=k2-1;
    arr[4][0]=p1;
    arr[4][1]=p2;
    p1=k1-1,p2=k2;
    arr[5][0]=p1;
    arr[5][1]=p2;
    p1=k1-1,p2=k2+1;
    arr[6][0]=p1;
    arr[6][1]=p2;
    p1=k1-1,p2=k2-1;
    arr[7][0]=p1;
    arr[7][1]=p2;
    for (i=0; i<8; i++)
    {
        p1=arr[i][0];
        p2=arr[i][1];
        if(((p1<=8 && p1>=1)&&(p2<=8 && p2>=1))&&(board[p1][p2]!='P'&&board[p1][p2]!='R'&&
                board[p1][p2]!='B'&&board[p1][p2]!='N'&&board[p1][p2]!='Q'))
        {
            checking=king(board,k1,k2,p1,p2);
            if (checking==1)
            {
                c=board[p1][p2];
                makingMoving(board,k1,k2,p1,p2);
                checking=check2(board);
                makingMoving(board,p1,p2,k1,k2);
                if (c!='-'&&c!='.')
                    board[p1][p2]=c;
                if (checking==0)
                    return checking;
            }
        }
    }
    for (i=1; i<=8; i++)
        for (j=1; j<=8; j++)
        {
            if (board[i][j]=='P' || board[i][j]=='R' ||
                    board[i][j]=='N' || board[i][j]=='B' ||
                    board[i][j]=='Q')
            {
                for (k=1; k<=8; k++)
                    for (m=1; m<=8; m++)
                    {
                        if (board[i][j]=='P'&&((i!=k)||(j!=m)))
                            if((board[k][m]!='P'&&board[k][m]!='R'&&
                                    board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                            {
                                checking=pawn(board,i,j,k,m);
                                if (checking==1)
                                {
                                    c=board[k][m];
                                    makingMoving(board,i,j,k,m);
                                    state=check2(board);
                                    makingMoving(board,k,m,i,j);
                                    if(c!='-'&&c!='.')
                                        board[k][m]=c;
                                    if (state==0)
                                        return state;
                                }
                            }
                        if (board[i][j]=='R'&&((i!=k)||(j!=m)))
                            if((board[k][m]!='P'&&board[k][m]!='R'&&
                                    board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                            {
                                checking=rook(board,i,j,k,m);
                                if (checking==1)
                                {
                                    c=board[k][m];
                                    makingMoving(board,i,j,k,m);
                                    state=check2(board);
                                    makingMoving(board,k,m,i,j);
                                    if(c!='-'&&c!='.')
                                        board[k][m]=c;
                                    if (state==0)
                                        return state;
                                }
                            }
                        if (board[i][j]=='N'&&((i!=k)||(j!=m)))
                            if((board[k][m]!='P'&&board[k][m]!='R'&&
                                    board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                            {
                                checking=Knight(board,i,j,k,m);
                                if (checking==1)
                                {
                                    c=board[k][m];
                                    makingMoving(board,i,j,k,m);
                                    state=check2(board);
                                    makingMoving(board,k,m,i,j);
                                    if(c!='-'&&c!='.')
                                        board[k][m]=c;
                                    if (state==0)
                                        return state;
                                }
                            }
                        if (board[i][j]=='B'&&((i!=k)||(j!=m)))
                            if((board[k][m]!='P'&&board[k][m]!='R'&&
                                    board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                            {
                                checking=bishop(board,i,j,k,m);
                                if (checking==1)
                                {
                                    c=board[k][m];
                                    makingMoving(board,i,j,k,m);
                                    state=check2(board);
                                    makingMoving(board,k,m,i,j);
                                    if(c!='-'&&c!='.')
                                        board[k][m]=c;
                                    if (state==0)
                                        return state;
                                }
                            }
                        if (board[i][j]=='Q'&&((i!=k)||(j!=m)))
                            if((board[k][m]!='P'&&board[k][m]!='R'&&
                                    board[k][m]!='N'&&board[k][m]!='B'&&board[k][m]!='Q'&&board[k][m]!='K'))
                            {
                                checking=queen(board,i,j,k,m);
                                if (checking==1)
                                {
                                    c=board[k][m];
                                    makingMoving(board,i,j,k,m);
                                    state=check2(board);
                                    makingMoving(board,k,m,i,j);
                                    if(c!='-'&&c!='.')
                                        board[k][m]=c;
                                    if (state==0)
                                        return state;
                                }
                            }
                    }
            }
        }
    state=1;
    return state;
}