# Essential Shell Commands (brief)

Note: Options may vary slightly by system (GNU vs BSD).

`exit`
- Purpose: Exit the current shell or script.
- Usage: `exit [N]` — return status `N` (default: last command).

`man`
- Purpose: Read manual pages.
- Usage: `man [section] name`
- Common: `-k` search (like apropos), `-f` whatis, `-P` set pager.

`apropos`
- Purpose: Search man page names/descriptions.
- Usage: `apropos pattern`
- Common: `-e` exact match, `-w` word match, `-r` regex, `-a` AND patterns.

`pwd`
- Purpose: Print working directory.
- Usage: `pwd`
- Common: `-L` logical (respects symlinks), `-P` physical (resolves symlinks).

`ls`
- Purpose: List directory contents.
- Usage: `ls [options] [path...]`
- Common: `-l` long, `-a` all, `-h` human sizes, `-R` recursive, `-t` sort time, `-S` sort size, `-1` one per line.

`cd`
- Purpose: Change directory.
- Usage: `cd [dir]`
- Tips: `-` previous dir, `..` parent, `~` home; `-P` physical path.

`cp`
- Purpose: Copy files/directories.
- Usage: `cp [options] SRC... DEST`
- Common: `-r`/`-R` recursive, `-a` archive (preserve attrs, recursive), `-i` prompt, `-n` no-clobber, `-u` update, `-v` verbose, `-p` preserve mode/owner/times.

`mv`
- Purpose: Move or rename files/directories.
- Usage: `mv [options] SRC... DEST`
- Common: `-i` prompt, `-n` no-clobber, `-u` update if newer, `-v` verbose.

`rm`
- Purpose: Remove files/directories.
- Usage: `rm [options] FILE...`
- Common: `-r` recursive, `-f` force (no prompt), `-i` prompt, `-d` remove empty dir. Irreversible.

`cat`
- Purpose: Print or concatenate files.
- Usage: `cat [options] [FILE...]`
- Common: `-n` number lines, `-A` show all (incl. non-printing), `-E` show ends, `-T` show tabs.

`head`
- Purpose: Show first lines of files.
- Usage: `head [-n N|-c N] [FILE...]` (default 10 lines)

`tail`
- Purpose: Show last lines of files.
- Usage: `tail [-n N|-c N] [FILE...]`
- Common: `-f` follow, `-F` follow and retry if rotated.

`less`
- Purpose: Pager to view text interactively.
- Usage: `less [options] FILE`
- Common: `-N` line numbers, `-S` cut long lines, `-R` show colors; keys: `/` search, `n` next, `q` quit.

`more`
- Purpose: Basic pager.
- Usage: `more [options] FILE`
- Common: Space next page, `q` quit; fewer features than `less`.

`clear`
- Purpose: Clear terminal screen.
- Usage: `clear`

`history`
- Purpose: Show/manage shell history (builtin).
- Usage: `history [n]`
- Common (bash): `-c` clear, `-d N` delete entry, `-a` append session, `-r` read file; `!N` run entry N, `!-N` relative.

`grep`
- Purpose: Search text with patterns (regex).
- Usage: `grep [options] PATTERN [FILE...]`
- Common: `-i` ignore case, `-R` recursive, `-n` line numbers, `-v` invert match, `-E` extended regex, `-F` fixed strings, `-w` word match, `--color=auto` highlight.

`test latex`
$$ \frac{-b \pm \sqrt{b^2-4ac}}{2a} $$