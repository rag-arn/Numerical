#include<bits/stdc++.h>
using namespace std;

#define eps 1e-9

int n;

void print (int sz, vector<vector<double>> arr)
{
    for (int i=0; i<sz; i++) {
        for (int j=0; j<=sz; j++) {
            if (fabs(arr[i][j])<eps) arr[i][j] = 0;
            cout << fixed << setprecision(3) << arr[i][j] << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

bool gaussJordan (int sz, vector<vector<double>> arr, vector<double> &ans)
{
    cout << "\nAugmented matrix : " << endl;
    print (sz, arr);

    int row = 0;

    for (int col=0; col<sz and row<sz; col++) {
        int pivot_row = row;

        for (int i=row+1; i<sz; i++) {
            if (fabs(arr[i][col])>fabs(arr[pivot_row][col])) pivot_row = i;
        }
        if (fabs(arr[pivot_row][col])<eps) continue;

        swap(arr[row], arr[pivot_row]);

        double pivot = arr[row][col];

        for (int i=0; i<=sz; i++) {
            arr[row][i] /= pivot;
        }

        for (int i=0; i<sz; i++) {
            if (i==row) continue;

            double m = arr[i][col];

            for (int j=col; j<=sz; j++) {
                arr[i][j] -= arr[row][j]*m;
            }
        }
        row++;
    }

    int rank = row;

    for (int i=rank; i<sz; i++) {
        if (fabs(arr[i][sz])>eps) {
            cout << "No solution" << endl;
            return false;
        }
    }

    if (rank<sz) {
        cout << "Infinite solution" << endl;
        return false;
    }

    for (int i=0; i<sz; i++) {
        ans[i] = arr[i][sz];
    }

    return true;
}

bool gaussElimination (int sz, vector<vector<double>> arr, vector<double> &ans)
{
    cout << "\nAugmented matrix : " << endl;
    print (sz, arr);

    int row = 0;

    for (int col=0; col<sz and row<sz; col++) {
        int pivot = row;

        for (int i=row+1; i<sz; i++) {
            if (fabs(arr[i][col])>fabs(arr[pivot][col])) pivot = i;
        }
        if (fabs(arr[pivot][col])<eps) continue;

        swap(arr[row], arr[pivot]);

        for (int i=row+1; i<sz; i++) {
            double m = arr[i][col]/arr[row][col];

            for (int j=col; j<=sz; j++) {
                arr[i][j] -= m*arr[row][j];
            }
        }
        row++;
    }


    int rank = row;

    for (int i=rank; i<sz; i++) {
        if (fabs(arr[i][sz])>eps) {
            cout << "No solution" << endl;
            return false;
        }
    }

    if (rank<sz) {
        cout << "Infinite solution" << endl;
        return false;
    }

    for (int i=sz-1; i>=0; i--) {
        double sum = arr[i][sz];

        for (int j=i+1; j<sz; j++) {
            sum -= arr[i][j]*ans[j];
        }
        ans[i] = sum/arr[i][i];
    }

    return true;
}

bool solve (int sz, vector<vector<double>> &M, vector<double> &X, int solver)
{
    if (solver == 1) return gaussElimination(sz, M, X);
    return gaussJordan(sz, M, X);
}

void linearRegression (vector<double> &x, vector<double> &y, int solver)
{
    double sumx = 0, sumy = 0, sumxy = 0, sumx2 = 0;

    for (int i=0; i<n; i++) {
        sumx += x[i];
        sumy += y[i];
        sumxy += x[i]*y[i];
        sumx2 += x[i]*x[i];
    }

    vector<vector<double>> M(2, vector<double> (3, 0));
    vector<double> X(2, 0);

    M[0][0] = n;     M[0][1] = sumx;   M[0][2] = sumy;
    M[1][0] = sumx;  M[1][1] = sumx2;  M[1][2] = sumxy;

    if (!solve(2, M, X, solver)) return;

    cout << fixed << setprecision(4);
    cout << "\n\nLinear Regression : " << endl;
    cout << "a = " << X[0] << endl;
    cout << "b = " << X[1] << endl;
    cout << "\nBest fit line : " << endl;
    cout << "y = " << X[0] << " + " << X[1] << "x" << endl;
}

void polynomialRegression (vector<double> &x, vector<double> &y, int solver)
{
    double sx = 0, sx2 = 0, sx3 = 0, sx4 = 0;
    double sy = 0, sxy = 0, sx2y = 0;

    for (int i=0; i<n; i++) {
        double xi = x[i];
        double yi = y[i];

        sx += xi;
        sx2 += xi*xi;
        sx3 += xi*xi*xi;
        sx4 += xi*xi*xi*xi;

        sy += yi;
        sxy += xi*yi;
        sx2y += xi*xi*yi;
    }

    vector<vector<double>> M(3, vector<double> (4, 0));
    vector<double> X(3, 0);

    M[0][0] = n;     M[0][1] = sx;   M[0][2] = sx2;  M[0][3] = sy;
    M[1][0] = sx;    M[1][1] = sx2;  M[1][2] = sx3;  M[1][3] = sxy;
    M[2][0] = sx2;   M[2][1] = sx3;  M[2][2] = sx4;  M[2][3] = sx2y;

    if (!solve(3, M, X, solver)) return;

    cout << fixed << setprecision(4);
    cout << "\n\nPolynomial Regression : " << endl;
    cout << "a = " << X[0] << endl;
    cout << "b = " << X[1] << endl;
    cout << "c = " << X[2] << endl;
    cout << "\nBest fit quadratic curve : " << endl;
    cout << "y = " << X[0] << " + " << X[1] << "x + " << X[2] << "x^2" << endl;
}

void transcendentalRegression (vector<double> &x, vector<double> &y, int solver)
{
    double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;

    for (int i=0; i<n; i++) {
        double xi = x[i];
        double yi = log(y[i]);

        Sx += xi;
        Sy += yi;
        Sxx += xi*xi;
        Sxy += xi*yi;
    }

    vector<vector<double>> M(2, vector<double> (3, 0));
    vector<double> X(2, 0);

    M[0][0] = n;    M[0][1] = Sx;   M[0][2] = Sy;
    M[1][0] = Sx;   M[1][1] = Sxx;  M[1][2] = Sxy;

    if (!solve(2, M, X, solver)) return;

    double A = X[0];
    double b = X[1];
    double a = exp(A);

    cout << fixed << setprecision(4);
    cout << "\n\nTranscendental Regression : " << endl;
    cout << "A = " << A << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "\nBest fit curve : " << endl;
    cout << "y = " << a << " * e^(" << b << "x)" << endl;
}

int main()
{
    int method, solver;

    cout << "1. Linear Regression\n2. Polynomial Regression\n3. Transcendental Regression\n";
    cout << "Enter regression method : ";
    cin >> method;

    cout << "\n1. Gaussian Elimination\n2. Gauss-Jordan Elimination\n";
    cout << "Enter solving method : ";
    cin >> solver;

    cout << "\nEnter the number of points, x and y values : \n";
    cin >> n;

    vector<double> x(n), y(n);

    for (int i=0; i<n; i++) {
        cin >> x[i];
    }

    for (int i=0; i<n; i++) {
        cin >> y[i];
    }

    if (method == 1) {
        linearRegression(x, y, solver);
    }
    else if (method == 2) {
        polynomialRegression(x, y, solver);
    }
    else if (method == 3) {
        for (int i=0; i<n; i++) {
            if (y[i] <= 0) {
                cout << "\nError : y must be positive for transcendental regression." << endl;
                return 0;
            }
        }

        transcendentalRegression(x, y, solver);
    }
    else {
        cout << "\nInvalid regression method!" << endl;
    }
}
