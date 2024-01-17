
History
=======

I remember a portable Brother typewriter that had user defined tabs which were set
by a lever on the left hand side of the keyboard. 
Basically-

1. You spaced using the [*spacebar*] to where you wanted to set the tab stop.
2. You set the stop by pushing the lever to the **S** position.
3. Repeat until you have set all the required stops.

Returning the carriage to the left hand side you could tab to the first
tab stop using the **red** [*tab*] key (on the right hand side I recall.)
At any point on the line you pressed the [*tab*] key to move to the right to the next tab stop.
If you wanted to remove a tab stop you tabbed to that stop and pushed the left hand lever to the **C** position.

So as an example if you set the first tab in column 8

````c
# Reference line
1234567890123456789
        
-------^ space to here push lever to 'S'
````



````c
#  Return, press [tab], type 'A'       
1234567890123456789
        A
````

Note: the tab is set in column 8 but the next character 'A'
appears in column 9.

Mechanical Terminals
====================

Terminals were originally something like an electric typewriter and many, or most would have supported tabs is some form or other.
Some terminals supporting tabs presumably were user definable and some fixed (every 8 columns?)
Tabs I imagine were either set programatically (escape sequences) or from the keyboard.

CRT Terminals
============
Later terminals like the VT100 supported programatically set tabs in pretty much way as the typewriter described above.
The required escape sequence(s) can be retrieved from terminfo or termcap.

See pp 129-131 *Setting and Using Tabs* in 
	**terminfo & termcap**
	John Strang, Linda Mui & Tim O'Reilly
	O'Reilly & Associates 1988

The attribute is **hts** (terminfo) or **st** (termcap)
eg

````c
infocmp -T vt100 | grep -E -e '\<hts=[^,]*,' | sed -E -e 's/^.*\<(hts=[^,]*).*$/\1/'
hts=\EH
````

ie [*esc*]H 
Can confirm with tput 

````C
tput -T vt100 hts | od -a
0000000 esc   H
````
You can confirm the vt52 doesn't support **hts** but vt220, vte etc support same
sequence as do almost all the X11 terminal applications.

Example setting tabs
====================

----------------------------------------------------------------------------
````c
#! /bin/sh

# @(#) settabs - using the terminfo capabilities directly
# but in practice use /bin/tabs

# tab cap
hts=$(tput -T $TERM hts)
ruler() {
	local	n="$1"
	local	i
	for i in $(seq 1 $n);
	do
		local	digit=$((i%10))
		if [[ $digit = 0 ]]; then
			printf "|"
		else
			printf "%c" $digit
		fi
	done
	printf "\n"
}
tabs_clear() {
	tbc=$(tput -T $TERM tbc)
	printf "%s\r" "$tbc"
}
tabs_set() {
	local	i
	local	col=1
	for i in $@
	do
		while [[ $col -le $i ]]; do
			printf " "
			col=$((col+1))
		done
		printf "%s" "$hts"
	done
	printf "\r"
} 

ruler 55
tabs_clear
tabs_set 8 11 14
printf "A\tB\tC\tD\n"
----------------------------------------------------------------------------

./settabs
123456789|123456789|123456789|123456789|123456789|12345
A       B  C  D
````

To reset standard -8 tabs use
````C
	tput reset
````

Note: infocmp, tput and tabs are likely part of the ncurses package(s) on most Linux distros.
