from mctsChess import MCTSChess
from extension.chess.gobang import GobangChess

class GobangChessForMCTS(MCTSChess, GobangChess):

    def possibleMoveSeq(self) -> list:
        ret = []
        for i in range(self.board.H):
            for j in range(self.board.W):
                if self.board.pos(i, j) == 0:
                    ret += [(i, j)]
        return ret