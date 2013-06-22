#!/bin/bash

INSTALL_DIR="./"

# Default directories
ERR_PATH="$INSTALL_DIR/output/out.log"
TEMP_PS2="$INSTALL_DIR/output/.graph.ps2"
PDF_OUT="$INSTALL_DIR/output/graph.pdf"
TEMP_DIR="$INSTALL_DIR/output/.graph.dot"

# Default apps
DELTA_COL="$INSTALL_DIR/deltaColoring"
DOT="dot"
PS2PDF="ps2pdf"
PDF="evince"

err_usage(){
	printf "\t\t\t\t[ \033[31mFAIL\033[0m ] - please see the $ERR_PATH for more details\n\n"
	cat $ERR_PATH
	exit
}

print_ok(){
	printf "[ \033[32mOK\033[0m ]\n"
}

printf "[ 1 ] Calling DeltaColoring"
if [ "$#" == 1 ]; then
	$DELTA_COL $1 2> $ERR_PATH > $TEMP_DIR
elif [ "$#" == 2 ]; then
	$DELTA_COL $1 $2 2> $ERR_PATH
	TEMP_DIR=$2
else
	$DELTA_COL 2> $ERR_PATH
	err_usage
fi

if [ $? == 0 ]; then
	printf "\t\t\t\t"
	print_ok
else
	err_usage
fi

printf "[ 2 ] Preparing pdf"
$DOT -Tps2 $TEMP_DIR > $TEMP_PS2
$PS2PDF $TEMP_PS2 $PDF_OUT

if [ "$#" == 1 ]; then
	rm $TEMP_DIR $TEMP_PS2
elif [ "$#" == 2 ]; then
	rm $TEMP_PS2
fi
printf "\t\t\t\t\t"
print_ok

printf "[ 3 ] Calling the $PDF with the output graph"
$PDF $PDF_OUT &
printf "\t\t"
print_ok

printf "\n"
cat $ERR_PATH
