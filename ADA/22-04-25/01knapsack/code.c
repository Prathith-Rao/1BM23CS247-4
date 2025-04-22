#include <stdio.h>
#include <stdlib.h>

// A structure to represent an item
typedef struct {
    int value;  // Value of the item
    int weight; // Weight of the item
} Item;

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve the 0/1 Knapsack problem using dynamic programming
int knapsack(int capacity, Item items[], int n) {
    int i, w;

    // Create a 2D array for dynamic programming
    // dp[i][w] will represent the maximum value that can be obtained
    // using the first i items and with a knapsack of capacity w
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
    }

    // Build table dp[][] in bottom-up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0; // Base case: no items or no capacity
            else if (items[i-1].weight <= w)
                // We have two choices: include the item or exclude it
                dp[i][w] = max(
                    items[i-1].value + dp[i-1][w - items[i-1].weight], // Include the item
                    dp[i-1][w] // Exclude the item
                );
            else
                // Item is too heavy, can't include it
                dp[i][w] = dp[i-1][w];
        }
    }

    // Store the result
    int result = dp[n][capacity];

    // To find which items are included in the optimal solution
    printf("Items included in the knapsack:\n");
    int res = result;
    w = capacity;

    for (i = n; i > 0 && res > 0; i--) {
        // If the result comes from including the item
        if (res != dp[i-1][w]) {
            printf("Item %d: Value = %d, Weight = %d\n",
                   i, items[i-1].value, items[i-1].weight);

            // Subtract the value of this item and reduce the capacity
            res -= items[i-1].value;
            w -= items[i-1].weight;
        }
    }

    // Free the dynamically allocated memory
    for (i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int n, capacity, i;

    // Get the number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    // Get the knapsack capacity
    printf("Enter the knapsack capacity: ");
    scanf("%d", &capacity);

    // Create an array of items
    Item *items = (Item *)malloc(n * sizeof(Item));

    // Get the value and weight of each item
    for (i = 0; i < n; i++) {
        printf("Enter value and weight for item %d: ", i + 1);
        scanf("%d %d", &items[i].value, &items[i].weight);
    }

    // Solve the knapsack problem
    int max_value = knapsack(capacity, items, n);

    printf("Maximum value that can be obtained: %d\n", max_value);

    // Free the dynamically allocated memory
    free(items);

    return 0;
}
