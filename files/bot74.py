#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 17 22:36:12 2018

@author: kunalsinha
"""
"Test Bot 1"

from math import sqrt
from math import log
import random
import copy
import time


b = [['B', 'B', 'B', 'B', 'B'], ['b', 'b', 'b', 'b', 'b'], ['_', '_', '_', '_', '_'],
                      ['w', 'w', 'w', 'w', 'w'], ['W', 'W', 'W', 'W', 'W']]

class GameState:

    def __init__(self):
        self.whosemove = whoAmI
        self.Bm = 0
        self.Wm = 0
        self.goFlag = 0
        self.board = b

    def Clone(self):
        #print "cloned"
        st = GameState()
        st.whosemove = self.whosemove
        st.board = copy.deepcopy(self.board)
        st.Bm = self.Bm
        st.Wm = self.Wm
        st.goFlag = self.goFlag
        #print st.board
        return st

    def Elimination(self, move, goFlag1):
        x = self.whosemove
        x = not x
        if x == 0:
            if goFlag1 == 2:
                self.Wm += 1
        else:
            if goFlag1 == 2:
                self.Bm += 1
        self.board[(move[0][0] + move[1][0]) / 2][(move[0][1] + move[1][1]) / 2] = '_'
        """s1= ""
        for i in range(5): 
            for j in range(5):
                s1 += str(self.board[i][j])
                if j % 5 == 4: s1 += "\n"
        print str(s1)"""
        # print self.board

    def DoMove(self, move):
        goFlag1 = 0
        goFlag1 = self.CheckMove(move)
       # print move
        if goFlag1 == 1:
            self.board[move[1][0]][move[1][1]] = self.board[move[0][0]][move[0][1]]
            self.board[move[0][0]][move[0][1]] = '_'

        elif goFlag1 == 2 or goFlag1 == 3:
            self.board[move[1][0]][move[1][1]] = self.board[move[0][0]][move[0][1]]
            self.board[move[0][0]][move[0][1]] = '_'
            #print "ELIMINATION"
            self.Elimination(move, goFlag1)
        self.whosemove = 1 - self.whosemove
        """s1= ""
        for i in range(5): 
            for j in range(5):
                s1 += str(self.board[i][j])
                if j % 5 == 4: s1 += "\n"
        print str(s1)"""

    def CheckMove(self, move):
        x = self.whosemove
        if x == 0:
            X = 'W'
            Y = 'w'
        else:
            X = 'B'
            Y = 'b'

        d1 = move[1][0] - move[0][0]
        d2 = move[1][1] - move[0][1]

        if move[0][0] < 0 or move[0][0] > 4 or move[0][1] < 0 or move[0][1] > 4 or move[1][0] < 0 or move[1][0] > 4 or \
                move[1][1] < 0 or move[1][1] > 4 or self.board[move[1][0]][move[1][1]] != '_' or (
                self.board[move[0][0]][move[0][1]] != X and self.board[move[0][0]][move[0][1]] != Y):
            return 0
        else:
            if self.board[move[0][0]][move[0][1]] == X:
                if (d1 == (2 * x - 1) or d1 == 0) and (d2 == (2 * x - 1) or d2 == -(2 * x - 1) or d2 == 0):
                    return 1
                elif (((d1 == 2 * (2 * x - 1) and d2 == 0) or (
                        d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1)))) and (
                              move[0][0] != 0 and move[0][0] != 4)):
                    if (d1 == 2 * (2 * x - 1) and d2 == 0):
                        t1 = self.board[move[0][0] + 2 * x - 1][move[0][1]]
                    elif (d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1))):
                        t1 = self.board[move[0][0]][(move[0][1] + move[1][1]) / 2]

                    if x == 1:
                        if t1 == 'W':
                            return 2
                        elif t1 == 'w':
                            return 3
                    else:
                        if t1 == 'B':
                            return 2
                        elif t1 == 'b':
                            return 3

            elif self.board[move[0][0]][move[0][1]] == Y:
                if ((d1 == (2 * x - 1) and d2 == (2 * x - 1)) or (d1 == (2 * x - 1) and d2 == -(2 * x - 1))):
                    return 1
                elif (((d1 == 2 * (2 * x - 1) and d2 == 0) or (
                        d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1)))) and (
                              move[0][0] != 0 and move[0][0] != 4)):
                    if (d1 == 2 * (2 * x - 1) and d2 == 0):
                        t1 = self.board[move[0][0] + 2 * x - 1][move[0][1]]
                    elif (d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1))):
                        t1 = self.board[move[0][0]][(move[0][1] + move[1][1]) / 2]

                    if x == 1:
                        if t1 == 'W':
                            return 2
                        elif t1 == 'w':
                            return 3
                    else:
                        if t1 == 'B':
                            return 2
                        elif t1 == 'b':
                            return 3
        return 0

    def mValidation(self):
        x = self.whosemove
        if x == 0:
            X = 'W'
            Y = 'w'
        else:
            X = 'B'
            Y = 'b'

        d1 = self.mrow - self.row
        d2 = self.mcol - self.col

        if self.row < 0 or self.row > 4 or self.col < 0 or self.col > 4 or self.mrow < 0 or self.mrow > 4 or self.mcol < 0 or self.mcol > 4 or \
                self.board[self.mrow][self.mcol] != '_' or (
                self.board[self.row][self.col] != X and self.board[self.row][self.col] != Y):
            return 0
        else:
            if self.board[self.row][self.col] == X:
                if (d1 == (2 * x - 1) or d1 == 0) and (d2 == (2 * x - 1) or d2 == -(2 * x - 1) or d2 == 0):
                    return 1
                elif (((d1 == 2 * (2 * x - 1) and d2 == 0) or (
                        d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1)))) and (
                              self.row != 0 and self.row != 4)):
                    if (d1 == 2 * (2 * x - 1) and d2 == 0):
                        t1 = self.board[self.row + 2 * x - 1][self.col]
                    elif (d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1))):
                        t1 = self.board[self.row][(self.col + self.mcol) / 2]

                    if x == 1:
                        if t1 == 'W':
                            return 2
                        elif t1 == 'w':
                            return 3
                    else:
                        if t1 == 'B':
                            return 2
                        elif t1 == 'b':
                            return 3

            elif self.board[self.row][self.col] == Y:
                if ((d1 == (2 * x - 1) and d2 == (2 * x - 1)) or (d1 == (2 * x - 1) and d2 == -(2 * x - 1))):
                    return 1
                elif (((d1 == 2 * (2 * x - 1) and d2 == 0) or (
                        d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1)))) and (
                              self.row != 0 and self.row != 4)):
                    if (d1 == 2 * (2 * x - 1) and d2 == 0):
                        t1 = self.board[self.row + 2 * x - 1][self.col]
                    elif (d1 == 0 and (d2 == 2 * (2 * x - 1) or d2 == -2 * (2 * x - 1))):
                        t1 = self.board[self.row][(self.col + self.mcol) / 2]

                    if x == 1:
                        if t1 == 'W':
                            return 2
                        elif t1 == 'w':
                            return 3
                    else:
                        if t1 == 'B':
                            return 2
                        elif t1 == 'b':
                            return 3
        return 0

    def GetMoves(self):
        if self.whosemove == 0:
            X = 'W'
            Y = 'w'
        else:
            X = 'B'
            Y = 'b'
        game = []
        sgame = []
        i = 0
        j = 0
        k = 0
        l = 0
        for i in range(5):
            for j in range(5):

                if self.board[i][j] == '_':
                    continue

                elif self.board[i][j] == X or self.board[i][j] == Y:
                    self.row = i
                    self.col = j
                    k = -2
                    l = 0
                    z = 0

                    while l <= 2 and l >= 0 and k <= 2:
                        if self.whosemove == 1:
                            self.mrow = i + l
                        else:
                            self.mrow = i - l
                        self.mcol = j + k

                        if self.mrow < 5 and self.mrow >= 0 and self.mcol < 5 and self.mcol >= 0:
                            # print "b"
                            self.goFlag = self.mValidation()
                            if self.goFlag == 1 or self.goFlag == 2 or self.goFlag == 3:
                                game.append((self.mrow, self.mcol))
                                sgame.append((self.row, self.col))
                        if l == 2:
                            z = 1
                            # print "b"
                        if z == 0:
                            l += 1
                            # print "c"
                        else:
                            l -= 1
                        # print "d"
                        k += 1

                    if self.board[i][j] == X:
                        self.row = i
                        self.col = j
                        k = -1
                        l = 0
                        z = 0

                        while l <= 1 and l >= 0 and k <= 1:
                            if self.whosemove == 1:
                                self.mrow = i + l
                            else:
                                self.mrow = i - l
                            self.mcol = j + k

                            if self.mrow < 5 and self.mrow >= 0 and self.mcol < 5 and self.mcol >= 0:
                                self.goFlag = self.mValidation()
                                if self.goFlag == 1 or self.goFlag == 2 or self.goFlag == 3:
                                    game.append((self.mrow, self.mcol))
                                    sgame.append((self.row, self.col))

                            if l == 1:
                                z = 1
                            if z == 0:
                                l += 1
                            else:
                                l -= 1
                            k += 1
        # if goFlag == 1 or goFlag == 2 or goFlag ==3:
        # game = list(set(game))
        # game.sort()
        # sgame = list(set(sgame))
        # sgame.sort()
        # print sgame
        # print game
        fgame = zip(sgame, game)
        # s1 = fgame[3][1][0]
        # print fgame
        gm = self.findgameover()
        if gm == 1:
            return []
        else:
            return fgame

    def findgameover(self):
        if self.Bm == 5 or self.Wm == 5:
            return 1
        for i in range(5):
            if self.board[0][i] == 'W':
                return 1
            if self.board[4][i] == 'B':
                return 1

    def gameover(self):
        if self.Bm == 5 or self.Wm == 5:
            return 1
        for i in range(5):
            if self.board[0][i] == 'W':
                return 1
            if self.board[4][i] == 'B':
                return 1

        if self.GetMoves() == []:
            return 2
        """i=0
        j=0
        k=0
        l=0
        for i in range(5):
            for j in range(5):
                if self.board[i][j] == '_':
                    continue
                else:
                    if self.board[i][j] == 'B' or self.board[i][j] == 'b':
                        x = 1
                    else:
                        x = 0
                    self.row = i
                    self.col = j
                    k = -2
                    l = 0
                    z = 0
                    while l<=2 and l>=0 and k<=2:
                        if x==1:
                            self.mrow = i + l
                        else:
                            self.mrow = i - l
                        self.mcol = j + k

                        if self.mrow < 5 and self.mrow >=0 and self.mcol < 5 and self.mcol >= 0:
                            self.goFlag = self.mValidation()
                            if self.goFlag==1 or self.goFlag==2 or self.goFlag==3:
                                return 0

                        if l == 2:
                            z = 1
                        if z == 0:
                            l+1
                        else:
                            l-1
                        k+1

                    if self.board[i][j] == 'B' or self.board[i][j] == 'W':
                        self.row = i
                        self.col = j
                        k = -1
                        l = 0
                        z = 0
                        while l<=1 and l>=0 and k<=1:
                            if x==1:
                                self.mrow = i + l
                            else:
                                self.mrow = i - l
                            self.mcol = j + k

                            if self.mrow < 5 and self.mrow >=0 and self.mcol < 5 and self.mcol >= 0:
                                self.goFlag = self.mValidation()
                                if self.goFlag == 1:
                                    return 0

                            if l == 1:
                                z = 1
                            if z == 0:
                                l+1
                            else:
                                l-1
                            k+1
        return 2"""

    def GetResult(self, pjm):
        result = self.gameover()
        if result == 1 and pjm == self.whosemove:
            return 1.0
        elif result == 1 and pjm != self.whosemove:
            return 0.0
        elif result == 2:
            return 0.5
        assert False

    def __repr__(self):
        s = ""
        for i in range(5):
            for j in range(5):
                s += str(self.board[i][j])
                if j % 5 == 4: s += "\n"
        return s


class Node:
    """ A node in the game tree. Note wins is always from the viewpoint of playerJustMoved.
        Crashes if state not specified.
    """

    def __init__(self, move=None, parent=None, state=None):
        self.move = move  # the move that got us to this node - "None" for the root node
        self.parentNode = parent  # "None" for the root node
        self.childNodes = []
        self.wins = 0
        self.visits = 0
        self.untriedMoves = state.GetMoves()  # future child nodes
        self.whosemove = state.whosemove  # the only part of the state that the Node needs later

    def UCTSelectChild(self):
        """ Use the UCB1 formula to select a child node. Often a constant UCTK is applied so we have
            lambda c: c.wins/c.visits + UCTK * sqrt(2*log(self.visits)/c.visits to vary the amount of
            exploration versus exploitation.
        """
        #print "UCT-SELECT-CHILD"
        s = sorted(self.childNodes, key=lambda c: c.wins / c.visits + sqrt(2 * log(self.visits) / c.visits))[-1]
       # print s
        return s

    def AddChild(self, m, s):
        """ Remove m from untriedMoves and add a new child node for this move.
            Return the added child node
        """
       # print "ADD-CHILD"
        n = Node(move=m, parent=self, state=s)
        self.untriedMoves.remove(m)
        self.childNodes.append(n)
        return n

    def Update(self, result):
        """ Update this node - one additional visit and result additional wins. result must be from the viewpoint of playerJustmoved.
        """
        self.visits += 1
        self.wins += result

    def __repr__(self):
        return "[M:" + str(self.move) + " W/V:" + str(self.wins) + "/" + str(self.visits) + " U:" + str(
            self.untriedMoves) + "]"

    def TreeToString(self, indent):
        s = self.IndentString(indent) + str(self)
        for c in self.childNodes:
            s += c.TreeToString(indent + 1)
        return s

    def IndentString(self, indent):
        s = "\n"
        for i in range(1, indent + 1):
            s += "| "
        return s

    def ChildrenToString(self):
        s = ""
        for c in self.childNodes:
            s += str(c) + "\n"
        return s


def UCT(rootstate, itermax, verbose=False):
    """ Conduct a UCT search for itermax iterations starting from rootstate.
        Return the best move from the rootstate.
        Assumes 2 alternating players (player 1 starts), with game results in the range [0.0, 1.0]."""

    rootnode = Node(state=rootstate)

    for i in range(itermax):
        node = rootnode
        #print "ROOTSTATE"
        #print rootstate
        state = rootstate.Clone()
       # print state
       # print "############"
       # print GameState().board

        # Select
        while node.untriedMoves == [] and node.childNodes != []:  # node is fully expanded and non-terminal
           # print "0"
            node = node.UCTSelectChild()
           # print node
            state.DoMove(node.move)
           # print state

        # Expand
        if node.untriedMoves != []:  # if we can expand (i.e. state/node is non-terminal)
            #print "1"
            m = random.choice(node.untriedMoves)
            # print m
            state.DoMove(m)
            #print state
            node = node.AddChild(m, state)  # add child and descend tree
           # print node

        # Rollout - this can often be made orders of magnitude quicker using a state.GetRandomMove() function
        while state.GetMoves() != []:  # while state is non-terminal
           # print "2"
            state.DoMove(random.choice(state.GetMoves()))
           # print state

        # Backpropagate
        while node != None:  # backpropagate from the expanded node and work back to the root node
            #print "3"
            #print node
            node.Update(state.GetResult(node.whosemove))
           # print node  # state is terminal. Update node with result from POV of node.whosemove
            node = node.parentNode
           # print node

    # Output some information about the tree - can be omitted
    """if (verbose):
       # print rootnode.TreeToString(0)
    else:
        #print rootnode.ChildrenToString()"""
    #print sorted(rootnode.childNodes, key=lambda c: c.visits)[-1].move


    return sorted(rootnode.childNodes, key=lambda c: c.visits)[-1].move  # return the move that was most visited



def UCTPlayGame():
    """ Play a sample game between two UCT players where each player gets a different number
        of UCT iterations (= simulations = tree nodes).
    """
    #start_time = time.time()
    state = GameState()
    #while (state.GetMoves() != []):
        #print state.GetMoves()
    #print str(state)
    #if state.whosemove == 1:
        #print "Black's move"
    m = UCT(rootstate=state, itermax=100, verbose=False)  # play with values for itermax and verbose = True
        #print m
    #else:
        #print "White's Move"
        #m = UCT(rootstate=state, itermax=150, verbose=False)
        #print m
    print str(m[0][0])+" "+str(m[0][1])+" "+str(m[1][0])+" "+str(m[1][1])

    state.DoMove(m)

    #print state
    #print("--- %s seconds ---" % (time.time() - start_time))
    """if state.GetResult(state.whosemove) == 1.0:
        print "Player " + str(1 - state.whosemove) + " wins!"
    elif state.GetResult(state.whosemove) == 0.0:
        print "Player " + str(state.whosemove) + " wins!"
    else:
        print "Nobody wins!"""



#UCTPlayGame()


def dooppmove(move):
    Wm1 = 0
    Bm1 = 0
    b[move[1][0]][move[1][1]] = b[move[0][0]][move[0][1]]
    b[move[0][0]][move[0][1]] = '_'
    d1 = move[1][0] - move[0][0] # difference  between initial and final row position
    d2 = move[1][1] - move[0][1] # difference  between initial and final col position

    if d1 > 1 or d1 < -1 or d2 > 1 or d2 < -1:
        t1 = b[(move[1][0] + move[0][0]) / 2][(move[1][1] + move[0][1]) / 2]
        if whoAmI == 0:
            if t1 == 'W':
                Wm1+=1
        else:
            if t1 == 'B':
                Bm1+=1
        b[(move[1][0] + move[0][0]) / 2][(move[1][1] + move[0][1]) / 2] = '_'


def gmmo():
    gmo = 0
    for i in range(5):
        if b[0][i] == 'W':
            gmo = 1
    return gmo
turn = None
turn = input()
whoAmI = turn
while (1):
    if turn != 1:
        input = raw_input()
        move = ((ord(input[0]) - 48, ord(input[2]) - 48), (ord(input[4]) - 48, ord(input[6]) - 48))
        dooppmove(move)
        #print GameState()



    if not (whoAmI == 1 and gmmo()==1):
        turn = 0
        UCTPlayGame()



