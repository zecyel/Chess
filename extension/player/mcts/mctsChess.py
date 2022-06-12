from bin.chess import Chess
from copy import deepcopy as deepCopy
from random import choice

class MCTSChess(Chess):
    
    def __init__(self, moveSuggestor: function = None, winnerEstimator: function = None):
        self.__suggestor = moveSuggestor
        self.__winnerEstimator = winnerEstimator

    def possibleMoveSeq(self) -> list: # list of tuples
        pass
    
    def _suggestMoveSeq(self) -> list: # list of tuples
        return self.possibleMoveSeq()

    def suggestMoveSeq(self) -> list: # list of tuples
        if self.__suggestor != None:
            return self.__suggestor(self)
        return self._suggestMoveSeq()

    def _estimiateWinner(self) -> int:
        a = deepCopy(self)
        while a.winner() == 0:
            a.move(choice(a.possibleMoveSeq()))
        return a.winner()

    def estimiateWinner(self) -> int:
        if self.__winnerEstimator != None:
            return self.__winnerEstimator(self)
        return self._estimiateWinner()