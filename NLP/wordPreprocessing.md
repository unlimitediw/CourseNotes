## Word Embedding
> Introduction
* Word embeddings provide a dense representation of words and their relative meanings.
* They are an improvement over sparse representations used in simpler bag of word model representations.

> Keras Embedding layer
* Input data should be integer encoded(unique)
* Three arguments:
  * input_dim: This is the size of the vocabulary in the text data.
  * output_dim: This is the size of the vector space in which words will be embedded.
  * input_length: This is the length of input sequences. (e.g a text document which is comprised of 1000 words)
  
