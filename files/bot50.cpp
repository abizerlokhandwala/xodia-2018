#include<iostream>
#include<string.h>
#include<sstream>
#include<cmath>
using namespace std;

char board[5][5];	//Your board
class move	//class for denoting a move
{
public:
	int x1,y1,x2,y2;
	move()	//constructor
	{
		x1=0;	y1=0;
		x2=0;	y2=0;
	}
    move(const move &tocopy)	//copy constructor
    {
        x1=tocopy.x1;	y1=tocopy.y1;
        x2=tocopy.x2;	y2=tocopy.y2;
    }
};
bool whoAmI;	//if whoAmI = 1, you are Sentinels. base=0
				//if whoAmI = 0, you are Scourges, base=4

//FUNCTIONS:
string findBestMoveSentinels();	//returns the move you want to make
string findBestMoveScourges();	//returns the move you want to make
int mValidation();		//validates your sample move according to the given rules in the documentation
void makemove (int, int, int, int);		//makes move temporarily
void undoMove();		//undoes the temporarily made move
int algorithm();		//your game's algorithm
int evaluate();			//evaluation for your move
string eliminateScourgesBombersSides(int, int);
string eliminateScourgesStingersSidesNotSafe(int, int);
string eliminateScourgesStingersSidesSafe(int, int);
string eliminateSentinelsBombersSides(int, int);
string eliminateSentinelsStingersSidesNotSafe(int, int);
string eliminateSentinelsStingersSidesSafe(int, int);


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

void printBoard(){
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;
}

int main()
{
	initBoard();
	bool turn;
	string input, output;
	cin>>turn;
	//if turn = 1, you are Sentinels and it's your turn first, base=0
	//if turn = 0, you are Scourges and it's opponent's turn first, base=4
	whoAmI=turn;

	//printBoard();

	while(1)
	{
		if(turn!=1)
		{
		    input="";
			getline(cin,input);
            if(input==""){
                getline(cin,input);
            }
			//getline(cin,input);
			//cout<<"Here: "<<input<<endl;
			makemove((int)input[0]-48, (int)input[2]-48, (int)input[4]-48, (int)input[6]-48);
			//Input from opponent
			//Use this input to make changes in your board
		}
		turn=0;	//after first iteration, (turn!=1) is always true
				//i.e. turn is always 0
        //printBoard();
        if(whoAmI==1){
            output=findBestMoveSentinels();
        }else{
            output=findBestMoveScourges();
        }
        //getline(cin,output);
        //getline(cin,output);
        makemove((int)output[0]-48, (int)output[2]-48, (int)output[4]-48, (int)output[6]-48);
        //printBoard();
		//your logic to make the next move
		//output your move string
		cout<<output<<endl;
	}
}

void makemove (int r1, int c1, int r2, int c2){
    if(abs(r2-r1)==1){
        board[r2][c2]=board[r1][c1];
        board[r1][c1]='_';
    }else if(abs(r2-r1)==2){
        board[r2][c2]=board[r1][c1];
        board[r1][c1]='_';
        if(c2==c1){
            int temp=(r1+r2)/2;
            board[temp][c1]='_';
        }
    }else if (abs(r2-r1)==0){
        if(abs(c2-c1)==1){
            board[r2][c2]=board[r1][c1];
            board[r1][c1]='_';
        }else if(abs(c2-c1)==2){
            board[r2][c2]=board[r1][c1];
            board[r1][c1]='_';
            if(r2==r1){
                int temp=(c1+c2)/2;
                board[r1][temp]='_';
            }
        }
    }
}


