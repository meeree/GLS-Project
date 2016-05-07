class Value {
public:
   Value ();
   virtual ~Value ();

   virtual int const &getInt () const;
   virtual double const &getFloat () const;
   virtual bool const &getBool () const;
   
   virtual bool isInt () const;
   virtual bool isFloat () const;
   virtual bool isBool () const;
};

class IntValue : public Value {
private:
   int mValue;
public:
   IntValue ( int const &value );
   virtual ~IntValue ();
   int const &getInt () const;
   double const &getFloat () const;
   bool isInt () const;
};

class FloatValue : public Value {
private:
   double mValue;
public:
   FloatValue ( double const &value );
   virtual ~FloatValue ();
   double const &getFloat () const;
   int const &getInt () const;
   bool isFloat () const;
};

class BoolValue : public Value {
private:
   bool mValue;
public:
   BoolValue ( bool const &value );
   virtual ~BoolValue ();
   bool const &getBool () const;
   bool isBool () const;
};

