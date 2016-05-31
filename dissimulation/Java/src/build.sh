#!/bin/sh

javac kgms/*.java kgms/*/*.java
jar cfe dissimulate.jar kgms.Dissimulate kgms/*.class kgms/*/*.class
