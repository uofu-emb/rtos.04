import time
from serial import Serial
from serial.serialutil import SerialException
import sys

tty = sys.argv[1]
while True:
    try:
        with Serial(tty) as s:
            f = s.readline()
            while f:
                print(str(f, encoding="ASCII"))
                f = s.readline()
    except SerialException as e:
        time.sleep(1)
        continue
