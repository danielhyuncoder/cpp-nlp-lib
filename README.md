# Custom C++ NLP Library

This project is a **lightweight NLP (Natural Language Processing) library** implemented in C++ for text classification.  
It uses a custom word-weighting approach to train on labeled text data and make predictions.  
The library also supports saving/loading models and fine-tuning during evaluation.

---

## Features

- **Import training data from JSON**  
  - Reads labeled text data and organizes it into a format suitable for training.
- **Trainable classification model**  
  - Uses a simple frequency-based approach with weighted scoring.
- **Prediction modes**  
  - Standard prediction (`predict`) returning only the label.  
  - Detailed prediction (`predict_test_mode`) showing word contributions.
- **Model optimization**  
  - Adjusts weights of influential words when misclassifications occur.
- **Save & load models**  
  - Store trained models as JSON and reload them later.
- **Evaluate on test data**  
  - Measures accuracy and optimizes during evaluation.

---

## Requirements

- **C++17 or higher**
- [nlohmann/json](https://github.com/nlohmann/json) library (included in `include/json.hpp`)
- A **Makefile** (provided) to compile and run the project

---

## File Structure

```
project/
├── include/
│   ├── NLP.h          # Library header
│   ├── json.hpp       # nlohmann/json library
├── src/
│   ├── NLP.cpp        # Implementation of NLP class
│   ├── main.cpp       # Example usage
├── data/
│   ├── train.json     # Example training data
│   ├── test.json      # Example test data
├── Makefile           # Build instructions
└── README.md          # This file
```

---

## Building & Running

1. **Clone or download** this project into a directory.

2. **Place your training and testing data** (in JSON format) inside a `data/` folder.  
   Example JSON structure for training:
   ```json
   [
     { "label": 0, "text": "hello world" },
     { "label": 1, "text": "machine learning" }
   ]
   ```

3. **Compile the project**:
   ```bash
   make
   ```

4. **Run the program**:
   ```bash
   ./app.exe
   ```

---

## Example Usage

```cpp
#include "include/NLP.h"
#include "include/json.hpp"

using namespace lib;

int main() {
    // Load training data
    auto trainData = importFromJSON("data/train.json", 2);

    // Create model and train
    NLP model(trainData);
    model.setRate(1.5);
    model.fit(10);

    // Evaluate
    auto testData = importFromJSON("data/test.json", 2);
    model.evaluate(testData);

    // Save model
    model.encodeTo("saved_model.json");

    // Load model
    NLP loadedModel("saved_model.json");
    auto prediction = loadedModel.predict("hello machine world");
    std::cout << "Predicted label: " << prediction << std::endl;

    return 0;
}
```

---

## Functions Overview

### Data Handling
- `importFromJSON(string path, int labels)` → Loads labeled data from JSON.

### Model Creation
- `NLP(vector<vector<string>> trainData)` → Initializes and prepares the model for training.
- `NLP(string savedModelPath)` → Loads a pre-trained model from JSON.

### Training & Evaluation
- `fit(int epochs)` → Train for a number of epochs.
- `evaluate(vector<vector<string>> test_data)` → Test and fine-tune on evaluation data.

### Prediction
- `predict(string text)` → Returns predicted label.
- `predict_test_mode(string text)` → Returns predicted label and word contributions.
- `getFullPredict(string text)` → Returns confidence score and label.

### Model Management
- `encodeTo(string path)` → Save model to JSON.
- `fromEncoded(string path)` → Load model from JSON.
- `setRate(double rate)` → Set learning rate for optimization.

---

## Notes

- The library **does not** use any external ML frameworks.
- It is designed for **simple, interpretable text classification** tasks.
- For larger datasets or more complex NLP tasks, consider integrating with existing ML frameworks.

---

## License

This project is provided under the **MIT License**.  
You are free to modify and use it in your own projects.
