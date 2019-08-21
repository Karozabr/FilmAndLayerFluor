#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



class FilmAndUnderlay {
public:
	FilmAndUnderlay();

	bool SetVariablesFromConsole();
	bool SetVariablesFromFile(const std::string FilePath);
	
	void CalculateFilmAlteringUnderlayFluor();

	inline double GetSingleResult(const size_t ResultNumber) const;
	inline const std::vector<double>& GetAllResults() const;
	inline size_t GetResultsSize() const;

private:
	
	// ------ Variables in formula ------------- //
	std::string UnderlayElementName;
	std::string FilmElementName;
	const std::vector<std::string> SampleFormulaNames = {
		"Sq", "Tau 1_B", "Tau 1_A", "Tau j_A", "P B", "Mu 1_B", "Mu j_B", "Mu j_A", "Mu i_A",
		"Mu A_B", "d", "Phi", "Psi", "Omega k_B", "Geomety constant", "I 1" };
	
	std::vector<std::vector<double>> AllSamplesDataForCalculation;
	std::vector<double> AllSamplesResults;

	void AddValue(std::string& item, std::vector<double>& SingleSampleValues);
};

inline double FilmAndUnderlay::GetSingleResult(size_t ResultNumber) const {
	return AllSamplesResults.at(ResultNumber);
}

inline size_t FilmAndUnderlay::GetResultsSize() const {
	return AllSamplesResults.size();
}

inline const std::vector<double>& FilmAndUnderlay::GetAllResults() const {
	return AllSamplesResults;
}