#define maxAcc 20
#define maxMenu 40
#define maxBasket 15

struct akun{ //Struct data akun yang terdaftar
	char id[16];
	char nama[30];
	char password[16];
	char tipe[8];
	long int saldo;
	int key;
};

struct menu{ //Struct data menu makanan
	char nama[30];
	char makanan[50];
	int harga;
	int kode;
};

struct basket{ //Struct data pesanan yang diterima
	char makanan[50];
	char nama[30];
	int harga;
	int kode;
	int ongkir;
	char resto[30];
	char statusResto[15];
	char statusKurir[15];
	char kurir[30];
	struct basket *next;
};

void login();
void createAcc();
void title();
void countLines(int *line, FILE *list);
void mainMenu(int selected);
void mainResto();
void mainPembeli();
void createResto(int selected, struct akun acc[maxAcc]);
void countResto(struct akun acc[maxAcc], int *menu, int line);
void addMenu(int selected, struct akun acc[maxAcc]);
void readMenu(FILE *listMenu, struct menu menu[maxMenu], int line);
void updateMenu(int selected, struct akun acc[maxAcc]);
void menuPembeli(struct akun acc[maxAcc], int selected);
void topUp(struct akun acc[maxAcc], int selected);
void createResto(int selected, struct akun acc[maxAcc]);
void printBasket(struct basket *queue);
void freeBasket(struct basket **head);
void linkStart(struct basket **head, char nama[30], char resto[30], char makanan[50], char statusResto[15], char statusKurir[15], char kurir[30], int harga, int kode, int ongkir);
void linkTail(struct basket **head, char nama[30], char resto[30], char makanan[50], char statusResto[15], char statusKurir[15], char kurir[30], int harga, int kode, int ongkir);
void printOrder(struct basket *basket, struct akun acc[maxAcc], int selected);
void displayMenu(int selected, struct akun acc[maxAcc]);
void queueResto(struct akun acc[], int selected);
void mainKurir();
void orderKurir(struct akun acc[maxAcc], int selected);
void statusOrder(struct akun acc[maxAcc], int selected);
void transferSaldo(char pembeli[30], char kurir[30], char resto[30], int total);
void deleteBasket(char pembeli[30], char kurir[30], char resto[30]);
void loading();
void end();