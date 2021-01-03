// ReSoW

#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::cerr;
using std::ios;
using std::string;
using std::vector;

float generateRand(int);
void createDataset(int, const string&);
void writeDataset(const vector<float>&, int, const string&);
vector<float> loadDataset(int, int, const string&);
float getAvg(const vector<float>&);
float getMax(const vector<float>&);
float getMin(const vector<float>&);

int main()
{
    createDataset(20, "DataSet.txt");
    vector<float> temp = loadDataset(20, 10, "DataSet.txt");
    for (float i : temp)
    {
        cout << i << endl;
    }
    cout << "Avg: " << getAvg(temp) << endl;
    cout << "Max: " << getMax(temp) << endl;
    cout << "Min: " << getMin(temp) << endl;
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
void writeDataset(const vector<float>& dataset, int bufferSize, const string& filename)
{
    vector<char> buf(bufferSize);
    std::ofstream file;

    file.open(filename, ios::out | ios::app);
    // set buffer
    file.rdbuf()->pubsetbuf(buf.data(), bufferSize);

    if (file.is_open())
    {
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
