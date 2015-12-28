#include <iostream>
#include <ctime>
#include <math.h>
#include <cstdlib>


using namespace std;

//��������� �������� �����
int getPrimeNumber(int aMinKey, int aMaxKey)
{
	static time_t UTC = time(0) + 1;
	int primeNumber;
	//����������� �������� �����
	int minNumber = aMinKey;
	//������������ �������� �����
	int maxNumber = aMaxKey;
	srand(UTC);
	while (true)
	{
		//������������� ������� �� ������� �����
		bool notPrime = false;
		primeNumber = rand() % maxNumber;
		//������� ���� ��������� ���������
		for (int i = 2; i < primeNumber; i++)
		{
			if (primeNumber%i == 1)
				continue;
			if (primeNumber%i == 0)//������� ��� �������, ������ �� �������
			{
				notPrime = true;
				break;
			}
		}
		//����������� ������� - ������� �� �����
		if ((!notPrime) && (primeNumber >= minNumber))
			break;
	}
	return primeNumber;
}
//���������� aNumber - ��������� �����, aPower - ������� ����� ������� ����������, aMod - ������ ����������
int encryption(int aNumber, int aPower, int aMod)
{
	int retNumber = 1;
	if (aPower == 0) return 1;
	while (aPower != 0)
	{
		if (aPower % 2 == 0)
		{
			aPower /= 2;
			aNumber *= aNumber;
			aNumber %= aMod;
		}
		else 
		{
			aPower--;
			retNumber *= aNumber;
			retNumber %= aMod;
		}
	}
	return retNumber;
}
//�������� ��������
int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}
//��������� �����, aPrimeNumber - ������� ������� �����, aMaxKey - ����������� ��������� ����
int getKey(int aPrimeNumber, int aMaxKey)
{
	int temp = 0;
	int returnNumber;
	while (temp != 1)
	{
		returnNumber = rand() % aMaxKey;
		temp = gcd(returnNumber, (aPrimeNumber - 1));
	}
	return returnNumber;
}

//��������� ����� �����������, aPrimeNumber - ������� ������� �����, aKey - ���� ����������
int getDKey(int aPrimeNumber, int aKey)
{
	int returnNumber;
	int i = 1;
	while (true)
	{
		if ((aKey*i) % (aPrimeNumber - 1) == 1)
		{
			returnNumber = i;
			break;
		}
		i++;
	}
	return returnNumber;
}
//���������� ������ ������������, size - ����������� �������
int *getPermutation(int aSize)
{
	int *returnArray = new int[aSize];
	int value;
	bool find;
	for (int i = 0; i < aSize; i++)
	{
		while (true)
		{
			find = false;
			value = rand() % aSize;
			for (int j = 0; j < i; j++)
			{
				if (returnArray[j] == value) { find = true; break; }
			}
			if (!find)
			{
				returnArray[i] = value;
				break;
			}
		}
	}

	return returnArray;
}

