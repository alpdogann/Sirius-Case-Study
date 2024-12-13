#include <iostream>
#include "Sensor.h"
#include "DataProcessor.h"
#include "UserInputHandler.h"

int main()
{


	UserInputHandler* inputHandler = new UserInputHandler();
	inputHandler->getInputs();

	Sensor* s = new Sensor(inputHandler->getNumDataPoints(), (DataGenerationTiming)inputHandler->getDataTimingOption(),
		inputHandler->getDataTimingPeriod(), (DataType)inputHandler->getDataType(), inputHandler->getRangeMin(), inputHandler->getRangeMax());

	DataProcessor* dp = new DataProcessor(inputHandler->getMovingAverageWindowSize(), inputHandler->getSubsetSize());

    s->collectAndStoreDataPoints();
	dp->setRawData(s->getData());
	dp->movingAverageFilter();
	dp->calculateAverages();
	dp->calculateSubsetAverages();

	std::cout << "\nNumber of data points: " << dp->getRawData().size() << "\n";
	std::cout << "Minimum value: " << dp->getRawDataMin() << "\n";
	std::cout << "Maximum value: " << dp->getRawDataMax() << "\n";
	std::cout << "Average value: " << dp->getRawAverage() << "\n";

	std::cout << "\nNumber of data points: " << dp->getProcessedData().size() << "\n";
	std::cout << "Minimum value: " << dp->getProcessedDataMin() << "\n";
	std::cout << "Maximum value: " << dp->getProcessedDataMax() << "\n";
	std::cout << "Average value: " << dp->getProcessedAverage() << "\n";

	inputHandler->saveDataToFile(dp->getRawData(), dp->getProcessedData());

    std::cin.get();
}

