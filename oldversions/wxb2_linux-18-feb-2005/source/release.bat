del *.td?
del *.il?
del *.obj

del a.out
del *.o

\bin\upx wxbasic.exe

deltree release

mkdir release
mkdir release\bin
mkdir release\doc
mkdir release\demos
mkdir release\source

copy *.* release
cd release

move wxbasic.exe    bin
move wxbasic.exe.manifest bin

move log            doc
move fixme          doc
move wxbasic.rtf    doc
move lgpl.txt       doc

move minimal.wxb    demos
move bind.wxb       demos
move freecell.wxb   demos
move cards.png      demos
move ide.wxb        demos
move ide_tips.txt   demos
move mines.wxb      demos
move mines.png      demos
move scribble.wxb   demos
move markov.wxb     demos
move emcty10.txt    demos

move *.*            source
cd source
move bin ..
move doc ..
move demos ..
cd ..
cd ..
