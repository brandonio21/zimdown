zimdown
=======

### zimdown is a ZIM to markdown conversion tool.
Originally, I created zimdown to turn my existing notes into notes that could
be easily read by the github markdown interpreter. I was looking for a way
to markdown my notes so that they could be written in vim with no problems 
whatsoever. Here is the result.

So far the process looks a little something like this
#### zimdown.c
1. Converts all syntax of a ZIM file into GFM (GitHub flavored markdown)

Currently, the following objects are converted:
* italics
* bold
* strikethrough
* headers
* images
* linebreak/formatting


Suggested call looks like
```
zimdown <zimFile> <mdFile>
```

####TODO
1. Add the -i flag (inverse) to allow for md->zim conversions
2. Completion of syntax, so all zim syntax can be converted
3. Add the -d flag (directory) to convert entire directories.
4. Add -h flag to produce HTML file zim->markdown->html


### To Compile zimdown
```
make
```
