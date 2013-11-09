/*
 * This file is a part of TTMath Bignum Library
 * and is distributed under the (new) BSD licence.
 * Author: Tomasz Sowa <t.sowa@ttmath.org>
 */

/* 
 * Copyright (c) 2006-2010, Tomasz Sowa
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *    
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *    
 *  * Neither the name Tomasz Sowa nor the names of contributors to this
 *    project may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef headerfilettmathttmath_uint_noasm
#define headerfilettmathttmath_uint_noasm


#ifdef TTMATH_NOASM

/*!
	\file ttmathttmath_uint_noasm.h
    \brief template class UInt<ttmath_uint> with methods without any assembler code

	this file is included at the end of ttmathttmath_uint.h
*/


namespace ttmath
{

	/*!
		returning the string represents the currect type of the library
		we have following types:
		  asm_vc_32   - with asm code designed for Microsoft Visual C++ (32 bits)
		  asm_gcc_32  - with asm code designed for GCC (32 bits)
		  asm_vc_64   - with asm for VC (64 bit)
		  asm_gcc_64  - with asm for GCC (64 bit)
		  no_asm_32   - pure C++ version (32 bit) - without any asm code
		  no_asm_64   - pure C++ version (64 bit) - without any asm code
	*/
	template<ttmath_uint value_size>
	const char * UInt<value_size>::LibTypeStr()
	{
		#ifdef TTMATH_PLATFORM32
			static const char info[] = "no_asm_32";
		#endif		

		#ifdef TTMATH_PLATFORM64
			static const char info[] = "no_asm_64";
		#endif

	return info;
	}

	
	/*!
		returning the currect type of the library
	*/
	template<ttmath_uint value_size>
	LibTypeCode UInt<value_size>::LibType()
	{
		#ifdef TTMATH_PLATFORM32
			LibTypeCode info = no_asm_32;
		#endif		

		#ifdef TTMATH_PLATFORM64
			LibTypeCode info = no_asm_64;
		#endif

	return info;
	}


	/*!
		this method adds two words together
		returns carry

		this method is created only when TTMATH_NOASM macro is defined
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::AddTwoWords(ttmath_uint a, ttmath_uint b, ttmath_uint carry, ttmath_uint * result)
	{
	ttmath_uint temp;

		if( carry == 0 )
		{
			temp = a + b;

			if( temp < a )
				carry = 1;
		}
		else
		{
			carry = 1;
			temp  = a + b + carry;

			if( temp > a ) // !(temp<=a)
				carry = 0;
		}

		*result = temp;

	return carry;
	}



	/*!
		this method adding ss2 to the this and adding carry if it's defined
		(this = this + ss2 + c)

		c must be zero or one (might be a bigger value than 1)
		function returns carry (1) (if it was)
	*/
	
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::Add(const UInt<value_size> & ss2, ttmath_uint c)
	{
	ttmath_uint i;

		for(i=0 ; i<value_size ; ++i)
			c = AddTwoWords(table[i], ss2.table[i], c, &table[i]);

		TTMATH_LOGC("UInt::Add", c)
	
	return c;
	}


