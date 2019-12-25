# 自作関数のインポート
from my_module.sub.subTest import subPrintTest as SPT

from my_module.super import superClass as Sp
from my_module.subC import subClass as Su


from my_module.sub.super import SUB_superClass as SUB_Sp
from my_module.sub.sub import SUB_subClass as SUB_Su
from my_module.sub.sub2 import SUB_subClass2 as SUB_Su2



if __name__ == '__main__':
    test = SPT()
    rsp = Sp()
    rsu = Su()
    
    sp = SUB_Sp()
    su = SUB_Su()
    su2 = SUB_Su2()
    print("==============")
    for i in range(0, 10, 2):
	    print("-----")
	    test.sayStr("Hello : " + str(i))

	    rsp.setData(i+10)
	    rsp.display()
	    rsu.setData(i+20)
	    rsu.display()
	    
	    sp.setData(i+30)
	    sp.display()
	    
	    su.setData(i + 40)
	    su.display()
	    
	    su2.setData(i + 50)
	    su2.display()
	    
    print("==============")


