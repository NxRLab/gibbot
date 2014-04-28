#!/usr/bin/python
"""
This program is a bootloader for the NU32_v2 from ME333: Introduction
to Mechatronics in the Winter of 2012.  It is basically a reproduction
of several of the functions provided by the Processing app
NU32_Utility.pde written by Nick Marchuk.  I am only writing this
because Processing requires Java to function correctly, and I was
having trouble getting his app to work correctly in 64-bit Linux.

Hopefully this can serve as a good backup to those having problems.

Jarvis Schultz
January 9, 2012
"""

import os
import sys
import time
import glob
try:
    import serial
except ImportError:
    print "[FATAL] Could not find pyserial package!"
    sys.exit(0)
#if os.name == 'nt':
#    import windows_functions as wf
#import windows_functions as wf


## Define constants for the recommended versions
pyser_ver_rec = 2.6
py_ver_rec = (2,6)
## constant for system information:
OS = ''


################################################################################
################################################################################
## function for calculating the crc
def calculate_crc(data):
    """
    This function creates a cyclic redundency check byte for a given
    packet of data.  This is similar to a checksum.
    """
    crc_table = [0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
                 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef]
    crc = 0

    for j in range(len(data)):
        i = (crc >> 12) ^ (data[j] >> 4)
        crc = crc_table[i & 0x0F]^(crc << 4)
        i = (crc >> 12) ^ (data[j] >> 0)
        crc = crc_table[i & 0x0F]^(crc << 4)

    return (crc & 0xFFFF)


################################################################################
################################################################################
## function for parsing incoming messages
def parse_message(got):
    """
    This function parses the message received from the PIC.
    """
    ## convert to string to int array:
    dat = [1]*len(got)
    for i in range(len(got)):
        dat[i] = ord(got[i])
    
    if dat[1]==16 and dat[2]==1: ## received a bootloader version
        if dat[3] == 16:
            c1 = dat[4]
            if dat[5] == 16:
                c2 = dat[6]
            else:
                c2 = dat[5]
        else:
            c1 = dat[3]
            if dat[4] == 16:
                c2 = dat[5]
            else:
                c2 = dat[4]
        print "connected to bootloader v{0}.{1}.".format(c1,c2)

    elif dat[1] == 2:
        print "successfully erased flash"

    elif dat[1] == 3:
        ## programming is going ok!
        return False
    else:
        return True

    
################################################################################
################################################################################
## function for sending a message
def send_message(data, size, crc, com):
    """
    This function assembles and sends out a message to the PIC.
    """
    global OS
    num = size+4

    for val in data:
        if (val == 1) or (val == 4) or (val == 16):
            num+=1

    ## convert crc to an 8-bit signed integer:
    tmp = int(crc & 0xFF)
    if (tmp == 1) or (tmp == 4) or (tmp == 16):
        num+=1

    tmp = int((crc>>8) & 0xFF)
    if (tmp == 1) or (tmp == 4) or (tmp == 16):
        num+=1

    ## Build data buffer:
    bfr = [1]*num
    j = 1

    for i in range(size):
        if (data[i] == 1) or (data[i] == 4) or (data[i] == 16):
            bfr[j] = 16
            j+=1
            bfr[j] = data[i]
        else:
            bfr[j] = data[i]
        j+=1


    tmp = int(crc & 0xFF)
    if (tmp == 1) or (tmp == 4) or (tmp == 16):
        bfr[j]  = 16
        j+=1
    bfr[j] = tmp
    j += 1

    tmp = int((crc>>8) & 0xFF)
    if (tmp == 1) or (tmp == 4) or (tmp == 16):
        bfr[j] = 16
        j+=1
		
    bfr[j] = tmp
    j+=1
    bfr[j] = 4

    ## write out the buffer:
    com.write(''.join(map(chr,bfr)))
    return
        
