from bin.chess import Chess
from bin.interactor import Interactor
from bin.player import Player

class Game:

    def __init__(self, chess_: Chess, interactor_: Interactor, player_seq_: list) -> None:
        self.chess = chess_
        self.interactor = interactor_
        self.player_seq = player_seq_
        self.interactor.update()
    
    def run(self):
        while self.chess.winner() == 0:
            m = self.player_seq[self.chess.currentPlayer() - 1].move()
            # .currentPlayer return 1 ~ playerCount
            # but player_seq's index is 0 ~ playerCount - 1
            # and assume that player.move() is always valid
            if m == None:
                m = self.interactor.getMove()
                while not self.chess.checkMove(m):
                    m = self.interactor.getMove()
            self.chess.move(m)
            self.interactor.update()
