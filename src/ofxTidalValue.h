#include <string>

class ofxTidalValue {
public:
  virtual ~ofxTidalValue() {}
  virtual std::string getName() { return name; }

protected:
  std::string name;
};

template <typename T> class ofxTidalValue_t : public ofxTidalValue {
public:
  ofxTidalValue_t(const std::string &name, const T &value)
      : name(name), value(value) {}
  std::string getName() { return name; }
  T getValue() { return value; }
  void setValue(const T value) { this->value = value; }

private:
  T value;
  std::string name;
};
