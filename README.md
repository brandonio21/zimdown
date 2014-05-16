zimdown
=======

### zimdown is a ZIM to markdown conversion tool.
Originally, I created zimdown to turn my existing notes into notes that could
be easily read by the github markdown interpreter. I was looking for a way
to markdown my notes so that they could be written in vim with no problems 
whatsoever. Here is the result.

So far the process looks a little something like this
#### zimdown.c
1. Copies all files/folders to the specified new directory
2. Converts all files to markdown (from zim)


Suggested call looks like
```
zimdown <zimDirectory> <proposedMarkdownDirecctory>
```
