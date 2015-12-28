#include <random>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int modPow(int a, int b, int mod)// функция a^b(mod mod)
{
	int res = 1;
	for (int i = b; i > 0; i--)
	{
		res = res * a;
		if (res > mod)
		{
			res = res % mod;
		}
	}
	return res;
}

static bool MillerRabinTest(int n, int k)//Тест Миллера — Рабина (проверка числа на простоту)
{
	if (n <= 1)
		return false;
	if (n == 2)
		return true;
	if (n % 2 == 0)
		return false;
	int s = 0, d = n - 1;
	while (d % 2 == 0)
	{
		d /= 2;
		s++;
	}

	int randNum = rand() + 2;

	for (int i = 0; i < k; i++)
	{
		long a = randNum % (n - 1);
		int x = modPow(a, d, n);
		if (x == 1 || x == n - 1)
			continue;
		for (int j = 0; j < s - 1; j++)
		{
			x = (x*x) % n;
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

int gen_rand(int min, int max)
{
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(min, max); // distribute results between 1 and 6 inclusive.
	return dist(gen);
}

int gen_prime(int min, int max)
{
	int randNum;
	bool test;
	do{
		randNum = gen_rand(min, max);
		int k = log2(randNum);
		test = MillerRabinTest(randNum, k);
	} while (!test);
	return randNum;
}

int generator(int p) { //вычисление первообразного корня по модулю p
	vector<int> fact;
	int phi = p - 1, n = phi;
	for (int i = 2; i*i <= n; ++i)
		if (n % i == 0) {
			fact.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		fact.push_back(n);

	for (int res = 2; res <= p; ++res) {
		bool ok = true;
		for (size_t i = 0; i<fact.size() && ok; ++i)
			ok &= modPow(res, phi / fact[i], p) != 1;
		if (ok)  return res;
	}
	return -1;
}