string findBestMoveSentinels(){
    if(whoAmI==1){
        string res="";
        for(int j=0; j<5; j++){
            if(board[3][j]=='B'){
                if(j==0){
                    if(board[4][0]=='_'){
                        return "3 0 4 0";
                    }
                    if(board[4][1]=='_'){
                        return "3 0 4 1";
                    }
                }
                if(j==4){
                    if(board[4][4]=='_'){
                        return "3 4 4 4";
                    }
                    if(board[4][3]=='_'){
                        return "3 4 4 3";
                    }
                }
                if(board[4][j]=='_'){
                    ostringstream str1;
                    str1<<"3 "<<j<<" 4 "<<j;
                    return str1.str();
                }
                if(board[4][j-1]=='_'){
                    ostringstream str1;
                    str1<<"3 "<<j<<" 4 "<<(j-1);
                    return str1.str();
                }
                if(board[4][j+1]=='_'){
                    ostringstream str1;
                    str1<<"3 "<<j<<" 4 "<<(j+1);
                    return str1.str();
                }
            }
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<5; j++){
                //To eliminate opponents first. Enemy bombers will get the priority while being eliminated.
                //Bombers get priority in attack upfront or to the safe sides.
                if(board[i][j] == 'B'){
                    //Take out bombers in front
                    if(i<=2){
                        if(board[i+1][j]=='R' && board[i+2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+2)<<" "<<j;
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                //cout<<"Here";
                if(board[i][j] == 'B'){
                    //Take out stingers on sides
                    res=eliminateScourgesStingersSidesSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                //If no bomber is in position to take anyone out, stingers will
                if(board[i][j] == 'b'){
                    //Take out bombers in front
                    if(i<=2){
                        if(board[i+1][j]=='R' && board[i+2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+2)<<" "<<j;
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'b'){
                    //Take out bombers on sides
                    res=eliminateScourgesBombersSides(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'b'){
                    //Take out stingers on sides
                    res=eliminateScourgesStingersSidesSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                    //Take out stingers in front
                    if(i<=2){
                        if(board[i+1][j]=='r' && board[i+2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+2)<<" "<<j;
                            return str1.str();
                        }
                    }
                    //Take out stingers in sides
                    res=eliminateScourgesStingersSidesNotSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }

        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'B'){
                    //Take out bombers on sides
                    res=eliminateScourgesBombersSides(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }
        for(int i= 0; i < 3; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'B'){
                    //Take out stingers in front
                    if(i<=2){
                        if(board[i+1][j]=='r' && board[i+2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+2)<<" "<<j;
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'B'){
                    //Take out stingers at sides
                    res=eliminateScourgesStingersSidesNotSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }

        for(int i = 2; i>=0; i--){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'B'){
                    //Move bomber
                    if(j==0){
                        if(board[i+1][0]=='_' && board[i+2][0]!='R' && board[i+2][0]!='r' ){
                            ostringstream str1;
                            str1<<i<<" "<<"0"<<" "<<(i+1)<<" "<<"0";
                            return str1.str();
                        }
                        if(board[i+1][1]=='_' && board[i+2][1]!='R' && board[i+2][1]!='r'){
                            ostringstream str1;
                            str1<<i<<" "<<"0"<<" "<<(i+1)<<" "<<"1";
                            return str1.str();
                        }
                    }
                    if(j==4){
                        if(board[i+1][4]=='_' && board[i+2][4]!='R' && board[i+2][4]!='r' ){
                            ostringstream str1;
                            str1<<i<<" "<<"4"<<" "<<(i+1)<<" "<<"4";
                            return str1.str();
                        }
                        if(board[i+1][3]=='_' && board[i+2][3]!='R' && board[i+2][3]!='r'){
                            ostringstream str1;
                            str1<<i<<" "<<"4"<<" "<<(i+1)<<" "<<"3";
                            return str1.str();
                        }
                    }
                    if(j!=0 && j!=4){
                        if(board[i+1][j]=='_' && board[i+2][j]!='R' && board[i+2][j]!='r'){
                            if((board[i+1][j-1]!='R' && board[i+1][j-1]!='r') || (board[i+1][j+1]=='_')){
                                if((board[i+1][j+1]=='R' && board[i+1][j+1]!='r') || (board[i+1][j-1]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<j;
                                    return str1.str();
                                }
                            }
                        }
                        if(j==1){
                            if(board[i+1][j-1]=='_' && board[i+2][j-1]!='R' && board[i+2][j-1]!='r'){
                                ostringstream str1;
                                str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                                return str1.str();
                            }
                            if(board[i+1][j+1]=='_' && board[i+2][j+1]!='R' && board[i+2][j+1]!='r'){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r') || (board[i+1][j+2]!='_')){
                                    if((board[i+1][j+2]!='R' && board[i+1][j+2]!='r') || (board[i+1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                                        return str1.str();
                                    }
                                }
                            }
                        }
                        if(j==3){
                            if(board[i+1][j+1]=='_' && board[i+2][j+1]!='R' && board[i+2][j+1]!='r'){
                                ostringstream str1;
                                str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                                return str1.str();
                            }
                            if(board[i+1][j-1]=='_' && board[i+2][j-1]!='R' && board[i+2][j-1]!='r'){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r') || (board[i+1][j-2]!='_')){
                                    if((board[i+1][j-2]!='R' && board[i+1][j-2]!='r') || (board[i+1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                                        return str1.str();
                                    }
                                }
                            }
                        }
                        if(j==2){
                            if(board[i+1][j+1]=='_' && board[i+2][j+1]!='R' && board[i+2][j+1]!='r'){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r') || (board[i+1][j+2]!='_')){
                                    if((board[i+1][j+2]!='R' && board[i+1][j+2]!='r') || (board[i+1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                                        return str1.str();
                                    }
                                }
                            }
                            if(board[i+1][j-1]=='_' && board[i+2][j-1]!='R' && board[i+2][j-1]!='r'){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r') || (board[i+1][j-2]!='_')){
                                    if((board[i+1][j-2]!='R' || board[i+1][j-2]!='r') && (board[i+1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                                        return str1.str();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int i=2; i>=0; i--){
            for(int j=0; j<5; j++){
                if(board[i][j]=='b'){
                    if(j==0){
                        if(board[i+1][j+1]=='_' && board[i+2][j+1]!='R' && board[i+2][j+1]!='r'){
                            if((board[i+1][j+2]!='R' && board[i+1][j+2]!='r')||(board[i+1][j]=='_')){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r')||(board[i+1][j+2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                                    return str1.str();
                                }
                            }
                        }
                    }
                    if(j==4){
                        if(board[i+1][j-1]=='_' && board[i+2][j-1]!='R' && board[i+2][j-1]!='r'){
                            if((board[i+1][j-2]!='R' && board[i+1][j-2]!='r')||(board[i+1][j]=='_')){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r')||(board[i+1][j-2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                                    return str1.str();
                                }
                            }
                        }
                    }
                    if(j!=0 && j!=4){
                        if(board[i+1][j+1]=='_' && board[i+2][j+1]!='R' && board[i+2][j+1]!='r'){
                            if((board[i+1][j+2]!='R' && board[i+1][j+2]!='r')||(board[i+1][j]=='_')){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r')||(board[i+1][j+2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                                    return str1.str();
                                }
                            }
                        }
                        if(board[i+1][j-1]=='_' && board[i+2][j-1]!='R' && board[i+2][j-1]!='r'){
                            if((board[i+1][j-2]!='R' && board[i+1][j-2]!='r')||(board[i+1][j]=='_')){
                                if((board[i+1][j]!='R' && board[i+1][j]!='r')||(board[i+1][j-2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                                    return str1.str();
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<5; j++){
                if(board[i][j]=='b'){
                    if(j==0){
                        if(board[i+1][j+1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                            return str1.str();
                        }
                    }
                    if(j==4){
                        if(board[i+1][j-1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                            return str1.str();
                        }
                    }
                    if(j!=0 && j!=4){
                        if(board[i+1][j+1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                            return str1.str();
                        }
                        if(board[i+1][j-1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<5; j++){
                if(board[i][j]=='B' && board[i+1][j]=='_'){
                    ostringstream str1;

                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<j;
                    return str1.str();
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=1; j<5; j++){
                if(board[i][j]=='B' && board[i+1][j-1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j-1);
                    return str1.str();
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(board[i][j]=='B' && board[i+1][j+1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                    return str1.str();
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=1; j<5; j++){
                if(board[i][j]=='B' && board[i][j-1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<i<<" "<<(j-1);
                    return str1.str();
                }
            }
        }
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(board[i][j]=='B' && board[i][j+1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<i<<" "<<(j+1);
                    return str1.str();
                }
            }
        }

    }
}

string eliminateScourgesBombersSides(int i, int j){
    if(j==2){
        if((board[i][j+1]=='R') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
        if((board[i][j-1]=='R') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    if(j<2){
        if((board[i][j+1]=='R') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
    }
    if(j>2){
        if((board[i][j-1]=='R') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    return "none";
}

string eliminateScourgesStingersSidesSafe(int i, int j){
    if(j==2){
        if((board[i][j+1]=='r') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
        if((board[i][j-1]=='r') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    return "none";
}
string eliminateScourgesStingersSidesNotSafe(int i, int j){
    if(j<2){
        if((board[i][j+1]=='r') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
    }
    if(j>2){
        if((board[i][j-1]=='r') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    return "none";
}


string eliminateSentinelsBombersSides(int i, int j){
    if(j==2){
        if((board[i][j+1]=='B') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
        if((board[i][j-1]=='B') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    if(j<2){
        if((board[i][j+1]=='B') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
    }
    if(j>2){
        if((board[i][j-1]=='B') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    return "none";
}

string eliminateSentinelsStingersSidesSafe(int i, int j){
    if(j==2){
        if((board[i][j+1]=='b') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
        if((board[i][j-1]=='b') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    return "none";
}

string eliminateSentinelsStingersSidesNotSafe(int i, int j){
    if(j<2){
        if((board[i][j+1]=='b') && board[i][j+2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j+2);
            return str1.str();
        }
    }
    if(j>2){
        if((board[i][j-1]=='b') && board[i][j-2]=='_'){
            ostringstream str1;
            str1<<i<<" "<<j<<" "<<i<<" "<<(j-2);
            return str1.str();
        }
    }
    return "none";
}






string findBestMoveScourges(){
    if(whoAmI==0){
        string res="";
        for(int j=0; j<5; j++){
            if(board[1][j]=='R'){
                if(j==0){
                    if(board[0][0]=='_'){
                        return "1 0 0 0";
                    }
                    if(board[0][1]=='_'){
                        return "1 0 0 1";
                    }
                }
                if(j==4){
                    if(board[0][4]=='_'){
                        return "1 4 0 4";
                    }
                    if(board[0][3]=='_'){
                        return "1 4 0 3";
                    }
                }
                if(board[0][j]=='_'){
                    ostringstream str1;
                    str1<<"1"<<" "<<j<<" "<<"0"<<" "<<j;
                    return str1.str();
                }
                if(board[0][j-1]=='_'){
                    ostringstream str1;
                    str1<<"1"<<" "<<j<<" "<<"0"<<" "<<(j-1);
                    return str1.str();
                }
                if(board[0][j+1]=='_'){
                    ostringstream str1;
                    str1<<"1"<<" "<<j<<" "<<"0"<<" "<<(j+1);
                    return str1.str();
                }
            }
        }
        for(int i=4; i>=2; i--){
            for(int j=0; j<5; j++){
                //To eliminate opponents first. Enemy bombers will get the priority while being eliminated.
                //Bombers get priority in attack upfront or to the safe sides.
                if(board[i][j] == 'R'){
                    //Take out bombers in front
                    if(i>=2){
                        if(board[i-1][j]=='B' && board[i-2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-2)<<" "<<j;
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'R'){
                    //Take out stingers on sides
                    res=eliminateSentinelsStingersSidesSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                //If no bomber is in position to take anyone out, stingers will
                if(board[i][j] == 'r'){
                    //Take out bombers in front
                    if(i>=2){
                        if(board[i-1][j]=='B' && board[i-2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-2)<<" "<<j;
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'r'){
                    //Take out bombers on sides
                    res=eliminateSentinelsBombersSides(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'r'){
                    //Take out stingers on sides
                    res=eliminateSentinelsStingersSidesSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                    //Take out stingers in front
                    if(i>=2){
                        if(board[i-1][j]=='b' && board[i-2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-2)<<" "<<j;
                            return str1.str();
                        }
                    }
                    //Take out stingers in sides
                    res=eliminateSentinelsStingersSidesNotSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }

        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'R'){
                    //Take out bombers on sides
                    res=eliminateSentinelsBombersSides(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }
        for(int i=4; i>=2; i--){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'R'){
                    //Take out stingers in front
                    if(i>=2){
                        if(board[i-1][j]=='b' && board[i-2][j]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-2)<<" "<<j;
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 5; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'R'){
                    //Take out stingers at sides
                    res=eliminateSentinelsStingersSidesNotSafe(i, j);
                    if(res!="none"){
                        return res;
                    }
                }
            }
        }

        for(int i = 2; i<=4; i++){
            for(int j=0; j<5; j++){
                if(board[i][j] == 'R'){
                    //Move bomber
                    if(j==0){
                        if(board[i-1][0]=='_' && board[i-2][0]!='B' && board[i-2][0]!='b' ){
                            ostringstream str1;
                            str1<<i<<" "<<"0"<<" "<<(i-1)<<" "<<"0";
                            return str1.str();
                        }
                        if(board[i-1][1]=='_' && board[i-2][1]!='B' && board[i-2][1]!='b'){
                            ostringstream str1;
                            str1<<i<<" "<<"0"<<" "<<(i-1)<<" "<<"1";
                            return str1.str();
                        }
                    }
                    if(j==4){
                        if(board[i-1][4]=='_' && board[i-2][4]!='B' && board[i-2][4]!='b' ){
                            ostringstream str1;
                            str1<<i<<" "<<"4"<<" "<<(i-1)<<" "<<"4";
                            return str1.str();
                        }
                        if(board[i-1][3]=='_' && board[i-2][3]!='B' && board[i-2][3]!='b'){
                            ostringstream str1;
                            str1<<i<<" "<<"4"<<" "<<(i-1)<<" "<<"3";
                            return str1.str();
                        }
                    }
                    if(j!=0 && j!=4){
                        if(board[i-1][j]=='_' && board[i-2][j]!='B' && board[i-2][j]!='b'){
                            if((board[i-1][j-1]=='B' || board[i-1][j-1]!='b') && (board[i-1][j+1]=='_')){
                                if((board[i-1][j+1]=='B' || board[i-1][j+1]!='b') && (board[i-1][j-1]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<j;
                                    return str1.str();
                                }
                            }
                        }
                        if(j==1){
                            if(board[i-1][j-1]=='_' && board[i-2][j-1]!='B' && board[i-2][j-1]!='b'){
                                ostringstream str1;
                                str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                                return str1.str();
                            }
                            if(board[i-1][j+1]=='_' && board[i-2][j+1]!='B' && board[i-2][j+1]!='b'){
                                if((board[i-1][j]!='B' || board[i-1][j]!='b') && (board[i-1][j+2]!='_')){
                                    if((board[i-1][j+2]!='B' || board[i-1][j+2]!='b') && (board[i-1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j+1);
                                        return str1.str();
                                    }
                                }
                            }
                        }
                        if(j==3){
                            if(board[i-1][j+1]=='_' && board[i-2][j+1]!='B' && board[i-2][j+1]!='b'){
                                ostringstream str1;
                                str1<<i<<" "<<j<<" "<<(i+1)<<" "<<(j+1);
                                return str1.str();
                            }
                            if(board[i-1][j-1]=='_' && board[i-2][j-1]!='B' && board[i-2][j-1]!='b'){
                                if((board[i-1][j]!='B' || board[i-1][j]!='b') && (board[i-1][j-2]!='_')){
                                    if((board[i-1][j-2]!='B' || board[i-1][j-2]!='b') && (board[i-1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                                        return str1.str();
                                    }
                                }
                            }
                        }
                        if(j==2){
                            if(board[i-1][j+1]=='_' && board[i-2][j+1]!='B' && board[i-2][j+1]!='b'){
                                if((board[i-1][j]!='B' || board[i-1][j]!='b') && (board[i-1][j+2]!='_')){
                                    if((board[i-1][j+2]!='B' || board[i-1][j+2]!='b') && (board[i-1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j+1);
                                        return str1.str();
                                    }
                                }
                            }
                            if(board[i-1][j-1]=='_' && board[i-2][j-1]!='B' && board[i-2][j-1]!='r'){
                                if((board[i-1][j]!='B' || board[i-1][j]!='b') && (board[i-1][j-2]!='_')){
                                    if((board[i-1][j-2]!='B' || board[i-1][j-2]!='b') && (board[i-1][j]!='_')){
                                        ostringstream str1;
                                        str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                                        return str1.str();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int i=2; i<=4; i++){
            for(int j=0; j<5; j++){
                if(board[i][j]=='r'){
                    if(j==0){
                        if(board[i-1][j+1]=='_' && board[i-2][j+1]!='B' && board[i-2][j+1]!='b'){
                            if((board[i-1][j+2]!='B' && board[i-1][j+2]!='b')||(board[i-1][j]=='_')){
                                if((board[i-1][j]!='B' && board[i-1][j]!='b')||(board[i-1][j+2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j+1);
                                    return str1.str();
                                }
                            }
                        }
                    }
                    if(j==4){
                        if(board[i-1][j-1]=='_' && board[i-2][j-1]!='B' && board[i-2][j-1]!='b'){
                            if((board[i-1][j-2]!='B' && board[i-1][j-2]!='b')||(board[i-1][j]=='_')){
                                if((board[i-1][j]!='B' && board[i-1][j]!='b')||(board[i-1][j-2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                                    return str1.str();
                                }
                            }
                        }
                    }
                    if(j!=0 && j!=4){
                        if(board[i-1][j+1]=='_' && board[i-2][j+1]!='B' && board[i-2][j+1]!='b'){
                            if((board[i-1][j+2]!='B' && board[i-1][j+2]!='b')||(board[i-1][j]=='_')){
                                if((board[i-1][j]!='B' && board[i-1][j]!='b')||(board[i-1][j+2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j+1);
                                    return str1.str();
                                }
                            }
                        }
                        if(board[i-1][j-1]=='_' && board[i-2][j-1]!='B' && board[i-2][j-1]!='b'){
                            if((board[i-1][j-2]!='B' && board[i-1][j-2]!='b')||(board[i-1][j]=='_')){
                                if((board[i-1][j]!='B' && board[i-1][j]!='b')||(board[i-1][j-2]=='_')){
                                    ostringstream str1;
                                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                                    return str1.str();
                                }
                            }
                        }
                    }
                }
            }
        }
        for(int i=1; i<=4; i++){
            for(int j=0; j<5; j++){
                if(board[i][j]=='r'){
                    if(j==0){
                        if(board[i-1][j+1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j+1);
                            return str1.str();
                        }
                    }
                    if(j==4){
                        if(board[i-1][j-1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                            return str1.str();
                        }
                    }
                    if(j!=0 && j!=4){
                        if(board[i-1][j+1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j+1);
                            return str1.str();
                        }
                        if(board[i-1][j-1]=='_'){
                            ostringstream str1;
                            str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                            return str1.str();
                        }
                    }
                }
            }
        }
        for(int i=1; i<=4; i++){
            for(int j=0; j<5; j++){
                if(board[i][j]=='R' && board[i-1][j]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<j;
                    return str1.str();
                }
            }
        }
        for(int i=1; i<=4; i++){
            for(int j=1; j<5; j++){
                if(board[i][j]=='R' && board[i-1][j-1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j-1);
                    return str1.str();
                }
            }
        }
        for(int i=1; i<=4; i++){
            for(int j=0; j<4; j++){
                if(board[i][j]=='R' && board[i-1][j+1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<(i-1)<<" "<<(j+1);
                    return str1.str();
                }
            }
        }
        for(int i=0; i<=4; i++){
            for(int j=1; j<5; j++){
                if(board[i][j]=='R' && board[i][j-1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<i<<" "<<(j-1);
                    return str1.str();
                }
            }
        }
        for(int i=0; i<=4; i++){
            for(int j=0; j<4; j++){
                if(board[i][j]=='R' && board[i][j+1]=='_'){
                    ostringstream str1;
                    str1<<i<<" "<<j<<" "<<i<<" "<<(j+1);
                    return str1.str();
                }
            }
        }

    }

}

/*
 * x = {"x1 y1 x2 y2"}
 * y = {"x1 y1 x1 y2"}
 *
 * Your code outputs a string of length 7 containing 4 characters each
 * separated by a space, where x1 & y1 are respective row and column
 * of your piece's initial position and x2 & y2 are respective row and
 * column of your piece's final position.
 *
 * Each of x1,y1,x2,y2 must be >=0 and <5.
 *
 * Consider "B"-> Sentinels' bombers "b"-> Sentinels' stingers (Blue)
 * 			"R"-> Scourges' bombers "r"-> Scourges' stingers   (Red)
 * 			'_'-> Empty space
 *
 * Board representation:
 *
 * B B B B B
 * b b b b b
 * _ _ _ _ _
 * r r r r r
 * R R R R R
 *
 * Note:- The program will be terminated automatically when either player wins.
 */

