#include <iostream>
using namespace std;

long long josephusProblem(long long totalPeople, int step) {
    if (totalPeople == 1) { 
        return 0; 
    }
    if (step == 1) { 
        return totalPeople - 1; 
    }
    if (step <= totalPeople) {
        long long remainingPeople = totalPeople - totalPeople / step;
        long long survivorPosition = josephusProblem(remainingPeople, step) - totalPeople % step;
        if (survivorPosition < 0) survivorPosition += remainingPeople;
        return (step * (survivorPosition % remainingPeople)) / (step - 1);
    } else {
        return (josephusProblem(totalPeople - 1, step) + step) % totalPeople;
    }
}

int main() {
    long long numberOfPeople, stepSize;
    cin >> numberOfPeople >> stepSize;
    cout << josephusProblem(numberOfPeople, stepSize) + 1;
}
