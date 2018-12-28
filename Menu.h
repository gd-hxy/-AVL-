#include<iostream>
#include<fstream>
#include<windows.h>
#include"userInfo.h"
#include"userTree.h"
#ifndef MENU
#define MENU
using namespace std;

class Menu
{
	private:
		userTree usertree;
	public:
		Menu();             //初始化
		void select();         //用户交互界面   
		void menuInput();      //用户登录验证函数 
		void menuInsert();
		void menuChange(Node *m);
		void menuDelete(Node *m);
		
};


Menu::Menu()
{
	ifstream inStream("userData.dat" ,ios::in|ios::binary);
	string userFile;
	userInfo user;
	getline(inStream, userFile);
	while(true)
	{
		if(inStream.eof())
			break;
		inStream >> user;                 //提取文件中的用户信息写入user变量中 
		usertree.insert(user);           //插入用户树 
	}
}

void Menu::select()
{
	system("cls");
	cout << "\t\t\t\t 欢迎使用用户登录系统！" << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "请选择您的操作：\n\n\n\n\n\n";
	cout << "\t\t\t\t 1.登录" << endl << endl;
	cout << "\t\t\t\t 2.注册" << endl << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\t\t 请输入操作对应的编号(1或2)" << endl;
	int num;
	input: cin >> num;
	switch(num)
	{
		case 1:
			{
				menuInput();                    //用户登录验证函数 
				break;
			}
		case 2:
			{
				menuInsert();                 //用户注册函数 
				break;
			}
		default:
			{
				cout << "错误的输入！请输入操作对应的编号(1或2)" << endl; 
				goto input;
			}
			
	}
}

void Menu::menuInput()
{
	system("cls");
	cout << "\t\t\t\t 欢迎进入用户登录页面！" << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\n\n\n\n            请输入用户名：";
	string id,password;
	cin >> id;
	cout << "\n\n\n\n            请输入密码：";
	cin >> password;
	userInfo user(id, password);
	cout << "\n\n\n\n";
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	
	system("cls");
	Node *ptr = new Node;
	if(usertree.search(user,ptr))
	{
		cout << "\t\t\t 登录成功！" << endl;
		for(int i = 0; i < 80; i++)
			cout << "*";
		cout << endl;
		cout << "\t\t\t 请选择你要进行的操作： \n\n\n\n\n\n";
		cout << "\t\t\t 1.更改密码" << endl << endl;
		cout << "\t\t\t 2.注销用户" << endl << endl;
		cout << "\t\t\t 3.退出" << endl << endl;
		for(int i = 0; i < 80; i++)
			cout << "*";
		cout << endl;
		cout << "\t\t 请输入操作对应的编号(1或2或3)" << endl;
		int num;
		input: cin >> num;
		switch(num)
		{
			case 1:
				{
					menuChange(ptr);                           //更改密码函数 
					break;
				}
			case 2:
				{
					menuDelete(ptr);                          //注销用户函数 
					break;
				}
			case 3:
				{
					cout << "系统将于3秒后退出"; 
					Sleep(3000);
					exit(0);
				}
			default:
				{
					cout << "错误的输入！请输入操作对应的编号(1或2)" << endl; 
					goto input;
				}
		}
	}
	else
	{
		cout << endl << endl;
		cout << "\t\t\t     用户名或密码错误！" << endl;
		 for(int i = 0; i < 80; i++)
			cout << "*";
		cout << endl;
		cout << "请选择您的操作：\n\n\n\n\n\n";
		cout << "\t\t\t\t 1.重新登录" << endl << endl;
		cout << "\t\t\t\t 2.注册" << endl << endl;
		for(int i = 0; i < 80; i++)
			cout << "*";
		cout << endl;
		cout << "\t\t 请输入操作对应的编号(1或2)" << endl;
		int num;
		_input: cin >> num;
		switch(num)
		{
			case 1:
				{
					menuInput();                    //用户登录验证函数 
					break;
				}
			case 2:
				{
					menuInsert();                 //用户注册函数 
					break;
				}
			default:
				{
					cout << "错误的输入！请输入操作对应的编号(1或2)" << endl; 
					goto _input;
				}
		}
	}
}

