#include "FilmAndUnderlay.h"

FilmAndUnderlay::FilmAndUnderlay(){}

void FilmAndUnderlay::AddValue(std::string& item, std::vector<double>& SingleSampleValues) {
	try
	{
		SingleSampleValues.push_back(std::stod(item));
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}
	
	item.clear();
}

bool FilmAndUnderlay::SetVariablesFromConsole() {
	std::string item;
	std::vector<double> SingleSampleValues;
	for (size_t z = 0; z < SampleFormulaNames.size(); z++)
	{
		std::cout << SampleFormulaNames.at(z) << "       ";
		std::cin >> item;
		if (std::cin.fail())
		{
			return false;
		}
		AddValue(item, SingleSampleValues);
	}
	AllSamplesDataForCalculation.push_back(SingleSampleValues);
	std::cout << "Input another sample?" << '\n';
	std::cout << "1 - Yes   /    Any other - No" << '\n';
	int key;
	std::cin >> key;
	if (key == 1) {
		if (!SetVariablesFromConsole()) return false;
	}
	return true;
}

bool FilmAndUnderlay::SetVariablesFromFile(const std::string FilePath) {
	std::ifstream input(FilePath, std::ios::in);
	std::vector<double> SingleSampleValues;
	while (!input.eof())
	{
		std::string item;
		std::string line;
		std::getline(input, line);
		auto line_it = line.begin();
		while (line_it != line.end())
		{
			if (*line_it == ' ') {
				AddValue(item, SingleSampleValues);
				line_it++;
				continue;
			}
			item += *line_it++;
			if (line_it == line.end())
			{
				AddValue(item, SingleSampleValues);
				AllSamplesDataForCalculation.push_back(SingleSampleValues);
				continue;
			}
		}
		
	}
	return true;
}

void FilmAndUnderlay::CalculateFilmAlteringUnderlayFluor() {
	
	for (const auto Sample : AllSamplesDataForCalculation)
	{
		double SingleResult = 0;
		/*for check*/
		for (const auto item : Sample) {
			SingleResult += item;
		}//*/
		AllSamplesResults.push_back(SingleResult);
	}
}

/*char c = input.get();
if (c == ' ') {
	AddValue(item, SingleSampleValues);
	continue;
}
if (c == '\n')
{
	AddValue(item, SingleSampleValues);
	AllSamplesDataForCalculation.push_back(SingleSampleValues);
	continue;
}
item += c;*/