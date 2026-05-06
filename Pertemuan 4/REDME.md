# Praktikum Sistem Mikrokontroler - Modul 4: Analog to Digital Converter (ADC) dan Pulse Width Modulation (PWM)

## Pertanyaan Praktikum Percobaan 1: ADC
1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
    
    Jawab: Fungsi analogRead() adalah untuk membaca tegangan analog dari pin input analog. Fungsi in mengubah tegangan input analog dari 0V-5V menjadi nilai digital diskrit 0-1023 (10bit).

2. Mengapa diperlukan fungsi map() dalam program tersebut?

    Jawab: Fungsi map() digunkan kareana adanya perbedaan rentang antara input nilai ADC dan output yang dibutuhkan. Nilai ADC dari potensiometer memiliki rentang 0-1023, sedangkan motor servo dikendalikan dengan parameter sudut dengan rentang 0-180 derajat. fungsi map() melakukan pemetaan linear sehingga nilai input dari potensiometer dapat dikonversi ke rentang sudut servo. 

3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md

    Jawab:
    ```cpp
    #include <Servo.h> 

    Servo myservo; 
    
    const int potensioPin = A0;   
    const int servoPin = 9;      

    int pos = 0; 
    int val = 0; 

    void setup() {
        myservo.attach(servoPin); 

        Serial.begin(9600); 
    }

    void loop() {
        val = analogRead(potensioPin); 
        // Ubah nilai ADC menjadi sudut servo (30–150 derajat)
        pos = map(val,
            0,  
            1023,   
            30,   // diisi dengan sudut 30 derajat
            150);  // diisi dengan sudut 150 derajat

        myservo.write(pos); 

        Serial.print("ADC Potensio: ");
        Serial.print(val); 

        Serial.print(" | Sudut Servo: ");
        Serial.println(pos); 
        
        delay(50); 
    }
    ```

    Penjelasan: program tersebut membaca nilai analog dari potensiometer melalui pin A0. nilai 0-1023 kemudian diproses menggunakan fungsi map(val, 0, 1023, 30, 150). Ini akan membatasi niali variabel val agar tidak kurang dari 30 dan tidak lebih dari 150. Hasil pemetaan tersebut dikirim ke motor servo melalui perintah myservo.write(), sehingga pergerakan fisik servo terbatas pada rentang 30-150 derajat. 

## Pertanyaan Praktikum Percobaan 2: PWM
1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!

    Jawab: Karena fungsi analogWrite() menerapkan teknik PWM, yaitu memanipulasi rata-rata tegangan yang diterima LED dengan cara menghidupkan dan mematikan LED dengan frekuensi yang sangat cepat. Karena frekuensi yang sangat cepat, mata manusia tidak dapat melihat kedipan LED tersebut, melainkan persepsi perubahan intensitas cahaya berdasarkan lamanya durasi kondisi ON dan OFF.

2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?

    Jawab: Hubungan antara keduanya terletak pada  resolusi bit yang digunakan. ADC pada arduino memiliki resolusi 10bit (1024), sedangkan PWM memiliki resolusi 8bit (256). Keduanya memiliki perbandingan 4:1, untuk mengkonversi nilai ADC menjadi PWM secara langsung, nilai ADC harus dibagi dengan 4 atau menggunakan fungsi map(val, 0, 1023, 0, 255).

3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.

    Jawab:
    ```cpp
    #include <Arduino.h> 

    const int potPin = A0;   
    const int ledPin = 9;   

    int nilaiADC = 0; 
    int pwm = 0;       

    void setup() {
        pinMode(ledPin, OUTPUT);
        Serial.begin(9600); 
    }

    void loop() {
        nilaiADC = analogRead(potPin); 
        // Ubah nilai ADC (0–1023) menjadi nilai PWM (50–200)
        pwm = map(nilaiADC,
            0,   
            1023,   
            50,   // Diisi dengan nilai PWM minimum 50
            200);  // Diisi dengan nilai PWM maksimum 200

        analogWrite(ledPin, pwm); 

        Serial.print("ADC: ");
        Serial.print(nilaiADC);

        Serial.print(" | PWM: ");
        Serial.println(pwm); 

        delay(50); 
    }
    ```
    Penjelasan: Program tersebut membaca input analog dan mengkonversi ke nilai PWM (0-255) menggunakan fungsi map(nilaiADC, 0, 1023, 50, 200). Ini akan membatasi agar LED tidak mati melainkan hanya redup.