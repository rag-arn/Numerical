#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;

// p(x) * (x - a)
vector<double> mulLinear(const vector<double> &p, double a) {
    vector<double> r(p.size() + 1, 0.0);
    for (int i = 0; i < (int)p.size(); ++i) {
        r[i + 1] += p[i];
        r[i] -= a * p[i];
    }
    return r;
}

// res += c * p
void addScaled(vector<double> &res, const vector<double> &p, double c) {
    if (res.size() < p.size()) res.resize(p.size(), 0.0);
    for (int i = 0; i < (int)p.size(); ++i) {
        res[i] += c * p[i];
    }
}

// Horner's rule
double evalPoly(const vector<double> &p, double x) {
    double r = 0.0;
    for (int i = (int)p.size() - 1; i >= 0; --i) {
        r = r * x + p[i];
    }
    return r;
}

void printPoly(const vector<double> &p) {
    cout << defaultfloat << setprecision(8);
    cout << "P(x) = ";
    bool first = true;
    for (int i = (int)p.size() - 1; i >= 0; --i) {
        double c = p[i];
        if (fabs(c) < EPS) continue;
        if (first) {
            if (c < 0) cout << "-";
        } else {
            cout << (c < 0 ? " - " : " + ");
        }
        cout << fabs(c);
        if (i == 1) cout << "x";
        else if (i > 1) cout << "x^" << i;
        first = false;
    }
    if (first) cout << 0;
    cout << "\n";
}

double factorial(int k) {
    double f = 1.0;
    for (int i = 2; i <= k; ++i) f *= i;
    return f;
}

// Builds d[i][j] = j-th order difference starting at index i
vector<vector<double>> buildDiff(const vector<double> &y) {
    int n = y.size();
    vector<vector<double>> d(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) d[i][0] = y[i];
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i + j < n; ++i) {
            d[i][j] = d[i + 1][j - 1] - d[i][j - 1];
        }
    }
    return d;
}

bool equallySpaced(const vector<double> &x, double &h) {
    h = x[1] - x[0];
    for (int i = 2; i < (int)x.size(); ++i) {
        if (fabs((x[i] - x[i - 1]) - h) > 1e-7) return false;
    }
    return true;
}

// ---------------- Newton's Forward ----------------
void forwardMethod(vector<double> x, vector<double> y, double xq) {
    int n = x.size();
    double h = 0.0;
    if (!equallySpaced(x, h)) {
        cout << "x values are not equally spaced. Use divided difference.\n";
        return;
    }
    vector<vector<double>> d = buildDiff(y);

    cout << "\nForward difference table:\n";
    for (int i = 0; i < n; ++i) {
        cout << setw(9) << x[i];
        for (int j = 0; j < n - i; ++j) {
            cout << setw(12) << d[i][j];
        }
        cout << "\n";
    }

    double u = (xq - x[0]) / h;
    cout << "\nh = " << h << ", u = (x - x0)/h = " << u << "\n";

    vector<double> P(1, 0.0), basis(1, 1.0);
    for (int k = 0; k < n; ++k) {
        double coeff = d[0][k] / (factorial(k) * pow(h, k));
        addScaled(P, basis, coeff);
        basis = mulLinear(basis, x[0] + k * h);
    }

    cout << "\nInterpolating polynomial (Newton's forward):\n";
    printPoly(P);
    cout << fixed << setprecision(6);
    cout << "f(" << defaultfloat << xq << fixed << ") = " << evalPoly(P, xq) << "\n";
}

