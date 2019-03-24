#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define MOD 1000000007
#define MOD9 1000000009
#define pi 3.1415926535
#define ms(s, n) memset(s, n, sizeof(s))
#define prec(n) fixed<<setprecision(n)
#define eps 0.000001
#define all(v) v.begin(), v.end()
#define bolt ios::sync_with_stdio(0)
#define light cin.tie(0);cout.tie(0)
#define forr(i,p,n) for(ll i=p;i<n;i++)
#define MAXN 10000003
#define INF int(1e6)
typedef int ll;
using namespace std;
ll mult(ll a,ll b, ll p=MOD){return ((a%p)*(b%p))%p;}
ll add(ll a, ll b, ll p=MOD){return (a%p + b%p)%p;}
ll fpow(ll n, ll k, ll p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n%p; n = n * n%p;} return r;}
ll inv(ll a, ll p = MOD) {return fpow(a, p - 2, p);}

ll bombr[] = {0,1,1,1,0};
ll bombc[] = {-1,-1,0,1,1};
ll str[] = {1,1};
ll stc[] = {-1,1};
ll attackr[] = {0,0,2};
ll attackc[] = {-2,2,0};
ll maxdepth = 6;
ll all_out=0;
ll myb=0;
ll nyb=0;

//old (2 wins, 2 draws, 1w1d)
/*
ll scbpb[][5]={{3,3,3,3,3},{3,3,3,3,3},{4,4,4,4,4},{4,4,4,4,4},{INF,INF,INF,INF,INF}};
ll scbnb[][5]={{INF,INF,INF,INF,INF},{5,6,6,6,5},{4,4,4,4,4},{3,3,3,3,3},{2,2,2,2,2}};
ll scbps[][5]={{0,0,0,0,0},{1,1,1,1,1},{2,1,1,1,2},{2,1,1,1,2},{0,0,0,0,0}};
ll scbns[][5]={{0,0,0,0,0},{2,1,1,1,2},{2,1,1,1,2},{1,1,1,1,1},{0,0,0,0,0}};

ll scrpb[][5]={{INF,INF,INF,INF,INF},{4,4,4,4,4},{4,4,4,4,4},{3,3,3,3,3},{3,3,3,3,3}};
ll scrnb[][5]={{2,2,2,2,2},{3,3,3,3,3},{4,4,4,4,4},{5,6,6,6,5},{INF,INF,INF,INF,INF}};
ll scrps[][5]={{0,0,0,0,0},{2,1,1,1,2},{2,1,1,1,2},{1,1,1,1,1},{0,0,0,0,0}};
ll scrns[][5]={{0,0,0,0,0},{1,1,1,1,1},{2,1,1,1,2},{2,1,1,1,2},{0,0,0,0,0}};
*/

// all draws, 2w
ll scbpb[][5]={{myb,myb,myb,myb,myb},{myb,myb,myb,myb,myb},{myb+3,myb+1,myb+1,myb+1,myb+3},{myb+1,myb+3,myb+3,myb+3,myb+1},{INF,INF,INF,INF,INF}};
ll scbnb[][5]={{INF,INF,INF,INF,INF},{nyb+2,nyb+3,nyb+3,nyb+3,nyb+2},{nyb+3,nyb+2,nyb+2,nyb+2,nyb+3},{nyb,nyb,nyb,nyb,nyb},{nyb-1,nyb-1,nyb-1,nyb-1,nyb-1}};
ll scbps[][5]={{0,0,0,0,0},{1,1,1,1,1},{3,2,2,2,3},{1,1,1,1,1},{0,0,0,0,0}};
ll scbns[][5]={{0,0,0,0,0},{1,1,1,1,1},{3,2,2,2,3},{1,1,1,1,1},{0,0,0,0,0}};

