#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;



int Play_Game(int size, int board[][10],int,int,int,int,int score);

void Display_Board(int size,int board[][10],int score);

void Setup_Board(int size, int board[][10]);

void Clear_Board(int size, int board[][10]);

int main()
{
	//srand(time(0));
	
	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	
	int const size=10;
	int board[size][size]={0};
	int row,col,row2,col2;
	int n=0;
	int score=0,total_score=0;
	
	Setup_Board(size,board);
	
	Display_Board(size,board,score);
	//Instructions: 
	// 1. When entering row,col,row2 and col2, make sure that the "row and col" index is the one with which a chain is being formed after the swap.
	
	
	while (n!=-1)
	{
	
	
		if (n==5)
		{
			ofstream fout("SaveFile.txt");
			if (!fout)
			{
				cout<<"File cannot be created.";
			}
			else
			{
				
				fout<<score<<endl;
				for (int i=0;i<size;i++)
				{
					for (int j=0;j<size;j++)
					{
						fout<<board[i][j]<<endl;
					}
					
				}
			}
			fout.close();
		}
		
		if (n==6)
		{
			ifstream fin("SaveFile.txt");
			if (!fin)
			{
				cout<<"File does not exist.";
			}
			else
			{
				
				fin>>score;
				for (int i=0;i<size;i++)
				{
					
					for (int j=0;j<size;j++)
					{
						fin>>board[i][j];
					}
				}
			}
			fin.close();
			Display_Board(size,board,score);
		}
		
		
		cout<<endl;
		cout<<"Enter row number to go to = ";
		cin>>row;
		cout<<"Enter coloumn number to go to = ";
		cin>>col;
		
		cout<<endl;
		
		cout<<"Enter row number to go from = ";
		cin>>row2;
		cout<<"Enter coloumn number to go from = ";
		cin>>col2;
		
		score=Play_Game(size, board,row,col,row2,col2,score);
		total_score=total_score + score;
		Clear_Board(size,board);
		Display_Board(size,board,score);
		
		cout<<endl<<"Enter n = ";
		cin>>n;
	}
	
	cout<<"GAME OVER! "<<endl<<"Total score = "<<total_score;


	return 0;
}

int Play_Game(int size, int board[][10],int row,int col,int row2,int col2,int score)
{
	int w=1,x=1,y=1,z=1;
	int p=0,q=0;
	int temp;
	int max=0;
	
	//check whether the swaps can be made or not. The row2 and col2 should be adjacent to the row and col and not diagonally. 
	if ( ((row2==row)|| (row2==row-1)|| (row2==row+1)) && ((col2==col)|| (col2==col-1)|| (col2==col+1)) )
	{
		if ((row2==row)&&(col2==col))
		{
			cout<<"Swap not possible with same element.";
		} 
		 else
		 {
		 
			temp=board[row2][col2];
			board[row2][col2]=board[row][col];
			board[row][col]=temp;
				
			//now check row,col for the chain length!
			
			
			//for going backwards in both cols and rows.
			for (int i=row;i>0;i--)
			{
				int k=1;
				if (i==row)
				{
					for (int j=col; j>0;j--)
					{
						if (board[i][j]==board[i][j-1])
						{
							w=w+1;
						}
						else
						{
							j=0;
						}
						
					}
				}	
				if (board[i][col]==board[i-1][col])
				{
					x=x+1;
				}
				else
				{
					i=0;
				}
				
			}
			
			//for going forwards in both cols and rows.
			for (int i = row; i<size;i++)
			{
				int k=1;
				if (i==row)
				{
					for (int j=col;j<size;j++)
					{
						if (board[i][j]==board[i][j+1])
						{
							y=y+1;
						}
						else
						{
							j=size;
						}
					}
				}
				if (board[i][col]==board[i+1][col])
				{
					z=z+1;
				}
				else
				{
					i=size;
				}
			}
			
			//for middle indexes where the swap is made inbetween an almost complete chain
			if ( (w>1)&&(y>1) )
			{
				 p=(w+y)-1;
			}
			
			if ( (x>1) && (z>1) )
			{
				q=(x+z)-1;
			}
			
			max=w;
			if (x>max)
			{
				max=x;
			}
			if (y>max)
			{
				max=y;
			}
			if (z>max)
			{
				max=z;
			}
			if (p>max)
			{
				max=p;
			}
			if (q>max)
			{
				max=q;
			}
			
			
			//for destroying the same colored elements and replacing them with above elements. The top row gets new random elements.
			
			if (max>=3)
			{
				if (max==w)
				{
					cout<<"1"<<endl;
					for (int j=col;j>col-w;j--)
					{
						int a=row;
						while (a>0)
						{
							board[a][j]=board[a-1][j];
							a--;
						}
						board[a][j]=1 + (rand()% 5);
					}
					score = score + 10;
				}
				
				else if (max==x)
				{
					cout<<endl<<"3";
					int c=row;
					while (c>=0)
					{
						if (c<3)
						{
							board[c][col]=1+(rand()%5);
						}
						else 
						{						
							board[c][col]=board[c-3][col];
						}
						c--;
					}
					score=score+10;
					
				}
				
				else if (max==y)
				{
					for (int j=col;j<col+y;j++)
					{
						int a=row;
						while (a>0)
						{
							board[a][j]=board[a-1][j];
							a--;
						}
						board[a][j]=1 + (rand()% 5);
					}
					score=score+10;
				}
				
				else if (max==z)
				{
					cout<<endl<<"4"<<endl;
					int	d=row + 2;
					if (row==8)
					{
						d=d-1;
					}
					if (row==9)
					{
						d=d-2;
					}
					while (d>=0)
					{
						
						if (d<3)
						{
							board[d][col]=1+(rand()%5);
						}
						else 
						{						
							board[d][col]=board[d-3][col];
						}
						d--;
					

					}
					score=score+10;
				}
				
				else if (max==p)
				{
					for (int j=col;j>col-w;j--)
					{
						int a=row;
						while (a>0)
						{
							board[a][j]=board[a-1][j];
							a--;
						}
						board[a][j]=1 + (rand()% 5);
					}
					
					for (int j=col+1;j<col+y;j++)
					{
						int a=row;
						while (a>0)
						{
							board[a][j]=board[a-1][j];
							a--;
						}
						board[a][j]=1 + (rand()% 5);
					}
					
					score = 30;
				}
				
				else if (max==q)
				{
					for (int i=row;i>row-x;i--)
					{
						int c=row+(z-1);
						while (c>=0)
						{
							if (c<x+1) 
							{
								board[c][col]=1+(rand()%5);
							}
							else 
							{						
								board[c][col]=board[c-(x+1)][col];
							}
							c--;
						}
					}
					score=score+30;
				}
			
			}
			else
			{
				cout<<endl<<"Swap not possible."<<endl;
			}
				
		}
			
	}
	else
	{
		cout<<endl<<"Swap is not possible."<<endl;
	}

	return score;
	
}

