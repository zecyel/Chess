'''
    The so-called abstract classes.
    Just define interface.
'''

class Board:

    def __init__(self, H: int, W: int):
        self.H = H
        self.W = W
        self.board = [[0] * W for _ in range(H) ]

    def pos(self, x: int, y: int) -> int: # safer than .board[x][y]
        assert 0 <= x < self.H and \
               0 <= y < self.W
        return self.board[x][y]
    
    def put(self, x: int, y: int, t: int) -> None:
        assert 0 <= x < self.H and \
               0 <= y < self.W
        self.board[x][y] = t

class Chess:

    def __init__(self):
        self.__current_player = 1 # 1 to n, 0 as void
        self.__player_count = 2 # if not, modify it in subclass
        self.board = None # modify it in subclass
        self.__winner = 0
    
    def move(self, move: tuple) -> bool:
        pass
    
    def checkMove(self, move: tuple) -> bool:
        pass

    def currentPlayer(self) -> int:
        return self.__current_player

    def _nextPlayer(self) -> None:
        self.__current_player = self.__current_player % self.__player_count + 1

    def _winner(self) -> int:
        pass

    def winner(self) -> int:
        if self.__winner != 0:
            return self.__winner
        self.__winner = self._winner()
        return self.__winner

    def parseMove(self, a: str) -> tuple:
        pass

    def getBoardSize(self) -> tuple: # (H, W)
        # if want to use TerminalInteractor, then it's a must
        pass