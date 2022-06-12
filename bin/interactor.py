from bin.chess import Chess


class DisplayScheme:
    
    def __init__(self):
        self.config = {} # str -> str
        self.image = {} # int -> str
    
    def fetch(self, key: str, backup: str = None) -> str:
        # That is quite weird ^^^^^^^^^^^^^^^^^^
        if key in self.config:
            return self.config[key]
        assert backup != None
        return backup

class Interactor:

    def __init__(self, ds: DisplayScheme, chess: Chess):
        self.ds = ds
        self.chess = chess

    def update(self) -> None:
        pass
    
    def getMove(self) -> tuple:
        pass