/*
 * A huge_number is an integer of arbitrary size. This class provides
 * method definitions for working with large integers in string formats.
 *
 * Author: Hannah Brock
 */

#include "huge_number.h"
#include <string>
#include <iostream>
#include <exception>

using namespace std;

/* Creates a new huge_number representing "0" */
huge_number::huge_number()
{
    num = "0";
}

/* Creates a new huge_number object representing the number
 * in the provided string. All leading 0s are ignored.
 */
huge_number::huge_number(string s)
{
    num = s;
    // Strip leading zeros
    while (num[0] == '0')
        num.erase(0, 1);

    // If the string is empty, it is 0
    if (num.length() == 0)
        num = "0";
}

/* Copies the given huge_number object into a new instance */
huge_number::huge_number(const huge_number& h)
{
    num = h.num;
}

/* Returns the value of this huge_number as a string */
string huge_number::get_value() const
{
    return num;
}

/* Assigns the value of the given huge_number to this huge_number */
huge_number & huge_number::operator= (const huge_number &rhs)
{
    this->num = rhs.num;
    return *this;
}

/* Adds the given huge_number to this huge_number and returns the result */
const huge_number huge_number::operator+ (const huge_number &h) const
{
    // Result holder
    string result = "";
    // Set positions to begin on the right side of the numbers
    int lhs_pos = this->num.length() - 1;
    int rhs_pos = h.num.length() - 1;
    int carry = 0;

    // Add columns and calculate the carry until there are no more columns
    // left and no carry left.
    while (lhs_pos >= 0 || rhs_pos >= 0 || carry > 0)
    {
        // Get the correct digits
        int lhdigit = lhs_pos >= 0 ? this->num[lhs_pos--]-'0' : 0;
        int rhdigit = rhs_pos >= 0 ? h.num[rhs_pos--]-'0' : 0;

        // Calculate the result and the carry
        int sum = lhdigit + rhdigit + carry;
        carry = sum / 10;
        sum = sum % 10 + '0'; //change the sum to be the appropriate char

        // Place the correct char in the result
        result.insert(0, 1, static_cast<char>(sum));
    }

    // Use the huge_number constructor to strip the leading zeros
    return huge_number(result);
}

/* 
 * Subtracts the given huge_number from this huge number and returns the result
 * Returns "0" if the result is negative
 */
const huge_number huge_number::operator- (const huge_number &rhs) const
{
    // If the rhs is bigger than the lhs or the two are equal, no point in subtracting,     // just return "0"
    if (*this < rhs)
        return huge_number("0");

    // Calculate each digit and borrow and create the subtraction result
    string result = "";
    int lhs_pos = this->num.length()-1;
    int rhs_pos = rhs.num.length()-1;
    int borrow = 0;
    while (lhs_pos >= 0)
    {
	int lhdigit = this->num[lhs_pos--] - '0';
        int rhdigit = rhs_pos >= 0 ? rhs.num[rhs_pos--] - '0' : 0;

        int sub = lhdigit - rhdigit - borrow;

        // If our result is less than 0, calculate in a borrow
        if (sub < 0)
        {
	    sub += 10;
            borrow = 1;
	}
        else
	    borrow = 0;
        result.insert(0, 1, static_cast<char>(sub + '0'));
    }
    return huge_number(result);
}

/* Multiplies the given huge_number with this huge_number and returns the result */
const huge_number huge_number::operator* (const huge_number &h) const
{
    // Create result holder and placeholder for this
    huge_number result;
    huge_number temp_this = *this;

    int rhs_pos = h.num.length() - 1;

    // Loop through for each digit in rhs
    while (rhs_pos >= 0)
    {
        // Get next digit and multiply current number the correct number of times
        int rhdigit = h.num[rhs_pos--] - '0'; 
        for (int i = 0; i < rhdigit; i++)
 	    result = result + temp_this;

        // Multiple lhs by ten
        temp_this.num.append("0");
    }
    return result;
}

/* Divides this huge_number by the given huge_number and returns the result */
const huge_number huge_number::operator/ (const huge_number &rhs) const
{
    if (rhs.num == "0")
        throw "Division by 0";
    return divide_or_mod(true,  rhs);
}

/* 
 * Takes the modulus of this huge_number with the given huge_number as the
 * divisor and returns the result.
 */
const huge_number huge_number::operator% (const huge_number &rhs) const
{
    if (rhs.num == "0")
        throw "Division by 0";
    return divide_or_mod(false, rhs);
}

/* 
 * Returns true if this huge_number is less than the given huge_number
 * returns false otherwise
 */
const bool huge_number::operator< (const huge_number &rhs) const
{
    if (this->num.length() < rhs.num.length())
        return true;
    if (this->num.length() > rhs.num.length())
        return false;

    for (int i = 0; i < rhs.num.length(); i++)
    {
        int lhdigit = this->num[i]-'0';
        int rhdigit = rhs.num[i]-'0';

        if (lhdigit < rhdigit)
            return true;
        if (lhdigit > rhdigit)
            return false;
    }
    return false;
}

/*
 * Returns the result of division of the two huge_numbers if the flag is
 * set to true or the result of the modulus of the two numbers otherwise.
 */
huge_number huge_number::divide_or_mod(const bool &division, const huge_number &rhs) const
{
    // If lhs is less than rhs, just return zero (integer division) or lhs
    if (*this < rhs)
    {
        if(division)
            return huge_number("0");
        return *this;
    }

    huge_number one("1");
    huge_number ten("10");
    huge_number div_count;
    huge_number shift_count;
    huge_number temp(*this);
    huge_number shifted_rhs = rhs;

    // Shift divisor to be closer to the size of the dividend
    while (shifted_rhs.num.length() < temp.num.length())
    {
        shifted_rhs.num.append("0");
        shift_count = shift_count + one;
    }

    // If fully shifted number is too big, unshift by one
    if(temp < shifted_rhs)
    {
	shift_count = shift_count - one;
        shifted_rhs.num.erase(shifted_rhs.num.length()-1,1);
    }
    
    huge_number total_shift("1");
    // calculate the total number of divisions in the shift
    while (!(shift_count < one))
    {
       total_shift = total_shift * ten;
       shift_count = shift_count - one;
    }

    //subtract out as many times as we can
    while (!(temp < shifted_rhs))
    {
        temp = temp - shifted_rhs;
        div_count = div_count + total_shift;
    }
    
    //do it all again
    if (division)
        return div_count + temp.divide_or_mod(division,rhs);
    
    return temp.divide_or_mod(division,rhs);
}
