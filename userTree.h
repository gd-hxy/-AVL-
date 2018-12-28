#include<iostream>
#include<string>
#include<new>
#include "userInfo.h"
#ifndef USERTREE
#define USERTREE
using namespace std;

class Node
{
	public:
		userInfo data;
		int balance; //平衡结点的参数
		Node* left;
		Node* right;
		
		Node():balance(0),left(NULL),right(NULL){};
		Node(userInfo user):data(user),balance(0),left(NULL), right(NULL){};
		bool compare(string& password)
		{
			return data.comparePassword(password);
		}
		
		void change(string& password)
		{
			data.changePassword(password);
		}
};

class userTree
{
	private:
		Node *root;
		void inorderAux(ostream& out, Node subtreeRoot) const;
		bool searchAux(const userInfo & user, Node*& ptr) const
		{
			Node *locptr = root;
			bool found = false;
			while(!found && locptr != NULL)
			{
				if(user < locptr -> data)
				{
					locptr = locptr -> left;
				} 
				else if(user == locptr -> data)
				{
					found = true;
					ptr = locptr;
				}
				else
					locptr = locptr -> right;
			}
			return found;
		}
		
		void R_roate(Node *& Rptr)           //右旋操作 
		{
			Node *temp = Rptr -> left;
			Rptr -> left = temp -> right;
			temp -> right = Rptr;
			Rptr = temp;
		}
		/*
		 *    Rptr ->  *                   *
		 *           /                   /   \ 
		 *  temp -> *         ===>      *     *
		 *        /
		 *       *
		 *
		 **/
		
		void L_roate(Node *& Rptr)            //左旋操作 
		{                                     
			Node *temp = Rptr -> right;
			Rptr -> right = temp -> left;
			temp -> left = Rptr;
			Rptr = temp;
		}
		/*
		 *    Rptr ->  *                   *
		 *              \                /   \ 
		 *      temp ->  *    ===>      *     *
		 *                \
		 *                 *
		 *
		 **/
		
		void L_balance(Node *& Rptr)            //左平衡操作 
		{
			Node *lc = NULL;
			Node *rc = NULL;
			lc = Rptr -> left;
			switch(lc -> balance)
			{
				case 1:
					Rptr -> balance = 0;
					lc -> balance = 0;
					R_roate(Rptr);
					break;
				case 0:          //删除结点时用于平衡
					Rptr -> balance = 1;
					lc -> balance = -1;
					R_roate(Rptr);
					break;
				case -1:
					rc = lc -> right;
					switch(rc -> balance)
					{
						case 1:
							Rptr -> balance = -1;
							lc -> balance = 0;
							break;
						case 0:
							Rptr -> balance = 0;
							lc -> balance = 0;
							break;
						case -1:
							Rptr -> balance = 0;
							lc -> balance = 1;
							break;
					} 
				rc -> balance = 0;
				L_roate(Rptr -> left);
				R_roate(Rptr);
				break;	
			}
		}
		
		void R_balance(Node *& Rptr)
		{
			Node *rc = NULL;
			Node *lc = NULL;
			
			rc = Rptr -> right;
			switch(rc -> balance)
			{
				case 1:                            //RL旋转 
					lc = rc -> left;
					switch(lc -> balance)
					{
						case 1:
							Rptr -> balance = 0;
							rc -> balance = 1;
							break;
						case 0:
							Rptr -> balance = 0;
							rc -> balance = 0;
							break;
						case -1:
							Rptr -> balance = 1;
							rc -> balance = 0;
							break;
					}
					lc -> balance = 0;
					R_roate(Rptr -> right);
					L_roate(Rptr);
					break;
				case 0:
					Rptr -> balance = -1;
					rc -> balance = 1;
					L_roate(Rptr);
					break;
				case -1:                          //RR旋转
					Rptr -> balance = 0;
					rc -> balance = 0;
					L_roate(Rptr);
					break; 
			}
		}
		