	/*!
		this method adds one word (at a specific position)
		and returns a carry (if it was)

		if we've got (value_size=3):
			table[0] = 10;
			table[1] = 30;
			table[2] = 5;	
		and we call:
			AddInt(2,1)
		then it'll be:
			table[0] = 10;
			table[1] = 30 + 2;
			table[2] = 5;

		of course if there was a carry from table[2] it would be returned
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::AddInt(ttmath_uint value, ttmath_uint index)
	{
	ttmath_uint i, c;

		TTMATH_ASSERT( index < value_size )


		c = AddTwoWords(table[index], value, 0, &table[index]);

		for(i=index+1 ; i<value_size && c ; ++i)
			c = AddTwoWords(table[i], 0, c, &table[i]);

		TTMATH_LOGC("UInt::AddInt", c)
	
	return c;
	}





	/*!
		this method adds only two unsigned words to the existing value
		and these words begin on the 'index' position
		(it's used in the multiplication algorithm 2)

		index should be equal or smaller than value_size-2 (index <= value_size-2)
		x1 - lower word, x2 - higher word

		for example if we've got value_size equal 4 and:
			table[0] = 3
			table[1] = 4
			table[2] = 5
			table[3] = 6
		then let
			x1 = 10
			x2 = 20
		and
			index = 1

		the result of this method will be:
			table[0] = 3
			table[1] = 4 + x1 = 14
			table[2] = 5 + x2 = 25
			table[3] = 6
		
		and no carry at the end of table[3]

		(of course if there was a carry in table[2](5+20) then 
		this carry would be passed to the table[3] etc.)
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::AddTwoInts(ttmath_uint x2, ttmath_uint x1, ttmath_uint index)
	{
	ttmath_uint i, c;

		TTMATH_ASSERT( index < value_size - 1 )


		c = AddTwoWords(table[index],   x1, 0, &table[index]);
		c = AddTwoWords(table[index+1], x2, c, &table[index+1]);

		for(i=index+2 ; i<value_size && c ; ++i)
			c = AddTwoWords(table[i], 0, c, &table[i]);

		TTMATH_LOGC("UInt::AddTwoInts", c)
	
	return c;
	}



	/*!
		this static method addes one vector to the other
		'ss1' is larger in size or equal to 'ss2'

		ss1 points to the first (larger) vector
		ss2 points to the second vector
		ss1_size - size of the ss1 (and size of the result too)
		ss2_size - size of the ss2
		result - is the result vector (which has size the same as ss1: ss1_size)

		Example:  ss1_size is 5, ss2_size is 3
		ss1:      ss2:   result (output):
		  5        1         5+1
		  4        3         4+3
		  2        7         2+7
		  6                  6
		  9                  9
	  of course the carry is propagated and will be returned from the last item
	  (this method is used by the Karatsuba multiplication algorithm)
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::AddVector(const ttmath_uint * ss1, const ttmath_uint * ss2, ttmath_uint ss1_size, ttmath_uint ss2_size, ttmath_uint * result)
	{
	ttmath_uint i, c = 0;

		TTMATH_ASSERT( ss1_size >= ss2_size )
		
		for(i=0 ; i<ss2_size ; ++i)
			c = AddTwoWords(ss1[i], ss2[i], c, &result[i]);

		for( ; i<ss1_size ; ++i)
			c = AddTwoWords(ss1[i], 0, c, &result[i]);

		TTMATH_VECTOR_LOGC("UInt::AddVector", c, result, ss1_size)

	return c;
	}




	/*!
		this method subtractes one word from the other
		returns carry

		this method is created only when TTMATH_NOASM macro is defined
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::SubTwoWords(ttmath_uint a, ttmath_uint b, ttmath_uint carry, ttmath_uint * result)
	{
		if( carry == 0 )
		{
			*result = a - b;

			if( a < b )
				carry = 1;
		}
		else
		{
			carry   = 1;
			*result = a - b - carry;

			if( a > b ) // !(a <= b )
				carry = 0;
		}

	return carry;
	}




	/*!
		this method's subtracting ss2 from the 'this' and subtracting
		carry if it has been defined
		(this = this - ss2 - c)

		c must be zero or one (might be a bigger value than 1)
		function returns carry (1) (if it was)
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::Sub(const UInt<value_size> & ss2, ttmath_uint c)
	{
	ttmath_uint i;

		for(i=0 ; i<value_size ; ++i)
			c = SubTwoWords(table[i], ss2.table[i], c, &table[i]);

		TTMATH_LOGC("UInt::Sub", c)

	return c;
	}




	/*!
		this method subtracts one word (at a specific position)
		and returns a carry (if it was)

		if we've got (value_size=3):
			table[0] = 10;
			table[1] = 30;
			table[2] = 5;	
		and we call:
			SubInt(2,1)
		then it'll be:
			table[0] = 10;
			table[1] = 30 - 2;
			table[2] = 5;

		of course if there was a carry from table[2] it would be returned
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::SubInt(ttmath_uint value, ttmath_uint index)
	{
	ttmath_uint i, c;

		TTMATH_ASSERT( index < value_size )


		c = SubTwoWords(table[index], value, 0, &table[index]);

		for(i=index+1 ; i<value_size && c ; ++i)
			c = SubTwoWords(table[i], 0, c, &table[i]);

		TTMATH_LOGC("UInt::SubInt", c)
	
	return c;
	}


	/*!
		this static method subtractes one vector from the other
		'ss1' is larger in size or equal to 'ss2'

		ss1 points to the first (larger) vector
		ss2 points to the second vector
		ss1_size - size of the ss1 (and size of the result too)
		ss2_size - size of the ss2
		result - is the result vector (which has size the same as ss1: ss1_size)

		Example:  ss1_size is 5, ss2_size is 3
		ss1:      ss2:   result (output):
		  5        1         5-1
		  4        3         4-3
		  2        7         2-7
		  6                  6-1  (the borrow from previous item)
		  9                  9
		                 return (carry): 0
	  of course the carry (borrow) is propagated and will be returned from the last item
	  (this method is used by the Karatsuba multiplication algorithm)
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::SubVector(const ttmath_uint * ss1, const ttmath_uint * ss2, ttmath_uint ss1_size, ttmath_uint ss2_size, ttmath_uint * result)
	{
	ttmath_uint i, c = 0;

		TTMATH_ASSERT( ss1_size >= ss2_size )
		
		for(i=0 ; i<ss2_size ; ++i)
			c = SubTwoWords(ss1[i], ss2[i], c, &result[i]);

		for( ; i<ss1_size ; ++i)
			c = SubTwoWords(ss1[i], 0, c, &result[i]);

		TTMATH_VECTOR_LOGC("UInt::SubVector", c, result, ss1_size)

	return c;
	}



	/*!
		this method moves all bits into the left hand side
		return value <- this <- c

		the lowest *bit* will be held the 'c' and
		the state of one additional bit (on the left hand side)
		will be returned

		for example:
		let this is 001010000
		after Rcl2_one(1) there'll be 010100001 and Rcl2_one returns 0
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::Rcl2_one(ttmath_uint c)
	{
	ttmath_uint i, new_c;

		if( c != 0 )
			c = 1;

		for(i=0 ; i<value_size ; ++i)
		{
			new_c    = (table[i] & TTMATH_UINT_HIGHEST_BIT) ? 1 : 0;
			table[i] = (table[i] << 1) | c;
			c        = new_c;
		}

		TTMATH_LOGC("UInt::Rcl2_one", c)

	return c;
	}







	/*!
		this method moves all bits into the right hand side
		c -> this -> return value

		the highest *bit* will be held the 'c' and
		the state of one additional bit (on the right hand side)
		will be returned

		for example:
		let this is 000000010
		after Rcr2_one(1) there'll be 100000001 and Rcr2_one returns 0
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::Rcr2_one(ttmath_uint c)
	{
	ttmath_sint i; // signed i
	ttmath_uint new_c;

		if( c != 0 )
			c = TTMATH_UINT_HIGHEST_BIT;

		for(i=ttmath_sint(value_size)-1 ; i>=0 ; --i)
		{
			new_c    = (table[i] & 1) ? TTMATH_UINT_HIGHEST_BIT : 0;
			table[i] = (table[i] >> 1) | c;
			c        = new_c;
		}

		c = (c != 0)? 1 : 0;

		TTMATH_LOGC("UInt::Rcr2_one", c)

	return c;
	}




	/*!
		this method moves all bits into the left hand side
		return value <- this <- c

		the lowest *bits* will be held the 'c' and
		the state of one additional bit (on the left hand side)
		will be returned

		for example:
		let this is 001010000
		after Rcl2(3, 1) there'll be 010000111 and Rcl2 returns 1
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::Rcl2(ttmath_uint bits, ttmath_uint c)
	{
		TTMATH_ASSERT( bits>0 && bits<TTMATH_BITS_PER_UINT )

		ttmath_uint move = TTMATH_BITS_PER_UINT - bits;
		ttmath_uint i, new_c;

		if( c != 0 )
			c = TTMATH_UINT_MAX_VALUE >> move;

		for(i=0 ; i<value_size ; ++i)
		{
			new_c    = table[i] >> move;
			table[i] = (table[i] << bits) | c;
			c        = new_c;
		}

		TTMATH_LOGC("UInt::Rcl2", (c & 1))

	return (c & 1);
	}




	/*!
		this method moves all bits into the right hand side
		C -> this -> return value

		the highest *bits* will be held the 'c' and
		the state of one additional bit (on the right hand side)
		will be returned

		for example:
		let this is 000000010
		after Rcr2(2, 1) there'll be 110000000 and Rcr2 returns 1
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::Rcr2(ttmath_uint bits, ttmath_uint c)
	{
		TTMATH_ASSERT( bits>0 && bits<TTMATH_BITS_PER_UINT )

		ttmath_uint move = TTMATH_BITS_PER_UINT - bits;
		ttmath_sint i; // signed
		ttmath_uint new_c;

		if( c != 0 )
			c = TTMATH_UINT_MAX_VALUE << move;

		for(i=value_size-1 ; i>=0 ; --i)
		{
			new_c    = table[i] << move;
			table[i] = (table[i] >> bits) | c;
			c        = new_c;
		}

		c = (c & TTMATH_UINT_HIGHEST_BIT) ? 1 : 0;

		TTMATH_LOGC("UInt::Rcr2", c)

	return c;
	}




	/*!
		this method returns the number of the highest set bit in x
		if the 'x' is zero this method returns '-1'
	*/
	template<ttmath_uint value_size>
	ttmath_sint UInt<value_size>::FindLeadingBitInWord(ttmath_uint x)
	{
		if( x == 0 )
			return -1;

		ttmath_uint bit = TTMATH_BITS_PER_UINT - 1;
		
		while( (x & TTMATH_UINT_HIGHEST_BIT) == 0 )
		{
			x = x << 1;
			--bit;
		}

	return bit;
	}



