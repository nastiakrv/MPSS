#include <iostream>
#include <locale>
using namespace std;

const int n = 8; // ʳ������ �����

// ����� ���
double x1[n] = { 0, 0, 0, 1, 1, 2, 2, 2 };
double x2[n] = { 1.5, 2.5, 3.5, 1.5, 3.5, 1.5, 2.5, 2.5 };
double y[n] = { 2.3, 4 + 0.3 * 11, 2 - 0.1 * 11, 5 - 0.2 * 11, 4 - 0.2 * 11, 6.1 + 0.2 * 11, 6.5 - 0.1 * 11, 7.2 };

int main() {

    setlocale(LC_ALL, "ukr");

    // ���������� �������� ������� ���������� ������
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

    // ��������� ������� �����������
    double det = n * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2) -
        sumX1 * (sumX1 * sumX2X2 - sumX1X2 * sumX2) +
        sumX2 * (sumX1 * sumX1X2 - sumX1X1 * sumX2);

    // ���������� �����������
    double a0 = (sumY * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2) -
        sumX1 * (sumX1Y * sumX2X2 - sumX1X2 * sumX2Y) +
        sumX2 * (sumX1Y * sumX1X2 - sumX1X1 * sumX2Y)) / det;

    double a1 = (n * (sumX1Y * sumX2X2 - sumX1X2 * sumX2Y) -
        sumY * (sumX1 * sumX2X2 - sumX1X2 * sumX2) +
        sumX2 * (sumX1 * sumX2Y - sumX1Y * sumX2)) / det;

    double a2 = (n * (sumX1X1 * sumX2Y - sumX1Y * sumX1X2) -
        sumX1 * (sumX1 * sumX2Y - sumX1Y * sumX2) +
        sumY * (sumX1 * sumX1X2 - sumX1X1 * sumX2)) / det;

    // ��������� ����������� �������
    cout << "�i������ �� ������: y = " << a0 << " + " << a1 << " * x1 + " << a2 << " * x2" << endl;

    // ���������� �������� � ����� (x1 = 1.5, x2 = 3)
    double x1_new = 1.5;
    double x2_new = 3;
    double y_new = a0 + a1 * x1_new + a2 * x2_new;
    cout << "�������� �����i� � ����i (" << x1_new << ", " << x2_new << ") = " << y_new << endl;

    // ���������� ����������� ����������� R^2
    double y_mean = sumY / n;
    double SS_tot = 0, SS_res = 0;
    for (int i = 0; i < n; i++) {
        SS_tot += (y[i] - y_mean) * (y[i] - y_mean);
        double y_pred = a0 + a1 * x1[i] + a2 * x2[i];
        SS_res += (y[i] - y_pred) * (y[i] - y_pred);
    }

    double R2 = 1 - (SS_res / SS_tot);

    cout << "����i�i��� ������i���i� R^2 = " << R2 << endl;

    return 0;
}




//#include <iostream>
//#include <locale>
//using namespace std;
//
//const int n = 8; // ʳ������ �����
//
//// ����� ���
//double x1[n] = { 0, 0, 0, 1, 1, 2, 2, 2 };  // �������� x1 ��� ����� �����
//double x2[n] = { 1.5, 2.5, 3.5, 1.5, 3.5, 1.5, 2.5, 2.5 };  // �������� x2 ��� ����� �����
//double y[n] = { 2.3, 4 + 0.3 * 2, 2 - 0.1 * 2, 5 - 0.2 * 2, 4 - 0.2 * 2, 6.1 + 0.2 * 2, 6.5 - 0.1 * 2, 7.2 };  // ������ �������� y ��� ����� �����
//
//int main() {
//
//    setlocale(LC_ALL, "ukr");  // ������������ ��������� ���������� ��� ���������� ��������� ������
//
//    // ���������� ������ ��� ���������� ���, �� �������� ��� ������� ���������� ������
//    double sumX1 = 0, sumX2 = 0, sumY = 0;
//    double sumX1X1 = 0, sumX2X2 = 0, sumX1X2 = 0;
//    double sumX1Y = 0, sumX2Y = 0;
//
//    // ���������� ���������� ��� �� ���� �������
//    for (int i = 0; i < n; i++) {
//        sumX1 += x1[i];  // ���� ������� x1
//        sumX2 += x2[i];  // ���� ������� x2
//        sumY += y[i];    // ���� ������� y
//        sumX1X1 += x1[i] * x1[i];  // ���� �������� x1
//        sumX2X2 += x2[i] * x2[i];  // ���� �������� x2
//        sumX1X2 += x1[i] * x2[i];  // ���� ������� x1 �� x2
//        sumX1Y += x1[i] * y[i];    // ���� ������� x1 �� y
//        sumX2Y += x2[i] * y[i];    // ���� ������� x2 �� y
//    }
//
//    // ���������� ����������� ������� �����������
//    double det = n * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2) -
//        sumX1 * (sumX1 * sumX2X2 - sumX1X2 * sumX2) +
//        sumX2 * (sumX1 * sumX1X2 - sumX1X1 * sumX2);
//
//    // ���������� ����������� a0, a1, a2 ������� ��������� ��������
//    double a0 = (sumY * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2) -
//        sumX1 * (sumX1Y * sumX2X2 - sumX1X2 * sumX2Y) +
//        sumX2 * (sumX1Y * sumX1X2 - sumX1X1 * sumX2Y)) / det;
//
//    double a1 = (n * (sumX1Y * sumX2X2 - sumX1X2 * sumX2Y) -
//        sumY * (sumX1 * sumX2X2 - sumX1X2 * sumX2) +
//        sumX2 * (sumX1 * sumX2Y - sumX1Y * sumX2)) / det;
//
//    double a2 = (n * (sumX1X1 * sumX2Y - sumX1Y * sumX1X2) -
//        sumX1 * (sumX1 * sumX2Y - sumX1Y * sumX2) +
//        sumY * (sumX1 * sumX1X2 - sumX1X1 * sumX2)) / det;
//
//    // ��������� ������� ����� ������
//    cout << "�i������ �� ������: y = " << a0 << " + " << a1 << " * x1 + " << a2 << " * x2" << endl;
//
//    // ���������� �������� ������� � ����� (x1 = 1.5, x2 = 3)
//    double x1_new = 1.5;
//    double x2_new = 3;
//    double y_new = a0 + a1 * x1_new + a2 * x2_new;
//    cout << "�������� �����i� � ����i (" << x1_new << ", " << x2_new << ") = " << y_new << endl;
//
//    // ���������� ����������� ����������� R^2
//    double y_mean = sumY / n;  // ������ �������� y
//    double SS_tot = 0, SS_res = 0;  // ����������� ������ ��� ���������� ��� ��������
//    for (int i = 0; i < n; i++) {
//        SS_tot += (y[i] - y_mean) * (y[i] - y_mean);  // �������� ���� �������� ��������
//        double y_pred = a0 + a1 * x1[i] + a2 * x2[i];  // ������������ �������� y ��� ����� �����
//        SS_res += (y[i] - y_pred) * (y[i] - y_pred);  // ���� �������� ���������� ��������
//    }
//
//    // ���������� ����������� ����������� R^2
//    double R2 = 1 - (SS_res / SS_tot);
//
//    // ��������� ����������� ����������� R^2
//    cout << "����i�i��� ���������i� R^2 = " << R2 << endl;
//
//    return 0;
//}
