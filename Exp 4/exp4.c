#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define an Activity structure with start and finish times
struct Activity {
    int start;
    int finish;
};

// Comparator function to sort activities based on their finish time
int compareActivities(const void* a, const void* b) {
    struct Activity* activityA = (struct Activity*)a;
    struct Activity* activityB = (struct Activity*)b;
    return activityA->finish - activityB->finish;
}

// Function to perform the Activity Selection using the greedy approach
void activitySelection(struct Activity activities[], int n) {
    // Sort the activities by finish time using the qsort function
    qsort(activities, n, sizeof(struct Activity), compareActivities);

    printf("Selected activities:\n");

    int i = 0; // Index of the first selected activity
    printf("Activity with start time %d and finish time %d\n", activities[i].start, activities[i].finish);

    // Select activities
    for (int j = 1; j < n; j++) {
        if (activities[j].start >= activities[i].finish) {
            printf("Activity with start time %d and finish time %d\n", activities[j].start, activities[j].finish);
            i = j; // Update the index of the last selected activity
        }
    }
}

int main() {
    struct Activity activities[] = {{5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};
    int n = sizeof(activities) / sizeof(activities[0]);

    // Record start time
    clock_t start = clock();

    // Run the activity selection function
    activitySelection(activities, n);

    // Record end time and calculate duration
    clock_t end = clock();
    double time_taken = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time taken: %.2f milliseconds\n", time_taken);

    return 0;
}