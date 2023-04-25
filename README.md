# Huffman Text Compressor

This is a text compression program that uses the Huffman coding algorithm to reduce the size of text files.

## How it Works
The Huffman coding algorithm works by creating a binary tree of symbols in the input text. Each leaf node in the tree represents a symbol and its frequency in the input text. The algorithm then assigns a binary code to each symbol based on its frequency, with the most frequent symbols getting shorter codes and the least frequent symbols getting longer codes.

To compress the input text, the algorithm reads the text character by character and replaces each symbol with its corresponding binary code. The binary codes are concatenated into a single bit stream, which is then written to the output file.

To decompress the compressed file, the algorithm reads the bit stream and follows the binary tree to decode each symbol.

## Performance

This program compresses text files to about 50% of their original size on average.

## Limitations
This implementation of the Huffman coding algorithm has the following limitations:

It only works with text files, that contain 0 - 127 ASCII codes.

It may not always produce a compressed file that is smaller than the original file.


### Note: This program is intended to be used on Unix-based operating systems.
