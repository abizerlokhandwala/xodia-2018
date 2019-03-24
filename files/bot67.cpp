
#include <iostream>
#include <string>
#include <vector>
#define INF 99999
#define MAX_DEPTH 6

int stingerWeights[5][5], bomberWeights[5][5], opponentStingerWeights[5][5], opponentBomberWeights[5][5];

class Board // class for representing the board
{
public:
    char board[5][5];
    Board()
    {
        for(int i = 0; i < 5; i++)
        {
            board[0][i] = 'B';
            board[1][i] = 'b';
            board[2][i] = '_';
            board[3][i] = 'r';
            board[4][i] = 'R';
        }
    }
};

class Move	// class for denoting a move
{
public:
	int x1, y1, x2, y2, capture;
    char capturedPiece;
    Move()
    {
        this->x1 = -1;
        this->y1 = -1;
        this->x2 = -1;
        this->y2 = -1;
        this->capture = 0;
        this->capturedPiece = '_';
    }
	Move(int x1, int y1, int x2, int y2, int capture = 0, char capturedPiece = '_')
	{
		this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->capture = capture;
        this->capturedPiece = capturedPiece;
	}
};

// capture = 0 -> Not a capture
// capture = 1 -> left side horizontal capture
// capture = 2 -> right side horizontal capture
// capture = 3 -> vertical capture
// NOTE: Horizontal captures are not allowed on rows 0 and 4
bool moveValidator(Board *brd, Move move)
{     
    if(move.x2 < 0 || move.x2 > 4 || move.y2 < 0 || move.y2 > 4) // move is out of bounds
        return false;
    if(brd->board[move.x2][move.y2] != '_') // (x2, y2) is already occupied
        return false;
    if((move.capture == 1 || move.capture == 2) && (move.x1 == 0 || move.x1 == 4)) // horizontal captures not allowed in rows 0 and 4
        return false;
    char myFirstToken = brd->board[move.x1][move.y1];
    char mySecondToken;
    int multiplier = 1;
    if(myFirstToken == 'b')
        mySecondToken = 'B';
    else if(myFirstToken == 'B')
        mySecondToken = 'b';
    else if(myFirstToken == 'r')
    {
        mySecondToken = 'R';
        multiplier = -1;
    }
    else
    {
        mySecondToken = 'r';
        multiplier = -1;
    }   
    if(move.capture == 1 && (brd->board[move.x1][move.y1 - 1] == myFirstToken || brd->board[move.x1][move.y1 - 1] == mySecondToken || brd->board[move.x1][move.y1 - 1] == '_')) // Left side horizontal capture
        return false;
    else if(move.capture == 2 && (brd->board[move.x1][move.y1 + 1] == myFirstToken || brd->board[move.x1][move.y1 + 1] == mySecondToken || brd->board[move.x1][move.y1 + 1] == '_')) // Right side horizontal capture
        return false;
    else if(move.capture == 3 && (brd->board[move.x1 + (multiplier * 1)][move.y1] == myFirstToken || brd->board[move.x1 + (multiplier * 1)][move.y1] == mySecondToken || brd->board[move.x1 + (multiplier * 1)][move.y1] == '_')) // Vertical elimination
        return false;
    return true;
}

