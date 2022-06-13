from bin.game import Game
from bin.interactor import DisplayScheme
from extension.player.terminal.interactive import InteractiveTerminalPlayer
from extension.player.mcts.mcts import MCTSPlayer
from extension.player.mcts.gobang.gobang import GobangChessForMCTS as GobangChess
from extension.interactor.terminal import TerminalInteractor

c = GobangChess()
p1 = InteractiveTerminalPlayer(c, 1)
p2 = MCTSPlayer(c, 2, budget = 5)
ds = DisplayScheme()
ds.image[0] = "."
ds.image[1] = "#"
ds.image[2] = "@"
i = TerminalInteractor(ds, c)
g = Game(c, i, [p1, p2])
g.run()