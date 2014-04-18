#!/bin/bash

../release/Roop -p > keywords.txt
python generate-pattern.py keywords.txt > ../ide/RoopIDE/syntaxkeywords.cpp
