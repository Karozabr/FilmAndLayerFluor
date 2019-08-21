#include <iostream>
#include "FilmAndUnderlay.h"

void PrintAllData(const std::vector<double>& DataToPrint){
	if (DataToPrint.empty())
	{
		std::cout << "No data to print. Data array is empty!" << '\n';
		return;
	}
	for (size_t i = 0; i < DataToPrint.size(); i++)
	{
		std::cout << DataToPrint.at(i) << '\n';
	}
	std::cout << '\n';
}
void PrintArgs(int argc, const char* argv[]) {
	std::cout << "argc = " << argc << '\n';
	for (int i = 0; i < argc ; i++)
	{
		std::cout << argv[i] << '\n';
	}
}
int main(int argc, const char* argv[])
{
	PrintArgs(argc, argv);
	if (argc > 2){
		std::cout << "Too many arguments" << '\n';
		return 0;
	}
	FilmAndUnderlay data;
	if (argc == 2) {
		if (!data.SetVariablesFromFile(argv[1])){ std::cout << "File error!" << '\n'; return 0;}
	}
	else{
		if (!data.SetVariablesFromConsole()) {
			std::cout << "Console input error!" << '\n'; return 0;
		};
	}
	data.CalculateFilmAlteringUnderlayFluor();
	PrintAllData(data.GetAllResults());
	std::cout << "-----------------------------------------" << '\n';
	if (data.GetResultsSize()==0)
	{
		return 0;
	}
	size_t Randmresult = rand() % data.GetResultsSize();
	std::cout << "Random result from sample " << Randmresult + 1 << " is equals to " << data.GetSingleResult(Randmresult) << '.' << '\n';
	return 0;
}
