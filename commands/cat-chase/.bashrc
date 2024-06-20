function hideflag {
	[ "${#FUNCNAME[@]}" -gt 1 ] && return # only trigger on user input
	fold -s <<< "You used 'cd'! In this level, I don't allow you to change the working directory --- you MUST chase down the flag where I've put it on the filesystem. I'm going to re-hide it..."
	/challenge/.hide_flag
}

alias cd='hideflag; cd'
if [ -f /flag ] || [ "$DID_HIDE" != 1 ]
then
	DID_HIDE=1
	fold -s <<< "You cannot use the 'cd' command in this level, and must retrieve the flag by absolute path. But in this level, I'll put the flag in some crazy directory!"
	/challenge/.hide_flag
fi
