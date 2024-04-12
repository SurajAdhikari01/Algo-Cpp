#include <iostream>
#include <iostream>
#include <time.h>
#include <cstdlib>

class DataGenerator
{
private:
    int dataArray[20];

public:
    int getNumberOfData()
    {
        int numberOfData;
        std::cout << "Enter number of data: ";
        std::cin >> numberOfData;
        return numberOfData;
    }
    int *generateData(int numberOfData)
    {

        int upperBound;
        int lowerBound;

        upperBound = numberOfData * 2;
        lowerBound = 0;
        srand(time(0));
        for (int i = 0; i < numberOfData; i++)
        {
            dataArray[i] = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
        }
        std::cout << "Data generated successfully " << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {
            std::cout << dataArray[i] << " ";
        }
        std::cout << std::endl;
        return dataArray;
    }
};
class AlgorithmSelection
{
private:
    int choiceIndex[2];

public:
    int *displayMenu()
    {

        std::cout << "Enter your choice: " << std::endl;
        std::cout << "1. Searching Algorithms" << std::endl;
        std::cout << "2. Sorting Algorithms" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choiceIndex[0];
        bool invalidOption = true;
        while (invalidOption)
        {
            switch (choiceIndex[0])
            {
            case 1:

                std::cout << "Enter your choice: " << std::endl;
                std::cout << "1. Linear Search" << std::endl;
                std::cout << "2. Binary Search" << std::endl;
                std::cout << "3. Exit" << std::endl;
                std::cout << "Your choice: ";
                std::cin >> choiceIndex[1];
                if (choiceIndex[1] < 1 || choiceIndex[1] > 2)
                {
                    std::cout << "Invalid choice" << std::endl;
                }
                else
                {
                    invalidOption = false;
                }
                break;
            case 2:

                std::cout << "Enter your choice: " << std::endl;
                std::cout << "1. Bubble Sort" << std::endl;
                std::cout << "2. Insertion Sort" << std::endl;
                std::cout << "3. Selection Sort" << std::endl;
                std::cout << "4. Quick Sort" << std::endl;
                std::cout << "5. Merge Sort" << std::endl;
                std::cout << "6. Heap Sort" << std::endl;
                std::cout << "7. Radix Sort" << std::endl;
                std::cout << "Your choice: ";
                std::cin >> choiceIndex[1];
                if (choiceIndex[1] < 1 || choiceIndex[1] > 7)
                {
                    std::cout << "Invalid choice" << std::endl;
                    invalidOption = true;
                }
                else
                {
                    invalidOption = false;
                }

                break;
            case 3:
                exit(0);
                break;
            default:
                break;
            }
        }
        return choiceIndex;
    }
};
class SearchAlgorithmVisualizer
{

public:
    int getSearchValue()
    {
        int searchValue;
        std::cout << "Enter value to be Searched: ";
        std::cin >> searchValue;
        return searchValue;
    }
    void visualizer(int choiceIndex, int dataArraySize, int dataArray[], int searchValue)
    {
        int searchIndexStatus[dataArraySize];
        for (int i = 0; i < dataArraySize; i++)
        {
            searchIndexStatus[i] = 0;
        }
        switch (choiceIndex)
        {
        case 1:
            linearSearch(dataArraySize, dataArray, searchIndexStatus, searchValue);
            break;
        case 2:
            binarySearch(dataArraySize, dataArray, searchIndexStatus, searchValue);
            break;
        default:
            break;
        }
    }
    // Sorting data array
    void sortDataArray(int dataArray[], int numberOfData)
    {
        for (int i = 0; i < numberOfData; i++)
        {
            for (int j = i + 1; j < numberOfData; j++)
            {
                if (dataArray[i] > dataArray[j])
                {
                    int temp = dataArray[i];
                    dataArray[i] = dataArray[j];
                    dataArray[j] = temp;
                }
            }
        }
    }
    void linearSearch(int numberOfData, int dataArray[], int searchIndexStatus[], int searchValue)
    {
        clock_t start, end;
        start = clock();

        std::cout << "Status of data (Not Searched = 0 || Searched  = 1 || Found = 2)" << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {
            searchIndexStatus[i] = 1;
            if (dataArray[i] == searchValue)
            {

                std::cout << searchValue << " found at index " << i << std::endl;
                searchIndexStatus[i] = 2;
            }

            visualizeDataStatus(dataArray, numberOfData, searchIndexStatus);
        }
        end = clock();
        std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
    }
    void binarySearch(int numberOfData, int dataArray[], int searchIndexStatus[], int searchValue)
    {

        sortDataArray(dataArray, numberOfData); // To perform binary search we first need to perform sorting of data
        std::cout << "Status of data (Not Searched = 0 || Searched  = 1 || Found = 2)" << std::endl;
        visualizeDataStatus(dataArray, numberOfData, searchIndexStatus); // Showing current data location on array
        clock_t start, end;
        start = clock();
        int left = 0;
        int right = numberOfData - 1;
        while (left <= right)
        {

            int midIndex = (left + right) / 2;
            if (dataArray[midIndex] == searchValue)
            {
                searchIndexStatus[midIndex] = 2;
                visualizeDataStatus(dataArray, numberOfData, searchIndexStatus);
                std::cout << searchValue << " found at index " << midIndex << std::endl;

                end = clock();
                std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;

                return;
            }
            else if (dataArray[midIndex] < searchValue)
            {
                searchIndexStatus[midIndex] = 1;
                for (int i = 0; i < midIndex; i++)
                {
                    searchIndexStatus[i] = 4;
                }
                visualizeDataStatus(dataArray, numberOfData, searchIndexStatus);
                left = midIndex + 1;
            }
            else
            {
                searchIndexStatus[midIndex] = 1;
                for (int i = (numberOfData - 1); i > midIndex; i--)
                {
                    searchIndexStatus[i] = 4;
                }
                visualizeDataStatus(dataArray, numberOfData, searchIndexStatus);
                right = midIndex - 1;
            }
        }

        std::cout << searchValue << " not found at any index " << std::endl;
        end = clock();
        std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
    }

