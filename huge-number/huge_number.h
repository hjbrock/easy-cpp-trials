/*
 * Definition of the huge_number class. Huge_numbers represent positive integers of arbi * arbitrary length.
 *
 * Author: Hannah Brock
 */

#ifndef HUGE_NUMBER_H
#define HUGE_NUMBER_H

#include <string>

  class huge_number
  {
    public:
      huge_number();
      huge_number(std::string s);
      huge_number(const huge_number& h);

      std::string get_value() const;
     
      huge_number & operator= (const huge_number &rhs); 
      const huge_number operator+ (const huge_number &h) const;
      const huge_number operator- (const huge_number &h) const;
      const huge_number operator* (const huge_number &h) const;
      const huge_number operator/ (const huge_number &rhs) const; 
      const huge_number operator% (const huge_number &rhs) const;
      const bool operator< (const huge_number &rhs) const;
    
    private:
      std::string num;
      huge_number divide_or_mod(const bool &division, const huge_number &rhs) const;
  };
#endif
