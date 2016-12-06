// 栈的操作.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h" //VS开发环境必须头文件 VC6.0环境请删除此头文件
#include "iostream"
#include "fstream"
#include "string"
#include "iomanip"
#include "regex" //正则表达式头文件
#define STACKSIZE 10 //栈大小
#define FAIL 0 //操作失败
#define SUCCESS 1 //操作成功
#define QUIT -1 //退出

using namespace std;
//双向链栈类
class Stack
{
public:
	
	Stack();
	~Stack();
	Stack(int number);
	float data;
	Stack *next;
	Stack *pre;
};

Stack::Stack()
{

}

Stack::~Stack()
{

}

Stack::Stack(int number)
{
	data = number;
	next = NULL;
	pre = NULL;
}



//栈操作类
class Admin
{
public:
	Admin();
	~Admin();

	bool isFull();//stack full?
	bool isEmpty();//stack empty?

	
	int inStack(int number);//in stack
	int outStack();//out stack

	void quit();

	void addTop(int number);
	void subTop(int number);
	void mulTop(int number);
	void divTop(int number);
private:
	Stack *base;
	Stack *top;
	Stack *bottom;
	int stacksize;
	fstream fileforwrite;
};

Admin::Admin()
{
	base = new Stack;
	base->next = NULL;
	base->pre = base;
	//指向栈底
	top = base;
	stacksize = 0;
	fileforwrite.open("实验二-模式三-链栈结果文件.txt", ios::out);
}

Admin::~Admin()
{
	
}

bool Admin::isFull()
{
	return (stacksize < STACKSIZE ?  false: true);
}

bool Admin::isEmpty()
{
	return (stacksize == 0 ? true : false);
}



int Admin::inStack(int number)
{
	if (isFull())
		return FAIL;
	Stack *newstack = new Stack(number);
	top->next = newstack;//入栈
	newstack->pre = top;
	top = top->next;//top移动，新的栈顶
	stacksize++;
	return SUCCESS;
}

int Admin::outStack()
{
	if (isEmpty())
		return FAIL;
	fileforwrite << top->data << setw(10);//写入文件
	top = top->pre;//top前移，准备出栈
	delete top->next;//出栈
	top->next = NULL;
	stacksize--;
	return SUCCESS;
}

//退出操作
void Admin::quit()
{
	//关闭文件
	fileforwrite.close();
}

void Admin::addTop(int number)
{
	top->data = number + top->data;
}

void Admin::subTop(int number)
{
	top->data = top->data - number;
}

void Admin::mulTop(int number)
{
	top->data = number * top->data;
}

void Admin::divTop(int number)
{
	top->data = top->data / number;
}


int main()
{
	system("title 实验二-模式三-链栈结果文件");
	system("color f0");
	Admin admin;
	string line;//用于读取字符串
	int item;

	//正则表达式的创建
	//regex number("^[0-9]{1,}$");//匹配数字0-9一次或多次用来入栈的数据
	regex in("^[I|i]{1}$");//匹配入栈操作 ^[I|i]{1}$ 匹配字符串，该字符串以I或i开头且结尾 I或i仅出现一次
	regex out("^[O|o]{1}$");//匹配出栈操作 ^[O|o]{1}$ 匹配字符串，该字符串以O或o开头且结尾 O或o仅出现一次
	regex quit("^[Q|q]{1}$");//匹配退出的操作 ^[Q|q]{1}$ 匹配字符串，该字符串以Q或q开头且结尾 Q或q仅出现一次
	regex astd("^[A|a|S|s|T|t|D|d]{1}$");//对栈顶进行加减乘除 匹配字符串，该字符串可以是以下字符串，但只能出现一次（AaSsTtDd）
	
	fstream fileforread("输入数据模3层3栈拓展.txt", ios::in);
	while (!fileforread.eof())
	{
		fileforread >> line;//读取文件
		if (regex_match(line, in)) {
			//如果有入栈操作那么执行下面操作
			fileforread >> line;//读下一个字符串
			item = atoi(line.c_str());//将字符串转换为整数
			admin.inStack(item);//准备入栈
		}
		else if (regex_match(line, astd)){
			//如果是加减乘除操作那么执行下面操作

			//加法操作
			if (line == "A" || line == "a") {
				fileforread >> line;
				item = atoi(line.c_str());
				admin.addTop(item);
				continue;
			}

			//减法操作
			else if (line == "S" || line == "s")
			{
				fileforread >> line;
				item = atoi(line.c_str());
				admin.subTop(item);
				continue;
			}

			//乘法操作
			else if (line == "T" || line == "t")
			{
				fileforread >> line;
				item = atoi(line.c_str());
				admin.mulTop(item);
				continue;
			}

			//除法操作
			else if(line == "D" || line == "d")
			{
				fileforread >> line;
				item = atoi(line.c_str());
				admin.divTop(item);
				continue;
			}
			//错误命令操作
			else
			{
				continue;
			}
		}
		else if(regex_match(line, out)){
			//如果是出栈操作那么执行下面操作
			admin.outStack();
		}
		else if (regex_match(line, quit)){
			//退出操作
			admin.quit();
			fileforread.close();//得到q的指令关闭文件
			break;
		}
		else {
			//如果没有相关的正则那么结束本次循环
			continue;
		}
	}
	system("pause");
	system("实验二-模式三-链栈结果文件.txt");
    return 0;
}