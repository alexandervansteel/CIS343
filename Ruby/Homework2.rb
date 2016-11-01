# Alexander Vansteel
# CIS343 Ruby Homework 2
# Due Monday 2016 October 31

# 1. Strict vs Loose Name Equivalence
# A language with a strict name equivalence will create distinct aliased types,
# while a language with loose name equivalence will allow for aliased types to
# be equivalent.  A strict equivalence will consider two different aliases to be
# distinct from one another even if they are both of the same type, such as Integer.
# A loose equivalence will allow two different aliases to be compared and assigned
# to one another as long as they are the same type, such as both being Integers.

# 2. C/C++ use strict name equivalence and do not allow any comparison of two different
# structures unless they are the same structure type.

# 3. Ruby uses loose name equivalence and allows comparison of the same types
# across structures.

# 4. Ruby uses name equivalence because it allows ythe comparison of primative values
# of the same type between two different structures; however, it does not allow
# for the comparison of two different structures comprised of the same types.

Student = Struct.new(:name, :age)
Teacher = Struct.new(:name, :age)

mike = Student.new("Michael", 29)
michael = Teacher.new("Michael", 29)

# Compares string values of two different structure types.
if mike.name == michael.name
  puts "Strings are equivalent."
else
  puts "Strings are not equivalent."
end

# Compares int values of two different structure types.
if mike.age == michael.age
  puts "Integers are equivalent."
else
  puts "Integers are not equivalent."
end

# Compares two different structures comprised of the same types.
if mike == michael
  puts "Structures are equivalent."
else
  puts "Structures are not equivalent."
end
