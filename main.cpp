#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Удаление ведущих нулей
string trimLeadingZeros(const string &num) {
    size_t pos = num.find_first_not_of('0');
    if (pos != string::npos)
        return num.substr(pos);
    return "0";
}

// Сравнение чисел
int compare(const string &a, const string &b) {
    string num1 = trimLeadingZeros(a);
    string num2 = trimLeadingZeros(b);
    if (num1.size() != num2.size())
        return num1.size() > num2.size() ? 1 : -1;
    return num1.compare(num2);
}

// Сложение
string add(const string &a, const string &b) {
    string num1 = a, num2 = b;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    
    string result;
    int carry = 0, sum = 0;

    size_t len = max(num1.size(), num2.size());
    for (size_t i = 0; i < len; ++i) {
        sum = carry;
        if (i < num1.size()) sum += num1[i] - '0';
        if (i < num2.size()) sum += num2[i] - '0';
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }
    if (carry) result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    return trimLeadingZeros(result);
}

//Вычитание
string subtract(const string &a, const string &b) {
    if (compare(a, b) < 0) return "-" + subtract(b, a);

    string num1 = a, num2 = b;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    string result;
    int borrow = 0, diff = 0;

    for (size_t i = 0; i < num1.size(); ++i) {
        diff = num1[i] - '0' - borrow;
        if (i < num2.size()) diff -= num2[i] - '0';
        borrow = (diff < 0) ? 1 : 0;
        result.push_back((diff + (borrow ? 10 : 0)) + '0');
    }
    reverse(result.begin(), result.end());
    return trimLeadingZeros(result);
}

// Умножение
string multiply(const string &a, const string &b) {
    string num1 = a, num2 = b;
    int len1 = num1.size(), len2 = num2.size();
    vector<int> result(len1 + len2, 0);

    for (int i = len1 - 1; i >= 0; --i) {
        for (int j = len2 - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }

    string strResult;
    for (int num : result) {
        if (!(strResult.empty() && num == 0)) strResult.push_back(num + '0');
    }
    return strResult.empty() ? "0" : strResult;
}

// Целочисленное деление
string divide(const string &a, const string &b) {
    if (compare(b, "0") == 0) throw invalid_argument("Division by zero");
    if (compare(a, b) < 0) return "0";

    string dividend = a, divisor = b, result;

    while (compare(dividend, divisor) >= 0) {
        string temp = divisor;
        string quotient = "1";

        while (compare(add(temp, temp), dividend) <= 0) {
            temp = add(temp, temp);
            quotient = add(quotient, quotient);
        }

        dividend = subtract(dividend, temp);
        result = add(result, quotient);
    }
    return trimLeadingZeros(result);
}

int main() {
    string num1, num2;
    cout << "Введите два числа:\n";
    cin >> num1 >> num2;

    cout << "Сложение: " << add(num1, num2) << "\n";
    cout << "Вычитание: " << subtract(num1, num2) << "\n";
    cout << "Умножение: " << multiply(num1, num2) << "\n";
    try {
        cout << "Целочисленное деление: " << divide(num1, num2) << "\n";
    } catch (invalid_argument &e) {
        cout << e.what() << "\n";
    }

    cout << "Сравнение: ";
    int cmp = compare(num1, num2);
    if (cmp == 0) cout << "равны\n";
    else if (cmp > 0) cout << "первое больше\n";
    else cout << "второе больше\n";

    return 0;
}