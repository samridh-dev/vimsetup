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

" Set make to save and make program silently
autocmd FileType * command! 
      \ -bar Make execute 'silent w' | silent make | redraw!
nnoremap <leader>m :Make<CR>

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
" Note: This is very Hacky. Do revise this implementation
function! SystemClipboardSetup()

  if !empty($WAYLAND_DISPLAY)
    " Wayland system
    nnoremap <silent> <leader>y :call system('wl-copy', @")<CR>
    xnoremap <silent> <leader>y :w !wl-copy<CR><CR>
       
  else
    " Other systems
    nnoremap <leader>y "*y
    vnoremap <leader>y "*y
    
  endif
endfunction

call SystemClipboardSetup()

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
""" Quickfix List
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Open and close quickfix
nnoremap <leader>co :copen<CR>
nnoremap <leader>cq :cclose<CR>

" Next and previous error
nnoremap <leader>c. :cnext<CR>
nnoremap <leader>c, :cprev<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""" Comments (Refer to comments.vim)
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

nnoremap <leader>cb :call MakeCommentBar()<CR>

" TODO: make this faster
nnoremap <leader>ch   :call MakeCommentHeader1()<CR>
nnoremap <leader>chh  :call MakeCommentHeader2()<CR>
nnoremap <leader>chhh :call MakeCommentHeader3()<CR>

nnoremap <leader>cf :call FormatBoundComment()<CR>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""" End
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
