# JSON Data Fetcher and Display Application

## Overview
This project is a C++ application built using the Qt framework. It fetches JSON data from a public API (JSONPlaceholder) using libcurl, parses the data using the nlohmann/json library, and displays it in a user-friendly table format within a Qt-based GUI. The application is designed to be cross-platform and supports both Qt5 and Qt6.

## Features
- **HTTP Requests**: Utilizes libcurl to perform HTTP GET requests to fetch JSON data from the JSONPlaceholder API.
- **JSON Parsing**: Uses the nlohmann/json library to parse the fetched JSON data.
- **GUI Display**: Displays the parsed JSON data in a QTableWidget within a Qt-based GUI.
- **Cross-Platform**: Supports both Qt5 and Qt6, making it compatible with multiple platforms.
- **Translation Support**: Includes support for internationalization (i18n) with Qt Linguist.

## Prerequisites
Before building and running the project, ensure you have the following installed:

- **CMake** (version 3.5 or higher)
- **Qt** (version 5 or 6)
- **libcurl** (version 8.5.0 or higher)
- **nlohmann/json** library
- **C++ Compiler** with C++17 support

## Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/your-repo-name.git
cd your-repo-name
```

### 2. Install Dependencies
Ensure that Qt, libcurl, and nlohmann/json are installed on your system. You can install them using your package manager or download them manually.

- **Qt**: Follow the official [Qt installation guide](https://www.qt.io/download).
- **libcurl**: Download and install from the [official website](https://curl.se/download.html).
- **nlohmann/json**: Include the single header file from the [GitHub repository](https://github.com/nlohmann/json).

### 3. Configure the Project
Update the paths in the `CMakeLists.txt` file to point to your local installations of libcurl and nlohmann/json.

```cmake
# Update these paths to match your local environment
set(CURL_DIR "C:/path/to/curl")
set(NLOHMANN_JSON_INCLUDE_DIR "C:/path/to/json/single_include")
```

### 4. Build the Project
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 5. Run the Application
After building the project, you can run the executable:

```bash
./untitled
```

## Usage
1. **Launch the Application**: Run the executable to start the application.
2. **Fetch Data**: The application will automatically fetch JSON data from the JSONPlaceholder API and display it in the table.
3. **View Data**: The fetched JSON data will be displayed in a tabular format, with each key as a column header and the corresponding values in the rows.

## Project Structure
- **CMakeLists.txt**: CMake configuration file for building the project.
- **main.cpp**: Entry point of the application, initializes the Qt application and sets up translation support.
- **mainwindow.h**: Header file for the `MainWindow` class, containing declarations for the main window and its components.
- **mainwindow.cpp**: Implementation of the `MainWindow` class, including functions for performing HTTP requests, parsing JSON, and displaying data.
- **mainwindow.ui**: Qt Designer UI file defining the layout of the main window.
- **untitled_en_GB.ts**: Translation file for English (United Kingdom).

## Customization
- **API Endpoint**: You can change the API endpoint in the `performCurlOperations` function in `mainwindow.cpp` to fetch data from a different API.
- **Table Display**: Modify the `displayJsonData` function in `mainwindow.cpp` to customize how the JSON data is displayed in the table.
- **Translations**: Add more translation files and update the `TS_FILES` variable in `CMakeLists.txt` to support additional languages.

## Troubleshooting
- **Build Errors**: Ensure that all dependencies are correctly installed and the paths in `CMakeLists.txt` are accurate.
- **Runtime Errors**: Check the console output for any error messages related to libcurl or JSON parsing.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
- **Qt**: For providing a powerful framework for building cross-platform applications.
- **libcurl**: For enabling easy HTTP requests.
- **nlohmann/json**: For a simple and efficient JSON parsing library.
