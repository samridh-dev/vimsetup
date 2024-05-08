let mapleader = " "

" Do not overwrite yank after paste
xnoremap <leader>p \"_dP

" Does not overwrite yank buffer
nnoremap <leader>d "_d
vnoremap <leader>d "_d
nnoremap <leader>c "_c
vnoremap <leader>c "_c

" Yank to system clipboard
nnoremap <leader>y \"+y
vnoremap <leader>y \"+y
nnoremap <leader>Y \"+Y

" J keeps cursor at beginning of file
nnoremap j mzJ`z

" Keeps cursor in middle when C^d and C^u
nnoremap <C-d> <C-d>zz
nnoremap <C-u> <C-u>zz

