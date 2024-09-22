#include <iostream>
#include <vector>
#include <algorithm>

struct Activity {
    int start, finish;
};

bool activityCompare(Activity a1, Activity a2) {
    return (a1.finish < a2.finish);
}

void activitySelection(std::vector<Activity>& activities) {
    std::sort(activities.begin(), activities.end(), activityCompare);

    std::cout << "Selected Activities: \n";

    int lastSelectedIndex = 0;
    std::cout << "(" << activities[0].start << ", " << activities[0].finish << ")\n";

    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= activities[lastSelectedIndex].finish) {
            std::cout << "(" << activities[i].start << ", " << activities[i].finish << ")\n";
            lastSelectedIndex = i;
        }
    }
}

int main() {
    std::vector<Activity> activities = {{5, 9}, {1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};
    
    activitySelection(activities);
    
    return 0;
}