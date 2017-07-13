/* Assignment 6: Huffman
 * Build a file compression algorithm that uses binary trees and priority queues.
 * This is the code to perform Huffman encoding and decoding.
 * @Author: Cong Chen
 * @Version: 2017/07
 */


#include "encoding.h"
#include <limits>
#include "pqueue.h"

// This is the recursion helper function for traversing the tree
void buildEncodingMap(HuffmanNode *encodingTree, Map<int, string>& encodingMap, string bits);

Map<int, int> buildFrequencyTable(istream& input) {
    /* Count and return a mapping from each character (represented as int here) to the number of times that character appears.
     * Also add a single occurrence of the fake character PSEUDO_EOF */
    Map<int, int> freqTable;
    while(true) {
        int byteIn = input.get();
        if (byteIn == EOF) {
            byteIn = PSEUDO_EOF;
            break;
        } else if (byteIn > numeric_limits<char>::max())
            byteIn = NOT_A_CHAR;

        if (freqTable.containsKey(byteIn))
            freqTable[byteIn]++;
        else
            freqTable.put(byteIn,1);
    }
    freqTable.put(PSEUDO_EOF,1);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    /* Create a Huffman encoding tree based on the freqTable, return a pointer to the node representing the root of the tree.
     * Use the PriorityQueue collection provided by the Stanford libraries, defined in library header pqueue.h */

    // Build the PriorityQueue from the map
    PriorityQueue<HuffmanNode> EncodingTree;
    Vector<int> keys = freqTable.keys();
    HuffmanNode* newOne;
    for (int i=0;i<keys.size();i++) {
        newOne = new HuffmanNode(keys[i],freqTable[keys[i]]);
        EncodingTree.enqueue(*newOne,freqTable[keys[i]]);
    }

    /* Repeatedly removes the two nodes from the front of the queue
     * and joins them into a new node whose frequency is their sum.
     * The two nodes are placed as children of the new node;
     * the first removed becomes the left child, and the second the right.
     * The new node is re-inserted into the queue in sorted order.
     * This process is repeated until the queue contains only one binary tree node
     * with all the others as its children. */
    while(EncodingTree.size()>1){
        HuffmanNode *left = new HuffmanNode();
        HuffmanNode *right = new HuffmanNode();
        *left  = EncodingTree.dequeue();
        *right = EncodingTree.dequeue();
        int newCount = left->count+right->count;
        newOne = new HuffmanNode(NOT_A_CHAR,newCount,left,right);
        EncodingTree.enqueue(*newOne,newCount);
    }
    *newOne = EncodingTree.peek();
    return newOne;
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    /* Create and return a Huffman encoding map based on the tree's structure.
       Each key in the map is a character, and each value is the binary encoding for that character represented as a string.*/
    Map<int, string> encodingMap;
    buildEncodingMap(encodingTree,encodingMap,"");
    return encodingMap;
}

void buildEncodingMap(HuffmanNode *encodingTree,Map<int, string>& encodingMap, string bits) {
    // Recursion helper
    if (encodingTree->isLeaf()) {
        encodingMap.put(encodingTree->character,bits);
    } else {
        buildEncodingMap(encodingTree->zero,encodingMap,bits+"0");
        buildEncodingMap(encodingTree->one,encodingMap,bits+"1");
    }
}


void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    /* Read one character at a time from a given input file, and use the provided encoding map to encode each character to binary,
     * then write the character's encoded binary bits to the given bit output bit stream.
     * After writing the file's contents, write a single occurrence of the binary encoding for PSEUDO_EOF into the output
     * so that the end of the data could be indentified when decompressing the file later. */
    string bits;
    int byteIn;
    while(true) {
        byteIn = input.get();
        if (byteIn == EOF) {
            byteIn = PSEUDO_EOF;
            break;
        } else if (byteIn > numeric_limits<char>::max())
            byteIn = NOT_A_CHAR;

        bits += encodingMap[byteIn];
    }
    bits += encodingMap[byteIn];
    for (int i=0;i<bits.size();i++) {
        int bit;
        if (bits[i]==stringToChar("1") )
            bit =1;
        else
            bit =0;
        output.writeBit(bit);
    }

}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    /* Read bits from the given input file one at a time, and recursively walk through the specified Huffman tree,
     * Stop until a leaf node was hit. Then go back to the root, traverse the tree again from the previous stop position of the input bitstream.
     * So to write the original uncompressed contents of that file to the given output stream. */
    int order;
    HuffmanNode* hole = new HuffmanNode();
    hole = encodingTree;
    while(true) {
        order = input.readBit();
        if (order == -1) break;

        if (order == 0 )
            hole = hole->zero;
        else
            hole = hole->one;

        if(hole->isLeaf()) {
            output.put(hole->character);
            if(hole->character == PSEUDO_EOF) break;
            hole = encodingTree;
        }

    }

}

void compress(istream& input, obitstream& output) {
    /* Compress the given input file into the given output file.
     * Parameters: an input file that should be encoded, an output bit stream to which the compressed bits of that input file should be written.
     */

    //building an encoding of its contents
    Map<int, int> freqMap =  buildFrequencyTable(input);
    HuffmanNode* EncodingTree = new HuffmanNode();
    EncodingTree = buildEncodingTree(freqMap);
    Map<int, string> EncodingMap = buildEncodingMap(EncodingTree);
    //Write the map of character frequency to the ouput stream as header.
    output << freqMap;
    //Write a compressed version of the input file to the output
    rewindStream(input); //!!! Tells the stream to seek back to the beginning !!!!
    encodeData(input, EncodingMap, output);
    // Free the tree memory
    freeTree(EncodingTree);
}

void decompress(ibitstream& input, ostream& output) {
    /* Read the bits from the given input file one at a time, including the header, and decoding it.
     * Then write the original contents of that file to the output. */

    // Read the header and generate the encoding tree from the read in frequency map.
    Map<int, int> freqMap;
    input >> freqMap;
    HuffmanNode* EncodingTree = new HuffmanNode();
    EncodingTree = buildEncodingTree(freqMap);
    //Decoding
    decodeData(input, EncodingTree, output);
    // Free the tree memory
    freeTree(EncodingTree);
}

void freeTree(HuffmanNode* node) {
    /* Free the memory associated with the tree whose root node is represented by the given pointer.
     * Free the root node and all nodes in its subtrees. There should be no effect if the tree passed is NULL. */
    if (node!=NULL) {
        if (node->isLeaf()) {
            delete node;
        } else {
            freeTree(node->zero);
            freeTree(node->one);
        }
    }
}