	/*!
		this method returns the number of the highest set bit in x
		if the 'x' is zero this method returns '-1'
	*/
	template<ttmath_uint value_size>
	ttmath_sint UInt<value_size>::FindLowestBitInWord(ttmath_uint x)
	{
		if( x == 0 )
			return -1;

		ttmath_uint bit = 0;
		
		while( (x & 1) == 0 )
		{
			x = x >> 1;
			++bit;
		}

	return bit;
	}



	/*!
		this method sets a special bit in the 'value'
		and returns the last state of the bit (zero or one)

		bit is from <0,TTMATH_BITS_PER_UINT-1>

		e.g.
		 ttmath_uint x = 100;
		 ttmath_uint bit = SetBitInWord(x, 3);
		 now: x = 108 and bit = 0
	*/
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::SetBitInWord(ttmath_uint & value, ttmath_uint bit)
	{
		TTMATH_ASSERT( bit < TTMATH_BITS_PER_UINT )

		ttmath_uint mask = 1;

		if( bit > 0 )
			mask = mask << bit;

		ttmath_uint last = value & mask;
		value     = value | mask;

	return (last != 0) ? 1 : 0;
	}






	/*!
	 *
	 * Multiplication
	 *
	 *
	*/


	/*!
		multiplication: result_high:result_low = a * b
		result_high - higher word of the result
		result_low  - lower word of the result
	
		this methos never returns a carry
		this method is used in the second version of the multiplication algorithms
	*/
	template<ttmath_uint value_size>
	void UInt<value_size>::MulTwoWords(ttmath_uint a, ttmath_uint b, ttmath_uint * result_high, ttmath_uint * result_low)
	{
	#ifdef TTMATH_PLATFORM32

		/*
			on 32bit platforms we have defined 'unsigned long long int' type known as 'ttmath_ulint' in ttmath namespace
			this type has 64 bits, then we're using only one multiplication: 32bit * 32bit = 64bit
		*/

		union ttmath_uint_
		{
			struct
			{
				ttmath_uint low;  // 32 bits
				ttmath_uint high; // 32 bits
			} u_;

			ttmath_ulint u;       // 64 bits
		} res;

		res.u = ttmath_ulint(a) * ttmath_ulint(b);     // multiply two 32bit words, the result has 64 bits

		*result_high = res.u_.high;
		*result_low  = res.u_.low;

	#else

		/*
			64 bits platforms

			we don't have a native type which has 128 bits
			then we're splitting 'a' and 'b' to 4 parts (high and low halves)
			and using 4 multiplications (with additions and carry correctness)
		*/

		ttmath_uint_ a_;
		ttmath_uint_ b_;
		ttmath_uint_ res_high1, res_high2;
		ttmath_uint_ res_low1,  res_low2;
		
		a_.u = a;
		b_.u = b;

		/*
			the multiplication is as follows (schoolbook algorithm with O(n^2) ):

                                                   32 bits         32 bits

                                             +--------------------------------+
                                             |   a_.u_.high   |   a_.u_.low   |
                                             +--------------------------------+
                                             |   b_.u_.high   |   b_.u_.low   |
            +--------------------------------+--------------------------------+
            |           res_high1.u          |           res_low1.u           |
            +--------------------------------+--------------------------------+
            |           res_high2.u          |           res_low2.u           |
            +--------------------------------+--------------------------------+

                          64 bits                          64 bits
		*/


		ttmath_uint_ temp;

		res_low1.u        = ttmath_uint(b_.u_.low) * ttmath_uint(a_.u_.low);

		temp.u            = ttmath_uint(res_low1.u_.high) + ttmath_uint(b_.u_.low) * ttmath_uint(a_.u_.high);
		res_low1.u_.high  = temp.u_.low;
		res_high1.u_.low  = temp.u_.high;
		res_high1.u_.high = 0;

		res_low2.u_.low   = 0;
		temp.u            = ttmath_uint(b_.u_.high) * ttmath_uint(a_.u_.low);
		res_low2.u_.high  = temp.u_.low;

		res_high2.u       = ttmath_uint(b_.u_.high) * ttmath_uint(a_.u_.high) + ttmath_uint(temp.u_.high);

		ttmath_uint c = AddTwoWords(res_low1.u, res_low2.u, 0, &res_low2.u);
		AddTwoWords(res_high1.u, res_high2.u, c, &res_high2.u);                 // there is no carry from here

		*result_high = res_high2.u;
		*result_low  = res_low2.u;

	#endif
	}




