# Advent of Code 2024: RPG Challenge
This repository contains solutions for Advent of Code 2024, presented with a unique twist: an RPG-inspired system. 
In this approach, solving puzzles becomes part of a larger challenge involving resource management, constraints, and character progression.
Instead of solving puzzles straightforwardly, you manage a limited mana pool, contend with aging as you rest, and carefully use an amulet with specific rules and restrictions.

- Mana System: Every memory allocation deducts from your mana pool.
- Amulet: Creates a custom scope where allocations won't cost mana, but each line of use wears it down, introducing loss of characters to use inside scope next time.
  - You may only use the amulet once per enemy (aoc half day)
  - You may not use it inside loops
  - You may not return early from the amulet's scope
  - Every 10 lines used will break characters, constraining the letters you can use within the amulet's scope for consequent uses, until repaired.
  - You may not exceed 25 broken characters, not even if you intend to repair it after.
- Resting and Aging:
  - Resting between puzzles restores mana but increases your character’s age.
  - You may also repair the amulet between puzzles, which won't restore mana, but will clear all broken characters from the amulet to give a fresh start to it. This action will age you the same way.
  - Your goal is to complete the challenges as young as possible.

---

| Mon | Tue | Wed | Thu | Fri | Sat | Sun |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|  |   |   |   |  | 👤🗡️ | Day 1 <br> ⏳⏳  |
| Day 2 <br> ⏳⏳ | Day 3 <br> ⏳⏳  | Day 4 <br> ⏳⏳  | Day 5 <br> ⏳⏳  | Day 6 <br> ⏳⏳  | Day 7 <br> ⏳⏳  | Day 8 <br> ⏳⏳  |
| Day 9 <br> ⏳⏳ | Day 10 <br> ⏳⏳  | Day 11 <br> ⏳⏳  | Day 12 <br> ⏳⏳  | Day 13 <br> ⏳⏳  | Day 14 <br> ⏳⏳  | Day 15 <br> ⏳⏳  |
| Day 16 <br> ⏳⏳ | Day 17 <br> ⏳⏳  | Day 18 <br> ⏳⏳  | Day 19 <br> ⏳⏳  | Day 20 <br> ⏳⏳  | Day 21 <br> ⏳⏳  | Day 22 <br> ⏳⏳  |
| Day 23 <br> ⏳⏳ |  Day 24 <br> ⏳⏳  |   Day 25 <br> ⏳⏳ |   |   |

---

![image](https://github.com/user-attachments/assets/bfe27f61-d2e6-4a98-a386-34c8ee8ed178)
