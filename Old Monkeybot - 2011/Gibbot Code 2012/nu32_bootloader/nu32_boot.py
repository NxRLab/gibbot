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
import glob, fnmatch
try:
    import serial
except ImportError:
    print "[FATAL] Could not find pyserial package!"
    sys.exit(0)
if os.name == 'nt':
    import windows_functions as wf


## Define constants for the recommended versions
pyser_ver_rec = 2.6
py_ver_rec = (2,5)
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
        print "connected to bootloader v"+str(c1)+"."+str(c2)

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
    global OS 
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
def list_ports(device=None):
    global OS
    if OS == 'lin' or OS == 'cyg':
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
    f = open(fname)
    a = 0
    for lines in f:
        a += 1
    f.close()
    return a
    

################################################################################
################################################################################
## function for writing out a hex file:
def write_program(fd, com, numlines=30):
    """
    This function actually reads in the hex file, and sends it to the
    PIC
    """
    global py_version
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
        if py_version[-1] >= 9:
            print "{0:3d}% complete -- programming " \
                  "line number: {1:6d}".\
                  format(int((line/float(num)*100.0)),line)
        else:
            print str(int((line/float(num)*100.0)))+" percent complete -- "\
                  +"programming line number "+str(line)
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
    Example usages:
        Unix/Linux/Cygwin:
                nu32_boot.py -f test.hex -p /dev/ttyUSB3
                nu32_boot.py -c localconfig.txt
                nu32_boot.py -f test.hex -p /dev/ttyUSB3 -w config.txt
                nu32_boot.py -l                

        Windows:
                python.exe nu32_boot.py -f test.hex -p COM6        
                python.exe nu32_boot.py -c localconfig.txt
                python.exe nu32_boot.py -f test.hex -p COM3 -w config.txt
                python.exe nu32_boot.py -l
                
    Arguments:
    -f | --file [HEXFILE]
        Specify the hex file to program to the PIC (either this or -x
        MUST be used)

    -p | --port [PORTNAME]
        Specify a port to bootload over other than the default

    -b | --baud [BAUDRATE]
        Specify a baud rate in bits per second (bps) to send serial data at, 
		default is 115200 bps

    -d | --directory [DIRECTORY]
        Specify a directory other than the working directory to look for hex
        files

    -c | --config [CONFIG_FILENAME]
        Specify a filename for the program to read a configuration from.
        CONFIG_FILENAME must either be in the working directory, or a path
        (relative or absolute) must be included.

    -l | --listports
        Request the program to list the available ports and exit. May not work
        on all OSs. Overrides all other args except --help.

    -s | --setdefaults [FILENAME]
        Overwrite the default configuration file stored in $HOME/.nubootconfig
        Will not write any option that does not require an argument.  If you
        really want those in a configuration file, add them manually.
        
    -w | --writedefaults [FILENAME]
        This option generates a configuration file in FILENAME, and
        writes all options parsed along with -w to FILENAME.  Will not
        write any option that does not require an argument.  If you
        really want those in a configuration file, add them manually.

    -r | --runfalse
        Providing this argument prevents the PIC from being rebooted to start
        the program running after a successful program.

    -n | --numlines [NUMLINES]
        Specify the number of lines on the *.hex file that you want to write
        per message sent to the PIC.  The upper limit is probably about 50;
        beyond there you may be exceeding the packet size limits of the FTDI
        chip on the board.  If programming is failing, playing with this
        parameter may help the situation.

    -x | --mplabx
        If this option is specified, automatically search the
        directory given by -d for a hex file, and use the first one
        found as the target hex file.  If no value is given for -d, it
        will recursively search the current working directory. Either
        this or -f must be used, -f takes precedence over -x.

    -h | --help
        Print this message, override all other args.
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
    if sys.platform.startswith('linux'):
        OS = 'lin'
    elif sys.platform.startswith('dar'):
        OS = 'mac'
    elif sys.platform.startswith('win'):
        OS = 'win'
    elif sys.platform.startswith('cyg'):
        print "[WARN] Running under cygwin is not fully tested"
        OS = 'cyg'
    else:
        print "[WARN] OS not recognized!"
        print "[WARN] Not all functionality guaranteed"
        OS = 'unknown'
    return


################################################################################
################################################################################
## function for rebooting the pic into run mode
def reboot_pic(com):
    time.sleep(0.5)
    print "rebooting pic"
    msg = [5]
    send_message(msg, 1, calculate_crc(msg), com);
    return



