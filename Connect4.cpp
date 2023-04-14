#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void GameMenu();

const int ROWS = 6;
const int COLS = 7;

template <class Rep, class Period>
void sleep_for(const chrono::duration<Rep,Period>& rel_time);

class Board
{
  private:
    char board[ROWS][COLS];

    //private functions
    void DisplayBoard()
    { 
      cout<<endl<<"\t\t---------------"<<endl;
      for(int i = 0; i < ROWS; i++) 
      {
        cout<<"\t\t|";
        for (int j = 0; j < COLS; j++) 
        {
          if(board[i][j] == 'R') 
          {
            cout<<"\x1B[31m"<<board[i][j]<<"\033[0m";
          } 
          else if(board[i][j] == 'B') 
          {
            cout<<"\x1B[34m"<<board[i][j]<<"\033[0m";
          } 
          else 
          {
            cout<<"\x1B[37m"<<board[i][j]<<"\033[0m";
          }
          cout<<"|";
        }
        cout<<endl;
      }
      cout<<"\t\t---------------"<<endl;
      cout<<"\t\t|1|2|3|4|5|6|7|"<<endl;
      cout<<"\t\t---------------"<<endl;
      cout<<endl;
    }

    bool AddElement(char col, char player) 
    {
      // Make the move
      for(int i = ROWS - 1; i >= 0; i--) 
      {
        if(board[i][col] == ' ') 
        {
          board[i][col] = player;
          return true;
        }
      }
      return false;
    }

    bool HorizontalCheck(char player)   // Check horizontal
    {
      for(int i = 0; i < ROWS; i++) 
      {
        for(int j = 0; j <= COLS - 4; j++) 
        {
          if(board[i][j] == player && 
             board[i][j + 1] == player && 
             board[i][j + 2] == player && 
             board[i][j + 3] == player) 
          {
            return true;
          }
        }
      }
      return false;
    }

    bool VerticalCheck(char player)   // Check vertical
    {
      for(int i = 0; i <= ROWS - 4; i++) 
      {
        for(int j = 0; j < COLS; j++) 
        {
          if(board[i][j] == player && 
             board[i + 1][j] == player && 
             board[i + 2][j] == player && 
             board[i + 3][j] == player) 
          {
            return true;
          }
        }
      }
      return false;
    }

    bool LeftDiagonalCheck(char player) //from top left to bottom right
    {
      for(int i = 0; i <= ROWS - 4; i++) 
      {
        for(int j = 0; j <= COLS - 4; j++) 
        {
          if(board[i][j] == player && 
             board[i + 1][j + 1] == player && 
             board[i + 2][j + 2] == player && 
             board[i + 3][j + 3] == player) 
          {
            return true;
          }
        }
      }
      return false;
    }
  
    bool RightDiagonalCheck(char player) //from top right to bottom left
    {
      for(int i = 0; i <= ROWS - 4; i++) 
      {
        for(int j = 3; j < COLS; j++) 
        {
          if(board[i][j] == player && 
             board[i + 1][j - 1] == player && 
             board[i + 2][j - 2] == player && 
             board[i + 3][j - 3] == player) 
          {
            return true;
          }
        }
      }
      return false;
    }

    // Function to check if a player has won or not
    bool checkWin(char player) 
    {
      return HorizontalCheck(player) || VerticalCheck(player) ||     
             LeftDiagonalCheck(player) || RightDiagonalCheck(player);
    }

    // Function to check if the game board is full or not
    bool isBoardFull() 
    {
      for(int i = 0; i < ROWS; i++) 
      {
        for(int j = 0; j < COLS; j++) 
        {
          if(board[i][j] == ' ') 
          {
            return false;
          }   
        }
      }
      return true;
    }

    //Main gameplay
    void playGame() 
    {
      system("clear");
      int flag = 1;
      char columnInput[10];
      char player1 = 'R';
      char player2 = 'B';
      while(!isBoardFull())
      {
        DisplayBoard();
        if(flag == 1)
        {
          cout<<"\x1B[31mPlayer 1 (Red) Its your turn \033[0m"<<endl;
          cout<<"Please input column number (1-7) : ";
          cin>>columnInput;
          if(strlen(columnInput) != 1 || columnInput[0] < '1' || columnInput[0] > '7')
          {
            cout<<endl<<endl<<"Please give correct column number"<<endl;
            continue;
          }
          if(board[0][columnInput[0] - '1'] != ' ')
          {
            cout<<endl<<endl<<"Column is full! Please choose new column"<<endl;
            continue;
          }
          AddElement(columnInput[0] - '1', player1);
          bool result = checkWin(player1);
          if(result == true)
          {
            system("clear");
            cout<<"\t+-----------------------+"<<endl;
            cout<<"\t|     \x1B[31mPlayer 1 won\033[0m      |"<<endl;
            cout<<"\t+-----------------------+"<<endl;
            DisplayBoard();
            break;
          }
          flag = 2;
        }
        else
        {
          cout<<"\x1B[34mPlayer 2 (Blue) Its your turn \033[0m "<<endl;
          cout<<"Please input column number (1-7) : ";
          cin>>columnInput;
          if(strlen(columnInput) != 1 || columnInput[0] < '1' || columnInput[0] > '7')
          {
            cout<<endl<<endl<<"Please give correct column number"<<endl;
            continue;
          }
          if(board[0][columnInput[0] - '1'] != ' ')
          {
            cout<<endl<<endl<<"Column is full! Please choose new column "<<endl;
            continue;
          }
          AddElement(columnInput[0] - '1', player2);
          bool result = checkWin(player2);
          if(result == true)
          {
            system("clear");
            cout<<"\t+-----------------------+"<<endl;
            cout<<"\t|     \x1B[34mPlayer 2 won\033[0m      |"<<endl;
            cout<<"\t+-----------------------+"<<endl;
            DisplayBoard();
            break;
          }
          flag = 1;
        }
      }
      
      if(isBoardFull())
      {
        system("clear");
        cout<<"+-----------------------+"<<endl;
        cout<<"|       Game Draw       |"<<endl;
        cout<<"+-----------------------+"<<endl;
        DisplayBoard();
      }
    }

