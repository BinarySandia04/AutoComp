#!/bin/bash

echo "Resetting... Please wait a while."

for i in {1..9}
do
	rm -r $i
	cp -r _contest_template $i
	echo -e "\\b-"
done

echo "Done."
sleep 1