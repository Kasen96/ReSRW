// ReSoW

#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <utility>
#include <vector>
#include <chrono>

using std::cout;
using std::endl;
using std::cerr;
using std::ios;
using std::string;
using std::vector;

float generateRand(int);
void createDataset(int, const string&);
void writeDataset(const vector<float>&, int, const string&, float, float, float);
vector<float> loadDataset(int, int, const string&);
void selectionSort(vector<float>&);
void insertSort(vector<float>&);
float getAvg(const vector<float>&);
float getMax(const vector<float>&);
float getMin(const vector<float>&);

int main(int argc, char* argv[])
{
    // <dataset size><buffer size><filename><algorithm mode>
    if (argc != 5)
    {
        cerr << "Usage: ReSoW <dataset size><buffer size><filename><algorithm mode>" << endl;
    }

    int dataset_size = std::stoi(argv[1]);
    int buffer_size = std::stoi(argv[2]);
    string filename = string(argv[3]) + ".txt";
    string result_filename = string(argv[3]) + "_result.txt";
    string algorithm_mode = argv[4];
    string algorithm_name;

    cout << "===========" << endl;

    // create the dataset
    std::ifstream f(filename);
    if (!f)
    {
        cout << "Generating the dataset..." << endl;
        createDataset(dataset_size, filename);
        cout << "Dataset is generated." << endl;

        cout << "===========" << endl;
    }
    else
    {
        f.close();
    }

    // load the dataset
    cout << "Loading the dataset..." << endl;
    auto start_load = std::chrono::high_resolution_clock::now();
    vector<float> temp = loadDataset(dataset_size, buffer_size, filename);
    auto end_load = std::chrono::high_resolution_clock::now();
    auto load_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_load - start_load).count();
    cout << "Finish loading the dataset." << endl;
    string load_duration_time = std::to_string(load_duration);
    cout << "It takes " << load_duration_time << " microseconds to load file." << endl;

    cout << "===========" << endl;

    // account avg value
    cout << "Accounting the average value..." << endl;
    auto start_avg = std::chrono::high_resolution_clock::now();
    float avg = getAvg(temp);
    auto end_avg = std::chrono::high_resolution_clock::now();
    auto avg_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_avg - start_avg).count();
    cout << "Finish accounting the average value." << endl;
    string avg_duration_time = std::to_string(avg_duration);
    cout << "It takes " << avg_duration_time << " microseconds to account the average value." << endl;

    cout << "===========" << endl;

    // find the max number
    cout << "Finding the max number..." << endl;
    auto start_max = std::chrono::high_resolution_clock::now();
    float max = getMax(temp);
    auto end_max = std::chrono::high_resolution_clock::now();
    auto max_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_max - start_max).count();
    cout << "Finish finding the max number." << endl;
    string max_duration_time = std::to_string(max_duration);
    cout << "It takes " << max_duration_time << " microseconds to find the max number." << endl;

    cout << "===========" << endl;

    // find the min number
    cout << "Finding the min number..." << endl;
    auto start_min = std::chrono::high_resolution_clock::now();
    float min = getMin(temp);
    auto end_min = std::chrono::high_resolution_clock::now();
    auto min_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_min - start_min).count();
    cout << "Finish finding the min number." << endl;
    string min_duration_time = std::to_string(min_duration);
    cout << "It takes " << min_duration_time << " microseconds to find the min number." << endl;

    cout << "===========" << endl;

    // algorithm
    cout << "Sorting the dataset..." << endl;
    auto start_sort = std::chrono::high_resolution_clock::now();
    if (algorithm_mode == "qs")
    {
         algorithm_name = "std::sort";
         std::sort(temp.begin(), temp.end()); // a highly efficient sorting algorithm based on the quick sort in the STL
    }
    else if (algorithm_mode == "ss")
    {
         algorithm_name = "selection sort";
         selectionSort(temp);
    }
    else if (algorithm_mode == "is")
    {
         algorithm_name = "insertion sort";
         insertSort(temp);
    }
    auto end_sort = std::chrono::high_resolution_clock::now();
    auto sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_sort - start_sort).count();
    cout << "Finish sorting the dataset." << endl;
    string sort_duration_time = std::to_string(sort_duration);
    cout << "It takes " << sort_duration_time << " microseconds to sort the dataset." << endl;

    cout << "===========" << endl;

    // write the dataset
    cout << "Writing the dataset..." << endl;
    auto start_write = std::chrono::high_resolution_clock::now();
    writeDataset(temp, buffer_size, result_filename, avg, max, min);
    auto end_write = std::chrono::high_resolution_clock::now();
    auto write_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_write - start_write).count();
    cout << "Finish writing the dataset." << endl;
    string write_duration_time = std::to_string(write_duration);
    cout << "It takes " << write_duration_time << " microseconds to write the dataset." << endl;

    // write time statistics
    std::ofstream file;
    file.open("time_result.txt", ios::out | ios::app);
    if (file.is_open())
    {
        file << "Dataset Size: " << dataset_size << endl;
        file << "Buffer Size:  " << buffer_size << endl;
        file << "Using " << algorithm_name << " ..." << endl;
        file << "Load Time:    " << load_duration_time << " μs" << endl;
        file << "Avg Time:     " << avg_duration_time << " μs" << endl;
        file << "Max Time:     " << max_duration_time << " μs" << endl;
        file << "Min Time:     " << min_duration_time << " μs" << endl;
        file << "Sort Time:    " << sort_duration_time << " μs" << endl;
        file << "Write Time:   " << write_duration_time << " μs" << endl;
        file << "==============" << endl;
        file.close();
    }
    else
    {
        cerr << "Can not open the file!" << endl;
    }

    return 0;
}

