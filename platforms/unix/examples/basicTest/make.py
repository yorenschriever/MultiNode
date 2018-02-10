#!/usr/bin/python

#Makefile is driving me crazy. For now i will use python

import glob
import re
import os
from subprocess import call

sources = []
RebuildAll = True

#compiler and args to use
CXX = "g++"
CXXFLAGS = "-std=c++11 -Wc++11-extensions"

#this function will scan the filesystem and add .cpp in the specified direcotry to a list.
#it will aso store where the object will be created
def addSources(sourcedir, objdir): #adds all source fiels to a list, together with the name of the object file that they will correspond to
    files =      glob.glob(sourcedir + "/*.cpp") #look for cpp files in the specified dir
    files.extend(glob.glob(sourcedir + "/**/*.cpp")) #also look in all subdirs

    for src in files:
        entry = {"src": src, "obj": re.sub('.cpp$','.o',src.replace(sourcedir, objdir,1)) }
        sources.append(entry)

#determine if we need to rebuild a file
def determineRebuild(src, obj):
    if RebuildAll:
        return True

    if not os.path.isfile(obj):
        return True

    if os.path.getmtime(src) > os.path.getmtime(obj):
        return True

    return False

# folder and name of the application to generate
TARGETDIR = "bin"
TARGET = "application"

addSources("../../../../src",    "obj/MultiNode")
#addSources("../../../../lib",    "obj/lib")
addSources("../../implementations", "obj/implementations")
addSources(".", "obj")


#build object files
for src in sources:
    command = CXX + " " + CXXFLAGS + " -c -o " + src["obj"] + " " + src["src"]    
    call("mkdir -p "+os.path.dirname(src["obj"]), shell=True)
    if determineRebuild(src["src"],src["obj"]):
        print command
        call(command, shell=True)

#link application
call("mkdir -p "+TARGETDIR, shell=True)

objectfiles = " ".join(src["obj"] for src in sources)
command  = CXX + " -o " + TARGETDIR + "/" + TARGET + " " + objectfiles + " "
print command
call(command, shell=True)