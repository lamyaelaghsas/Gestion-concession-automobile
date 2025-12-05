#ifndef MODEL_H
#define MODEL_H

#include <iostream>
using namespace std;

namespace carconfig {

enum Engine { Petrol, Diesel, Electric, Hybrid };

class Model
{
  friend ostream& operator<<(ostream& s, const Model& m);
  friend istream& operator>>(istream& s, Model& m);
  
private:
  char* name;
  int power;
  Engine engine;
  float basePrice;
  
public:
  Model(); // constructeur par défaut
  Model(const char* n, int p, Engine e, float bp); // constructeur d'initialisation
  Model(const Model& mod); // constructeur de copie
  ~Model();
  
  void setPower(int p);
  int getPower() const;
  void setName(const char* n);
  const char* getName() const;
  void setEngine(Engine e);
  Engine getEngine() const;
  void setBasePrice(float bp);
  float getBasePrice() const;
  void display() const;
  string toString() const;  // Pour affichage console
  
  // Opérateur d'affectation
  Model& operator=(const Model& m);
};

} // namespace carconfig

#endif