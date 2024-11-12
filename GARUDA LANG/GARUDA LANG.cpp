#include <iostream>
#include <string>
#include <cctype> 

using namespace std;

typedef struct node {
    char data;
    struct node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

//stack global
Stack stack;

//deklaras fungsi
void createStack();
bool isEmpty();
void pushStack(char data);
void popStack();
char stackTop();
void destroyStack();
bool isValidBracketSequence(const string& expression);


//menu utama
int main() {
    createStack();
    string expression;
    string completeExpression = "";
    char continueChecking;

    do {
        
        system("cls");

        cout << "Masukkan ekspresi untuk diperiksa validitasnya (akhiri ekspresi dengan tanda  '#'): \n";
        
        // Baca input multi-baris hingga '#' ditemukan
        completeExpression = "";  
        while (true) {
            getline(cin, expression);  
            if (expression.find('#') != string::npos) {  // Jika ditemukan karakter '#', berhenti
                completeExpression += expression.substr(0, expression.find('#')); //
                break;
            } else {
                completeExpression += expression + "\n";  
            }
        }

        // Periksa validitas ekspresi
        if (isValidBracketSequence(completeExpression)) {
            cout << "Ekspresi valid\n";
        } else {
            cout << "Ekspresi tidak valid\n";
        }

        destroyStack();

        // Tanya apakah pengguna ingin melanjutkan atau keluar
        cout << "\nTekan Enter2X untuk memeriksa kode lain atau tekan 'E' untuk keluar: ";
        continueChecking = getchar();
        getchar();  

    } while (continueChecking != 'E' && continueChecking != 'e');

    return 0;
}

void createStack() {
    stack.top = NULL;
}

bool isEmpty() {
    return stack.top == NULL;
}

void pushStack(char data) {
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
    }
}

char stackTop() {
    if (!isEmpty()) {
        return stack.top->data;
    } else {
        return '\0';  
    }
}

void destroyStack() {
    while (!isEmpty()) {
        popStack();
    }
}

bool isValidBracketSequence(const string& expression) {
    for (size_t i = 0; i < expression.length(); i++) {
        char ch = expression[i];

        // Abaikan spasi dan tab
        if (isspace(ch)) {
            continue; // Jika karakter adalah spasi / tab. lanjutkan ke karakter berikutnya
        }

        // Proses hanya tanda kurung
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
            pushStack(ch);  
        } 
        // Periksa tanda kurung tutup
        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            if (isEmpty()) {
                return false;  
            }
            char top = stackTop();
            // memastikan pasangan tanda kurung yang benar
            if ((top == '(' && ch == ')') ||
                (top == '{' && ch == '}') ||
                (top == '[' && ch == ']') ||
                (top == '<' && ch == '>')) {
                popStack();  // Pop jika pasangan cocok
            } else {
                return false;  
            }
        }
       
    }

    return isEmpty();  
}

