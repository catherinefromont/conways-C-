#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
  
#define width 10
#define height 10
int gridSize = width * height;

 void printBoard(int *board)
  //nested for loop
  {
    int v = 0;

    for (int x = 0; x < gridSize; x++) 
    {
      v++;

      cout << board[x];
      if (v % width == 0)
      {
        cout << endl;
      }
    }
  }

  int checkNeighbours(int *board, int i, int j)
  {
   //checking the alive neighbours
  
   int count=0;
  

     count+=board[((i+width)%width) *width + ((j-1+height)%height)]; //left
     count+=board[((i+width)%width) *width + ((j+1+height)%height)];    //right
     count+=board[((i-1+width)%width) *width + j];    //up
     count+=board[((i+1+width)%width) *width + j];    //down
     count+=board[((i-1+width)%width) *width + ((j-1+height)%height)];  //up-left
     count+=board[((i+1+width)%width) *width + ((j+1+height)%height)];  //down-right
     count+=board[((i+1+width)%width) *width + ((j-1+height)%height)];  //down-left
     count+=board[((i-1+width)%width) *width + ((j+1+height)%height)] ;//up-right
      return count;
   
  }

  void gameRules(int *board, int *copyBoard)
  {
    
       // int neighbours;

    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++) {
        int x = width * i + j;
        int cell = board[x];
        int neighbours = checkNeighbours(board, i, j);
// Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
        if (cell == 1 && neighbours < 2) {

          copyBoard[x] = 0;
// Any live cell with more than three live neighbours dies, as if by overpopulation.
        } else if (cell == 1 && neighbours > 3) {

          copyBoard[x] = 0;
 // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        } else if (cell != 1 && neighbours == 3) {

          copyBoard[x] = 1;
// Any live cell with two or three live neighbours lives on to the next generation.
        } else if (cell == 1 && neighbours == 2 || neighbours == 3) {

          copyBoard[x] = 1;

        }
      }
      
    }
  }

  	int main()
	{

    // int* tempArr;
    int board[gridSize];
    int copyBoard[gridSize];
    for (int x = 0; x < gridSize; x++)
    {
      board[x] = 0;
      copyBoard[x] = 0;
    }
    //adding glider pattern
    board[2] = 1;
    board[13] = 1;
    board[23] = 1;
    board[22] = 1;
    board[21] = 1;

    printBoard(board);

    
    //for loop over all code (print board multiple times)
    for (int x = 0; x < 40; x++)
    {
      gameRules(board, copyBoard);
      for (int x = 0; x < gridSize; x++) 
    {   
      board[x] = copyBoard[x];
    }
    usleep(60000);
    printBoard(board);
    }



   
  }
