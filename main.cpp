#include <iostream>
#include <string>

using namespace std;

class LongNumber{
    char znak;
    string number;
private:
    int get_number(char c);
    string sum(char znak1, string num1, char znak2, string num2);
    string difference(char znak1, string num1, char znak2, string num2);
    string mult(char znak1, string num1, char znak2, string num2);
    void division(char znak1, string num1, char znak2, string num2, string &q, string &r);
    char compare(char znak1, string num1, char znak2, string num2);
public:
    LongNumber(string num);
    void show(){cout << znak << number << endl;};
    LongNumber operator+(LongNumber ob2){return LongNumber(sum(znak, number, ob2.znak, ob2.number));}
    LongNumber operator-(LongNumber ob2){return LongNumber(difference(znak, number, ob2.znak, ob2.number));}
    LongNumber operator*(LongNumber ob2){return LongNumber(mult(znak, number, ob2.znak, ob2.number));}
    LongNumber operator/(LongNumber ob2){
        string q;
        string r;
        division(znak, number, ob2.znak, ob2.number, q, r);
        return LongNumber(q);
    }
    LongNumber operator%(LongNumber ob2){
        string q;
        string r;
        division(znak, number, ob2.znak, ob2.number, q, r);
        return LongNumber(r);
    }
    bool operator>(LongNumber ob2){return compare(znak, number, ob2.znak, ob2.number) == '>';};
    bool operator<(LongNumber ob2){return compare(znak, number, ob2.znak, ob2.number) == '<';};
    bool operator==(LongNumber ob2){return compare(znak, number, ob2.znak, ob2.number) == '=';};
    bool operator>=(LongNumber ob2){
        char c = compare(znak, number, ob2.znak, ob2.number);
        return (c == '=' || c == '>');
    };
    bool operator<=(LongNumber ob2){
        char c = compare(znak, number, ob2.znak, ob2.number);
        return (c == '=' || c == '<');
    };
};

LongNumber::LongNumber(string num){
    if (num[0] == '-'){
        znak = '-';
        number = num.substr(1, num.length() - 1);
    }
    else if (num[0] == '+'){
        znak = '+';
        number = num.substr(1, num.length() - 1);
    }
    else{
        znak = '+';
        number = num;
    }
}

int LongNumber::get_number(char c){
    switch (c){
        case '0': {return 0;}
        case '1': {return 1;}
        case '2': {return 2;}
        case '3': {return 3;}
        case '4': {return 4;}
        case '5': {return 5;}
        case '6': {return 6;}
        case '7': {return 7;}
        case '8': {return 8;}
        case '9': {return 9;}
    }
    return 0;
}

string LongNumber::sum(char znak1, string num1, char znak2, string num2){
    char znak_res;
    if (znak1 == '-' && znak2 == '+')
        return difference('+', num2, '+', num1);
    if (znak1 == '+' && znak2 == '-')
        return difference('+', num1, '+', num2);
    if (znak1 == '+' && znak2 == '+')
        znak_res = '+';
    else if (znak1 == '-' && znak2 == '-')
        znak_res = '-';
    const string digits[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string result = "";
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int mod = 0;
    while (i >= 0 || j >= 0)
    {
        int a = i >= 0 ? get_number(num1[i]) : a = 0;
        int b = j >= 0 ? get_number(num2[j]) : b = 0;
        a += b + mod;
        mod = a / 10;
        result = digits[a % 10] + result;
        i--;
        j--;
    }
    if (mod != 0){
        result = digits[mod] + result;
    }
    return znak_res + result;
}

string LongNumber::difference(char znak1, string num1, char znak2, string num2){
    string result = "";
    if (znak1 == '+' && znak2 == '-') // a - -b == a + b
        return sum('+', num1, '+', num2);
    if (znak1 == '-' && znak2 == '+'){ // -a - b == -(a + b)
        result = sum('+', num1, '+', num2);
        result[0] = '-';
        return result;
    }
    if (znak1 == '-' and znak2 == '-') { // -a - -b == -a + b == b - a
        znak1 = '+';
        znak2 = '+';
        swap(num1, num2);
    }
    char znak_res = '+';
    switch (compare('+', num1, '+', num2)) {
        case '=' : {return "0";}
        case '<' : {
            znak_res = '-';
            swap(num1, num2);
            break;
        }
    }
    const string digits[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    int mod = 0;
    while (i >= 0 || j >= 0){
        int a = i >= 0 ? get_number(num1[i]) : a = 0;
        int b = j >= 0 ? get_number(num2[j]) : b = 0;
        a -= b + mod;
        if (a < 0){
            a += 10;
            mod = -1;
        }
        else mod = 0;
        result = digits[a % 10] + result;
        i--;
        j--;
    }
    return znak_res + result;
}

string LongNumber::mult(char znak1, string num1, char znak2, string num2){
    const string digits[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string null = "";
    string result = "";
    for (int i = num2.length() - 1; i >= 0; i--){
        int a = get_number(num2[i]);
        int mod = 0;
        string s = "";
        for (int j = num1.length() - 1; j >= 0; j--){
            int b = get_number(num1[j]) * a + mod;
            mod = b / 10;
            s = digits[b % 10] + s;
        }
        if (mod != 0){
            s = digits[mod] + s;
        }
        if (result == ""){
            result = s;
        }
        else {
            s += null;
            result = sum('+', result, '+', s);
        }
        null += "0";
    }
    if (znak1 != znak2)
        return '-' + result;
    return result;
}

void LongNumber::division(char znak1, string num1, char znak2, string num2, string &q, string &r){
    q = "";
    r = "";
    if (znak1 != znak2)
        q = "-" + q;
}

char LongNumber::compare(char znak1, string num1, char znak2, string num2){
    if (znak1 == '+' && znak2 == '-')
        return '>';
    if (znak1 == '-' && znak2 == '+')
        return '<';
    if (num1 == num2)
        return '=';
    if (num1.length() > num2.length())
        return '>' ? znak1 == '+' : '<';
    if (num1.length() < num2.length())
        return '<' ? znak1 == '+' : '>';
    for (int i = 0; i < num1.length(); i++){
        if (num1[i] > num2[i]) return '>' ? znak1 == '+' : '<';
        if (num1[i] < num2[i]) return '<' ? znak1 == '+' : '>';
    }
}

int main()
{
    string n;
    cin >> n;
    LongNumber numb1 = LongNumber(n);
    cin >> n;
    LongNumber numb2 = LongNumber(n);
    cout << (numb1 > numb2) << endl;
    LongNumber result = numb1 - numb2;
    result.show();
    return 0;
}