// ---------------- Newton's Backward ----------------
void backwardMethod(vector<double> x, vector<double> y, double xq) {
    int n = x.size();
    double h = 0.0;
    if (!equallySpaced(x, h)) {
        cout << "x values are not equally spaced. Use divided difference.\n";
        return;
    }
    vector<vector<double>> d = buildDiff(y);

    cout << "\nBackward difference table:\n";
    for (int i = 0; i < n; ++i) {
        cout << setw(9) << x[i];
        for (int j = 0; j <= i; ++j) {
            cout << setw(12) << d[i - j][j];
        }
        cout << "\n";
    }

    double v = (xq - x[n - 1]) / h;
    cout << "\nh = " << h << ", v = (x - xn)/h = " << v << "\n";

    vector<double> P(1, 0.0), basis(1, 1.0);
    for (int k = 0; k < n; ++k) {
        double coeff = d[n - 1 - k][k] / (factorial(k) * pow(h, k));
        addScaled(P, basis, coeff);
        basis = mulLinear(basis, x[n - 1] - k * h);
    }

    cout << "\nInterpolating polynomial (Newton's backward):\n";
    printPoly(P);
    cout << fixed << setprecision(6);
    cout << "f(" << defaultfloat << xq << fixed << ") = " << evalPoly(P, xq) << "\n";
}

// ---------------- Newton's Divided Difference ----------------
void dividedMethod(vector<double> x, vector<double> y, double xq) {
    int n = x.size();
    vector<vector<double>> dd(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) dd[i][0] = y[i];

    for (int j = 1; j < n; ++j) {
        for (int i = 0; i + j < n; ++i) {
            dd[i][j] = (dd[i + 1][j - 1] - dd[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    cout << "\nDivided difference table:\n" << fixed << setprecision(7);
    for (int i = 0; i < n; ++i) {
        cout << setw(9) << x[i];
        for (int j = 0; j < n - i; ++j) {
            cout << setw(14) << dd[i][j];
        }
        cout << "\n";
    }

    int order;
    cout << "\nEnter order of polynomial to use (0 to " << n - 1
         << ", " << n - 1 << " uses all points): ";
    cin >> order;
    if (order < 0 || order > n - 1) order = n - 1;

    vector<double> P(1, 0.0), basis(1, 1.0);
    for (int k = 0; k <= order; ++k) {
        addScaled(P, basis, dd[0][k]);
        basis = mulLinear(basis, x[k]);
    }

    cout << "\nInterpolating polynomial of order " << order
         << " (Newton's divided difference):\n";
    printPoly(P);
    cout << fixed << setprecision(7);
    cout << "f(" << defaultfloat << xq << fixed << ") = " << evalPoly(P, xq) << "\n";

    if (order < n - 1) {
        double prod = 1.0;
        for (int i = 0; i <= order; ++i) prod *= (xq - x[i]);
        double R = dd[0][order + 1] * prod;
        cout << "Error estimate R_" << order << " = f[x0..x" << order + 1
             << "] * prod = " << dd[0][order + 1] << " * " << prod
             << " = " << R << "\n";
    } else {
        cout << "(No extra data point left, so the error estimate is not computed.)\n";
    }
}

int main() {

    cout << "1. Newton's Forward Interpolation\n"
         << "2. Newton's Backward Interpolation\n"
         << "3. Newton's Divided Difference Interpolation\n"
         << "Choose a method: ";
    int choice;
    if (!(cin >> choice)) return 0;

    int n;
    cout << "Enter number of data points: ";
    cin >> n;
    if (n < 2) {
        cout << "At least 2 points are needed.\n";
        return 0;
    }

    vector<double> x(n), y(n);
    cout << "Enter the values of x:\n";
    for (int i = 0; i < n; ++i) cin >> x[i];

    cout << "Enter the values of f(x):\n";
    for (int i = 0; i < n; ++i) cin >> y[i];

    double xq;
    cout << "Enter the value of x to interpolate: ";
    cin >> xq;

    if (choice == 1 || choice == 2) {
        vector<pair<double, double>> pts(n);
        for (int i = 0; i < n; ++i) pts[i] = {x[i], y[i]};
        sort(pts.begin(), pts.end());
        for (int i = 0; i < n; ++i) {
            x[i] = pts[i].first;
            y[i] = pts[i].second;
        }
    }

    cout << fixed << setprecision(6);
    if (choice == 1) forwardMethod(x, y, xq);
    else if (choice == 2) backwardMethod(x, y, xq);
    else if (choice == 3) dividedMethod(x, y, xq);
    else cout << "Invalid choice.\n";

    return 0;
}
