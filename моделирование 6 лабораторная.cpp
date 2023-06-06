// моделирование 6 лабораторная.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
using namespace std;

void print_mass(float** ptr, int lenght);
int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Задание: Поиск пересечения и объединения нечетких множеств\n" << endl;
	cout << "----------------------------------------------------------\n" << endl;
	
	bool trigger = 0;
	int size_ms1, size_ms2, max, num = 0;
	int itera = 0;
	float prinadlej; 
	float** ms1 = nullptr; 
	float** ms2 = nullptr; 
	float** vec_answer = nullptr;
	float** vec_answer1 = nullptr;

	cout << "Введите размер первого нечеткого множества: ";
	cin >> size_ms1;
	cout << "Введите размер второго нечеткого множества: ";
	cin >> size_ms2;
	max = size_ms1;

	ms1 = new float* [size_ms1];  
	for (int q = 0; q < size_ms1; q++)
		ms1[q] = new float[2];

	ms2 = new float* [size_ms2];  
	for (int q = 0; q < size_ms2; q++)
		ms2[q] = new float[2];


	if (size_ms1 < size_ms2)  
		max = size_ms1;
	else if (size_ms1 > size_ms2)
		max = size_ms2;

	vec_answer = new float* [max]; 
	for (int b = 0; b < size_ms2; b++)
		vec_answer[b] = new float[2];

	// -------------------------------------
	cout << "\nЗаполните первое множество: " << endl;
	for (int i = 0; i < size_ms1; i++)
	{
		cout << "\nU" << i + 1 << ":";
		cin >> ms1[0][i];
		cout << "\nMa(u):";
		cin >> ms1[1][i];
	}
	print_mass(ms1, size_ms1);
	// -------------------------------------

	cout << endl;
	cout << "\nЗаполните второе множество: " << endl;
	for (int i = 0; i < size_ms2; i++)
	{
		cout << "\nU" << i + 1 << ":";
		cin >> ms2[0][i];
		cout << "\nMa(u):";
		cin >> ms2[1][i];
	}
	print_mass(ms2, size_ms2);



	cout << "Выберите тип задачи:\n0 - Пересечение\n1 - Объединение:";
	cin >> trigger;

	if (trigger == 0) // пересечение 
	{

		for (int u = 0; u < size_ms1; u++)
		{

			for (int i = 0; i < size_ms2; i++)
			{
				if (ms1[0][u] == ms2[0][i])
				{

					if (ms1[1][u] < ms2[1][i])
						prinadlej = ms1[1][u];
					else if (ms1[1][u] > ms2[1][i])
						prinadlej = ms2[1][i];
					else
						prinadlej = ms1[1][u];

					vec_answer[0][num] = ms1[0][u];
					vec_answer[1][num] = prinadlej;
					num++;

				}

			}

		}
		print_mass(vec_answer, num);
	}
	else if (trigger == 1) // объединение
	{
		bool ok;
		cout << "Множества разные:\n0 - нет\n1 - да\n";
		cin >> ok;

		vec_answer1 = new float* [size_ms1 + size_ms2]; // векторов ответов для объединения
		for (int q = 0; q < size_ms1 + size_ms2; q++)
			vec_answer1[q] = new float[2];

		for (int i = 0; i < size_ms1; i++) // копирование первого множества в ответы для сравнения со вторым множеством
		{
			vec_answer1[0][i] = ms1[0][i];
			vec_answer1[1][i] = ms1[1][i];
		}

		num = size_ms1;

		for (int y = 0; y < size_ms2; y++)
		{

			for (int z = 0; z < size_ms1; z++) // изменяет знч. по правилу объединения(с одинаковыми и разными элементами множества)
			{
				itera++;
				if (vec_answer1[0][z] == ms2[0][y])
				{
					if (ms2[1][y] > vec_answer1[1][z])
						vec_answer1[1][z] = ms2[1][y];
					itera = 0;
					break;

				}
			}
			if (itera == size_ms1)
			{
				vec_answer1[0][num] = ms2[0][y];
				vec_answer1[1][num] = ms2[1][y];
				num++;
				itera = 0;
			}

		}
		// сортировка 

		if (ok == 1)
		{
			float tmp = 0;
			float f_tmp = 0.0;

			for (int i = 0; i < num - 1; ++i) // i - номер прохода
			{
				for (int j = 0; j < num - 1; ++j) // внутренний цикл прохода
				{
					if (vec_answer1[0][j + 1] < vec_answer1[0][j])
					{
						tmp = vec_answer1[0][j + 1]; // значения данных
						vec_answer1[0][j + 1] = vec_answer1[0][j];
						vec_answer1[0][j] = tmp;

						f_tmp = vec_answer1[1][j + 1]; // функция принадлежности 
						vec_answer1[1][j + 1] = vec_answer1[1][j];
						vec_answer1[1][j] = f_tmp;

					}
				}
			}
		}

		print_mass(vec_answer1, num);
	}

}

void print_mass(float** ptr, int lenght)
{
	cout << endl;
	cout << "**************************************************************************************************************************************" << endl;
	cout << "U*:   ";
	for (int i = 0; i < lenght; i++)
		cout << "|" << "\t" << ptr[0][i] << "\t";
	cout << endl;
	cout << "\nM(U): ";
	for (int y = 0; y < lenght; y++)
		cout << "|" << "\t" << ptr[1][y] << "\t";
	cout << endl;
	cout << "**************************************************************************************************************************************" << endl;

	cout << endl;
}
