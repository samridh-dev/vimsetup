let mapleader = " "

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""" Miscellaneous
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" J keeps cursor at beginning of file
nnoremap J mzJ`z

" Keeps cursor in middle when C^d and C^u
nnoremap <C-d> <C-d>zz
nnoremap <C-u> <C-u>zz

" Clear search highlighting
nnoremap <leader><space> :nohlsearch<CR><CR>

" Faster Scrolling
nnoremap <C-e> 4<C-e>
nnoremap <C-y> 4<C-y>

" Redo
nnoremap U <C-R>

" quickly execute macros
nnoremap Q @q

" Making :w, :q case insensitive
command! Q  q
command! W  w
command! WQ wq
command! Wq wq

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""" Yank/Paste
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Do not overwrite yank after paste
xnoremap <leader>p "_dP

" Does not overwrite yank buffer
nnoremap <leader>d "_d
vnoremap <leader>d "_d
nnoremap <leader>c "_c
vnoremap <leader>c "_c

" Yank to system clipboard
nnoremap <leader>y "+y
vnoremap <leader>y "+y
nnoremap <leader>Y "+Y

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""" Buffer Workflow
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Lists buffers and switch based on buffer index 
nnoremap <leader>b :buffers<CR>:buffer<space>

" Switch between buffers cyclicly
nnoremap <leader>. :bnext<CR>
nnoremap <leader>, :bprevious<CR>

" Switch to last buffer used
nnoremap <leader>/ <C-^>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""" Comments (Refer to comment.vim)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

nnoremap <leader>cb :call MakeCommentBar()<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""" End
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
