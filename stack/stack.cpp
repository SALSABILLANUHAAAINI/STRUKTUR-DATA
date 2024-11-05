#include <iostream>
#include<cstdlib>

using namespace std;


//membuat node
typedef struct node {
    int data;
    struct node *next;
} Node;

//membuat stack 
typedef struct Stack {
    int count;
    int maxSize;
    struct node *top;
} Stack;

Stack stack;

//deklarasi fungsi 
void createStack();
int  stackCount();
void sizemax(int maxSize);
bool isEmpty();
bool isFull();
void pushStack(int data);
void popStack();
void stackTop();
void emptyStack();
void destroyStack();
void displayStack();


//tampilan menu
int main() {
	sizemax(5);//membatasi size stack
	createStack();
	char pilihan;
	int data;
	
	do {
		system("cls");
		cout << "=========Menu==============\n";
		cout <<"pilih opsi menu :\n";
		cout <<"1. Push Stack:(menambah data kedalam stack)\n";
		cout <<"2. Pop Stack:(menghapus data paling atas dari stack)\n";
		cout <<"3. Stack Top :(mengecek apakah ada top dalam stack)\n";
		cout <<"4. Empty Stack:( mengecek apakah stack kosong)\n";
		cout <<"5. Stack Count :(menghitung ukuran stack)\n";
		cout <<"6. Display Stack :(menampilkan stack)\n";
		cout <<"7. Destroy Stack :(menghapus semua isi stack)\n";
		cout <<"masukan pilihan(tekan E untuk keluar) :";
		cin >> pilihan;
		
		if (pilihan == '1'){
			 cout << "Masukkan nilai untuk di push: ";
            cin >> data;
			pushStack(data);
		}else if(pilihan == '2'){
			popStack();
		}else if(pilihan == '3'){
			stackTop();
		}else if(pilihan == '4'){
			emptyStack();
		}else if(pilihan == '5'){
			cout << "ukuran stack saat ini : " << stackCount() << endl;
		}else if(pilihan== '6'){
			displayStack();
		}else if(pilihan == '7'){
			destroyStack();
		}else if (pilihan == 'E' || pilihan == 'e') {
			cout <<  "Keluar dari program.\n";
		}else {
            cout << "Pilihan tidak valid!\n";
        }
        cout << "\nTekan Enter untuk melanjutkan...\n";
        cin.ignore(); 
        cin.get();
	
	} while (pilihan != 'E' || pilihan != 'e') ;
	return 0;
		
}

//membuat stack baru 
void createStack(){
	stack.count = 0;
    stack.top = NULL;
    return;
}

int stackCount() {
    return stack.count;
}

//membuat inisialisasi maxsimal size
void sizemax(int maxSize){
	stack.top = NULL;
	stack.maxSize = maxSize;
	stack.count = 0;
}

//fungsi  mengecek apakan stack kosong
bool isEmpty() {
    return stack.top == NULL;
}
//fungsi stack penuh
bool isFull(){
	return stack.count == stack.maxSize;
}

//memasukan data/ menambah data di top
void pushStack(int data){
	//cek fullstack
	if (isFull()) {
    cout << "Stack penuh!, jumlah data : " << stackCount() << " \n Hapus beberapa data terlebih dahulu untuk menambah data. ";
    return;
    }
    Node *newPtr = new Node;
    if(newPtr == NULL){
        cout << "Alokasi memori gagal!";
        return;
    }
    newPtr -> data = data;
    newPtr -> next = stack.top;
    stack.top = newPtr;
    stack.count++;
    cout << "Data " << data  << " berhasil ditambahkan ke stack.\n";
}

//menghapus data pada top
void popStack(){
	Node *newPtr = new Node;
    if (isEmpty()) {
        cout << "Stack kosong, tidak ada data untuk di-pop.\n";
        return;
    }
    node *dltPtr = stack.top;
    int dataOut = stack.top -> data;
    stack.top = stack.top -> next;
    stack.count--;
    delete dltPtr;
    cout << "Data " << dataOut<< " berhasil dihapus dari stack.\n";
}

//mengecek isi stack/kondisi stack saai ini
void emptyStack() {
    if (isEmpty()) {
        cout << "Stack kosong saat ini" << endl;
    } else if (isFull()) {
        cout << "Stack sudah penuh" << endl;
    } else {
        cout << "Stack berisi beberapa data" << endl;
    }
}
	
//cek value data pada top
void stackTop(){
	   if(isEmpty()){
        cout << "Stack kosong saat ini !";
        return;
    }
    cout << "data di top adalah : " << stack.top -> data;	
}

//menampilkan isi stack
void displayStack() {
    Node *pWalker = stack.top;

    if (pWalker == NULL) {
        cout << "Stack kosong!\n";
    } else {
        cout << "Isi stack: ";
        while (pWalker != NULL) {
            cout << pWalker->data << " ";
            pWalker = pWalker->next;
        }
        cout << endl;
    }
}

//mengosongkan/ menghapus semua isi stack
void destroyStack(){
    while (stack.top != NULL){
        Node *temp = stack.top;
        stack.top = stack.top -> next;
        delete temp;
    }
    stack.count = 0;
    cout<< "stack telah dikosongkan.\n";
}


