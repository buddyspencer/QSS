# 🔍 QSS - Quantized Similarity Search 

QSS is a vector search engine written in C that uses a 1-bit binary representation for embeddings and calculate Hamming's distance with an XOR + popcount pipeline to achieve high-precision approximate search, followed by a re-ranking phase using cosine similarity.

This software is an experiment on embedding vector quantization, with the goal of analyzing its accuracy and performance compared to standard floating-point representations.

# Features
🔍 High-speed vector search (up to 18× faster)

🧠 100% accuracy on Word2Vec (with re-ranking)

📦 Quantized embeddings: from 1200B → 40B

⚡ Compatible with GloVe / Word2Vec / fastText


# 📚 Dataset 👀...🟡 

The experiments are based on 
- GloVe 6B dataset embedding https://nlp.stanford.edu/projects/glove/   --> file glove.6B.300d.txt
- Word2vec dataset https://code.google.com/archive/p/word2vec/   --> file GoogleNews-vectors-negative300.bin

  

# ⚙️ How It Works 👀...🟡 

Loading the embedding file
For Glove the file is in .txt format for word2vec is in binary format. 

Both file containing the embeddings, this is loaded into memory. Each word is associated with its vector, which is then quantized and stored in a dedicated data structure.

- to load glove file digit ./qss --glove <filename.txt>

- to load word2vec file digit ./qss --word2vec <filename.bin>

## User interaction
Once the embeddings are loaded, the program prompts the user to input a word.

If the word is found in the embedding dictionary (using a linear search—not optimized as it's not critical to this experiment), the analysis proceeds.

## Vector search (QSS vs Cosine Similarity)
For the input word, two types of vector searches are performed:

### QSS (Quantized Similarity Search):
A bitwise XOR is computed between the quantized embedding of the input word and all the quantized embeddings in memory.

If the number of different bits (i.e., number of 1s in the XOR result) is ≤ TOTAL_1_CHECK, the candidate word is selected.

These selected words are put into a vector with length = MAX_LEN_QUANTIZATION_RESULT and for each of them the cosine similarity is calculated using the original (non-quantized) embeddings.

The results are sorted in descending order by similarity.

Use TOTAL_1_CHECK and MAX_LEN_QUANTIZATION_RESULT to tune your solution.

### Standard Cosine Similarity Search:
As a baseline, a cosine similarity search is performed using the input word’s original embedding against all embeddings, without quantization.

# 🧪 Goals of the Experiment 👀...🟡 

Assess how quantization affects semantic search accuracy.

Measure potential gains in speed and memory usage.

Evaluate the scalability of the method with increasing embedding dimensions.

# 🚧 Technical Note 👀...🟡 

Word lookup in the embedding dictionary is performed linearly. This is not optimized intentionally, as the goal is to assess the impact of quantization on search quality, not access speed.

the experimentation has been done on Imac 2018 with 3,6 GHz Intel Core i3 quad-core

# 📊 Preliminary Results 👀...🟡 

While only a limited number of experiments have been conducted so far, the initial results are promising.

Parameters used:
- MAX_LEN_QUANTIZATION_RESULT = 60000
- TOTAL_1_CHECK = 120

## with GloVe:
Word: "hello"
→ ✅ 100% accuracy on the top 30 retrieved items
→ ⚡ 3× faster search time compared to standard cosine similarity

Word: "men"
→ ✅ 90% accuracy on the top 30
→ ⚡ 3× faster

Word: "italy"
→ ✅ 100% accuracy
→ ⚡ 3× faster

## with word2vec:
word "hello"
→ ✅ 100% accuracy on the top 30
→ ⚡ 18× faster

man "men"
→ ✅ 100% accuracy on the top 30
→ ⚡ 18× faster

man "italy"
→ ✅ 100% accuracy on the top 30
→ ⚡ 18× faster


These results suggest that the quantized approach can maintain high accuracy while providing a significant performance improvement.


# Example
## With GloVe

<img width="519" alt="Screenshot 2025-06-14 alle 08 41 06" src="https://github.com/user-attachments/assets/e5d7f424-643a-4223-ab63-cb91228ff3f8" />


## With word2vec

<img width="492" alt="Screenshot 2025-06-21 alle 18 42 48" src="https://github.com/user-attachments/assets/941136d4-15b4-4b30-afe1-e5868dc72939" />
