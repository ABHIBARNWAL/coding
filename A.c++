#include <bits/stdc++.h>
using namespace std;

long long count_distinct_subsequences(vector<int>& A) {
    int n = A.size();
    unordered_map<int, int> freq;  // Frequency map to track element counts.
    long long total_sum = 0;  // Final sum of distinct counts.

    int distinct_count = 0;  // Current count of distinct elements.
    int j = 0;  // Right endpoint of the sliding window.

    for (int i = 0; i < n; ++i) {
        // Expand the right endpoint `j` as far as possible.
        while (j < n) {
            if (freq[A[j]] == 0) ++distinct_count;  // New distinct element found.
            ++freq[A[j]];  // Add A[j] to the window.
            ++j;

            // Add the current distinct count to the total sum.
            total_sum += distinct_count;
        }

        // Shrink the window from the left by removing A[i].
        --freq[A[i]];
        if (freq[A[i]] == 0) --distinct_count;  // Element no longer in the window.
    }

    return total_sum;
}

int main() {
    vector<int> A = {1, 2, 2};  // Example input.
    cout << count_distinct_subsequences(A) << endl;  // Output should be 8
    return 0;
}
