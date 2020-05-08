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
        return inBounds;
    }else{
        return inBounds;
    }
}

void convertToChar(int row, int col, char highestPosition[2]){
    char alphabets[]="abcdefghijklmnopqrstuvwxyz";
    highestPosition[0]=alphabets[row];
    highestPosition[1]=alphabets[col];
}

bool checkLegalInDirection(char board[26][26], int n, char turn, int row, int col, int deltaRow, int deltaCol){

    char opposite;
    if (turn == 'B'){
        opposite = 'W';
    }else{
        opposite = 'B';
    }
    bool legal=false;

    //something wrong with the conditional statement in the first if statement
    if (positionInBounds(n, row+deltaRow, col+deltaCol) == true && board[row+deltaRow][col+deltaCol] == opposite){
            int currentRow, currentCol;
            int i=1;

            do{
                i++; // starts looking at the element two steps away from initial position
                currentRow = row + deltaRow*i;
                currentCol = col + deltaCol*i;
            }while(positionInBounds(n, currentRow, currentCol) == true && board[currentRow][currentCol] == opposite);

            //printf("\n%c, row-%d col-%d, delta: %d %d\n", board[currentRow][currentCol], currentRow, currentCol, deltaRow, deltaCol);
            if (positionInBounds(n, currentRow, currentCol) == true && board[currentRow][currentCol] == turn){
                legal = true;
                return legal;
            }else{
                return legal;
            }

    } else {
        return legal;
    }
}

bool checkIfLegal (char board[26][26], int n, char turn, int row, int col){

    if (checkLegalInDirection(board, n, turn, row, col, 1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 1, 0)==true ||
        checkLegalInDirection(board, n, turn, row, col, 1, 1)==true || checkLegalInDirection(board, n, turn, row, col, 0, 1)==true ||
        checkLegalInDirection(board, n, turn, row, col, -1, 1)==true || checkLegalInDirection(board, n, turn, row, col, -1, 0)==true ||
        checkLegalInDirection(board, n, turn, row, col, -1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 0, -1)==true){
        return true;
    }else {
        return false;
    }
}

bool moveAvailable(char board[26][26], int n, char turn){
    bool availableMoves = false;

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
            if (board[row][col] == 'U'){
                    if (checkLegalInDirection(board, n, turn, row, col, 1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 1, 0)==true ||
                        checkLegalInDirection(board, n, turn, row, col, 1, 1)==true || checkLegalInDirection(board, n, turn, row, col, 0, 1)==true ||
                        checkLegalInDirection(board, n, turn, row, col, -1, 1)==true || checkLegalInDirection(board, n, turn, row, col, -1, 0)==true ||
                        checkLegalInDirection(board, n, turn, row, col, -1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 0, -1)==true){
                        availableMoves = true;
                        return availableMoves;
                    }
            }
        }
    }

    return availableMoves;
}

int fASHelper(char board[26][26], int n, char turn, int row, int col, int deltaRow, int deltaCol, bool flip){  //flips tiles and outputs the score

    char opposite;
    if (turn == 'B'){
        opposite = 'W';
    }else{
        opposite = 'B';
    }
    bool legal = false;
    int i=1;
    //checks the next steps first
    if (positionInBounds(n, row+deltaRow, col+deltaCol) == true && board[row+deltaRow][col+deltaCol] == opposite){
        int currentRow, currentCol;

            do{
                i = i+1; // starts checking the the element to two steps away
                currentRow = row + deltaRow*i;
                currentCol = col + deltaCol*i;
            }while(positionInBounds(n, currentRow, currentCol) == true && board[currentRow][currentCol] == opposite);


            if (positionInBounds(n, currentRow, currentCol) == true && board[currentRow][currentCol] == turn){
                    if(flip == true){
                        for(int j=0; j<i; j++){
                            board[row + (deltaRow*j)][col + (deltaCol*j)] = turn;
                        } // flipping happens here
                    }
                    return i-1;
            } else{
                return 0;
            }

    } else {
        return 0;
    }
}

int decideFlipAndScore(char board[26][26], int n, int row, int col, char turn, bool flip){  //calls the helper function for every direction and adds the total score

    //as i am slipping for each direction I am changing the board
    //but it doesnt matter, it should still work because each diferection takes a different path
    int totalScore = fASHelper(board, n, turn, row, col, 1, -1, flip) +
    fASHelper(board, n, turn, row, col, 1, 0, flip) +
    fASHelper(board, n, turn, row, col, 1, 1, flip) +
    fASHelper(board, n, turn, row, col, 0, 1, flip) +
    fASHelper(board, n, turn, row, col, -1, 1, flip) +
    fASHelper(board, n, turn, row, col, -1, 0, flip) +
    fASHelper(board, n, turn, row, col, -1, -1, flip) +
    fASHelper(board, n, turn, row, col, 0, -1, flip);

    return totalScore;

}

