#!/usr/bin/python
from ftplib import FTP
from glob import glob as files
import os
host = "192.168.0.18"
port = 5000
rootname = os.getcwd().split("/")[-1]
f = FTP()
f.connect(host,port=port)
try:
    f.cwd("3ds/"+rootname)
except:
    f.mkd("3ds/"+rootname)
for match in files(rootname+"*"):
    print("Sending",match)
    with open(match,'rb') as file:
        f.storbinary('STOR ' + match,file)
print("Files sent over")
f.close()

