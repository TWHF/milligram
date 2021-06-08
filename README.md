# Milligram
A quadtree is a tree data structure where each internal node has exactly four children. It is primarily used to recursively divide a two-dimensional space into four quadrants. Using quadtree to encode bitmap images for usage in spatial analysis is common because it is convenient to code and follows a natural recursive order when compared to other algorithms. In this project we exploit the power of quadtree for encoding the marked frames of whiteboard lectures because of their simple color scheme. Lecture notes are rather simple because of limited colors in text as well as diagrams and no complex features like shadows and gradients.

## Motivation

Online Education in the pandemic hasn’t been equally accessible across the society because of the high cost of internet services , lack of  availability of bandwidth etc. To send a large amount of data for study material (Video lectures being of more importance) to the remotest part of the country, it’s required to bring down the cost of transmission while upping the efficiency in the transmission of data. We aim to help in one such aspect of the problem by reducing the size of the video lectures by means of video encoding. One such way for doing it efficiently is through the use of Quad Trees.

## Morton Raster Scan:
Morton scanning of raster data is one of the many methods under Direct raaster coding.
Direct encoding is to treat raster data as a data matrix and record the code row by row (or column by column). In the encoding schema the image is divided into blocks which are traversed and further subdivided using this method.

##Encoding scheme:
First, we divide the image blocks of defined block size which are to be encoded 
The block encoding only saves information for all the black sub divisions in the image. :
If block is white -> return nothing
If block is black -> calculate and return opcode
The main difference of the code from normal quad trees appears at this step of the process:
Instead of using a tree data structure, a stack is used to implement quadtree subdivision.
The block is subdivided into four sub-blocks which are pushed into the stack.
Then we recurse through the contents of the stack subdividing till we either reach a black block or the threshold.
Opcodes for each encoded block are separated by a 000 to signal a white block or end of block

## Decoding Scheme:

The decoding of the image is relatively easier as it just has to track all the black blocks through the opcodes and mark them as balck or 1.
We start with a blank white image in which all the black blocks will be marked. A 2D matrix filled with 0 is the blank image
We go through the linear bool vector that is the stream of all the opcodes combined.
The first 3 bits of the code are converted to decimal to find out the number of subdivisions and the size of morton code in following bits which is 2*(value of 3 bits).
Using the morton codes the top left corner of the block to be marked black is obtained.
Then the last 7 bits of the opcode tell the size of the current block to be turned which is marked as 1.
The process is repeated for every 64 bit block and the image is restored.



