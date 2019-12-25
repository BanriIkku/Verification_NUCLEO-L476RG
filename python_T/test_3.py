# 自作関数のインポート
from my_module.classTest import printTest as AST


if __name__ == '__main__':
    test = AST()
    test.sayStr("Hello")   # Hello