std::vector<Move> moveGenerator(Board *brd, int player)
{
    // player = 1 -> Sentinels
    // player = -1 -> Scourges
    char stingers = 'r', bombers = 'R';
    std::vector<Move> moveList;
    Move move;
    if(player == 1)
    {
        stingers = 'b';
        bombers = 'B';
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(brd->board[i][j] == stingers || brd->board[i][j] == bombers)
            {
                move.x1 = i;
                move.y1 = j;
                // Left diagonal
                move.x2 = i + (player * 1);
                move.y2 = j - 1;
                move.capture = 0;
                if(moveValidator(brd, move))
                {
                    moveList.push_back(move);  
                }
                // Right diagonal
                move.x2 = i + (player * 1);
                move.y2 = j + 1;
                move.capture = 0;
                if(moveValidator(brd, move))
                {
                    moveList.push_back(move);
                }   
                // Horizontal capture to the right
                move.x2 = i;
                move.y2 = j + 2;
                move.capture = 2;
                if(moveValidator(brd, move))
                {
                    move.capturedPiece = brd->board[i][j + 1];
                    moveList.push_back(move); 
                }
                // Horizontal capture to the left
                move.x2 = i;
                move.y2 = j - 2;
                move.capture = 1;
                if(moveValidator(brd, move))
                {
                    move.capturedPiece = brd->board[i][j - 1];
                    moveList.push_back(move);
                }
                // Vertical capture
                move.x2 = i + (player * 2);
                move.y2 = j;
                move.capture = 3;
                if(moveValidator(brd, move))
                {
                    move.capturedPiece = brd->board[i + (player * 1)][j];
                    moveList.push_back(move);
                }  
                if(brd->board[i][j] == bombers)
                {
                    // Left side move
                    move.x2 = i;
                    move.y2 = j - 1;
                    move.capture = 0;
                    if(moveValidator(brd, move))
                    {
                        moveList.push_back(move);
                    }
                        
                    // Straight down
                    move.x2 = i + (player * 1);
                    move.y2 = j;
                    move.capture = 0;
                    if(moveValidator(brd, move))
                    {
                        moveList.push_back(move);
                    }
                        
                    // Right side move
                    move.x2 = i;
                    move.y2 = j + 1;
                    move.capture = 0;
                    if(moveValidator(brd, move))
                    {
                        moveList.push_back(move);
                    }
                }
            }
        }
    }
    return moveList;
}

void makeMove(Board *brd, Move move)
{
    int multiplier = 1;
    char token = brd->board[move.x1][move.y1];
    if(token == 'r' || token == 'R')
        multiplier = -1;
    brd->board[move.x1][move.y1] = '_';
    brd->board[move.x2][move.y2] = token;
    if(move.capture == 1)  // left side horizontal capture
        brd->board[move.x1][move.y1 - 1] = '_';
    else if(move.capture == 2) // Right side horizontal capture
        brd->board[move.x1][move.y1 + 1] = '_';
    else if(move.capture == 3) // Vertical capture
        brd->board[move.x1 + (multiplier * 1)][move.y1] = '_';
}

void undoMove(Board *brd, Move move)
{
    int multiplier = 1;
    char token = brd->board[move.x2][move.y2];
    if(token == 'r' || token == 'R')
        multiplier = -1;
    brd->board[move.x2][move.y2] = '_';
    brd->board[move.x1][move.y1] = token;
    if(move.capture == 1) // left side horizontal capture
        brd->board[move.x1][move.y1 - 1] = move.capturedPiece;
    else if(move.capture == 2) // Right side horizontal capture
        brd->board[move.x1][move.y1 + 1] = move.capturedPiece;
    else if(move.capture == 3) // Vertical capture
        brd->board[move.x1 + (multiplier * 1)][move.y1] = move.capturedPiece;
}

inline int max(const int a, const int b)
{
    return a < b ? b : a;
}

inline int min(const int a, const int b)
{
    return a > b ? b : a;
}

