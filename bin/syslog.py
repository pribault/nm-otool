#!/usr/bin/python
# clem@42.fr - 02/11/2015
try:
	import socket
	import time
	import sys

	if len(sys.argv) > 1:
			sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			data = "<30>%s %s" % (socket.gethostname(), ' '.join(sys.argv[1:]))
			sock.sendto(data, ('syslog-student.42.fr', 514))
	else:
		print 'Usage: %s <message>' % sys.argv[0]
except:
	pass
