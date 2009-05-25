PATH=c:\lcc\bin;%PATH
lcc -DMSDOS -c -O opendir.c
lcc -DMSDOS -c -O closedir.c
lcc -DMSDOS -c -O readdir.c
lcc -c -O strncmpi.c
lcc -DMSDOS -DLESSTIF -DDISABLE_ZCATS -c -O man2html.c
lcclnk -o man2html.exe man2html.obj opendir.obj closedir.obj readdir.obj strncmpi.obj
copy man2html.exe man2html.cgi
