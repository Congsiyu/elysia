#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include<stdlib.h>
#define MAX 10000//数据库最大容量
using namespace std;
string num2str(int i)//数字转字符串
{
	stringstream ss;
	ss << i;
	return ss.str();
}
class drugs//定义类
{
public:
	string num;//药品编号
	string name;//药品名称
	double money;//单价
	int fund;//库余量
	int mai;//销售量
	drugs()
	{
		fund = -1;
		money = 0;
		mai = 0;
	}
};
void xie(fstream& fs, drugs arr[])//刷新数据库
{
	fs.close();
	fs.open("data.txt", ios::out);
	for (int i = 1; arr[i].fund != -1; i++)
	{
		fs << arr[i].num << " " << arr[i].name << " " << arr[i].money << " " << arr[i].fund << endl;
	}
	fs.close();
	fs.open("data.txt", ios::in);

}
drugs* duqu(drugs sp[], fstream& file,int&i)//读取数据库
{
	string line;
	std::istringstream sin;
	getline(file, line);
	//string num;//药品编号
	//string name;//药品名称
	//double money;//单价
	//int fund;//库余量
	string cs;
	while (getline(file, line))
	{
		sin.str(line);
		getline(sin, cs, ',');//读取序号
		for (int k = 0; k < 5; k++)
		{
			getline(sin, cs, ',');
			if (k == 0)
			{
				sp[i].num = cs;
			}
			if (k == 1)
			{
				sp[i].name = cs;
			}
			if (k == 2)
			{
				stringstream ss;
				ss << cs;
				ss >> sp[i].money;
			}
			if (k == 3)
			{
				stringstream ss;
				ss << cs;
				ss >> sp[i].mai;
			}
		}
		sin.clear();
		i++;
	}
	return sp;
}
void temp(drugs *str[], int* st,int top)//登记当天销售记录
{
	/*fstream file;*/
	time_t now;
	now = time(NULL);
	struct tm* local;
	local = localtime(&now);
	string c = num2str(local->tm_year + 1900) + "年" + num2str(local->tm_mon + 1) + "月" + num2str(local->tm_mday) + "日销售记录.csv";
	fstream file;
	fstream ofile;
	file.open(c, ios::in);
	//file.open(c, ios::out );//建立或读取当天销售表格
	if (!file)
	{
		file.close();
		ofile.open(c, ios::out);
		ofile << "序号" << "," << "药品编号" << "," << "药品名称" << "," << "零售价" << "," << "销售量" << "," << "总销售额" << endl;
		ofile.close();
		file.open(c, ios::in);
	}
	drugs* sp = new drugs[MAX];
	int i = 1;
	sp=duqu(sp, file,i);
	
	for (int t = 1;t<top ; t++)
	{
		bool flag = 0;
		int p = 1;
		while (sp[p].money != 0)
		{
			if (sp[p].num == str[t]->num)
			{
				sp[p].mai += st[t];
				flag = 1;
				break;
			}
			p++;
		}
		if (!flag)
		{
			sp[i] = *str[t];
			sp[i++].mai = st[t];
		}
	}
	file.close();
	file.open(c, ios::out);
	file << "序号" << "," << "药品编号" << "," << "药品名称" << "," << "零售价" << "," << "销售量" << "," << "总销售额" << endl;
	for (int s = 1; s < i; s++)//按销售量从大到小排序
	{
		for (int k = 1; k < i - s; k++)
		{
			if (sp[k].mai < sp[k + 1].mai)
			{
				drugs temp = sp[k];
				sp[k] = sp[k + 1];
				sp[k + 1] = temp;
			}
		}
	}
	for (int nu = 1; sp[nu].money != 0; nu++)
	{
		file << nu << "," << sp[nu].num << "," << sp[nu].name << "," << sp[nu].money << "," << sp[nu].mai << "," << sp[nu].money * sp[nu].mai << endl;
	}
	delete[]sp;
}
bool sxx(fstream &fs)//工作界面
{
	

	string s;
	//string num;//药品编号
	//string name;//药品名称
	//double money;//单价
	//int fund;//库余量

	int count;
	drugs *arr=new drugs[MAX];
	for (int i = 1; i<MAX && fs >> s; i++)
	{
		arr[i].num = s;
		fs >> arr[i].name;
		fs >> arr[i].money;
		fs >> arr[i].fund;
	}
	cout << "请输入药品编号及购买数量：(可输入多组数据，回车后按‘#’结束)" << endl;
	cin >> s;
	drugs* str[100];
	int st[100] = { 0 };
	int i = 1, t = 1;
	while (s != "#")
	{
		cin >> count;
		for (i = 1; arr[i].fund != -1 && arr[i].num != s; i++) {}
		if (arr[i].fund == -1)
		{
			cout << "未搜索到对应药品，请检查您的输入是否有误   (请继续输入药品编号及购买数量)" << endl;
		}
		else
		{
			while (arr[i].fund < count)
			{
				cout << "当前库存不足，请重新输入购买药品数量,按'#'结束。当前库存：" << arr[i].fund << endl;
				cin >> count;
			}
			st[t] = count;
			str[t++] = &arr[i];
		}
		cin >> s;
	}
	cout << "购物清单如下:" << endl;
	cout << "\t\t\t\t*********************************************************" << endl;
	cout << "\t\t\t\t*编号\t\t名称\t\t单价\t\t数量 \t*" << endl;
	double tal = 0;
	for (int k = 1; k < t; k++)
	{
		cout << "\t\t\t\t*" << str[k]->num << "\t\t" << str[k]->name << "\t" << str[k]->money << "\t\t" << st[k] << "\t*" << endl;
		tal += str[k]->money * st[k];
	}
	tal = ((int)(tal * 100)) / 100.0;
	cout<< "\t\t\t\t*********************************************************" << endl;
	cout << "\t\t\t\t合计：" << tal << "元，是否确认支付(Y/N)：";
	char x;
	cin >> x;
	while (x != 'Y' && x != 'N')
	{
		cout << "输入格式错误，请重新输入!" << endl;
		cout << "是否确认支付(Y / N)：";
		cin >> x;
	}
	if (x == 'Y')
	{
		cout << "请输入收款金额：" << endl;
		double m;
		cin >> m;
		cout << "应找零：" << m - tal << "元" << endl;
		for (int k = 1; k < t; k++)
		{
			str[k]->fund -= st[k];
		}
		xie(fs, arr);
		temp(str, st,t);
	}
	else
	{
		cout << "订单已取消！" << endl;
	}
	cout << "请选择：1.继续    2.返回上一层" << endl;
	int c = 0;
	cin >> c;
	while (c != 1 && c != 2)
	{
		cout << "输入格式错误，请重新输入!" << endl;
		cout << "请选择：1.继续    2.返回上一层" << endl; 
		cin >> c;
	}
	if (c == 1)
	{
		fs.close();
		delete []arr;
		return 1;
	}
	else
	{
		delete[]arr;
		return 0;
	}
}
string zhuan(double value, int digits)//小数转字符串
{

	double val1 = value;
	double  resVal;

	val1 = value * pow(10, digits);

	resVal = int(val1);
	resVal = resVal / (pow(10, digits));



	ostringstream os;
	os << resVal;
	string result;
	istringstream is(os.str());
	is >> result;

	return result;
}
void chaxun(int days,fstream&fs)//查找往日记录
{
	time_t now;
	now = time(NULL);
	struct tm* local;
	local = localtime(&now);
	string c = num2str(local->tm_year + 1900) + "年" + num2str(local->tm_mon + 1) + "月" + num2str(local->tm_mday) + "日销售记录.csv";
	string x = to_string(days) + "日内销售总结(" + num2str(local->tm_year + 1900) + "." + num2str(local->tm_mon + 1) + "." + num2str(local->tm_mday) + " "+ num2str(local->tm_hour)+"."+ num2str(local->tm_min)+"."+ num2str(local->tm_sec)+").csv";
	time(&now);
	//local = localtime(&now);
	//cout << local->tm_mday;
	fstream file,ofile;
	file.open(x, ios::out);
	file << "序号" << "," << "药品编号" << "," << "药品名称" << "," << "零售价" << "," << "销售量" << "," << "总销售额"<<","<<"库余量" << endl;
	drugs* tol = new drugs[MAX];
	int lon = 1;
	for (int is = 0; is < days; is++)
	{
		ofile.open(num2str(local->tm_year + 1900) + "年" + num2str(local->tm_mon + 1) + "月" + num2str(local->tm_mday) + "日销售记录.csv", ios::in);
		if (ofile.is_open())
		{
			drugs* sp = new drugs[MAX];
			int i = 1;
			sp=duqu(sp, ofile, i);
			for (int k = 1; k < i; k++)
			{
				bool flag = 0;
				for (int t = 1; t < lon; t++)
				{
					if (tol[t].num == sp[k].num)
					{
						tol[t].mai += sp[k].mai;
						flag = 1;
						break;
					}
				}
				if (!flag)
				{
					tol[lon++] = sp[k];
				}
			}
		}
		ofile.close();
		now -= 24 * 60 * 60 * 1;
		local = localtime(&now);
	}
	int co = 0;
	cout << "请选择排序方式:1.按销售额从大到小排序    2.按销售量从大到小排序    3.按单价从大到小排序" << endl;
	cin >> co;
	if (co != 1 && co != 2&&co!=3)
	{
		cout << "输入格式错误，请重新输入:" << endl;
		cin >> co;
	}
	if(co==1)
	{ 
		for (int i = 1; i < lon; i++)//按销售额从大到小排序
		{
			for (int k = 1; k < lon -i; k++)
			{
				if (tol[k].mai * tol[k].money < tol[k + 1].mai * tol[k + 1].money)
				{
					drugs temp = tol[k];
					tol[k] = tol[k + 1];
					tol[k + 1] = temp;
				}
			}
		}
	}
	if (co == 2)
	{
		for (int i = 1; i < lon; i++)//按销售量从大到小排序
		{
			for (int k = 1; k < lon -i; k++)
			{
				if (tol[k].mai < tol[k + 1].mai)
				{
					drugs temp = tol[k];
					tol[k] = tol[k + 1];
					tol[k + 1] = temp;
				}
			}
		}
	}
	if (co == 3)
	{
		for (int i = 1; i < lon; i++)//按单价从大到小排序
		{
			for (int k = 1; k < lon -i; k++)
			{
				if (tol[k].money < tol[k + 1].money)
				{
					drugs temp = tol[k];
					tol[k] = tol[k + 1];
					tol[k + 1] = temp;
				}
			}
		}
	}
	string s;
	drugs* arr = new drugs[MAX];
	int i = 0;
	for ( i = 1; i<MAX && fs >> s; i++)//导入数据库
	{
		arr[i].num = s;
		fs >> arr[i].name;
		fs >> arr[i].money;
		fs >> arr[i].fund;
	}
	for (int k = 1; k < lon; k++)
	{
		bool flag = 0;
		for (int t = 1; t < i; t++)
		{
			if (tol[k].num == arr[t].num)
			{
				tol[k].fund = arr[t].fund;
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			cout << "编号:" << tol[k].num << "的药品已从数据库删除，当前无库存" << endl;
		}
	}
	for (int i = 1; i < lon; i++)
	{
		double x = tol[i].money * tol[i].mai;
		file << num2str(i) << "," << tol[i].num << "," << tol[i].name << "," << tol[i].money << "," << tol[i].mai << "," << zhuan(x, 2)<<","<<tol[i].fund<<endl;
	}
	cout << "生成成功" << endl;
	delete[]tol;
	file.close();
}
void start()//主界面
{


	fstream file;
	file.open("data.txt", ios::in);
	if (!file.is_open())//如果"data.txt"文件不存在
	{
		file.close();
		file.open("data.txt", ios::out);
		file.close();
		file.open("data.txt", ios::in);
	}
	char bbb;
	file >> bbb;
	if (file.eof())//判断数据库是否为空
	{
		file.close();
		file.open("data.txt", ios::out);
		cout << "检测到当前药品库为空，请输入药品库存信息:" << endl;
		cout << "请依次输入每种药品编号，药品名称，单价(元)，库余量(个)，回车后按‘#’结束" << endl;
		string num;//药品编号
		string name;//药品名称
		double money;//单价
		int fund;//库余量
		while (1)
		{
			cin >> num;
			if (num == "#")
			{
				break;
			}
			cin >> name >> money >> fund;
			file << num<<" "<< name << " " << money << " " << fund<<endl;
		}
		cout << "设置已完成！" << endl;
		file.close();
		file.open("data.txt", ios::in);
	}
	file.seekg(0, ios::beg);//回到文件开头
	int a=1;
	while (a != 4)
	{
		cout << "\t\t\t\t\t欢迎使用思雨药品销售统计系统" << endl;
		cout << "\t\t1.开始今日工作    2.销售总结导出    3.更改药品库    4.退出       (请输入序号执行对应操作)" << endl;
		cin >> a;
		while (a != 1 && a != 2 && a != 3 && a != 4)
		{
			cout << "您的输入不符合规范，请重新输入;" << endl;
			cin >> a;
		}
		int day = 0;
		string num;//药品编号
		string name;//药品名称
		double money;//单价
		int fund;//库余量
		switch (a)
		{
		case 1:
			while(sxx(file))
			{ 
				file.close();
				file.open("data.txt", ios::in);
			}
			break;
		case 2:
			cout << "您要查询最近多少天的销售情况：";
			cin >> day;
			chaxun(day, file);
			file.close();
			file.open("data.txt", ios::in);
			break;
		case 3:
			cout << "请依次输入每种药品编号，药品名称，单价(元)，库余量(个)，回车后按‘#’结束" << endl;
			file.close();
			file.open("data.txt", ios::out);
			while (1)
			{
				cin >> num;
				if (num == "#")
				{
					break;
				}
				cin >> name >> money >> fund;
				file << num << " " << name << " " << money << " " << fund << endl;
			}
			cout << "设置已完成！" << endl;
			file.close();
			file.open("data.txt", ios::in);
			break;
		case 4:
			file.close();
			cout << "欢迎下次使用" << endl;
			return;
		}
	}
}
int main()
{
	start();
	return 0;
}
