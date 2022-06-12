import bin.chess as chess

class GobangChess(chess.Chess):

    def __init__(self):
        super().__init__()
        self.board = chess.Board(15, 15) # standard size
    
    def move(self, move: tuple) -> bool:
        if not self.checkMove(move):
            return False
        self.board.put(*move, self.currentPlayer())
        self._nextPlayer()
        return True
    
    def checkMove(self, move: tuple) -> bool:
        # move :== (x, y)
        assert len(move) == 2 and \
               isinstance(move[0], int) and \
               isinstance(move[1], int)
        return self.board.pos(*move) == 0
    
    def _winner(self) -> int:
        xlim = [(0, 15), (0, 11), (0, 11), (0, 11)]
        ylim = [(0, 11), (0, 15), (0, 11), (4, 15)]
        dire = [(0, 1), (1, 0), (1, 1), (1, -1)]
        for k in range(4):
            for i in range(*xlim[k]):
                for j in range(*ylim[k]):
                    dx, dy = dire[k]
                    if self.board.pos(i, j) == \
                       self.board.pos(i + dx, j + dy) == \
                       self.board.pos(i + 2 * dx, j + 2 * dy) == \
                       self.board.pos(i + 3 * dx, j + 3 * dy) == \
                       self.board.pos(i + 4 * dx, j + 4 * dy) != 0:
                        return self.board.pos(i, j)
        return 0

    def getBoardSize(self) -> tuple:
        return (15, 15)