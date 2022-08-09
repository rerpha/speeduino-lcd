#define RPM_LB              14
#define RPM_HB              15
#define COOLANT_PLUS_OFFSET  7
#define WAITING_INTERVAL  100  // ms
#define TEMP_OFFSET 40
const byte responseSize = 100;
byte reply;
int bytesRead;
byte response[responseSize];
unsigned long start;
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
}


void loop() {
    bytesRead = 0;
    Serial1.print("A"); 

  start = millis();
  while ( (millis() - start) < WAITING_INTERVAL ) {
    while (Serial1.available() != 0) {
      reply = Serial1.read();
      if (bytesRead > 0 ) {
        response[bytesRead - 1] = reply;
      }
      if (bytesRead < responseSize - 1) {
        bytesRead++;
      }
    }
  }

  unsigned int rpm = response[RPM_HB] * 255 + response[RPM_LB]; 
  int clt = response[7]-TEMP_OFFSET;
  // TODO rather than print here, print to i2c LCD 
  Serial.print("rpm: ");
  Serial.print(rpm, DEC);
  Serial.print("clt: ");
  Serial.print(clt, DEC); 
}
