#!/usr/bin/env python2
import os
import sys
##########
#Written by Peter Nguyen
#Python version
##########


host_dir="/etc/hosts"
dir_host="list"
old_data="127.0.0.1 localhost.localdomain thekiller-laptop\n127.0.1.1 thekiller-laptop"

def change_host_file(dir_host,host_dir):  
  try:
    os.system("chattr -i "+host_dir)
    if os.path.isfile(file_in) and os.path.isfile(file_out):
      f_in=open(dir_host,'r+')
      f_out=open(host_dir,'w+')
      while True:
	block=f_in.readline()
	if not block:
	  break
	f_out.write(block)
      f_in.close()
      f_out.close()
      os.system("chattr +i "+host_dir)
    else:
      print "File %s doesn't exist" % file_in
      sys.exit(1)
    print "File has been changed"
  except IOError:
      print "Host File has been changed error: %s" % IOError
      sys.exit(1)

def restore_host_file(old_data,host_dir):
  try:
    os.system("chattr -i "+host_dir)
    if os.path.isfile(host_dir):    
      f_out=open(host_dir,'w+')
      f_out.write(old_data)
      f_out.close()
    else:
      print "File %s doesn't exist" % file_out
      sys.exit(1)
    print "File has been changed"
    os.system("chattr +i "+file_out)
  except IOError:
      print "Host File has been changed error: %s" % IOError
      sys.exit(1)

#######################
#    Main Program
#######################

if __name__ == "__main__":
  print "======================="
  print "= 1 - Change Host     ="
  print "= 2 - Restore Host    ="
  print "= 3 - Quit            ="
  print "======================="
  choices=int(raw_input("Choices: "))

  if choices == 1:
	change_host_file(dir_host,host_dir)
  if choices == 2:
	restore_host_file(old_data,host_dir)
  if choices == 3:
	sys.exit(0)