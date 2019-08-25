unsigned int iRelativeHumidity, dRelativeHumidity, dataSum;
unsigned int dTemperature, iTemperature, checkSum;
const int DHTPIN = 2;
void setup() 
{
  Serial.begin(9600);
}

void requestToSensor()
{
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, LOW);
  delay(18);
  digitalWrite(DHTPIN, HIGH);
}

void responseFromSensor()
{
  pinMode(DHTPIN, INPUT);
  while(digitalRead(DHTPIN) == 1);
  while(digitalRead(DHTPIN) == 0);
  while(digitalRead(DHTPIN) == 1);
}

unsigned int getDataFromSensor()
{
  unsigned int rxdByte = 0;
  for (int k = 0; k < 8; k++)
  {
    while(digitalRead(DHTPIN) == 0);
    delayMicroseconds(28);
    if (digitalRead(DHTPIN) == 1)
      rxdByte = (rxdByte << 1) | (0x01);
    else
      rxdByte = (rxdByte << 1);
    while(digitalRead(DHTPIN) == 1);  
  }
  return rxdByte;
}

void loop() 
{
  requestToSensor();
  responseFromSensor(); 
  iRelativeHumidity = getDataFromSensor();
  dRelativeHumidity = getDataFromSensor();
  iTemperature = getDataFromSensor();
  dTemperature = getDataFromSensor();
  checkSum = getDataFromSensor();
  dataSum = iRelativeHumidity + dRelativeHumidity + iTemperature + dTemperature;
  if (dataSum == checkSum)
  {
    Serial.print("Relative Humidity: " + String(iRelativeHumidity) + "%\t");
    Serial.println("Temperature: " + String(iTemperature) + "°C");
  }
  delay(2000);
}

