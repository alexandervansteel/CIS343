# Author: Alexander Vansteel
# Assignment: Homework 3 Car Solitaire
# Due Date: 2016 November 18

# Author: Alexander Vansteel
# Purpose: Creates class Card to be used in Deck
# Inputs:
# Outputs:
# Error Handling:
class Card
  attr_accessor :rank, :suit
  def initialize(rank, suit)
    @rank = rank
    @suit = suit
  end

  def to_s
    "#{@rank} of #{@suit}"
  end
end

# Author: Alexander Vansteel
# Purpose: Creates a shuffled deck of cards
# Inputs:
# Outputs:
# Error Handling:
class Deck
  def initialize
    @ranks = %w{A 2 3 4 5 6 7 8 9 10 J Q K}
    @suits = %w{Spades Hearts Diamonds Clubs}
    @cards = []

    @ranks.each do |rank|
      @suits.each do |suit|
        @cards << Card.new(rank, suit)
      end
    end
  end

  def deal
    @cards.shift
  end

  def empty?
    @cards.empty?
  end

  def shuffle!
    @cards.shuffle!
  end

  def to_s
    result = ''
    @cards.each do |card|
      result += card.to_s + "\n"
    end
    return result
  end
end

# Author: Alexander Vansteel
# Purpose: Displays commands to User.
# Inputs:
# Outputs:
# Error Handling:
def display_rules
  puts "Initializing Game of Car Solitaire..."
  puts "User Commands:"
  puts "\tX -> Exit Game"
  puts "\tL -> Display Leaderboard"
  puts "\tD -> Display the current deck"
  puts "\tP -> Play Game"
  puts "\tH -> Play Hidden Game"
  print "Enter Command: "
end

# Author: Alexander Vansteel
# Purpose: Creates Leaderboard as a file
# Inputs:
# Outputs:
# Error Handling:
def create_leaderboard

end

# Author: Alexander Vansteel
# Purpose: Updates Leaderboard
# Inputs:
# Outputs:
# Error Handling:
def update_leaderboard

end

display_rules
u_input = gets.upcase.chomp
while u_input != "X" do
  my_deck = Deck.new
  if u_input == "D"
    puts my_deck.to_s
  end

  if u_input == "L"
    # this is where we will read and display the stupid Leaderboard file
  end

  if u_input == "P" || u_input == "H"
    # this is where the game logic will take place
  end

  display_rules
  u_input = gets.upcase.chomp
end
