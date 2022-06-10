import extension.interactor.terminal as ti
import extension.chess.gobang as gc
import bin.interactor as i
a = gc.GobangChess()
b = i.DisplayScheme()
b.image[0] = "."
b.image[1] = "#"
b.image[2] = "@"
c = ti.TerminalInteractor(b, a)
while a.winner() == 0:
    c.update()
    a.move(c.getMove())
