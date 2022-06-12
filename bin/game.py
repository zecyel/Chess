from bin.chess import Chess
from bin.interactor import Interactor
from bin.player import Player

class Game:

    def __init__(self, chess: Chess, interactor: Interactor, player_seq: list) -> None:
        self.chess = chess
        self.interactor = interactor
        self.player_seq = player_seq
        self.interactor.update()
    
    def run(self):
        while self.chess.winner() == 0:
            cur_player = self.player_seq[self.chess.currentPlayer() - 1]
            # .currentPlayer return 1 ~ playerCount
            # but player_seq's index is 0 ~ playerCount - 1
            # and assume that player.move() is always valid
            m = cur_player.move()
            if m == None:
                m = self.interactor.getMove()
                while not self.chess.checkMove(m):
                    m = self.interactor.getMove()
            self.chess.move(m)
            for i in self.player_seq:
                i.moveNotify(cur_player.rank(), m)
            self.interactor.update()
