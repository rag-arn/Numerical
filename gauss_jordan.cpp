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
        int pivot_row = row;

        for (int i=row+1; i<n; i++) {
            if (fabs(arr[i][col])>fabs(arr[pivot_row][col])) pivot_row = i;
        }
        if (fabs(arr[pivot_row][col])<eps) continue;

        swap(arr[row], arr[pivot_row]);

        double pivot = arr[row][col];

        for (int i=0; i<=n; i++) {
            arr[row][i] /= pivot;
        }

        for (int i=0; i<n; i++) {
            if (i==row) continue;

            double m = arr[i][col];

            for (int j=col; j<=n; j++) {
                arr[i][j] -= arr[row][j]*m;
            }
        }
        row++;
    }

    cout << "reduced row :" << endl;
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

    cout << "Ans : " << endl;
    for (int i=0; i<n; i++) {
        cout << fixed << setprecision(3) << arr[i][n] << endl;
    }
}

int main() {
    while (true) {
        solve();
    }
}
