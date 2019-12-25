class SUB_superClass:
    def __init__(self):
         self.id = 55
         self.data = -999
    def setData(self, value):
        self.data = value
    def display(self):
        print("THIS IS SUB_superClass.display() : " + str(self.data) + "[" + str(self.id) + "]")
