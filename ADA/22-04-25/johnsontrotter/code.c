#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a mobile element
typedef struct {
    int value;        // Value of the element
    bool direction;   // Direction: true = left, false = right
} MobileElement;

// Function to find the largest mobile element
// A mobile element is one that is greater than the adjacent element in its direction
int findLargestMobile(MobileElement *elements, int n) {
    int largestMobile = -1;
    int largestMobileIndex = -1;

    for (int i = 0; i < n; i++) {
        if (elements[i].direction == true && i > 0) {
            // Check if mobile to the left
            if (elements[i].value > elements[i-1].value && elements[i].value > largestMobile) {
                largestMobile = elements[i].value;
                largestMobileIndex = i;
            }
        } else if (elements[i].direction == false && i < n-1) {
            // Check if mobile to the right
            if (elements[i].value > elements[i+1].value && elements[i].value > largestMobile) {
                largestMobile = elements[i].value;
                largestMobileIndex = i;
            }
        }
    }

    return largestMobileIndex;
}

// Function to swap two elements
void swap(MobileElement *a, MobileElement *b) {
    MobileElement temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print a permutation
void printPermutation(MobileElement *elements, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", elements[i].value);
    }
    printf("\n");
}

// Function to generate all permutations using Johnson-Trotter algorithm
void johnsonTrotter(int n) {
    if (n <= 0) {
        printf("Input size must be greater than 0\n");
        return;
    }

    // Initialize the elements
    MobileElement *elements = (MobileElement *)malloc(n * sizeof(MobileElement));
    for (int i = 0; i < n; i++) {
        elements[i].value = i + 1;
        elements[i].direction = true;  // Initially all pointing left
    }

    // Print the initial permutation
    printPermutation(elements, n);

    while (true) {
        int mobileIndex = findLargestMobile(elements, n);

        // If no mobile element, we're done
        if (mobileIndex == -1) {
            break;
        }

        // Swap the mobile element with the adjacent element in its direction
        if (elements[mobileIndex].direction == true) {
            swap(&elements[mobileIndex], &elements[mobileIndex - 1]);
            mobileIndex--;
        } else {
            swap(&elements[mobileIndex], &elements[mobileIndex + 1]);
            mobileIndex++;
        }

        // Reverse the direction of all elements larger than the largest mobile element
        for (int i = 0; i < n; i++) {
            if (elements[i].value > elements[mobileIndex].value) {
                elements[i].direction = !elements[i].direction;
            }
        }

        // Print the new permutation
        printPermutation(elements, n);
    }

    free(elements);
}

int main() {
    int n;


        printf("Enter the size of the permutation: ");
        scanf("%d", &n);


    printf("All permutations of size %d using Johnson-Trotter algorithm:\n", n);
    johnsonTrotter(n);

    return 0;
}
