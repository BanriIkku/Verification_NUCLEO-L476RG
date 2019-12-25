from .super import SUB_superClass

class SUB_subClass(SUB_superClass):
    def __init__(self):
         super().__init__()
         self.data = -100
         self.id = self.id + 11000
    def display(self):
        print("this is SUB_subClass.display()   : " + str(self.data) + "[" + str(self.id) + "]")
    def display2(self):
        print("this is SUB_subClass.display()   : " + str(self.data) + "[" + str(self.id) + "]")

