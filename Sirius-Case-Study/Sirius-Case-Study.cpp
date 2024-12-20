#include <iostream>
#include "Sensor.h"
#include "DataProcessor.h"
#include "UserInputHandler.h"
#include <iomanip>

int main()
{
	UserInputHandler* inputHandler = new UserInputHandler(); // Create an instance of the UserInputHandler class to handle user inputs
	inputHandler->getInputs(); // Get inputs from the user for data generation parameters

	// Create an instance of the Sensor class with parameters passed from the UserInputHandler
	Sensor* s = new Sensor(inputHandler->getNumDataPoints(),
						  (DataGenerationTiming)inputHandler->getDataTimingOption(),
						  inputHandler->getDataTimingPeriod(),
						  (DataType)inputHandler->getDataType(),
						  inputHandler->getRangeMin(),
						  inputHandler->getRangeMax());

	// Create an instance of the DataProcessor class to process the generated data
	DataProcessor* dp = new DataProcessor(inputHandler->getMovingAverageWindowSize(), inputHandler->getSubsetSize());

    s->collectAndStoreDataPoints(); // Collect and store data points generated by the sensor
	dp->setRawData(s->getData());   // Pass the raw data from Sensor to the DataProcessor for processing
	dp->movingAverageFilter();	    // Apply the moving average filter to the raw data
	dp->calculateAverages();		// Calculate the average of the raw and processed data
	dp->calculateSubsetAverages();  // Calculate the average for each subset of data (for both raw and processed data)

	// Output statistics for both raw and processed data in a table format
	std::cout << "\n------------------------- Data Statistics -------------------------\n";
	std::cout << std::setw(25) << std::left << "Statistic"
		<< std::setw(15) << std::left << "Raw Data"
		<< std::setw(15) << std::left << "Processed Data"
		<< "\n";
	std::cout << "---------------------------------------------------------------\n";

	// Number of data points
	std::cout << std::setw(25) << std::left << "Number of data points"
		<< std::setw(15) << dp->getRawData().size()
		<< std::setw(15) << dp->getProcessedData().size()
		<< "\n";

	// Minimum value
	std::cout << std::setw(25) << std::left << "Minimum value"
		<< std::setw(15) << dp->getRawDataMin()
		<< std::setw(15) << dp->getProcessedDataMin()
		<< "\n";

	// Maximum value
	std::cout << std::setw(25) << std::left << "Maximum value"
		<< std::setw(15) << dp->getRawDataMax()
		<< std::setw(15) << dp->getProcessedDataMax()
		<< "\n";

	// Average value
	std::cout << std::setw(25) << std::left << "Average value"
		<< std::setw(15) << dp->getRawAverage()
		<< std::setw(15) << dp->getProcessedAverage()
		<< "\n";

	std::cout << "-----------------------------------------------------------------\n";

	inputHandler->saveDataToFile(dp->getRawData(), dp->getProcessedData());

    std::cin.get();
}

