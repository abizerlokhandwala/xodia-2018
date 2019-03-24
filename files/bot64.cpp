#include<bits/stdc++.h>
using namespace std;
#define ll int
#define ull unsigned long long
#define ld long double
#define pi pair<ll,ll>
#define pii vector<pair<ll,ll> >
#define v vector
#define vi vector<ll>
#define f(a,i,n) for(int i=a;i<n;i++)
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define MAX 1000001
#define max_dept 6
#define all(x) x.begin(),x.end()
const ll inf=(ll) 1e18;

//Probable changes in the heuristics:
/*
1. Increase weight for sides,they are more safer.
2. Decrease weights of third last row, as getting to the second last row is valuable.
*/
 
// ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
// ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
// ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
// int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
// ll spf[MAX+1];
// void sieve()//complexity = approx 3*10^6
// {
//     f(1,i,MAX) {spf[i]=i;} 
//     for(ll i=2;i<MAX;i+=2){spf[i]=2;}
//     for(ll i=3;i<MAX;i+=2)
//     {
//         if(spf[i]==i) //if i is prime mark its multiples with spf as i
//         {
//             for(ll j=i*i;j<MAX;j+=i)
//             {
//                 spf[j]=min(i,(ll)spf[j]);
//             }
//         }
//     }
// }
/*
In the game_state and local_game_state matrix:
1 denotes airplane for player 1
2 denotes bomber for player 1
3 denotes airplane for player 2
4 denotes bomber for player 2
0 denotes a empty cell

Printer

*/
v<vi>game_state; //global game state
v<vi>weight_matrix_bomber,weight_matrix_airplane; //store the weights for static evaluation
ll which_player,not_which_player,sign1,sign2;
pair<pi,pi> best_move;
ll limiting_dept;
clock_t start,end;

void print(v<vi>game_state)
{
	f(0,i,5)
	{
		f(0,j,5) cout<<game_state[i][j]<<" ";cout<<endl;
	}
}

void print_moves(v<pair<pi,pi> >moves)
{
	f(0,i,moves.size())
	{
		cout<<moves[i].first.first<<" "<<moves[i].first.second<<" "<<moves[i].second.first<<" "<<moves[i].second.second<<endl;
	}
}


void init()
{
	game_state = v<vi>(5,vi(5,0));
	weight_matrix_bomber = v<vi>(5,vi(5,0));
	weight_matrix_airplane = v<vi>(5,vi(5,0));
	f(0,i,5) {game_state[0][i]=2;game_state[1][i]=1;game_state[3][i]=3;game_state[4][i]=4;}
	f(0,i,5) {weight_matrix_bomber[4][i]=MOD;}
	f(0,i,5) {weight_matrix_bomber[3][i]=12;weight_matrix_airplane[3][i]=2;} 
	weight_matrix_bomber[3][0]=10;
	weight_matrix_bomber[3][4]=10;
	weight_matrix_airplane[3][0]=1;
	weight_matrix_airplane[3][4]=1;
	f(0,i,5) {weight_matrix_bomber[2][i]=9;weight_matrix_airplane[2][i]=3;}
	weight_matrix_bomber[2][0]=75;
	weight_matrix_bomber[2][4]=75;
	weight_matrix_airplane[2][0]=2;
	weight_matrix_airplane[2][4]=2;
	f(0,i,5) {weight_matrix_bomber[1][i]=5;weight_matrix_airplane[1][i]=3;}
	weight_matrix_bomber[1][0]=4;
	weight_matrix_bomber[1][4]=4;
	weight_matrix_airplane[1][0]=2;
	weight_matrix_airplane[1][4]=2;
	f(0,i,5) {weight_matrix_bomber[0][i]=2;}
	//weight_matrix_airplane = v<vi>(5,vi(5,0));
	f(0,i,5) f(0,j,5) if(weight_matrix_bomber[i][j]<15) weight_matrix_bomber[i][j]*=10;
	f(0,i,5) f(0,j,5) weight_matrix_airplane[i][j]*=10;
	f(0,i,5)
	{
		f(0,j,5) cout<<weight_matrix_airplane[i][j]<<" ";cout<<endl;
	}
	cout<<endl;
	f(0,i,5)
	{
		f(0,j,5) cout<<weight_matrix_bomber[i][j]<<" ";cout<<endl;
	}
}

ll count_bomber(v<vi>local_game_state,ll sign)
{
	ll valid1,cnt=0;
	if(sign==1) valid1=2;
	else valid1=4;
	f(0,i,5)
	{
		f(0,j,5) if(local_game_state[i][j]==valid1) cnt++;
	}
	return cnt;
}

