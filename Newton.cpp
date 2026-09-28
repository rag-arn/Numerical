#include<bits/stdc++.h>
using namespace std;
int n;

double fact (int num) {
    double ans = 1;

    for (int i=1; i<=num; i++) {
        ans *= i;
    }

    return ans;
}

void backward (vector<double> &x, vector<double> &y) {
    double x_val;
    cin >> x_val;

    double h = x[1]-x[0];

    vector<vector<double>> table(n, vector<double> (n, 0));

    for (int i=0; i<n; i++) {
        table[i][0] = y[i];
    }

    for (int j=1; j<n; j++) {
        for (int i=n-1; i>=j; i--) {
            table[i][j] = table[i][j-1]-table[i-1][j-1];
        }
    }

    cout << "Backward table : " << endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<=i; j++) {
            cout << fixed << setprecision(6) << table[i][j] << "   ";
        }
        cout << endl;
    }

    cout << "Backward function : " << endl;

    for (int i=0; i<n; i++) {
        if (i>0) cout << " + ";

        double coeff = table[n-1][i]/(fact(i)* pow(h, i));
        cout << coeff << " ";

        for (int j=n-1; j>n-i-1; j--) {
            cout << "(x - " << x[j] << " )";
        }
    }
    cout << endl;

    double ans = 0;

    for (int i=0; i<n; i++) {
        double d = 1;

        double coeff = table[n-1][i]/(fact(i)* pow(h, i));

        for (int j=n-1; j>n-i-1; j--) {
            d *= (x_val-x[j]);
        }
        d *= coeff;

        ans += d;
    }

    cout << "Backward answer for " << x_val << " = " << ans << endl;
}


void forward (vector<double> &x, vector<double> &y) {
    double h = x[1]-x[0];

    double x_val;
    cin >> x_val;

    vector<vector<double>> table(n, vector<double> (n, 0));

    for (int i=0; i<n; i++) {
        table[i][0] = y[i];
    }

    for (int j=1; j<n; j++) {
        for (int i=0; i<n-j; i++) {
            table[i][j] = (table[i+1][j-1]-table[i][j-1]);
        }
    }

    cout << "Table : " << endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) {
            cout << fixed << setprecision(6) << table[i][j] << "   ";
        }
        cout << endl;
    }

    cout << "\n\nFunction : " << endl;

    for (int i=0; i<n; i++) {
        if (i>0) cout << " + ";

        double coeff = table[0][i]/(fact(i)*pow(h, i));
        cout << coeff << " ";

        for (int j=0; j<i; j++) {
            cout << "(x - " << x[j] << " )"; 
        }
    }
    cout << endl;


    double ans = 0;

    for (int i=0; i<n; i++) {
        double d = 1;

        double coeff = table[0][i]/(fact(i)*pow(h, i));

        for (int j=0; j<i; j++) {
            d *= (x_val-x[j]);
        }
        d *= coeff;

        ans += d;
    }

    cout << "Answer is : " << ans << endl;
}

void dd (vector<double> &x, vector<double> &y) {
    double x_val;
    cin >> x_val;

    vector<vector<double>> table(n, vector<double> (n, 0));

    for (int i=0; i<n; i++) {
        table[i][0] = y[i];
    }

    for (int j=1; j<n; j++) {
        for (int i=0; i<n-j; i++) {
            table[i][j] = (table[i+1][j-1]-table[i][j-1])/(x[i+j]-x[i]);
        }
    }

    cout << "Table : " << endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) {
            cout << fixed << setprecision(6) << table[i][j] << "   ";
        }
        cout << endl;
    }

    cout << "\n\nFunction : " << endl;

    for (int i=0; i<n; i++) {
        if (i>0) cout << " + ";

        double coeff = table[0][i];
        cout << coeff << " ";

        for (int j=0; j<i; j++) {
            cout << "(x - " << x[j] << " )"; 
        }
    }
    cout << endl;


    double ans = 0;

    for (int i=0; i<n; i++) {
        double d = 1;

        double coeff = table[0][i];

        for (int j=0; j<i; j++) {
            d *= (x_val-x[j]);
        }
        d *= coeff;

        ans += d;
    }

    cout << "Answer is : " << ans << endl;
}

void dd_error (vector<double> &x, vector<double> &y) {
    n--;
    double x_val;
    cin >> x_val;

    vector<vector<double>> table(n, vector<double> (n, 0));

    for (int i=0; i<n; i++) {
        table[i][0] = y[i];
    }

    for (int j=1; j<n; j++) {
        for (int i=0; i<n-j; i++) {
            table[i][j] = (table[i+1][j-1]-table[i][j-1])/(x[i+j]-x[i]);
        }
    }

    cout << "Table : " << endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) {
            cout << fixed << setprecision(6) << table[i][j] << "   ";
        }
        cout << endl;
    }

    cout << "\n\nFunction : " << endl;

    for (int i=0; i<n; i++) {
        if (i>0) cout << " + ";

        double coeff = table[0][i];
        cout << coeff << " ";

        for (int j=0; j<i; j++) {
            cout << "(x - " << x[j] << " )"; 
        }
    }
    cout << endl;


    double ans = 0;

    for (int i=0; i<n; i++) {
        double d = 1;

        double coeff = table[0][i];

        for (int j=0; j<i; j++) {
            d *= (x_val-x[j]);
        }
        d *= coeff;

        ans += d;
    }

    cout << "Answer is : " << ans << endl;

    int nn = n+1;
    x_val = x[nn-1];
    double e_ans = 0;

    for (int i=0; i<n; i++) {
        double d = 1;

        double coeff = table[0][i];

        for (int j=0; j<i; j++) {
            d *= (x_val-x[j]);
        }
        d *= coeff;

        e_ans += d;
    }

    double percentage = (fabs(e_ans-y[nn-1])/y[nn-1])*100;
    cout << "Error percentage : " << percentage << endl;
}

int main() {
    cout << "1 for forward" << endl;
    cout << "2 for backward" << endl;
    cout << "3 for divided difference" << endl;
    cout << "4 for divided difference with error" << endl;

    int choice;
    cout << "Choice : ";
    cin >> choice;


    cin >> n;

    vector<double> x(n);
    vector<double> y(n);

    for (int i=0;i<n; i++) {
        cin >> x[i];
    }
    for (int i=0;i<n; i++) {
        cin >> y[i];
    }

    vector<pair<double, double>> xy(n);

    for (int i=0; i<n; i++) {
        xy[i] = {x[i], y[i]};
    }

    sort (xy.begin(), xy.end());

    for (int i=0; i<n; i++) {
        x[i] = xy[i].first;
        y[i] = xy[i].second;
    }

    if (choice==1) {
        forward(x, y);
    }

    else if (choice==2) {
        backward(x, y);
    }

    else if (choice==3) {
        dd(x, y);
    }
    
    else if (choice==4) {
        dd_error(x, y);
    }

}
