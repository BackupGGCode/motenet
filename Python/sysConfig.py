#!/usr/bin/env python
import sys, json, os
# http://stackoverflow.com/questions/6578986/how-to-convert-json-data-into-a-python-object
from collections import namedtuple 


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
		# convert json into named tuple object
		cfg = json.load(json_fh, object_hook=lambda d: namedtuple('X', d.keys())(*d.values()))
		return cfg
	def getConfig(self):
		'''
		Public interface for collecting system configuration
		'''
		return self._loadConfig()
	def getIndex(self):
		return self._loadConfig().keys()

if __name__ == '__main__':
	# Unit tests 
	# (data saved in motenet.conf for testing. )
	'''
		SEED Data used in testing
		{
			"SERIAL_PORT":"/dev/ttyBlue",
			"SERIAL_BAUD": 115200,
			"ITEMS" : [
				{"A":1, "B":30},
				{"A": 25, "B": 2}
			]
		}
	'''
	
	# Get system configuration
	sysConf = sysConfig()
	conf = sysConf.getConfig()
	print "Config Value [Serial Port]: {0}".format(conf.SERIAL_PORT)

	# Get element from index
	for x in conf.ITEMS:
		print "Config Value [Item A]: {0}".format(x.A)

	# Get Index
	print "Index = {0}".format(conf)
