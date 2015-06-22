#!/bin/bash

teams="Anaheim Boston Buffalo Calgary Carolina Chicago Colorado Columbus Dallas Detroit Edmonton Florida Angeles Minnesota Montreal Nashville Jersey Islanders Rangers Ottawa Philadelphia Phoenix Pittsburgh Jose Louis Tampa Toronto Vancouver Washington Winnipeg"

file=$1

echo "FILE $file"

fileText=`cat $file | sort -n | uniq | tail -100`
#echo "$fileText"


for team in $teams; do
    count=`echo $fileText | grep -o $team | wc -l`
    echo "$count $team"
done
