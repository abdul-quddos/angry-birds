#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "myvector.h"
#include <fstream>

template <typename T>
class ScoreManager {
private:
    Dynamic_array<T> scores; 
    T currentScore;

public:
    
    ScoreManager() {
        currentScore = 0;
    }

   
    void addScore(T points) {
        currentScore += points;
        scores.push(currentScore);
    }

    void setScore(T score)
    {
        currentScore = score;
    }

   
    T getCurrentScore() const {
        return currentScore;
    }

    
    void resetScore() {
        currentScore = 0;
    }

    
    void saveToFile(const char* filename) const {
        std::ofstream out(filename, std::ios::binary);
        if (!out) return;

        for (int i = 0; i < scores.size(); i++) {
            out.write(reinterpret_cast<const char*>(&scores[i]), sizeof(T));
        }

        out.close();
    }

  
    void loadFromFile(const char* filename) {
        std::ifstream in(filename, std::ios::binary);
        if (!in) return;

        scores.clear();
        currentScore = 0;

        T value;
        while (in.read(reinterpret_cast<char*>(&value), sizeof(T))) {
            scores.push(value);
        }

        if (scores.size() > 0)
            currentScore = scores.back();

        in.close();
    }
};

#endif // SCOREMANAGER_H
