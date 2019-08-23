#include "FilmAndUnderlay.h"

namespace {
	void AddValue(std::string& item, std::vector<double>& valuesvector) {
		valuesvector.push_back(std::stod(item));
		item.clear();
	}
}

double FilmAndUnderlay::GetSingleResult(size_t ResultNumber) const {
	return AllSamplesResults.at(ResultNumber);
}

size_t FilmAndUnderlay::GetResultsSize() const {
	return AllSamplesResults.size();
}

const std::vector<double>& FilmAndUnderlay::GetAllResults() const {
	return AllSamplesResults;
}

void FilmAndUnderlay::SetVariablesFromConsole() {
	std::string item;
	std::vector<double> SingleSampleValues;
	for (size_t z = 0; z < SampleFormulaNames.size(); z++)
	{
		std::cout << SampleFormulaNames.at(z) << "       ";
		std::cin >> item;
		if (std::cin.fail())
		{
			throw std::runtime_error("Wrong argument! Input should be float-point value.");
		}
		AddValue(item, SingleSampleValues);
	}
	AllSamplesDataForCalculation.push_back(SingleSampleValues);
	std::cout << "Input another sample?" << '\n';
	std::cout << "1 - Yes   /    Any other nuber - No" << '\n';
	int key;
	std::cin >> key;
	if (std::cin.fail())
	{
		throw std::runtime_error("Wrong argument! Input should be an integer value.");
	}
	if (key == 1) SetVariablesFromConsole();
}

void FilmAndUnderlay::SetVariablesFromFile(const std::string& filepath) {
	std::ifstream input(filepath, std::ios::in);
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
}

void FilmAndUnderlay::CalculateFilmAlteringUnderlayFluor() {
	
	for (const auto& Sample : AllSamplesDataForCalculation)
	{
		double SingleResult = 0;
//B = Cu, A = Ni
		const double Sq = Sample.at(0);
		const double Tau1_B = Sample.at(1);
		const double Tau1_A = Sample.at(2);
		const double Tauj_A = Sample.at(3);
		const double PB = Sample.at(4);
		const double Mu1_B = Sample.at(5);
		const double Mui_B = Sample.at(6);
		const double Muj_B = Sample.at(7);
		const double Muj_A = Sample.at(8);
		const double Mui_A = Sample.at(9);
		const double MuA_B = Sample.at(10);
		const double d = Sample.at(11);
		const double Phi = Sample.at(12);
		const double Psi = Sample.at(13);
		const double Omegak_B = Sample.at(14);
		const double Geometyconstant = Sample.at(15);
		const double I1 = Sample.at(16);
		const double Omegaeff = Sample.at(17);

		const double M = ((Sq - 1)* Tau1_B* Omegak_B* PB* Tauj_A) /
							(Geometyconstant * Sq * Tau1_A);
		const double Part_1 = std::exp(-1*Muj_B* d / std::sin(Omegaeff)) /
							(Mu1_B/std::sin(Phi) - Muj_B/std::sin(Omegaeff)); //Â, Ä in formula
		const double Part_2 = 1 - std::exp(	-1 * d *
											(Mu1_B/std::sin(Phi) - Muj_B/std::sin(Omegaeff))
										   ); //Ã in formula
		const double Part_3 = std::exp(-1* d* Mui_B/std::sin(Psi)) /
										(Muj_A/ std::sin(Omegaeff) + MuA_B/ std::sin(Phi)); //Å, Æ in formula
		SingleResult = M * Part_1 * Part_2 * Part_3;
		AllSamplesResults.push_back(SingleResult);
	}
}