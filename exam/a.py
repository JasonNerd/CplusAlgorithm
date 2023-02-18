# import语句一般放在开头, 表示程序中使用到的非自定义变量从这里找
from decimal import Decimal     # 这一句意思是引入库
# 变量名小写
a = 1.1 # a是一个小数 float
print(a, type(a))   # 一般空格放在, 后面
b = "1.1"   # b是一个字符串 string
print(b, type(b))
# 问: a与b相等吗？
print(a == b, type(a==b))   # == 表示判断是不是相等
# 输出true或者false, 也即布尔值, 真或者假, 表示一个式子是不是成立的
# 问: 可以把b转成数字类型吗?
# 可以
b = Decimal(b)  
print(b, type(b))
# 现在a和b相等吗?
print(a == b)
# 最后转为基本的 float 类型
b = float(b)
print(a == b)