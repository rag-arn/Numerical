#include<bits/stdc++.h>
using namespace std;

#define eps 1e-9

int n;

void print (vector<vector<double>> arr) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<=n; j++) {
            if (fabs(arr[i][j])<eps) arr[i][j] = 0;
            cout << fixed << setprecision(3) << arr[i][j] << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

void solve () {
    cin >> n;

    vector<vector<double>> arr(n, vector<double>(n+1));

    for (int i=0; i<n; i++) {
        for (int j=0; j<=n; j++) {
            cin >> arr[i][j];
        }
    }

    cout << "Augmented matrix : " << endl;
    print (arr);
    
    int row = 0;

    for (int col=0; col<n and row<n; col++) {
        int pivot = row;

        for (int i=row+1; i<n; i++) {
            if (fabs(arr[i][col])>fabs(arr[pivot][col])) pivot = i;
        }
        if (fabs(arr[pivot][col])<eps) continue;

        swap(arr[row], arr[pivot]);

        for (int i=row+1; i<n; i++) {
            double m = arr[i][col]/arr[row][col];

            for (int j=col; j<=n; j++) {
                arr[i][j] -= m*arr[row][j];
            }
        }
        row++;
    }

    cout << "After forward elimination : " << endl;
    print (arr);

    int rank = row;

    for (int i=rank; i<n; i++) {
        if (fabs(arr[i][n])>eps) {
            cout << "No solution" << endl;
            return;
        }
    }

    if (rank<n) {
        cout << "Infinite solution" << endl;
        return;
    }

    cout << "Unique solutions : " << endl;

    vector<double> ans(n);

    for (int i=n-1; i>=0; i--) {
        double sum = arr[i][n];

        for (int j=i+1; j<n; j++) {
            sum -= arr[i][j]*ans[j];
        }
        ans[i] = sum/arr[i][i];
    }

    cout << "Ans : " << endl;
    for (int i=0; i<n; i++) {
        cout << fixed << setprecision(3) << ans[i] << endl;
    }
}

int main() {
    while (true) {
        solve();
    }
}
