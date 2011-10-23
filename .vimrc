autocmd FileType make set noexpandtab " Use tabs instead of spaces, otherwise `make` will hate you
set expandtab " Use spaces instead of tabs
set tabstop=4 " set tabstop to 2 spaces
set shiftwidth=4 " make >> and friends (<<, ^T, ^D)  shift 2, not 8
set shiftround " round to nearest n, don't just move n
