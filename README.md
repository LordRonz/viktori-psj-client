# Viktori PSJ Client

## Kelompok

- Aaron Christopher 07211940000055
- I Putu Haris Setiadi 07211940000046
- I Gusti Agung Hari 07211940000073

***Hanya bisa di run di UNIX System, windows gabisa***
> Bisa tapi ribet nanti

## Fitur

- Komunikasi dengan server menggunakan TCP Socket
- Membaca serial port dengan konfigurasinya
- Membaca serial port menggunakan delimiter untuk mencegah pergeseran input
- Implementasi command `tail` untuk mendapatkan `n` baris terakhir pada txt
- Menggunakan signal handler untuk mematikan server, dan membersihkan semua resources yang ada.

## Yang perlu diinstall supaya bisa ngerun

- gcc (Pasti ada sih klo install linux)
- make (untuk build)
- cmake (untuk memudahkan build)
- vscode (*opsional, ada ekstensi yang memudahkan ngebuild binarynya)

> make sama cmake itu opsional **KALAU** bisa compile manual pake gcc dan segala flagsnya

## Cara ngerun

### Compile cara pertama

Pindah ke direktori dimana `CMakeLists.txt` berada, trus

```sh
cmake --build ./build
```

### Compile cara kedua

Eksekusi command build.sh

```sh
./build.sh
```

Atau

```sh
bash build.sh
```

### Ngerun

Ini gapake argument sih, buat output cara pemakaian aja

```sh
./build/Client
```

Argumen pertama adalah IP server, lalu argumen kedua adalah Port server

```sh
./build/Client 192.168.1.5 6969
```

Ini untuk mengaktifkan mode tail, server akan mengirim 5 baris terakhir dari txt

```sh
./build/Client 192.168.1.5 6969 tail
```

Ini untuk mengaktifkan mode tail, dan menentukan berapa baris yang akan dikirim server, misal disini 9 baris

```sh
./build/Client 192.168.1.5 6969 tail 9
```
