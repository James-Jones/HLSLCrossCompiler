from subprocess import call
import os;
import glob;
import sys;
import argparse

executable = ""

passCount = 0
failCount = 0
listOfFailedTests = []

i = 0

parser = argparse.ArgumentParser(description='Test runner.')
parser.add_argument("-e", "--exe", dest="argExecutableName", required=False, help="The executable")
options = parser.parse_args()

def FindExecutable():
	global executable

	if os.path.isfile("../bin/HLSLByteCodeToGLSLStandalone.exe") or os.path.isfile("../bin/HLSLByteCodeToGLSLStandalone"):
		executable = "../bin//HLSLByteCodeToGLSLStandalone"
	elif os.path.isfile("../bin/Release/HLSLByteCodeToGLSLStandalone.exe") or os.path.isfile("../bin/Release/HLSLByteCodeToGLSLStandalone"):
		executable = "../bin/Release/HLSLByteCodeToGLSLStandalone"
	elif os.path.isfile("../bin/Debug/HLSLByteCodeToGLSLStandalone.exe") or os.path.isfile("../bin/Debug/HLSLByteCodeToGLSLStandalone"):
		executable = "../bin/Debug/HLSLByteCodeToGLSLStandalone"
	else:
		#Search system paths
		for path in os.environ["PATH"].split(os.pathsep):
			win_exe_file = os.path.join(path, "HLSLByteCodeToGLSLStandalone.exe")
			otheros_exe_file = os.path.join(path, "HLSLByteCodeToGLSLStandalone")
			if os.path.isfile(win_exe_file) or os.path.isfile(otheros_exe_file):
				executable = otheros_exe_file #okay on windows as well.
				return
		print "Failed to find exe.\n"
		sys.exit(0)

def RunTest(ByteCodeFileName, lang):

	global failCount
	global passCount
	global listOfFailedTests
	global executable

	(head, tail) = os.path.split(ByteCodeFileName);
	outputfilename = tail + ".glsl"
	directory = "results/glsl" + lang

	if os.path.isdir(directory) == False:
		os.makedirs(directory)

	returnCode = call([executable, ByteCodeFileName, directory+"/"+outputfilename, lang])

	if returnCode == 1:
		print "vs4/mov failed to compile"
		failCount += 1
		listOfFailedTests.append(ByteCodeFileName)
	else:
		passCount += 1

if(options.argExecutableName):
	executable = options.argExecutableName
else:
	FindExecutable()

for files in glob.glob("vs4/*.o"):
	RunTest(files, "150")

for files in glob.glob("ps4/*.o"):
	RunTest(files, "150")

for files in glob.glob("gs4/*.o"):
	RunTest(files, "150")

for files in glob.glob("vs5/*.o"):
	 RunTest(files, "400")

for files in glob.glob("ps5/*.o"):
	RunTest(files, "400")

for files in glob.glob("gs5/*.o"):
	RunTest(files, "400")

for files in glob.glob("hs5/*.o"):
	RunTest(files, "400")

for files in glob.glob("ds5/*.o"):
	RunTest(files, "400")

print str(passCount) + " passed; " + str(failCount) + " failed.\n"
print "Failed tests:"
for testName in listOfFailedTests:
	print testName
