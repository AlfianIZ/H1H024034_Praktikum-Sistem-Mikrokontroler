## Pertanyaan dan Jawaban Modul 1
#### 1.5.4 Pertanyaan Praktikum:
1. Pada Kondisi apa program masuk ke blok if?
Jawab: Program masuk ke blok if ketika nilai variabel timeDelay kurang dari atau sama dengan 100.
2. Pada kondisi apa program masuk ke blok else?
Jawab: Program masuk ke blok else ketika nilai variabel timeDelay lebih besar dari 100.
3. Apa fungsi dari perintah delay(timeDelay)?
Jawab: Fungsi delay(timeDelay) adalah untuk memberikan jeda waktu pada program selama 1000 milidetik atau 1 detik. Dalam percobaan ini fungsi tersebut digunakan untuk mengatur durasi LED saat menyala dan mati, sehingga menghasilkan efek kedipan dengan kecepatan yang berubah-ubah.
4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan disetiap baris kode nya.
Jawab:
```cpp
const int ledPin = 6;
int timeDelay = 1000;

bool percepatan = true;
void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay(timeDelay);

    digitalWrite(ledPin, LOW);
    delay(timeDelay);
    
    if (percepatan) {
        if (timeDelay <= 100){
            percepatan = false;
        } else {
            timeDelay -= 100;
        }
    } else {
        if (timeDelay >= 1000) {
            percepatan = true;
        } else {
            timeDelay += 300;
        }
    }
}
```

1.6.4 Pertanyaan praktikum
1. Gambarkan rangkaian schematik 5 LED running yang digunakan pada percobaan!
Jawab: 
// gambar
2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
Jawab: Efek LED berjalan dari kiri ke kanan dihasilkan menggunakan struktur perulangan for dengan proses increment. Program dimulai dari pin terendah, kemudian secara bertahap berpindah ke pin yang lebih tinggi. Pada setiap iterasi: -LED dinyalakan dengan digitalWrite(HIGH) -Diberikan jeda menggunakan delay() -LED dimatikan kembali dengan digitalWrite(LOW) Proses ini menciptakan efek visual seolah-olah LED bergerak dari kiri ke kanan.
3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri!
Jawab: Efek ini merupakan kebalikan dari sebelumnya, yaitu menggunakan perulangan for dengan decrement. Program dimulai dari pin tertinggi, kemudian bergerak ke pin yang lebih rendah. Langkahnya tetap sama: -LED menyala -Delay -LED mati Sehingga menghasilkan efek LED berjalan dari kanan ke kiri.
4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian dan berikan penjelasan disetiap baris kode nya
Jawab:
```cpp
int timer = 1000;

void setup() {
    for (int ledPin = 2; ledPin < 8; ledPin++) {
        pinMode(ledPin, OUTPUT);
    }
}
void loop() {
    for (int ledPin = 2; ledPin <= 4; ledPin++) {
    	digitalWrite(ledPin, HIGH);
    }
    for (int ledPin = 5; ledPin <= 7; ledPin++){
        digitalWrite(ledPin, LOW);
    }
    delay(timer);
                 
    for (int ledPin = 5; ledPin <= 7; ledPin++){
        digitalWrite(ledPin, HIGH);
    }
    for (int ledPin = 2; ledPin <= 4; ledPin++) {
    	digitalWrite(ledPin, LOW);
    }
    delay(timer);
}