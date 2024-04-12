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
private:
    class BubbleSort
    {
    public:
        BubbleSort(int numberOfData, int dataArray[], int searchIndexStatus[])
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

    class InsertionSort
    {
    public:
        InsertionSort(int numberOfData, int dataArray[], int searchIndexStatus[])
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

    class SelectionSort
    {
    public:
        SelectionSort(int numberOfData, int dataArray[], int searchIndexStatus[])
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

    class QuickSort
    {
    public:
        QuickSort(int numberOfData, int dataArray[], int searchIndexStatus[])
        {
            clock_t start, end;
            start = clock();
            QuickSortHelper(dataArray, 0, numberOfData - 1, searchIndexStatus);
            end = clock();
            std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
        }

        void visualizeDataStatus(int dataArray[], int numberOfData, int indexSearchStatus[], int pivotIndex)
        {
            std::cout << std::endl;
            std::cout << "Data Array: " << std::endl;
            for (int i = 0; i < numberOfData; i++)
            {
                if (i == pivotIndex)
                {
                    indexSearchStatus[i] = 1; // Set status to 1 for pivot element
                    std::cout << "[" << dataArray[i] << "] ";
                }
                else
                {
                    indexSearchStatus[i] = 0; // Set status to 0 for other elements
                    std::cout << dataArray[i] << " ";
                }
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

        int Partition(int dataArray[], int low, int high, int searchIndexStatus[])
        {
            int pivot = dataArray[high];
            int i = (low - 1);

            for (int j = low; j <= high - 1; j++)
            {
                if (dataArray[j] < pivot)
                {
                    i++;
                    std::swap(dataArray[i], dataArray[j]);
                    visualizeDataStatus(dataArray, high + 1, searchIndexStatus, i);
                }
            }
            std::swap(dataArray[i + 1], dataArray[high]);
            visualizeDataStatus(dataArray, high + 1, searchIndexStatus, i + 1);
            return (i + 1);
        }

        void QuickSortHelper(int dataArray[], int low, int high, int searchIndexStatus[])
        {
            if (low < high)
            {
                int pi = Partition(dataArray, low, high, searchIndexStatus);

                QuickSortHelper(dataArray, low, pi - 1, searchIndexStatus);
                QuickSortHelper(dataArray, pi + 1, high, searchIndexStatus);
            }
        }
    };

    class MergeSort
    {
    public:
        MergeSort(int numberOfData, int dataArray[], int indexSearchStatus[])
        {
            clock_t start, end;
            start = clock();
            int middle = (int)(numberOfData / 2);
            Merge(dataArray, 0, middle, numberOfData - 1, indexSearchStatus);
            end = clock();
            std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
        }
        void Merge(int dataArray[], int left, int middle, int right, int indexSearchStatus[])
        {
            int i, j, k;
            int n1 = middle - left + 1;
            int n2 = right - middle;

            int *Left = new int[n1];
            int *Right = new int[n2];

            for (i = 0; i < n1; i++)
                Left[i] = dataArray[left + i];
            for (j = 0; j < n2; j++)
                Right[j] = dataArray[middle + 1 + j];

            i = 0;
            j = 0;
            k = left;
            while (i < n1 && j < n2)
            {
                if (Left[i] <= Right[j])
                {
                    dataArray[k] = Left[i];
                    i++;
                }
                else
                {
                    dataArray[k] = Right[j];
                    j++;
                }
                visualizeDataStatus(dataArray, n1 + n2, indexSearchStatus, k);
                k++;
            }

            while (i < n1)
            {
                dataArray[k] = Left[i];
                i++;
                k++;
                visualizeDataStatus(dataArray, n1 + n2, indexSearchStatus, k);
            }

            while (j < n2)
            {
                dataArray[k] = Right[j];
                j++;
                k++;
                visualizeDataStatus(dataArray, n1 + n2, indexSearchStatus, k);
            }

            delete[] Left;
            delete[] Right;
        }
        void MergeSortHelper(int dataArray[], int left, int right, int indexSearchStatus[])
        {
            if (left < right)
            {
                int middle = left + (right - left) / 2;

                MergeSortHelper(dataArray, left, middle, indexSearchStatus);
                MergeSortHelper(dataArray, middle + 1, right, indexSearchStatus);

                Merge(dataArray, left, middle, right, indexSearchStatus);
            }
        }

        void PerformMergeSort(int dataArray[], int numberOfData, int indexSearchStatus[])
        {
            clock_t start, end;
            start = clock();
            MergeSortHelper(dataArray, 0, numberOfData - 1, indexSearchStatus);
            end = clock();
            std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
        }

        void visualizeDataStatus(int dataArray[], int numberOfData, int indexSearchStatus[], int key)
        {
            std::cout << std::endl;
            std::cout << "Data Array: " << std::endl;
            for (int i = 0; i < numberOfData; i++)
            {
                if (i == key)
                {
                    indexSearchStatus[i] = 1; // Set status to 1 for elements being worked on
                    std::cout << "[" << dataArray[i] << "] ";
                }
                else
                {
                    indexSearchStatus[i] = 0; // Set status to 0 for other elements
                    std::cout << dataArray[i] << " ";
                }
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
    class HeapSort
    {
    public:
        HeapSort(int numberOfData, int dataArray[], int indexSearchStatus[])
        {
            clock_t start, end;
            start = clock();
            for (int i = numberOfData / 2 - 1; i >= 0; i--)
                Heapify(dataArray, numberOfData, i, indexSearchStatus);

            for (int i = numberOfData - 1; i > 0; i--)
            {
                std::swap(dataArray[0], dataArray[i]);
                visualizeDataStatus(dataArray, numberOfData, indexSearchStatus, i);
                Heapify(dataArray, i, 0, indexSearchStatus);
            }
            end = clock();
            std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
        }

        void Heapify(int dataArray[], int dataArraySize, int i, int indexSearchStatus[])
        {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < dataArraySize && dataArray[left] > dataArray[largest])
                largest = left;

            if (right < dataArraySize && dataArray[right] > dataArray[largest])
                largest = right;

            if (largest != i)
            {
                std::swap(dataArray[i], dataArray[largest]);
                visualizeDataStatus(dataArray, dataArraySize, indexSearchStatus, i);
                Heapify(dataArray, dataArraySize, largest, indexSearchStatus);
            }
        }

        void visualizeDataStatus(int dataArray[], int numberOfData, int indexSearchStatus[], int key)
        {
            std::cout << std::endl;
            std::cout << "Data Array: " << std::endl;
            for (int i = 0; i < numberOfData; i++)
            {
                if (i == key)
                {
                    indexSearchStatus[i] = 1; // Set status to 1 for elements being worked on
                    std::cout << "[" << dataArray[i] << "] ";
                }
                else
                {
                    indexSearchStatus[i] = 0; // Set status to 0 for other elements
                    std::cout << dataArray[i] << " ";
                }
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

    class RadixSort
    {
    public:
        RadixSort(int numberOfData, int dataArray[], int indexSearchStatus[])
        {
            clock_t start, end;
            start = clock();
            int maxElement = dataArray[0];
            for (int i = 1; i < numberOfData; i++)
            {
                if (dataArray[i] > maxElement)
                    maxElement = dataArray[i];
            }

            for (int exp = 1; maxElement / exp > 0; exp *= 10)
                CountSort(dataArray, numberOfData, exp, indexSearchStatus);

            end = clock();
            std::cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
        }

        void CountSort(int dataArray[], int dataArraySize, int exp, int indexSearchStatus[])
        {
            int output[dataArraySize];
            int count[10] = {0};

            for (int i = 0; i < dataArraySize; i++)
                count[(dataArray[i] / exp) % 10]++;

            for (int i = 1; i < 10; i++)
                count[i] += count[i - 1];

            for (int i = dataArraySize - 1; i >= 0; i--)
            {
                output[count[(dataArray[i] / exp) % 10] - 1] = dataArray[i];
                count[(dataArray[i] / exp) % 10]--;
            }

            for (int i = 0; i < dataArraySize; i++)
            {
                dataArray[i] = output[i];
                visualizeDataStatus(dataArray, dataArraySize, indexSearchStatus, i);
            }
        }

        void visualizeDataStatus(int dataArray[], int numberOfData, int indexSearchStatus[], int key)
        {
            std::cout << std::endl;
            std::cout << "Data Array: " << std::endl;
            for (int i = 0; i < numberOfData; i++)
            {
                if (i == key)
                {
                    indexSearchStatus[i] = 1; // Set status to 1 for elements being worked on
                    std::cout << "[" << dataArray[i] << "] ";
                }
                else
                {
                    indexSearchStatus[i] = 0; // Set status to 0 for other elements
                    std::cout << dataArray[i] << " ";
                }
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

public:
    void
    visualizer(int choiceIndex, int dataArraySize, int dataArray[])
    {
        int searchIndexStatus[dataArraySize];
        for (int i = 0; i < dataArraySize; i++)
        {
            searchIndexStatus[i] = 0;
        }
        switch (choiceIndex)
        {
        case 1:
        {
            BubbleSort bubbleSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        }

        case 2:
        {
            InsertionSort insertionSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        }

        case 3:
        {
            SelectionSort selectionSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        }

        case 4:
        {
            QuickSort quickSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        }

        case 5:
        {
            MergeSort mergeSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        }

        case 6:
        {
            HeapSort heapSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        }

        case 7:
        {
            RadixSort radixSort(dataArraySize, dataArray, searchIndexStatus);
            break;
        }

        default:
            break;
        }
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