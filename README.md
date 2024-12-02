# Advent of Code 2024: RPG Challenge
This repository contains solutions for Advent of Code 2024, presented with a unique twist: an RPG-inspired system. 
In this approach, solving puzzles becomes part of a larger challenge involving resource management, constraints, and character progression.
Instead of solving puzzles straightforwardly, you manage a limited energy pool, contend with aging as you rest, and carefully use an artifact with specific rules and restrictions.

- Energy System: Every memory allocation deducts from your energy pool.
- Artifact: Creates a custom scope where allocations won't cost energy, but each line of use wears it down, introducing loss of characters to use inside scope next time.
  - You may only use the artifact once per enemy (aoc half day)
  - You may not use it inside loops
  - You may not return early from the artifact's scope
  - Every 10 lines used will break characters, constraining the letters you can use within the artifact's scope for consequent uses, until repaired.
  - You may not exceed 25 broken characters, not even if you intend to repair it after.
- Resting and Aging:
  - Resting between puzzles restores energy but increases your character’s age.
  - You may also repair the artifact between puzzles, which won't restore energy, but will clear all broken characters from the artifact to give a fresh start to it. This action will age you the same way.
  - Your goal is to complete the challenges as young as possible.

---

| Mon | Tue | Wed | Thu | Fri | Sat | Sun |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|  |   |   |   |  |    | [Day 1](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room1/Room1.cpp) <br> ⭐⭐  |
| Day 2 <br> 📜📜 | Day 3 <br> ⏳⏳  | Day 4 <br> ⏳⏳  | Day 5 <br> ⏳⏳  | Day 6 <br> ⏳⏳  | Day 7 <br> ⏳⏳  | Day 8 <br> ⏳⏳  |
| Day 9 <br> ⏳⏳ | Day 10 <br> ⏳⏳  | Day 11 <br> ⏳⏳  | Day 12 <br> ⏳⏳  | Day 13 <br> ⏳⏳  | Day 14 <br> ⏳⏳  | Day 15 <br> ⏳⏳  |
| Day 16 <br> ⏳⏳ | Day 17 <br> ⏳⏳  | Day 18 <br> ⏳⏳  | Day 19 <br> ⏳⏳  | Day 20 <br> ⏳⏳  | Day 21 <br> ⏳⏳  | Day 22 <br> ⏳⏳  |
| Day 23 <br> ⏳⏳ |  Day 24 <br> ⏳⏳  |   Day 25 <br> ⏳⏳ |   |   |

---

![image](https://github.com/user-attachments/assets/441bc3c4-85a3-4abd-a7ab-1980eee3d30a)

