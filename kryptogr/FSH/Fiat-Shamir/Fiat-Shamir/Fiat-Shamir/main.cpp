#include <iostream>
#include <time.h>
#include <random>
#include <limits>
#include <vector>

using namespace std;


// ������� a^b(mod mod)
double modPow(double a, double b, double mod)
{
	double res = 1;
	for (double i = b; i > 0; i--)
	{
		res = res * a;
		if (res > mod)
		{
			res = fmod(res, mod);
		}
	}
	return res;
}
//������
double getRandom(double min, double max)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(min, max);
	return dist(gen);
}

//���� ������� � ������ (�������� ����� �� ��������)
static bool MillerRabdoubleest(double n, double k)
{
	if (n <= 1)
		return false;
	if (n == 2)
		return true;
	if (fmod(n, 2) == 0)
		return false;
	double s = 0, d = n - 1;
	while (fmod(d, 2) == 0)
	{
		d /= 2;
		s++;
	}

	double randNum = rand() + 2;

	for (double i = 0; i < k; i++)
	{
		long a = fmod(randNum, (n - 1));
		double x = modPow(a, d, n);
		if (x == 1 || x == n - 1)
			continue;
		for (double j = 0; j < s - 1; j++)
		{
			x = fmod((x*x), n);
			if (x == 1)
				return false;
			if (x == n - 1)
				break;
		}
		if (x != n - 1)
			return false;
	}
	return true;
}

//���������� �������������� ����� �� ������ p
double generator(double p)
{
	vector<double> fact;
	double phi = p - 1, n = phi;
	for (double i = 2; i*i <= n; ++i)
	if (fmod(n, i) == 0) {
		fact.push_back(i);
		while (fmod(n, i) == 0)
			n /= i;
	}
	if (n > 1)
		fact.push_back(n);

	for (double res = 2; res <= p; ++res) {
		bool ok = true;
		for (size_t i = 0; i<fact.size() && ok; ++i)
			ok &= modPow(res, phi / fact[i], p) != 1;
		if (ok)  return res;
	}
	return -1;
}

//��������� ������� �����
double getPrimeNumber(double min, double max)
{
	double randNum;
	bool test;
	do{
		randNum = getRandom(min, max);
		double k = log2(randNum);
		test = MillerRabdoubleest(randNum, k);
	} while (!test);
	return randNum;
}
//�������� ��������
double gcd(double x, double y)
{
	return y ? gcd(y, fmod(x, y)) : x;
}

//����� ����������� ������� ��� ������ �����
class Abonent{
private:
	double s,r;
public:
	double x, n, v, e;
	Abonent(double n)
	{
		this->n = n;
		do
		{
			s = getRandom(1, (this->n - 1));
		} while (gcd(s, this->n) != 1);
		this->v = modPow(this->s, 2, this->n);
		
	}
	Abonent(double n, int nn)
	{
		this->n = n;
	}
	void getX()
	{
		this->r = getRandom(1, this->n - 1);
		this->x = modPow(this->r, 2, this->n);
		cout << endl << "�������������� x = r^2 mod n : " << this->x << " = " << this->r << "^2 mod " << this->n;
	}
	double calcY(double e)
	{
		if(e == 0) return modPow(this->r,1,this->n);
		else return modPow((this->r * this->s),1,this->n);		
	}
	void showS()
	{
		cout << this->s;
	}
	void showV()
	{
		cout << this->v;
	}
	void genE()
	{
		this->e = getRandom(0, 1);
	}
	void setX(double x)
	{
		this->x = x;
	}
	bool check(double y, double v)
	{
		double ch = (this->e > 0) ? modPow(x*v, 1, this->n) : modPow(x, 1, n);
		cout << "y^2 mod n = x*V^e mod n " << endl << modPow(y, 2, this->n) << " = " << ch;
		if (modPow(y, 2, this->n) == ch)
		{
			cout << endl << "�������� ��������" << endl;
			return true;
		}
		else
		{
			cout << endl << "�������� ���������" << endl;
			return false;
		}
	}
};

int main()
{
	//������� srand ��������� ������������� ���������� ��������� �����
	srand(time(NULL));
	double p = getPrimeNumber(100, 1000);
	double q = getPrimeNumber(100, 1000);
	setlocale(LC_ALL, "Russian");
	double n = p*q;
	cout << "���������� �����\n���������: p=" << p << "  q=" << q << " ���������: n = p*q = " << n << endl;
	cout << endl<< "����� : ";
	Abonent Alice(n);
	cout << "    ������ s=";
	Alice.showS();
	cout << "   ��������� ���� V = s^2 mod n = ";
	Alice.showV();
	cout<< endl;
	double v = Alice.v;	
	
	Abonent Bob(n,1);
	bool checkA = true;
	for (double i = 0; i < 20; i++)
	{
		cout << endl << endl << "��� t" << i << endl;
		cout << endl << "������� �����:";
		Alice.getX();
		cout << endl << "���������� x = " << Alice.x;
		Bob.setX(Alice.x);	
		Bob.genE();	
		cout << endl << "��������� e = {0,1} = " << Bob.e;
		double y = Alice.calcY(Bob.e);
		cout << endl << "���������� y = (r * s^e) mod n = " << y;
		cout << endl << endl << "������� ����:" << endl << "���������, ������������� �� ";
		if (!Bob.check(y, v))
		{
			cout << "�������� ������� ��������������!\n";
			checkA = false;
			break;
		}
		cout << endl;
		system("pause");
	}
	if (checkA)
	{
		cout << endl << endl << "�������������� ������� �����������!!!\n" << endl;
		Alice.showS();
	}
	system("pause");
	return 0;
}