#pragma once

#include <cmath>
#include <future>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <exception>



class FilmAndUnderlay {
public:
	FilmAndUnderlay() = default;

	void SetVariablesFromConsole();
	void SetVariablesFromFile(const std::string& filepath);
	
	void CalculateFilmAlteringUnderlayFluor();

	double GetSingleResult(const size_t resultnumber) const;
	const std::vector<double>& GetAllResults() const;
	size_t GetResultsSize() const;

private:
	
	// ------ Variables in formula ------------- //
	double CalculateSingleSample(const std::vector<double>& Sample) const;
	std::string UnderlayElementName;

	std::string FilmElementName;
	const std::vector<std::string> SampleFormulaNames = {
		"Sq", "Tau 1_B", "Tau 1_A", "Tau j_A", "P B", "Mu 1_B","Mu i_B", "Mu j_B", "Mu j_A", "Mu i_A",
		"Mu A_B", "d", "Phi (in rad)", "Psi (in rad)", "Omega k_B", "Geomety constant", "I 1",  "Omega_eff"};
	
	std::vector<std::vector<double>> AllSamplesDataForCalculation;
	std::vector<double> AllSamplesResults;
};