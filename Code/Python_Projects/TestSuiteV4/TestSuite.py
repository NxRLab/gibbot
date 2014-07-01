import argparse

#Create an argument parser for command line interface
parser = argparse.ArgumentParser(description='Serial communication burst pass through test')

parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
args = parser.parse_args()
print args.verbose