################################################################################
################################################################################
## create function for opening a comport
def open_comm(device='/dev/ttyUSB1',
              baud=115200,
              stop=1):
    """
    Function for opening comport
    """
    print "opening serial port:",device
    if OS == 'win':
        device = wf.full_port_name(device)
    try:
        s = serial.Serial(device)
        s.close()
        comport = serial.Serial(device,
                            baudrate=baud,
                            timeout=1,
                            parity=serial.PARITY_NONE,
                            stopbits=stop,
                            rtscts=False)
    except (serial.SerialException, ValueError):
        print "Could not open serial port",device+"!"
        list_ports(device)
        sys.exit(1)
        
    comport.flushInput()
    comport.flushOutput()
    return comport


################################################################################
################################################################################
## function for returning list of serial ports:
def list_ports(device):
    global OS
    if OS == 'lin':
        ports = glob.glob('/dev/ttyS*') + glob.glob('/dev/ttyUSB*')
        if device in ports:
            "Is the port busy?"
        else:
            print "Port must be one of the following:"
            print ports
    elif OS == 'mac':
        ports =  glob.glob('/dev/tty.*') + glob.glob('/dev/cu.*')
        if device in ports:
            "Is the port busy?"
        else:
            print "Port must be one of the following:"
            print ports
    elif OS == 'win':
        ports =  wf.enumerate_windows_ports()
        print "Port must be one of the following:"
        for p in ports: print p
    else:
        print "Could not determine port list"
    return

        
################################################################################
################################################################################
## Function for closing comport:
def close_comm(comport):
    print "closing comm port"
    comport.close()

    
################################################################################
################################################################################
## function for getting total number of lines:
def filelen(fname):
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1


################################################################################
################################################################################
## function for writing out a hex file:
def write_program(fd, com, numlines=30):
    """
    This function actually reads in the hex file, and sends it to the
    PIC
    """
    num = filelen(fd)
    print "total lines = ",num
    ## open the file:
    f = open(fd, 'rU')
    
    print "programming the pic..."

    ## set the timeout to an appropriate value for this section
    com.timeout = 0.5

    line = 1
    while line < num:
        msg = [3] ## set first char to tell PIC we are programming
        print "{0:3d}% complete -- programming " \
              "line number: {1:6d}".format(int((line/float(num)*100.0)),line)
        for i in range(numlines):
            ## get current line:
            lines = f.readline()
            ## strip newline
            lines = lines.split()[0][0:]
            ## convert to correct values
            for i in range(1, len(lines), 2):
                msg.append(int(lines[i:i+2],16)&0xFF)
            if line+1 > num:
                break
            line+=1

        ## send them to the PIC
        send_message(msg, len(msg), calculate_crc(msg), com)
        ## wait for a response
        data = ""
        chars = 0
        while chars < 5:
            tmp = ''
            tmp = com.read(1)
            if len(tmp)==0:
                break
            else:
                chars+=1
                data += tmp
        if len(data) == 0:
            print "programming timeout!!!"
            print [hex(x) for x in data]
            return True
        elif(parse_message(data)):
            print "returned bad value during programming"
            return True
        else:
            com.flushInput()
            
    return False


################################################################################
################################################################################

def showdoc():
    usage = """
    Required:
    -f | --file [HEXFILE]
        Specify the hex file to program to the PIC

    Optional
    -d | --diretory [DIRECTORY]
        Specify a directory for the .hex file (if it resides in a directory
        other than the cwd.) This can also be included with the -f flag by
        providing either a relative or absolute path in the arg to -f.

    -p | --port [PORTNAME]
        Specify a port to bootload over other than the default '/dev/ttyUSB1'.

    -l | --lines [NUMLINES]
        Specify the number of lines on the *.hex file that you want to write
        per message sent to the PIC.  The upper limit is probably about 50;
        beyond there you may be exceeding the packet size limits of the FTDI
        chip on the board.  If programming is failing, playing with this
        parameter may help the situation.

    -h | --help
        Print this messge
        """            
    print (usage)
    
        
################################################################################
################################################################################

