/**
 * This program creates a simple "hash" of
 * a person's name. A hash is an integer that is
 * mathematically derived from another object.
 * In this case, a string (the first and last name)
 * is accessed character by character and the hash
 * is built up from a number generated by each character.
 * While this function does not necessarily produce
 * unique hashes (different names can hash to the
 * same value), there is a relatively low possibility
 * of a "collision" with a class of roughly 400 students.
 *
 * We will learn more about hashing later this quarter!
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"  // for getLine
#include "grid.h"
#include "vector.h"
#include "queue.h"
#include "stack.h"
#include "filelib.h"
#include <fstream>
using namespace std;

/* Prototype for the nameHash function. This lets us use the function
 * in main and then define it later in the program.
 */
int nameHash(string first, string last);
void mirror(Grid<int>& matrix);
int crossSum(const Grid<int>& g, int rowInd, int colInd);
Grid<int> m = {{1,2,3},{4,5,6},{7,8,9}};
Vector<int> vec = {1,2,3,4,5};
void removeConsecutiveDuplicates(Vector<int>& v);
void switchPairs(Vector<int>& v);
void reorder(Queue<int>& q);
void inputStats(string s);
int checkBalance(string s);



int main() {

    cout << checkBalance("if (a(4) > 9) {foo(a(2));}") << endl;
    cout << checkBalance("for(i=0;i&lt;a(3};i++{foo{0;)") << endl;
    cout << checkBalance("if (x) {") << endl;

    return 0;
}

/* This is the actual function that computes the hash code. We're going
 * to talk more about what hash functions do later in the quarter. In
 * the meantime, think of it as a function that scrambles up the characters
 * of the input and produces a number.
 *
 * For those of you who are more mathematically inclined, this function
 * treats each character in the input name as a number between 0 and 128.
 * It then uses them as coefficients in a polynomial over the finite field
 * F_p, where p is a large prime number, and evaluates that polynomial at
 * some smaller prime number q. (You aren't expected to know this for CS106B,
 * but we thought it might be fun!)
 */
int nameHash(string first, string last){
    /* This hashing scheme needs two prime numbers, a large prime and a small
     * prime. These numbers were chosen because their product is less than
     * 2^31 - kLargePrime - 1.
     */
    static const int kLargePrime = 16908799;
    static const int kSmallPrime = 127;

    int hashVal = 0;

    /* Iterate across all the characters in the first name, then the last
     * name, updating the hash at each step.
     */
    for (char ch: first + last) {
        /* Convert the input character to lower case. The numeric values of
         * lower-case letters are always less than 127.
         */
        ch = tolower(ch);
        hashVal = (kSmallPrime * hashVal + ch) % kLargePrime;
    }
    return hashVal;
}


void mirror(Grid<int>& board){
    int col = board.numCols();
    int row = board.numRows();

    Vector<int> elements;

    for(int r = row-1; r >= 0 ; r--){
        for(int c = col-1; c >= 0; c--){
            elements.insert(0,board[r][c]);
        }
    }

    board.resize(col, row);

   for(int c2 = 0; c2 < row; c2++){
        for(int r2 = 0; r2 < col; r2++){
            board[r2][c2] = elements[0];
            elements.remove(0);
        }
    }
}


int crossSum(const Grid<int>& g, int rowInd, int colInd){
    //int rowSum = 0;
    //int colSum = 0;
    int rowSum;
    int colSum;


    for (int i = 0; i < g.numCols(); i++) {
        rowSum += g[rowInd][i];
    }

    for (int j = 0; j < g.numRows(); j++) {
        colSum += g[j][colInd];
    }

    int sum = rowSum + colSum - g[rowInd][colInd];

    return sum;
}


void removeConsecutiveDuplicates(Vector<int>& v ){
    for (int i = v.size()-1; i > 0; i--){
        if (v[i] == v[i-1]) {
            v.remove(i);
        }
    }
}


void switchPairs(Vector<int>& v){
    for (int i = 0; i < v.size()-1; i += 2) {
        int temp = v[i+1];
        v[i+1] = v [i];
        v[i] = temp;
    }
}

void inputStats(string s){
    ifstream infile;
    infile.open(s);
    Vector<int> wordCount;
    int sum = 0;
    int longest = 0;

    string line;
    while (getline(infile, line)){
        wordCount.add(line.size());
    }

    if (!wordCount.isEmpty()){
        for (int i = 0; i < wordCount.size(); i++){
            cout << "Line " << i + 1 << " has " << wordCount[i] << " chars" << endl;
            sum += wordCount[i];
            if (wordCount[i] >= longest){
                longest = wordCount[i];
            }
        }

        cout << wordCount.size() << " lines; longest = " << longest << ", average = " << double(sum/wordCount.size()) << endl;

    }

    }


void reorder(Queue<int>& q){
    Stack<int> s;
    int size = q.size();
    for (int i = 0; i < size; i++){
        int n = q.dequeue();
        if (n < 0){
            s.push(n);
        } else {
            q.enqueue(n);
        }
    }

    int size_positive = q.size();
    int size_negative = s.size();
    for (int j = 0; j < size_negative; j++){
        q.enqueue(s.pop());
    }

    for (int k = 0; k < size_positive; k++){
        q.enqueue(q.dequeue());
    }

}


int checkBalance(string s){

    Stack<char> st;
    for (int i = 0; i < s.size(); i++){
        if (s[i] == '{' || s[i] == '('){
            st.push(s[i]);
        }

        if (s[i] == '}' || s[i] == ')'){
            if (st.isEmpty()){
                return i;
            } else if ((s[i] == '}' && st.peek() != '{') || (s[i] == ')' && st.peek() != '(')){
                return i;
            } else {
                st.pop();
            }
        }

    }

    if (!st.isEmpty()){
        return s.size();
    }

    return -1;
}

