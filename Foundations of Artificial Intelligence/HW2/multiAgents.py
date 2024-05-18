# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).

# discuss with b08502041
# reference: https://github.com/zhangjiedev/pacman/tree/master/multiagent

import sys
import util
import random

from util import manhattanDistance
from game import Directions

from game import Agent
from pacman import GameState

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """

    def getAction(self, gameState: GameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState: GameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"

        foods = newFood.asList()
        score = successorGameState.getScore()
        capsules = currentGameState.getCapsules()

        ghostPos = successorGameState.getGhostPosition(1)
        ghostDist = util.manhattanDistance(newPos, ghostPos)
        
        minDist = sys.maxsize
        for food in foods:
            dist = util.manhattanDistance(newPos, food)
            minDist = min(minDist, dist)

        score += ghostDist

        if len(foods) < len(currentGameState.getFood().asList()):
            score += 250

        score += 250 / minDist
        
        if newPos in capsules:
            score += 100

        if action == Directions.STOP:
            score -= 200
        
        return score

def scoreEvaluationFunction(currentGameState: GameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def maxValue(self, gameState, index, depth):
        actions = []
        for action in gameState.getLegalActions(index):
            value = self.minimax(gameState.generateSuccessor(index, action), (index + 1), depth)[0]
            actions.append((value, action))
        
        return max(actions)
    
    def minValue(self, gameState, index, depth):
        actions = []
        for action in gameState.getLegalActions(index):
            value = self.minimax(gameState.generateSuccessor(index, action), (index + 1), depth)[0]
            actions.append((value, action))

        return min(actions)

    def minimax(self, gameState, index, depth, alpha = -sys.maxsize, beta = sys.maxsize):
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return (self.evaluationFunction(gameState), "Stop")
        
        num = gameState.getNumAgents()
        index %= num
        if index == (num - 1):
            depth -= 1

        if index == 0:
            return self.maxValue(gameState, index, depth)
        else:
            return self.minValue(gameState, index, depth)

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"

        return self.minimax(gameState, 0, self.depth)[1]

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def maxValue(self, gameState, index, depth, alpha, beta):
        actions = []
        for action in gameState.getLegalActions(index):
            value = self.minimax(gameState.generateSuccessor(index, action), (index + 1), depth, alpha, beta)[0]
            
            if value > beta:
                return (value, action)
            
            actions.append((value, action))
            alpha = max(alpha, value)
        
        return max(actions)
    
    def minValue(self, gameState, index, depth, alpha, beta):
        actions = []
        for action in gameState.getLegalActions(index):
            value = self.minimax(gameState.generateSuccessor(index, action), (index + 1), depth, alpha, beta)[0]
            
            if value < alpha:
                return (value, action)

            actions.append((value, action))
            beta = min(beta, value)

        return min(actions)

    def minimax(self, gameState, index, depth, alpha = -sys.maxsize, beta = sys.maxsize):
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return (self.evaluationFunction(gameState), "Stop")
        
        num = gameState.getNumAgents()
        index %= num
        if index == (num - 1):
            depth -= 1

        if index == 0:
            return self.maxValue(gameState, index, depth, alpha, beta)
        else:
            return self.minValue(gameState, index, depth, alpha, beta)

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        
        return self.minimax(gameState, 0, self.depth)[1]

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def maxValue(self, gameState, index, depth):
        actions = []
        for action in gameState.getLegalActions(index):
            value = self.expectimax(gameState.generateSuccessor(index, action), (index + 1), depth)[0]
            actions.append((value, action))

        return max(actions)
    
    def expectValue(self, gameState, index, depth):
        actions = []
        sum = 0
        for action in gameState.getLegalActions(index):
            value = self.expectimax(gameState.generateSuccessor(index, action), (index + 1), depth)[0]
            actions.append((value, actions))
            sum += value

        return ((sum / len(actions)), )

    def expectimax(self, gameState, index, depth):
        if gameState.isWin() or gameState.isLose() or depth == 0:
            return (self.evaluationFunction(gameState), "Stop")
        
        num = gameState.getNumAgents()
        index %= num
        if index == (num - 1):
            depth -= 1

        if index == 0:
            return self.maxValue(gameState, index, depth)
        else:
            return self.expectValue(gameState, index, depth)

    def getAction(self, gameState: GameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        
        return self.expectimax(gameState, 0, self.depth)[1]

def betterEvaluationFunction(currentGameState: GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    
    pos = currentGameState.getPacmanPosition()
    foods = currentGameState.getFood().asList()
    capsules = currentGameState.getCapsules()

    ghostPos = currentGameState.getGhostPosition(1)
    ghostTimer = currentGameState.getGhostStates()[0].scaredTimer
    ghostDist = util.manhattanDistance(pos, ghostPos)

    foodDist = 100
    for food in foods:
        foodDist = min(foodDist, util.manhattanDistance(pos, food))
    foodScore = 500 - 10 * len(foods) - foodDist

    if ghostTimer > 0:
        ghostScore = max((80 - ghostDist), 72)
    else:
        ghostScore = -max((80 - ghostDist), 72)

    capDist = 100
    for capsule in capsules:
        capDist = min(capDist, util.manhattanDistance(pos, capsule))
    capScore = 500 - 10 * len(capsules) - capDist

    score = currentGameState.getScore() + foodScore + ghostScore + capScore
    return score


# Abbreviation
better = betterEvaluationFunction
