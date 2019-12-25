from ..super import superClass

class SUB_subClass2(superClass):
    def __init__(self):
         super().__init__()
         self.data = -80
         self.id = self.id + 21000
    def display(self):
        print("this is SUB_subClass2.display()  : " + str(self.data) + "[" + str(self.id) + "]")
    def display2(self):
        print("this is SUB_subClass2.display()  : " + str(self.data) + "[" + str(self.id) + "]")

