# Sirius-Case-Study
Sirius Design Lab Case Study

## Overview

This program allows users to generate, process, and optionally save raw and processed data. The user can specify the number of data points, data generation timing, data type (Linear, Sinusoidal, or Random), range, moving average window size, and more. The program then performs the necessary processing and provides the option to save the raw and processed data to a text file.

## Instructions for Compiling and Running the Program

### Prerequisites:
- **Visual Studio 2022** with C++ development tools installed.

### Clone the Repository:
 ```bash
 git clone https://github.com/alpdogann/Sirius-Case-Study.git
 ```
     
### Steps to Compile and Run:

1. **Open Visual Studio**:
   
2. **Launch the Project**:

3. **Build the Project**:
   - Click **Build** in the top menu and select **Build Solution** (or press `Ctrl+Shift+B`).
   - Visual Studio will compile the code into an executable.

4. **Run the Program**:
   - Once the project is built successfully, click **Debug** > **Start Without Debugging** (or press `Ctrl+F5`).
   - Follow the prompts in the terminal to input data, select options, and choose whether to save the generated data.

### Example Build Output:
If the program is successfully compiled and run, it will prompt the user for input and display the corresponding results.

## Assumptions Made During Development

1. **Valid User Inputs**: The program assumes that the user will provide valid inputs within the specified ranges. In case of invalid inputs, the program prompts the user to re-enter the values.
   
2. **Data Ranges**: For **Linear** and **Random** data types, the program assumes that the user will specify a valid range for both the minimum and maximum values.

3. **Integer Only Inputs**: The program assumes that the user will provide integers when prompted for numerical input (e.g., number of data points, window size, range, etc.).

4. **File Handling**: The program assumes that the current working directory is writable, as it attempts to create and write to the `output.txt` file.

5. **Use of `double` Data Type**: The program assumes that the generated data points are of type `double`. This allows for more precise data representation, especially for real-world measurements that might involve decimal values.

## Design Choices

1. **Modular Design**:
   - The program has been divided into separate classes with specific responsibilities: `UserInputHandler` for handling user input, `DataProcessor` for processing the data and 'Sensor' for generating the data. This makes the code more readable and maintainable.
   
2. **Data Types**:
   - Chose to allow multiple data types (`LINEAR`, `SINUSOIDAL`, `RANDOM`) because it provides flexibility in generating different kinds of data for further processing. Each data type has its own characteristics (e.g., `LINEAR` for predictable, `SINUSOIDAL` for periodic, and `RANDOM` for unpredictable data).
   
3. **User-Friendly Input Validation**:
   - The program uses a loop to repeatedly ask the user for valid input if the input is out of range or incorrectly formatted. This ensures that the program operates smoothly without unexpected crashes or errors.
   
4. **File Output**:
   - Implemented the option to save the raw and processed data to a text file (`output.txt`). This allows the user to save their work for later reference or analysis. The file format is simple and easy to parse (with one value per line).
   - 
5. **Moving Average Filter**:
   - The choice of implementing a simple moving average filter was made to smooth the data and reduce noise, which is a common requirement in data processing. I used a sliding window approach to compute the moving average.

## Bonus Features Implemented

1. **Flexible Data Range Handling**:
   - The program handles both **negative** and **positive** ranges for `m_rangeMin` and `m_rangeMax` for **Linear** and **Random** data types, allowing the user to generate data with different characteristics (e.g., negative data points for modeling negative values).
   
2. **File Output Option**:
   - After generating the data, the program asks the user if they want to save the generated raw and processed data to a file (`output.txt`). If the user selects "YES", both datasets are saved to the file in a readable format with headers ("Raw Data" and "Processed Data").
   
3. **Moving Average Window Adjustment**:
   - The program automatically adjusts the moving average window size to ensure it is always an **odd number**, as required for the moving average filter to function properly.
   
4. **Handling of Invalid Inputs**:
   - The program handles invalid inputs by clearing and ignoring invalid input streams, prompting the user to enter valid values. This prevents the program from crashing due to invalid user inputs.
