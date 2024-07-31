#include <iostream>
#include <time.h>
#include <iomanip>

// Function prototypes
int maxSubSum1(int array[], int index);
int maxSubSum2(int array[], int index);
int max3(int a, int b, int c);
int maxSumRec(int array[], int left, int right);
int maxSubSum3(int array[], int index);
int maxSubSum4(int array[], int index);

// Algorithm 1
int maxSubSum1(int array[], int index) {
  int maxSum = 0;
  double start = clock();

  for (int i = 0; i < index; ++i) {
    for (int j = i; j < index; ++j) {
      int thisSum = 0;

      for (int k = i; k <= j; ++k) {
        thisSum += array[k];
      }

      if (thisSum > maxSum) {
        maxSum = thisSum;
      }
    }
  }

  double end = clock();
  double elapsed_time = (end - start) / CLOCKS_PER_SEC * 1000000;

  std::cout << "Algorithm 1: " << maxSum << "\n\n";
  return elapsed_time;
}

// Algorithm 2
int maxSubSum2(int array[], int index) {
  int maxSum = 0;
  double start = clock();

  for (int i = 0; i < index; ++i) {
    int thisSum = 0;
    for (int j = i; j < index; ++j) {
      thisSum += array[j];

      if (thisSum > maxSum) {
        maxSum = thisSum;
      }
    }
  }

  double end = clock();
  double elapsed_time = (end - start) / CLOCKS_PER_SEC * 1000000;

  std::cout << "Algorithm 2: " << maxSum << "\n\n";
  return elapsed_time;
}

// Helper function for Algorithm 3
int max3(int a, int b, int c) {
  return (a >= b) ? ((a >= c) ? a : c) : ((b >= c) ? b : c);
}

// Algorithm 3
int maxSumRec(int array[], int left, int right) {
  if (left == right) {
    if (array[left] > 0) {
      return array[left];
    }
    else {
      return 0;
    }
  }

  int center = (left + right) / 2;
  int maxLeftSum = maxSumRec(array, left, center);
  int maxRightSum = maxSumRec(array, center + 1, right);

  int maxLeftBorderSum = 0, leftBorderSum = 0;
  for (int i = center; i >= left; --i) {
    leftBorderSum += array[i];
    if (leftBorderSum > maxLeftBorderSum) {
      maxLeftBorderSum = leftBorderSum;
    }
  }

  int maxRightBorderSum = 0, rightBorderSum = 0;
  for (int j = center + 1; j <= right; ++j) {
    rightBorderSum += array[j];
    if (rightBorderSum > maxRightBorderSum) {
      maxRightBorderSum = rightBorderSum;
    }
  }

  return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

// Algorithm 3 driver
int maxSubSum3(int array[], int index) {
  double start = clock();
  int maxSum = maxSumRec(array, 0, index - 1);
  double end = clock();
  double elapsed_time = (end - start) / CLOCKS_PER_SEC * 1000000.0;

  std::cout << "Algorithm 3: " << maxSum << "\n\n";
  return elapsed_time;
}

// Algorithm 4
int maxSubSum4(int array[], int index) {
  int maxSum = 0, thisSum = 0;

  double start = clock();
  for (int j = 0; j < index; ++j) {
    thisSum += array[j];

    if (thisSum > maxSum) {
      maxSum = thisSum;
    } else if (thisSum < 0) {
      thisSum = 0;
    }
  }
  double end = clock();
  double elapsed_time = (end - start) / CLOCKS_PER_SEC * 1000000.0;

  std::cout << "Algorithm 4: " << maxSum << "\n\n";
  return elapsed_time;
}

int main() {
  int array[2500];
  int index = 0;

  std::cout << std::fixed << std::setprecision(0);
  std::cout << "Please enter sequence integers: ";

  while (std::cin >> array[index]) {
    index++;
  }

  std::cout << "\n\n";
  double time1 = maxSubSum1(array, index);
  double time2 = maxSubSum2(array, index);
  double time3 = maxSubSum3(array, index);
  double time4 = maxSubSum4(array, index);

  std::cout << "Final Results" << std::endl;
  std::cout << "  Algorithm 1 O(n^3)   : " << time1 << " ms\n";
  std::cout << "  Algorithm 2 O(n^2)   : " << time2 << " ms\n";
  std::cout << "  Algorithm 3 O(n lg n): " << time3 << " ms\n";
  std::cout << "  Algorithm 4 O(n)     : " << time4 << " ms\n";
}
