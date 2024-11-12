#include <iostream>
#include <string>
#include <cctype> 
#include <cstdlib> 

using namespace std;


typedef struct node {
    int data;
    struct node *next;
} Node;


typedef struct Stack {
    Node *top;
} Stack;

Stack stack;
void createStack();
bool isEmpty();
void pushStack(int data);
void popStack();
int stackTop();
void destroyStack();
int precedence(char op); 
string infixToPostfix(const string& infix, bool& isValid);
int stringToInt(const string& str);
int evaluatePostfix(const string& postfix);

int main() {
    createStack();
    char pilihan;
    string infixExp;

    do {
        system("cls");

        cout << "=========Menu==============\n";
        cout << "Pilih opsi:\n";
        cout << "1. Infix to Postfix (masukan angka 0-9 & tanda perhitungan (+,-,/,*))\n";
        cout << "2. Evaluasi hasil postfix\n";
        cout << "Masukan pilihan (tekan E untuk keluar) : ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == '1') {
            cout << "Masukkan ekspresi infix: ";
            getline(cin, infixExp);

            bool isValid = true;
            string postfix = infixToPostfix(infixExp, isValid);

            if (!isValid) {
                cout << "Ekspresi infix tidak valid (keseimbangan kurung salah)." << endl;
            } else {
                cout << "Ekspresi postfix: " << postfix << endl;
                int result = evaluatePostfix(postfix);
                cout << "Hasil evaluasi postfix: " << result << endl;
            }
        } else if (pilihan == '2') {
            cout << "Masukkan ekspresi postfix yang ingin diselesaikan: ";
            string postfixExp;
            getline(cin, postfixExp);
            cout << "Hasil evaluasi: " << evaluatePostfix(postfixExp) << endl;
        } else if (pilihan == 'E' || pilihan == 'e') {
            cout << "Keluar dari program.\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }

        cout << "\nTekan Enter untuk melanjutkan...\n";
        cin.ignore();

    } while (pilihan != 'E' && pilihan != 'e');

    return 0;
}


void createStack() {
    stack.top = NULL;
}


bool isEmpty() {
    return stack.top == NULL;
}


void pushStack(int data) {
    Node *newPtr = new Node;
    newPtr->data = data;
    newPtr->next = stack.top;
    stack.top = newPtr;
}


void popStack() {
    if (!isEmpty()) {
        Node *dltPtr = stack.top;
        stack.top = stack.top->next;
        delete dltPtr;
    } else {
        cout << "Stack kosong, tidak bisa pop." << endl;
    }
}


int stackTop() {
    if (!isEmpty()) {
        return stack.top->data;
    } else {
        cout << "Stack kosong, tidak ada elemen teratas." << endl;
        return -1;
    }
}


void destroyStack() {
    while (!isEmpty()) {
        Node *temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
}

// Fungsi untuk menentukan urutan operasi
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

//  Konversi infix ke postfix
string infixToPostfix(const string& infix, bool& isValid) {
    createStack();
    string postfix = "";
    int balance = 0;

    for (size_t i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            i--;
        } else if (ch == '(') {
            pushStack(ch);
            balance++;
        } else if (ch == ')') {
            balance--;
            if (balance < 0) {
                isValid = false;
                destroyStack();
                return "";
            }
            while (!isEmpty() && stackTop() != '(') {
                postfix += (char)stackTop();
                postfix += ' ';
                popStack();
            }
            if (!isEmpty()) popStack();
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!isEmpty() && precedence(stackTop()) >= precedence(ch)) {
                postfix += (char)stackTop();
                postfix += ' ';
                popStack();
            }
            pushStack(ch);
        }
    }

    if (balance != 0) {
        isValid = false;
        destroyStack();
        return "";
    }

    while (!isEmpty()) {
        postfix += (char)stackTop();
        postfix += ' ';
        popStack();
    }

    return postfix;
}

// konversi manual string ke integer
int stringToInt(const string& str) {
    int num = 0;
    for (size_t i = 0; i < str.length(); i++) {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}

// Evaluasi ekspresi postfix
int evaluatePostfix(const string& postfix) {
    createStack();
    string number = "";

    for (size_t i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            number += ch;
        } else if (ch == ' ' && !number.empty()) {
            pushStack(stringToInt(number));
            number = "";
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (isEmpty()) return 0;
            int b = stackTop(); popStack();
            if (isEmpty()) return 0;
            int a = stackTop(); popStack();
            int result = 0;

            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b != 0) result = a / b;
                    else {
                        cout << "Error: Pembagian dengan nol!" << endl;
                        destroyStack();
                        return 0;
                    }
                    break;
            }
            pushStack(result);
        }
    }
    int finalResult = stackTop();
    destroyStack();
    return finalResult;
}

