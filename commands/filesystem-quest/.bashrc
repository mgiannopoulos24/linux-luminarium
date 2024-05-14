#!/bin/bash

function hint_handler
{
	[ -f *-TRAPPED ] && echo "BOOM! This hint has self-destructed! You will need to restart the challenge to continue." > *-TRAPPED
	ls -d [A-Z][A-Z][A-Z]* 2>/dev/null | while read FILE
	do
		stat $FILE | grep -q "Access: .0000.*Uid:...1000" || continue
		chmod 644 $FILE
	done
}

trap hint_handler DEBUG
