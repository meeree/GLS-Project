enum class value_type_t;

class Value {
public:
   virtual value_type_t getType () const = 0;
};
