#include "Sensor.h"
#include <thread>
#include <iostream>

Sensor::Sensor(int numDataPoints, DataGenerationTiming generationTiming, int periodIfNecessary, DataType dataType, double rangeMin, double rangeMax)
	:	m_numOfDataPoints(numDataPoints),         // Total number of data points to generate
		m_generationTiming(generationTiming),     // Timing mode for data generation
		m_periodForGeneration(periodIfNecessary), // Delay period for periodic generation
		m_dataType(dataType),                     // Type of data to generate
		m_rangeMin(rangeMin),                     // Minimum range for generated data
		m_rangeMax(rangeMax),                     // Maximum range for generated data
		m_currentStep(0)                          // Initialize current step to 0
{
	// Constructor body
}
Sensor::~Sensor()
{
	// Destructor body
}

void Sensor::collectAndStoreDataPoints()
{

	if (m_generationTiming == eImmediate)
	{
		// Generate all data points immediately without delay
		for (int i = 0; i < m_numOfDataPoints; i++)
		{
			m_physicalData.push_back(generateDataPoint()); // Store the generated data point
			std::cout << "Data Generated\n"; // Log the generation event
		}
	}
	else if (m_generationTiming == ePeriodic)
	{
		// Generate data points periodically with a fixed delay
		for (int i = 0; i < m_numOfDataPoints; i++)
		{
			m_physicalData.push_back(generateDataPoint()); // Store the generated data point
			std::this_thread::sleep_for(std::chrono::milliseconds(m_periodForGeneration)); // Wait for the specified period before generating the next point
			std::cout << "Data Generated\n"; // Log the generation event
		}
	}
	else
	{
		// Generate data points asynchronously with a random delay
		for (int i = 0; i < m_numOfDataPoints; i++)
		{
			m_physicalData.push_back(generateDataPoint()); // Store the generated data point
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 200 + 100)); // Wait for a random delay between 100 and 300 milliseconds
			std::cout << "Data Generated\n"; // Log the generation event
		}
	}
}

const std::vector<double>& Sensor::getData() const
{
	// Return a constant reference to the collected data points
	return m_physicalData;
}

double Sensor::generateDataPoint()
{
	if (m_dataType == LINEAR)
	{
		// Calculate the step size for linear data generation
		double step = (m_rangeMax - m_rangeMin) / (m_numOfDataPoints - 1);

		// Compute the current value based on the current step
		double value = m_rangeMin + m_currentStep * step;

		// Increment the step counter, wrapping around to 0 when the maximum is reached
		m_currentStep = (m_currentStep + 1) % m_numOfDataPoints;

		return value;
	}
	else if(m_dataType == SINE)
	{
		// Define the frequency for the sine wave
		double frequency = 0.1;

		// Calculate the sine value based on the current step
		double value = sin(m_currentStep * frequency);

		// Increment the step counter
		m_currentStep++;

		return value;
	}
	else
	{
		// Generate a random double value between 0 and 1
		double f = (double)rand() / RAND_MAX;

		// Scale and shift the random value to fit within the specified range
		return m_rangeMin + f * (m_rangeMax - m_rangeMin);
	}

}