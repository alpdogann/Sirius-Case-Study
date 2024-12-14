#include "DataProcessor.h"
#include <algorithm>
#include <numeric>
#include <iostream>

DataProcessor::DataProcessor(int movingAverageWindowSize, int subsetSize)
	:m_windowSize(movingAverageWindowSize),  // Set the moving average window size
	 m_subsetSize(subsetSize),               // Set the subset size for averaging
	 m_rawAverage(0.0),                      // Initialize raw average to 0
	 m_processedAverage(0.0)                 // Initialize processed average to 0
{
	// Constructor body
}

DataProcessor::~DataProcessor()
{
	// Destructor body
}

std::vector<double> DataProcessor::getRawData() const
{
	// Return the raw data stored in m_rawData
	return m_rawData;
}

std::vector<double> DataProcessor::getProcessedData() const
{
	// Return the processed data stored in m_processedData
	return m_processedData;
}

std::vector<double> DataProcessor::getRawSubsetAverageData() const
{
	// Return the raw subset averages stored in m_rawSubsetAverageData
	return m_rawSubsetAverageData;
}

std::vector<double> DataProcessor::getProcessedSubsetAverageData() const
{
	// Return the processed subset averages stored in m_processedSubsetAverageData
	return m_processedSubsetAverageData;
}

std::vector<double> DataProcessor::calculateSubsetAverage(const std::vector<double>& vec) const
{
	double dScale = 1.0 / (double)m_subsetSize; // Scaling factor to calculate the average of each subset

	if (!vec.empty())
	{
		int size = vec.size();
		int padding = size % m_subsetSize > 0 ? m_subsetSize - (size % m_subsetSize) : 0; // Calculate padding if the size isn't a multiple of m_subsetSize
		std::vector<double> tempSubsetVector(size + padding, 0.0);  // Create a temporary vector with padding (filled with 0s) to handle incomplete subsets
		std::vector<double> tempSubsetAverageVector; // Create a temporart vector to store the average of each subset

		// Copy the input data into the temporary vector
		for (int i = 0; i < size; i++)
		{
			tempSubsetVector[i] = vec[i];
		}
		// Loop through the temporary vector in steps of m_subsetSize
		for (int i = 0; i < tempSubsetVector.size(); i += m_subsetSize)
		{
			double sum = std::accumulate(tempSubsetVector.begin() + i, tempSubsetVector.begin() + i + m_subsetSize, 0.0); // Calculate the sum of the current subset using std::accumulate with initial sum of 0.0
			double average = sum * dScale;
			tempSubsetAverageVector.push_back(average);
		}
		return tempSubsetAverageVector;
	}
	// If the vector is empty, return an empty vector
	return std::vector<double>();
}

double DataProcessor::getRawDataMin() const
{
	// Find and return the minimum value in the raw data vector
	return (*std::min_element(m_rawData.begin(), m_rawData.end())); 
}

double DataProcessor::getRawDataMax() const
{
	// Find and return the maximum value in the raw data vector
	return (*std::max_element(m_rawData.begin(), m_rawData.end()));
}

double DataProcessor::getProcessedDataMin() const
{
	// Find and return the minimum value in the processed data vector
	return (*std::min_element(m_processedData.begin(), m_processedData.end()));
}

double DataProcessor::getProcessedDataMax() const
{
	// Find and return the maximum value in the processed data vector
	return (*std::max_element(m_processedData.begin(), m_processedData.end()));
}

double DataProcessor::getRawAverage() const
{
	// Return the average of the raw data stored in m_rawAverage
	return m_rawAverage;
}

double DataProcessor::getProcessedAverage() const
{
	// Return the average of the processed data stored in m_processedAverage
	return m_processedAverage;
}

double DataProcessor::calculateAverage(const std::vector<double>& vec)
{	// Check if raw data is not empty
	if (!vec.empty())
	{
		int size = vec.size();
		double dScale = 1.0 / (double)size; // Calculate the scaling factor for averaging
		double sum = 0.0;
		// Loop through the vector to sum all values
		for (int i = 0; i < size; i++)
		{
			sum += vec[i];
		}
		return (sum * dScale); // Multiply by the scale to get the average and return
	}
	return 0.0; // If the vector is empty, return 0.0
}

void DataProcessor::setRawData(const std::vector<double>& vec)
{
	// Replace the current raw data with the provided vector vec
	m_rawData = vec;
}

void DataProcessor::calculateAverages()
{
	m_rawAverage = calculateAverage(m_rawData); // Calculate and store the average for raw data
	m_processedAverage = calculateAverage(m_processedData); // Calculate and store the average for processed data
}

void DataProcessor::calculateSubsetAverages()
{ 
	m_rawSubsetAverageData = calculateSubsetAverage(m_rawData); // Calculate the subset averages for raw data and store them in m_rawSubsetAverageData
	m_processedSubsetAverageData = calculateSubsetAverage(m_processedData); // Calculate the subset averages for processed data and store them in m_processedSubsetAverageData
}

void DataProcessor::movingAverageFilter()
{
	int offset = (m_windowSize - 1) / 2; // Calculate the offset for the window (half the window size, rounded down)
	int index = 0;
	double dScaler = 1.0 / (double)m_windowSize; // Scaling factor to normalize the sum to get the average
	
	std::vector<double> tempVec(m_rawData.size() + m_windowSize - 1); // Temporary vector to store padded data (to handle edge cases)

	// Add padding at the beginning of tempVec using the first value of m_rawData
	for (int i = 0; i < offset; i++)
	{
		tempVec[index++] = m_rawData.front();
	}

	// Copy the raw data into the temporary vector
	for (int i = 0; i < m_rawData.size(); i++)
	{
		tempVec[index++] = m_rawData[i];
	}

	// Add padding at the end of tempVec using the last value of m_rawData
	for (int i = 0; i < offset; i++)
	{
		tempVec[index++] = m_rawData.back();
	}

	// Perform the moving average calculation
	for (int i = 0; i < m_rawData.size(); i++)
	{
		double sum = 0.0;

		// Sum the elements within the window (of size m_windowSize)
		for (int j = 0, k= i; j < m_windowSize; j++, k++)
		{
			sum += tempVec[k];
		}

		m_processedData.push_back(sum * dScaler); // Store the average of the window in the processed data
	}
	
}