ll count_planes(v<vi>local_game_state,ll sign)
{
	ll valid1,cnt=0;
	if(sign==1) valid1=1;
	else valid1=3;
	f(0,i,5)
	{
		f(0,j,5) if(local_game_state[i][j]==valid1) cnt++;
	}
	return cnt;
}

bool isvalid(ll x,ll y)
{
	if(x<0 or x>4 or y<0 or y>4) return false;
	return true;
}

v<pair<pi,pi> > move_generator(v<vi>local_game_state,ll sign) // sign 1 for player 1(Blue) -1 for player 2(Red)
{
	ll valid1,valid2,p1,p2;
	if(sign>0) {valid1=3;valid2=4;p1=1;p2=2;}
	else {valid1=1;valid2=2;p1=3;p2=4;}
	v<pair<pi,pi> >moves,moves1,moves3;
	//x is row
	//y is col
	//first is x before move	
	//second is y before move
	//third is x after move
	//fourth is y after move
	f(0,i,5)
	{
		f(0,j,5)
		{
			if(local_game_state[i][j]==0) continue;
			if(local_game_state[i][j]==p1)
			{
				//airplane

				if(isvalid(i+1*sign,j-1) and local_game_state[i+1*sign][j-1]==0)
					moves.pb({{i,j},{i+1*sign,j-1}});

				if(isvalid(i+1*sign,j+1) and local_game_state[i+1*sign][j+1]==0)
					moves.pb({{i,j},{i+1*sign,j+1}});
			}
			else if(local_game_state[i][j]==p2)
			{
				//bomber
				if(isvalid(i,j-1) and local_game_state[i][j-1]==0)
					moves.pb({{i,j},{i,j-1}});

				if(isvalid(i,j+1) and local_game_state[i][j+1]==0)
					moves.pb({{i,j},{i,j+1}});

				if(isvalid(i+1*sign,j) and local_game_state[i+1*sign][j]==0)
				{
					if(i+1*sign==0 or i+1*sign==4)
						moves3.pb({{i,j},{i+1*sign,j}});
					else 
						moves.pb({{i,j},{i+1*sign,j}});
				}

				if(isvalid(i+1*sign,j-1) and local_game_state[i+1*sign][j-1]==0)
				{
					if(i+1*sign==0 or i+1*sign==4)
						moves3.pb({{i,j},{i+1*sign,j-1}});
					else
						moves.pb({{i,j},{i+1*sign,j-1}});
				}

				if(isvalid(i+1*sign,j+1) and local_game_state[i+1*sign][j+1]==0)
				{
					if(i+1*sign==0 or i+1*sign==4)
						moves3.pb({{i,j},{i+1*sign,j+1}});
					else
						moves.pb({{i,j},{i+1*sign,j+1}});
				}
			}
			//leftkill
			if(isvalid(i,j-2) and (local_game_state[i][j]==p1 or local_game_state[i][j]==p2) and local_game_state[i][j-2]==0 and (local_game_state[i][j-1]==valid1 or local_game_state[i][j-1]==valid2) and i!=0 and i!=4)
				moves1.pb({{i,j},{i,j-2}});

			//rightkill
			if(isvalid(i,j+2) and (local_game_state[i][j]==p1 or local_game_state[i][j]==p2) and local_game_state[i][j+2]==0 and (local_game_state[i][j+1]==valid1 or local_game_state[i][j+1]==valid2) and i!=0 and i!=4)
				moves1.pb({{i,j},{i,j+2}});

			//aagey ka kill
			if(isvalid(i+2*sign,j) and (local_game_state[i][j]==p1 or local_game_state[i][j]==p2) and local_game_state[i+2*sign][j]==0 and (local_game_state[i+1*sign][j]==valid1 or local_game_state[i+1*sign][j]==valid2))
			{
				if(i+2*sign==0 or i+2*sign==4)
					moves3.pb({{i,j},{i+2*sign,j}});
				else 
					moves1.pb({{i,j},{i+2*sign,j}});
			}
		}
		
	}
	for(auto it:moves1) moves3.pb(it);
	for(auto it:moves) moves3.pb(it);
	return moves3;
}

