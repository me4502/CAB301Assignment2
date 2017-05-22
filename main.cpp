#include <iostream>
#include <vector>
#include <climits>
#include <random>
#include <fstream>
#include <ctime>
#include <tuple>
#include <iterator>
#include <sstream>

#ifdef OPERATIONS
unsigned long long operationCount = 0;
#endif

int minDistance(std::vector<int> &input) {
    int dmin = INT_MAX;
    for (size_t i = 0; i < input.size(); i++) {
        for (size_t j = 0; j < input.size(); j++) {
#ifdef OPERATIONS
            if (i != j) {
                operationCount ++;
            }
#endif
            if (i != j and abs(input[i] - input[j]) < dmin) {
#ifdef OPERATIONS
                operationCount ++;
#endif
                dmin = abs(input[i] - input[j]);
            }
        }
    }
    return dmin;
}

int minDistance2(std::vector<int> &input) {
    // Set dmin to a 'infinity' In this case the maximum integer value is being used,
    // due to a lack of 'inf' type.
    int dmin = INT_MAX;

    for (size_t i = 0; i < input.size() - 1; i++) {
        for (size_t j = i + 1; j < input.size(); j++) {
#ifdef OPERATIONS
            operationCount ++;
#endif
            const int temp = abs(input[i] - input[j]);
            if (temp < dmin) {
                dmin = temp;
            }
        }
    }

    return dmin;
}

enum TEST_TYPE {
    SORTED = 0,
    REVERSED = 1,
    RANDOMIZED = 2
};

std::vector<int> generateArray(unsigned int n, TEST_TYPE type) {
    if (n <= 0) {
        n = 1;
    }
    std::vector<int> generatedArray(n);

    // Fill the array.
    switch (type) {
    case SORTED:
        for (size_t i = 0; i < n; i++) {
            generatedArray[i] = (int) i;
        }
        break;
    case REVERSED:
        for (size_t i = 0; i < n; i++) {
            generatedArray[i] = (int) (n - i - 1);
        }
        break;
    case RANDOMIZED:
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> distribution(0, n);

        for (size_t i = 0; i < n; i++) {
            generatedArray[i] = (int) (distribution(rng));
        }
        break;
    }

    return generatedArray;
}

int runMethod(std::vector<int> &testVector, int methodNumber) {
#ifdef OPERATIONS
    operationCount = 0;
#endif
    int output = 0;

    switch (methodNumber) {
    case 1:
        output = minDistance(testVector);
        break;
    case 2:
        output = minDistance2(testVector);
        break;
    default:
        break;
    }
#ifdef OPERATIONS
#elif TIMING
#elif TEST
#else
    std::cout << "Test Output: " << output << std::endl;
#endif
    return output;
}

unsigned int testCases[] = {10, 100, 1000, 10000};

#ifdef TEST
#define TEST_COUNT 5
#elif TIMING
#define TEST_COUNT 10
#elif OPERATIONS
#define TEST_COUNT 1
#else
#define TEST_COUNT 10
#endif

