
#include <windows.h>
#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string>
#include <iostream>
#include <winsock.h>
#include <mysql.h>

#pragma warning(disable: 4996)

using namespace std;
MYSQL* con;
MYSQL_RES* res;
MYSQL_ROW row;
MYSQL conn;
char cmd[500] = {};

void connection()
{
	char dbuser[30] = "root";
	char dbpasswd[30] = "123456";
	char dbip[30] = "localhost";
	char dbname[50]="student";
	char* query = NULL;

	con = mysql_init((MYSQL*)0);//初始化
	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0))
		cout << "数据库链接成功！";
	else
		cout << "数据库链接失败！";
	cout << "\n";
	//system("pause");    //press any key to exit  //system用来调用系统命令，类似于shell;
	mysql_query(con, "set names GBK");//mysql_query()发送一条 MySQL 指令查询。
	if (mysql_query(con, "show tables")) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}
	res = mysql_use_result(con);
}

void shouye(int &m0) 
{
	system("cls");
	cout << "\n"<<"\n"<<"\n"<<"*************************************************************"<<"\n";
	cout << "                   1.显示数据库中所有列表" << "\n";
	cout << "                   2.删除表" << "\n";
	cout << "                   3.新建表" << "\n";
	cout << "                   4.按条件查询" << "\n";
	cout << "                   5.录入信息" << "\n";
	cout << "                   6.信息的修改与删除" << "\n";
	cout << "                   7.录入信息" << "\n";
	cout << "                   8.退出" << "\n";
	cout << "*************************************************************" << "\n";
	cin >> m0 ;
}


void one(int& m1)
{
	system("cls");
	connection();
	cout << "数据库中列表信息： \n";

	while ((row = mysql_fetch_row(res)) != NULL)
		cout << row[0] << "\n";
	mysql_free_result(res);
	system("pause");
}

bool two()
{
	
	connection();
	char mingling[500] = {};
	char* dname;
	mysql_free_result(res);
	cout << "请输入要删除的表名：" << endl;
	cin >> mingling;
	strcpy_s(cmd, "set names utf8");
	sprintf_s(cmd,"drop table `%s`;" ,mingling);
	if (mysql_query(con,cmd))
	{
		// 打错误log，这里直接显示到控制台
		cerr << "执行sql语句失败，错误信息为： " << mysql_error(con) << endl;
		system("pause");
		cin.clear();
		cin.ignore(1000, '\n');
		return false;
	}
	else
	{
		cout << "执行sql语句成功！" << endl;
	}
	system("pause");
	cin.clear();
	cin.ignore(1000, '\n');
	return true;

}

 bool three()
{
	connection();
	mysql_free_result(res);
	char nname[500] = {};
	cout << "输入创建表名：" << endl;
	cin.clear();
	cin.ignore(1000, '\n');
	cin.getline(nname, 500);
	if (mysql_query(con, nname))
	{
		// 打错误log，这里直接显示到控制台
		cerr << "执行sql语句失败，错误信息为： " << mysql_error(con) << endl;
		system("pause");
		return false;
	}
	else
	{
		cout << "执行sql语句成功！" << endl;
	}
	system("pause");
	return true;
	
}

