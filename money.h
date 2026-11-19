#ifndef MONEY_H_
#define MONEY_H_

#include <iostream>

class Money {
 public:
  Money();
  Money(unsigned int rubles, short int kopeks);
  explicit Money(unsigned int total_kopeks);

  unsigned int GetRubles() const;
  short int GetKopeks() const;
  void SetRubles(unsigned int rubles);
  void SetKopeks(short int kopeks);

  Money SubtractKopeks(unsigned int kopeks) const;

  explicit operator unsigned int() const;
  operator bool() const;

  friend std::ostream& operator<<(std::ostream& os, const Money& money);
  friend Money operator--(Money& m);
  friend Money operator--(Money& m, int);
  friend Money operator++(Money& m);
  friend Money operator++(Money& m, int);
  friend Money operator-(const Money& m, unsigned int kopeks);
  friend Money operator-(const Money& left, const Money& right);

 private:
  unsigned int rubles_;
  short int kopeks_;

  void Normalize();
};

#endif  // MONEY_H_