	/*!
	 *
	 * Division
	 *
	 *
	*/
	

	/*!
		this method calculates 64bits word a:b / 32bits c (a higher, b lower word)
		r = a:b / c and rest - remainder
		
		*
		* WARNING:
		* the c has to be suitably large for the result being keeped in one word,
		* if c is equal zero there'll be a hardware interruption (0)
		* and probably the end of your program
		*
	*/
	template<ttmath_uint value_size>
	void UInt<value_size>::DivTwoWords(ttmath_uint a, ttmath_uint b, ttmath_uint c, ttmath_uint * r, ttmath_uint * rest)
	{
	// (a < c ) for the result to be one word
	TTMATH_ASSERT( c != 0 && a < c )

	#ifdef TTMATH_PLATFORM32

		union
		{
			struct
			{
				ttmath_uint low;  // 32 bits
				ttmath_uint high; // 32 bits
			} u_;

			ttmath_ulint u;       // 64 bits
		} ab;

		ab.u_.high = a;
		ab.u_.low  = b;

		*r    = ttmath_uint(ab.u / c);
		*rest = ttmath_uint(ab.u % c);

	#else

		ttmath_uint_ c_;
		c_.u = c;


		if( a == 0 )
		{
			*r    = b / c;
			*rest = b % c;
		}
		else
		if( c_.u_.high == 0 )
		{
			// higher half of 'c' is zero
			// then higher half of 'a' is zero too (look at the asserts at the beginning - 'a' is smaller than 'c')
			ttmath_uint_ a_, b_, res_, temp1, temp2;

			a_.u = a;
			b_.u = b;

			temp1.u_.high = a_.u_.low;
			temp1.u_.low  = b_.u_.high;

			res_.u_.high  = (unsigned int)(temp1.u / c);
			temp2.u_.high = (unsigned int)(temp1.u % c);
			temp2.u_.low  = b_.u_.low;
			
			res_.u_.low  = (unsigned int)(temp2.u / c);
			*rest        = temp2.u % c;

			*r = res_.u;
		}
		else
		{
			return DivTwoWords2(a, b, c,  r,  rest);
		}

	#endif
	}


#ifdef TTMATH_PLATFORM64


