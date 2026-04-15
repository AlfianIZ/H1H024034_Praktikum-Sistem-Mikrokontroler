# Pertanyaan dan Jawaban Modul 2

## 2.5.4 Pertanyaan Praktikum
1. Gambarkan rangkaian schemaatic yang digunakan pada percobaan !

   Jawab:
    <img width="626" height="486" alt="Screenshot 2026-04-15 071423" src="https://github.com/user-attachments/assets/e14a0daa-7272-4aac-81f2-72ec8b06cdde" />


3. Apa yang terjadi jika nilai num lebih dari 15?

   Jawab: Akan terjadi error tampilan karena array `digitalPatern` hanya memiliki indeks dari 0-15. Jika lebih dari 15, maka program mengakses data di luar array.

4. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasannya!

   Jawab: Praogram menggunakan Common Anode, alasannya logika output dibalilk menggunakan `!digitalPattern[num][i]` karena Common Anode membaca logika 0 sebagai menyala dan logika 1 sebagai mati

5. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kodenya dalam bentuk README.md

    Jawab: 
    ```cpp
    #include <Arduino.h>

    //7-Segment Display (Efficient Version)
    //Display 0 - 9 and A - F

    // Pin mapping segment
    const int segmentPins[8] = {7, 6, 5, 11, 10, 8, 9, 4};
    // a b c d  e  f g dp

    // Segment pattern for 0-F
    // urutan segment: a b c d e f g dp
    byte digitPattern[16][8] = {
  
    {1,1,1,1,1,1,0,0},   //0
    {0,1,1,0,0,0,0,0},   //1
    {1,1,0,1,1,0,1,0},   //2
    {1,1,1,1,0,0,1,0},   //3
    {0,1,1,0,0,1,1,0},   //4
    {1,0,1,1,0,1,1,0},   //5
    {1,0,1,1,1,1,1,0},   //6
    {1,1,1,0,0,0,0,0},   //7
    {1,1,1,1,1,1,1,0},   //8
    {1,1,1,1,0,1,1,0},   //9
    {1,1,1,0,1,1,1,0},   //A
    {0,0,1,1,1,1,1,0},   //b
    {1,0,0,1,1,1,0,0},   //C
    {0,1,1,1,1,0,1,0},   //d
    {1,0,0,1,1,1,1,0},   //E
    {1,0,0,0,1,1,1,0}    //F
    };

    // Fungsi menampilkan digit
    void displayDigit(int num)
    {
        for(int i=0;i<8;i++)
        {
            digitalWrite(segmentPins[i], !digitPattern[num][i]); //logika dibalik
        }
    }

    void setup()
    {
        for(int i=0;i<8;i++)
        {
            pinMode(segmentPins[i], OUTPUT); //set pin sebagai output
        }
    }

    void loop()
    {
        for(int i=15;i>=0;i--)   //F sampai 0
        {
            displayDigit(i); //menampilkan digit
            delay(1000); //delay 1 detik
        }
    }
    ```

## 2.6.4 Pertanyaan Praktikum
1. Gambarkan rangkaian  schematic yang digunakan pada percobaan!
    
    Jawab: <img width="677" height="526" alt="Screenshot 2026-04-15 075542" src="https://github.com/user-attachments/assets/c56a1281-325b-4331-b8e3-057feb997999" />


2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno?
Apa keuntungannya dibandingkan rangkaian biasa?

    Jawab: Karena tidak perlu resistor tambahan (internal pull-up sudah tersedia). Keuntungannya adaalah input lebih stabil, rangkaian lebih sederhana.

3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?

    Jawab: 
    
    Hardware: 
    - LED segment rusak
    - Resistor rusak
    - Kabel tidak terhubung
    - Wiring salah

    Software: 
    - Pin tidak sesuai mapping
    - Kesalahan pada array `digitPattern`
    - PinMode belum diset output

4. Modifikasi  rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

    Jawab: 
    ```cpp
    #include <Arduino.h>

    // Pin segment
    const int segmentPins[8] = {7,6,5,11,10,8,9,4};

    // Tombol
    const int btnUp = 2;
    const int btnDown = 3;

    // Counter  
    int counter = 0;

    // State tombol
    bool lastUp = HIGH;
    bool lastDown = HIGH;

    // Pola digit
    byte digitPattern[16][8] = {
    {1,1,1,1,1,1,0,0},{0,1,1,0,0,0,0,0},{1,1,0,1,1,0,1,0},{1,1,1,1,0,0,1,0},
    {0,1,1,0,0,1,1,0},{1,0,1,1,0,1,1,0},{1,0,1,1,1,1,1,0},{1,1,1,0,0,0,0,0},
    {1,1,1,1,1,1,1,0},{1,1,1,1,0,1,1,0},{1,1,1,0,1,1,1,0},{0,0,1,1,1,1,1,0},
    {1,0,0,1,1,1,0,0},{0,1,1,1,1,0,1,0},{1,0,0,1,1,1,1,0},{1,0,0,0,1,1,1,0}
    };

    // Fungsi tampil digit
    void displayDigit(int num){
        for(int i=0;i<8;i++){
            digitalWrite(segmentPins[i], !digitPattern[num][i]);
        }
    }

    void setup(){
        for(int i=0;i<8;i++){
            pinMode(segmentPins[i], OUTPUT); // set pin segment
        }

        pinMode(btnUp, INPUT_PULLUP);   // tombol naik
        pinMode(btnDown, INPUT_PULLUP); // tombol turun

        displayDigit(counter); // tampil awal
    }

    void loop(){
        bool upState = digitalRead(btnUp);
        bool downState = digitalRead(btnDown);

        // tombol naik
        if(lastUp == HIGH && upState == LOW){
            counter++;
            if(counter > 15) counter = 0;
            displayDigit(counter);
            delay(200);
        }

        // tombol turun
        if(lastDown == HIGH && downState == LOW){
            counter--;
            if(counter < 0) counter = 15;
            displayDigit(counter);
            delay(200);
        }

        lastUp = upState;
        lastDown = downState;
    }
    ```

## 2.7 Pertanyaan Praktikum

1. Uraikan hasil tugas pada praktikum yang telah dilakukan pada setiap percobaan!

    Jawab:
    * Percobaan 1: Seven segment berhasil menampilkan angka 0–F secara otomatis
    * Percobaan 2: Counter berhasil dikontrol menggunakan push button

2. Bagaimana prinsip kerja dari Seven Segment Display dalam menampilkan angka dan karakter?

    Jawab: Seven segment bekerja dengan menyalakan kombinasi LED (a–g) untuk membentuk angka/karakter tertentu sesuai pola yang ditentukan.

3. Jelaskan bagaimana sistem counter bekerja pada program tersebut!

    Jawab: 
    * Mendeteksi perubahan tombol (HIGH → LOW)
* Menambah atau mengurangi nilai variabel `counter`
* Menampilkan nilai tersebut ke seven segment menggunakan fungsi `displayDigit()`