  public:
    Board() 
    {
      for (int i = 0; i < ROWS; i++) 
      {
        for (int j = 0; j < COLS; j++) 
        {
          board[i][j] = ' ';
        }
      }
    }
    
    void startGame()
    {
      playGame();
    }
    
};

void Restart()                        //To Restart The Game Again
{
  char restart[10];
  
  cout<<"\t+-------------------------+"<<endl;
  cout<<"\t|        GAME ENDS        |"<<endl;
  cout<<"\t|  THANK YOU FOR PLAYING  |"<<endl;
  cout<<"\t+-------------------------+"<<endl;
  
  cout<<endl<<endl<<" To Restart Game press 1 or press 2 to exit : ";
  cin>>restart;
  if(strlen(restart) == 1)
  {
    if(restart[0] == '1')
      GameMenu();
    else if(restart[0] == '2')
      exit(0);
    else
    {  
      cout<<endl<<" Wrong Option! Please choose correct option"<<endl<<endl;
      Restart();
    }
  }
  else
  {  
    cout<<endl<<" Wrong Option! Please choose correct option"<<endl<<endl;
    Restart();
  }
}

void Rules()
{
  char rulechoice;
  system("clear");

  cout<<"**********************************************************************************************************"<<endl;
  cout<<"*  RULES :                                                                                               *"<<endl;
  cout<<"*                                                                                                        *"<<endl;
  cout<<"*  1. Two-player (red(R) & blue(B)) game.                                                                *"<<endl;
  cout<<"*  2. Board size is 6 rows and 7 columns.                                                                *"<<endl;
  cout<<"*  3. A player wins if he/she is able to connect 4 dots horizontally, vertically or diagonally.          *"<<endl;
  cout<<"*  4. The game will draw when the board gets fully filled.                                               *"<<endl;
  cout<<"*                                                                                                        *"<<endl;
  cout<<"*  How to Play :                                                                                         *"<<endl;
  cout<<"*                                                                                                        *"<<endl;
  cout<<"*  1. Game always start with player 1 i.e. Red(R).                                                       *"<<endl;
  cout<<"*  2. In each step choose the column number in which you want to drop the ball.                          *"<<endl;
  cout<<"*  3. Rows will be filled from bottom to top in any column.                                              *"<<endl;
  cout<<"*                                                                                                        *"<<endl;
  cout<<"**********************************************************************************************************"<<endl;

  cout<<endl<<"Press 'R' to return Back To Main Menu : ";
  cin>>rulechoice;
  cin.ignore();
  
  if(rulechoice == 'R' || rulechoice == 'r')
    GameMenu();
  else
  {
    cout<<"Please give correct Input"<<endl<<endl;
    this_thread::sleep_for(chrono::milliseconds(900));
    Rules();
  }
}

void GameMenu()   //To display Game Menu
{
  Board board;
  char menuchoice[10];

  this_thread::sleep_for(chrono::milliseconds(900));

  system("clear");

  cout<<"******************************************************************************************"<<endl;
  cout<<"*                                                                                        *"<<endl;
  cout<<"*                       \x1B[33m+-----------------------\x1B[31m/|\033[0m\x1B[33m--------+\033[0m                              *"<<endl;
  cout<<"*                       \x1B[33m|\033[0m   Welcome To Connect \x1B[31m/_|_\033[0m Game  \x1B[33m|\033[0m                              *"<<endl;
  cout<<"*                       \x1B[33m+------------------------\x1B[31m|\033[0m\x1B[33m--------+\033[0m                              *"<<endl;
  cout<<"*                                                                                        *"<<endl;
  cout<<"******************************************************************************************"<<endl;
  cout<<"*                                                                                        *"<<endl;
  cout<<"*  Press '1' to start the Game                                                           *"<<endl;
  cout<<"*  Press '2' for Controls and Rules                                                      *"<<endl;
  cout<<"*  Press '3' to exit the Game                                                            *"<<endl;
  cout<<"*                                                                                        *"<<endl;
  cout<<"******************************************************************************************"<<endl;

  cout<<" Enter your choice : ";
  cin>>menuchoice;

  if(strlen(menuchoice) == 1)
  {
    if(menuchoice[0] == '1')
      board.startGame();
    else if(menuchoice[0] == '2')
      Rules();
    else if(menuchoice[0] == '3')
      exit(0);
    else
    {
      cout<<" Wrong Option! Please choose correct option "<<endl<<endl;
      this_thread::sleep_for(chrono::milliseconds(900));
      GameMenu();
    }
  }
  else
  {
    cout<<" Wrong Option! Please choose correct option "<<endl<<endl;
    this_thread::sleep_for(chrono::milliseconds(900));
    GameMenu();
  }
}

int main()
{
  GameMenu();
  Restart();
  return 0;
}