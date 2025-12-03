#ifndef OPTION_H
#define OPTION_H

#include <string>
using namespace std;

namespace carconfig {

class Option
{
    friend ostream& operator<<(ostream& s, const Option& opt);
private:
    string code;
    string label;
    float price;

public:
    Option();
    Option(const string& c, const string& l, float p);
    Option(const Option& opt);
    ~Option();
    
    string getCode() const;
    string getLabel() const;
    float getPrice() const;
    
    void setCode(const string& c);
    void setLabel(const string& l);
    void setPrice(float p);
    
    void display() const;
    
    
};

} // namespace carconfig

#endif