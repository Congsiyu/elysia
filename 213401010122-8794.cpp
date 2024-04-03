#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include<stdlib.h>
#define MAX 10000//���ݿ��������
using namespace std;
string num2str(int i)//����ת�ַ���
{
	stringstream ss;
	ss << i;
	return ss.str();
}
class drugs//������
{
public:
	string num;//ҩƷ���
	string name;//ҩƷ����
	double money;//����
	int fund;//������
	int mai;//������
	drugs()
	{
		fund = -1;
		money = 0;
		mai = 0;
	}
};
void xie(fstream& fs, drugs arr[])//ˢ�����ݿ�
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
drugs* duqu(drugs sp[], fstream& file,int&i)//��ȡ���ݿ�
{
	string line;
	std::istringstream sin;
	getline(file, line);
	//string num;//ҩƷ���
	//string name;//ҩƷ����
	//double money;//����
	//int fund;//������
	string cs;
	while (getline(file, line))
	{
		sin.str(line);
		getline(sin, cs, ',');//��ȡ���
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
void temp(drugs *str[], int* st,int top)//�Ǽǵ������ۼ�¼
{
	/*fstream file;*/
	time_t now;
	now = time(NULL);
	struct tm* local;
	local = localtime(&now);
	string c = num2str(local->tm_year + 1900) + "��" + num2str(local->tm_mon + 1) + "��" + num2str(local->tm_mday) + "�����ۼ�¼.csv";
	fstream file;
	fstream ofile;
	file.open(c, ios::in);
	//file.open(c, ios::out );//�������ȡ�������۱��
	if (!file)
	{
		file.close();
		ofile.open(c, ios::out);
		ofile << "���" << "," << "ҩƷ���" << "," << "ҩƷ����" << "," << "���ۼ�" << "," << "������" << "," << "�����۶�" << endl;
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
	file << "���" << "," << "ҩƷ���" << "," << "ҩƷ����" << "," << "���ۼ�" << "," << "������" << "," << "�����۶�" << endl;
	for (int s = 1; s < i; s++)//���������Ӵ�С����
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
bool sxx(fstream &fs)//��������
{
	

	string s;
	//string num;//ҩƷ���
	//string name;//ҩƷ����
	//double money;//����
	//int fund;//������

	int count;
	drugs *arr=new drugs[MAX];
	for (int i = 1; i<MAX && fs >> s; i++)
	{
		arr[i].num = s;
		fs >> arr[i].name;
		fs >> arr[i].money;
		fs >> arr[i].fund;
	}
	cout << "������ҩƷ��ż�����������(������������ݣ��س��󰴡�#������)" << endl;
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
			cout << "δ��������ӦҩƷ���������������Ƿ�����   (���������ҩƷ��ż���������)" << endl;
		}
		else
		{
			while (arr[i].fund < count)
			{
				cout << "��ǰ��治�㣬���������빺��ҩƷ����,��'#'��������ǰ��棺" << arr[i].fund << endl;
				cin >> count;
			}
			st[t] = count;
			str[t++] = &arr[i];
		}
		cin >> s;
	}
	cout << "�����嵥����:" << endl;
	cout << "\t\t\t\t*********************************************************" << endl;
	cout << "\t\t\t\t*���\t\t����\t\t����\t\t���� \t*" << endl;
	double tal = 0;
	for (int k = 1; k < t; k++)
	{
		cout << "\t\t\t\t*" << str[k]->num << "\t\t" << str[k]->name << "\t" << str[k]->money << "\t\t" << st[k] << "\t*" << endl;
		tal += str[k]->money * st[k];
	}
	tal = ((int)(tal * 100)) / 100.0;
	cout<< "\t\t\t\t*********************************************************" << endl;
	cout << "\t\t\t\t�ϼƣ�" << tal << "Ԫ���Ƿ�ȷ��֧��(Y/N)��";
	char x;
	cin >> x;
	while (x != 'Y' && x != 'N')
	{
		cout << "�����ʽ��������������!" << endl;
		cout << "�Ƿ�ȷ��֧��(Y / N)��";
		cin >> x;
	}
	if (x == 'Y')
	{
		cout << "�������տ��" << endl;
		double m;
		cin >> m;
		cout << "Ӧ���㣺" << m - tal << "Ԫ" << endl;
		for (int k = 1; k < t; k++)
		{
			str[k]->fund -= st[k];
		}
		xie(fs, arr);
		temp(str, st,t);
	}
	else
	{
		cout << "������ȡ����" << endl;
	}
	cout << "��ѡ��1.����    2.������һ��" << endl;
	int c = 0;
	cin >> c;
	while (c != 1 && c != 2)
	{
		cout << "�����ʽ��������������!" << endl;
		cout << "��ѡ��1.����    2.������һ��" << endl; 
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
string zhuan(double value, int digits)//С��ת�ַ���
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
void chaxun(int days,fstream&fs)//�������ռ�¼
{
	time_t now;
	now = time(NULL);
	struct tm* local;
	local = localtime(&now);
	string c = num2str(local->tm_year + 1900) + "��" + num2str(local->tm_mon + 1) + "��" + num2str(local->tm_mday) + "�����ۼ�¼.csv";
	string x = to_string(days) + "���������ܽ�(" + num2str(local->tm_year + 1900) + "." + num2str(local->tm_mon + 1) + "." + num2str(local->tm_mday) + " "+ num2str(local->tm_hour)+"."+ num2str(local->tm_min)+"."+ num2str(local->tm_sec)+").csv";
	time(&now);
	//local = localtime(&now);
	//cout << local->tm_mday;
	fstream file,ofile;
	file.open(x, ios::out);
	file << "���" << "," << "ҩƷ���" << "," << "ҩƷ����" << "," << "���ۼ�" << "," << "������" << "," << "�����۶�"<<","<<"������" << endl;
	drugs* tol = new drugs[MAX];
	int lon = 1;
	for (int is = 0; is < days; is++)
	{
		ofile.open(num2str(local->tm_year + 1900) + "��" + num2str(local->tm_mon + 1) + "��" + num2str(local->tm_mday) + "�����ۼ�¼.csv", ios::in);
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
	cout << "��ѡ������ʽ:1.�����۶�Ӵ�С����    2.���������Ӵ�С����    3.�����۴Ӵ�С����" << endl;
	cin >> co;
	if (co != 1 && co != 2&&co!=3)
	{
		cout << "�����ʽ��������������:" << endl;
		cin >> co;
	}
	if(co==1)
	{ 
		for (int i = 1; i < lon; i++)//�����۶�Ӵ�С����
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
		for (int i = 1; i < lon; i++)//���������Ӵ�С����
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
		for (int i = 1; i < lon; i++)//�����۴Ӵ�С����
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
	for ( i = 1; i<MAX && fs >> s; i++)//�������ݿ�
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
			cout << "���:" << tol[k].num << "��ҩƷ�Ѵ����ݿ�ɾ������ǰ�޿��" << endl;
		}
	}
	for (int i = 1; i < lon; i++)
	{
		double x = tol[i].money * tol[i].mai;
		file << num2str(i) << "," << tol[i].num << "," << tol[i].name << "," << tol[i].money << "," << tol[i].mai << "," << zhuan(x, 2)<<","<<tol[i].fund<<endl;
	}
	cout << "���ɳɹ�" << endl;
	delete[]tol;
	file.close();
}
void start()//������
{


	fstream file;
	file.open("data.txt", ios::in);
	if (!file.is_open())//���"data.txt"�ļ�������
	{
		file.close();
		file.open("data.txt", ios::out);
		file.close();
		file.open("data.txt", ios::in);
	}
	char bbb;
	file >> bbb;
	if (file.eof())//�ж����ݿ��Ƿ�Ϊ��
	{
		file.close();
		file.open("data.txt", ios::out);
		cout << "��⵽��ǰҩƷ��Ϊ�գ�������ҩƷ�����Ϣ:" << endl;
		cout << "����������ÿ��ҩƷ��ţ�ҩƷ���ƣ�����(Ԫ)��������(��)���س��󰴡�#������" << endl;
		string num;//ҩƷ���
		string name;//ҩƷ����
		double money;//����
		int fund;//������
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
		cout << "��������ɣ�" << endl;
		file.close();
		file.open("data.txt", ios::in);
	}
	file.seekg(0, ios::beg);//�ص��ļ���ͷ
	int a=1;
	while (a != 4)
	{
		cout << "\t\t\t\t\t��ӭʹ��˼��ҩƷ����ͳ��ϵͳ" << endl;
		cout << "\t\t1.��ʼ���չ���    2.�����ܽᵼ��    3.����ҩƷ��    4.�˳�       (���������ִ�ж�Ӧ����)" << endl;
		cin >> a;
		while (a != 1 && a != 2 && a != 3 && a != 4)
		{
			cout << "�������벻���Ϲ淶������������;" << endl;
			cin >> a;
		}
		int day = 0;
		string num;//ҩƷ���
		string name;//ҩƷ����
		double money;//����
		int fund;//������
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
			cout << "��Ҫ��ѯ�������������������";
			cin >> day;
			chaxun(day, file);
			file.close();
			file.open("data.txt", ios::in);
			break;
		case 3:
			cout << "����������ÿ��ҩƷ��ţ�ҩƷ���ƣ�����(Ԫ)��������(��)���س��󰴡�#������" << endl;
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
			cout << "��������ɣ�" << endl;
			file.close();
			file.open("data.txt", ios::in);
			break;
		case 4:
			file.close();
			cout << "��ӭ�´�ʹ��" << endl;
			return;
		}
	}
}
int main()
{
	start();
	return 0;
}
