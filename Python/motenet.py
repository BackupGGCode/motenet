#!/usr/bin/env python


import serial, os, sys, struct, json
from pprint import pprint
from collections import namedtuple # http://stackoverflow.com/questions/6578986/how-to-convert-json-data-into-a-python-object


'''
Details for struct 
https://docs.python.org/2/library/struct.html
Note: Struct does not support byte data type. Using char transformation.
'''

class sysConfig():
	'''
		Configuration processor
	'''
	def __init__(self):
		self.configFile = 'motenet.conf'
	def _loadConfig(self):
		'''
		Read configuration file 
		'''
		json_fh = open(self.configFile)
		#json_data = json.load(json_fh)
		cfg = json.load(json_fh, object_hook=lambda d: namedtuple('X', d.keys())(*d.values()))
		return cfg
	def getConfig(self):
		'''
		Public interface for collecting system configuration
		'''
		return self._loadConfig()







if __name__ == '__main__':
	'Execute'
	print 'Starting unit testing'
	sysConf = sysConfig()
	conf = sysConf.getConfig()
	print 'Serial Port = {0}'.format(conf.SERIAL_PORT)
	print 'Serial Baud = {0}'.format(conf.SERIAL_BAUD)
	print "Done"


