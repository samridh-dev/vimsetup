colorscheme quiet

set background=dark

highlight Pmenu ctermfg=White ctermbg=Black guifg=White guibg=Black
highlight PmenuSel ctermfg=Black ctermbg=White guifg=Black guibg=White

" Change highlighting of cursor line when entering/leaving Insert Mode
set cursorline
highlight CursorLine 
        \ cterm=NONE ctermfg=NONE ctermbg=233 guifg=NONE guibg=#121212
autocmd InsertEnter * highlight CursorLine 
      \ cterm=NONE ctermfg=NONE ctermbg=234 guifg=NONE guibg=#1c1c1c
autocmd InsertLeave * highlight CursorLine 
      \ cterm=NONE ctermfg=NONE ctermbg=233 guifg=NONE guibg=#121212