void Setup_Board(int size,int board[][10])
{
	
	int a;
	
	for (int i=0;i<size;i++)
	{
		for (int j=0;j<size;j++)
		{
			//to get random numbers from 1 to 5.
			a = 1 + (rand() % 5);
			board[i][j]=a;
			
			if (j>1)
			{
				while ( (board[i][j]==board[i][j-1]) && (board[i][j]==board[i][j-2]) )
				{
					a = 1 + (rand()%5);
					board[i][j]=a;
				}
			}
			
			if (i>1)
			{
				while ( (board[i][j]==board[i-1][j]) && (board[i][j]==board[i-2][j]) )
				{
					a = 1 + (rand()%5);
					board[i][j]=a;
				}
			}
			
		}
	
	}
	
	
}

void Display_Board(int size, int board[][10],int score)
{

	system("CLS");

	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	
	cout<<"Welcome to Color Puzzle! "<<endl<<"---------------------------------------------"<<endl;
	cout<<"Instructions: "<<endl<<"1. Enter 5 to save. "<<endl<<"2. Enter 6 to load."<<endl<<"3. Enter -1 to quit."<<endl;
	cout<<"4. Enter any other number to continue the game."<<endl<<"---------------------------------------------"<<endl<<endl;
	
		
	cout<<endl<<"Current score = "<<score<<endl<<endl;	
		
		
	for (int i =0;i<size;i++)
	{
		if (i==0)
		{
			cout<<"   ";
		}
		
		cout<<i<<" ";
		
	}	
	cout<<endl<<endl;
	
	for (int i =0;i<size;i++)
	{
		
		cout<<i<<"  ";
		for (int j=0;j<size;j++)
		{
			if (board[i][j]==1)
			{
				SetConsoleTextAttribute (h,10);
			}
			if (board[i][j]==2)
			{
				SetConsoleTextAttribute (h, 11);
			}
			if (board[i][j]==3)
			{
				SetConsoleTextAttribute (h, 12);
				
			}
			if (board[i][j]==4)
			{
				SetConsoleTextAttribute (h, 13);
			}
			if (board[i][j]==5)
			{
				SetConsoleTextAttribute (h, 14);
			}
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
		SetConsoleTextAttribute (h,15);
	}
	
	
	
}

void Clear_Board(int size,int board[][10])
{
	int a;
	for (int i =0;i<size;i++)
	{
		for (int j=0;j<size;j++)
		{
		
			if (j>1)
			{
				while ( (board[i][j]==board[i][j-1]) && (board[i][j]==board[i][j-2]) )
				{
					a = 1 + (rand()%5);
					board[i][j]=a;
				}
			}
			
			if (i>1)
			{
				while ( (board[i][j]==board[i-1][j]) && (board[i][j]==board[i-2][j]) )
				{
					a = 1 + (rand()%5);
					board[i][j]=a;
				}
			}
		}
	}
}
