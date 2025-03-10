#include <iostream>
#include <locale>
using namespace std;

const int n = 8; // Ê³ëüê³ñòü òî÷îê

// Âõ³äí³ äàí³
double x1[n] = { 0, 0, 0, 1, 1, 2, 2, 2 };
double x2[n] = { 1.5, 2.5, 3.5, 1.5, 3.5, 1.5, 2.5, 2.5 };
double y[n] = { 2.3, 4 + 0.3 * 11, 2 - 0.1 * 11, 5 - 0.2 * 11, 4 - 0.2 * 11, 6.1 + 0.2 * 11, 6.5 - 0.1 * 11, 7.2 };

int main() {

    setlocale(LC_ALL, "ukr");

    // Îá÷èñëåííÿ åëåìåíò³â ìàòðèö³ íîðìàëüíèõ ð³âíÿíü
    double sumX1 = 0, sumX2 = 0, sumY = 0;
    double sumX1X1 = 0, sumX2X2 = 0, sumX1X2 = 0;
    double sumX1Y = 0, sumX2Y = 0;

    for (int i = 0; i < n; i++) {
        sumX1 += x1[i];
        sumX2 += x2[i];
        sumY += y[i];
        sumX1X1 += x1[i] * x1[i];
        sumX2X2 += x2[i] * x2[i];
        sumX1X2 += x1[i] * x2[i];
        sumX1Y += x1[i] * y[i];
        sumX2Y += x2[i] * y[i];
    }

    // Âèçíà÷íèê ìàòðèö³ êîåô³ö³ºíò³â
    double det = n * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2) -
        sumX1 * (sumX1 * sumX2X2 - sumX1X2 * sumX2) +
        sumX2 * (sumX1 * sumX1X2 - sumX1X1 * sumX2);

    // Îá÷èñëåííÿ êîåô³ö³ºíò³â
    double a0 = (sumY * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2) -
        sumX1 * (sumX1Y * sumX2X2 - sumX1X2 * sumX2Y) +
        sumX2 * (sumX1Y * sumX1X2 - sumX1X1 * sumX2Y)) / det;

    double a1 = (n * (sumX1Y * sumX2X2 - sumX1X2 * sumX2Y) -
        sumY * (sumX1 * sumX2X2 - sumX1X2 * sumX2) +
        sumX2 * (sumX1 * sumX2Y - sumX1Y * sumX2)) / det;

    double a2 = (n * (sumX1X1 * sumX2Y - sumX1Y * sumX1X2) -
        sumX1 * (sumX1 * sumX2Y - sumX1Y * sumX2) +
        sumY * (sumX1 * sumX1X2 - sumX1X1 * sumX2)) / det;

    // Âèâåäåííÿ êîåô³ö³ºíò³â ð³âíÿííÿ
    cout << "Ðiâíÿííÿ ìàº âèãëÿä: y = " << a0 << " + " << a1 << " * x1 + " << a2 << " * x2" << endl;

    // Îá÷èñëåííÿ çíà÷åííÿ ó òî÷ö³ (x1 = 1.5, x2 = 3)
    double x1_new = 1.5;
    double x2_new = 3;
    double y_new = a0 + a1 * x1_new + a2 * x2_new;
    cout << "Çíà÷åííÿ ôóíêöi¿ â òî÷öi (" << x1_new << ", " << x2_new << ") = " << y_new << endl;

    // Îá÷èñëåííÿ êîåô³ö³ºíòà äåòåðì³íàö³¿ R^2
    double y_mean = sumY / n;
    double SS_tot = 0, SS_res = 0;
    for (int i = 0; i < n; i++) {
        SS_tot += (y[i] - y_mean) * (y[i] - y_mean);
        double y_pred = a0 + a1 * x1[i] + a2 * x2[i];
        SS_res += (y[i] - y_pred) * (y[i] - y_pred);
    }

    double R2 = 1 - (SS_res / SS_tot);

    cout << "Êîåôiöiºíò äåòåðìiíàöi¿ R^2 = " << R2 << endl;

    return 0;
}