int main() {
    std::vector<int> testVector;

#ifdef OPERATIONS
    std::ofstream csvExporter;
    csvExporter.open("operations.csv");
    for (int i = 1; i <= 10000; i += (10000 * TEST_COUNT) / 255) {
        for (int j = 0; j < TEST_COUNT; j++) {
            testVector = generateArray((unsigned long) i, TEST_TYPE::RANDOMIZED);
            runMethod(testVector, 1);
            csvExporter << 1 << "," << i << "," << operationCount << std::endl;
            runMethod(testVector, 2);
            csvExporter << 2 << "," << i << "," << operationCount << std::endl;
        }
    }
    csvExporter.close();
#elif TIMING
    std::ofstream csvExporter;
    csvExporter.open("timings.csv");
    for (int k = TEST_TYPE::SORTED; k <= TEST_TYPE::RANDOMIZED; k++) {
        switch(k) {
        case TEST_TYPE::SORTED:
            csvExporter << "SORTED,time" << std::endl;
            break;
        case TEST_TYPE::REVERSED:
            csvExporter << "REVERSED,time" << std::endl;
            break;
        case TEST_TYPE::RANDOMIZED:
            csvExporter << "RANDOMIZED,time" << std::endl;
            break;
        default:
            break;
        }
        for (int i = 1; i <= 10000; i += (10000 * TEST_COUNT) / (255)) {
            for (int j = 0; j < TEST_COUNT; j++) {
                testVector = generateArray((unsigned long) i, (TEST_TYPE) k);
                clock_t start = clock();
                runMethod(testVector, 1);
                double duration = (std::clock() - start) / (CLOCKS_PER_SEC / 1000.0);
                csvExporter << 1 << "," << i << "," << duration << std::endl;
                start = clock();
                runMethod(testVector, 2);
                duration = (std::clock() - start) / (CLOCKS_PER_SEC / 1000.0);
                csvExporter << 2 << "," << i << "," << duration << std::endl;
            }
        }
    }
    csvExporter.close();
#else
    std::cout << "== Sorted Test ==" << std::endl;
    for (int n = 0; n < TEST_COUNT; n++) {
        for (unsigned int testCase : testCases) {
            testVector = generateArray(testCase, TEST_TYPE::SORTED);
            runMethod(testVector, 1);
            runMethod(testVector, 2);
        }
    }
    std::cout << "== Reversed Test ==" << std::endl;
    for (int n = 0; n < TEST_COUNT; n++) {
        for (unsigned int testCase : testCases) {
            testVector = generateArray(testCase, TEST_TYPE::REVERSED);
            runMethod(testVector, 1);
            runMethod(testVector, 2);
        }
    }
    std::cout << "== Random Test ==" << std::endl;
    for (int n = 0; n < TEST_COUNT; n++) {
        for (unsigned int testCase : testCases) {
            testVector = generateArray(testCase, TEST_TYPE::RANDOMIZED);
            runMethod(testVector, 1);
            runMethod(testVector, 2);
        }
    }
#endif

#ifdef TEST
    std::cout << "== Test ==" << std::endl;
    std::vector<std::tuple<std::vector<int>, int>> tests(6);
    tests[0] = std::make_tuple((std::vector<int>) {
        10, 9, 8, 7, 6, 5, 4, 3, 2, 1
    }, 1);
    tests[1] = std::make_tuple((std::vector<int>) {
        0, 50, 101
    }, 50);
    tests[2] = std::make_tuple((std::vector<int>) {
        0, 51, 101
    }, 50);
    tests[3] = std::make_tuple((std::vector<int>) {
        1000, 0, 492
    }, 492);
    tests[4] = std::make_tuple((std::vector<int>) {
        0, 0, 9
    }, 0);
    tests[5] = std::make_tuple((std::vector<int>) {
        -902, 19, 901
    }, 882);
    int result;

    for (auto &test : tests) {
        testVector = std::get<0>(test);

        std::ostringstream testVectorString;
        testVectorString << "[";
        std::copy(testVector.begin(), testVector.end()-1, std::ostream_iterator<int>(testVectorString, ","));
        testVectorString << testVector.back() << "]";

        int correctAnswer = std::get<1>(test);
        result = runMethod(testVector, 1);
        if (result != correctAnswer) {
            std::cout << "Test: " << testVectorString.str() << " Failed on Method 1! Got "
                      << result << " but expected " << correctAnswer << std::endl;
        } else {
            std::cout << "Test: " << testVectorString.str() << " Passed on Method 1!" << std::endl;
        }
        result = runMethod(testVector, 2);
        if (result != correctAnswer) {
            std::cout << "Test: " << testVectorString.str() << " Failed on Method 2! Got "
                      << result << " but expected " << correctAnswer << std::endl;
        } else {
            std::cout << "Test: " << testVectorString.str() << " Passed on Method 2!" << std::endl;
        }
    }
#endif

    return 0;
}
