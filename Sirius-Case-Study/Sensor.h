#include <vector>

/**
 * @brief Represents the timing mode for generating sensor data.
 *
 * Defines the timing behavior for data generation:
 * - **eImmediate**: Data points are generated immediately without delay.
 * - **ePeriodic**: Data points are generated with a fixed delay between each point.
 * - **eAsynchronous**: Data points are generated with a random delay between 100-300 milliseconds.
 */
enum DataGenerationTiming
{
	eImmediate = 0, ///< Immediate data generation with no delay.
	ePeriodic,      ///< Data generation with a fixed periodic delay.
	eAsynchronous   ///< Data generation with a random delay.
};

/**
 * @brief Represents the different types of sensor data generation.
 *
 * This enumeration defines the possible data generation types:
 * - **LINEAR**: Generates linearly spaced data points.
 * - **SINE**: Generates data points following a sinusoidal pattern.
 * - **RANDOM**: Generates data points with random values within a specified range.
 */
enum DataType 
{ 
	LINEAR = 0,  ///< Linearly spaced data points.
	SINE,        ///< Sinusoidal data points.
	RANDOM       ///< Randomly generated data points within a specified range.
};

class Sensor
{
public:
	/**
 * @brief Constructs a Sensor object with configurable parameters.
 *
 * Initializes the Sensor with user-defined or default values for data generation.
 * The parameters include the number of data points to generate, timing settings,
 * data type, and the range of values.
 *
 * @param numDataPoints The number of data points to generate (default: 10).
 * @param generationTiming The timing mode for data generation (default: eImmediate).
 *        - eImmediate: No delay between data points.
 *        - ePeriodic: Fixed delay specified by `periodIfNecessary`.
 *        - eAsync: Random delay between 100-300 milliseconds.
 * @param periodIfNecessary The period for periodic data generation in milliseconds
 *        (default: 100). Used only when `generationTiming` is ePeriodic.
 * @param dataType The type of data to generate (default: LINEAR).
 *        - LINEAR: Linearly spaced data.
 *        - SINE: Sinusoidal data.
 *        - RANDOM: Random data within the range.
 * @param rangeMin The minimum value of the data range (default: -100.0).
 * @param rangeMax The maximum value of the data range (default: 100.0).
 */
	Sensor(int numDataPoints = 10, DataGenerationTiming generationTiming = eImmediate, int periodIfNecessary = 100,
		DataType dataType = LINEAR, double rangeMin = -100.0, double rangeMax = 100.0);
	~Sensor();

	/**
 * @brief Collects and stores multiple data points based on the selected generation timing.
 *
 * This method generates and stores `m_numOfDataPoints` data points into `m_physicalData`
 * using the timing specified by `m_generationTiming`:
 * - **eImmediate**: Generates all data points as quickly as possible without delay.
 * - **ePeriodic**: Generates data points with a fixed delay (`m_periodForGeneration`) between each point.
 * - **eAsync**: Generates data points with a random delay between 100 and 300 milliseconds.
 *
 * Additionally, a message "Data Generated" is printed to the console for each point.
 */
	void collectAndStoreDataPoints();

	/**
 * @brief Retrieves the collected sensor data.
 *
 * @return A constant reference to the vector containing the collected data points.
 */
	const std::vector<double>& getData() const;

private:

	std::vector<double> m_physicalData;		 // A container to store the generated data points
	DataGenerationTiming m_generationTiming; // Specifies the timing mode for data generation
	int m_periodForGeneration;				 // The delay period (in milliseconds) used for periodic data generation
	int m_numOfDataPoints;					 // The total number of data points to generate
	int m_dataType;							 // The type of data to generate
	double m_rangeMin;						 // The minimum value in the range of generated data
	double m_rangeMax;						 // The maximum value in the range of generated data
	int m_currentStep;						 // Tracks the current step for deterministic data generation

	/**
 * Generates a single data point based on the current data type.
 *
 * The method produces a data point depending on the `m_dataType`:
 * - **LINEAR**: Generates linearly spaced values between `m_rangeMin` and `m_rangeMax`.
 * - **SINE**: Produces sinusoidal values based on a fixed frequency.
 * - **RANDOM**: Produces random values uniformly distributed within the specified range.
 *
 * @return A double representing the generated data point.
 */
	double generateDataPoint();
};