def prepare_pic(com):
    """
    This function sends the appropriate commands to get the PIC in
    bootloading mode, and veririfes that the it is in bootloading
    mode.
    """
    print "putting the PIC in bootloading mode..."
    com.write(chr(0x42))
    time.sleep(0.1)
    com.write(chr(0x42))
    time.sleep(0.1)
    
    ## now try to connect, and verify that we are in bootloading mode.
    com.timeout = 1.0
    print "connecting..."
    msg = [1]
    send_message(msg, 1, calculate_crc(msg), com)
    print "waiting for reply..."
    data = com.read(11)
    if len(data) == 0:
        print "no reply recieved! check device is in bootloader mode."
        return True

    parse_message(data)
    
    ## now, let's send the command to have the PIC erase its flash
    com.timeout = 5.0 ## since erasing may take a long time, increase timeout
    msg = [2]
    print "\nsending erase command"
    send_message(msg, 1, calculate_crc(msg), com)
    print "waiting for reply..."
    data = com.read(5)
    if len(data) == 0:
        print "no confirmation of erase received!"
        return True
    parse_message(data)

    return False


################################################################################
################################################################################
## function for determining OS
def determine_os():
    """
    This function will determine which OS we are running, and make any
    necessary imports
    """
    global OS
    if sys.platform.startswith('linux') or True:
        OS = 'lin'
    elif sys.platform.startswith('dar'):
        OS = 'mac'
    elif sys.platform.startswith('win') or sys.platform.startswith('cyg'):
        OS = 'win'
    else:
        print "[WARN] OS not recognized!"
        print "[WARN] Not all functionality guaranteed"
        OS = 'unknown'
    return


        
################################################################################
## MAIN ########################################################################
################################################################################
if __name__ == "__main__":
    try:
        ## if they have pkg_resources, let's import it
        import pkg_resources
        ## checking of python modules:
        ser_version = float(pkg_resources.get_distribution("pyserial").version)
        py_version = sys.version_info[0:2]
        if ser_version < pyser_ver_rec:
            print "WARNING: python serial library is older than recommended"\
                  "; please consider updating"
            print "Version used:",ser_version
            print "Recommended: Version >= 2.6\n"
        if py_version < py_ver_rec:
            print "WARNING: python version is older than recommended"\
                  "; please consider updating"
            print "Version used:",sys.version
            print "Recommended: Version >= 2.6\n"
    except ImportError:
        print "[WARN] pkg_resources module not found"
        print "\tconsider installing python-setuptools\n"
        print "[WARN] unable to check package versions"

    ## let's sort out the operating system:
    determine_os()
    
    ## first, let's parse the command line options:
    abbreviations = {
        '-h' : '--help',
        '-f' : '--file',
        '-p' : '--port',
        '-d' : '--directory',
        '-l' : '--lines'
        }
    ## replace abbreviations with full name
    for i in range(len(sys.argv)):
        if sys.argv[i] in abbreviations:
            sys.argv[i] = abbreviations[sys.argv[i]]

    ## now we can parse
    if '--help' in sys.argv:
        showdoc()
        sys.exit(1)
    if '--file' in sys.argv:
        fname = str(sys.argv[sys.argv.index('--file')+1])
        ## then check for a directory argument:
        if '--directory' in sys.argv:
            pth = str(sys.argv[sys.argv.index('--directory')+1])
            if not pth[-1] == '/':
                pth += '/'
            fname = pth+fname
        ## then let's check for the existence of the file
        if not os.path.isfile(fname):
            print "\nhex file does not exist!!\n"
            sys.exit(1)
        print "hex file:",fname
    else:
        showdoc()
        sys.exit(1)
    if '--port' in sys.argv:
        ## open the serial port
        comport = open_comm(device=str(sys.argv[sys.argv.index('--port')+1]))
    else:
        comport = open_comm(device='/dev/ttyUSB1')
    if '--lines' in sys.argv:
        numlines = int(sys.argv[sys.argv.index('--lines')+1])
    else:
        numlines = 30

    
    ## let's send the command to get the PIC in bootloading mode
    if(prepare_pic(comport)):
        print "\nPreparations failed!!!\n"
        close_comm(comport)
        sys.exit(1)

    ## now we can program the PIC
    if(write_program(fname, comport, numlines)):
        print "\nProgramming failed!!!\n"
        close_comm(comport)
        sys.exit(1)
    else:
        print "Programming successful!\n"

    ## close the comport
    close_comm(comport)
    comport.close()
    sys.exit(0)

    

    
