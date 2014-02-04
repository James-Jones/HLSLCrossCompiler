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
parser.add_argument("-e", "--exe", dest="argExecutableName", help="The executable")
parser.add_argument("-v", "--verbose", dest="argVerbose", action='store_true', help="Verbose output")
options = parser.parse_args()	

def FindExecutable():
	global executable

	if os.path.isfile("../bin/HLSLcc.exe") or os.path.isfile("../bin/HLSLcc"):
		executable = "../bin//HLSLcc"
	elif os.path.isfile("../bin/Release/HLSLcc.exe") or os.path.isfile("../bin/Release/HLSLcc"):
		executable = "../bin/Release/HLSLcc"
	elif os.path.isfile("../bin/Debug/HLSLcc.exe") or os.path.isfile("../bin/Debug/HLSLcc"):
		executable = "../bin/Debug/HLSLcc"
	else:
		#Search system paths
		for path in os.environ["PATH"].split(os.pathsep):
			win_exe_file = os.path.join(path, "HLSLcc.exe")
			otheros_exe_file = os.path.join(path, "HLSLcc")
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

	if options.argVerbose:
		print "Running " + ByteCodeFileName +"\n"

	(head, tail) = os.path.split(ByteCodeFileName);

	# tail2 will be shader model folder name
	# e.g. vs4, hs5 etc.
	(head2, tail2) = os.path.split(head);

	outputfilename = tail + ".glsl"

	directory = "results/glsl" + lang + os.sep + tail2

	if os.path.isdir(directory) == False:
		os.makedirs(directory)
		
	stdinFile = None;
	stdoutFile = None;
	stderrFile = None;

	if options.argVerbose != True:
		stdinFile = open(os.devnull);
		stdoutFile = open(os.devnull);
		stderrFile = open(os.devnull);

	returnCode = call([executable, '-in='+ByteCodeFileName, '-out='+directory+"/"+outputfilename, '-lang='+lang], stdin=stdinFile, stdout=stdoutFile, stderr=stderrFile)

	if returnCode == 1:
		failCount += 1
		listOfFailedTests.append(ByteCodeFileName)
	else:
		passCount += 1

	if options.argVerbose:
		print "\n"

if(options.argExecutableName):
	executable = options.argExecutableName
else:
	FindExecutable()

print "Using " + executable + "\n"

for files in glob.glob("vs2/*.o"):
	RunTest(files, "120")

for files in glob.glob("ps2/*.o"):
	RunTest(files, "120")

for files in glob.glob("ps3/*.o"):
	RunTest(files, "150")

for files in glob.glob("vs4/*.o"):
	RunTest(files, "330")

for files in glob.glob("ps4/*.o"):
	RunTest(files, "330")

for files in glob.glob("gs4/*.o"):
	RunTest(files, "330")

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

for files in glob.glob("cs5/*.o"):
	RunTest(files, "430")

print str(passCount) + " passed; " + str(failCount) + " failed.\n"
print "Failed tests:"
for testName in listOfFailedTests:
	print testName
