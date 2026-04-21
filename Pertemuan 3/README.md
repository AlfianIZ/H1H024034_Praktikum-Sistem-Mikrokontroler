# Praktikum Sistem Mikrokontroler - Modul 3: Protokol Komunikasi

### 3.5.4 Pertanyaan Praktikum Percobaan 3A: Komunikas Serial (UART)
1. Jelaskan proses dari input keyboard hingga LED menyala/mati!

    Jawab: Saat user memasukkan karakter pada serial monitor lalu menekan enter, data tersebut dikirim ke buffer UART pada Arduino. Setelah itu data di dalam buffer akan diperiksa oleh fungsi Serial.available(). Jika data tersedia, maka data tersebut akan dibaca oleh fungsi Serial.read() dan disimpan dalam variabel input. Kemudian, data tersebut akan dibandingkan dengan karakter '1' atau '0'. Jika data sama dengan '1', maka LED akan menyala. Jika data sama dengan '0', maka LED akan mati.

2. Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?

    Jawab: Fungsi Serial.available() digunakan untuk memeriksa apakah ada data yang tersedia di buffer UART. Jika baris tersebut dihilangkan, maka fungsi Serial.read() akan tetap dijalankan pada setiap perulangan loop() walaupun sebenarnya tidak ada data yang tersedia. Dalam kondisi buffer kosong, Serial.read() akan menghasilkan nilai -1, yang setelah dikonversi ke tipe char menjadi karakter yang tidak valid. Akibatnya, program terus memproses karakter tersebut sebagai input, sehingga kondisi else if (data != '\n' && data != '\r') akan terus bernilai benar. Hal ini menyebabkan Serial Monitor menampilkan pesan "Perintah tidak dikenal" secara berulang-ulang tanpa henti.

3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi
jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan dan
berikan penjelasan disetiap baris kode nya dalam bentuk README.md

    Jawab:
    ```cpp
    #include <Arduino.h>

    const int PIN_LED = 12;     // Menentukan pin LED
    bool modeBlink = false;     // Status mode blink

    void setup() {
    Serial.begin(9600);       // Memulai komunikasi serial
    pinMode(PIN_LED, OUTPUT); // Set pin LED sebagai output
    }

    void loop() {

        if (Serial.available() > 0) {  // Cek apakah ada data masuk
            char data = Serial.read();   // Baca data dari serial

            if (data == '1') {           
                modeBlink = false;         
                digitalWrite(PIN_LED, HIGH); // LED menyala
            }
            else if (data == '0') {      
                modeBlink = false;         
                digitalWrite(PIN_LED, LOW);  // LED mati
            }
            else if (data == '2') {      
                modeBlink = true;          // Aktifkan mode blink
            }
        }

        if (modeBlink) {               
            digitalWrite(PIN_LED, HIGH); 
            delay(500);                  
            digitalWrite(PIN_LED, LOW);  
            delay(500);                  
        }
    }
    ```
    Penjelasan:
    * `modeBlink` digunakan untuk menyimpan kondisi LED apakah berkedip atau tidak
    * Jika menerima '2', LED masuk mode berkedip terus menerus
    * ika menerima '1' atau '0', mode blink dimatikan
    * `delay(500)` mengatur kecepatan kedipan LED

4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap
sistem

    Jawab: `delay()` digunakan karena program ini tidak memerlukan multitasking. `delay()` menyebabkan program berhenti sementara selama waktu yang ditentukan, sehingga program tidak dapat melakukan hal lain selama periode tersebut. Namun, karena program ini hanya melakukan satu tugas (mengontrol LED), `delay()` tidak menjadi masalah. Jika program ini memerlukan multitasking, maka `milis()` akan lebih cocok digunakan.

----------------------------------------------------------------------------------

### 3.6.4 Pertanyaan Praktikum Percobaa 3B: Inter-Integrated Circuit (I2C)
1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!

    Jawab: Komunikasi I2C bekerja menggunakan dua jalur utama, yaitu SDA sebagai saluran data dan SCL sebagai saluran clock. Pada rangkaian ini, Arduino berfungsi sebagai master, sedangkan modul I2C pada LCD yang menggunakan IC PCF8574 berperan sebagai slave dengan alamat 0x20.

    Saat proses pengiriman data berlangsung, Arduino terlebih dahulu membangkitkan kondisi START pada jalur SDA, kemudian mengirimkan alamat slave 7-bit beserta bit write. Setelah itu, data dikirimkan secara bertahap per byte dengan sinkronisasi dari sinyal clock pada jalur SCL. Data yang diterima oleh PCF8574 selanjutnya diubah dari bentuk komunikasi serial melalui dua kabel menjadi sinyal paralel 8-bit yang dapat diteruskan ke pengendali LCD HD44780. Dengan mekanisme tersebut, Arduino hanya perlu memanfaatkan dua pin, yaitu A4 dan A5, untuk mengontrol LCD yang secara fisik memiliki 16 pin.

2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar!

    Jawab: Jika kaki kiri dan kaki kanan potensiometer tertukar, maka nilai ADC yang terbaca akan terbalik. Artinya, saat potensiometer diputar ke satu arah, nilai ADC akan meningkat, sedangkan saat diputar ke arah sebaliknya, nilai ADC akan menurun. Hal ini disebabkan karena potensiometer berfungsi sebagai pembagi tegangan, dan posisi kaki kiri dan kanan menentukan arah pembagian tegangan.

3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:
- Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor
- Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut:
    
    
    |ADC: 0          |Volt:0.00V         |Persen: 0%     |
    |----------------|-------------------|---------------|

    Jawab:
    ```cpp
    #include <Wire.h>
    #include <LiquidCrystal_I2C.h>
    #include <Arduino.h>

    LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD
    const int pinPot = A0;              // Pin potensiometer

    void setup() {
        Serial.begin(9600);   // Memulai serial
        lcd.init();           // Inisialisasi LCD
        lcd.backlight();      // Menyalakan lampu LCD
    }

    void loop() {
        int nilai = analogRead(pinPot);     // Baca ADC
        float volt = nilai * (5.0 / 1023.0); // Konversi ke volt
        int persen = map(nilai, 0, 1023, 0, 100); // Konversi ke persen

        // Tampilkan ke Serial
        Serial.print("ADC: ");
        Serial.print(nilai);
        Serial.print(" Volt: ");
        Serial.print(volt);
        Serial.print(" V Persen: ");
        Serial.print(persen);
        Serial.println("%");

        // Tampilkan ke LCD
        lcd.setCursor(0, 0);
        lcd.print("ADC: ");
        lcd.print(nilai);
        lcd.print(" ");
        lcd.print(persen);
        lcd.print("%   ");

        lcd.setCursor(0, 1);
        int bar = map(nilai, 0, 1023, 0, 16);

        for (int i = 0; i < 16; i++) {
            if (i < bar) {
                lcd.print((char)255);
            } else {
                lcd.print(" ");
            }   
        }

        delay(200);
    }
    ```
    Penjelasan:
    - Data analog dibaca dari potensiometer
    - Nilai dikonversi menjadi volt dan persen
    - Output ditampilkan ke Serial Monitor dan LCD

4. Lengkapi tabel berikut berdasarkan pengamatan pada Serial Monitor

    Jawab:
    | ADC | Volt (V) | Persen (%) |
    | --- | -------- | ---------- |
    | 1   | 0.00     | 0%         |
    | 21  | 0.10     | 2%         |
    | 49  | 0.24     | 4%         |
    | 74  | 0.36     | 7%         |
    | 96  | 0.47     | 9%         |

