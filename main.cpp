#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <sstream>

#include "money.h"

void Pause() {
  std::cout << "\nНажмите Enter для продолжения..." << std::flush;
  std::string temp;
  std::getline(std::cin, temp);
}

unsigned int InputUnsignedInt(const std::string& prompt) {
  long long value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      std::string remainder;
      std::getline(std::cin, remainder);
      bool is_clean = true;
      for (char c : remainder) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
          is_clean = false;
          break;
        }
      }
      if (is_clean && value >= 0) {
        return static_cast<unsigned int>(value);
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Некорректный ввод. Введите целое неотрицательное число.\n";
  }
}

short int InputShortInt(const std::string& prompt) {
  long long value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      std::string remainder;
      std::getline(std::cin, remainder);
      bool is_clean = true;
      for (char c : remainder) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
          is_clean = false;
          break;
        }
      }
      if (is_clean && value >= 0 && value <= 99) {
        return static_cast<short int>(value);
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Некорректный ввод. Введите целое число от 0 до 99.\n";
  }
}

Money InputMoney(const std::string& label) {
  std::cout << "  Ввод " << label << ":\n";
  unsigned int rub = InputUnsignedInt("    Рубли: ");
  short int kop = InputShortInt("    Копейки: ");
  return Money(rub, kop);
}

void PrintSeparator(const std::string& title) {
  std::cout << "\n" << std::string(60, '=') << "\n";
  std::cout << "  " << title << "\n";
  std::cout << std::string(60, '=') << "\n\n";
}

void PrintTest(const std::string& description, const Money& result) {
  std::cout << "  " << description << "\n";
  std::cout << "  Результат: " << result << "\n\n";
}

int main() {
  setlocale(LC_ALL, "Russian");

  PrintSeparator("ЗАДАНИЕ 1: Конструкторы и метод SubtractKopeks");

  std::cout << "1. Конструктор по умолчанию:\n";
  Money m1;
  std::cout << "   m1 = " << m1 << "\n\n";

  std::cout << "2. Конструктор (рубли, копейки):\n";
  Money m2 = InputMoney("m2");
  std::cout << "   m2 = " << m2 << "\n\n";

  std::cout << "3. Конструктор (всего копеек):\n";
  unsigned int total_kop = InputUnsignedInt("    Всего копеек: ");
  Money m3(total_kop);
  std::cout << "   m3 = " << m3 << "\n\n";

  std::cout << "4. Метод SubtractKopeks:\n";
  unsigned int sub_kop = InputUnsignedInt("    Вычесть копеек из m2: ");
  std::ostringstream oss1;
  oss1 << "m2.SubtractKopeks(" << sub_kop << ")";
  PrintTest(oss1.str(), m2.SubtractKopeks(sub_kop));

  Pause();

  PrintSeparator("ЗАДАНИЕ 2: Унарные операции ++ и --");

  Money m6 = InputMoney("m6");
  std::cout << "   Исходное значение: " << m6 << "\n\n";

  std::cout << "  Операции инкремента:\n";
  std::cout << "    ++m6  = " << ++m6 << "\n";
  std::cout << "    m6++  = " << m6++ << " (возврат старого значения)\n";
  std::cout << "    m6    = " << m6 << " (после постфикса)\n\n";

  std::cout << "  Операции декремента:\n";
  std::cout << "    --m6  = " << --m6 << "\n";
  std::cout << "    m6--  = " << m6-- << " (возврат старого значения)\n";
  std::cout << "    m6    = " << m6 << " (после постфикса)\n\n";

  std::cout << "  Граничный случай (декремент нуля):\n";
  Money m_zero(0, 0);
  std::cout << "    --(0 rub. 0 kop.) = " << --m_zero << "\n\n";

  Pause();

  PrintSeparator("ЗАДАНИЕ 2: Операции приведения типа");

  Money m7 = InputMoney("m7");
  std::cout << "   Исходное значение: " << m7 << "\n\n";

  std::cout << "  Явное приведение к unsigned int:\n";
  std::cout << "    static_cast<unsigned int>(" << m7
            << ") = " << static_cast<unsigned int>(m7) << "\n\n";

  std::cout << "  Неявное приведение к bool:\n";
  std::cout << "    " << m7 << " -> " << (m7 ? "true" : "false") << "\n";
  std::cout << "    0 rub. 0 kop. -> " << (Money(0, 0) ? "true" : "false")
            << "\n\n";

  Pause();

  PrintSeparator("ЗАДАНИЕ 2: Бинарные операции вычитания");

  std::cout << "1. Вычитание копеек (Money - unsigned int):\n";
  Money m8 = InputMoney("m8");
  unsigned int kopeks_to_sub = InputUnsignedInt("    Вычесть копеек: ");
  std::ostringstream oss2;
  oss2 << m8 << " - " << kopeks_to_sub << " коп.";
  PrintTest(oss2.str(), m8 - kopeks_to_sub);

  std::cout << "2. Вычитание денежных сумм (Money - Money):\n";
  Money m10 = InputMoney("m10");
  std::ostringstream oss3;
  oss3 << m8 << " - " << m10;
  PrintTest(oss3.str(), m8 - m10);

  std::cout << "3. Граничный случай (вычитание большего из меньшего):\n";
  Money m12 = InputMoney("m12 (меньшее)");
  Money m13 = InputMoney("m13 (большее)");
  std::ostringstream oss4;
  oss4 << m12 << " - " << m13;
  PrintTest(oss4.str(), m12 - m13);

  Pause();

  std::cout << "\n[Все тесты завершены успешно]\n";

  return 0;
}