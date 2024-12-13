#include <vector>

class DataProcessor
{
public:
	/**
 * @brief Constructs a DataProcessor object for processing sensor data.
 *
 * Initializes the DataProcessor with specified values for the moving average window size and subset size.
 *
 * @param movingAverageWindowSize The size of the moving average window (default: 3).
 * @param subsetSize The number of elements in each subset for averaging (default: 3).
 */
	DataProcessor(int movingAverageWindowSize = 3, int subsetSize = 3);
	~DataProcessor();

	/**
 * @brief Retrieves the raw data processed by the DataProcessor.
 *
 * @return A copy to the vector of raw data.
 */
	std::vector<double> getRawData() const;
	/**
 * @brief Retrieves the processed data after applying the moving average filter.
 *
 * @return A copy to the vector of processed data.
 */
	std::vector<double> getProcessedData() const;
	/**
 * @brief Retrieves the raw subset average data.
 *
 * @return A copy to the vector of raw subset averages.
 */
	std::vector<double> getRawSubsetAverageData() const;
	/**
 * @brief Retrieves the processed subset average data.
 *
 * @return A copy to the vector of processed subset averages.
 */
	std::vector<double> getProcessedSubsetAverageData() const;
	/**
 * @brief Calculates the subset averages of the given data vector.
 *
 * This function divides the input vector into subsets of a fixed size (`m_subsetSize`),
 * calculates the average for each subset, and returns a vector of the subset averages.
 * If the number of elements in the input vector is not a multiple of `m_subsetSize`,
 * the function adds padding to the end of the vector to complete the last subset.
 *
 * @param vec The vector of data for which the subset averages will be calculated.
 * @return A vector containing the averages of each subset.
 */
	std::vector<double> calculateSubsetAverage(const std::vector<double>& vec) const;
	/**
 * @brief Retrieves the minimum value from the raw data.
 *
 * This function calculates and returns the smallest value in the raw data vector,
 * `m_rawData`, using the `std::min_element` algorithm.
 *
 * @return The minimum value in the raw data vector.
 */
	double getRawDataMin() const;
	/**
 * @brief Retrieves the maximum value from the raw data.
 *
 * This function calculates and returns the largest value in the raw data vector,
 * `m_rawData`, using the `std::max_element` algorithm.
 *
 * @return The maximum value in the raw data vector.
 */
	double getRawDataMax() const;
	/**
 * @brief Retrieves the minimum value from the processed data.
 *
 * This function calculates and returns the smallest value in the processed data vector,
 * `m_processedData`, using the `std::min_element` algorithm.
 *
 * @return The minimum value in the processed data vector.
 */
	double getProcessedDataMin() const;
	/**
 * @brief Retrieves the maximum value from the processed data.
 *
 * This function calculates and returns the largest value in the processed data vector,
 * `m_processedData`, using the `std::max_element` algorithm.
 *
 * @return The maximum value in the processed data vector.
 */
	double getProcessedDataMax() const;
	/**
 * @brief Retrieves the average of the raw data.
 *
 * This function returns the average value of the raw data stored in `m_rawAverage`.
 *
 * @return The average value of the raw data.
 */
	double getRawAverage() const;
	/**
 * @brief Retrieves the average of the processed data.
 *
 * This function returns the average value of the processed data stored in `m_processedAverage`.
 * The processed data is typically the result after applying any data filtering or transformation.
 *
 * @return The average value of the processed data.
 */
	double getProcessedAverage() const;
	/**
 * @brief Calculates the average of a given data vector.
 *
 * This function computes the average by summing all elements of the input vector
 * and dividing by the number of elements. If the vector is empty, it does not perform
 * the calculation and returns nothing.
 *
 * @param vec The vector of data for which the average is to be calculated.
 * @return The average value of the elements in the vector, or 0.0 if the vector is empty.
 */
	double calculateAverage(const std::vector<double>& vec);
	/**
 * @brief Sets the raw data for the DataProcessor.
 *
 * This function updates the internal `m_rawData` vector with the provided data vector `vec`.
 * It replaces the current raw data with the new data and recalculates any necessary values,
 * such as averages or processed data.
 *
 * @param vec A vector containing the new raw data to be processed.
 */
	void setRawData(const std::vector<double>& vec);
	/**
	 * @brief Calculates the averages of the raw and processed data.
	 *
	 * This function calls the helper function `calculateAverage` twice:
	 * once for `m_rawData` and once for `m_processedData`. It stores the results
	 * in `m_rawAverage` and `m_processedAverage`, respectively.
	 * If the data vectors are empty, their averages remain unchanged.
	 */
	void calculateAverages();
	/**
 * @brief Calculates the subset averages for both raw and processed data.
 *
 * This function calls `calculateSubsetAverage` for both the raw data (`m_rawData`)
 * and processed data (`m_processedData`) and stores the resulting subset averages
 * in `m_rawSubsetAverageData` and `m_processedSubsetAverageData`, respectively.
 */
	void calculateSubsetAverages();
	/**
 * @brief Applies a moving average filter to the raw data.
 *
 * This function performs a simple moving average filtering operation on the raw data (`m_rawData`),
 * smoothing the data by averaging each point with its neighboring points. The window size of the filter
 * is defined by `m_windowSize`. The filtered result is stored in `m_processedData`.
 *
 * The algorithm works as follows:
 * 1. The raw data is padded with the first and last values to handle edge cases.
 * 2. For each data point, the function calculates the sum of the current point and its neighbors
 *    within the window size, then scales the sum to calculate the average.
 * 3. The averages are stored in the `m_processedData` vector.
 */
	void movingAverageFilter();

private:

	std::vector<double> m_rawData;					  // A vector containing the raw data that will be processed by the filter and averaging functions
	std::vector<double> m_processedData;			  // A vector containing the processed data after applying filters or transformations on the raw data
	std::vector<double> m_rawSubsetAverageData;		  // A vector to store the average of the raw data in subsets, where each element corresponds to the average of a subset
	std::vector<double> m_processedSubsetAverageData; // A vector to store the average of the processed data in subsets, similar to m_rawSubsetAverageData
	double m_rawAverage;							  // The average value of the raw data. This value is updated after processing the raw data
	double m_processedAverage;						  // The average value of the processed data. This value is updated after processing the raw data
	int m_windowSize;								  // The size of the moving average window used in the filter. Defines how many data points are considered for calculating each average
	int m_subsetSize;								  // The size of the subsets used when calculating the subset averages. Defines how many elements are grouped together to calculate each subset average
};

