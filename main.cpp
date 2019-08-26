#include <random>
#include "FilmAndUnderlay.h"

bool PrintAllData(const std::vector<double>& DataToPrint){
	if (DataToPrint.empty()){
		std::cout << "No data to print. Data array is empty!" << '\n';
		return false;
	}
	for (size_t i = 0; i < DataToPrint.size(); i++){
		std::cout << DataToPrint.at(i) << '\n';
	}
	std::cout << '\n';
	return true;
}
void PrintArgs(int argc, const char* argv[]){
	std::cout << "argc = " << argc << '\n';
	for (int i = 0; i < argc ; i++){
		std::cout << argv[i] << '\n';
	}
}

int main(int argc, const char* argv[]){
	//PrintArgs(argc, argv); //for argc & argv tests only
	if (argc > 2){
		std::cout << "Too many arguments" << '\n';
		return EXIT_FAILURE;
	}
	FilmAndUnderlay data;
	try{
		if (argc == 2){
			data.SetVariablesFromFile(argv[1]);
		}
		else{
			data.SetVariablesFromConsole();
		}
	}
	catch (const std::exception& e){
		std::cerr << e.what() << '\n';
	}
	
	data.CalculateFilmAlteringUnderlayFluor();
	if (!PrintAllData(data.GetAllResults())){
		return EXIT_FAILURE;
	}
	std::cout << "-----------------------------------------" << '\n';
	std::random_device rd;
	std::uniform_int_distribution<> distr(0, data.GetResultsSize() - 1);
	size_t Randmresult = distr(rd);
	std::cout << "Random result from sample " << Randmresult + 1 << " is equals to " << data.GetSingleResult(Randmresult) << '.' << '\n';
	return 0;
}
