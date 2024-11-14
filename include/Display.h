#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

class Display {
public:
    void clear() const;
    void showResult(double result) const;
    void showError(const std::string& message) const;
    void showMessage(const std::string& message) const;
};

#endif 