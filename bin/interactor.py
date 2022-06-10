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

    def __init__(self, ds_ : DisplayScheme, chess_ : Chess):
        self.ds = ds_
        self.chess = chess_

    def update(self) -> None:
        pass
    
    def getMove(self) -> tuple:
        pass