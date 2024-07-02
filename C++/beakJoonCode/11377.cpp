#include <iostream>
#include <vector>
using namespace std;

vector<int> jobPreferences[9999];
int assignedWorker[9999];
bool isVisited[9999];

bool DepthFirstSearch(int currentWorker) {
    for (int preferenceIndex = 0; preferenceIndex < jobPreferences[currentWorker].size(); ++preferenceIndex) {
        int currentJob = jobPreferences[currentWorker][preferenceIndex];

        if (isVisited[currentJob]) {
            continue;
        }
        isVisited[currentJob] = true;

        if (assignedWorker[currentJob] == 0 || DepthFirstSearch(assignedWorker[currentJob])) {
            assignedWorker[currentJob] = currentWorker;
            return true;
        }
    }
    return false;
}

int main(int argumentCount, char *argumentValues[]) {
    int numberOfWorkers, numberOfJobs, numberOfExtraAssignments;
    int numberOfPreferences;
    int jobIndex;
    int maximumAssignments = 0;

    cin >> numberOfWorkers >> numberOfJobs >> numberOfExtraAssignments;

    for (int workerIndex = 1; workerIndex <= numberOfWorkers; ++workerIndex) {
        cin >> numberOfPreferences;
        for (int preferenceIndex = 0; preferenceIndex < numberOfPreferences; ++preferenceIndex) {
            cin >> jobIndex;
            jobPreferences[workerIndex].push_back(jobIndex);
        }
    }

    fill(assignedWorker, assignedWorker + 1010, 0);
    for (int workerIndex = 1; workerIndex <= numberOfWorkers; ++workerIndex) {
        fill(isVisited, isVisited + 1010, false);
        if (DepthFirstSearch(workerIndex)) {
            ++maximumAssignments;
        }
    }

    for (int workerIndex = 1; workerIndex <= numberOfWorkers; ++workerIndex) {
        fill(isVisited, isVisited + 1010, false);
        if (DepthFirstSearch(workerIndex)) {
            ++maximumAssignments;
            --numberOfExtraAssignments;
            if (numberOfExtraAssignments == 0) {
                break;
            }
        }
    }
    cout << maximumAssignments << endl;
    return 0;
}
