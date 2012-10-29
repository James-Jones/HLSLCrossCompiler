from subprocess import call
import os;
import glob;

executable = "../bin/Debug/HLSLByteCodeToGLSLStandalone"

passCount = 0
failCount = 0
listOfFailedTests = []

i = 0

def RunTest(ByteCodeFileName, lang):

	global failCount
	global passCount
	global listOfFailedTests

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
