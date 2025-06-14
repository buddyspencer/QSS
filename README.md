# 🔍 QSS - Quantized Similarity Search (Just an experiment for fun)

This software is an experiment on embedding vector quantization, with the goal of analyzing its accuracy and performance compared to standard floating-point representations.

# 📚 Dataset 👀...🟡 

The experiments use the GloVe 6B dataset, with pre-trained embeddings of the following dimensions:

50

100

200

300

# ⚙️ How It Works 👀...🟡 

Loading the embedding file
The .txt file containing the embeddings is loaded into memory. Each word is associated with its vector, which is then quantized and stored in a dedicated data structure.

User interaction
Once the embeddings are loaded, the program prompts the user to input a word.

If the word is found in the embedding dictionary (using a linear search—not optimized as it's not critical to this experiment), the analysis proceeds.

Vector search (QSS vs Cosine Similarity)
For the input word, two types of vector searches are performed:

QSS (Quantized Similarity Search):
A bitwise XOR is computed between the quantized embedding of the input word and all the quantized embeddings in memory.

If the number of different bits (i.e., number of 1s in the XOR result) is ≤ TOTAL_1_CHECK, the candidate word is selected.

Use TOTAL_1_CHECK to tune your solution.

For these selected words, the cosine similarity is calculated using the original (non-quantized) embeddings.

The results are sorted in descending order by similarity.

Standard Cosine Similarity Search:
As a baseline, a cosine similarity search is performed using the input word’s original embedding against all embeddings, without quantization.

# 🧪 Goals of the Experiment 👀...🟡 

Assess how quantization affects semantic search accuracy.

Measure potential gains in speed and memory usage.

Evaluate the scalability of the method with increasing embedding dimensions.

# 🚧 Technical Note 👀...🟡 

Word lookup in the embedding dictionary is performed linearly. This is not optimized intentionally, as the goal is to assess the impact of quantization on search quality, not access speed.



# 📊 Preliminary Results 👀...🟡 

While only a limited number of experiments have been conducted so far, the initial results are promising:

Word: "hello"
→ ✅ 100% accuracy on the top 30 retrieved items
→ ⚡ 3× faster search time compared to standard cosine similarity

Word: "men"
→ ✅ 90% accuracy on the top 30
→ ⚡ 3× faster

Word: "Italy"
→ ✅ 100% accuracy
→ ⚡ 3× faster

These results suggest that the quantized approach can maintain high accuracy while providing a significant performance improvement.


# Example

<img width="519" alt="Screenshot 2025-06-14 alle 08 41 06" src="https://github.com/user-attachments/assets/e5d7f424-643a-4223-ab63-cb91228ff3f8" />