ll scrpb[][5]={{INF,INF,INF,INF,INF},{myb+1,myb+3,myb+3,myb+3,myb+1},{myb+3,myb+1,myb+1,myb+1,myb+3},{myb,myb,myb,myb,myb},{myb,myb,myb,myb,myb}};
ll scrnb[][5]={{nyb-1,nyb-1,nyb-1,nyb-1,nyb-1},{nyb,nyb,nyb,nyb,nyb},{nyb+3,nyb+2,nyb+2,nyb+2,nyb+3},{nyb+2,nyb+3,nyb+3,nyb+3,nyb+2},{INF,INF,INF,INF,INF}};
ll scrps[][5]={{0,0,0,0,0},{1,1,1,1,1},{3,2,2,2,3},{1,1,1,1,1},{0,0,0,0,0}};
ll scrns[][5]={{0,0,0,0,0},{1,1,1,1,1},{3,2,2,2,3},{1,1,1,1,1},{0,0,0,0,0}};


bool whoAmI;	//if whoAmI = 1, you are Sentinels
				//if whoAmI = 0, you are Scourges
void makeMove(char board[5][5],vector<ll>mv){
	int r1=mv[0];
	int c1=mv[1];
	int r2=mv[2];
	int c2=mv[3];
	if(board[r1][c1]=='B'){
		if(abs(r1-r2)==2 || abs(c1-c2)==2){
			if(r1==r2){
				board[r1][c1]='_';
				board[r1][min(c1,c2)+1] = '_';
				board[r2][c2]='B';
			}else if(c1==c2){
				board[r1][c1] = '_';
				board[min(r1,r2)+1][c1] = '_';
				board[r2][c2]='B';
			}
		}else{
			board[r1][c1]='_';
			board[r2][c2]='B';
		}
	}else if(board[r1][c1]=='b'){
		if(r1!=r2 && c1!=c2){
			board[r1][c1]='_';
			board[r2][c2]='b';
		}else if(r1==r2){
			board[r1][c1]='_';
			board[r1][min(c1,c2)+1] = '_';
			board[r2][c2]='b';
		}else if(c1==c2){
			board[r1][c1]='_';
			board[min(r1,r2)+1][c1] = '_';
			board[r2][c2]='b';
		}
	}else if(board[r1][c1]=='R'){
		if(abs(r1-r2)==2 || abs(c1-c2)==2){
			if(r1==r2){
				board[r1][c1]='_';
				board[r1][min(c1,c2)+1] = '_';
				board[r2][c2]='R';
			}else if(c1==c2){
				board[r1][c1] = '_';
				board[min(r1,r2)+1][c1] = '_';
				board[r2][c2]='R';
			}
		}else{
			board[r1][c1]='_';
			board[r2][c2]='R';
		}
	}else if(board[r1][c1]=='r'){
		if(r1!=r2 && c1!=c2){
			board[r1][c1]='_';
			board[r2][c2]='r';
		}else if(r1==r2){
			board[r1][c1]='_';
			board[r1][min(c1,c2)+1] = '_';
			board[r2][c2]='r';
		}else if(c1==c2){
			board[r1][c1]='_';
			board[min(r1,r2)+1][c1] = '_';
			board[r2][c2]='r';
		}
	}
}

void initBoard (char board[5][5])		//Function to initialize the Board
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

void printBoard(char board[5][5]){
	for(ll i=0;i<5;i++){
		for(ll j=0;j<5;j++){
			cout<<board[i][j];
		}
		cout<<"\n";
	}
}

ll issafe(ll x,ll y,char board[5][5]){
	if(x>=0 && x<5 && y>=0 && y<5 && board[x][y]=='_'){
		return 1;
	}else return 0;
}

ll issafeat(ll x1,ll y1,ll x2,ll y2,char board[5][5]){
	if((x1==x2 && x1==0) || (x1==x2 && x1==4))
		return 0;
  	if(x2>=0 && x2<5 && y2>=0 && y2<5 && board[x2][y2]=='_'){
		ll avgr=(x1+x2)/2;
		ll avgc=(y1+y2)/2;
		if(tolower(board[avgr][avgc])!=tolower(board[x1][y1]) && board[avgr][avgc]!='_')
			return 1;
		else return 0;
	}else return 0;
}

