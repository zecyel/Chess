from ast import In
from bin.game import Game
from extension.chess.gobang import GobangChess
from extension.player.terminal.interactive import InteractiveTerminalPlayer
from bin.interactor import DisplayScheme
from extension.interactor.terminal import TerminalInteractor

c = GobangChess()
p1 = InteractiveTerminalPlayer(c, 1)
p2 = InteractiveTerminalPlayer(c, 2)
ds = DisplayScheme()
ds.image[0] = "."
ds.image[1] = "#"
ds.image[2] = "@"
i = TerminalInteractor(ds, c)
g = Game(c, i, [p1, p2])
g.run()