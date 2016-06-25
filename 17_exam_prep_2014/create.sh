#!/bin/bash 

printf "project number: "
read NAME

mkdir $NAME
cp template/template.ino $NAME/$NAME.ino
cp template/TEMPLATE.nsd $NAME/$NAME.nsd
