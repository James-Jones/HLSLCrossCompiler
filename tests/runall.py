from subprocess import call
import os;

executable = "../bin/Debug/HLSLByteCodeToGLSLStandalone"

passCount = 0
failCount = 0

if os.path.isdir("results/glsl130") == False:
	os.makedirs("results/glsl130")

returnCode = call([executable, "vs4/mov.o", "results/glsl130/vs4mov.glsl", "130"])

if returnCode == 1:
	print "vs4/mov failed to compile"
	failCount += 1
else:
	passCount += 1

print str(passCount) + "passed; " + str(failCount) + " failed.\n"