/**
 * get the average value.
 * @param dataset
 * @return float
 */
float getAvg(const vector<float>& dataset)
{
    return std::accumulate(dataset.cbegin(), dataset.cend(), 0.0f) / dataset.size();
}

/**
 * get the max value.
 * maxPosition: iterator to the greatest element.
 * @param dataset
 * @return float
 */
float getMax(const vector<float>& dataset)
{
    auto maxPosition = std::max_element(dataset.cbegin(), dataset.cend());
    return *maxPosition;
}

/**
 * get the min value.
 * minPosition: iterator to the smallest element.
 * @param dataset
 * @return float
 */
float getMin(const vector<float>& dataset)
{
    auto minPosition = std::min_element(dataset.cbegin(), dataset.cend());
    return *minPosition;
}

/**
 * generate a floating point random number between 0 and rmax.
 * @param rmax
 * @return float
 */
float generateRand(int rmax)
{
    std::random_device rd;
    std::mt19937 gen(rd()); // a Mersenne Twister pseudo-random generator(32 bit)
    std::uniform_real_distribution<float> dis(0.0, rmax);
    return dis(gen);
}

/**
 * create the dataset.
 * omit the vector which is not necessary in C++
 * @param size: dataset size
 * @param filename
 */
void createDataset(int size, const string& filename)
{
    /*
     * Pseudocode:
     * float v[DataSetSize];
     * for i = 1 to DataSetSize
     * {
     *     v[i]=generateRand(100);
     * }
     */

    std::ofstream file;
    file.open(filename, ios::out | ios::trunc);

    if (file.is_open())
    {
        for (int i = 0; i < size; ++i)
        {
            // create a floating point random number between 1 and 100
            file << generateRand(100) << endl;
        }
        file.close();
    }
    else
    {
        cerr << "Can not open the file!" << endl;
    }
}

/**
 * write the dataset, and define the buffer size.
 * @param dataset
 * @param bufferSize
 * @param filename
 */
void writeDataset(const vector<float>& dataset, int bufferSize, const string& filename, float avg, float max, float min)
{
    vector<char> buf(bufferSize);
    std::ofstream file;

    file.open(filename, ios::out | ios::trunc);
    // set buffer
    file.rdbuf()->pubsetbuf(buf.data(), bufferSize);

    if (file.is_open())
    {
        file << "Avg: " << avg << endl;
        file << "Max: " << max << endl;
        file << "Min: " << min << endl;
        for (float i : dataset)
        {
            file << i << endl;
        }
        file.close();
    }
    else
    {
        cerr << "Can not open the file!" << endl;
    }
}

/**
 * load the dataset and define the buffer size.
 * @param datesetSize
 * @param bufferSize
 * @param filename
 * @return vector<float>
 */
vector<float> loadDataset(int datesetSize, int bufferSize, const string& filename)
{
    vector<float> dateset;
    vector<char> buf(bufferSize);
    std::ifstream file;
    float temp = 0.0f;

    file.open(filename, ios::in);
    file.rdbuf()->pubsetbuf(buf.data(), bufferSize);

    if (file.is_open())
    {
        for (int i = 0; i < datesetSize; ++i)
        {
            file >> temp;
            dateset.push_back(temp);
        }
        file.close();
    }
    else
    {
        cerr << "Can not open the file!" << endl;
    }
    return dateset;
}

/**
 * selection sort, avg time complexity: O(n^2).
 * using std::swap.
 * @param dataset
 */
void selectionSort(vector<float>& dataset)
{
    for (size_t i = 0; i < dataset.size(); ++i)
    {
        size_t min = i;
        for (size_t j = i + 1; j < dataset.size(); ++j)
        {
            if (dataset[j] < dataset[min])
            {
                min = j;
            }
        }
        std::swap(dataset[i], dataset[min]);
    }
}

/**
 * insertion sort, avg time complexity: O(n^2).
 * @param dataset
 */
void insertSort(vector<float>& dataset)
{
    for (size_t i = 1; i < dataset.size(); ++i)
    {
        float node = dataset[i];
        size_t j = i - 1;
        while (j >= 0 && node < dataset[j])
        {
            dataset[j + 1] = dataset[j];
            --j;
        }
        dataset[j + 1] = node;
    }
}
