# Author: Alexander Vansteel
# Assignment: Homework 3 Car Solitaire
# Due Date: 2016 November 18

# Author: Alexander Vansteel
# Purpose: Creates class Card to be used in Deck
# Inputs:
# Outputs: value of the card, overload of to_s for Card object
# Error Handling:
class Card
  attr_accessor :rank, :suit
  def initialize(rank, suit)
    @rank = rank
    @suit = suit
  end

  ##
  # returns values of the card
  def value
    if ["J", "Q", "K"].include? @rank then
      return 10
    elsif @rank == "A" then
      return 1
    else
      @rank
    end
  end

  ##
  # overloads to_s
  def to_s
    "#{@rank} of #{@suit}"
  end
end

# Author: Alexander Vansteel
# Purpose: Creates a shuffled deck of cards
# Inputs:
# Outputs: the top card, overload of to_s for Deck
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

  ##
  # returns top card on the deck and removes it from the deck
  def deal
    @cards.shift
  end

  ##
  # checks if the deck is empty
  def empty?
    @cards.empty?
  end

  ##
  # shuffles the deck
  def shuffle!
    @cards.shuffle!
  end

  ##
  # overloads to_s to print the deck
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
# Outputs: displays rules in terminal
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
# Purpose: Updates Leaderboard
# Inputs: player name, player score
# Outputs:
# Error Handling:
def update_leaderboard(name, score)
  if !(File.exist? 'Leaderboard.txt') then
    lb = File.new("Leaderboard.txt", "w+")
    lb.puts score + " " + name
    lb.close
  else
    scores = File.read('Leaderboard.txt').lines
    scores << score + " " + name
    scores.sort!
    scores.pop
    File.open("Leaderboard.txt") do |f|
      f.puts(scores)
    end
  end
end

# Author: Alexander Vansteel
# Purpose: Updates Leaderboard
# Inputs: the array of cards representing the hand
# Outputs: returns the score
# Error Handling:
def calc_score(hand)
 hand.each do |card|
   score += card.value
 end
 return score
end

##
# The Game of Car Solitaire
print "Enter name: "
name = gets.gsub(/\s+/,"").chomp

display_rules
u_input = gets.upcase.chomp
while u_input != "X" do
  my_deck = Deck.new
  hand = []

  if u_input == "D"
    puts my_deck.to_s
  end

  if u_input == "L"
    puts ">> CURRENT LEADERBOARD <<"
    if File.exist? 'Leaderboard.txt' then
      File.open('Leaderboard.txt') do |f|
        f.each_line do |line|
          puts line
        end
      end
    else
      puts "There are no records of any previous games."
    end
  end

  if u_input == "P" || u_input == "H"
    # this is where the game logic will take place
  end

  calc_score(hand)

  update_leaderboard(name, score)

  display_rules
  u_input = gets.upcase.chomp
end
