#include<iostream>
#include<Windows.h>
#include<iomanip>
#include<functional>

void print_answer(const char* message, double s);
double sum_series(double x, int n);
double sum_series(double x, double eps, int& i);
template <typename T, typename Predicat>
void Read_and_check(T& x, Predicat condition, const char* message);
int main_menu();


int main()
{
	SetConsoleOutputCP(1251);

	short choice;
	do
	{
		choice = main_menu();


		if (choice != 3)
		{

			double x;
			Read_and_check(x, [](double x)->bool {return true; }, "\nВведите значение x (x-любое число): ");


			if (choice == 1)
			{
				//std::cout << "Задача 1\n";
				int n;
				std::cout << "\nВведите количество слагаемых: ";
				std::cin >> n;
				std::cout << "-------------------------------------" << '\n';
				print_answer("Приближенное значение", sum_series(x, n));
			}

			else

			{
				//std::cout << "Задача 2\n";
				double eps;
				std::cout << "\nВведите точность вычисления: ";
				std::cin >> eps;
				int count = 0;
				double res = sum_series(x, eps, count);
				std::cout << "-------------------------------------" << '\n';
				print_answer("Приближенное значение", res);
				std::cout << "Количество слагаемых: " << count << '\n';


			}
			std::cout << "-------------------------------------" << '\n';
			print_answer("Точное значение", cosh(x));

			std::cout << "-------------------------------------" << '\n';
			std::cout << "\nЗавершить работу ? (Y / любая клавиша) : ";

			char isExit;
			std::cin >> isExit;

			if (isExit == 'Y' || isExit == 'y')
				choice = 3;
		}

	} while (choice != 3);


}


void print_answer(const char* message, double s)
{

	std::cout << '\n' << std::setw(28) << std::left << message << " = " << std::fixed << std::setprecision(11) << s << '\n';

}

double sum_series(double x, int n)
{
	double res = 1;
	double fact = 1;
	double term = 1;
	for (int i = 1; i <= n; ++i)
	{
		term = (term * x * x) / (fact * (fact + 1));
		res = res + term;
		fact = fact + 2;
	}
	return res;
}

double sum_series(double x, double eps, int& count)
{
	double term = 1;
	double res = 1;

	while (abs(term) > eps)
	{
		term = (term * x * x) / ((2 * count + 1) * 2 * (count + 1));
		res = res + term;
		count++;
	}
	return res;
}

int main_menu()
{
	std::cout << "-------------------------------------" << '\n';
	std::cout << "\nМеню\n";
	std::cout << "\n1. Сумма заданного количества слагаемых\n";
	std::cout << "2. Сумма с заданной точностью\n";
	std::cout << "3. Завершение работы\n";
	std::function<bool(int)> Lambda = [](int x)->bool
		{
			return x >= 1 && x <= 3;
		};
	int choice = 0;
	Read_and_check(choice, Lambda, "\n-> ");
	return choice;
}

template<typename T, typename Predicat>
void Read_and_check(T& x, Predicat condition, const char* message)
{
	std::cout << message;
	while (!(std::cin >> x && condition(x)))
	{
		std::cout << "Ошибка ввода!\n";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message;

	}
}
