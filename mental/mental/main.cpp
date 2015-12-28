#include <iostream>
#include <ctime>
#include <math.h>
#include <cstdlib>


using namespace std;

//Генерация простого числа
int getPrimeNumber(int aMinKey, int aMaxKey)
{
	static time_t UTC = time(0) + 1;
	int primeNumber;
	//минимальное значение числа
	int minNumber = aMinKey;
	//максимальное значение числа
	int maxNumber = aMaxKey;
	srand(UTC);
	while (true)
	{
		//переключатель условия не простое число
		bool notPrime = false;
		primeNumber = rand() % maxNumber;
		//перебор всех возможных делителей
		for (int i = 2; i < primeNumber; i++)
		{
			if (primeNumber%i == 1)
				continue;
			if (primeNumber%i == 0)//делится без остатка, значит не простое
			{
				notPrime = true;
				break;
			}
		}
		//выполнилось условие - выходим из цикла
		if ((!notPrime) && (primeNumber >= minNumber))
			break;
	}
	return primeNumber;
}
//шифрование aNumber - шифруемое число, aPower - простое число степень возведения, aMod - модуль возведения
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
//взаимная простота
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
//генерация ключа, aPrimeNumber - большое простое число, aMaxKey - максимально возможный ключ
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

//генерация ключа расшифровки, aPrimeNumber - большое простое число, aKey - ключ шифрования
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
//возвращает массив перетассовки, size - размерность массива
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

	//Функция srand выполняет инициализацию генератора случайных чисел
	srand(time(NULL));

	//Генерируем большое простое число
	bigPrimeNumber = getPrimeNumber(min, maxKey);

	//Генерируем ключи для Алисы и Боба
	keyAlice = getKey(bigPrimeNumber, maxKey);
	keyBob = getKey(bigPrimeNumber, maxKey);
	dKeyAlice = getDKey(bigPrimeNumber, keyAlice);
	dKeyBob = getDKey(bigPrimeNumber, keyBob);
	cout << "Большое простое число: " << bigPrimeNumber <<" Ключ Алисы: " << keyAlice << " Ключ Боба: " << keyBob <<endl<<endl;
	cout << "Алиса шифрует каждую карту колоды, используя ключ keyAlice"<<endl;
	for (int i = 0; i < cardSize; i++)
	{
		cardDeckAlice[i] = encryption(cardDeckAlice[i], keyAlice, bigPrimeNumber);
		cout << "  №" << i << "=" << cardDeckAlice[i];
	}
	cout << endl << endl<<"Алиса тасует карты. Массив перетасовки:"<<endl;
	//Алиса тасует карты
	permutationArrayAlice = getPermutation(cardSize);
	for (int i = 0; i < cardSize; i++)
		cout << permutationArrayAlice[i] << "  ";

	cout << endl << endl << "Алиса передает зашифрованную и перемешанную колоду Бобу. Он не знает, где какие карты:" << endl;
	//Алиса передает зашифрованную и перемешанную колоду Бобу. Он не знает, где какие карты
	for (int i = 0; i < cardSize; i++)
	{
		cardDeckBob[i] = cardDeckAlice[permutationArrayAlice[i]];
		cout << "  №" << i << "=" << cardDeckBob[i];
	}
	
	cout << endl << endl << "Боб выбирает шифрование ключа keyBob и использует его для шифрования каждой карты из уже зашифрованной и перетасованной колоды:" << endl;
	//Боб выбирает шифрование ключа keyBob и использует его для шифрования каждой карты из уже зашифрованной и перетасованной колоды
	for (int i = 0; i < cardSize; i++)
	{
		cardDeckBob[i] = encryption(cardDeckBob[i], keyBob, bigPrimeNumber);
		cout << "  №" << i << "=" << cardDeckBob[i];
	}

	cout << endl << endl << "Боб тасует колоду. Массив перетасовки:" << endl;
	//Боб тасует колоду
	permutationArrayBob = getPermutation(cardSize);
	for (int i = 0; i < cardSize; i++)
		cout << permutationArrayBob[i] << "  ";

	cout << endl << endl << "Боб передает дважды зашифрованную и перетасованную колоду обратно Алисе" << endl;
	//Боб передает дважды зашифрованную и перетасованную колоду обратно Алисе
	for (int i = 0; i < cardSize; i++)
		cardDeckAlice[i] = cardDeckBob[permutationArrayBob[i]];

	//Алиса расшифровывает каждую карту, используя её ключ keyAlice. Но шифрование Боба все ещё остается, то есть она не знает, где какие карты
	dKeyAlice = getDKey(bigPrimeNumber, keyAlice);
	for (int i = 0; i < cardSize; i++)
		cardDeckAlice[i] = encryption(cardDeckAlice[i], dKeyAlice, bigPrimeNumber);

	//Алиса выбирает ключ шифрования каждой карты (А1, А2 и т. д.) и шифрует их по отдельности
	for (int i = 0; i < cardSize; i++)
	{
		cardKeysAlice[i] = getKey(bigPrimeNumber, maxKey);
		cardDKeysAlice[i] = getDKey(bigPrimeNumber, cardKeysAlice[i]);
		cardDeckAlice[i] = encryption(cardDeckAlice[i], cardKeysAlice[i], bigPrimeNumber);
	}

	//Алиса передает колоду Бобу
	for (int i = 0; i < cardSize; i++)
		cardDeckBob[i] = cardDeckAlice[i];

	//Боб расшифровывает каждую карту, используя его ключ keyBob. Индивидуальное шифрование Алисы все ещё остается, то есть он не знает, где какие карты
	dKeyBob = getDKey(bigPrimeNumber, keyBob);
	for (int i = 0; i < cardSize; i++)
		cardDeckBob[i] = encryption(cardDeckBob[i], dKeyBob, bigPrimeNumber);

	//Боб выбирает ключ для шифрования каждой карты (B1, B2 и т. д.) и шифрует их по отдельности
	for (int i = 0; i < cardSize; i++)
	{
		cardKeysBob[i] = getKey(bigPrimeNumber, maxKey);
		cardDKeysBob[i] = getDKey(bigPrimeNumber, cardKeysBob[i]);
		cardDeckBob[i] = encryption(cardDeckBob[i], cardKeysBob[i], bigPrimeNumber);
	}

	//Боб передает колоду обратно Алисе
	for (int i = 0; i < cardSize; i++)
		cardDeckAlice[i] = cardDeckBob[i];

	//Алиса показывает колоду всем игрокам (в данном случае игроки — Алиса и Боб)
	cout << "Алиса расшифровывает каждую карту, используя её ключ keyAlice. Но шифрование Боба все ещё остается, то есть она не знает, где какие карты" << endl;
	cout << "Алиса выбирает ключ шифрования каждой карты (А1, А2 и т. д.) и шифрует их по отдельности" << endl;
	cout << "Алиса передает колоду Бобу" << endl;
	cout << "Боб расшифровывает каждую карту, используя его ключ keyBob. Индивидуальное шифрование Алисы все ещё остается, то есть он не знает, где какие карты" << endl;
	cout << "Боб выбирает ключ для шифрования каждой карты (B1, B2 и т. д.) и шифрует их по отдельности" << endl;
	cout << "Боб передает колоду обратно Алисе" << endl;
	cout << "Алиса показывает колоду всем игрокам (в данном случае игроки — Алиса и Боб)" << endl;
	cout <<endl<< "Алиса получает первые 3 карты и просит их ключи у Боба, тот их передает" << endl<<endl;
	//Алиса получает первые 3 карты и просит их ключи у Боба, тот их передает
	for (int i = 0; i < 3; i++)
		cout << "  №" <<i<<"="<< cardDeckAlice[i];

	cout <<endl<< "Алиса расшифровывает свои 3 карты сначала собственными ключами А1, А2, А3, потом ключами Боба В1, В2, В3" << endl;
	//Алиса расшифровывает свои 3 карты сначала собственными ключами А1, А2, А3, потом ключами Боба В1, В2, В3
	int cardA[3];
	for (int i = 0; i < 3; i++)
	{
		cardA[i] = encryption(cardDeckAlice[i], cardDKeysAlice[i], bigPrimeNumber);
		cardA[i] = encryption(cardA[i], cardDKeysBob[i], bigPrimeNumber);
		cout << "  Карта №" << i << "=" << cardA[i];
	}
	cout <<endl<<"Для того, чтобы увидеть свои карты, игрокам необходимы ключи соперника: Алисе ключи В1, В2... Бобу А1, А2..."<< endl;
	cout << "Если Алисе выпадет десятая карта в прикупе, то Боб передаст десятый ключ, и Алиса увидит свою карту, но Боб без десятого ключа Алисы ее не видит." << endl;
	system("pause");
	}
