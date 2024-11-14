#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Clean previous build
echo -e "${GREEN}Cleaning previous build...${NC}"
make clean

# Build the project
echo -e "${GREEN}Building project...${NC}"
make

# Check if build was successful
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Build successful! Running calculator...${NC}"
    echo -e "${GREEN}----------------------------------------${NC}"
    ./build/calculator
else
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi 