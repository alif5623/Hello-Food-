# Hello-Food-
Deksripsi program:

Hello Food! adalah program pemesanan makanan online yang dapat menguhubungkan transaksi antara 3 jenis akun yaitu pembeli, restoran, dan kurir melalui file handling
Pada akun ini terdapat 3 file txt, yaitu account.txt yang berfungsi untuk mencatat seluruh akun yang terdaftar, basket.txt yang berfungsi untuk mencatat pesanan yang berlangsung,
dan menu.txt yang berfungsi untuk mencatat seluruh menu yang didaftarkan oleh restoran.

Ketika program tidak menemukan akun yang terdaftar pada account.txt, program akan mengarahkan user untuk membuat akun baru pada fungsi createAcc. Jika program menemukan akun
pada account.txt maka program akan memberikan pilihan untuk user login atau membuat akun baru. Program akan menyimpan data akun ke account.txt, sebelum password disimpan ke
account.txt, password akan dienkripsi terlebih dahulu.

Ketiga tipe akun akan memiliki tampilan main menu yang berbeda karena masing-masing tipe akun memiliki fungsi yang berbeda. Akun pembeli dapat memesanan makanan dan mengisi saldo,
akun restoran dapat menambah ataupun mengubah daftar makanan yang terdaftar pada restoran tersebut. 
Akun pembeli dapat membeli makanan dari akun restoran yang terdaftar dan pesanan tersebut akan diteruskan ke restoran melalui sistem Queue dalam linked list.

Pesanan pertama akan menjadi head pada linked list dan pesanan berikutnya akan menjadi tail pada linked list. Dalam menyelesaikan pesanan, pesanan yang pertama masuk(head)
akan dieksekusi terlebih dahulu melalui function deleteHead. 
Pada saat yang sama, akun kurir juga dapat menerima pesanan. Akun kurir dapat menerima pesanan pembeli dan mengantarkannya.
Kondisi pesanan selesai adalah ketika kurir dan restoran telah memproses pesanan pembeli, setelah itu transaksi akan dilanjutkan dengan memindahkan saldo yang terdapat pada
pembeli ke akun restoran dan kurir. Saldo yang akan masuk ke akun restoran adalah total harga makanan yang dipesan, sedangkan saldo yang akan masuk pada saldo kurir adalah 
total ongkos kirim. Perpindahan saldo ini memanfaatkan sistem struct dan file handling di mana isi dari struct akan diubah terlebih dahulu, lalu struct yang telah diubah
akan kembali diprint ke file account.txt

Cara menggunakan program:
1. Menjalankan Hello_Food Final.exe
2. Jika akun belum ditemukan, program akan mengarahkan untuk membuat akun baru, ikuti instruksi pada program
3. Login dengan ID dan password akun yang sudah terdaftar
4. Jika login sebagai restoran, daftarkan makanan yang ingin didaftarkan pada aplikasi dengan memilih opsi tambah menu pada main menu
5. Jika login sebagai pembeli, pesan makanan melalui opsi Order makanan pada main menu
6. Jika login sebagai kurir, terima pesanan melalui opsi Terima Order pada main menu
7. Restoran dapat menerima pesanan melalui opsi daftar pesanan, jika pesanan sudah siap maka masukkan 1 untuk menghapus antrian
8. Ketika restoran dan kurir telah menerima pesanan, pembeli dapat melihat status pesanannya kembali pada opsi status pesanan di main menu
9. Ketika pesanan telah sampai, masukkan 1 untuk menyelesaikan pesanan
10. Transaksi selesai dan saldo akan ditransfer ke masing-masing akun yang terlibat dalam transaksi