int main()
{
	int bigPrimeNumber, keyAlice, keyBob, dKeyAlice, dKeyBob, maxKey = 10000, min = 1000;
	const int cardSize = 52;
	int cardDeckAlice[cardSize], cardDeckBob[cardSize], cardKeysAlice[cardSize], cardDKeysAlice[cardSize], cardKeysBob[cardSize], cardDKeysBob[cardSize];
	int *permutationArrayAlice, *permutationArrayBob;
	for (int i = 0; i < cardSize; i++)
		cardDeckAlice[i] = i;
	setlocale(LC_ALL, "Russian");

	//������� srand ��������� ������������� ���������� ��������� �����
	srand(time(NULL));

	//���������� ������� ������� �����
	bigPrimeNumber = getPrimeNumber(min, maxKey);

	//���������� ����� ��� ����� � ����
	keyAlice = getKey(bigPrimeNumber, maxKey);
	keyBob = getKey(bigPrimeNumber, maxKey);
	dKeyAlice = getDKey(bigPrimeNumber, keyAlice);
	dKeyBob = getDKey(bigPrimeNumber, keyBob);
	cout << "������� ������� �����: " << bigPrimeNumber <<" ���� �����: " << keyAlice << " ���� ����: " << keyBob <<endl<<endl;
	cout << "����� ������� ������ ����� ������, ��������� ���� keyAlice"<<endl;
	for (int i = 0; i < cardSize; i++)
	{
		cardDeckAlice[i] = encryption(cardDeckAlice[i], keyAlice, bigPrimeNumber);
		cout << "  �" << i << "=" << cardDeckAlice[i];
	}
	cout << endl << endl<<"����� ������ �����. ������ �����������:"<<endl;
	//����� ������ �����
	permutationArrayAlice = getPermutation(cardSize);
	for (int i = 0; i < cardSize; i++)
		cout << permutationArrayAlice[i] << "  ";

	cout << endl << endl << "����� �������� ������������� � ������������ ������ ����. �� �� �����, ��� ����� �����:" << endl;
	//����� �������� ������������� � ������������ ������ ����. �� �� �����, ��� ����� �����
	for (int i = 0; i < cardSize; i++)
	{
		cardDeckBob[i] = cardDeckAlice[permutationArrayAlice[i]];
		cout << "  �" << i << "=" << cardDeckBob[i];
	}
	
	cout << endl << endl << "��� �������� ���������� ����� keyBob � ���������� ��� ��� ���������� ������ ����� �� ��� ������������� � �������������� ������:" << endl;
	//��� �������� ���������� ����� keyBob � ���������� ��� ��� ���������� ������ ����� �� ��� ������������� � �������������� ������
	for (int i = 0; i < cardSize; i++)
	{
		cardDeckBob[i] = encryption(cardDeckBob[i], keyBob, bigPrimeNumber);
		cout << "  �" << i << "=" << cardDeckBob[i];
	}

	cout << endl << endl << "��� ������ ������. ������ �����������:" << endl;
	//��� ������ ������
	permutationArrayBob = getPermutation(cardSize);
	for (int i = 0; i < cardSize; i++)
		cout << permutationArrayBob[i] << "  ";

	cout << endl << endl << "��� �������� ������ ������������� � �������������� ������ ������� �����" << endl;
	//��� �������� ������ ������������� � �������������� ������ ������� �����
	for (int i = 0; i < cardSize; i++)
		cardDeckAlice[i] = cardDeckBob[permutationArrayBob[i]];

	//����� �������������� ������ �����, ��������� � ���� keyAlice. �� ���������� ���� ��� ��� ��������, �� ���� ��� �� �����, ��� ����� �����
	dKeyAlice = getDKey(bigPrimeNumber, keyAlice);
	for (int i = 0; i < cardSize; i++)
		cardDeckAlice[i] = encryption(cardDeckAlice[i], dKeyAlice, bigPrimeNumber);

	//����� �������� ���� ���������� ������ ����� (�1, �2 � �. �.) � ������� �� �� �����������
	for (int i = 0; i < cardSize; i++)
	{
		cardKeysAlice[i] = getKey(bigPrimeNumber, maxKey);
		cardDKeysAlice[i] = getDKey(bigPrimeNumber, cardKeysAlice[i]);
		cardDeckAlice[i] = encryption(cardDeckAlice[i], cardKeysAlice[i], bigPrimeNumber);
	}

	//����� �������� ������ ����
	for (int i = 0; i < cardSize; i++)
		cardDeckBob[i] = cardDeckAlice[i];

	//��� �������������� ������ �����, ��������� ��� ���� keyBob. �������������� ���������� ����� ��� ��� ��������, �� ���� �� �� �����, ��� ����� �����
	dKeyBob = getDKey(bigPrimeNumber, keyBob);
	for (int i = 0; i < cardSize; i++)
		cardDeckBob[i] = encryption(cardDeckBob[i], dKeyBob, bigPrimeNumber);

	//��� �������� ���� ��� ���������� ������ ����� (B1, B2 � �. �.) � ������� �� �� �����������
	for (int i = 0; i < cardSize; i++)
	{
		cardKeysBob[i] = getKey(bigPrimeNumber, maxKey);
		cardDKeysBob[i] = getDKey(bigPrimeNumber, cardKeysBob[i]);
		cardDeckBob[i] = encryption(cardDeckBob[i], cardKeysBob[i], bigPrimeNumber);
	}

	//��� �������� ������ ������� �����
	for (int i = 0; i < cardSize; i++)
		cardDeckAlice[i] = cardDeckBob[i];

	//����� ���������� ������ ���� ������� (� ������ ������ ������ � ����� � ���)
	cout << "����� �������������� ������ �����, ��������� � ���� keyAlice. �� ���������� ���� ��� ��� ��������, �� ���� ��� �� �����, ��� ����� �����" << endl;
	cout << "����� �������� ���� ���������� ������ ����� (�1, �2 � �. �.) � ������� �� �� �����������" << endl;
	cout << "����� �������� ������ ����" << endl;
	cout << "��� �������������� ������ �����, ��������� ��� ���� keyBob. �������������� ���������� ����� ��� ��� ��������, �� ���� �� �� �����, ��� ����� �����" << endl;
	cout << "��� �������� ���� ��� ���������� ������ ����� (B1, B2 � �. �.) � ������� �� �� �����������" << endl;
	cout << "��� �������� ������ ������� �����" << endl;
	cout << "����� ���������� ������ ���� ������� (� ������ ������ ������ � ����� � ���)" << endl;
	cout <<endl<< "����� �������� ������ 3 ����� � ������ �� ����� � ����, ��� �� ��������" << endl<<endl;
	//����� �������� ������ 3 ����� � ������ �� ����� � ����, ��� �� ��������
	for (int i = 0; i < 3; i++)
		cout << "  �" <<i<<"="<< cardDeckAlice[i];

	cout <<endl<< "����� �������������� ���� 3 ����� ������� ������������ ������� �1, �2, �3, ����� ������� ���� �1, �2, �3" << endl;
	//����� �������������� ���� 3 ����� ������� ������������ ������� �1, �2, �3, ����� ������� ���� �1, �2, �3
	int cardA[3];
	for (int i = 0; i < 3; i++)
	{
		cardA[i] = encryption(cardDeckAlice[i], cardDKeysAlice[i], bigPrimeNumber);
		cardA[i] = encryption(cardA[i], cardDKeysBob[i], bigPrimeNumber);
		cout << "  ����� �" << i << "=" << cardA[i];
	}
	cout <<endl<<"��� ����, ����� ������� ���� �����, ������� ���������� ����� ���������: ����� ����� �1, �2... ���� �1, �2..."<< endl;
	cout << "���� ����� ������� ������� ����� � �������, �� ��� �������� ������� ����, � ����� ������ ���� �����, �� ��� ��� �������� ����� ����� �� �� �����." << endl;
	system("pause");
	}
