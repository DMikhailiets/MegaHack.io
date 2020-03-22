#include <ESP8266WiFi.h>
#include <PubSubClient.h> // установить



#define LED  16// определяем пин светодиода
#define LED1 5
#define MQTT_client "ESPled3" // произвольное название MQTT клиента, иногда требуется уникальное.

// настройки домашней сети
const char *ssid =  "iPhone";  // название точки достпа 
const char *pass =  "12345678t"; // Пароль от точки доступа

// настройки для MQTT брокера
const char *mqtt_server = "172.20.10.3"; // адрес сервера MQTT 
const int mqtt_port = 1883; // Порт для подключения к серверу MQTT
const char *mqtt_user = "admin"; // Логин от сервера MQTT
const char *mqtt_pass = "admin"; // Пароль от сервера MQTT
const char *led_topic="test/led"; // топик для светодиода
const char *data_topic="test/data"; // топик для данных


int pause = 300; // переменная для паузы между отправками данных
long int times=0; // для времени




WiFiClient wclient;      
PubSubClient client(wclient, mqtt_server, mqtt_port);



// получение данных с сервера и отработка
void callback(const MQTT::Publish& pub)    
{
    String topic = pub.topic();
    Serial.print(topic);                // выводим в сериал порт название топика
    Serial.print(" => ");
    String payload = pub.payload_string(); // чтение данных из топика
    Serial.print(payload);   // выводим в сериал порт значение полученных данных
    Serial.println(); 
    // действия над светодиодом в зависимости от данных из топика
    if (topic==led_topic) 
    {
    if (payload[0] == '0') digitalWrite(LED, LOW); 
    else if (payload[0] == '1') digitalWrite(LED, HIGH); 
    else if (payload[0] == '2') digitalWrite(LED, !digitalRead(LED)); 
    }
}
//-------------------------------



// Функция отправки показаний
void refreshData() {
  if (pause == 0) {
    times = millis(); // формируем данные для отправки
    client.publish(data_topic, String(times));
    pause = 3000; // пауза меду отправками 3 секунды
  }
  pause--;
  
  delay(1); 
}
//------------------------------------

void setup() {
    Serial.begin(115200);
    delay(10);
    
    
    Serial.println();
    Serial.println();
    pinMode(LED, OUTPUT); // пин светика на выход
    pinMode(LED1, OUTPUT);
}

void loop() {
    
    if (WiFi.status() != WL_CONNECTED) { // если соединения нет
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.println("...");
        WiFi.begin(ssid, pass);// подключаемся к wi-fi
        
        if (WiFi.waitForConnectResult() != WL_CONNECTED) // ждем окончания подключения
            return;
        Serial.println("WiFi connected");
    }
    
    // подключаемся к MQTT серверу
    if (WiFi.status() == WL_CONNECTED) { // если есть подключение к wi-fi
        if (!client.connected()) { // если нет подключения к серверу MQTT
           // Serial.println("MQTT - none");
            if (client.connect(MQTT::Connect(MQTT_client) // если соединились то делаем всякое
                                 .set_auth(mqtt_user, mqtt_pass))) {
               // Serial.println("MQTT - ok");
                client.set_callback(callback);
                client.subscribe(led_topic);                  // подписка на топик led
                client.subscribe(data_topic);                 // подписка на топик data
            } else {
                Serial.println("MQTT - error");   // если не удалось подключиться сообщаем в порт
            }
        }
        
        if (client.connected()){ // если есть соединение с MQTT 
            client.loop();
            refreshData();
        }
    }
} // конец основного цикла
