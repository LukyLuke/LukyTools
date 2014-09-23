# Small Helper Scripts 

Maybe usefull scripts and tools which will help you during the daily business.

## image2pdf

Convert a bunch of Images to a PDF. As default with a Color-Range of 32, but that's definable by a prepanding COLOR environment variable.
I use this to convert scanned Documents into a PDF.

`$ image2pdf FILE [FILE [...]] OUTPUT`

or with a give COLOR Range:

`$ COLORS=256 image2pdf FILE [FILE [...]] OUTPUT`