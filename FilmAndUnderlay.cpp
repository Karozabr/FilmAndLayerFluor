#include "FilmAndUnderlay.h"

FilmAndUnderlay::FilmAndUnderlay(){}

void FilmAndUnderlay::AddValue(std::string& item, std::vector<double>& SingleSampleValues) {
	SingleSampleValues.push_back(std::stod(item));
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
				if (SingleSampleValues.size() != SampleFormulaNames.size()) throw std::runtime_error("Wrong amount of variables in file!");
				AllSamplesDataForCalculation.push_back(SingleSampleValues);
				SingleSampleValues.clear();
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
//B = Cu, A = Ni
//"Sq", "Tau 1_B", "Tau 1_A", "Tau j_A", "P B", "Mu 1_B", "Mu j_B", "Mu j_A", "Mu i_A", "Mu A_B", "d", "Phi (in rad)", "Psi (in rad)", "Omega k_B", "Geomety constant", "I 1", "Omega_eff"
//  0      1           2           3       4        5        6          7         8        9      10     11              12               13                14           15         16
		double M = ((Sample.at(0) - 1)* Sample.at(1)* Sample.at(13)* Sample.at(4)* Sample.at(3)) / (Sample.at(14) * Sample.at(0) * Sample.at(2));
		double Part_1 = std::exp(-1*Sample.at(6)* Sample.at(10) / std::sin(Sample.at(16))) / (Sample.at(5)/std::sin(Sample.at(11)) - Sample.at(6)/std::sin(Sample.at(16))); //Â, Ä in formula
		double Part_2 = 1 - std::exp(-1 * Sample.at(10) * (Sample.at(5)/std::sin(Sample.at(11)) - Sample.at(6)/std::sin(Sample.at(16)))); //Ã in formula
		double Part_3 = std::exp(-1* Sample.at(10)* Sample.at(8)/std::sin(Sample.at(12))) / (Sample.at(7)/ std::sin(Sample.at(16)) + Sample.at(8)/ std::sin(Sample.at(12))); //Å, Æ in formula
		SingleResult = M * Part_1 * Part_2 * Part_3;
		/*for check*
		for (const auto item : Sample) {
			SingleResult += item;
		}//*/
		AllSamplesResults.push_back(SingleResult);
	}
}