	/*!
		this method is available only on 64bit platforms
		
		the same algorithm like the third division algorithm in ttmathttmath_uint.h
		but now with the radix=2^32
	*/
	template<ttmath_uint value_size>
	void UInt<value_size>::DivTwoWords2(ttmath_uint a, ttmath_uint b, ttmath_uint c, ttmath_uint * r, ttmath_uint * rest)
	{
		// a is not zero
		// c_.u_.high is not zero

		ttmath_uint_ a_, b_, c_, u_, q_;
		unsigned int u3; // 32 bit

		a_.u  = a;
		b_.u  = b;
		c_.u  = c;

		// normalizing
		ttmath_uint d = DivTwoWordsNormalize(a_, b_, c_);

		// loop from j=1 to j=0
		//   the first step (for j=2) is skipped because our result is only in one word,
		//   (first 'q' were 0 and nothing would be changed)
		u_.u_.high = a_.u_.high;
		u_.u_.low  = a_.u_.low;
		u3         = b_.u_.high;
		q_.u_.high = DivTwoWordsCalculate(u_, u3, c_);
		MultiplySubtract(u_, u3, q_.u_.high, c_);
		
		u_.u_.high = u_.u_.low;
		u_.u_.low  = u3;
		u3         = b_.u_.low;
		q_.u_.low  = DivTwoWordsCalculate(u_, u3, c_);
		MultiplySubtract(u_, u3, q_.u_.low, c_);

		*r = q_.u;

		// unnormalizing for the remainder
		u_.u_.high = u_.u_.low;
		u_.u_.low  = u3;
		*rest = DivTwoWordsUnnormalize(u_.u, d);
	}



	
	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::DivTwoWordsNormalize(ttmath_uint_ & a_, ttmath_uint_ & b_, ttmath_uint_ & c_)
	{
		ttmath_uint d = 0;

		for( ; (c_.u & TTMATH_UINT_HIGHEST_BIT) == 0 ; ++d )
		{
			c_.u = c_.u << 1;
			
			ttmath_uint bc = b_.u & TTMATH_UINT_HIGHEST_BIT; // carry from 'b'

			b_.u = b_.u << 1;
			a_.u = a_.u << 1; // carry bits from 'a' are simply skipped 

			if( bc )
				a_.u = a_.u | 1;
		}

	return d;
	}


