# For MQTT
import context  # Ensures paho is in PYTHONPATH
import paho.mqtt.client as mqtt
import time
import json
# For GPIO
import RPi.GPIO as GPIO

def on_connect(client, userdata, flags, rc):
    global isConnect
    print("Connected with result code " + str(rc))
    if rc == 0:
        isConnect = 1;
    client.publish("connect", "true", 1)
    
def on_disconnect(client, userdata, rc):
    global isConnect
    print("Unexpected disconnection")
    isConnect = 0;

isConnect = 0;
client = mqtt.Client(client_id="truba_111")
client.on_connect = on_connect
client.on_disconnect = on_disconnect
client.loop_start()
client.connect("172.20.10.3", 1883, 60)
GPIO.setmode(GPIO.BCM)
GPIO.setup(13,GPIO.IN)
GPIO.setup(19,GPIO.IN)
GPIO.setup(26,GPIO.IN)
ev1=ev2=ev3=0;

while True:
    if isConnect == 1:
        currentEv1=GPIO.input(13);
        currentEv2=GPIO.input(19);
        currentEv3=GPIO.input(26);
        if((currentEv1 != ev1) | (currentEv2 != ev2) | (currentEv3 != ev3)):
            ev1 = currentEv1;
            ev2 = currentEv2;
            ev3 = currentEv3;
            millis = int(round(time.time()*1000))
            print("Publish new event")
            client.publish("state", json.dumps({"ev1":ev1, "ev2":ev2, "ev3":ev3, "time": millis}), 1)
        time.sleep(0.5)
# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_stop()
GPIO.clenup()
