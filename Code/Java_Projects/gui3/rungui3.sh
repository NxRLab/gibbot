#!/bin/bash
#git pull
cp ../imagefiles/* .
javac -d ./ -cp "../newserial/jssc-2.8.0.jar;gui3src" gui3src/GibbotGUI3.java
java -cp ".;../newserial/jssc-2.8.0.jar;" GibbotGUI3 $1