void four()
{
	system("cls");
	cout << "\n" << "\n" << "\n" << "\n" << endl;
	char cx[500] = {}; //查询限定条件
	string cx1[10]; 
	int df;  //用来判断执行有无条件查询
	char cha1[200];
	char cha2[100];
	char cha3[500];
	connection();
	mysql_free_result(res);

	cin.clear();
	cin.ignore(1000, '\n');
	cout << "1.无条件查询" << endl;
	cout << "2.有条件查询" << endl;
	cin >> df;
	if (df == 1)
	{
		cout << "请输入查询的表名：" << endl;
		cin >> cha2;
		cout << "请输入查询的列(查询所有的列请输入*)：" << endl;
		cin >> cha1;
		sprintf_s(cx, "select %s from %s", cha1, cha2);
	}
	else if (df == 2)
	{
		cout << "请输入查询的表名：" << endl;
		cin >> cha2;
		cout << "请输入查询的列(查询所有的列请输入*)：" << endl;
		cin >> cha1;
		cout << "输入查询条件：" << endl;
		cin >> cha3;
		sprintf_s(cx,"select %s from %s where %s", cha1, cha2, cha3);
	}


	if (mysql_query(con, cx))
	{
		// 打错误log，这里直接显示到控制台
		cerr << "执行sql语句失败，错误信息为： " << mysql_error(con) << endl;
		system("pause");
	}
	else
	{
		cout << "执行sql语句成功！" << endl;
	}

	res = mysql_use_result(con);
	int N = mysql_num_fields(res); //获取列数
	char* str[20];
	printf("查询结果：\n");
	for (int i = 0; i < N; i++)
	{
		str[i] = mysql_fetch_field(res)->name;//获取列名
		printf("   %s    ", str[i]);//打印列名
	}
	printf("\n");
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		
		for (int i = 0;i<N; i++)
		{
			printf(" %s    ", row[i]);
		}
		cout << "\n";
	}
	
	system("pause");
	mysql_free_result(res);
}

void five()
{
	char luru[500] = {}; //录入信息操作指令
	connection();
	mysql_free_result(res);
	char sj1[20];
	char sj2[20];
	char sj3[20];
	char sj4[20] = {};
	char sj5[10];
	char sj6[40] = {};
	char sj7[20] = {};
	char sj8[40] = {};
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "请依次输入插入信息(学号，姓名，年龄，性别，出生年月，地址，电话)：" << "\n";
	cin >> sj1;
	cin >> sj2;
	cin >> sj3;
		cin>> sj4>> sj5>> sj6 >> sj7>> sj8;
	sprintf_s(luru, "insert into student values('%s','%s','%s','%s','%s','%s','%s','%s'')", sj1, sj2, sj3,sj4,sj5,sj6,sj7,sj8);
	//cin.getline(luru);
	if (mysql_query(con, luru))
	{
		// 打错误log，这里直接显示到控制台
		cerr << "执行sql语句失败，错误信息为： " << mysql_error(con) << endl;
		system("pause");
	}
	else
	{
		cout << "执行sql语句成功！" << endl;
	}
	system("pause");
}

void seven()
{
	char luru[500] = {}; //录入信息操作指令
	connection();
	mysql_free_result(res);
	char sj1[20];
	char sj2[20];
	char str[30];
	char sj3[50];
	int sj4;
	int sj5;
	cout << "请依次输入(学号，姓名，成绩)" << endl;
	cin >> sj1;
	cin >> sj2;
	cin >> sj3;
	cin >> sj4;
	cin >> sj5;
	/*if (sj3<0 || sj3>100)
	{
		cout << "输入成绩不规范,请重新输入。"<<endl;
		seven();
	}
	/*
	*/
	/*else if (sj3 >= 0 && sj3 <= 100)
	{*/
		sprintf_s(luru, "insert into grades values('%s','%s','%d')", sj1, sj2, sj3);
		if (mysql_query(con, luru))
		{
			// 打错误log，这里直接显示到控制台
			cerr << "执行sql语句失败，错误信息为： " << mysql_error(con) << endl;
			system("pause");
		}
		else
		{
			cout << "执行sql语句成功！" << endl;
		}
		system("pause");
	/*}
	else
	{
		cout << "输入不合法，请重试!" << endl;
		seven();
	}*/
}

