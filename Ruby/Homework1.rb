# Homework1
# Alexander Vansteel
# 2016 October 26

class String
  def hex_to_dec
    self.each_char{|char|
      if self[char] =~ /\H/
        return puts "Error: #{self[char]} is not a valid Hex digit."
      end
    }
    return puts "The Hex number #{self} is #{self.to_i(16)} in Decimal."
  end
end

print "Input a Hex number to convert to Decimal: "
u_input = gets.upcase.gsub(/\s+/,"").chomp
u_input.hex_to_dec

# The conversion will not overflow because even if the number becomes too
# big to be held in an integer value, Ruby will automatically convert the
# data type will just be converted from a Fixnum type of integer to a
# Bignum type.
