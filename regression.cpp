#include<bits/stdc++.h>
using namespace std;

#define eps 1e-9

int n;

vector<double> gauss_jordan (vector<vector<double>> arr, int sz) {
    int row = 0;

    for (int col=0; col<sz and row<sz; col++) {
        int prow = row;

        for (int i=row+1; i<sz; i++) {
            if (fabs(arr[i][col])>fabs(arr[prow][col])) prow = i;
        }

        if (fabs(arr[prow][col])<eps) continue;

        swap (arr[prow], arr[row]);

        double pivot = arr[row][col];

        for (int j=0; j<=sz; j++) {
            arr[row][j] /= pivot;
        }

        for (int i=0; i<sz; i++) {
            if (i==row) continue;

            double m = arr[i][col];

            for (int j=0; j<=sz; j++) {
                arr[i][j] -= m*arr[row][j];
            }
        }
        row++;
    }

    int rank = row;

    for (int i=rank; i<sz; i++) {
        if (fabs(arr[i][sz])>eps) {
            cout << "No solution" << endl;
            return {};
        }
    }

    if (rank<sz) {
        cout << "Inf solution" << endl;
        return {};
    }

    vector<double> ans(sz);
    for (int i=0; i<sz; i++) {
        ans[i] = arr[i][sz];
    }
    return ans;
    
}

void td (vector<double> x, vector<double> y) {
    double xi=0, Yi=0, xiYi=0, xi2 = 0;

    for (int i=0; i<n; i++) {
        xi += x[i];
        Yi += log(y[i]);
        xiYi += x[i]*(log(y[i]));
        xi2 += x[i]*x[i];
    }

    vector<vector<double>> arr(2, vector<double> (3));

    arr[0][0] = n;
    arr[0][1] = xi;
    arr[0][2] = Yi;
    
    arr[1][0] = xi;
    arr[1][1] = xi2;
    arr[1][2] = xiYi;

    vector<double> ans = gauss_jordan(arr, 2);

    double a = exp(ans[0]), b = ans[1];

    cout << "Equation : " << endl;
    cout << "y = " << a << "e^(" << b << "x)" << endl;
}

void td2 (vector<double> x, vector<double> y) {
    double Xi=0, Yi=0, XiYi=0, Xi2 = 0;

    for (int i=0; i<n; i++) {
        Xi += log(x[i]);
        Yi += log(y[i]);
        XiYi += log(x[i])*(log(y[i]));
        Xi2 += log(x[i])*log(x[i]);
    }

    vector<vector<double>> arr(2, vector<double> (3));

    arr[0][0] = n;
    arr[0][1] = Xi;
    arr[0][2] = Yi;
    
    arr[1][0] = Xi;
    arr[1][1] = Xi2;
    arr[1][2] = XiYi;

    vector<double> ans = gauss_jordan(arr, 2);

    double a = exp(ans[0]), b = ans[1];

    cout << "Equation : " << endl;
    cout << "y = " << a << "x^(" << b << ")" << endl;
}

void poly (vector<double> x, vector<double> y) {
    double xi=0, yi=0, xiyi=0, xi2=0, xi3=0, xi4=0, xi2yi=0;

    for (int i=0; i<n; i++) {
        xi += x[i];
        yi += y[i];
        xi2 += x[i]*x[i];
        xiyi += x[i]*y[i];
        xi3 += pow(x[i], 3);
        xi4 += pow(x[i], 4);
        xi2yi += pow(x[i], 2)*y[i]; 
    }

    vector<vector<double>> arr(3, vector<double> (4));

    arr[0][0] = n, arr[0][1] = xi, arr[0][2] = xi2, arr[0][3] = yi;
    arr[1][0] = xi, arr[1][1] = xi2, arr[1][2] = xi3, arr[1][3] = xiyi;
    arr[2][0] = xi2, arr[2][1] = xi3, arr[2][2] = xi4, arr[2][3] = xi2yi;

    vector<double> ans = gauss_jordan(arr, 3);

    cout << "\nEquation : " << endl;
    cout << "y = " << ans[0] << " + " << ans[1] << "x + " << ans[2] << "x^2\n";

}

void poly_n (vector<double> x, vector<double> y) {
    int deg;
    cout << "Enter degree : ";
    cin >> deg;

    vector<vector<double>> arr(deg+1, vector<double> (deg+2));

    vector<double> xi(2*deg, 0.0), yi(deg+1, 0.0);

    for (int i=0; i<2*deg; i++) {
        for (int j=0; j<n; j++) {
            xi[i] += pow(x[j], i+1);
        }
    }
    
    for (int i=0; i<deg+1; i++) {
        for (int j=0; j<n; j++) {
            yi[i] += pow(x[j], i)*y[j];
        }
    }

    arr[0][0] = n;
    for (int j=1; j<=deg; j++) {
        arr[0][j] = xi[j-1];
    }
    for (int i=1; i<=deg; i++) {
        for (int j=0; j<=deg; j++) {
            arr[i][j] = xi[i+j-1];
         }
    }

    for (int i=0; i<deg+1; i++) {
        arr[i][deg+1] = yi[i];
    }

    vector<double> ans = gauss_jordan(arr, deg+1);

    if (ans.size()==0){
        return;
    }

    cout << "\nEquation : " << endl;
    cout << fixed << setprecision(4) << "y = ";
    for (int i=0; i<ans.size(); i++) {
        if (i > 0) cout << " + ";
        cout << ans[i];
        if (i == 1) cout << "x";
        else if (i > 1) cout << "x^" << i;

    }
    cout << endl;
}

void linear(vector<double> x, vector<double> y) {
    double xi=0, yi=0, xi2=0, xiyi=0;

    for (int i=0; i<n; i++) {
        xi += x[i];
        yi += y[i];
        xi2 += x[i]*x[i];
        xiyi += x[i]*y[i];
    }

    double a, b;
    vector<vector<double>> arr(2, vector<double> (3));

    arr[0][0] = n;
    arr[0][1] = xi;
    arr[0][2] = yi;
    
    arr[1][0] = xi;
    arr[1][1] = xi2;
    arr[1][2] = xiyi;

    vector<double> ans = gauss_jordan(arr, 2);

    cout << "\nEquation : " << endl;
    cout << "y = " << ans[0] << " + " << ans[1] << "x" << endl;
}



int main() {
    cin >> n;

    vector<double> x(n), y(n);

    for (int i=0; i<n; i++) {
        cin >> x[i];
    }
    
    for (int i=0; i<n; i++) {
        cin >> y[i];
    }

    int choice;
    cout << "1. Linear\n";
    cout << "2. Polynomial\n";
    cout << "3. Transcendental (y=ae^x)\n";
    cout << "4. Transcendental (y=ax^b)\n";
    cout << "5. Polynomial of useer input degree\n";

    cout << "Enter choice : ";
    cin >> choice;

    switch (choice) {
        case 1 : linear(x, y);
        break;

        case 2 : poly(x, y);
        break;

        case 3 : td (x, y);
        break;

        case 4 : td2(x, y);
        break;

        case 5 : poly_n(x, y);
        break;
    }
}
