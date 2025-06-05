#!/bin/bash

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_status() {
    echo -e "${BLUE}[BUILD]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Build configuration
BUILD_TYPE=${1:-Release}  # Default to Release, allow override with first argument
JOBS=${2:-$(nproc)}       # Use all CPU cores by default

print_status "Starting build process for No-Time-To-Fall"
print_status "Build type: $BUILD_TYPE"
print_status "Using $JOBS parallel jobs"

# Function to build a project
build_project() {
    local project_path=$1
    local project_name=$2
    
    print_status "Building $project_name..."
    
    if [ ! -d "$project_path" ]; then
        print_error "Directory $project_path does not exist!"
        return 1
    fi
    
    cd "$project_path"
    
    # Check if CMakeLists.txt exists
    if [ ! -f "CMakeLists.txt" ]; then
        print_error "CMakeLists.txt not found in $project_path"
        cd - > /dev/null
        return 1
    fi
    
    # Generate ninja files if they don't exist or if CMakeLists.txt is newer
    if [ ! -f "build.ninja" ] || [ "CMakeLists.txt" -nt "build.ninja" ]; then
        print_status "Generating ninja files for $project_name..."
        cmake -G Ninja -DCMAKE_BUILD_TYPE=$BUILD_TYPE .
        if [ $? -ne 0 ]; then
            print_error "Failed to generate ninja files for $project_name"
            cd - > /dev/null
            return 1
        fi
    else
        print_status "Ninja files for $project_name are up to date"
    fi
    
    # Build with ninja
    print_status "Running ninja for $project_name..."
    ninja -j $JOBS
    if [ $? -ne 0 ]; then
        print_error "Failed to build $project_name"
        cd - > /dev/null
        return 1
    fi
    
    print_success "$project_name built successfully"
    cd - > /dev/null  # Return to original directory silently
}

# Store original directory
ORIGINAL_DIR=$(pwd)

# Build Yuna/mfGUI first (dependency of Yuna)
build_project "Yuna/mfGUI" "Yuna/mfGUI"

# Copy mfGUI library to expected location for Yuna
print_status "Copying mfGUI library for Yuna..."
cp "Yuna/mfGUI/lib/libMFGUId.a" "Yuna/lib/libMFGUI.a"

# Build Yuna (depends on mfGUI)
build_project "Yuna" "Yuna"

# Build main game (depends on Yuna)
build_project "." "No-Time-To-Fall"

print_success "All projects built successfully!"
print_status "Build process completed in $(pwd)"

# Optional: Run the game if built successfully
if [ -f "No-Time-To-Fall" ] || [ -f "NoTimeToFall" ] || [ -f "game" ]; then
    echo ""
    read -p "Would you like to run the game? (y/N): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        print_status "Starting game..."
        # Try common executable names
        if [ -f "No-Time-To-Fall" ]; then
            ./No-Time-To-Fall
        elif [ -f "NoTimeToFall" ]; then
            ./NoTimeToFall
        elif [ -f "game" ]; then
            ./game
        else
            print_warning "Could not find game executable in current directory"
            ls -la
        fi
    fi
fi