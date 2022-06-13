from bin.chess import Chess
from copy import deepcopy as deepCopy
from random import choice

class MCTSChess(Chess):
    
    def __init__(self, moveSuggestor = None, winnerEstimator = None):
        super().__init__()
        if moveSuggestor:
            self.moveSuggestor = moveSuggestor
        if winnerEstimator:
            self.winnerEstimator = winnerEstimator

    def possibleMoveSeq(self) -> list: # list of tuples
        pass
    
    def suggestMoveSeq(self) -> list: # list of tuples
        return self.possibleMoveSeq()

    def estimiateWinner(self) -> int:
        a = deepCopy(self)
        while a.winner() == 0:
            a.move(choice(a.possibleMoveSeq()))
        return a.winner()