ll evaluate_state(v<vi>local_game_state,ll player)
{
	ll weight = 0,sign1,sign2;

	if(player==1) {sign1=1;sign2=-1;}
	else {sign1=-1;sign2=1;}

	f(0,i,5)
	{
		f(0,j,5)
		{
			if(local_game_state[i][j]==1)
			{
				weight+=(sign1*weight_matrix_airplane[i][j]);
			}
			else if(local_game_state[i][j]==2)
			{
				weight+=(sign1*weight_matrix_bomber[i][j]);
			}
			else if(local_game_state[i][j]==3)
			{
				weight+=(sign2*weight_matrix_airplane[4-i][j]);
			}
			else if(local_game_state[i][j]==4)
			{
				weight+=(sign2*weight_matrix_bomber[4-i][j]);
			}
		}
	}
	//ll eval = weight + 5*sign1*count_bomber(local_game_state,1)+5*sign2*count_bomber(local_game_state,-1)+2*sign1*count_planes(local_game_state,1)+2*sign2*count_planes(local_game_state,-1);
	return weight+20*sign1*(count_bomber(local_game_state,1))+20*sign2*(count_bomber(local_game_state,-1));
	//return eval;
}

void make_move_changes(v<vi>&local_game_state,ll i1,ll j1,ll i2,ll j2)
{
	ll val = local_game_state[i1][j1];
	local_game_state[i1][j1] = 0;
	local_game_state[i2][j2] = val;
	if(abs(i2-i1)>1 and j1==j2)
	{
		//vertical jump
		local_game_state[(i1+i2)/2][j1] = 0;
	}
	if(abs(j2-j1)>1 and i1==i2)
	{
		//horizontal jump
		local_game_state[i1][(j1+j2)/2] = 0;
	}
}

bool is_end_game(v<vi>local_game_state)
{
	f(0,i,5)
	{
		if(local_game_state[0][i]==4) return true;
		if(local_game_state[4][i]==2) return true;
	}
	return false;
}

ll game_play(v<vi>local_game_state,ll dept,ll motive,ll alpha,ll beta)
{
	if(is_end_game(local_game_state) and motive) //opponent winning
	{
		return -inf+dept;
	}
	if(is_end_game(local_game_state) and !motive)
	{
		return inf-dept;
	}
	//motive = 1 if maximizing the score is the aim
	//else motive = 0 if minimizing the score is the aim
	if(dept>=max_dept or is_end_game(local_game_state))
		return evaluate_state(local_game_state,which_player);
	if(motive)
	{
		//maximizing is the aim
		ll best = -inf;
		v<pair<pi,pi > >possible_moves = move_generator(local_game_state,sign1); //idhar changes karney hay
		for(auto it:possible_moves)
		{
			v<vi>duplicate = local_game_state;
			make_move_changes(duplicate,it.first.first,it.first.second,it.second.first,it.second.second);
			ll child_val = game_play(duplicate,dept+1,!motive,alpha,beta);
			if(best < child_val)
			{
				best = child_val;
				if(dept==0)
				{
					best_move = it;
				}
			}
			alpha = max(alpha , best);
			if(beta <= alpha)
				break;
		}
		return alpha;
	}
	else
	{
		//minimizing is the aim
		ll best = inf;
		v<pair<pi,pi> >possible_moves = move_generator(local_game_state,sign2); //idhar changes karney hay
		for(auto it:possible_moves)
		{
			v<vi>duplicate = local_game_state;
			make_move_changes(duplicate,it.first.first,it.first.second,it.second.first,it.second.second);
			ll child_val = game_play(duplicate,dept+1,!motive,alpha,beta);
			if(best > child_val)
			{
				best = child_val;
			}
			beta = min(beta , best);
			if(beta <= alpha)
				break;
		}
		return beta;
	}
}

int main()
{
	ll ip1,jp1,ip2,jp2;
	init();

	cin>>which_player;
	if(which_player==1) {not_which_player=2;sign1=1;sign2=-1;}
	else {not_which_player=1;sign1=-1;sign2=1;} 
	if(which_player!=1)
	{
		cin>>ip1>>jp1>>ip2>>jp2;
		make_move_changes(game_state,ip1,jp1,ip2,jp2);
	}
	while(1)
	{
		game_play(game_state,0,1,-inf,inf);
		cout<<best_move.first.first<<" "<<best_move.first.second<<" "<<best_move.second.first<<" "<<best_move.second.second<<endl;
		make_move_changes(game_state,best_move.first.first,best_move.first.second,best_move.second.first,best_move.second.second);
		//print(game_state);
		cin>>ip1>>jp1>>ip2>>jp2;
		make_move_changes(game_state,ip1,jp1,ip2,jp2);
		//print(game_state);
	}
} 	