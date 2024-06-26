" This is mupdf specific. To make this more portable, think about what should
" this do.
command! ViewPdf :silent !mupdf out/main.pdf &

nnoremap <silent><leader>ll :Make<CR>
nnoremap <leader>ls :ViewPdf<CR>
