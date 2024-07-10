" Function: MakeCommentBar
" Purpose: Creates a customizable comment bar based on filetype.
" Details: Constructs a comment line that includes a prefix, a body pattern
"          repeated to fit within a column limit, and a suffix.
" Usage: The comment bar adapts to the filetype of the currently edited file,
"        useful for adding structured comments.

function! MakeCommentBar()

  let patterns = {
        \  'c'      :    ['/*', '-', '*/'],
        \  'cpp'    :    ['/*', '-', '*/'],
        \  'vim'    :    ['"',  '"', '"'],
        \  'python' :    ['#', '-', '#'],
        \  'sh'     :    ['#', '-', '#'],
        \  'txt'     :   ['#', '-', '#'],
        \  'tex'    :    ['%', '-', '%'],
        \  }
  let pattern = get(patterns, &filetype, ['','',''])
  if pattern == ['','','']
    return
  endif

  let column_limit = 79

  let prefix = pattern[0]
  let body   = pattern[1]
  let suffix = pattern[2]

  let prefix_len = len(prefix)
  let suffix_len = len(suffix)

  let body_len = column_limit - prefix_len - suffix_len - 2
  if len(body) > 0
    let body_len = body_len / len(body)
  endif

  let line = prefix . " " . repeat(body, body_len) . " " . suffix

  execute  "normal! i" . line . "\<Esc>"

endfunction

" Function: MakeCommentHeader1
" Purpose: Generates a level 1 comment header based on filetype.
" Details: The header uses the primary comment symbol of the filetype to
"          create a line that spans the full width.
" Usage: This function can be used to insert decorative or section-dividing
"        comments in code.
function! MakeCommentHeader1()

  let patterns = {
        \  'c'      :    '/',
        \  'cpp'    :    '/',
        \  'vim'    :    '"',
        \  'python' :    '#',
        \  'sh'     :    '#',
        \  'tex'    :    '%'
        \  }
  let pattern = get(patterns, &filetype, '')
  if pattern == ''
    return
  endif

  let column_limit = 79

  let line = repeat(pattern, column_limit)
  let prefix = repeat(pattern, 3)
  let suffix = repeat(pattern, 3)

  let prefix_len = len(prefix)
  let suffix_len = len(suffix)
  
  set formatoptions-=cro
  execute "normal! g0i" .
        \ prefix . " " . "\<Esc>" .
        \ "g$a" .
        \ repeat(' ', column_limit - col('$') - suffix_len - prefix_len) . 
        \ suffix . "\<Esc>" .
        \ "O"  . line . "\<Esc>" .
        \ "jo" . line . "\<Esc>"
  set formatoptions+=cro


endfunction


" Function: MakeCommentHeader2
" Purpose: Generates a level 2 comment header based on filetype.
" Details: The header uses the primary comment symbol of the filetype to
"          create a line that spans the full width. This is used for
"          subsections within a code.
" Usage: This function can be used to insert decorative or section-dividing
"        comments in code.
function! MakeCommentHeader2()

  let patterns = {
    \  'c'      :    ['/*' , '-' , '*/'],
    \  'cpp'    :    ['/*' , '-' , '*/'],
    \  'vim'    :    ['"'  , '-' , '"'],
    \  'python' :    ['#'  , '-' , '#'],
    \  'sh'     :    ['#'  , '-' , '#'],
    \  'tex'    :    ['%'  , '-' , '%'],
    \  }
  let pattern = get(patterns, &filetype, ['', '', ''])
  if pattern == ['','','']
    return
  endif

  let column_limit = 79

  let prefix = pattern[0]
  let body = pattern[1]
  let suffix = pattern[2]

  let prefix_len = len(prefix)
  let suffix_len = len(suffix)

  let body_len = column_limit - prefix_len - suffix_len - 2
  if len(body) > 0
    let body_len = body_len / len(body)
  endif

  let line = prefix . " " . repeat(body, body_len) . " " . suffix

  set formatoptions-=cro
  execute "normal! g0i" .
        \ prefix . " " . "\<Esc>" .
        \ "g$a" .
        \ repeat(' ', column_limit - col('$') - suffix_len - prefix_len) . 
        \ suffix . "\<Esc>" .
        \ "O"  . line . "\<Esc>" .
        \ "jo" . line . "\<Esc>"
  set formatoptions+=cro

endfunction

" Function: MakeCommentHeader2
" Purpose: Generates a level 3 comment header based on filetype.
" Details: The header uses the primary comment symbol of the filetype to
"          create a line that spans the full width. This is used for
"          subsections within subsections in a code.
" Usage: This function can be used to insert decorative or section-dividing
"        comments in code.
function! MakeCommentHeader3()

  let patterns = {
    \  'c'      :    ['/*' , '-' , '*/'],
    \  'cpp'    :    ['/*' , '-' , '*/'],
    \  'vim'    :    ['"'  , '-' , '"'],
    \  'python' :    ['#'  , '-' , '#'],
    \  'sh'     :    ['#'  , '-' , '#'],
    \  'tex'    :    ['%'  , '-' , '%'],
    \  }
  let pattern = get(patterns, &filetype, ['', '', ''])
  if pattern == ['','','']
    return
  endif

  let column_limit = 79

  let prefix = pattern[0]
  let body = pattern[1]
  let suffix = pattern[2]

  let prefix_len = len(prefix)
  let suffix_len = len(suffix)

  set formatoptions-=cro
  execute "normal! g0i" .
        \ prefix . " " . "\<Esc>" .
        \ "g$a " .
        \ repeat('-', column_limit - col('$') - suffix_len - prefix_len - 2) . 
        \ " " . suffix . "\<Esc>"
  set formatoptions+=cro

endfunction

" Function: FormatBoundComment
" Purpose: Formats a comment according to specific boundaries defined by the
"          column limit and comment syntax for different file types.
" Details: This function dynamically adjusts a line of code to fit within a
"          set column limit by ensuring the suffix is correctly placed at or
"          before the column limit.
" Usage: Can be used to automatically reformat comments in code to maintain a
"        uniform style and length.
function! FormatBoundComment()

  let patterns = {
    \  'c'      :    ['/*' , '-' , '*/'],
    \  'cpp'    :    ['/*' , '-' , '*/'],
    \  'vim'    :    ['"'  , '-' , '"'],
    \  'python' :    ['#'  , '-' , '#'],
    \  'sh'     :    ['#'  , '-' , '#'],
    \  'tex'    :    ['%'  , '-' , '%'],
    \  }
  let pattern = get(patterns, &filetype, ['', '', ''])
  if pattern == ['','','']
    return
  endif

  let column_limit = 79
  
  let prefix = pattern[0]
  let body = pattern[1]
  let suffix = pattern[2]

  let prefix_len = len(prefix)
  let suffix_len = len(suffix)

  let target_column = column_limit - suffix_len
  if target_column <= 0
    return
  endif

  execute "normal! g$" . target_column . "|\"_d$" . 
        \ "A" . " " . suffix . "\<Esc>"
  
endfunction
