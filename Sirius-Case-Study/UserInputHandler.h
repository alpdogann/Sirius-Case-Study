#include <iostream>
#include <string>
#include <limits>
#include <vector>

class UserInputHandler
{
public:

    UserInputHandler();
    ~UserInputHandler();

    /**
 * @brief Retrieves the number of data points.
 *
 * This function returns the value of `m_numDataPoints`, which represents the number
 * of data points that the user has specified.
 *
 * @return The number of data points.
 */
    int getNumDataPoints() const;
    /**
 * @brief Retrieves the data timing period in milliseconds.
 *
 * This function returns the value of `m_dataTimingPeriod`, which represents the
 * period (in milliseconds) for data generation timing when the `ePeriodic` option is selected.
 *
 * @return The data timing period in milliseconds.
 */
    int getDataTimingPeriod() const;
    /**
 * @brief Retrieves the selected data timing option.
 *
 * This function returns the value of `m_dataTimingOption`, which represents the
 * user's selection for data timing. It could be options like `eImmediate`, `ePeriodic`, etc.
 *
 * @return The data timing option.
 */
    int getDataTimingOption() const;
    /**
 * @brief Retrieves the window size for the moving average filter.
 *
 * This function returns the value of `m_movingAverageWindowSize`, which defines the
 * size of the moving average window used for filtering the data.
 *
 * @return The size of the moving average window.
 */
    int getMovingAverageWindowSize() const;
    /**
 * @brief Retrieves the subset size for averaging.
 *
 * This function returns the value of `m_subsetSize`, which specifies the number of elements
 * to include in each subset for subset averaging.
 *
 * @return The size of each subset.
 */
    int getSubsetSize() const;
    /**
 * @brief Retrieves the minimum value of the data range.
 *
 * This function returns the value of `m_rangeMin`, which represents the minimum value
 * of the data range. This value is used for constraining data generation or processing.
 *
 * @return The minimum value of the data range.
 */
    int getRangeMin() const;
    /**
 * @brief Retrieves the maximum value of the data range.
 *
 * This function returns the value of `m_rangeMax`, which represents the maximum value
 * of the data range. This value is used for constraining data generation or processing.
 *
 * @return The maximum value of the data range.
 */
    int getRangeMax() const;
    /**
 * @brief Retrieves the selected data type.
 *
 * This function returns the value of `m_dataType`, which represents the data type selected
 * by the user (such as `LINEAR`, `SINE`, `RANDOM`, etc.).
 *
 * @return The data type.
 */
    int getDataType() const;
    
    /**
 * @brief Prompts the user for an integer input within a specified range.
 *
 * This function continuously prompts the user for input until a valid integer is entered
 * within the specified range (inclusive). If the user enters invalid input (non-integer or
 * out-of-range values), it will ask the user to try again.
 *
 * @param prompt The prompt message displayed to the user.
 * @param minValue The minimum valid value the user can enter.
 * @param maxValue The maximum valid value the user can enter.
 * @return A valid integer within the specified range.
 */
    void getInputs();
    /**
 * @brief Prompts the user to save the generated data to a text file.
 *
 * This function asks the user whether they want to save the generated raw and processed data
 * to a text file named `output.txt`. If the user confirms, the function writes the raw and
 * processed data to the file. If the file is successfully opened, the data is written with
 * "Raw Data" and "Processed Data" headings, each data point on a new line. If the user declines
 * or the file cannot be opened, appropriate messages are displayed.
 *
 * @param rawData A vector containing the raw data points.
 * @param processedData A vector containing the processed data points.
 */
    void saveDataToFile(const std::vector<double>& rawData, const std::vector<double>& processedData);

private:

    int m_numDataPoints;           // The number of data points to be generated or processed
    int m_dataTimingPeriod;        // The data timing period in milliseconds, relevant only when the data timing option is set to 'Periodic'
    int m_movingAverageWindowSize; // The size of the moving average window
    int m_subsetSize;              // The number of elements in each subset for subset averaging
    int m_dataTimingOption;        // The data timing option selected by the user
    int m_dataType;                // The type of data generation selected by the user
    int m_rangeMin;                // The minimum possible value for data points
    int m_rangeMax;                // The maximum possible value for data points
    
    /**
 * @brief Prompts the user for various input parameters.
 *
 * This function prompts the user to input values for the following parameters:
 * - Number of data points
 * - Data timing options (Immediate, Periodic, or Asynchronous)
 * - Data type (Linear, Sinusoidal, or Random)
 * - Range for Linear and Random data types
 * - Moving average window size
 * - Subset size
 *
 * The function ensures that the input values are within valid ranges and enforces constraints
 * such as using odd numbers for the moving average window size. Invalid inputs are rejected
 * and the user is prompted again until valid values are provided.
 */
    int getIntInput(const std::string& prompt, int minValue, int maxValue);
};