		bool AVL_build(Node *& t, userInfo &item, bool &flag)
		{
			if(t == NULL)
			{
				t = new Node(item);         //用户列表为空则直接插入 
				flag = true;
			} else{
				if(item == t -> data)      //若用户已存在，则不插入 
				{
					flag = false;
					return false;
				}
				else if(item < t -> data)  //在左子树中寻找插入点 
				{
					if(!AVL_build(t -> left, item, flag)) //左子树插入失败 
						return false;
					if(flag)                             //左子树插入成功 
					{
						switch(t -> balance)
						{
							case 1:                     //原先t的左子树高于右子树
								L_balance(t);          //左平衡处理 
								flag = false;
								break;
							case 0:                   //左右子树等高 
								t -> balance = 1;     //左子树插入后比右子树高了，所以变为1
								flag = true;
								break;
							case -1:                  //原先t的右子树高于左子树
								t -> balance = 0;      //左子树插入后，左右子树等高
								flag = false;
								break; 
								 
						}
					}
				}
				else                                       //在右子树中寻找插入点 
				{
					if(!AVL_build(t -> right, item, flag))
						return false;
					if(flag)
					{
						switch(t -> balance)
						{
							case 1:                       //原先t的左子树高于右子树 
								t -> balance = 0;         //右子树插入后，左右等高
								flag = false;
								break;
							case 0:                       //原先左右子树等高
								t -> balance = -1;        //右子树插入后比左子树高了，所以变为-1；
								flag = true;
								break; 
							case -1:                      //原先t的右子树高于左子树 
								R_balance(t);             //右平衡处理
								flag = false;
								break; 
						}
					}
				}
			}
			return true;                                   //返回插入成功的信号 
		}
		
		int AVL_deleteAux(Node*& t, userInfo data, bool &low)
		{
			Node *d1, *d2;                             
			int tag = 0;                      //删除标志
			int flag = 0;
			if(!t)                           //用户树可能为空 
			{
				return 0;
			}
			if(data == t -> data)        //找到要删除的结点 
			{
				low = true;                 //标记为成功删除 
				if(t -> right == NULL)      //如果被删除的结点没有右子结点
				{
					d1 = t;
					t = t -> left;
					delete d1;
					return 1;              //左子树平衡，无需平衡操作 
				} 
				else
				{
					d1 = t -> right;
					while(d1 -> left != NULL)                 //寻找删除结点右子树的最左的结点 
					{
						d1 = d1 -> left;
					}
					t -> data = d1 -> data;
					flag = AVL_delete(t -> right, d1 -> data, low);
					tag = -1;
				}
			}
			else if(data < t -> data)
			{
				flag = AVL_delete(t -> left, data, low);
				tag = 1;
			}
			else
			{
				flag = AVL_delete(t -> right, data, low);
				tag = -1;
			}
			if(low == true)                            //用户树中确实存在过结点 
			{
				if(tag == 1)                          //要删除的结点位于左子树 
				{
					switch(t -> balance)
					{
						case 1:                              //原先左子树比右子树高，删除后balance为0 
							{
								t -> balance = 0;
								low = true;
								break;
							}
						case 0:
							{
								t -> balance = -1;
								low = false;
								break;
							}
						case -1:                             //因为本身右子树就比左子树高，再删除左子树会导致不平衡 
							{
								R_balance(t);
								low = true;
								break; 
							}
					}
				}
				else                                           //删除右子树 
				{
					switch(t -> balance)
					{
						case 1:                              //因为本身左子树就比右子树高，再删除右子树会导致不平衡 
							{
								L_balance(t);
								low = true;
								break;
							}
						case 0:
							{
								t -> balance = 1;
								low = false;
								break;
							}
						case -1:
							{
								t -> balance = 0;
								low = true;
								break;
							}
					}
				}
			}
			return flag;
		}
	
	public:
		userTree():root(0){}
		bool empty() const
		{
			return root == 0;
		}
		bool search(const userInfo &user, Node*& ptr) const  
		{                                                                 
			searchAux(user, ptr);                       
		}
		bool search(const userInfo &user) const
		{
			Node *locptr = root;
			bool found = false;
			while(!found && locptr != NULL)
			{
				if(user < locptr -> data)
				{
					locptr = locptr -> left;
				} 
				else if(user == locptr -> data)
				{
					found = true;
				}
				else
					locptr = locptr -> right;
			}
			return found;
		}
		void insert(userInfo &item)
		{
			bool flag = true;
			AVL_build(root, item, flag);
		}
		int AVL_delete(Node*& t, userInfo data, bool &low)
		{
			AVL_deleteAux(t, data, low);
		}             
};

#endif