	template<ttmath_uint value_size>
	ttmath_uint UInt<value_size>::DivTwoWordsUnnormalize(ttmath_uint u, ttmath_uint d)
	{
		if( d == 0 )
			return u;

		u = u >> d;

	return u;
	}


	template<ttmath_uint value_size>
	unsigned int UInt<value_size>::DivTwoWordsCalculate(ttmath_uint_ u_, unsigned int u3, ttmath_uint_ v_)
	{
	bool next_test;
	ttmath_uint_ qp_, rp_, temp_;

		qp_.u = u_.u / ttmath_uint(v_.u_.high);
		rp_.u = u_.u % ttmath_uint(v_.u_.high);

		TTMATH_ASSERT( qp_.u_.high==0 || qp_.u_.high==1 )

		do
		{
			bool decrease = false;

			if( qp_.u_.high == 1 )
				decrease = true;
			else
			{
				temp_.u_.high = rp_.u_.low;
				temp_.u_.low  = u3;

				if( qp_.u * ttmath_uint(v_.u_.low) > temp_.u )
					decrease = true;
			}
			
			next_test = false;

			if( decrease )
			{
				--qp_.u;
				rp_.u += v_.u_.high;

				if( rp_.u_.high == 0 ) 
					next_test = true;
			}
		}
		while( next_test );

	return qp_.u_.low;
	}


	template<ttmath_uint value_size>
	void UInt<value_size>::MultiplySubtract(ttmath_uint_ & u_, unsigned int & u3, unsigned int & q, ttmath_uint_ v_)
	{
	ttmath_uint_ temp_;
		
		ttmath_uint res_high;
		ttmath_uint res_low;

		MulTwoWords(v_.u, q, &res_high, &res_low);

		ttmath_uint_ sub_res_high_;
		ttmath_uint_ sub_res_low_;

		temp_.u_.high = u_.u_.low;
		temp_.u_.low  = u3;

		ttmath_uint c = SubTwoWords(temp_.u, res_low, 0, &sub_res_low_.u);
			
		temp_.u_.high = 0;
		temp_.u_.low  = u_.u_.high;
		c = SubTwoWords(temp_.u, res_high, c, &sub_res_high_.u);

		if( c )
		{
			--q;

			c = AddTwoWords(sub_res_low_.u, v_.u, 0, &sub_res_low_.u);
			AddTwoWords(sub_res_high_.u, 0, c, &sub_res_high_.u);
		}

		u_.u_.high = sub_res_high_.u_.low;
		u_.u_.low  = sub_res_low_.u_.high;
		u3         = sub_res_low_.u_.low;
	}

#endif // #ifdef TTMATH_PLATFORM64



} //namespace


#endif //ifdef TTMATH_NOASM
#endif




