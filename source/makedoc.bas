' makedoc.bas
' convert markup into HTML documentation
'
' Markup Grammar
'
'   _word               word is rendered in italics
'   .chapter title      start of chapter with title "title"
'   .section title      start of section with title "title"
'   .subsection title   start of subsection with title "title"
'   .code               start of code section
'   .endcode            end of code section
'                       blank lines indicate paragraph breaks
'   .list               start of list section
'   .item               list item
'   .endlist            end of list
'   .note               start of note
'   .endnote            end of note
'
' Except in [code] blocks, spacing is ignored
' [...] constructs are the first commands on a line
