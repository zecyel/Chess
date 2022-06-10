import bin.interactor as interactor

standardIndex = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def standardParser(a: str) -> tuple:
    r = dict(zip(standardIndex, range(0, 35)))
    return (r[a[0]], r[a[1]])

class TerminalInteractor(interactor.Interactor):

    def update(self) -> None:
        board_height = self.chess.getBoardSize()[0]
        board_width = self.chess.getBoardSize()[1]
        row_index = self.ds.fetch("rowIndex", standardIndex[:board_height])
        column_index = self.ds.fetch("columnIndex", standardIndex[:board_width])
        print(" " + column_index)
        for i in range(board_height):
            print(row_index[i], end = "")
            for j in range(board_width):
                print(self.ds.image[self.chess.board.pos(i, j)], end = "")
            print()
        if self.chess.winner() != 0:
            print(self.ds.fetch("display.win", lambda x: str(x) + " is Winner")(self.chess.winner()))
    
    def getMove(self) -> tuple:
        a = input(self.ds.fetch("display.hint", "Please input your move: "))
        return self.ds.fetch("move.movePaser", standardParser)(a)