vector<ll>getValid(char board[5][5],ll mytyp){
	char chk;
	vector<ll>v;
	ll com;
	if(mytyp==1){
		chk='b';
		com=1;
		forr(i,0,5){
			forr(j,0,5){
				if(tolower(board[i][j])==chk){
					if(board[i][j]==chk){//lower alpha
						forr(k,0,2){
							if(issafe(i+com*str[k],j+com*stc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*str[k])+(j+com*stc[k]));
								v.pb(mv);
							}
						}
						forr(k,0,3){
							if(issafeat(i,j,i+com*attackr[k],j+com*attackc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*attackr[k])+(j+com*attackc[k]));
								v.pb(mv);
							}
						}
					}else{//upper alpha
						forr(k,0,5){
							if(issafe(i+com*bombr[k],j+com*bombc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*bombr[k])+(j+com*bombc[k]));
								v.pb(mv);
							}
						}
						forr(k,0,3){
							if(issafeat(i,j,i+com*attackr[k],j+com*attackc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*attackr[k])+(j+com*attackc[k]));
								v.pb(mv);
							}
						}
					}
				}
			}
		}
		return v;
	}else{
		chk='r';
		com=-1;
		forr(i,0,5){
			forr(j,0,5){
				if(tolower(board[i][j])==chk){
					if(board[i][j]==chk){//lower alpha
						forr(k,0,2){
							if(issafe(i+com*str[k],j+com*stc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*str[k])+(j+com*stc[k]));
								v.pb(mv);
							}
						}
						forr(k,0,3){
							if(issafeat(i,j,i+com*attackr[k],j+com*attackc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*attackr[k])+(j+com*attackc[k]));
								v.pb(mv);
							}
						}
					}else{//upper alpha
						forr(k,0,5){
							if(issafe(i+com*bombr[k],j+com*bombc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*bombr[k])+(j+com*bombc[k]));
								v.pb(mv);
							}
						}
						forr(k,0,3){
							if(issafeat(i,j,i+com*attackr[k],j+com*attackc[k],board)){
								ll mv=5*5*(5*i+j)+(5*(i+com*attackr[k])+(j+com*attackc[k]));
								v.pb(mv);
							}
						}
					}
				}
			}
		}
		return v;
	}
}

vector<ll>convertmove(ll mv){
	vector<ll>v(4);
	v[0] = (mv/25)/5;//r1
	v[1] = (mv/25)%5;//c1
	v[2] = (mv%25)/5;//r2
	v[3] = (mv%25)%5;//c2
	return v;
}

ll calcscore(char board[5][5],ll mytyp){
	char chk;
	ll score=0;
	ll num_bomb=0;
	ll num_opp_bomb=0;
	if(mytyp==1){
		chk='b';
		forr(i,0,5){
			forr(j,0,5){
				if(tolower(board[i][j])==chk){
					if(board[i][j]==chk){//smaller
						score+=scbps[i][j];
					}else{//bigger
						score+=scbpb[i][j];
                        num_bomb++;
					}
				}else if(tolower(board[i][j])=='r'){
					if(board[i][j]=='r'){//smaller
						score-=scbns[i][j];
					}else{
						score-=scbnb[i][j];
						num_opp_bomb++;
					}
				}
				// cout<<i<<" "<<j<<" "<<score<<"\n";
			}
		}
	}else{
		chk='r';
		forr(i,0,5){
			forr(j,0,5){
				if(tolower(board[i][j])==chk){
					if(board[i][j]==chk){//smaller
						score+=scrps[i][j];
					}else{//bigger
						score+=scrpb[i][j];
						num_bomb++;
					}
				}else if(tolower(board[i][j])=='b'){
					if(board[i][j]=='b'){//smaller
						score-=scrns[i][j];
					}else{
						score-=scrnb[i][j];
						num_opp_bomb++;
					}
				}
			}
		}
	}
	if(num_bomb==0)
        return -INF;
    if(num_opp_bomb==0)
        return INF;

	return score;
}

pair<ll,ll>bombfunc(char board[5][5], ll mytyp){
    char chk,nchk;
	ll num_bomb=0;
	ll num_opp_bomb=0;
	if(mytyp==1){
		chk='B';
		nchk='R';
	}else{
	    chk='R';
	    nchk='B';
	}
	forr(i,0,5){
        forr(j,0,5){
            if(board[i][j]==chk){
                num_bomb++;
            }else if(board[i][j]==nchk){
                num_opp_bomb++;
            }
        }
    }
    return mp(num_bomb,num_opp_bomb);
}

