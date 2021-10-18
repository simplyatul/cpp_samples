# This script greps following pattern in a given file 
# and then executes the binary a.out
# run: <compilation command>
# e.g. 
# run: g++ hello.cpp

# $1 => filename to compile and execute
# grep 'run:' $1 | awk -F":" '{print $NF}' | sh - && ./a.out
CMD=`grep 'run:' $1 | awk -F":" '{print $NF}'`
[ -z "$CMD" ] && echo "Command to compile not found. Existing." && exit 1
RUN_CMD="$CMD && ./a.out"
echo $RUN_CMD
eval "$RUN_CMD"
#sh -c "$RUN_CMD" && ./a.out