void Menu::menuInsert()
{
	system("cls");
	cout << "\t\t\t\t 欢迎进入用户注册页面！" << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\n\n\n\n            请输入新的用户名：";
	string id,password, con_password;
	cin >> id;
	cout << "\n\n\n\n            请输入新密码：";
	cin >> password;
	cout << "\n\n\n\n            请确认密码：";
	cin >> con_password;
	if(password != con_password)
	{
		cout <<"\n\n\n";
		for(int i = 0; i < 80; i++)
		{
			cout << "*";
		}
		cout << "\n\n          密码输入不一致，请重新注册！";
		Sleep(3000);
		menuInsert();
	}
	userInfo user(id, password);
	if(usertree.search(user))
	{
		system("cls");
		cout << "\t\t\t\t 该用户已被注册" << endl;
		for(int i = 0; i < 80; i++)
		{
			cout << "*";
		}
		cout << endl;
		cout << "\t\t\t 请选择你要进行的操作： \n\n\n\n\n\n";
		cout << "\t\t\t 1.返回登录菜单" << endl << endl;
		cout << "\t\t\t 2.重新注册" << endl << endl;
		for(int i = 0; i < 80; i++)
		{
			cout << "*";
		}
		cout << endl;
		cout << "\t\t 请输入操作对应的编号(1或2)" << endl;
		int num;
		sinput: cin >> num;
		switch(num)
		{
			case 1:
				{
					menuInput();                    //用户登录验证函数 
					break;
				}
			case 2:
				{
					menuInsert();                 //用户注册函数 
					break;
				}
			default:
				{
					cout << "错误的输入！请输入操作对应的编号(1或2)" << endl; 
					goto sinput;
				}
		}
	}
	else
	{
		user.writeMessage();
		usertree.insert(user);
		Sleep(3000);
		system("cls");
		cout << "\t\t\t  注册成功！" << endl;
		for(int i = 0; i < 80; i++)
		{
			cout << "*";
		}
		cout << endl;
		cout << "\t\t\t 请选择你要进行的操作： \n\n\n\n\n\n";
		cout << "\t\t\t 1.返回登录菜单" << endl << endl;
		cout << "\t\t\t 2.退出" << endl << endl;
		for(int i = 0; i < 80; i++)
		{
			cout << "*";
		}
		cout << endl;
		cout << "\t\t 请输入操作对应的编号(1或2)" << endl;
		int num;
		tinput: cin >> num;
		switch(num)
		{
			case 1:
				{
					menuInput();                    //用户登录验证函数 
					break;
				}
			case 2:
				{
					cout << "系统将于3秒后退出"; 
					Sleep(3000);
					exit(0);
				}
			default:
				{
					cout << "错误的输入！请输入操作对应的编号(1或2)" << endl; 
					goto tinput;
				}
		}
	}
}

void Menu::menuDelete(Node *ptr)
{
	system("cls");
	cout << "\t\t\t\t 欢迎进入用户注销页面！" << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\t\t\t 请选择你要进行的操作： \n\n\n\n\n\n";
	cout << "\t\t\t 1.注销当前用户" << endl << endl;
	cout << "\t\t\t 2.返回登录系统" << endl << endl;
	cout << "\t\t\t 3.退出" << endl << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\t\t 请输入操作对应的编号(1或3)" << endl;
	int num;
	bool low = false;
	finput: cin >> num;
	switch(num)
		{
			case 1:
				{
					usertree.AVL_delete(ptr, ptr -> data, low);
					break;                     
				}
			case 2:
				{
					menuInput();                          
					break;
				}
			case 3:
				{
					cout << "系统将于3秒后退出"; 
					Sleep(3000);
					exit(0);
				}
			default:
				{
					cout << "错误的输入！请输入操作对应的编号(1或3)" << endl; 
					 goto finput;
				}
		}
	system("cls");
	cout << "\t\t\t  删除成功！" << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\t\t\t 请选择你要进行的操作： \n\n\n\n\n\n";
	cout << "\t\t\t 1.返回主菜单" << endl << endl;
	cout << "\t\t\t 2.退出" << endl << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\t\t 请输入操作对应的编号(1或2)" << endl;
	xinput: cin >> num;
	switch(num)
	{
		case 1:
			{
				select();
				break;
			}
		case 2:
			{
				cout << "系统将于3秒后退出"; 
				Sleep(3000);
				exit(0);
			}
		default:
				{
					cout << "错误的输入！请输入操作对应的编号(1或2)" << endl; 
					goto xinput;
				}
	}
}

void Menu::menuChange(Node *ptr)
{
	system("cls");
	cout << "\t\t\t\t 欢迎进入密码修改页面！" << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\n\n\n\n            请输入原密码：";
	string password;
	cin >> password;
	if(!ptr -> compare(password))
	{
		system("cls");
		cout << "\n\n\n";
		for(int i = 0; i < 80; i++)
		{
			cout << "*";
		}
		cout << endl;
		cout << "\n\n            密码不正确，请重新输入！";
		menuChange(ptr);
	}
	string newPassword;
	cout << "\n\n\n\n            请输入新密码：";
	cin >> newPassword;
	ptr -> change(newPassword);
	system("cls");
	cout << "\t\t\t       修改密码成功！" << endl;
	for(int i = 0; i < 80; i++)
		{
			cout << "*";
		}
	cout << endl;
	cout << "\t\t\t 请选择你要进行的操作： \n\n\n\n\n\n";
	cout << "\t\t\t 1.返回主菜单" << endl << endl;
	cout << "\t\t\t 2.退出" << endl << endl;
	for(int i = 0; i < 80; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "\t\t 请输入操作对应的编号(1或2)" << endl;
	int num;
	einput: cin>>num;
	switch(num)
	{
		case 1:
			{
				select();
				break;
			}
		case 2:
			{
				cout << "系统将于3秒后退出"; 
				Sleep(3000);
				exit(0);
			}
		default:
			{
				cout << "错误的输入！请输入操作对应的编号(1或2)" << endl; 
				goto einput;
			}
	}
}
#endif
