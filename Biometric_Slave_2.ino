#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
char bio;
String rec = "";
String att = "";
bool done_a = false;
bool Start_a = false;
SoftwareSerial master(2, 3); // RX, TX
const int chipSelect = 4;
File myFile;
File aFile;
void setup() {
Serial.begin(57600);
master.begin(19200);
Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void loop() {
master.listen();
while (master.available() > 0) {
    bio = master.read();
    if(bio == 'a'){
    Start_a = true; 
    }
    
     while(Start_a){
    att += bio;  
   if (bio == '\n'){
    done_a = true;
    break;
    }
    break;
    Start_a = false;
     }
    }
    
    
    


if(done_a){
Serial.println(rec);
aFile = SD.open("Attend.txt", FILE_WRITE);
if (aFile) {
    Serial.print("Writing to Attendance.txt...");
    aFile.println(att);
    // close the file:
    aFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Attendance.txt");
  }
  att = "";
done_a = false;
}
}
