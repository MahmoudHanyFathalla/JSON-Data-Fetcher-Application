#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <nlohmann/json.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), curl(nullptr)
{
    ui->setupUi(this);

    // Initialize libcurl globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize libcurl easy handle
    curl = curl_easy_init();

    // Perform the CURL operations
    performCurlOperations();
}

MainWindow::~MainWindow()
{
    // Cleanup libcurl easy handle
    if (curl)
    {
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl globally
    curl_global_cleanup();

    // Delete the user interface
    delete ui;
}

/*
 *post request*
void MainWindow::performCurlOperations()
{
    try {
        // Check if libcurl easy handle is initialized
        if (!curl) {
            qCritical() << "Failed to initialize libcurl easy handle";
            return;
        }

        // Set the URL to create a new post on JSONPlaceholder
        curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts");

        // Set the callback function for writing received data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Create a string to store the raw response
        std::string response;

        // Set the string as the data to be written to
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Set the request type to POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Provide the data to be sent in the body of the POST request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, R"({"title":"New Post Title","body":"New post body","userId":1})");

        // Include required headers (e.g., Content-Type)
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the HTTP POST request
        CURLcode res = curl_easy_perform(curl);

        // Check if the HTTP request was successful
        if (res != CURLE_OK) {
            qCritical() << "curl_easy_perform() failed:" << curl_easy_strerror(res);

            // Get and log the HTTP response code in case of failure
            long httpCode = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            qCritical() << "HTTP response code:" << httpCode;
        } else {
            // Log the raw response
            qDebug() << "Raw Response:" << QString::fromStdString(response);

            // Parse the JSON response
            try {
                json jsonResponse = json::parse(response);
                qDebug() << "Parsed Response:" << QString::fromStdString(jsonResponse.dump());
                // You can now process the jsonResponse as needed
            } catch (const json::parse_error& e) {
                qCritical() << "JSON parsing error:" << e.what();
                qCritical() << "Raw JSON Response:" << QString::fromStdString(response);
            }
        }

        // Cleanup headers
        curl_slist_free_all(headers);
    } catch (const std::exception& e) {
        // Log any standard C++ exceptions that may occur
        qCritical() << "Exception occurred:" << e.what();
    } catch (...) {
        // Log any unknown exceptions that may occur
        qCritical() << "Unknown exception occurred";
    }
}
*/

void MainWindow::performCurlOperations()
{
    try
    {
        // Check if libcurl easy handle is initialized
        if (curl)
        {
            // Set the URL to retrieve information about a post from JSONPlaceholder API
            curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts");

            // Set the callback function for writing received data
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

            // Create a string to store the raw response
            std::string response;

            // Set the string as the data to be written to
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            // Add User-Agent header to the request
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "YourAppName/1.0");

            // Perform the HTTP request
            CURLcode res = curl_easy_perform(curl);

            // Check if the HTTP request was successful
            if (res != CURLE_OK)
            {
                qCritical() << "curl_easy_perform() failed:" << curl_easy_strerror(res);

                // Get and log the HTTP response code in case of failure
                long httpCode = 0;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
                qCritical() << "HTTP response code:" << httpCode;
            }
            else
            {
                // Parse the JSON response
                try
                {
                    json jsonResponse = json::parse(response);

                    // Display the JSON data in the table
                    displayJsonData(jsonResponse);
                }
                catch (const json::parse_error &e)
                {
                    qCritical() << "JSON parsing error:" << e.what();
                    qCritical() << "Raw JSON Response:" << QString::fromStdString(response);
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        // Log any standard C++ exceptions that may occur
        qCritical() << "Exception occurred:" << e.what();
    }
    catch (...)
    {
        // Log any unknown exceptions that may occur
        qCritical() << "Unknown exception occurred";
    }
}

void MainWindow::displayJsonData(const json &jsonData)
{
    // Clear the existing table contents
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Extract unique keys from the JSON data
    QStringList uniqueKeys;
    for (const auto &jsonItem : jsonData)
    {
        if (jsonItem.is_object())
        {
            for (auto it = jsonItem.begin(); it != jsonItem.end(); ++it)
            {
                QString key = QString::fromStdString(it.key());
                if (!uniqueKeys.contains(key))
                {
                    uniqueKeys.append(key);
                }
            }
        }
        else
        {
            qWarning() << "Invalid JSON array item encountered (not an object).";
        }
    }

    // Add headers
    ui->tableWidget->setColumnCount(uniqueKeys.size());
    ui->tableWidget->setHorizontalHeaderLabels(uniqueKeys);

    // Populate the table with JSON data
    for (const auto &jsonItem : jsonData)
    {
        if (jsonItem.is_object())
        {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            for (const QString &key : uniqueKeys)
            {
                auto it = jsonItem.find(key.toStdString());
                QString value = (it != jsonItem.end()) ? QString::fromStdString(it.value().dump()) : "";

                // Remove double quotes from the displayed values
                value.remove(QChar('"'), Qt::CaseInsensitive);

                int column = uniqueKeys.indexOf(key);
                auto item = new QTableWidgetItem(value);

                // Make the QTableWidgetItem uneditable
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);

                ui->tableWidget->setItem(row, column, item);
            }
        }
        else
        {
            qWarning() << "Invalid JSON array item encountered (not an object).";
        }
    }
}






size_t MainWindow::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    // Calculate the total size of the received data
    size_t realsize = size * nmemb;

    // Cast the user data pointer to a std::string pointer
    std::string *result = static_cast<std::string *>(userp);

    // Append the received data to the result string
    result->append(static_cast<char *>(contents), realsize);

    // Return the total size of the received data
    return realsize;
}
