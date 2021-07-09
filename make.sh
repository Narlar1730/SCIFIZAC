#!/bin/bash

clear
echo "Cleaning the directory"
rm scifizac
echo "Making"
make
echo "Running"
./scifizac
