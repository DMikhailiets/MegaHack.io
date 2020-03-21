import paho.mqtt.client as paho
broker="sandbox.rightech.io"
port=1883
def on_publish(client,userdata,result):             #create function for callback
   # print("data published \n")
    pass
client1= paho.Client("Glados")                           #create client object
client1.on_publish = on_publish                          #assign function to callback
client1.connect(broker,port)                                 #establish connection


while True:
        message=(input());
        if (message=="on"):
            message='1'
        if (message=="off"):
            message='0'
        ret= client1.publish("test/led",message )                   #publish
        ret= client1.publish("test/led2",message )    
