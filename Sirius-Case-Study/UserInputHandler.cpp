#include "UserInputHandler.h"
#include <fstream>

UserInputHandler::UserInputHandler()
{
    // Constructor body
}

UserInputHandler::~UserInputHandler()
{
    // Destructor body
}

int UserInputHandler::getNumDataPoints() const
{
    return m_numDataPoints; // Return the number of data points
}

int UserInputHandler::getDataTimingPeriod() const
{
    return m_dataTimingPeriod; // Return the data timing period in milliseconds
}

int UserInputHandler::getDataTimingOption() const
{
    return m_dataTimingOption; // Return the selected data timing option
}

int UserInputHandler::getMovingAverageWindowSize() const
{
    return m_movingAverageWindowSize; // Return the window size for the moving average filter
}

int UserInputHandler::getSubsetSize() const
{
    return m_subsetSize; // Return the size of each subset for averaging
}

int UserInputHandler::getRangeMin() const
{
    return m_rangeMin; // Return the minimum value of the data range
}

int UserInputHandler::getRangeMax() const
{
    return m_rangeMax; // Return the maximum value of the data range
}

int UserInputHandler::getDataType() const
{
    return m_dataType; // Return the selected data type
}

void UserInputHandler::getInputs()
{
    // Get number of data points
    m_numDataPoints = getIntInput("Enter the number of data points (1 to 10000): ", 1, 10000);

    // Get timing option
    std::cout << "Select timing option:\n";
    std::cout << "0 - Immediate\n";
    std::cout << "1 - Periodic\n";
    std::cout << "2 - Asynchronous\n";
    m_dataTimingOption = getIntInput("Enter your choice (0, 1 or 2): ", 0, 2);

    // If periodic, get timing period
    if (m_dataTimingOption == 1)
        m_dataTimingPeriod = getIntInput("Enter the data timing period in milliseconds (100 to 1000): ", 100, 1000);

    // Get data type
    std::cout << "Select data type:\n";
    std::cout << "0 - LINEAR\n";
    std::cout << "1 - SINUSOIDAL\n";
    std::cout << "2 - RANDOM\n";;
    m_dataType = getIntInput("Enter your choice (0, 1 or 2): ", 0, 2);

    // If RANDOM or LINEAR, get range values
    if (m_dataType == 2 || m_dataType == 0)
    {
        bool validRange = false;
        while (!validRange)
        {
            std::cout << "Enter the minimum and maximum possible values for data points (between -1000 and 1000):\n";
            m_rangeMin = getIntInput("Minimum: ", -1000, 1000);
            m_rangeMax = getIntInput("Maximum: ", -1000, 1000);

            // Check if both values are zero
            if (m_rangeMin == 0 && m_rangeMax == 0)
            {
                std::cout << "Both minimum and maximum cannot be zero. Please enter valid range values.\n";
                validRange = false;
            }
            else
                validRange = true;

            // Check if min range is lower than max range
            if (m_rangeMin >= m_rangeMax)
            {
                std::cout << "Minimum range cannot be greater or equal to maximum range. Please enter valid range values.\n";
                validRange = false;
            }
            else
                validRange = true;
        }
    }
    // Get moving average window size
    m_movingAverageWindowSize = getIntInput("Enter the moving average window size (3 to 101, odd numbers only): ", 3, 101);
    if (m_movingAverageWindowSize % 2 == 0) {
        std::cout << "Window size must be odd. Incrementing to the next odd number.\n";
        m_movingAverageWindowSize++; // Ensure it's odd
    }

    // Get subset size
    m_subsetSize = getIntInput("Enter the subset size: ", 1, m_numDataPoints);
}

void UserInputHandler::saveDataToFile(const std::vector<double>& rawData, const std::vector<double>& processedData) {
    // Ask the user if they want to save the generated data
    std::cout << "\nDo you want to save the generated data to a text file (output.txt)?\n";
    std::cout << "0 - YES\n";
    std::cout << "1 - NO\n";
    int userResponse = getIntInput("Enter your choice (0 or 1): \n", 0, 1);

    // If the user responds with "yes", proceed to save the data
    if (userResponse == 0) {
        // Open the file output.txt for writing
        std::ofstream outFile("output.txt");

        // Check if the file is open successfully
        if (outFile.is_open()) {
            // Save raw data to the file
            outFile << "Raw Data:\n";
            for (const auto& dataPoint : rawData) {
                outFile << dataPoint << "\n";  // Write each data point on a new line
            }

            // Save processed data to the file
            outFile << "\nProcessed Data:\n";
            for (const auto& dataPoint : processedData) {
                outFile << dataPoint << "\n";  // Write each processed data point on a new line
            }

            // Close the file after writing
            outFile.close();

            std::cout << "Data has been saved to 'output.txt'.\n";
        }
        else {
            std::cout << "Failed to open the file for writing.\n";
        }
    }
    else {
        std::cout << "Data was not saved.\n";
    }
}

int UserInputHandler::getIntInput(const std::string& prompt, int minValue, int maxValue)
{
    int value;

    // Infinite loop to keep asking for input until it's valid
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        // Check if input is valid (an integer within the specified range)
        if (std::cin.fail() || value < minValue || value > maxValue) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between " << minValue << " and " << maxValue << ".\n"; // Notify the user about the invalid input and prompt them to try again
        }
        else {
            // If input is valid, discard any remaining input and return the valid value
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear remaining input
            return value;
        }
    }
}