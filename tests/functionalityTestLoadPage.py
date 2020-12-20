import socket
import datetime
import time

HOST = "192.168.1.20"
PORT = 8888

now = datetime.datetime.now()
three_hours_in_future = now.replace(hour=now.hour + 3)

try:
    while now < three_hours_in_future:
        mySock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        mySock.settimeout(2.0)
        mySock.connect((HOST, PORT))

        mySock.send(b"GET / HTTP/2\nHost: 192.168.1.20:8888\n")
        data = mySock.recv(16000)
        # print(str(data))
        mySock.close()
        time.sleep(1)
        now = datetime.datetime.now()

    print("TEST OK")

except socket.timeout:
    timeoutTime = datetime.datetime.now()
    print(f"TEST FAILED: Server timed out at {timeoutTime}")
