# Milligram
A quadtree is a tree data structure where each internal node has exactly four children. It is primarily used to recursively divide a two-dimensional space into four quadrants. Using quadtree to encode bitmap images for usage in spatial analysis is common because it is convenient to code and follows a natural recursive order when compared to other algorithms. In this project we exploit the power of quadtree for encoding the marked frames of whiteboard lectures because of their simple color scheme. Lecture notes are rather simple because of limited colors in text as well as diagrams and no complex features like shadows and gradients.

## MOTIVATION

Online Education in the pandemic hasn’t been equally accessible across the society because of the high cost of internet services , lack of  availability of bandwidth etc. To send a large amount of data for study material (Video lectures being of more importance) to the remotest part of the country, it’s required to bring down the cost of transmission while upping the efficiency in the transmission of data. We aim to help in one such aspect of the problem by reducing the size of the video lectures by means of video encoding. One such way for doing it efficiently is through the use of Quad Trees.

## Morton Raster Scan:
Morton scanning of raster data is one of the many methods under Direct reaster coding.
Direct encoding is to treat raster data as a data matrix and record the code row by row (or column by column). Each row can be recorded from left to right, or even rows can be recorded from left to right, even rows can also be recorded from right to left, and other special orders can be used for special purposes. In the encoding schema the image is divided into blocks which are traversed and further subdivided using this method.