################################################################################
################################################################################
## function for rebooting the pic into run mode
def parse_args(args):
    ## define all of the command line options
    abbreviations = {
        '-h' : '--help',
        '-f' : '--file',
        '-p' : '--port',
        '-n' : '--numlines',
        '-l' : '--listports',
        '-r' : '--runfalse',
        '-c' : '--config',
        '-d' : '--directory',
        '-s' : '--setdefaults',
        '-w' : '--writedefaults',
        '-x' : '--mplabx',
        '-b' : '--baud'
        }
    noargs = ['--runfalse', '--setdefaults',
              '--listports', '--help', '--mplabx']
    opts = {}

    ## replace abbreviations with full name
    for i in range(len(args)):
        if args[i] in abbreviations:
            args[i] = abbreviations[args[i]]

    ## now, let's get the list of args from the default configuration
    defconfig = '.nu32bootconfig'
    defconfig = os.path.join(os.path.expanduser('~'), defconfig)
    ## does the file exist?
    if not os.path.isfile(defconfig):
        createflag = True
        defargs = []
    else:
        createflag = False
        ## read in the configurations
        f = open(defconfig, 'rU')
        defargs = [lines.split() for lines in f]
        defargs = [item for sublist in defargs for item in sublist]
        f.close()
        for i in range(len(defargs)):
            if defargs[i] in abbreviations:
                defargs[i] = abbreviations[defargs[i]]

    ## did we specify a configuration file?
    fname = ''
    cargs = []
    if ('--config' in defargs):
        fname = str(defargs[defargs.index('--config')+1])
    if ('--config' in args):
        fname = str(args[args.index('--config')+1])
    if fname:
        if not os.path.isfile(fname):
            print "Configuration file",fname,"not found"
            sys.exit(1)
        else:
            f = open(fname, 'rU')
            cargs = [lines.split() for lines in f]
            cargs = [item for sublist in cargs for item in sublist]
            f.close()
            for i in range(len(cargs)):
                if cargs[i] in abbreviations:
                    cargs[i] = abbreviations[cargs[i]]

    ## now we can begin parsing the configurations:
    for vals in [defargs, cargs, args]: 
        for a in vals:
            if a in abbreviations.values():
                if a not in noargs:
                    opts[a] = str(vals[vals.index(a)+1])
                else:
                    opts[a] = True

    print "Determined the following options:"
    print opts

    ## should we create the default file?:
    if opts.has_key('--writedefaults'):
        createflag = True
        f = open(opts['--writedefaults'], 'w')
        opts.pop('--writedefaults')
    elif opts.has_key('--setdefaults'):
        createflag = True
        f = open(defconfig, 'w')
        opts.pop('--setdefaults')
    elif createflag:
        f = open(defconfig, 'w')
    if createflag:
        print "\n\rWriting config file to\n\r",f.name,"\n\r"
        for i in opts.iteritems():
            if i[0] not in noargs:
                line = i[0]+" "+i[1]+"\r\n"
                f.write(line)
        f.close()

    return opts


        
################################################################################
## MAIN ########################################################################
################################################################################
if __name__ == "__main__":
    global py_version
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
        py_version = [0];
        print "[WARN] pkg_resources module not found"
        print "\tconsider installing python-setuptools\n"
        print "[WARN] unable to check package versions"


    ## let's sort out the operating system:
    determine_os()

    ## now, let's parse the specified options:
    opts = parse_args(sys.argv)
    if opts.has_key('--help'):
        showdoc()
        sys.exit(1)
    if opts.has_key('--listports'):
        print "Listing available ports"
        list_ports()
        sys.exit(1)

    ## hex file parsing:
    if opts.has_key('--file'):
        fname = opts['--file']
        ## now check for the directory arg
        if opts.has_key('--directory'):
            pth = opts['--directory']
            fname = os.path.join(pth,fname)
        ## then let's check for the existence of the file
        if not os.path.isfile(fname):
            print "\nhex file does not exist!!\n"
            sys.exit(1)
        print "hex file:",fname
    elif opts.has_key('--mplabx'):
        ## we will just search for the first hex file we can find in a
        ## subdirecory
        if opts.has_key('--directory'):
            pth = opts['--directory']
        else:
            pth = os.getcwd()
        matches = []
        for root, dirnames, filenames in os.walk(pth):
            for filename in fnmatch.filter(filenames, '*.hex'):
                matches.append(os.path.join(root, filename))
        if len(matches) > 1:
            print "More than one hex file found, using the first one"
        print "Located the following hex files:"
        for i in matches: print i
        print "\r\n"
        fname = matches[0]
    else:
        showdoc()
        sys.exit(1)

    ## serial port parsing
    if opts.has_key('--port'):
        ## open the serial port
		if opts.has_key('--baud'):
			comport = open_comm(device=opts['--port'], baud=opts['--baud'])
		else:
			comport = open_comm(device=opts['--port'])
    else:
        print "[ERROR] No comport specifed! Use the -p (--port) option."
        sys.exit(1)

    ## miscellaneous parsing
    if opts.has_key('--numlines'):
        numlines = int(opts['--numlines'])
    else:
        numlines = 30
    if opts.has_key('--runfalse'):
        run = False
    else:
        run = True
        
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

    ## reboot pic if we are supposed to
    if run:
        reboot_pic(comport)

    ## close the comport
    close_comm(comport)
    comport.close()
    sys.exit(0)

    

    