pair<ll,ll> rec(char board[5][5], ll mytyp, ll whoAmI, ll dpt, ll alpha, ll beta){
	vector<ll>v=getValid(board,mytyp^whoAmI);
	if(v.size()==0){
		return mp(calcscore(board,whoAmI),-1);
	}
	ll bestmv=-1;
	ll best;
	if(mytyp==0){
		best = INT_MIN;
		for(auto e:v){
			char tempb[5][5];
			forr(i,0,5){
				forr(j,0,5){
					tempb[i][j]=board[i][j];
				}
			}
			makeMove(tempb,convertmove(e));
			pair<ll,ll>num = bombfunc(tempb,whoAmI);
			myb=3+5-num.fi;
			nyb=3+5-num.se;
			ll curr_sc = calcscore(tempb,whoAmI);
			if(curr_sc>=100000){
				best=curr_sc;
				bestmv=e;
				break;
			}
			ll sc;
			if(dpt==1){
				sc = calcscore(tempb,whoAmI);
			}else sc = rec(tempb,mytyp^1,whoAmI,dpt-1,alpha,beta).fi;
			// printBoard(tempb);
			// cout<<"Score: "<<sc<<" Depth: "<<dpt<<" MAX\n";
			if(sc>best){
				best=sc;
				bestmv=e;
			}
			alpha = max(alpha,best);
			if(beta<=alpha){
				break;
			}
		}
		return mp(best,bestmv);
	}else{
		best = INT_MAX;
		for(auto e:v){
			char tempb[5][5];
			forr(i,0,5){
				forr(j,0,5){
					tempb[i][j]=board[i][j];
				}
			}
			makeMove(tempb,convertmove(e));
			pair<ll,ll>num = bombfunc(tempb,whoAmI);
			myb=3+5-num.fi;
			nyb=3+5-num.se;
			ll curr_sc = calcscore(tempb,whoAmI);
			if(curr_sc<=-100000){
				best=curr_sc;
				bestmv=e;
				break;
			}
			ll sc;
			if(dpt==1){
				sc = calcscore(tempb,whoAmI);
			}else sc = rec(tempb,mytyp^1,whoAmI,dpt-1,alpha,beta).fi;
			// printBoard(tempb);
			// cout<<"Score: "<<sc<<" Depth: "<<dpt<<" MIN\n";
			if(sc<best){
				best=sc;
				bestmv=e;
			}
			beta = min(beta,best);
			if(beta<=alpha){
				break;
			}
		}
		return mp(best,bestmv);
	}
}

int main()
{
	bolt;
	char board[5][5];	//Your board
	initBoard(board);
	bool turn;
	string input, output;
	cin>>turn;
	cin.ignore();
	//if turn = 1, you are Sentinels and it's your turn first
	//if turn = 0, you are Scourges and it's opponent's turn first
	whoAmI=turn;
	while(1)
	{
		// printBoard(board);
		if(turn!=1)
		{
			getline(cin,input);
			vector<ll>mv{input[0]-'0', input[2]-'0', input[4]-'0', input[6]-'0'};
			makeMove(board,mv);
		}
		turn=0;	//after first iteration, (turn!=1) is always true
				//i.e. turn is always 0
		ll bstmv=rec(board,turn,whoAmI,maxdepth,INT_MIN,INT_MAX).se;
		vector<ll>vv=convertmove(bstmv);
		makeMove(board,vv);
		string output;
		forr(i,0,(ll)vv.size()){
			output.pb(vv[i]+'0');
			if(i!=(ll)vv.size()-1)
				output.pb(' ');
		}
		//your logic to make the next move
		//output your move string
		cout<<output<<endl;
	}
}
/*
 * x = {"r1 c1 r2 c2"}
 * y = {"r1 c1 r2 c2"}
 *
 * Your code outputs a string of length 7 containing 4 characters each
 * separated by a space, where r1 & c1 are respective row and column
 * of your piece's initial position and r2 & c2 are respective row and
 * column of your piece's final position.
 *
 * Each of r1,c1,r2,c2 must be >=0 and <5.
 *
 * Consider "B"-> Sentinels' bombers "b"-> Sentinels' stingers (Blue)
 * 			"R"-> Scourges' bombers "r"-> Scourges' stingers   (Red)
 * 			"_"-> Empty space
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
