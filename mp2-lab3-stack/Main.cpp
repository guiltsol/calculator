#include <iostream>
#include <fstream>
#include <clocale>
#include <ctime>
#include <string>

#include "TCalculator.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	setlocale(LC_NUMERIC, "eng");
	
	TCalculator calc;

	string str;

	while (true) {
		cout << "Введите пример"<<endl;
		getline(cin, str);
		cout << "========================"<<endl;
		calc.SetExpr(str);
		cout << "Пример: " << calc.GetExpr() << "\n\n";

		bool K = calc.CheckExpr();
		if (K) {
			cout << " "<<endl;
		}
		else {
			cout << "Скобки рассталвены не верно"<<endl;
			continue;
		}

		cout << "Постфикс: ";
		calc.PreparePostfix();
		cout << calc.GetPostfix() <<endl;

		cout << "Результат (CalcPostfix):  ";
		try
		{
			cout << calc.CalcPostfix() <<endl;
		}
		catch (...)
		{
			cout << "Исключение"<<endl;
		}

		cout << "Результат (Calc):         ";
		try
		{
			cout << calc.Calc() <<endl;
		}
		catch (...)
		{
			cout << "Исключение"<<endl;
		}
		cout << "=================================="<<endl;
	}
	return 0;
}