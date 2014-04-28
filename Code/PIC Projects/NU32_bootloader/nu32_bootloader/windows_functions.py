import re
import _winreg as winreg
import itertools

"""
These functions are utility functions that were borrowed from
http://eli.thegreenplace.net/2009/07/31/listing-all-serial-ports-on-windows-with-python/
"""


################################################################################
################################################################################

## function for listing all of the windows ports:
def enumerate_windows_ports():
    """ Uses the Win32 registry to return an
        iterator of serial (COM) ports
        existing on this computer.
    """
    path = 'HARDWARE\\DEVICEMAP\\SERIALCOMM'
    try:
        key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, path)
    except WindowsError:
        raise IterationError

    for i in itertools.count():
        try:
            val = winreg.EnumValue(key, i)
            yield str(val[1])
        except EnvironmentError:
            break

################################################################################
################################################################################

## function for returning the full name of the windows ports
def full_port_name(portname):
    """ Given a port-name (of the form COM7,
        COM12, CNCA0, etc.) returns a full
        name suitable for opening with the
        Serial class.
    """
    m = re.match('^COM(\d+)$', portname)
    if m and int(m.group(1)) < 10:
        return portname
    return '\\\\.\\' + portname
