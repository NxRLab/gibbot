import serial
import argparse

#Create an argument parser for command line interface
parser = argparse.ArgumentParser(description='Magnet control function. Calling the function with no arguments toggles the output of both magnets.')
#Add arguments that can be passed through the command line
parser.add_argument('-t', '--top', action='store_true', help='Control top magnet')
parser.add_argument('-b', '--bottom', action='store_true', help='Control bottom magnet')
parser.add_argument('-n', '--on', action='store_true', help='Turn magnet(s) on')
parser.add_argument('-f', '--off', action='store_true', help='Turn magnet(s) of')

args = parser.parse_args()

#initialize serial port
ser = serial.Serial(2) #COM 3       7 -> COM 8
ser.baudrate = 115200  #set the baud rate
ser.timeout = 1        #1s timeout

if args.on == True: #If command is to turn magnets on 
    if args.top == False:   #
        ser.write('g')  #Turn lower magnet on
    if args.bottom == False:   
        ser.write('d')  #Turn top magnet on
elif args.off ==True: #If command is to turn magnets off
    if args.top == False:   #
        ser.write('h')  #Turn lower magnet off
    if args.bottom == False:   
        ser.write('e')  #Turn top magnet off
else: #Toggle magnets
    if args.top == False:   #
        ser.write('c')  #Toggle lower magnet
    if args.bottom == False:   
        ser.write('f')  #Toggle top magnet   
