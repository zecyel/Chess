from bin.chess import Chess

class Player:
    
    def __init__(self, chess_: Chess, rank_: int):
        self._chess = chess_
        self._rank = rank_

    def move(self) -> tuple or None:
        # Returning None means that the move should be get from the Interactor.
        pass

    def moveNotify(self, move: tuple) -> None:
         # no need to update ._chess
        pass

    def rank(self):
        return self._rank