char findOpposite (char turn){

    if(turn == 'W'){
        return 'B';
    }else if(turn == 'B'){
        return 'W';
    }
}


int main(void){

    const int n;
    char board[26][26];
    const char computer;

    printf("Enter the board dimension: ");
    scanf("%d", &n);

    printf("Computer plays (B/W): ");
    scanf(" %c", &computer);

    //prints the starting board
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

    char turn = 'B';
    bool continueGame = true;
    int score;


    while(continueGame = true){

        //computers turn
        if (turn == computer){
            int highestScore=0, bestRow, bestCol;
            char highestPosition[2];

            //processes info in numbers until the end (before printing)
            //int i=3, j=2;
            for(int row=0; row<n; row++){
                for(int col=0; col<n; col++){
                        if (board[row][col] == 'U' ){
                            if (checkLegalInDirection(board, n, turn, row, col, 1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 1, 0)==true ||
                                checkLegalInDirection(board, n, turn, row, col, 1, 1)==true || checkLegalInDirection(board, n, turn, row, col, 0, 1)==true ||
                                checkLegalInDirection(board, n, turn, row, col, -1, 1)==true || checkLegalInDirection(board, n, turn, row, col, -1, 0)==true ||
                                checkLegalInDirection(board, n, turn, row, col, -1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 0, -1)==true){

                                score = decideFlipAndScore(board, n, row, col, turn, false);  //don't flip just count the score

                                if ( score > highestScore){
                                    highestScore = score;
                                    bestRow = row;
                                    bestCol = col;
                                }else if( score == highestScore){
                                    highestScore = highestScore;
                                    bestRow = bestRow;
                                    bestCol = bestCol;
                                }
                            }
                    }
                }
           }

            highestScore = decideFlipAndScore(board, n, bestRow, bestCol, turn, true);
            convertToChar(bestRow, bestCol, highestPosition);
            printf("\nComputer places %c at %c%c.\n", turn, highestPosition[0], highestPosition[1]);
            printBoard(board, n);


        }else {
            //setup to convert Char to Number
            int row, col;
            char rowChar, colChar;
            char sequence[] = "abcdefghijklmnopqrstuvwxyz";
            char *locationRow, *locationCol;

            printf("\nEnter move for colour %c (RowCol): ", turn);
            scanf(" %c%c", &rowChar, &colChar);

            locationRow = strchr(sequence, rowChar);
            row = (int)(locationRow - sequence);

            locationCol = strchr(sequence, colChar);
            col = (int)(locationCol-sequence);

            if (board[row][col] == 'U'){
                if (checkLegalInDirection(board, n, turn, row, col, 1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 1, 0)==true ||
                    checkLegalInDirection(board, n, turn, row, col, 1, 1)==true || checkLegalInDirection(board, n, turn, row, col, 0, 1)==true ||
                    checkLegalInDirection(board, n, turn, row, col, -1, 1)==true || checkLegalInDirection(board, n, turn, row, col, -1, 0)==true ||
                    checkLegalInDirection(board, n, turn, row, col, -1, -1)==true || checkLegalInDirection(board, n, turn, row, col, 0, -1)==true){
                    score = decideFlipAndScore(board, n, row, col, turn, true); //flips all tiles
                    printBoard(board, n);
                }else {
                        printf("\Invalid move.\n%c player wins.", computer);
                        return 0;
                }
            }else {
                printf("\Invalid move.\n%c player wins.", computer);
                return 0;
            }
        }

        //decide who goes next
        if (moveAvailable(board, n, findOpposite(turn)) == true ){
            turn = findOpposite(turn);
        }else if (moveAvailable(board, n,turn) == true){
            turn = turn;
            printf("\n%c player has no valid move.", findOpposite(turn));
        }

        if (moveAvailable(board, n, findOpposite(turn)) != true && moveAvailable(board, n, turn) != true){
            break;
        }

    }//end of while loop

    //Decide the winner
    int counterB, counterW;

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){
                if(board[row][col] == 'B'){
                    counterB = counterB + 1;
                }else if (board[row][col] == 'W'){
                    counterW = counterW + 1;
                }else{
                    counterB = counterB;
                    counterW = counterW;
                }
        }
    }

    if (counterW > counterB) {
        printf("\nW player wins.");
        return 0;
    }else if (counterW < counterB){
        printf("\nB player wins.");
        return 0;
    }else if (counterW == counterB){
        printf("\nDraw!");
        return 0;
    }

}
