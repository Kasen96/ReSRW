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
using std::string;

float generateRand(int);
void createDataset(int, const string&);
float getAvg(const std::vector<float>&);
float getMax(const std::vector<float>&);
float getMin(const std::vector<float>&);

int main()
{
    createDataset(20, "DataSet.txt");
    return 0;
}

/**
 * get the average value.
 * @param dataset
 * @return float
 */
float getAvg(const std::vector<float>& dataset)
{
    return std::accumulate(dataset.cbegin(), dataset.cend(), 0.0f) / dataset.size();
}

/**
 * get the max value.
 * maxPosition: iterator to the greatest element.
 * @param dataset
 * @return float
 */
float getMax(const std::vector<float>& dataset)
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
float getMin(const std::vector<float>& dataset)
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
    file.open(filename, std::ios::out | std::ios::trunc);

    for (int i = 0; i < size; ++i)
    {
        // create a floating point random number between 1 and 100
        file << generateRand(100) << endl;
    }

    file.close();
}

