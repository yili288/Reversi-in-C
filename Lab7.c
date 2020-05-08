#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void printBoard(char board[26][26], int n){

    char letter = 'a';

    //first row of board
    printf("  ");
    for (int i=0; i<n; i++){
        printf("%c", letter+i);
    }

    for (int i=0; i<n; i++){
        printf("\n%c ", letter+i);
        for (int j=0; j<n; j++){
            printf("%c", board[i][j]);
        }
    }
}


bool positionInBounds(int n, int currentRow, int currentCol){
    bool inBounds=false;
    if (currentRow >= 0 && currentCol >= 0 && currentRow <n && currentCol <n){
        inBounds=true;
    }
    return inBounds;
}

void convertToCharAndPrint(int row, int col, int k, char allWMoves[100]){
    char alphabets[]="abcdefghijklmnopqrstuvwxyz";

    printf("%c%c\n", alphabets[row], alphabets[col]);
    allWMoves[k]=alphabets[row];
    allWMoves[k+1]=alphabets[col];
}

bool checkLegalInDirection(char board[26][26], int n, char player, int row, int col, int deltaRow, int deltaCol){

    bool legal=false;

    //something wrong with the conditional statement in the first if statement
    if (positionInBounds(n, row+deltaRow, col+deltaCol) == true && board[row+deltaRow][col+deltaCol] != player && board[row+deltaRow][col+deltaCol] != 'U') {
            int currentRow, currentCol;
            int i=1;

            do{
                i++; // starts looking at the element two steps away from initial position
                currentRow = row + deltaRow*i;
                currentCol = col + deltaCol*i;
            }while(positionInBounds(n, currentRow, currentCol) == true && board[currentRow][currentCol] != player && board[currentRow][currentCol] != 'U');


             if(board[currentRow][currentCol] == 'U'){
                    return legal;
              }else if (board[currentRow][currentCol] == player){
                    legal=true;
                    return legal;
                }else{
                    return legal;
                }


    } else {
        return legal;
    }
}


int totalPoints(char board[26][26], int n, char player, int row, int col, int deltaRow, int deltaCol){

    bool legal=false, decision=false;
    int i=1;
    //checks the next steps first
    if (positionInBounds(n, row+deltaRow, col+deltaCol) == true && board[row+deltaRow][col+deltaCol] != player && board[row+deltaRow][col+deltaCol] != 'U') {
        int currentRow, currentCol;
            while(true){
                i++; // starts checking the the element to two steps away
                currentRow = row + deltaRow*i;
                currentCol = col + deltaCol*i;
                decision = positionInBounds(n, currentRow, currentCol);
                if( decision == true){
                    if(board[currentRow][currentCol] == 'U'){
                        i=0;
                        return i;
                        break;
                    } else if (board[currentRow][currentCol] == player){
                        for(int j=0; j<i; j++){
                            board[row + deltaRow*j][col + deltaCol*j] = player;
                        }
                        return i-1;
                        break;
                    }
                }

            }

    } else {
        i=0;
        return i;
    }
}

void flipTiles(char board[26][26], int n, int row, int col, char player){

    int allPoints = totalPoints(board, n, player, row, col, 1, -1) +
    totalPoints(board, n, player, row, col, 1, 0) +
    totalPoints(board, n, player, row, col, 1, 1) +
    totalPoints(board, n, player, row, col, 0, 1) +
    totalPoints(board, n, player, row, col, -1, 1) +
    totalPoints(board, n, player, row, col, -1, 0) +
    totalPoints(board, n, player, row, col, -1, -1) +
    totalPoints(board, n, player, row, col, 0, -1);

}


int main(void){

    //the game ends when no player can move anymore or the board is full

    const int n;
    char board[26][26];
    printf("Enter the board dimension: ");
    scanf("%d", &n);

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            board[i][j] = 'U';
        }
    }

    board[(n/2)-1][(n/2)-1]= 'W';
    board[(n/2)-1][(n/2)]= 'B';
    board[(n/2)][(n/2)-1]= 'B';
    board[(n/2)][(n/2)]= 'W';

    printBoard(board, n);

    char colour, rowChar, colChar;
    char sequence[] = "abcdefghijklmnopqrstuvwxyz";
    char *locationRow, *locationCol;
    int rowValue, columnValue;

    //takes inputs and rewrite the new board
    printf("\nEnter board configuration: \n");
    scanf(" %c%c%c", &colour, &rowChar, &colChar);
    while(colour != '!' && rowChar != '!' && colChar != '!'){

        locationRow = strchr(sequence, rowChar);
        rowValue = (int)(locationRow - sequence);

        locationCol = strchr(sequence, colChar);
        columnValue = (int)(locationCol-sequence);

        board[rowValue][columnValue] = colour;

        scanf(" %c%c%c", &colour, &rowChar, &colChar);

    }

    //print out the reconfigured board
    printBoard(board, n);

    //show available positions from this point on
    printf("\nAvailable moves for W: \n");

    char player = 'W';
    char allWMoves[20];

    int k=0;

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
            if (board[row][col] == 'U'){
                if (checkLegalInDirection(board, n, player, row, col, 1, -1)==true){  //run time error starts here
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                } else if(checkLegalInDirection(board, n, player, row, col, 1, 0)==true){
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                }else if( checkLegalInDirection(board, n, player, row, col, 1, 1)==true){
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, 0, 1)==true){
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, -1, 1)==true){
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, -1, 0)==true){
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, -1, -1)==true){
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, 0, -1)==true){
                    convertToCharAndPrint(row, col, k, allWMoves);
                    k = k+2;
                }
            }
        }
    }

    printf("Available moves for B: \n");

    player = 'B';
    char allBMoves[20];

    k=0;

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
            if (board[row][col] == 'U'){
                if (checkLegalInDirection(board, n, player, row, col, 1, -1)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                } else if(checkLegalInDirection(board, n, player, row, col, 1, 0)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                }else if( checkLegalInDirection(board, n, player, row, col, 1, 1)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, 0, 1)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, -1, 1)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, -1, 0)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, -1, -1)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                }else if (checkLegalInDirection(board, n, player, row, col, 0, -1)==true){
                    convertToCharAndPrint(row, col, k, allBMoves);
                    k = k+2;
                }
            }
        }
    }


    printf("Enter a move: \n");
    scanf(" %c%c%c", &colour, &rowChar, &colChar);

    locationRow = strchr(sequence, rowChar);
    rowValue = (int)(locationRow - sequence);

    locationCol = strchr(sequence, colChar);
    columnValue = (int)(locationCol-sequence);

    if (colour == 'W')
    {
        for(int i=0; i<9; i++){
            if (allWMoves[2*i]==rowChar && allWMoves[2*i+1]==colChar){
                printf("Valid move.\n");
                flipTiles(board, n, rowValue, columnValue, 'W');
                printBoard(board, n);
                return 0;
            }
        }
        printf("Invalid move.");
        printBoard(board, n);
    }
    else if (colour == 'B')
    {
        for(int i=0; i<9; i++)
        {
            if (allBMoves[2*i]==rowChar && allBMoves[2*i+1]==colChar){
                printf("Valid move. \n");
                flipTiles(board, n, rowValue, columnValue, 'B');
                printBoard(board, n);
                return 0;
            }
        }
        printf("Invalid move.");
        printBoard(board, n);

    }
}
