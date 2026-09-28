#include<bits/stdc++.h>
using namespace std;
int n;

int fact (int num) {
    int sum = 1;
    for (int i=num; i>1; i--) {
        sum*=i;
    }
    return sum;
}

void dd (vector<double> &x, vector<double> &y) {
    vector<vector<double>> table (n, vector<double> (n, 0));

    for (int i=0; i<n; i++) {
        table[i][0] = y[i];
    }

    for (int j=1; j<n; j++) {
        for (int i=0; i+j<n; i++) {
            table[i][j] = (table[i+1][j-1]-table[i][j-1])/(x[i+j]-x[i]);
        }
    }
    

    cout << "Table : " << endl;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) {
            cout << table[i][j] << "   ";
        }
        cout << endl;
    }

    for (int i=0; i<n; i++) {
        if (i>0) cout << " + ";

        double coeff = table[0][i];
        cout << coeff << " ";

        for (int j=0; j<i; j++) {
            cout << "(x - " << x[j] << " )";
        }
    }
    
    cout << endl;

    double x_val;
    cin >> x_val;

    double ans = 0;

    for (int i=0; i<n; i++) {

        double coeff = table[0][i];
        double d = 1;

        for (int j=0; j<i; j++) {
            d *= (x_val-x[j]);
        }
        ans += d*coeff;
    }
    cout << ans << endl;
}


void backword (vector<double> x, vector<double> y) {
    double h = x[1]-x[0];

    vector<vector<double>> table(n, vector<double> (n, 0));

    for (int i=0; i<n; i++) {
        table[i][0] = y[i];
    }

    for (int j=1; j<n; j++) {
        for (int i=0; i+j<n; i++) {
            table[i][j] = table[i+1][j-1]-table[i][j-1];
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) {
            cout << setw(4) << table[i][j] << "   ";
        }
        cout << endl;
    }

    for (int i=0; i<n; i++) {
        if (i > 0)
            cout << " + ";
        double coeff = table[0][i]/(fact(i)*pow(h, i));
        cout << coeff;

        for (int j=0; j<i; j++) {
            cout << "(x - " << x[j] << " ) " ; 
        }
    }

    double x_val;
    cout << endl;
    cin >> x_val;

    double ans = 0;

    for (int i=0; i<n; i++) {
        double d = 1;
        double coeff = table[0][i]/(fact(i)*pow(h, i));

        for (int j=0; j<i; j++) {
            double something = x_val-x[j];
            d*=something;
        }
        d*=coeff;
        ans+=d;
    }

    cout << fixed << setprecision(3) << "Ans " << ans << endl;
}

void forward (vector<double> x, vector<double> y) {
    double h = x[1]-x[0];

    vector<vector<double>> table(n, vector<double> (n, 0));

    for (int i=0; i<n; i++) {
        table[i][0] = y[i];
    }

    for (int j=1; j<n; j++) {
        for (int i=0; i+j<n; i++) {
            table[i][j] = table[i+1][j-1]-table[i][j-1];
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i; j++) {
            cout << setw(4) << table[i][j] << "   ";
        }
        cout << endl;
    }

    for (int i=0; i<n; i++) {
        if (i > 0)
            cout << " + ";
        double coeff = table[0][i]/(fact(i)*pow(h, i));
        cout << coeff;

        for (int j=0; j<i; j++) {
            cout << "(x - " << x[j] << " ) " ; 
        }
    }

    double x_val;
    cout << endl;
    cin >> x_val;

    double ans = 0;

    for (int i=0; i<n; i++) {
        double d = 1;
        double coeff = table[0][i]/(fact(i)*pow(h, i));

        for (int j=0; j<i; j++) {
            double something = x_val-x[j];
            d*=something;
        }
        d*=coeff;
        ans+=d;
    }

    cout << fixed << setprecision(3) << "Ans " << ans << endl;
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

    vector<pair<double, double>> xy(n);
    for (int i=0; i<n; i++) {
        xy[i] = {x[i], y[i]};
    }
    sort(xy.begin(), xy.end());

    for (int i=0; i<n; i++) {
        x[i] = xy[i].first;
        y[i] = xy[i].second;
    }

    dd (x, y);


    // forward (x, y);

    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    // backword(x, y);
}
