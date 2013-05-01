from math import *
from GibbotModel import *

# All controllers should return an accelleration scalar (q2dd).
# Controllers shoud NOT modify the bot directly.

def nullController(bot):
    return 0

def spongController(bot):
    return .1 # need to implement...


