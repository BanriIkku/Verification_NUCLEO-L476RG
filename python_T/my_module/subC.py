from .super import superClass

class subClass(superClass):
    def __init__(self):
         super().__init__()
         self.data = -100
         self.id = self.id + 1000
    def display(self):
        print("this is subClass.display()       : " + str(self.data) + "[" + str(self.id) + "]")
    def display2(self):
        print("this is subClass.display()       : " + str(self.data) + "[" + str(self.id) + "]")

