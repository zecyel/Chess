from math import sqrt, log
from bin.player import Player
from extension.player.mcts.mctsChess import MCTSChess
from copy import deepcopy as deepCopy

class MCTSNode():
    # just a data class
    
    def __init__(self, parent, chess: MCTSChess):
        self.parent = parent
        self.son = {}
        self.quality = 0
        self.visit = 0
        if parent != None:
            self.chess = deepCopy(parent.chess)
        else:
            self.chess = chess
        self.untried_move_seq = self.chess.suggestMoveSeq()

    def bestMove(self) -> tuple:
        return max(self.son, key = lambda x: self.son[x].quality / self.son[x].visit)

class MCTSPlayer(Player): # two players only

    def __init__(self, chess: MCTSChess, rank: int, budget: int = 50000, C: float = 0.707):
        super().__init__(chess, rank)
        # self._root = MCTSNode(None, chess)
        self.budget = budget
        self.C = C

    def _treePolicy(self, node: MCTSNode) -> MCTSNode:
        while node.chess.winner() == 0:
            if node.untried_move_seq != []:
                return self._expand(node)
            else:
                node = self._bestChild(node)
        return node
    
    def _expand(self, node: MCTSNode) -> MCTSNode:
        move = node.untried_move_seq.pop(0)
        new_node = deepCopy(node)
        node.son[move] = new_node
        new_node.chess.move(move)
        return new_node
    
    def _bestChild(self, node: MCTSNode) -> MCTSNode:
        argmax = max(node.son, key = lambda x: node.son[x].quality / node.son[x].visit +
                                               self.C * sqrt(2 * log(node.visit) / (node.son[x].visit + 0.0001)))
        # add 0.0001 to prevent 'ZeroDivisionError'
        return node.son[argmax]

    def _defaultPolicy(self, node: MCTSNode) -> int:
        return node.chess.estimiateWinner()

    def _backUp(self, node: MCTSNode, reward: int) -> None:
        while node:
            node.visit += 1
            node.quality += reward
            reward = -reward
            node = node.parent

    def _search(self) -> tuple:
        self._root = MCTSNode(None, self._chess)
        for _ in range(self.budget):
            v = self._treePolicy(self._root)
            delta = self._defaultPolicy(v)
            if delta == self.rank():
                reward = 1
            else:
                reward = -1
            self._backUp(v, reward)
        return self._root.bestMove()

    def move(self) -> tuple or None:
        return self._search()

    '''
    def moveNotify(self, rank: int, move: tuple) -> None:
        self._root = self._root.son[move]
        self._root.parent = None # Python-Garbage-Collector
    '''