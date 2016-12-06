// ջ�Ĳ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h" //VS������������ͷ�ļ� VC6.0������ɾ����ͷ�ļ�
#include "iostream"
#include "fstream"
#include "string"
#include "iomanip"
#include "regex" //������ʽͷ�ļ�
#define STACKSIZE 10 //ջ��С
#define FAIL 0 //����ʧ��
#define SUCCESS 1 //�����ɹ�
#define QUIT -1 //�˳�

using namespace std;
//˫����ջ��
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



//ջ������
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
	//ָ��ջ��
	top = base;
	stacksize = 0;
	fileforwrite.open("ʵ���-ģʽ��-��ջ����ļ�.txt", ios::out);
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
	top->next = newstack;//��ջ
	newstack->pre = top;
	top = top->next;//top�ƶ����µ�ջ��
	stacksize++;
	return SUCCESS;
}

int Admin::outStack()
{
	if (isEmpty())
		return FAIL;
	fileforwrite << top->data << setw(10);//д���ļ�
	top = top->pre;//topǰ�ƣ�׼����ջ
	delete top->next;//��ջ
	top->next = NULL;
	stacksize--;
	return SUCCESS;
}

//�˳�����
void Admin::quit()
{
	//�ر��ļ�
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
	system("title ʵ���-ģʽ��-��ջ����ļ�");
	system("color f0");
	Admin admin;
	string line;//���ڶ�ȡ�ַ���
	int item;

	//������ʽ�Ĵ���
	//regex number("^[0-9]{1,}$");//ƥ������0-9һ�λ���������ջ������
	regex in("^[I|i]{1}$");//ƥ����ջ���� ^[I|i]{1}$ ƥ���ַ��������ַ�����I��i��ͷ�ҽ�β I��i������һ��
	regex out("^[O|o]{1}$");//ƥ���ջ���� ^[O|o]{1}$ ƥ���ַ��������ַ�����O��o��ͷ�ҽ�β O��o������һ��
	regex quit("^[Q|q]{1}$");//ƥ���˳��Ĳ��� ^[Q|q]{1}$ ƥ���ַ��������ַ�����Q��q��ͷ�ҽ�β Q��q������һ��
	regex astd("^[A|a|S|s|T|t|D|d]{1}$");//��ջ�����мӼ��˳� ƥ���ַ��������ַ��������������ַ�������ֻ�ܳ���һ�Σ�AaSsTtDd��
	
	fstream fileforread("��������ģ3��3ջ��չ.txt", ios::in);
	while (!fileforread.eof())
	{
		fileforread >> line;//��ȡ�ļ�
		if (regex_match(line, in)) {
			//�������ջ������ôִ���������
			fileforread >> line;//����һ���ַ���
			item = atoi(line.c_str());//���ַ���ת��Ϊ����
			admin.inStack(item);//׼����ջ
		}
		else if (regex_match(line, astd)){
			//����ǼӼ��˳�������ôִ���������

			//�ӷ�����
			if (line == "A" || line == "a") {
				fileforread >> line;
				item = atoi(line.c_str());
				admin.addTop(item);
				continue;
			}

			//��������
			else if (line == "S" || line == "s")
			{
				fileforread >> line;
				item = atoi(line.c_str());
				admin.subTop(item);
				continue;
			}

			//�˷�����
			else if (line == "T" || line == "t")
			{
				fileforread >> line;
				item = atoi(line.c_str());
				admin.mulTop(item);
				continue;
			}

			//��������
			else if(line == "D" || line == "d")
			{
				fileforread >> line;
				item = atoi(line.c_str());
				admin.divTop(item);
				continue;
			}
			//�����������
			else
			{
				continue;
			}
		}
		else if(regex_match(line, out)){
			//����ǳ�ջ������ôִ���������
			admin.outStack();
		}
		else if (regex_match(line, quit)){
			//�˳�����
			admin.quit();
			fileforread.close();//�õ�q��ָ��ر��ļ�
			break;
		}
		else {
			//���û����ص�������ô��������ѭ��
			continue;
		}
	}
	system("pause");
	system("ʵ���-ģʽ��-��ջ����ļ�.txt");
    return 0;
}