int evaluate(Board *brd, int player)
{
    int playerBase = 4, opponentBase = 0, playerBomberCount = 0, opponentBomberCount = 0;
    int playerStingerCount = 0, opponentStingerCount = 0;
    int playerPositionalScore = 0, opponentPositionalScore = 0;
    char playerStinger = 'r', playerBomber = 'R', opponentStinger = 'b', opponentBomber = 'B';
    if(player == 1)
    {
        playerBase = 0;
        opponentBase = 4;
        playerStinger = 'b';
        playerBomber = 'B';
        opponentStinger = 'r';
        opponentBomber = 'R';
    }
    for(int i = 0; i < 5; i++)
    {
        if(brd->board[opponentBase][i] == playerBomber)
            return INF;
        else if(brd->board[playerBase][i] == opponentBomber)
            return -INF;
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(brd->board[i][j] == playerBomber)
            {
                playerPositionalScore += bomberWeights[i][j];
                playerBomberCount++;
            }
            else if(brd->board[i][j] == opponentBomber)
            {
                opponentPositionalScore += opponentBomberWeights[i][j];
                opponentBomberCount++;
            }
            else if(brd->board[i][j] == playerStinger)
            {
                playerPositionalScore += stingerWeights[i][j];
                playerStingerCount++;
            }   
            else if(brd->board[i][j] == opponentStinger)
            {
                opponentPositionalScore += opponentStingerWeights[i][j];
                opponentStingerCount++;
            }     
        }
    }
    if(playerBomberCount == 0)
        return -INF;
    else if(opponentBomberCount == 0)
        return INF;
    else
    {
        int evaluation = (playerPositionalScore - opponentPositionalScore) + ((4 * playerBomberCount + playerStingerCount) - (4 * opponentBomberCount + opponentStingerCount));
        return evaluation;
    }
}

// Player = 1 -> Sentinels
// Player = -1 -> Scourges
int algorithm(Board *brd, int depth, int maxDepth, int player, int alpha, int beta, bool isMaximizer)
{
    int score = evaluate(brd, player);
    if(score == INF)
        return score - depth;
    else if(score == -INF)
        return score + depth;
    else if(depth == maxDepth)
        return score;
    else
    {
        int opponent = 1;
        if(player == 1)
            opponent = -1;
        std::vector<Move> movesList;
        std::vector<Move> :: iterator movesItr;
        if(isMaximizer)
        {
            int best = -INF, eval;
            movesList = moveGenerator(brd, player);
            for(movesItr = movesList.begin(); movesItr != movesList.end(); movesItr++)
            {
                Move currentMove = *movesItr;
                makeMove(brd, currentMove);
                eval = algorithm(brd, depth + 1, maxDepth, player, alpha, beta, false);
                undoMove(brd, currentMove);
                best = max(best, eval);
                alpha = max(alpha, best);
                if(beta <= alpha)
                    break;
            }
            return best;
        }
        else
        {
            int best = INF, eval;
            movesList = moveGenerator(brd, opponent);
            for(movesItr = movesList.begin(); movesItr != movesList.end(); movesItr++)
            {
                Move currentMove = *movesItr;
                makeMove(brd, currentMove);
                eval = algorithm(brd, depth + 1, maxDepth, player, alpha, beta, true);
                undoMove(brd, currentMove);
                best = min(best, eval);
                beta = min(beta, best);
                if(beta <= alpha)
                    break;
            }
            return best;
        }
    }
    
}

Move findBestMove(Board brd, bool whoAmI)
{   
    int bestVal = -INF, player = 1, currVal;
    std::vector<Move> movesList;
    std::vector<Move>::iterator movesItr;
    Move bestMove, currentMove;
    Board *boardRef = &brd;
    if(!whoAmI)
        player = -1;
    movesList = moveGenerator(boardRef, player);
    for(movesItr = movesList.begin(); movesItr != movesList.end(); movesItr++)
    {
        currentMove = *movesItr;
        // Make a valid move
        makeMove(boardRef, currentMove);

        // Compute evaluation of board after this move
        currVal = algorithm(boardRef, 0, MAX_DEPTH, player, -INF, INF, false);
        if(currVal > bestVal)
        {
            bestVal = currVal;
            bestMove = currentMove;
        }
        
        // Undo the move
        undoMove(&brd, currentMove);
    }
    return bestMove;
}

