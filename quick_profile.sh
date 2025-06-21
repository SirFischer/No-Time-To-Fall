#!/bin/bash
set -e

echo "🔧 Building with gprof profiling using existing build system..."

# Use your existing build script but ensure Debug mode
export CMAKE_BUILD_TYPE=Debug

# Build using your existing build.sh
./build.sh

echo ""
echo "🎮 Starting game for profiling..."
echo "   → Play the game for 30-60 seconds to get meaningful data"
echo "   → Move around, test different game features"
echo "   → Close the game normally (don't force quit)"
echo ""
echo "Press Enter to start..."
read

# Run the game
./No-Time-To-Fall

# Check if profiling data was generated
if [ -f gmon.out ]; then
    echo ""
    echo "📊 Generating gprof report..."
    
    # Generate full report
    gprof ./No-Time-To-Fall gmon.out > gprof_report.txt
    
    echo "📈 === TOP FUNCTIONS BY TIME ==="
    gprof ./No-Time-To-Fall gmon.out | head -25
    
    echo ""
    echo "📈 === CALL GRAPH SUMMARY ==="
    gprof ./No-Time-To-Fall gmon.out | grep -A 30 "Call graph" | head -30
    
    echo ""
    echo "✅ Complete gprof report saved to: gprof_report.txt"
    echo ""
    echo "📖 Useful gprof commands:"
    echo "   View flat profile:    gprof ./No-Time-To-Fall gmon.out | head -30"
    echo "   View call graph:      gprof ./No-Time-To-Fall gmon.out | grep -A 100 'Call graph'"
    echo "   Full report:          less gprof_report.txt"
    echo "   Functions only:       gprof ./No-Time-To-Fall gmon.out | grep -E '^[ ]*[0-9]'"
    
else
    echo "❌ No gmon.out file found!"
    echo ""
    echo "Troubleshooting:"
    echo "1. Make sure you built with Debug mode (has -pg flags)"
    echo "2. Let the game run for at least 15-30 seconds"
    echo "3. Close the game normally (don't kill the process)"
    echo "4. Check if gprof is installed: which gprof"
fi
