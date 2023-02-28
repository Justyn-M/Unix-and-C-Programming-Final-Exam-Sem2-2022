#!/bin/bash

grep -E "08:[5][3-9]:[0-5][0-9]" log.txt | grep -E -o "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)"

# first grep searches for lines that has a time of after 08:53:00 and before 08:59:59 
# second grep searches for IP addresses in the lines found by the first grep
# 2nd grep searches only for IP addresses that have integers from 0 - 225, in other words, only valid IP addresses