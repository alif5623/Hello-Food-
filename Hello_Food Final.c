/*
Kelas Pemrograman Lanjut 02
Proyek Akhir Semester: Hello Food!

Kelompok 13:
Laode Alif Ma'sum Sidrajat Raja Ika / 2106731213
Zalfy Putra Rezky / 2106731453
*/
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <conio.h>
#include <time.h> 
#include "Header_HF.h"

int main(void){
	loading();
	system("CLS");
	system("Color 0F");
	omp_set_num_threads(omp_get_max_threads());  //Menggunakan seluruh thread yang terdapat pada komputer yang menjalankan
	if(access("account.txt", F_OK) == 0){
		login();
	}else{
		printf("Belum ada akun yang terdaftar\nSilahkan buat akun baru!\n\n");
		createAcc();
	}
}

//Fungsi untuk login dengan akun yang telah terdaftar
void login(){
	system("CLS");
	int opt, i, selected;
	int line = 0;
	char ch;
	char id[16];
	char password[16];
	FILE *listAcc;
	listAcc = fopen("account.txt", "r");
	countLines(&line, listAcc);
	rewind(listAcc);
	struct akun acc[maxAcc];
	for(i = 0; i < line; i++){
		fscanf(listAcc, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%ld,%d", acc[i].id, acc[i].password, acc[i].tipe, acc[i].nama, &acc[i].saldo, &acc[i].key);
	}
	fclose(listAcc);
	title();
	printf("==========================================\n");
	printf("  ======================================\n");
	printf("    |||                            |||\n");
	printf("    |||        1. Log in           |||\n");
	printf("    |||        2. Buat Akun        |||\n");
	printf("    |||                            |||\n");
	printf("  ======================================\n");
	printf("==========================================\n\n");
	printf("Pilihan anda: "); scanf("%d", &opt);
	if(opt == 1){
		system("CLS");
		do{
			printf("====================\n");
			printf("        LOGIN       \n");
			printf("====================\n\n");
			printf("ID: "); scanf(" %[^\n]s", id);
			printf("Password: ");
			for(i = 0; i < 16; i++){
				ch = getch();
				if(ch == 13){
					break;
				}else if(ch == 8){
					password[i-1] = '\0';
					printf("\b \b");
					i-= 2;
				}else{
					password[i] = ch;
					ch = '*';
					printf("%c", ch);
				}		
			}
			for(i = 0; i < line; i++){
				if(strcmp(id, acc[i].id) == 0){
					//Mendecrypt password 
					for(int j = 0; j < strlen(acc[i].password); j++){
						acc[i].password[j] -= acc[i].key;
					}
				}
				if(strcmp(id, acc[i].id) == 0 && strcmp(password, acc[i].password) == 0){
					printf("\nLogin berhasil\n");
					selected = i;
					if(strcmp(acc[i].tipe, "Restoran") == 0 && access("menu.txt", F_OK) != 0){
						createResto(selected, acc);
					}
					mainMenu(selected);	
				}
			}if(i == line){
				printf("\nID atau Passowrd salah!\n");
			}		
		}while(strcmp(id, acc[i].id) != 0 && strcmp(password, acc[i].password) != 0);	
	}else if(opt == 2){
		system("CLS");
		createAcc();
	}else{
		system("CLS");
		printf("ERROR: Hanya masukkan 1 atau 2!\n");
		login();
	}
}

//Function tampilan main menu
void mainMenu(int selected){
	system("CLS");
	title();
	int opt;
	int line = 0;
	int sen = 0;
	struct akun acc[maxAcc];
	FILE *akun = fopen("account.txt", "r");
	countLines(&line, akun);
	rewind(akun);
	for(int i = 0; i < line; i++){
		fscanf(akun, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%ld,%d", acc[i].id, acc[i].password, acc[i].tipe, acc[i].nama, &acc[i].saldo, &acc[i].key);
	}
	fclose(akun);
	printf("Nama: %s\n", acc[selected].nama);
	printf("Tipe Akun: %s\n", acc[selected].tipe);
	printf("Saldo: Rp %ld\n", acc[selected].saldo);
	//Main Menu Pembeli 
	if(strcmp(acc[selected].tipe, "Pembeli") == 0){
		mainPembeli();
		do{
			printf("Pilihan anda: "); scanf("%d", &opt);
			if(opt == 1){
				system("CLS");
				printf("=====================\n");
			    printf("    ORDER MAKANAN    \n");
			    printf("=====================\n\n");
				menuPembeli(acc, selected);
				mainMenu(selected);
			}
			else if(opt == 2){
				topUp(acc, selected);
				
			}else if(opt == 3){
				statusOrder(acc, selected);
				mainMenu(selected);
			}
			else if(opt == 4)
				login();
			else if(opt == 5)
				end();
			else
				printf("Hanya masukkan pilihan 1 sampai 4 saja!\n");
		} while(opt < 1 || opt > 4);
	}
	
	//Main menu Restoran
	if(strcmp(acc[selected].tipe, "Restoran") == 0){
		mainResto();
		do{
			printf("Pilihan anda: "); scanf("%d", &opt);
			if(opt == 1){
				system("CLS");
				printf("=====================\n");
			    printf("     DAFTAR MENU     \n");
			    printf("=====================\n\n");
			    do{
			    	displayMenu(selected, acc);
			    	printf("\nTekan 1 untuk kembali ke main menu: "); scanf("%d", &sen);
				}while(sen != 1);
				mainMenu(selected);
			}
			else if(opt == 2){
				system("CLS");
				printf("=====================\n");
			    printf("     UPDATE MENU     \n");
			    printf("=====================\n\n");
				updateMenu(selected, acc);
				mainMenu(selected);
			}
			else if(opt == 3){
			    system("CLS");
				printf("=====================\n");
			    printf("     TAMBAH MENU     \n");
			    printf("=====================\n\n");
				addMenu(selected, acc);
				mainMenu(selected);
			}
			else if(opt ==4){
			    system("CLS");
				printf("=======================\n");
			    printf("     DAFTAR PESANAN    \n");
			    printf("=======================\n\n");
				queueResto(acc, selected);
				mainMenu(selected);
			}
			else if(opt == 5)
				login();
			else if(opt == 6)
				end();
			else
				printf("Hanya masukkan pilihan 1 sampai 6 saja!\n");
		} while(opt < 1 || opt > 6);
	}
	
	//User login sebagai kurir
	if(strcmp(acc[selected].tipe, "Kurir") == 0){
		mainKurir();
		do{
			printf("Pilihan anda: "); 
			scanf("%d", &opt);
			if(opt == 1){
				system("CLS");
				printf("=====================\n");
			    printf("     TERIMA ORDER    \n");
			    printf("=====================\n\n");
				orderKurir(acc, selected);
				mainMenu(selected);
			}
			else if(opt == 2)
				login();
			else if(opt == 3)
				end();
			else
				printf("Hanya masukkan pilihan 1 sampai 3!\n");
		} while(opt < 1 || opt > 3);
	}
}

//Function untuk melihat status pesanan
void statusOrder(struct akun acc[maxAcc], int selected){
	struct basket basket;
	FILE *order = fopen("basket.txt", "r");
	int i = 0, j = 1;
	int line = 0;
	int total = 0;
	int status, opt;
	countLines(&line, order);
	if(line == 0){
		printf("Tidak terdapat pesanan!\n\n");
		printf("1. Kembali ke main menu\n");
		printf("2. Keluar program\n");
		do{
			printf("Pilihan anda: "); scanf("%d", &opt);
			if(opt == 1){
				mainMenu(selected);
			}else if(opt == 2){
				end();
			}else{
				printf("Pilih 1 atau 2!\n");
			}
		}while(opt != 1 && opt != 2);
	}
	rewind(order);
	char resto[30];
	char kurir[30];
	char pembeli[30];
	printf("Nama: %s\n", acc[selected].nama);
	printf("Status Pesanan\n");
	printf("====================================\n");
	for(i = 0; i < line; i++){
		fscanf(order, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d,%d,%d", basket.nama, basket.resto, basket.makanan, basket.statusResto, basket.statusKurir, basket.kurir, &basket.harga, &basket.kode, &basket.ongkir);
		if(strcmp(acc[selected].nama, basket.nama) == 0){
			if(j == 1){
				printf("Nama: %s\n", basket.nama);
				printf("Restoran: %s\n", basket.resto);
				printf("Kurir: %s\n", basket.kurir);
				printf("Daftar Pesanan:\n");
				strcpy(kurir, basket.kurir);
				strcpy(resto, basket.resto);
				strcpy(pembeli, basket.nama);
			}
			total += basket.harga;
			printf("%-3s%d. %s (Rp %d)\n"," ", j, basket.makanan, basket.harga);
			j++;
			if(strcmp(basket.statusResto, "Diterima") == 0 && strcmp(basket.statusKurir, "Diterima") == 0){
				status = 0;
			}else if(strcmp(basket.statusResto, "Belum Diterima") == 0){
				status = 1;
			}else if(strcmp(basket.statusKurir, "Belum Diterima") == 0){
				status = 1;
			}
		}
	}
	fclose(order);
	printf("\nTotal pesanan: Rp %d\n", total);
	printf("Ongkos kirim: Rp 10000\n");
	printf("Total keseluruhan: Rp %d\n", total+10000);
	if(status == 0){
		printf("\nKurir sedang mengantar pesanan..\n");
		for(int j = 0; j < 2090000000; j++);
		printf("\nKurir telah sampai!\n");
		printf("Pesanan sudah diterima? (Tekan 1 jika sudah menerima pesanan)\n");
		printf("Pilihan anda: "); scanf("%d", &opt);
		if(opt == 1){
			transferSaldo(pembeli, kurir, resto, total);
			deleteBasket(pembeli, kurir, resto);
			printf("Basket didelete\n");
		}
	}else if(status == 1){
		do{
			printf("\nRestoran sedang menyiapkan pesanan...\n");
			printf("\nKembali ke main menu? (Masukkan 1 untuk kembali ke main menu)\n");
			printf("Pilihan anda: "); scanf("%d", &opt);
			if(opt == 1){
				mainMenu(selected);
			}
		}while(opt != 1);
			
	}
	printf("====================================\n");
}

//Function untuk menghapus pesanan yang sudah selesai pada file txt
void deleteBasket(char pembeli[30], char kurir[30], char resto[30]){
	struct basket basket;
	int line = 0;
	FILE *order = fopen("basket.txt", "r");
	FILE *temp1 = fopen("temp1.txt", "w");
	countLines(&line, order);
	rewind(order);
	for(int i = 0; i < line; i++){
		fscanf(order, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d,%d,%d", basket.nama, basket.resto, basket.makanan, basket.statusResto, basket.statusKurir, basket.kurir, &basket.harga, &basket.kode, &basket.ongkir);
		if(strcmp(pembeli, basket.nama) == 0 && strcmp(kurir, basket.kurir) == 0 && strcmp(resto, basket.resto) == 0){
			continue;
		}else{
			fprintf(temp1, "%s,%s,%s,%s,%s,%s,%d,%d,%d\n", basket.nama, basket.resto, basket.makanan, basket.statusResto, basket.statusKurir, basket.kurir, basket.harga, basket.kode, basket.ongkir);
		}
	}
	fclose(temp1);
	fclose(order);
	remove("basket.txt");
	rename("temp1.txt", "basket.txt");
	remove("temp1.txt");
}

//Function untuk memindahkan saldo dari akun pembeli ke restoran dan kurir
void transferSaldo(char pembeli[30], char kurir[30], char resto[30], int total){
	FILE *akun = fopen("account.txt", "r");
	FILE *temp = fopen("temp.txt", "w");
	int line = 0;
	printf("Pembeli: %s\nResto: %s\nKurir: %s\n", pembeli, resto, kurir);
	countLines(&line, akun);
	struct akun acc[line];
	rewind(akun);
	for(int i = 0; i < line; i++){
		fscanf(akun, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%ld,%d", acc[i].id, acc[i].password, acc[i].tipe, acc[i].nama, &acc[i].saldo, &acc[i].key);
		printf("Nama: %s\n", acc[i].nama);
		if(strcmp(acc[i].nama, pembeli) == 0){
			acc[i].saldo -= total;
		}else if(strcmp(acc[i].nama, resto) == 0){
			acc[i].saldo += total;
		}else if(strcmp(acc[i].nama, kurir) == 0){
			acc[i].saldo += 10000;
		}
		fprintf(temp, "%s,%s,%s,%s,%d,%d\n", acc[i].id, acc[i].password, acc[i].tipe, acc[i].nama, acc[i].saldo, acc[i].key);
	}
	fclose(temp);
	fclose(akun);
	remove("account.txt");
	rename("temp.txt", "account.txt");
}

//Function untuk menghitung jumlah restoran yang terdaftar
void countResto(struct akun acc[maxAcc], int *menu, int line){
	int i;
	for(i = 0; i < line; i++){
		if(strcmp(acc[i].tipe, "Restoran") == 0){
			*menu++;
		}
	}
}

//Function untuk menampilkan menu yang disediakan restoran
void displayMenu(int selected, struct akun acc[maxAcc]){
	int i;
	int line = 0;
	FILE *listMenu = fopen("menu.txt", "r");
	countLines(&line, listMenu);
	struct menu menu[line];
	rewind(listMenu);
	readMenu(listMenu, menu, line);
	fclose(listMenu);
	printf("============================================================================\n");
	printf("|ID | Menu                                             | Harga            ||\n");
	printf("============================================================================\n");
	for(i = 0; i < line; i++){
		if(strcmp(acc[selected].nama, menu[i].nama) == 0){
			printf("|%-3d| %-49s| Rp %-14ld||\n", menu[i].kode, menu[i].makanan, menu[i].harga);
		}
	}
	printf("============================================================================\n");
}

//Function untuk menambahkan menu pada restoran
void addMenu(int selected, struct akun acc[maxAcc]){
	int jumlah, i;
	int line = 0;
	struct menu menu[maxMenu];
	displayMenu(selected, acc);
	FILE *listMakanan = fopen("menu.txt", "r");
	countLines(&line, listMakanan);
	rewind(listMakanan); 
	readMenu(listMakanan, menu, line);
	fclose(listMakanan);
	listMakanan = fopen("menu.txt", "a");
	printf("Menu yang ingin ditambahkan: \n");
	printf("Nama Makanan/Minuman: "); scanf(" %[^\n]%*c", menu[line+1].makanan);
	printf("Harga: "); scanf("%d", &menu[line+1].harga);
	fprintf(listMakanan, "%s,%s,%ld,%d\n", acc[selected].nama, menu[line+1].makanan, menu[line+1].harga, line+1);
	fclose(listMakanan);
}

//Function untuk membaca menu yang terdafatar pada menu.txt
void readMenu(FILE *listMenu, struct menu menu[maxMenu], int line){
	int i;
	#pragma omp parallel for ordered shared(i)
	for(i = 0; i < line; i++){
		#pragma omp ordered
		fscanf(listMenu, " %[^,]%*c%[^,]%*c%ld,%d", menu[i].nama, menu[i].makanan, &menu[i].harga, &menu[i].kode);
	}	
}

//Function untuk mengubah nama atau harga pada menu yang telah terdaftar
void updateMenu(int selected, struct akun acc[maxAcc]){
	int opt1, opt2, i;
	int line = 0;
	displayMenu(selected, acc);
	FILE *listMenu = fopen("menu.txt", "r");
	FILE *tempData = fopen("temp.txt", "w");
	countLines(&line, listMenu);
	rewind(listMenu);
	struct menu menu[line];
	readMenu(listMenu, menu, line);
	fclose(listMenu);
	printf("\nMenu yang ingin diupdate: "); scanf("%d", &opt1);
	system("CLS");	
	#pragma omp parallel for ordered shared(i)
	for(i = 0; i < line; i++){
		if(opt1 == menu[i].kode){
			printf("Nama Makanan: %s\n", menu[i].makanan);
			printf("Harga: %ld\n\n", menu[i].harga);
			do{
				printf("Bagian yang ingin diupdate:\n"); 
				printf("1.Nama\n2.Harga\n");
				printf("Pilihan anda: "); scanf("%d", &opt2);
					if(opt2 == 1){
						printf("Nama yang baru: "); scanf(" %[^\n]%*c", menu[i].makanan);
						printf("Nama berhasil diganti!\n");
					}else if(opt2 == 2){
						printf("Harga yang baru: "); scanf("%ld", &menu[i].harga);
						printf("Harga berhasil diganti!\n");
					}
			} while(opt2 < 1 || opt2 > 2);
		}	
	}	
	#pragma omp critical
	for(i = 0; i < line; i++){
		fprintf(tempData, "%s,%s,%ld,%d\n", menu[i].nama, menu[i].makanan, menu[i].harga, menu[i].kode);
	}		
	fclose(tempData);
	remove("menu.txt");
	rename("temp.txt", "menu.txt");
	remove("temp.txt");	
}

//Function untuk menghitung jumlah line pada file txt
void countLines(int *line, FILE *list){  //Menghitung jumlah line dalam file txt
	int ch = 0;
	#pragma omp parallel
	{
		#pragma omp single
		while(!feof(list)){
			ch = fgetc(list);
			if(ch == '\n'){  //Ketika ditemukan enter, line increment
			    *line = *line + 1;
			  }
		}	
	}
	rewind(list);
}

//Function untuk menampilkan nama program
void title(){
	system("Color 0B");
	printf("\n              _ _           ___               _   _     \n");
	printf("    /\\  /\\___| | | ___     / __\\__   ___   __| | / \\  \n");
	printf("   / /_/ / _ \\ | |/ _ \\   / _\\/ _ \\ / _ \\ / _` |/  / \n");
	printf("  / __  /  __/ | | (_) | / / | (_) | (_) | (_| /\\_/      \n");
	printf("  \\/ /_/ \\___|_|_|\\___/  \\/   \\___/ \\___/ \\__,_\\/ \n");
    printf("\n\n");                                                                                 
}

//Function untuk menampilkan tampilan main menu akun restoran
void mainResto(){
	printf("\n==========================================\n");
	printf("  |||                                |||\n");
	printf("  |||        1. Daftar Menu          |||\n");
	printf("  |||        2. Update Menu          |||\n");
	printf("  |||        3. Tambah Menu          |||\n");
	printf("  |||        4. Daftar Pesanan       |||\n");
	printf("  |||        5. Ganti Akun           |||\n");
	printf("  |||        6. Keluar               |||\n");
	printf("  |||                                |||\n");
	printf("==========================================\n\n");
}

//Function untuk menampilkan tampilan main menu akun kurir
void mainKurir(){
	printf("\n==========================================\n");
	printf("  |||                                |||\n");
	printf("  |||        1. Terima Order         |||\n");
	printf("  |||        2. Ganti Akun           |||\n");
	printf("  |||        3. Keluar               |||\n");
	printf("  |||                                |||\n");
	printf("==========================================\n\n");
}

//Function untuk menampilkan tampilan main menu akun pembeli
void mainPembeli(){
	printf("\n==========================================\n");
	printf("  |||                                |||\n");
	printf("  |||        1. Order Makanan        |||\n");
	printf("  |||        2. Top-Up Saldo         |||\n");
	printf("  |||        3. Status Pesanan       |||\n");
	printf("  |||        4. Ganti Akun           |||\n");
	printf("  |||        5. Keluar               |||\n");
	printf("  |||                                |||\n");
	printf("==========================================\n\n");
}

//Function untuk memesan makanan pada akun pembeli
void menuPembeli(struct akun acc[maxAcc], int selected){
	int line = 0, j = 0;
	int line2 = 0;
	int i, opt, order, sen, opt1; 
	FILE *listAcc = fopen("account.txt", "r");
	countLines(&line2, listAcc);
	fclose(listAcc);
	FILE *listMenu = fopen("menu.txt", "r");
	countLines(&line, listMenu);
	rewind(listMenu);
	struct menu menu[line];
	FILE *listBasket;
	int total = 0;
	if(access("basket.txt", F_OK) == 0){
		listBasket = fopen("basket.txt", "a");
	}else{
		listBasket = fopen("basket.txt", "w");
	}
	struct basket basket[maxBasket];
	for(i = 0; i < line; i++){
		fscanf(listMenu, " %[^,]%*c%[^,]%*c%ld,%d", menu[i].nama, menu[i].makanan, &menu[i].harga, &menu[i].kode);
	}
	printf("=====================================\n");
	printf("||No | Restoran                    ||\n");
	printf("=====================================\n");
	#pragma omp parallel for ordered shared(i)
	for(i = 0; i < line2; i++){
		#pragma omp ordered
		if(strcmp(acc[i].tipe, "Restoran") == 0){
			printf("||%-3d| %-28s||\n", i+1, acc[i].nama);
		}	
	}
	printf("=====================================\n");
	printf("Pilihan anda: "); scanf("%d", &opt);
	system("CLS");
	do{
		system("CLS");
		printf("Restoran: %s\n", acc[opt-1].nama);
		printf("============================================================\n");
		printf("|| ID |           Makanan/Minuman          |     Harga    ||\n");
		printf("============================================================\n");
		#pragma omp parallel for ordered shared(i)
		for(i = 0; i <line; i++){	
			#pragma omp ordered
			if(strcmp(acc[opt-1].nama, menu[i].nama) == 0){
				printf("|| %-2d | %-35s| Rp %-10d||\n", menu[i].kode, menu[i].makanan, menu[i].harga);
			}
		}
		printf("============================================================\n");
		do{
			printf("Masukkan ID makanan yang ingin dipesan: "); scanf("%d", &order);
			if(acc[selected].saldo - menu[order-1].harga < 10000){
				printf("\nSaldo anda tidak mencukupi!\n");
				printf("Silahkan isi saldo terlebih dahulu\n");
				printf("Tekan 1 untuk masuk ke halaman top up!\n");
				printf("Pilihan anda: "); scanf("%d", &opt1);
				if(opt1 == 1){
					topUp(acc, selected);
					mainMenu(selected);
				}
			}else{
				printf("Pesanan berhasil ditambahkan!\n");
				acc[selected].saldo -= menu[order-1].harga;
			}
		strcpy(basket[j].resto, menu[order-1].nama);
		strcpy(basket[j].makanan, menu[order-1].makanan);
		basket[j].harga = menu[order-1].harga;
		basket[j].kode = menu[order-1].kode;
		fprintf(listBasket, "%s,%s,%s,Belum Diterima,Belum Diterima,Belum Ditemukan,%d,%d,10000\n", acc[selected].nama, basket[j].resto, basket[j].makanan, basket[j].harga, basket[j].kode);
		j++;
		printf("Ingin tambah pesanan?\nTekan 1 untuk tambah pesanan!\n"); 
		printf("Pilihan anda: "); scanf("%d", &sen);
		}while(acc[selected].saldo - menu[order-1].harga > 10000 && sen == 1);	
		if(sen != 1){
			system("CLS");
			title();
			printf("\nTotal Pesanan: \n");
			printf("=====================================\n");
			for(i = 0; i < j; i++){
				printf("%d. %s (Rp %d)\n", i+1, basket[i].makanan, basket[i].harga);
				total += basket[i].harga;
			}
			printf("=====================================\n");
			printf("\nTotal harga makanan: Rp %d\n", total);
			printf("Ongkos kirim: Rp 10000\n");
			printf("Total Harga: Rp %d\n", total+10000);
			printf("=====================================\n\n");
			printf("1. Pesan makanan\n");
			printf("2. Batalkan pemesanan\n");
			printf("Pilihan anda: "); scanf("%d", &opt);
			if(opt == 1){
				fclose(listBasket);
			}else if(opt == 2){
				continue;
			}
		}
	}while(sen == 1);
	fclose(listMenu);
	if(sen != 1){
		mainMenu(selected);
	}
}

//Function untuk menghapus seluruh node pada linked list
void freeBasket(struct basket **head){
	struct basket* current = *head;
	struct basket* next;
	
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

//Function untuk menghapus node paling awal
void deleteHead(struct basket **head){ 
	struct basket *temp = *head;
	*head = temp->next; //node head dipindahkan ke node kedua
	free(temp);  //node temp yang merupakan node head dihapus
}

//Function untuk menampilkan antrian pesanan pada akun restoran
void queueResto(struct akun acc[], int selected){
	FILE *listOrder = fopen("basket.txt", "r");
	int line = 0;
	char makanan[50];
	char nama[30];
	char resto[30];
	char statusResto[15];
	char statusKurir[15];
	char kurir[30];
	struct basket *head = NULL;
	int harga, kode, i, ongkir, opt;
	FILE *temp = fopen("temp.txt", "w");
	fclose(temp);
	temp = fopen("temp.txt", "a");
	countLines(&line, listOrder);
	rewind(listOrder);
	printf("List Order\n");
	printf("Restoran: %s\n", acc[selected].nama);
	for(i = 0; i < line; i++){
		fscanf(listOrder, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d,%d,%d", nama, resto, makanan, statusResto, statusKurir, kurir, &harga, &kode, &ongkir);
		if(strcmp(resto, acc[selected].nama) == 0 && strcmp(statusResto, "Diterima") != 0){
			line = line - i;
			i = 0;
			if(i == 0){
				linkStart(&head, nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
			}else{
				linkTail(&head, nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
			}								
		} else{
			fprintf(temp, "%s,%s,%s,%s,%s,%s,%d,%d,%d\n", nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
		}
	}	
	printf("\nLINKED LIST:\n");
	FILE *temp1 = fopen("temp1.txt", "w");
	while(head != NULL){
		printBasket(head);	
		printf("Proses pesanan?(Tekan 1 untuk proses pesanan)\n");
		printf("Pilihan anda: "); scanf("%d", &opt);
		if(opt == 1){
			fprintf(temp1, "%s,%s,%s,Diterima,%s,%s,%d,%d,%d\n", head->nama, head->resto, head->makanan, head->statusKurir, head->kurir, head->harga, head->kode, head->ongkir);
			deleteHead(&head);
		}	
	}
	fclose(temp);
	temp = fopen("temp.txt", "r");
	fclose(temp1);
	fopen("temp1.txt", "a");
	line = 0;
	countLines(&line, temp);
	rewind(temp);
	for(i = 0; i < line; i++){
		fscanf(temp, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d,%d,%d", nama, resto, makanan, statusResto, statusKurir, kurir, &harga, &kode, &ongkir);
		fprintf(temp1, "%s,%s,%s,%s,%s,%s,%d,%d,%d\n", nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
	}
	fclose(temp1);
	fclose(temp);
	fclose(listOrder);
	remove("basket.txt");
	remove("temp.txt");
	rename("temp1.txt", "basket.txt");
}

//Function untuk menampilkan list pesanan 
void printBasket(struct basket *queue){
	if(queue == NULL){
		printf("Tidak terdapat pesanan\n");
	}else{
		printf("============================================================\n");
		printf("|Nama                  | Pesanan                           |\n");
		printf("============================================================\n");
		while(queue != NULL){
			printf("|%-22s| %-34s|\n", queue->nama, queue->makanan);
			queue = queue->next;
		}
		printf("============================================================\n");
	}
}

//Function untuk menciptakan node pertama pada linked list
void linkStart(struct basket **head, char nama[30], char resto[30], char makanan[50], char statusResto[15],
char statusKurir[15], char kurir[30], int harga, int kode, int ongkir){
	struct basket *basket = malloc(sizeof(struct basket));
	strcpy(basket->nama, nama);
	strcpy(basket->resto, resto);
	strcpy(basket->makanan, makanan);
	strcpy(basket->statusResto, statusResto);
	strcpy(basket->statusKurir, statusKurir);
	strcpy(basket->kurir, kurir);
	basket->harga = harga;
	basket->kode = kode;
	basket->ongkir = ongkir;
	basket->next = *head;
	*head = basket;
}

//Function untuk menambahkan node linked list di akhir
void linkTail(struct basket **head, char nama[30], char resto[30], char makanan[50], char statusResto[15],
char statusKurir[15], char kurir[30], int harga, int kode, int ongkir){
	struct basket *basket = malloc(sizeof(struct basket));
	struct basket *last = *head;
	strcpy(basket->nama, nama);
	strcpy(basket->resto, resto);
	strcpy(basket->makanan, makanan);
	strcpy(basket->statusResto, statusResto);
	strcpy(basket->statusKurir, statusKurir);
	strcpy(basket->kurir, kurir);
	basket->harga = harga;
	basket->kode = kode;
	basket->ongkir = ongkir;
	basket->next = NULL;
	if(*head == NULL){
		*head = basket;
	}
	while(last->next != NULL){
		last = last->next;
	}
	last->next = basket;
}

//Function untuk menampilkan pesanan yang akan diterima oleh kurir
void orderKurir(struct akun acc[maxAcc], int selected){
	FILE *listOrder = fopen("basket.txt", "r");
	int line = 0;
	char makanan[50];
	char nama[30];
	char resto[30];
	char statusResto[15];
	char statusKurir[15];
	char firstNama[30];
	char kurir[30];
	struct basket *head = NULL;
	int no = 1;
	int harga, kode, ongkir, i, opt, opt2;
	countLines(&line, listOrder);
	rewind(listOrder);
	FILE *temp1 = fopen("temp1.txt", "w");
	FILE *temp = fopen("temp.txt", "w");
	fclose(temp);
	printf("Anda akan menerima order:\n");
	printf("==================================\n");
	for(i = 0; i < line; i++){
		fscanf(listOrder, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d,%d,%d", nama, resto, makanan, statusResto, statusKurir, kurir, &harga, &kode, &ongkir);
			if(i == 0){
				strcpy(firstNama, nama);
				printf("Nama Penerima: %s\n", firstNama);
				printf("Nama Restoran: %s\n", resto);
				printf("Ongkos kirim: Rp %d\n", ongkir);
				printf("Daftar Pesanan:\n\n");
				linkStart(&head, nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
			}else{
				if(strcmp(nama, firstNama) == 0){
					linkTail(&head, nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
				}else{
					fprintf(temp1, "%s,%s,%s,%s,%s,%s,%d,%d,%d\n", nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
				}		
			}
	}
	fclose(temp1);
	printOrder(head, acc, selected);
	printf("\nTerima pesanan? (Tekan 1 untuk terima pesanan)\n"); 
	printf("Pilihan anda: "); scanf("%d", &opt);	
	if(opt == 1){
		FILE *temp = fopen("temp.txt", "a");
		FILE *temp1 = fopen("temp1.txt", "r");
		line = 0;
		countLines(&line, temp1);
		rewind(temp1);
		#pragma omp parallel
		{
			#pragma omp single
			#pragma omp task
			{				
				for(i = 0; i < line; i++){
					fscanf(temp1, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d,%d,%d", nama, resto, makanan, statusResto, statusKurir, kurir, &harga, &kode, &ongkir);
					fprintf(temp, "%s,%s,%s,%s,%s,%s,%d,%d,%d\n", nama, resto, makanan, statusResto, statusKurir, kurir, harga, kode, ongkir);
				}
			}
			#pragma omp taskwait
			#pragma omp task
			{
				fclose(temp1);
				fclose(temp);	
			}
		}
	}
	fclose(listOrder);
	remove("temp1.txt");
	remove("basket.txt");
	rename("temp.txt", "basket.txt");
}

//Function untuk menampilkan seluruh pesanan yang masuk ke kurir
void printOrder(struct basket *basket, struct akun acc[maxAcc], int selected){
	FILE *temp = fopen("temp.txt", "a");
	struct basket *iterator = basket;
	int i = 1;
	while(iterator != NULL){
		fprintf(temp, "%s,%s,%s,%s,Diterima,%s,%d,%d,%d\n", iterator->nama, iterator->resto, iterator->makanan, iterator->statusResto, acc[selected].nama, iterator->harga, iterator->kode, iterator->ongkir);
		iterator = iterator->next;
	}
	while(basket != NULL){
		printf("%d. %s (Rp %d)\n", i, basket->makanan, basket->harga);
		basket = basket->next;
		i++;
	}
	fclose(temp);
}

//Function untuk menambahkan saldo pada akun pembeli
void topUp(struct akun acc[maxAcc], int selected){
	system("CLS");
	printf("===================\n");
 	printf("    TOPUP SALDO    \n");
	printf("===================\n\n");
	FILE *listAcc;
	int line = 0;
	int i;
	int saldo; 
	listAcc = fopen("account.txt", "r");
	countLines(&line, listAcc);
	rewind(listAcc);
	for(i = 0; i < line; i++){
		fscanf(listAcc, " %[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%ld,%d", acc[i].id, acc[i].password, acc[i].tipe, acc[i].nama, &acc[i].saldo, &acc[i].key);
	}
	fclose(listAcc);
	printf("Jumlah saldo yang ingin ditopup: "); 
	scanf("%ld", &saldo);
	acc[selected].saldo += saldo;
	printf("Top up saldo berhasil!\n"); 
	remove("account.txt");
	listAcc = fopen("account.txt", "w");
	for(i = 0; i < line; i++){
		fprintf(listAcc, "%s,%s,%s,%s,%ld,%d\n", acc[i].id, acc[i].password, acc[i].tipe, acc[i].nama, acc[i].saldo, acc[i].key);
	}
	fclose(listAcc);
	mainMenu(selected);
}

//Function untuk membuat akun baru
void createAcc(){
	struct akun acc;
	FILE *listAcc;
	int opt, i, sen;
	int line = 0;
	char ch;
	if(access("account.txt", F_OK) == 0){
	    printf("====================\n");
	    printf("      BUAT AKUN     \n");
	    printf("====================\n\n");
		printf("Tipe Akun: \n");
		printf("1. Pembeli\n2. Kurir\n3. Restoran\n");
		do{
			printf("Pilihan anda: "); scanf("%d", &opt);
			if(opt == 1){
				strcpy(acc.tipe, "Pembeli");
			}else if(opt == 2){
				strcpy(acc.tipe, "Kurir");
			}else if(opt == 3){
				strcpy(acc.tipe, "Restoran");
			}else{
				printf("\nHanya pilih 1, 2, atau 3!\n");
			}		
		} while(opt < 1 || opt > 3);
		listAcc = fopen("account.txt", "a");
		printf("\nMasukkan akun %s!\n", acc.tipe);
		printf("ID: "); scanf(" %[^\n]s", acc.id);
		printf("Password: "); 
		for(i = 0; i < 16; i++){
			ch = getch();
			if(ch == 13){
				break;
			}else if(ch == 8){
				acc.password[i-1] = '\0';
				printf("\b \b");
				i-= 2;
			}else{
				acc.password[i] = ch;
				ch = '*';
				printf("%c", ch);
			}		
		}
		printf("\nNama: "); scanf(" %[^\n]s", acc.nama);
		acc.key = (rand()%(5-1+1)+1); //Mendapatkan kunci encrypt random 1-5
		int len = strlen(acc.password);
		//Encrypt password
		for(i = 0; i < len; i++){
			acc.password[i] += acc.key;
		}
		fprintf(listAcc, "%s,%s,%s,%s,0,%d\n", acc.id, acc.password, acc.tipe, acc.nama, acc.key);
		fclose(listAcc);
		do{
			printf("\nMasukkan 1 untuk login!\n");
			printf("Pilihan Anda: "); scanf("%d", &sen);
			if(sen == 1)
				login();
		} while(sen != 1);	
	}else{
		listAcc = fopen("account.txt", "w");
		createAcc();
	}
}

//Function untuk menambahkan menu pertama pada restoran
void createResto(int selected, struct akun acc[]){
	int opt;
	FILE *listMakanan = fopen("menu.txt", "w+");
	struct menu menu;
	printf("\nRestoran berhasil ditambahkan!\nMasukkan menu pertama: \n");
	printf("Nama makanan: "); scanf(" %[^\n]%*c", menu.makanan);
	printf("Harga makanan: Rp "); scanf("%d", &menu.harga);
	fprintf(listMakanan, "%s,%s,%d,1", acc[selected].nama, menu.makanan, menu.harga);
	fclose(listMakanan);
	printf("Ingin menambahkan makanan?\n");
	printf("1. Iya\n2. Tidak\n");
	printf("Pilihan anda: "); scanf("%d", &opt);
	if(opt == 1){
		addMenu(selected, acc);
	}else{
		mainMenu(selected);
	}
}

//Function untuk menambahkan delay 
void delay(int s){
    int ms = 1000 * s;
    clock_t start = clock();
    while(clock() < start + ms);
}

//Function untuk mengakhiri program
void end(){
	system("CLS");
	printf("\n    TERIMA KASIH sudah menggunakan program ini!\n");
	exit(0);
}

//Function untuk menampilkan loading screen
void loading(){
	title();
	int i, j, a;
	system("Color 0B");
	printf("\n\n\n\t\tLoading....\n\n\t\t");
	for(i = 1; i <= 40; i++){
		for(j = 0; j <= 10000000; j++)
			a = j;
		printf("%c", 219);
	}
	delay(1);
}
