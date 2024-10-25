import socket

# Replace with the ESP32 IP address
esp32_ip = "10.67.76.146"  
port = 80

def receive_data():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((esp32_ip, port))
        data = s.recv(1024)  # Receive data from ESP32
        return data.decode()

if __name__ == "__main__":
    while True:
        try:
            data = receive_data()
            print("Received photoresistor | touch values:", data)
        except Exception as e:
            print("Failed to receive data:", e)
