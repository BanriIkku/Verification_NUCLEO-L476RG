class superClass:
    def __init__(self):
         self.id = 1
         self.data = -999
    def setData(self, value):
        self.data = value
    def display(self):
        print("THIS IS superClass.display()     : " + str(self.data) + "[" + str(self.id) + "]")