int main()
{
    // if whoAmI = 1, I am Sentinels
    // if whoAmI = 0, I am Scourges
	bool turn, whoAmI;
    int myBase = 4, opponentBase = 0, myMultiplier = -1, opponentMultiplier = 1;
	std::string output;
    Board theBoard;
	std::cin>>turn;
	// if turn = 1, I am Sentinels and it's my turn first
	// if turn = 0, I am Scourges and it's my opponent's turn first
	whoAmI=turn;
    if(whoAmI)
    {
        myBase = 0;
        opponentBase = 4;
        myMultiplier = 1;
        opponentMultiplier = -1;
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(i == myBase)
                bomberWeights[i][j] = 1;
            if(i == (myBase + (myMultiplier * 1)))
            {
                stingerWeights[i][j] = 1;
                if(j == 0 || j == 4)
                	bomberWeights[i][j] = 3;
                bomberWeights[i][j] = 2;
            }
            if(i == (myBase + (myMultiplier * 2)))
            {
                stingerWeights[i][j] = 2;
                bomberWeights[i][j] = 3;
            }
            if(i == (myBase + (myMultiplier * 3)))
            {
                if(j == 0 || j == 4)
                {
                	stingerWeights[i][j] = 0;
                	bomberWeights[i][j] = 5;
                }
                else   
                {
                	stingerWeights[i][j] = 1;
                	bomberWeights[i][j] = 4;
                }
            }
            if(i == (myBase + (myMultiplier * 4)))
            {
                stingerWeights[i][j] = -2;
                bomberWeights[i][j] = 1000;
            }
            if(i == opponentBase)
                opponentBomberWeights[i][j] = 1;
            if(i == (opponentBase + (opponentMultiplier * 1)))
            {
                opponentStingerWeights[i][j] = 1;
                opponentBomberWeights[i][j] = 2;
            }
            if(i == (opponentBase + (opponentMultiplier * 2)))
            {
                opponentStingerWeights[i][j] = 2;
                opponentBomberWeights[i][j] = 4;
            }
            if(i == (opponentBase + (opponentMultiplier * 3)))
            {
                if(j == 0 || j == 4)
                    opponentStingerWeights[i][j] = 0;
                else
                    opponentStingerWeights[i][j] = 1;
                opponentBomberWeights[i][j] = 5;
            }
            if(i == (opponentBase + (opponentMultiplier * 4)))
            {
                opponentStingerWeights[i][j] = -2;
                opponentBomberWeights[i][j] = 1000;
            }
        }
    }
	while(1)
	{
		if(turn != 1)
		{
            int x1, y1, x2, y2, rowDiff = 0, colDiff = 0;
            char token = '_';
			std::cin>>x1>>y1>>x2>>y2;
            token = theBoard.board[x1][y1];
            theBoard.board[x1][y1] = '_';
            theBoard.board[x2][y2] = token;
            rowDiff = x2 - x1;
            colDiff = y2 - y1;
            if(rowDiff == 0 && colDiff == 2) // Right horizontal capture
                theBoard.board[x1][y1 + 1] = '_';
            else if(rowDiff == 0 && colDiff == -2) // Left horizontal capture
                theBoard.board[x1][y1 - 1] = '_';
            else if(colDiff == 0 && rowDiff == 2) // Downward vertical capture
                theBoard.board[x1 + 1][y1] = '_';
            else if(colDiff == 0 && rowDiff == -2) // Upward vertical capture
                theBoard.board[x1 - 1][y1] = '_';
		}
		turn = 0;	// after first iteration, (turn != 1) is always true
				//i.e. turn is always 0
		// logic to make the next move
        Move bestMove = findBestMove(theBoard, whoAmI);
        makeMove(&theBoard, bestMove);
        output = std::to_string(bestMove.x1) + " " + std::to_string(bestMove.y1) + " " + std::to_string(bestMove.x2) + " " + std::to_string(bestMove.y2);
        std::cout<<output<<"\n";
	}
    return 0;
}