    // Showing status array
    void visualizeDataStatus(int dataArray[], int numberOfData, int indexSearchStatus[])
    {
        std::cout << std::endl;
        std::cout << "Data Array: " << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {

            std::cout << dataArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Status Array: " << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {
            std::cout << indexSearchStatus[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
};
class SortAlgorithmVisualizer
{
public:
    void visualizer(int choiceIndex, int dataArraySize, int dataArray[])
    {
        int searchIndexStatus[dataArraySize];
        for (int i = 0; i < dataArraySize; i++)
        {
            searchIndexStatus[i] = 0;
        }
        switch (choiceIndex)
        {
        case 1:
            BubbleSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        case 2:
            InsertionSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        case 3:
            SelectionSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        case 4:
            QuickSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        case 5:
            MergeSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        case 6:
            HeapSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        case 7:
            RadixSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        default:
            break;
        }
    }

    void BubbleSort(int numberOfData, int dataArray[], int searchIndexStatus[])
    {
        clock_t start, end;
        start = clock();
        for (int i = 0; i < numberOfData - 1; i++)
        {
            std::cout << "Iteration: " << (i + 1) << std::endl;
            for (int j = 0; j < numberOfData - i - 1; j++)
            {
                if (dataArray[j] > dataArray[j + 1])
                {
                    int temp = dataArray[j];
                    dataArray[j] = dataArray[j + 1];
                    dataArray[j + 1] = temp;
                    searchIndexStatus[j] = 1;
                    searchIndexStatus[j + 1] = 1;
                    visualizeDataStatus(dataArray, numberOfData, searchIndexStatus);
                    searchIndexStatus[j] = 0;
                    searchIndexStatus[j + 1] = 0;
                }
            }
        }
        end = clock();
        std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
    }
    void InsertionSort(int numberOfData, int dataArray[], int searchIndexStatus[])
    {
        clock_t start, end;
        start = clock();
        std::cout << "Initial data:" << std::endl;
        visualizeDataStatus(dataArray, numberOfData, searchIndexStatus, -1);

        for (int i = 1; i < numberOfData; i++)
        {
            std::cout << "Iteration: " << i << std::endl;
            int key = dataArray[i];
            int j = i - 1;

            while (j >= 0 && dataArray[j] > key)
            {
                dataArray[j + 1] = dataArray[j];
                j = j - 1;
            }
            dataArray[j + 1] = key;

            // Set status for the elements being worked on
            searchIndexStatus[i] = 1;
            searchIndexStatus[i - 1] = 1;

            visualizeDataStatus(dataArray, numberOfData, searchIndexStatus, i);

            // Reset status after visualization
            searchIndexStatus[i] = 0;
            searchIndexStatus[i - 1] = 0;
        }

        end = clock();
        std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
    }

    void SelectionSort(int numberOfData, int dataArray[], int searchIndexStatus[])
    {
        clock_t start, end;
        start = clock();
        for (int i = 0; i < numberOfData - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < numberOfData; j++)
            {
                if (dataArray[j] < dataArray[minIndex])
                {
                    minIndex = j;
                }
            }

            // Swap the minimum element with the first element
            searchIndexStatus[minIndex] = 1;
            searchIndexStatus[i] = 1;

            int temp = dataArray[i];

            dataArray[i] = dataArray[minIndex];
            dataArray[minIndex] = temp;
            visualizeDataStatus(dataArray, numberOfData, searchIndexStatus);
            searchIndexStatus[minIndex] = 0;
            searchIndexStatus[i] = 0;
        }
        end = clock();
        std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
    }

    void QuickSort(int numberOfData, int dataArray[], int searchIndexStatus[])
    {
    }
    void MergeSort(int numberOfData, int dataArray[], int searchIndexStatus[])
    {
    }
    void HeapSort(int numberOfData, int dataArray[], int searchIndexStatus[])
    {
    }
    void RadixSort(int numberOfData, int dataArray[], int searchIndexStatus[])
    {
    }

    void visualizeDataStatus(int dataArray[], int numberOfData, int indexSearchStatus[])
    {
        std::cout << std::endl;
        std::cout << "Data Array: " << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {

            std::cout << dataArray[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Status Array: " << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {
            std::cout << indexSearchStatus[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    void visualizeDataStatus(int dataArray[], int numberOfData, int indexSearchStatus[], int key)
    {
        std::cout << std::endl;
        std::cout << "Data Array: " << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {

            std::cout << dataArray[i] << " ";
        }
        std::cout << "   ";
        std::cout << "Key: " << key << std::endl;
        std::cout << "Status Array: " << std::endl;
        for (int i = 0; i < numberOfData; i++)
        {
            std::cout << indexSearchStatus[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
};
int main()
{

    DataGenerator dataGenerator;
    int dataArraySize = dataGenerator.getNumberOfData();
    int *dataArrayPointer = dataGenerator.generateData(dataArraySize);
    int dataArray[dataArraySize];
    for (int i = 0; i < dataArraySize; i++)
    {
        dataArray[i] = *(dataArrayPointer + i);
    }
    AlgorithmSelection algorithmSelection;
    int *selectedOption = algorithmSelection.displayMenu();
    switch (*selectedOption)
    {
    case 1:
    {
        SearchAlgorithmVisualizer searchVisualizer;
        int searchValue = searchVisualizer.getSearchValue();
        searchVisualizer.visualizer(*(selectedOption + 1), dataArraySize, dataArray, searchValue);
        break;
    }

    case 2:
    {
        SortAlgorithmVisualizer sortVisualizer;
        sortVisualizer.visualizer(*(selectedOption + 1), dataArraySize, dataArray);
        break;
    }

    default:
        break;
    }
}