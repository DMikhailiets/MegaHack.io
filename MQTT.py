from paho.mqtt import publish


def main():
    while True:
        message=(input());
        if (message=="on"):
            message='1'
        if (message=="off"):
            message='0'
            
        msgs = [{'topic': "test/led", 'payload': message}]
        publish.multiple(msgs, hostname="192.168.43.2")

if __name__ == "__main__":  
    main()
