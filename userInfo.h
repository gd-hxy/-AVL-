#include<fstream>
#include<string>
#include<iostream>
using namespace std;

#ifndef USERINFO
#define USERINFO

class userInfo
{
	private:
		string myId, myPassword;
	
	public:
		userInfo(){};
		userInfo(string id, string password):myId(id), myPassword(password){}
		
		string getId() const //get方法 
		{
			return myId;
		}
		
		void output(ostream & out)
		{
			out << myId <<" " << myPassword << endl;
		}
		
		void writeMessage()            //将用户信息记录 
		{
			ofstream out;
			out.open("userData.dat", ios::app|ios::binary);
			if(out.fail())
			{
				cout << "写入用户信息失败！" << endl;
				exit(0);          //中断错误进程 
			}
			out << myId << " " << myPassword << endl;
			for(int i = 0; i < 80; i++)
				cout << "*";
			cout << endl;
			cout << "用户信息保存成功" << endl << "将于3秒后返回主菜单";
			out.close(); 
		}
		
		void changePassword (string & password)
		{
			myPassword = password;
		}
		
		bool comparePassword (string & password)
		{
			return myPassword == password;
		}
		//----------------------------运算符重载-------------------------------------------- 
		
		bool operator==(const userInfo &userinfo) const //校验用户名、密码 
		{
			return myId == userinfo.myId && myPassword == userinfo.myPassword;
		}
		
		bool operator==(const string s) const
		{
			return myId == s;
		}
		
		bool operator < (const userInfo &userinfo) const
		{
			return myId < userinfo.myId || myId == userinfo.myId && myPassword < userinfo.myPassword;
		}
		
		bool operator < (const string &id)
		{
			return myId < id;
		}
		
		friend istream &operator >>(istream &in, userInfo &userinfo)
		{
			in >> userinfo.myId >> userinfo.myPassword;
			return in;
		}
		
		
		
};
#endif
