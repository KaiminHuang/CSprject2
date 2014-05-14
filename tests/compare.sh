#! /usr/bin/env bash

cd ../client
make

rm -f ../tests/temp/expected.txt
rm -f ../tests/temp/output.txt

pwd

for i in $(cat ../tests/temp/url.txt); do
	OUTPUT=$(./run-client localhost 12345 $i 80)
    content="$(curl -i "$i")"
    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" >> ../tests/temp/output.txt
    echo ">>>Test $i" >> ../tests/temp/output.txt
    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" >> ../tests/temp/output.txt

    echo "$OUTPUT" >> ../tests/temp/output.txt

    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" >> ../tests/temp/expected.txt
    echo ">>>Test $i" >> ../tests/temp/expected.txt
    echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" >> ../tests/temp/expected.txt

    echo "$content" >> ../tests/temp/expected.txt
done

vim -d ../tests/temp/expected.txt ../tests/temp/output.txt