void six()
{
	char xiugai[500];
	char xg1[50];
	char xg2[50];
	char xg3[50];
	int as;
	cout << "请输入要修改的表名：" << endl;
	cin >> xg1;
	cout << "\n" << "\n";
	cout << "1.删除数据" << endl;
	cout << "2.有条件修改数据" << endl;
	cout << "3.修改整列" << endl;
	cin >> as;
	if (as == 1)
	{
		cout << "请输入删除条件(列名='值',列名='值'例如:学号='201727100')：" << endl;
		cin >> xg2;
		sprintf_s(xiugai, "delete from %s where %s", xg1, xg2);
	}
	else if (as == 2)
	{
		cout << "请输入修改的数据(列名='值',列名='值'例如:学号='201727100'或年龄=年龄+2)：" << endl;
		cin >> xg2;
		cout << "请输入修改查询的条件(同上)：" << endl;
		cin >> xg3;
		sprintf_s(xiugai, "update %s set %s where %s", xg1, xg2, xg3);
	}
	else if (as == 3)
	{
		cout << "请输入修改的数据(列名='值',列名='值'例如:学号='201727100'或年龄=年龄+2)：" << endl;
		cin >> xg2;
		sprintf_s(xiugai, "update %s set %s where %s", xg1, xg2);
	}
	
	
	if (mysql_query(con, xiugai))
	{
		// 打错误log，这里直接显示到控制台
		cerr << "执行sql语句失败，错误信息为： " << mysql_error(con) << endl;
		system("pause");
	}
	else
	{
		cout << "执行sql语句成功！" << endl;
	}
}


int main()
{
	char cmd[500] = {};
	int m;
	int sd;
	//database configuartion
	//res = mysql_use_result(con);

	while(1)
	{
		fflush(stdin);
		shouye(m);
		if (m == 1)
		{
			while (1)
			{
				fflush(stdin);//清除缓存区
				char c;
				cout << "按任意键继续，按ESC退出：" << endl;
				c = getch(); //conio.h中
				if (27 == c)
				{
					break;
				}
				else
					one(m);
			}
		}
		else if (m == 2)
		{
			while (1)
			{
				fflush(stdin);//清除缓存区
				char c;
				cout << "按任意键继续，按ESC退出：" << endl;
				c = getch(); //conio.h中
				if (27 == c)
				{
					break;
				}
				else
					two();
			}
		}
		else if (m == 3)
		{
			while (1)
			{
				fflush(stdin);//清除缓存区
				char c;
				cout << "按任意键继续，按ESC退出：" << endl;
				c = getch(); //conio.h中
				if (27 == c)
				{
					break;
				}
				else
					three();
			}
		}
		else if (m == 4)
		{
			//按ESC(ascii为27)则退出
			while (1)
			{
				fflush(stdin);//清除缓存区
				char c;
				cout << "按任意键继续，按ESC退出：" << endl;
				c=getch(); //conio.h中
				if (27 ==c)
				{
					break;
				}
				else
					four();
			}
		}
		else if (m == 5)
		{
			while (1)
			{
				fflush(stdin);//清除缓存区
				char c;
				cout << "按任意键继续，按ESC退出：" << endl;
				c = getch(); //conio.h中
				if (27 == c)
				{
					break;
				}
				else
					five();
			}
		}
		else if (m == 6)
		{
			while (1)
			{
				fflush(stdin);//清除缓存区
				char c;
				cout << "按任意键继续，按ESC退出：" << endl;
				c = getch(); //conio.h中
				if (27 == c)
				{
					break;
				}
				else
					six();
				cout << "按任意键继续，按ESC退出：" << endl;
				c = getch(); //conio.h中
				if (27 == c)
				{
					break;
				}
			}
		}
		else if (m == 7)
		{
			while (1)
			{
				fflush(stdin);//清除缓存区
				char c;
				cout << "按任意键继续，按ESC退出：" << endl;
				c = getch(); //conio.h中
				if (27 == c)
				{
					break;
				}
				else
					seven();
			}
		}
		else
		{
			cout << "您确定要退出么?(退出请按ESC，按任意键继续)"<<endl;
				sd=getch();
				if (27 == sd)
					break;
				else
					continue;

					
		}
		
			

	}
	fflush(stdin);//清除缓存区
	cin.clear();
	cin.ignore(1000, '\n');
	mysql_close(con);
	return 0;
}