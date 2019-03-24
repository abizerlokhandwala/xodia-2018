#include<iostream>
#include<string.h>
using namespace std;
char board[5][5];
int cost=0;
bool whoAmI;
// Nodes of Graph
class Node{
public :
char temp_board [5][5];
int depth;
Node *next;
friend class Game;
};

class Game
{

public :
Node *root;
Game()
{
	Node *curr=new Node;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			
		}
	}
	root=curr;
}
	void makemove()
	{
		
	}
};
//FUNCTIONS:

int mValidation();		//validates your sample move according to the given rules in the documentation

void undoMove();		//undoes the temporarily made move
int algorithm();		//your game's algorithm
int evaluate();			//evaluation for your move


void initBoard ()		//Function to initialize the Board
{
    for (int i = 0; i < 5; i++)
    {
        board[0][i] = 'B';
        board[1][i] = 'b';
        board[2][i] = '_';
        board[3][i] = 'r';
        board[4][i] = 'R';
    }
}
bool check(int i,int j)
{
	if(i<=4 and i>=0 and j>=0 and j<=4)
		return true;
	else
		return false;
}
string makemove(bool whoAmI)
{
	string output,fin_output;
	int temp_cost;
	cost=-1;
	
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				temp_cost=0;
				if(board[i][j]=='B')
				{
					output.append(to_string(i));
					output.append(" ");
					output.append(to_string(j));
					output.append(" ");
					if(check(i+2,j) and (board[i+1][j]=='R' or board[i+1][j]=='r'))
					{
						temp_cost+=100;
						board[i+1][j]='_';
						output.append(to_string(i+2));
					output.append(" ");
					output.append(to_string(j));
					}
					else if(check(i,j-2) and (board[i][j-1]=='R' or board[i][j-1]=='r'))
					{
						temp_cost+=100;
						board[i][j-1]='_';
						output.append(to_string(i));
					output.append(" ");
					output.append(to_string(j-1));
					}
					else if(check(i,j+2) and (board[i][j+1]=='R' or board[i][j+1]=='r'))
					{
						temp_cost+=100;
						board[i][j+1]='_';
						output.append(to_string(i));
					output.append(" ");
					output.append(to_string(j+1));
					}
					else if(check(i+1,j) and board[i+1][j]=='_')
					{
						
						temp_cost+=10*(i+1);
						output.append(to_string(i+1));
					output.append(" ");
					output.append(to_string(j));
					

					}
					else if(check(i+1,j+1) and board[i+1][j+1]=='_')
					{
						
						temp_cost+=10*(i+1);
						output.append(to_string(i+1));
					output.append(" ");
					output.append(to_string(j+1));
					
					}
					else if(check(i+1,j-1) and board[i+1][j-1]=='_')
					{
						
						temp_cost+=10*(i+1);
						output.append(to_string(i+1));
					output.append(" ");
					output.append(to_string(j-1));
						
					}
					else if(check(i,j+1) and board[i][j+1]=='_')
					{
						temp_cost+=0;
						output.append(to_string(i));
					output.append(" ");
					output.append(to_string(j+1));
					}
					else if(check(i,j-1) and board[i][j-1]=='_')
					{
						temp_cost+=0;
						output.append(to_string(i));
					output.append(" ");
					output.append(to_string(j-1));
					}

				}
				else if(board[i][j]=='b'){
					output.append(to_string(i));
					output.append(" ");
					output.append(to_string(j));
					output.append(" ");
					if(check(i+1,j+1) and board[i+1][j+1]=='_')
					{
						temp_cost+=1;
						output.append(to_string(i+1));
					output.append(" ");
					output.append(to_string(j+1));
					}
					else if(check(i+1,j-1) and board[i+1][j-1]=='_')
					{
						temp_cost+=1;
						output.append(to_string(i+1));
					output.append(" ");
					output.append(to_string(j-1));
					}

				}

				if(cost==-1)
				{
					cost=temp_cost;
					fin_output=output;
				}
				else if(temp_cost>cost)
				{
					cost=temp_cost;
					fin_output=output;
				}
				output.clear();
			}
		}
	
	

	return fin_output;
		

	
}
 void makechange(string output)
 {
 	int a=(int)output[0]%48;
 	int b=(int)output[2]%48;
 	int c=(int)output[4]%48;
 	int d=(int)output[6]%48;

 	char temp=board[a][b];
 	board[a][b]='_';
 	board[c][d]=temp;
 	/*	for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				cout<<board[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	*/
 }

int main()
{
	initBoard();
	bool turn;
	string input, output;
	cin>>turn;
	//if turn = 1, you are Sentinels(blue) and it's your turn first
	//if turn = 0, you are Scourges(red) and it's opponent's turn first
	 whoAmI=turn;


	while(1)
	{
		string a,b,c,d;
		int p,q,r,s;
		if(turn!=1)
		{
			
			cin>>a>>b>>c>>d;
			p=stoi(a);
			q=stoi(b);
			r=stoi(c);
			s=stoi(d);
			input.append(a);
			input.append(" ");
			input.append(b);
			input.append(" ");
			input.append(c);
			input.append(" ");
			input.append(d);
			if(q==s and abs(p-r)==2 and (board[p-1][q]=='b' or board[p-1][q]=='B'))
			{
				board[p-1][q]='_';
			}
			if(p==r and s>q and (board[p][q+1]=='b' or board[p][q+1]=='B'))
			{
				board[p][q+1]='_';
			}
			if(p==r and s<q and (board[p][q-1]=='b' or board[p][q-1]=='B'))
			{
				board[p][q-1]='_';
			}

			makechange(input);
			input.clear();
			//Input from opponent
			//Use this input to make changes in your board
		}
	//	Game g;
	
		turn=0;	//after first iteration, (turn!=1) is always true
				//i.e. turn is always 0
		//g.makemove();
		output=makemove(whoAmI);

		makechange(output);
		//your logic to make the next move
		//output your move string
		cout<<output<<endl;
	}
}

