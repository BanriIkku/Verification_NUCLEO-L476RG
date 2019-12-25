# 自作関数のインポート
from my_module.super import superClass as AST
from my_module.sub import subClass as AST2


if __name__ == '__main__':
    test = AST()
    test2 = AST2()
    test3 = AST2()
    for i in range(0, 10, 1):
	    print("-----")
	    test.setData(i)
	    test.display()

	    test2.setData(i + 10)
	    test2.display2()
	    
	    test3.display()
	    
    print("-----")


