"""
Project Euler Problem 54

Problem:

In the card game poker, a hand consists of five cards and are ranked, from lowest to highest, in the following way:

- **High Card**: Highest value card.
- **One Pair**: Two cards of the same value.
- **Two Pairs**: Two different pairs.
- **Three of a Kind**: Three cards of the same value.
- **Straight**: All cards are consecutive values.
- **Flush**: All cards of the same suit.
- **Full House**: Three of a kind and a pair.
- **Four of a Kind**: Four cards of the same value.
- **Straight Flush**: All cards are consecutive values of same suit.
- **Royal Flush**: Ten, Jack, Queen, King, Ace, in same suit.

The cards are valued in the order: 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the highest value wins; for example, a pair of
eights beats a pair of fives (see example 1 below). But if two ranks tie, for example, both players have a pair of
queens, then highest cards in each hand are compared (see example 4 below); if the highest cards tie then the next
highest cards are compared, and so on.

Consider the following five hands dealt to two players:

====== ================================================= ================================================== ==========
 Hand   Player 1                                          Player 2                                           Winner
====== ================================================= ================================================== ==========
 1      5H 5C 6S 7S KD Pair of Fives                      2C 3S 8S 8D TD Pair of Eights                      Player 2
 2      5D 8C 9S JS AC Highest card Ace                   2C 5C 7D 8S QH Highest card Queen                  Player 1
 3      2D 9C AS AH AC Three Aces                         3D 6D 7D TD QD Flush  with Diamonds                Player 2
 4      4D 6S 9H QH QC Pair of Queens Highest card Nine   3D 6D 7H QD QS Pair of Queens Highest card Seven   Player 1
 5      2H 2D 4C 4D 4S Full House With Three Fours        3C 3D 3S 9S 9D Full House with Three Threes        Player 1
====== ================================================= ================================================== ==========

The file, poker.txt, contains one-thousand random hands dealt to two players. Each line of the file contains ten cards
(separated by a single space): the first five are Player 1's cards and the last five are Player 2's cards. You can
assume that all hands are valid (no invalid characters or repeated cards), each player's hand is in no specific order,
and in each hand there is a clear winner.

How many hands does Player 1 win?
"""
from collections import Counter
from statistics import multimode
from typing import Sequence, Tuple

from .lib.utils import get_data_file

numerals = {
    'T': 10,
    'J': 11,
    'Q': 12,
    'K': 13,
    'A': 14,
}
numerals.update({
    str(x): x for x in range(2, 10)
})

HandType = Sequence[Tuple[int, str]]


def main() -> int:
    p1_wins = 0
    for line in get_data_file("p0054_poker.txt").splitlines():
        cards = [parse_card(x) for x in line.split()]
        p1 = sorted(cards[:5])
        p2 = sorted(cards[5:])
        v1 = assign_value(p1)
        v2 = assign_value(p2)
        print(p1, v1, p2, v2)
        if v1 > v2:
            p1_wins += 1
    return p1_wins


def parse_card(card: str) -> Tuple[int, str]:
    return numerals[card[0]], card[1]


def assign_value(hand: HandType) -> Tuple[float, int]:
    highest_card = max(card[0] for card in hand)
    if has_royal_flush(hand):
        return (9, highest_card)
    if has_straight_flush(hand):
        return (8, highest_card)
    modal_card = max(multimode(card[0] for card in hand))
    for idx, test in enumerate((
        has_four_of_a_kind,
        has_full_house,
        has_flush,
        has_straight,
        has_three_of_a_kind,
        has_two_pairs,
        has_two_of_a_kind
    )):
        if test(hand):
            return (7 - idx, modal_card)
    return (0, highest_card)


def has_royal_flush(hand: HandType) -> bool:
    suits = set(card[1] for card in hand)
    if len(suits) == 1:
        values = [card[0] for card in hand]
        return values == list(range(10, 15))
    return False


def has_straight_flush(hand: HandType) -> bool:
    return has_straight(hand) and has_flush(hand)


def has_flush(hand: HandType) -> bool:
    return len(set(card[1] for card in hand)) == 1


def has_straight(hand: HandType) -> bool:
    values = [card[0] for card in hand]
    return values == list(range(min(values), max(values) + 1))


def has_four_of_a_kind(hand: HandType) -> bool:
    return 4 in Counter(card[0] for card in hand).values()


def has_full_house(hand: HandType) -> bool:
    return has_three_of_a_kind(hand) and has_two_of_a_kind(hand)


def has_three_of_a_kind(hand: HandType) -> bool:
    return 3 in Counter(card[0] for card in hand).values()


def has_two_pairs(hand: HandType) -> bool:
    return [1, 2, 2] == sorted(Counter(card[0] for card in hand).values())


def has_two_of_a_kind(hand: HandType) -> bool:
    return 2 in Counter(card[0] for card in hand).values()
