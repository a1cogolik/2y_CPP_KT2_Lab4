#include "money.h"

#include <stdexcept>

Money::Money() : rubles_(0), kopeks_(0) {}

Money::Money(unsigned int rubles, short int kopeks)
    : rubles_(rubles), kopeks_(kopeks) {
  if (kopeks < 0) {
    throw std::invalid_argument("Копейки не могут быть отрицательными");
  }
  Normalize();
}

Money::Money(unsigned int total_kopeks) {
  if (total_kopeks < 0) {
    throw std::invalid_argument("Копейки не могут быть отрицательными");
  }
  rubles_ = total_kopeks / 100;
  kopeks_ = total_kopeks % 100;
}

unsigned int Money::GetRubles() const { return rubles_; }

short int Money::GetKopeks() const { return kopeks_; }

void Money::SetRubles(unsigned int rubles) { rubles_ = rubles; }

void Money::SetKopeks(short int kopeks) {
  if (kopeks < 0) {
    throw std::invalid_argument("Копейки не могут быть отрицательными");
  }
  kopeks_ = kopeks;
  Normalize();
}

void Money::Normalize() {
  if (kopeks_ >= 100) {
    rubles_ += kopeks_ / 100;
    kopeks_ %= 100;
  }
}

Money Money::SubtractKopeks(unsigned int kopeks) const {
  unsigned int total_kopeks = rubles_ * 100 + kopeks_;
  if (kopeks > total_kopeks) {
    return Money(0, 0);
  }
  total_kopeks -= kopeks;
  return Money(total_kopeks);
}

Money::operator unsigned int() const { return rubles_; }

Money::operator bool() const { return (rubles_ != 0 || kopeks_ != 0); }

std::ostream& operator<<(std::ostream& os, const Money& money) {
  os << money.rubles_ << " руб. " << money.kopeks_ << " коп.";
  return os;
}

Money operator--(Money& m) {
  if (m.rubles_ == 0 && m.kopeks_ == 0) {
    return m;
  }
  if (m.kopeks_ == 0) {
    --m.rubles_;
    m.kopeks_ = 99;
  } else {
    --m.kopeks_;
  }
  return m;
}

Money operator--(Money& m, int) {
  Money temp = m;
  --m;
  return temp;
}

Money operator++(Money& m) {
  ++m.kopeks_;
  m.Normalize();
  return m;
}

Money operator++(Money& m, int) {
  Money temp = m;
  ++m;
  return temp;
}

Money operator-(const Money& m, unsigned int kopeks) {
  return m.SubtractKopeks(kopeks);
}

Money operator-(const Money& left, const Money& right) {
  unsigned int total_1 = left.rubles_ * 100 + left.kopeks_;
  unsigned int total_2 = right.rubles_ * 100 + right.kopeks_;
  if (total_2 > total_1) {
    return Money(0, 0);
  }
  return Money(total_1 - total_2);
}