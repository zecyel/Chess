from math import sqrt, log
from bin.player import Player
from mctsChess import MCTSChess
from copy import deepcopy as deepCopy

class MCTSNode():
    # just a data class
    
    def __init__(self, parent, board: MCTSChess):
        self.parent = parent
        self.son = {}
        self.quality = 0
        self.visit = 0
        if parent != None:
            self.board = deepCopy(parent.board)
        else:
            self.board = board

    def bestMove(self) -> tuple:
        return max(self.son, key = lambda x: self.son[x].quality / self.son[x].visit)


class MCTSPlayer(Player): # two players only

    def __init__(self, chess: MCTSChess, rank: int, budget: int = 50000, C: float = 0.707):
        super().__init__(chess, rank)
        self._root = MCTSNode(None)
        self.budget = budget
        self.C = C

    def _treePolicy(self, node: MCTSNode) -> MCTSNode:
        pass
    
    def _expand(self, node: MCTSNode) -> MCTSNode:
        pass
    
    def _bestChild(self, node: MCTSNode) -> MCTSNode:
        argmax = max(node.son, key = lambda x: node.son[x].quality / node.son[x].visit +
                                               self.C * sqrt(2 * log(node.visit) / (node.son[x].visit + 0.0001)))
        # add 0.0001 to prevent 'ZeroDivisionError'
        return node.son[argmax]

    def _defaultPolicy(self, node: MCTSNode) -> int:
        return node.board.estimiateWinner()

    def _backUp(self, node: MCTSNode) -> None:
        pass

    def _search(self) -> tuple:
        for _ in range(self.budget):
            v = self._treePolicy(self._root)
            delta = self._defaultPolicy(v)
            self._backUp(v, delta)
        return self._root.bestMove()

    def move(self) -> tuple or None:
        # Returning None means that the move should be get from the Interactor.
        pass

    def moveNotify(self, rank: int, move: tuple) -> None:
         # no need to update ._chess
        # ._chess has already been updated
        pass