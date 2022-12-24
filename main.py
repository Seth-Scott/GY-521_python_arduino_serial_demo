'''
A barebones python script to read serial data from an Arduino and print it to the console.
In this example, we're taking pitch and roll measurements from a GY-521 board.
The Arduino is sending serial data as a string in the format of "(x, y)" 
We want to strip the non-numeric characters and split the string into a list of two elements. 

This can be adjusted to fit your needs.
'''

import serial
import re
import os
from dotenv import load_dotenv

# load the .env file
load_dotenv()

'''
.env file should contain the following:
SP=path/to/serial/port
BR=baudrate
'''

# path to serial port
serial_port = os.getenv('SP')
# probably 9600
baudrate = os.getenv('BR')

# this isn't necessary if the Arduino is sending only numbers
def strip_non_numeric(string):
    '''strips non-numeric characters from a string except for . , and -'''
    return re.sub(r'[^\d.,-]', '', string)

# this may need to be adjusted to fit your needs
def output_serial():
    ''''reads serial data from the Arduino and prints it to the console'''
    ser = serial.Serial(serial_port, baudrate)
    while True:
        line = ser.readline()
        # the Arduino is sending encoded data that needs to be decoded, split, and stripped
        line_str = strip_non_numeric(line.decode('utf-8')).split(",")
        # this is where you can do whatever you want with the data
        print(line_str[0], line_str[1])
        
        
output_serial()
